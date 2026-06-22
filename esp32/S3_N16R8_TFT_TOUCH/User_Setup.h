#define ILI9341_DRIVER

#define TFT_MISO 13
#define TFT_MOSI 11
#define TFT_SCLK 12
#define TFT_CS   10
#define TFT_DC    9
#define TFT_RST   8
#define TFT_BL   14
#define TFT_BACKLIGHT_ON HIGH

#define SPI_FREQUENCY  40000000
#define SPI_READ_FREQUENCY 20000000
#define SPI_TOUCH_FREQUENCY 2500000

// If touch is present:
#define TOUCH_CS 2