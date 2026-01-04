#include <Adafruit_NeoPixel.h>

#define RGB_PIN   48     // onboard RGB LED pin
#define LED_COUNT 1

Adafruit_NeoPixel rgb(LED_COUNT, RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  rgb.begin();
  rgb.setBrightness(50);   // 0–255
  rgb.show();              // turn off initially
}

void loop() {
  // RED
  rgb.setPixelColor(0, rgb.Color(255, 0, 0));
  rgb.show();
  delay(500);

  // GREEN
  rgb.setPixelColor(0, rgb.Color(0, 255, 0));
  rgb.show();
  delay(500);

  // BLUE
  rgb.setPixelColor(0, rgb.Color(0, 0, 255));
  rgb.show();
  delay(500);

  // OFF
  rgb.clear();
  rgb.show();
  delay(500);
}
