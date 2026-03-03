#include "esp_camera.h"
#include <SPI.h>
#include <TFT_eSPI.h> 

TFT_eSPI tft = TFT_eSPI(); 

// ==========================================================
// CAMERA PIN CONFIGURATION (ESP32-S3 CAM)
// ==========================================================
#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  15
#define SIOD_GPIO_NUM   4
#define SIOC_GPIO_NUM   5

#define Y9_GPIO_NUM    16
#define Y8_GPIO_NUM    17
#define Y7_GPIO_NUM    18
#define Y6_GPIO_NUM    12
#define Y5_GPIO_NUM    10
#define Y4_GPIO_NUM     8
#define Y3_GPIO_NUM     9
#define Y2_GPIO_NUM    11
#define VSYNC_GPIO_NUM  6
#define HREF_GPIO_NUM   7
#define PCLK_GPIO_NUM  13

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing system...");

  // ==========================================================
  // TFT INITIALIZATION
  // ==========================================================
  tft.init();
  tft.setRotation(0); // 0 or 2 for square displays
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(false); // Keep this true for RGB565 byte alignment

  // ==========================================================
  // CAMERA CONFIGURATION
  // ==========================================================
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 10000000;

  config.pixel_format = PIXFORMAT_RGB565; 
  
  // NEW: Perfect 240x240 resolution for the ST7789
  config.frame_size = FRAMESIZE_240X240; 
  
  config.jpeg_quality = 12; 
  config.fb_count = 2;      
  config.fb_location = CAMERA_FB_IN_PSRAM;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x\n", err);
    tft.setTextColor(TFT_RED);
    tft.drawString("Camera Init Failed!", 10, 60, 2);
    return;
  }

  // ==========================================================
  // SENSOR STABILITY FIX
  // ==========================================================
  sensor_t * s = esp_camera_sensor_get();
  s->set_vflip(s, 1);   
  s->set_hmirror(s, 1); 
  s->set_brightness(s, 0);     
  s->set_contrast(s, 0);       
  s->set_saturation(s, 2);     
  s->set_special_effect(s, 0); 
  s->set_whitebal(s, 1);       
  s->set_exposure_ctrl(s, 1);  
  s->set_gain_ctrl(s, 1);      
  s->set_raw_gma(s, 1);
  
  Serial.println("ST7789 Camera Initialized successfully!");
}

void loop() {
  camera_fb_t *fb = esp_camera_fb_get();
  
  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }

  // Draw exactly from 0,0 since resolution matches screen size
  tft.pushImage(0, 0, fb->width, fb->height, (uint16_t *)fb->buf);

  esp_camera_fb_return(fb);
}