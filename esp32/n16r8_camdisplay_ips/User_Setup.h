#define USER_SETUP_INFO "ESP32S3_ST7789_CAM"

// 1. DRIVER & DIMENSIONS
#define ST7789_DRIVER
#define TFT_WIDTH  240
#define TFT_HEIGHT 240

// 2. NO CHIP SELECT (CS) PIN
#define TFT_CS   -1  // Crucial: Tells the library you don't have a CS pin

// 3. COLOR ORDER & INVERSION
#define TFT_RGB_ORDER TFT_BGR
#define TFT_INVERSION_ON // ST7789 IPS panels usually require inversion ON by default

// 4. ESP32-S3 PINS
#define TFT_MOSI 41
#define TFT_SCLK 42
#define TFT_DC   40
#define TFT_RST  39

// 5. FONTS & SPEED
#define LOAD_GLCD  
#define SPI_FREQUENCY  40000000 // ST7789 can handle much faster SPI speeds (40MHz)