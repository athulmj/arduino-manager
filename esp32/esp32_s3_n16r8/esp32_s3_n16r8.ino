#include <Adafruit_NeoPixel.h>

#define RGB_PIN       48   // Standard pin for built-in LED on S3 DevKit M
#define NUMPIXELS     1    
#define DELAYVAL      500  

Adafruit_NeoPixel pixels(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // 1. Initialize Serial Communication at 115200 baud
  Serial.begin(115200);
  
  // Wait for Serial Monitor to open (useful for S3 Native USB)
  while (!Serial) { delay(10); } 

  pixels.begin(); 
  pixels.setBrightness(50); 
  randomSeed(analogRead(0)); 

  Serial.println("System Ready: Starting Random Color Blink...");
}

void loop() {
  // 2. Generate random values
  int r = random(0, 256);
  int g = random(0, 256);
  int b = random(0, 256);

  // 3. Print the values to Serial Monitor
  Serial.print("Blinking Color -> R: ");
  Serial.print(r);
  Serial.print(" | G: ");
  Serial.print(g);
  Serial.print(" | B: ");
  Serial.println(b);

  // 4. LED ON
  pixels.setPixelColor(0, pixels.Color(r, g, b));
  pixels.show();   
  delay(DELAYVAL); 

  // 5. LED OFF
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  delay(DELAYVAL); 
}
