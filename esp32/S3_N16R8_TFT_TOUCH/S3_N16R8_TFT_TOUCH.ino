// VCC     -> 3.3V
// GND     -> GND
// MOSI -> GPIO11
// MISO -> GPIO13
// SCK  -> GPIO12
// CS   -> GPIO10
// DC   -> GPIO9
// RST  -> GPIO8
// LED  -> 3.3V
// T_CLK -> GPIO12
// T_DIN -> GPIO11
// T_DO  -> GPIO13
// T_CS  -> GPIO7
// T_IRQ -> GPIO6 (optional)

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>

#define TFT_CS    10
#define TFT_DC     9
#define TFT_RST    8

#define TOUCH_CS   7
#define TOUCH_IRQ  6

#define TFT_MOSI 11
#define TFT_MISO 13
#define TFT_SCLK 12

Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen ts(TOUCH_CS, TOUCH_IRQ);

void setup() {

  Serial.begin(115200);

  SPI.begin(TFT_SCLK, TFT_MISO, TFT_MOSI);

  tft.begin();
  tft.setRotation(3);

  ts.begin();
  ts.setRotation(4);

  tft.fillScreen(ILI9341_WHITE);

  // Clear button
  tft.fillRect(260, 0, 60, 30, ILI9341_RED);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(270, 8);
  tft.print("CLR");
}

void loop() {

  if (ts.touched()) {

    TS_Point p = ts.getPoint();

    // Adjust these values if needed
    int x = map(p.y, 200, 3800, 0, 320);
    int y = map(p.x, 200, 3800, 0, 240);

    // Shift left
    x -= 15;

    // Prevent out-of-range values
    x = constrain(x, 0, 319);
    y = constrain(y, 0, 239);

    Serial.print(x);
    Serial.print(",");
    Serial.println(y);

    // Clear screen button
    if (x > 260 && y < 30) {

      tft.fillScreen(ILI9341_WHITE);

      tft.fillRect(260, 0, 60, 30, ILI9341_RED);
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextSize(2);
      tft.setCursor(270, 8);
      tft.print("CLR");

      delay(300);
    }
    else {

      // Draw with finger
      tft.fillCircle(x, y, 2, ILI9341_BLACK);
    }
  }
}