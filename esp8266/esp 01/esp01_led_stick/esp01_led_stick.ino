#include <Adafruit_NeoPixel.h>

// ── Configuration ────────────────────────────────────────────
#define LED_PIN       2       // GPIO2 — only reliable output on ESP-01
#define NUM_LEDS      8       // Number of pixels on your stick
#define EFFECT_DURATION 8000  // Milliseconds before switching to next effect
#define BRIGHTNESS    80      // Global brightness 0–255 (keep low to reduce current draw)

// ── Effect list ───────────────────────────────────────────────
// Add or remove effect names here — the rest of the code adapts automatically
enum Effect {
  FX_RAINBOW_CYCLE,
  FX_COLOR_WIPE,
  FX_THEATER_CHASE,
  FX_BREATHING,
  FX_SPARKLE,
  FX_METEOR,
  FX_COUNT  // always last — used to wrap the index
};

// ── Globals ───────────────────────────────────────────────────
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

uint8_t  currentEffect   = 0;
uint32_t effectStartTime = 0;
uint32_t lastStepTime    = 0;
uint16_t stepIndex       = 0;      // generic step counter reused by each effect

// ── Color helpers ─────────────────────────────────────────────
uint32_t wheel(uint8_t pos) {
  // Input 0–255 → smooth color wheel
  pos = 255 - pos;
  if (pos < 85)  return strip.Color(255 - pos * 3, 0,           pos * 3);
  if (pos < 170) { pos -= 85;  return strip.Color(0, pos * 3, 255 - pos * 3); }
  pos -= 170;    return strip.Color(pos * 3, 255 - pos * 3, 0);
}

// ── Effect: Rainbow cycle ─────────────────────────────────────
// Each pixel offset in the wheel so all 8 show different hues; wheel rotates
void fxRainbowCycle(uint32_t now) {
  if (now - lastStepTime < 20) return;
  lastStepTime = now;
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, wheel((i * 256 / NUM_LEDS + stepIndex) & 255));
  }
  strip.show();
  stepIndex++;
}

// ── Effect: Color wipe ────────────────────────────────────────
// Wipes through R → G → B one pixel at a time, then clears
static const uint32_t WIPE_COLORS[] = {
  0xFF0000, 0x00FF00, 0x0000FF, 0xFF6600, 0x9900FF
};
static const uint8_t WIPE_COUNT = sizeof(WIPE_COLORS) / sizeof(WIPE_COLORS[0]);

void fxColorWipe(uint32_t now) {
  if (now - lastStepTime < 80) return;
  lastStepTime = now;
  uint8_t  colorIdx = (stepIndex / (NUM_LEDS + 4)) % WIPE_COUNT;
  uint16_t phase    = stepIndex % (NUM_LEDS + 4);  // +4 pause frames
  if (phase < NUM_LEDS) {
    strip.setPixelColor(phase, WIPE_COLORS[colorIdx]);
    strip.show();
  } else if (phase == NUM_LEDS) {
    strip.clear(); strip.show();
  }
  stepIndex++;
}

// ── Effect: Theater chase ─────────────────────────────────────
// Classic every-third-pixel marquee, cycling hue slowly
void fxTheaterChase(uint32_t now) {
  if (now - lastStepTime < 60) return;
  lastStepTime = now;
  strip.clear();
  uint32_t color = wheel((stepIndex * 2) & 255);
  for (uint8_t i = stepIndex % 3; i < NUM_LEDS; i += 3) {
    strip.setPixelColor(i, color);
  }
  strip.show();
  stepIndex++;
}

// ── Effect: Breathing ─────────────────────────────────────────
// All pixels breathe in and out with a slowly shifting hue
void fxBreathing(uint32_t now) {
  if (now - lastStepTime < 16) return;
  lastStepTime = now;
  // Sine wave: stepIndex 0–255 → one full breath
  float rad   = (stepIndex % 256) * (PI / 128.0f);
  uint8_t bri = (uint8_t)((sinf(rad) + 1.0f) * 0.5f * 200.0f + 10.0f);
  uint32_t c  = wheel((stepIndex / 4) & 255);
  uint8_t r   = ((c >> 16) & 0xFF) * bri / 255;
  uint8_t g   = ((c >>  8) & 0xFF) * bri / 255;
  uint8_t b   = ( c        & 0xFF) * bri / 255;
  strip.fill(strip.Color(r, g, b));
  strip.show();
  stepIndex++;
}

// ── Effect: Sparkle ───────────────────────────────────────────
// Random pixels flash white briefly against a dark background
void fxSparkle(uint32_t now) {
  if (now - lastStepTime < 30) return;
  lastStepTime = now;
  strip.clear();
  // Light 1–2 random pixels
  uint8_t px = random(NUM_LEDS);
  uint8_t bri = random(120, 255);
  strip.setPixelColor(px, strip.Color(bri, bri, bri));
  if (random(2)) {
    strip.setPixelColor(random(NUM_LEDS), wheel(random(256)));
  }
  strip.show();
  stepIndex++;
}

// ── Effect: Meteor ────────────────────────────────────────────
// A comet-tail sweeps back and forth with fading trail
#define METEOR_SIZE   3
#define METEOR_DECAY  64   // how fast the tail fades (0=instant, 255=never)

void fxMeteor(uint32_t now) {
  if (now - lastStepTime < 40) return;
  lastStepTime = now;

  // Fade all pixels
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint32_t c = strip.getPixelColor(i);
    uint8_t r  = max(0, (int)((c >> 16) & 0xFF) - METEOR_DECAY);
    uint8_t g  = max(0, (int)((c >>  8) & 0xFF) - METEOR_DECAY);
    uint8_t b  = max(0, (int)( c        & 0xFF) - METEOR_DECAY);
    strip.setPixelColor(i, strip.Color(r, g, b));
  }

  // Draw meteor head (bounces 0 → NUM_LEDS-1 → 0)
  uint16_t period = NUM_LEDS * 2 - 2;
  uint16_t pos    = stepIndex % period;
  if (pos >= NUM_LEDS) pos = period - pos;

  uint32_t headColor = wheel((stepIndex * 3) & 255);
  for (int8_t j = 0; j < METEOR_SIZE; j++) {
    if ((int)pos - j >= 0 && (int)pos - j < NUM_LEDS) {
      strip.setPixelColor(pos - j, headColor);
    }
  }
  strip.show();
  stepIndex++;
}

// ── Effect dispatcher ─────────────────────────────────────────
void runEffect(uint8_t fx, uint32_t now) {
  switch (fx) {
    case FX_RAINBOW_CYCLE:  fxRainbowCycle(now);  break;
    case FX_COLOR_WIPE:     fxColorWipe(now);     break;
    case FX_THEATER_CHASE:  fxTheaterChase(now);  break;
    case FX_BREATHING:      fxBreathing(now);     break;
    case FX_SPARKLE:        fxSparkle(now);       break;
    case FX_METEOR:         fxMeteor(now);        break;
  }
}

// ── Setup ─────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.clear();
  strip.show();

  effectStartTime = millis();
  lastStepTime    = effectStartTime;
  stepIndex       = 0;
  currentEffect   = FX_RAINBOW_CYCLE;

  Serial.println("\nESP-01 LED Stick ready.");
  Serial.print("Effect 0: Rainbow Cycle\n");
}

// ── Main loop ─────────────────────────────────────────────────
void loop() {
  uint32_t now = millis();

  // Switch effect after EFFECT_DURATION ms
  if (now - effectStartTime >= EFFECT_DURATION) {
    currentEffect = (currentEffect + 1) % FX_COUNT;
    effectStartTime = now;
    lastStepTime    = now;
    stepIndex       = 0;
    strip.clear();
    strip.show();

    Serial.print("Switching to effect ");
    Serial.println(currentEffect);
  }

  runEffect(currentEffect, now);

  // Yield to the ESP8266 watchdog — never block with delay() in main loop
  yield();
}
