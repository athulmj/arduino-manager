## ESP32-S3 Dev Kit M (N16R8)

The ESP32-S3 Dev Kit M is based on ESP32-S3 and comes with:
- N16 → 16 MB Flash
- R8 → 8 MB PSRAM
- Dual-core Xtensa LX7
- Wi-Fi + Bluetooth LE
- Native USB (USB-OTG)
### settings

- Tools → Board → ESP32 Arduino → ESP32S3 Dev Module
- Tools → Port → COMx

### configurations

- USB CDC On Boot → Disabled
- Upload Speed: 921600
- CPU Frequency: 240MHz (WiFi)"
- Core Debug Level: "None"
- USB DFU On Boot: "Disabled"
- Erase All Flash Before Sketch Upload: "Disabled"
- Events Run On: "Core 1"
- Flash Mode: "QIO 80MHz"
- Flash Size: "16MB (128Mb)"
- JTAG Adapter: "Disabled"
- Arduino Runs On: "Core 1"
- USB Firmware MSC On Boot: "Disabled"
- Partition Scheme: "16M Flash (3MB APP/9.9MB FATFS)"
- PSRAM: "OPI PSRAM"
- Upload Mode: "UARTO / Hardware CDC"
- Upload Speed: "921600"
- USB Mode: "Hardware CDC and JTAG"
- Zigbee Mode: "Disabled"

### Reference
- https://randomnerdtutorials.com/esp32-s3-devkitc-pinout-guide/
- https://www.circuitstate.com/tutorials/getting-started-with-esp32-s3-wi-fi-bluetooth-soc-using-esp32-s3-dev-kit-nxr8/
- https://lonelybinary.com/blogs/tinkerblock-esp32-s3-starter-kit/01_2_esp32-s3_two_usb_ports_guide
