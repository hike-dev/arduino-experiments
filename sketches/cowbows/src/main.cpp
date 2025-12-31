
// Cowboy duel (2 players)
//
// Wiring (Arduino Uno):
// - RGB LED (through resistors): R=D11, G=D10, B=D9, common -> GND (common cathode)
// - Player 1 button: D2 -> button -> GND (uses INPUT_PULLUP)
// - Player 2 button: D3 -> button -> GND (uses INPUT_PULLUP)
// - Winner LEDs: P1=D4 -> LED -> GND, P2=D5 -> LED -> GND
// - Buzzer (piezo): D6 -> buzzer -> GND

#include <Arduino.h>

#include "shared/Pinout.h"

namespace {

// --- Pins ---
constexpr uint8_t kBtnP1 = 2;
constexpr uint8_t kBtnP2 = 3;
constexpr uint8_t kP1WinLed = 4;
constexpr uint8_t kP2WinLed = 5;
constexpr uint8_t kBuzzerPin = 6;
constexpr shared::PwmPins kRgbPins{.r = 11, .g = 10, .b = 9};

// Set to true if your RGB LED is common-anode (common to +5V).
constexpr bool kRgbCommonAnode = false;

// --- Timings ---
constexpr uint16_t kDebounceMs = 30;
constexpr uint16_t kPostRoundHoldMs = 2000;

// Red (waiting) duration before switching to yellow.
constexpr uint16_t kWaitRedMs = 1200;

// Yellow (preparing) random duration range.
constexpr uint16_t kPrepareMinMs = 1200;
constexpr uint16_t kPrepareMaxMs = 5000;

// --- Colors (0..255 PWM) ---
// Keep brightness moderate for comfort.
constexpr uint8_t kBright = 140;

struct Rgb {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

constexpr Rgb kColorRed{120, 0, 0};
constexpr Rgb kColorYellow{180, 40, 0};
constexpr Rgb kColorGreen{0, 120, 0};

enum class Winner : uint8_t {
	None,
	Player1,
	Player2,
	Both,
};

uint8_t pwmLevel(uint8_t value) {
	return kRgbCommonAnode ? static_cast<uint8_t>(255 - value) : value;
}

void setRgb(const Rgb& color) {
	shared::writePwm(kRgbPins.r, pwmLevel(color.r));
	shared::writePwm(kRgbPins.g, pwmLevel(color.g));
	shared::writePwm(kRgbPins.b, pwmLevel(color.b));
}

void setWinnerLeds(Winner winner) {
	// Assumption: each LED is wired from pin -> resistor -> LED -> GND (active HIGH).
	const uint8_t p1 = (winner == Winner::Player1 || winner == Winner::Both) ? HIGH : LOW;
	const uint8_t p2 = (winner == Winner::Player2 || winner == Winner::Both) ? HIGH : LOW;
	digitalWrite(kP1WinLed, p1);
	digitalWrite(kP2WinLed, p2);
}

struct BeepStep {
	uint16_t freqHz;  // 0 = silence
	uint16_t ms;
};

template <size_t N>
constexpr uint8_t countOf(const BeepStep (&)[N]) {
	return static_cast<uint8_t>(N);
}

// Sound effects (short and simple)
constexpr BeepStep kSfxPrepare[] = {
	{880, 50},
	{0, 40},
};

constexpr BeepStep kSfxShoot[] = {
	{1400, 90},
	{0, 60},
	{1400, 90},
};

constexpr BeepStep kSfxFalseStart[] = {
	{220, 220},
	{0, 60},
	{220, 220},
};

constexpr BeepStep kSfxTie[] = {
	{600, 120},
	{0, 60},
	{600, 120},
};

constexpr BeepStep kSfxWinP1[] = {
	{1600, 180},
	{0, 60},
	{1900, 180},
};

constexpr BeepStep kSfxWinP2[] = {
	{1900, 180},
	{0, 60},
	{1600, 180},
};

struct Buzzer {
	uint8_t pin;
	const BeepStep* steps = nullptr;
	uint8_t stepCount = 0;
	uint8_t stepIndex = 0;
	unsigned long stepStartedAt = 0;
	bool playing = false;

	explicit Buzzer(uint8_t p) : pin(p) {}

	void begin() {
		shared::setupOutput(pin, LOW);
		noTone(pin);
		playing = false;
		steps = nullptr;
		stepCount = 0;
		stepIndex = 0;
		stepStartedAt = millis();
	}

	void stop() {
		noTone(pin);
		playing = false;
		steps = nullptr;
		stepCount = 0;
		stepIndex = 0;
	}

	void play(const BeepStep* newSteps, uint8_t newCount) {
		if (newSteps == nullptr || newCount == 0) {
			return;
		}
		steps = newSteps;
		stepCount = newCount;
		stepIndex = 0;
		stepStartedAt = 0;  // force immediate apply
		playing = true;
	}

	void update(unsigned long nowMs) {
		if (!playing || steps == nullptr || stepIndex >= stepCount) {
			return;
		}

		if (stepStartedAt == 0) {
			stepStartedAt = nowMs;
			const auto& s = steps[stepIndex];
			if (s.freqHz == 0) {
				noTone(pin);
			} else {
				tone(pin, s.freqHz);
			}
			return;
		}

		const auto& s = steps[stepIndex];
		if ((nowMs - stepStartedAt) >= s.ms) {
			stepIndex++;
			stepStartedAt = 0;
			if (stepIndex >= stepCount) {
				stop();
			}
		}
	}
};

struct DebouncedButton {
	uint8_t pin;
	bool stablePressed = false;
	bool lastRawPressed = false;
	unsigned long lastRawChangeAt = 0;
	bool pressedEdge = false;

	explicit DebouncedButton(uint8_t p) : pin(p) {}

	static bool readPressed(uint8_t p) {
		// INPUT_PULLUP: pressed connects pin to GND.
		return digitalRead(p) == LOW;
	}

	void begin() {
		shared::setupInputPullup(pin);
		const bool raw = readPressed(pin);
		stablePressed = raw;
		lastRawPressed = raw;
		lastRawChangeAt = millis();
		pressedEdge = false;
	}

	void update(unsigned long nowMs) {
		pressedEdge = false;
		const bool raw = readPressed(pin);
		if (raw != lastRawPressed) {
			lastRawPressed = raw;
			lastRawChangeAt = nowMs;
		}

		const bool stableTimeReached = (nowMs - lastRawChangeAt) >= kDebounceMs;
		if (stableTimeReached && raw != stablePressed) {
			stablePressed = raw;
			if (stablePressed) {
				pressedEdge = true;
			}
		}
	}
};

enum class Phase : uint8_t {
	WaitingRed,
	PreparingYellow,
	ShootingGreen,
	RoundOver,
};

DebouncedButton btn1{kBtnP1};
DebouncedButton btn2{kBtnP2};
Buzzer buzzer{kBuzzerPin};

Phase phase = Phase::RoundOver;
unsigned long phaseStartedAt = 0;
unsigned long nextRoundAllowedAt = 0;
uint16_t prepareDurationMs = 0;

bool bothReleased() { return !btn1.stablePressed && !btn2.stablePressed; }

void startRound(unsigned long nowMs) {
	phase = Phase::WaitingRed;
	phaseStartedAt = nowMs;
	prepareDurationMs = 0;
	setRgb(kColorRed);
	setWinnerLeds(Winner::None);
	Serial.println(F("Round started: WAIT (red)"));
}

void toPreparing(unsigned long nowMs) {
	phase = Phase::PreparingYellow;
	phaseStartedAt = nowMs;
	// random(min, max) is [min, max)
	prepareDurationMs = static_cast<uint16_t>(random(kPrepareMinMs, kPrepareMaxMs + 1));
	setRgb(kColorYellow);
	buzzer.play(kSfxPrepare, countOf(kSfxPrepare));
	Serial.print(F("PREPARE (yellow), ms="));
	Serial.println(prepareDurationMs);
}

void toShooting(unsigned long nowMs) {
	phase = Phase::ShootingGreen;
	phaseStartedAt = nowMs;
	setRgb(kColorGreen);
	buzzer.play(kSfxShoot, countOf(kSfxShoot));
	Serial.println(F("SHOOT (green)!"));
}

void endRound(unsigned long nowMs, Winner winner, const __FlashStringHelper* reason) {
	const bool wasShooting = (phase == Phase::ShootingGreen);
	phase = Phase::RoundOver;
	phaseStartedAt = nowMs;
	nextRoundAllowedAt = nowMs + kPostRoundHoldMs;
	setRgb(kColorRed);
	setWinnerLeds(winner);
	if (!wasShooting) {
		buzzer.play(kSfxFalseStart, countOf(kSfxFalseStart));
	} else if (winner == Winner::Player1) {
		buzzer.play(kSfxWinP1, countOf(kSfxWinP1));
	} else if (winner == Winner::Player2) {
		buzzer.play(kSfxWinP2, countOf(kSfxWinP2));
	} else {
		buzzer.play(kSfxTie, countOf(kSfxTie));
	}
	Serial.println(reason);
	Serial.println(F("Round over. Re-arming..."));
}

void handleFalseStart(unsigned long nowMs, bool p1Pressed, bool p2Pressed) {
	// Spec: pressing before green = loss.
	// If both pressed (same tick), treat as both lose.
	if (p1Pressed && p2Pressed) {
		endRound(nowMs, Winner::Both, F("FALSE START: both players"));
		return;
	}

	if (p1Pressed) {
		endRound(nowMs, Winner::Player2, F("FALSE START: player 1 loses (player 2 wins)"));
		return;
	}

	if (p2Pressed) {
		endRound(nowMs, Winner::Player1, F("FALSE START: player 2 loses (player 1 wins)"));
		return;
	}
}

void handleShot(unsigned long nowMs, bool p1Pressed, bool p2Pressed) {
	if (p1Pressed && p2Pressed) {
		endRound(nowMs, Winner::Both, F("TIE: both players shot at the same time"));
		return;
	}
	if (p1Pressed) {
		endRound(nowMs, Winner::Player1, F("WINNER: player 1"));
		return;
	}
	if (p2Pressed) {
		endRound(nowMs, Winner::Player2, F("WINNER: player 2"));
		return;
	}
}

}  // namespace

void setup() {
	shared::startSerial(115200);
	Serial.println(F("Cowboy duel"));

	shared::setupOutput(kRgbPins.r);
	shared::setupOutput(kRgbPins.g);
	shared::setupOutput(kRgbPins.b);
	shared::setupOutput(kP1WinLed);
	shared::setupOutput(kP2WinLed);
	setRgb(kColorRed);
	setWinnerLeds(Winner::None);

	btn1.begin();
	btn2.begin();
	buzzer.begin();

	// Seed randomness; A0 is usually free in this sketch.
	randomSeed(analogRead(A0));

	const unsigned long nowMs = millis();
	endRound(nowMs, Winner::None, F("Ready"));
}

void loop() {
	const unsigned long nowMs = millis();
	buzzer.update(nowMs);

	btn1.update(nowMs);
	btn2.update(nowMs);

	const bool p1Edge = btn1.pressedEdge;
	const bool p2Edge = btn2.pressedEdge;

	switch (phase) {
		case Phase::RoundOver: {
			// Re-arm when cooldown elapsed AND nobody is holding a button.
			if (nowMs >= nextRoundAllowedAt && bothReleased()) {
				startRound(nowMs);
			}
			break;
		}

		case Phase::WaitingRed: {
			if (p1Edge || p2Edge) {
				handleFalseStart(nowMs, p1Edge, p2Edge);
				break;
			}
			if ((nowMs - phaseStartedAt) >= kWaitRedMs) {
				toPreparing(nowMs);
			}
			break;
		}

		case Phase::PreparingYellow: {
			if (p1Edge || p2Edge) {
				handleFalseStart(nowMs, p1Edge, p2Edge);
				break;
			}
			if ((nowMs - phaseStartedAt) >= prepareDurationMs) {
				toShooting(nowMs);
			}
			break;
		}

		case Phase::ShootingGreen: {
			if (p1Edge || p2Edge) {
				handleShot(nowMs, p1Edge, p2Edge);
			}
			break;
		}
	}
}
