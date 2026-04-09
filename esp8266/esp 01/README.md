# Getting Started with ESP-01

```Hardware```
- ESP-01
- USB-TTL Programmer

#### connection

| ESP-01 Pin | USB-TTL                               |
| ---------- | ------------------------------------- |
| VCC        | 3.3V ⚠️ (NOT 5V)                      |
| GND        | GND                                   |
| TX         | RX                                    |
| RX         | TX                                    |
| CH_PD / EN | 3.3V                                  |
| GPIO0      | GND (for flashing mode)               |
| GPIO2      | Leave (or pull-up 3.3V)               |
| RST        | Leave or connect to 3.3V via resistor |

Key point:

* GPIO0 → GND → Programming mode
* Remove GND → Normal run mode

#### Board Settings

* Board: Generic ESP8266 Module
* Flash Mode: DOUT
* Flash Size: 1MB
* Upload Speed: 115200 (or 9600 if error)


#### Install Board
1. Upload Steps
2. Connect GPIO0 → GND
Power ON ESP
3. Click Upload
    
#### After Upload
1. Disconnect GPIO0 from GND
2. Reset ESP → Program runs
