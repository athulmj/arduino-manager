## ESP32-C3 Super Mini

The ESP32-C3 Super Mini is a compact development board based on ESP32-C3 (RISC-V) with:

- Wi-Fi + Bluetooth LE
- Low power consumption
- USB-to-Serial built-in
- Ideal for IoT and small embedded projects
### settings

1. step 1
- File → Preferences
Add this URL in Additional Board Manager URLs:

```html
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

2. step 2
- Tools → Board → Boards Manager
- Search for esp32 → Install “esp32 by Espressif Systems”
- Tools → Board → ESP32 Arduino → ESP32C3 Dev Module
- Tools → Port → COMx

### configurations

- USB CDC On Boot → Enabled
- Upload Speed: 921600
- CPU Frequency: 160MHz
- Flash Mode: QIO
- Flash Frequency: 80MHz
- Flash Size: 4MB
- Partition Scheme: Default 4MB with spiffs

### Reference

https://randomnerdtutorials.com/getting-started-esp32-c3-super-mini/
