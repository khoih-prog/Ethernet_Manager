## Ethernet_Manager

[![arduino-library-badge](https://www.ardu-badge.com/badge/Ethernet_Manager.svg?)](https://www.ardu-badge.com/Ethernet_Manager)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Ethernet_Manager.svg)](https://github.com/khoih-prog/Ethernet_Manager/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/Ethernet_Manager/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Ethernet_Manager.svg)](http://github.com/khoih-prog/Ethernet_Manager/issues)

---
---

New recent features:

- **DoubleDetectDetector** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
- Configurable **Config Portal Title** to be either BoardName or default undistinguishable names.
- Examples are redesigned to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device

---

### Releases v1.1.0

1. Add support to ESP32 and ESP8266 using EEPROM, SPIFFS or LittleFS
2. Add many complex MQTT Examples to demonstrate how to use the dynamic parameters, entered via Config Portal, to connect to **ThingStream MQTT Server** at `mqtt.thingstream.io`.


### Releases v1.0.0

1. Initial coding to support SAMD21/SAMD51, nRF52, SAM DUE, Teensy.
2. Provide support to W5x00, ENC28J60 and Teensy 4.1 NativeEthernet.
3. Supporting Ethernet, EthernetLarge, Ethernet2, Ethernet3, EthernetENC, UIPEthernet and Teensy NativeEthernet Libraries


---

- This is the new library, adding to the current WiFiManager sets of libraries. It's designed to help you eliminate `hardcoding` your Credentials in **Teensy, SAM DUE, SAMD21, SAMD51, nRF52, etc. boards using Ethernet shields (W5100, W5200, W5500, ENC28J60, Teensy 4.1 NativeEthernet, etc)**. It's currently **not supporting SSL**. Will support soon.
- It's not supporting UNO/Nano/Mega and other AVR boards for not enough memory.
- You can update Credentials any time you need to change via Configure Portal. Data are saved in configurable locations in EEPROM, DueFlashStorage or FlashStorage
- Teensy LC, 2.0++ and 2.0 not supported.
- **DoubleDetectDetector** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
- Configurable **Config Portal Title** to be either BoardName or default undistinguishable names.
- Examples are redesigned to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.13+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Teensy core v1.53+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0) boards.
 3. [`Arduino SAM DUE core v1.6.12+`](https://www.arduino.cc/en/Guide/ArduinoDue) for SAM DUE ARM Cortex-M3 boards.
 4. [`Arduino SAMD core 1.8.9+`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards  (Nano 33 IoT, etc.).
 5. [`Adafruit SAMD core 1.6.4+`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Itsy-Bitsy M4, etc.)
 6. [`Seeeduino SAMD core 1.8.1+`](https://www.seeedstudio.com/) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.) 
 7. [`Adafruit nRF52 v0.21.0+`](https://www.adafruit.com/) for nRF52 boards such as AdaFruit Feather nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.
 8. [`ESP32 core 1.0.4+`](https://github.com/espressif/arduino-esp32/releases) for ESP32 boards
 9. [`ESP8266 core 2.7.4+`](https://github.com/esp8266/Arduino#installing-with-boards-manager) for ESP8266 boards. To use ESP8266 core 2.7.1+ for LittleFS. 
10. Depending on which Ethernet card you're using:
   - [`Ethernet library v2.0.0+`](https://www.arduino.cc/en/Reference/Ethernet) for W5100, W5200 and W5500.
   - [`EthernetLarge library v2.0.0+`](https://github.com/OPEnSLab-OSU/EthernetLarge) for W5100, W5200 and W5500.
   - [`Ethernet2 library v1.0.4+`](https://github.com/khoih-prog/Ethernet2) for W5500.
   - [`Ethernet3 library v1.5.3+`](https://github.com/sstaub/Ethernet3) for W5500/WIZ550io/WIZ850io/USR-ES1 with Wiznet W5500 chip.
   - [`EthernetENC library v2.0.0+`](https://github.com/jandrassy/EthernetENC) for ENC28J60. **New and Better**
   - [`UIPEthernet library v2.0.9+`](https://github.com/UIPEthernet/UIPEthernet) for ENC28J60
   - [`NativeEthernet Library version stable111+`](https://github.com/vjmuzik/NativeEthernet) for Teensy 4.1 built-in NativeEthernet
11. Depending on which board you're using:
   - [`DueFlashStorage library`](https://github.com/sebnil/DueFlashStorage) for SAM DUE
   - [`FlashStorage_SAMD library v1.0.0+`](https://github.com/khoih-prog/FlashStorage_SAMD) for SAMD (DUE, ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit CIRCUITPLAYGROUND_EXPRESS, etc.)
12. [`EthernetWebServer library v1.2.0+`](https://github.com/khoih-prog/EthernetWebServer). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer.svg?)](https://www.ardu-badge.com/EthernetWebServer).
13. [`ESP_DoubleResetDetector library v1.1.0+`](https://github.com/khoih-prog/ESP_DoubleResetDetector) for ESP32 and ESP8266.  To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_DoubleResetDetector.svg?)](https://www.ardu-badge.com/ESP_DoubleResetDetector).
14. [`DoubleResetDetector_Generic library v1.0.2+`](https://github.com/khoih-prog/DoubleResetDetector_Generic) for other boards (not ESP32 or ESP8266). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/DoubleResetDetector_Generic.svg?)](https://www.ardu-badge.com/DoubleResetDetector_Generic).
15. [`Functional-VLPP library v1.0.1+`](https://github.com/khoih-prog/functional-vlpp) to use server's lambda function. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/Functional-Vlpp.svg?)](https://www.ardu-badge.com/Functional-Vlpp)

---

### Installation

The suggested way to install is to:

#### Use Arduino Library Manager
The best way is to use `Arduino Library Manager`. Search for `Ethernet_Manager`, then select / install the latest version. You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/Ethernet_Manager.svg?)](https://www.ardu-badge.com/Ethernet_Manager) for more detailed instructions.

### Manual Install

1. Navigate to [Ethernet_Manager](https://github.com/khoih-prog/Ethernet_Manager) page.
2. Download the latest release `Ethernet_Manager-main.zip`.
3. Extract the zip file to `Ethernet_Manager-main` directory 
4. Copy the whole `Ethernet_Manager-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**Ethernet_Manager** library](https://platformio.org/lib/show/11568/Ethernet_Manager) by using [Library Manager](https://platformio.org/lib/show/11568/Ethernet_Manager/installation). Search for Ethernet_Manager in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---

### Packages' Patches

 1. **To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 0.21.0](Packages_Patches/adafruit/hardware/nrf52/0.21.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0). 

Supposing the Adafruit nRF52 version is 0.21.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

 2. **To be able to compile and run on Teensy boards**, you have to copy the file [Teensy boards.txt](Packages_Patches/hardware/teensy/avr/boards.txt) into Teensy hardware directory (./arduino-1.8.13/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.13. These files must be copied into the directory:

- `./arduino-1.8.13/hardware/teensy/avr/boards.txt`
- ***`./arduino-1.8.13/hardware/teensy/avr/cores/teensy4/Stream.h`***
- ***`./arduino-1.8.13/hardware/teensy/avr/cores/teensy3/Stream.h`***

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- ***`./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`***
- ***`./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`***

 3. **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

 4. ***To be able to compile without error and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD cores 1.8.9](Packages_Patches/arduino/hardware/samd/1.8.9) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.9).
 
Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:
- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

 5. ***To be able to automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the file [Adafruit SAMD platform.txt](Packages_Patches/adafruit/hardware/samd/1.6.4) into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.6.4). 

Supposing the Adafruit SAMD core version is 1.6.4. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.6.4/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`

 6. ***To be able to automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the file [Seeeduino SAMD platform.txt](Packages_Patches/Seeeduino/hardware/samd/1.8.1) into Adafruit samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.1). 

Supposing the Seeeduino SAMD core version is 1.8.1. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.1/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`

7. **To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/1.9.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/1.9.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 1.9.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_L053R8/variant.h`

---

### Libraries' Patches

1. If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

2. To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

3. To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)

4. To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for this [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

6. ***To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library***, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
- [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
- [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
- [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

7. To fix [`ESP32 compile error`](https://github.com/espressif/arduino-esp32), just copy the following file into the [`ESP32`](https://github.com/espressif/arduino-esp32) cores/esp32 directory (e.g. ./arduino-1.8.12/hardware/espressif/cores/esp32) to overwrite the old file:
- [Server.h](LibraryPatches/esp32/cores/esp32/Server.h)

---
---

### HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)

Please have a look at [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to have more detailed description and solution of the issue.

#### 1.  ESP32 has 2 ADCs, named ADC1 and ADC2

#### 2. ESP32 ADCs functions

- ADC1 controls ADC function for pins **GPIO32-GPIO39**
- ADC2 controls ADC function for pins **GPIO0, 2, 4, 12-15, 25-27**

#### 3.. ESP32 WiFi uses ADC2 for WiFi functions

Look in file [**adc_common.c**](https://github.com/espressif/esp-idf/blob/master/components/driver/adc_common.c#L61)

> In ADC2, there're two locks used for different cases:
> 1. lock shared with app and Wi-Fi:
>    ESP32:
>         When Wi-Fi using the ADC2, we assume it will never stop, so app checks the lock and returns immediately if failed.
>    ESP32S2:
>         The controller's control over the ADC is determined by the arbiter. There is no need to control by lock.
> 
> 2. lock shared between tasks:
>    when several tasks sharing the ADC2, we want to guarantee
>    all the requests will be handled.
>    Since conversions are short (about 31us), app returns the lock very soon,
>    we use a spinlock to stand there waiting to do conversions one by one.
> 
> adc2_spinlock should be acquired first, then adc2_wifi_lock or rtc_spinlock.


- In order to use ADC2 for other functions, we have to **acquire complicated firmware locks and very difficult to do**
- So, it's not advisable to use ADC2 with WiFi/BlueTooth (BT/BLE).
- Use ADC1, and pins GPIO32-GPIO39
- If somehow it's a must to use those pins serviced by ADC2 (**GPIO0, 2, 4, 12, 13, 14, 15, 25, 26 and 27**), use the **fix mentioned at the end** of [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to work with ESP32 WiFi/BlueTooth (BT/BLE).

---
---

### Important Notes

1. Code is restructured to provide flexibility to make it easy to support many more **Ethernet** modules/shields in the future. Please delete the *.cpp files, replaced by *.hpp files, in the src directory, if *.cpp files still exist after installing new version.

2. For **Adafruit nRF52**, use the SPI's  pin as follows:

  - SS/CS     = 10
  - SPI_MOSI  = MO(SI)
  - SPI_MISO  = MI(SO)
  - SPI_SCK   = SCK

3. For **Adafruit SAMD21/SAMD51**, use the SPI's CS/SS pin as follows:

  - Itsy-Bitsy M0/M4, Feather M0 (Express), Hallowing M0 Express, Zero, Metro M0 => use CS = 16 = pin A2
  - Feather M4 (SAMD51)   => use SS/CS = 9
  - Grand Central M4      => use SS/CS = 53
  - Hallowing M4          => use SS/CS = 10
  - Metro M4 AirLift      => use SS/CS = 36

To know the default CS/SS pins of not listed boards, check the related `variant.h` files in 

`~/.arduino15/packages/adafruit/hardware/samd/x.y.zz/variants/board_name/variant.h`

4. For **Arduino SAM DUE**, use the SPI's  pin as follows:

  - SS/CS     = 10
  - SPI_MOSI  = 75 ( pin 4 @ [ICSP connector](pics/ICSP_connector.jpg) )
  - SPI_MISO  = 74 ( pin 1 @ [ICSP connector](pics/ICSP_connector.jpg) )
  - SPI_SCK   = 76 ( pin 3 @ [ICSP connector](pics/ICSP_connector.jpg) )
  
<p align="center">
    <img src="https://github.com/khoih-prog/Ethernet_Manager/blob/main/pics/ICSP_connector.jpg">
</p>
  
---

### Configuration Notes

#### 1. How to select which built-in Ethernet or shield to use

The easiest way is to use 

```
#define USE_ETHERNET_WRAPPER    true
```

then select **one and only one** Ethernet library to use as follows:

- Standard Ethernet library is used by default, in the sketch, just be sure to comment out or leave these #defines to be false :

```
//#define USE_UIP_ETHERNET   true
#define USE_UIP_ETHERNET   false

  // Only one if the following to be true
  #define USE_ETHERNET          true
  #define USE_ETHERNET2         false
  #define USE_ETHERNET3         false
  #define USE_ETHERNET_LARGE    false
  #define USE_ETHERNET_ESP8266  false 
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false
```

- To use built-in UIPEthernet built-in or shield:

```
#define USE_UIP_ETHERNET   true
//#define USE_UIP_ETHERNET   false

  // Only one if the following to be true
  #define USE_ETHERNET          false
  #define USE_ETHERNET2         false
  #define USE_ETHERNET3         false
  #define USE_ETHERNET_LARGE    false
  #define USE_ETHERNET_ESP8266  false 
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false
```

- To use any of the custom Ethernet library, such as Ethernet2, Ethernet3, EthernetLarge:

```
#define USE_UIP_ETHERNET   true
//#define USE_UIP_ETHERNET   false

  // Only one if the following to be true
  #define USE_ETHERNET          false
  #define USE_ETHERNET2         true
  #define USE_ETHERNET3         false
  #define USE_ETHERNET_LARGE    false
  #define USE_ETHERNET_ESP8266  false 
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false
```

- To use another Ethernet library
For example, Ethernet_XYZ library uses **Ethernet_XYZ.h**

```
#define USE_UIP_ETHERNET   true
//#define USE_UIP_ETHERNET   false

  // Only one if the following to be true
  #define USE_ETHERNET          false
  #define USE_ETHERNET2         false
  #define USE_ETHERNET3         false
  #define USE_ETHERNET_LARGE    false
  #define USE_ETHERNET_ESP8266  false 
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   true
...

#include <EthernetWebServer.h>
```

---

#### Important:

- The **Ethernet_Shield_W5200, EtherCard, EtherSia  libraries are not supported**. Don't use unless you know how to modify those libraries.
- Requests to support for any future custom Ethernet library will be ignored. **Use at your own risk**.


#### 2. How to select another CS/SS pin to use

The default CS/SS pin is GPIO4(D2) for ESP8266, GPIO22 for ESP32, 10 for all other boards.

If the default pin is not corect, the easiest way is to change is to use 

```
#define USE_ETHERNET_WRAPPER    true
```

then select the CS/SS pin (e.g. 22) to use as follows:

```
// To override the default CS/SS pin. Don't use unless you know exactly which pin to use
#define USE_THIS_SS_PIN   22
```

#### 3. How to use W5x00/ENC28J60 with ESP32


These pins are tested OK with ESP32 and W5x00/ENC28J60: 

* MOSI:  GPIO23
* MISO:  GPIO19
* SCK:   GPIO18 
* CS/SS: GPIO22

```
  #define PIN_D18           18        // Pin D18 mapped to pin GPIO18/VSPI_SCK of ESP32
  #define PIN_D19           19        // Pin D19 mapped to pin GPIO19/VSPI_MISO of ESP32
  #define PIN_D23           23        // Pin D23 mapped to pin GPIO23/VSPI_MOSI of ESP32
   
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // Connection for ESP32
  // MOSI: GPIO23, MISO: GPIO19, SCK: GPIO18, CS/SS: GPIO22
  
  #ifndef USE_THIS_SS_PIN
    #define USING_M5STACK_W5500     false
    #if USING_M5STACK_W5500
      #warning Using M5Stack_Core_ESP32 with W5500 mudule
      #define USE_THIS_SS_PIN   26    // For M5Stack_Core_ESP32 with W5500 mudule
    #else
      #define USE_THIS_SS_PIN   22    // For ESP32
    #endif
  #endif

```

#### 4. How to use W5x00/ENC28J60 with ESP8266

To avoid using the default but not-working Ethernet library of ESP8266, rename the Ethernet.h/cpp to Ethernet_ESP8266.h/cpp to avoid library conflict if you're using the Arduino Ethernet library. The Ethernet2, Ethernet3, EthernetLarge library can be used without conflict.

These pins are tested OK with ESP8266 and W5x00/ENC28J60

* MOSI:   D7/GPIO13
* MISO:   D6/GPIO12
* SCK:    D5/GPIO14
* CS/SS:  D2/GPIO4

```
  #define PIN_D5            14        // Pin D5 mapped to pin GPIO14/HSCLK of ESP8266
  #define PIN_D6            12        // Pin D6 mapped to pin GPIO12/HMISO of ESP8266
  #define PIN_D7            13        // Pin D7 mapped to pin GPIO13/RXD2/HMOSI of ESP8266
  
  // Connection for ESP8266
  // MOSI: D7/GPIO13, MISO: D6/GPIO12, SCK: D5/GPIO14, CS/SS: D2/GPIO4
  
  // For ESP8266, change for other boards if necessary
  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   D2    // For ESP8266
  #endif
  
  // For ESP8266
  // Pin                D0(GPIO16)    D1(GPIO5)    D2(GPIO4)    D3(GPIO0)    D4(GPIO2)    D8
  // Ethernet           0                 X            X            X            X        0
  // Ethernet2          X                 X            X            X            X        0
  // Ethernet3          X                 X            X            X            X        0
  // EthernetLarge      X                 X            X            X            X        0
  // Ethernet_ESP8266   0                 0            0            0            0        0
  // D2 is safe to used for Ethernet, Ethernet2, Ethernet3, EthernetLarge libs
  // Must use library patch for Ethernet, EthernetLarge libraries
  //Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (USE_THIS_SS_PIN);

```

#### 5. How to increase W5x00 TX/RX buffer

- For **Ethernet3** library only,  use as follows

```
  // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
  #ifndef ETHERNET3_MAX_SOCK_NUM
    #define ETHERNET3_MAX_SOCK_NUM      4
  #endif
  
  Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
```

#### Important:

- The **Ethernet_Shield_W5200, EtherCard, EtherSia  libraries are not supported**. Don't use unless you know how to modify those libraries to make them compatible. Will do in the near future.
- Requests to support for any future custom Ethernet library will be ignored. **Use at your own risk**.

---


### How to use default Credentials and have them pre-loaded onto Config Portal

See this example and modify as necessary

1. To load [Default Credentials](examples/Ethernet_Generic/Credentials.h)
```
bool LOAD_DEFAULT_CONFIG_DATA = true;
```

2. To use system default to load "blank" when there is no valid Credentials
```
bool LOAD_DEFAULT_CONFIG_DATA = false;
```

3. Example of [Default Credentials](examples/Ethernet_Generic/Credentials.h)

```cpp
/// Start Default Config Data //////////////////

/*
typedef struct Configuration
{
  char header         [16];
  char static_IP      [16];
  char board_name     [24];
  int  checkSum;
} Ethernet_Configuration;
*/

#define TO_LOAD_DEFAULT_CONFIG_DATA      true

#if TO_LOAD_DEFAULT_CONFIG_DATA

bool LOAD_DEFAULT_CONFIG_DATA = false;

Ethernet_Configuration defaultConfig =
{
  //char header[16], dummy, not used
#if USE_SSL
  "Eth_SSL",
#else
  "Eth_NonSSL",
#endif

  // char static_IP      [16];
  //"192.168.2.230",
  // Use dynamic DHCP IP
  "",
  //char board_name     [24];
  "Air-Control",
  // terminate the list
  //int  checkSum, dummy, not used
  0
  /////////// End Default Config Data /////////////
};

#else

bool LOAD_DEFAULT_CONFIG_DATA = false;

Ethernet_Configuration defaultConfig;

#endif    // TO_LOAD_DEFAULT_CONFIG_DATA

/////////// End Default Config Data /////////////
```

---

### How to add dynamic parameters from sketch

- To add custom parameters, just modify from the example below

```
#define USE_DYNAMIC_PARAMETERS      true

/////////////// Start dynamic Credentials ///////////////

//Defined in BlynkEthernet_WM.h, <BlynkEthernet_ESP8266_WM.h>, <BlynkEthernet_ESP32 or_WM.h>
/**************************************
  #define MAX_ID_LEN                5
  #define MAX_DISPLAY_NAME_LEN      16

  typedef struct
  {
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
  } MenuItem;
**************************************/

#if USE_DYNAMIC_PARAMETERS

  #define MAX_MQTT_SERVER_LEN      34
  char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "default-mqtt-server";
  
  #define MAX_MQTT_PORT_LEN        6
  char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "1883";
  
  #define MAX_MQTT_USERNAME_LEN      34
  char MQTT_UserName  [MAX_MQTT_USERNAME_LEN + 1]   = "default-mqtt-username";
  
  #define MAX_MQTT_PW_LEN        34
  char MQTT_PW   [MAX_MQTT_PW_LEN + 1]  = "default-mqtt-password";
  
  #define MAX_MQTT_SUBS_TOPIC_LEN      34
  char MQTT_SubsTopic  [MAX_MQTT_SUBS_TOPIC_LEN + 1]   = "default-mqtt-SubTopic";
  
  #define MAX_MQTT_PUB_TOPIC_LEN       34
  char MQTT_PubTopic   [MAX_MQTT_PUB_TOPIC_LEN + 1]  = "default-mqtt-PubTopic";
  
  MenuItem myMenuItems [] =
  {
    { "mqtt", "MQTT Server",      MQTT_Server,      MAX_MQTT_SERVER_LEN },
    { "mqpt", "Port",             MQTT_Port,        MAX_MQTT_PORT_LEN   },
    { "user", "MQTT UserName",    MQTT_UserName,    MAX_MQTT_USERNAME_LEN },
    { "mqpw", "MQTT PWD",         MQTT_PW,          MAX_MQTT_PW_LEN },
    { "subs", "Subs Topics",      MQTT_SubsTopic,   MAX_MQTT_SUBS_TOPIC_LEN },
    { "pubs", "Pubs Topics",      MQTT_PubTopic,    MAX_MQTT_PUB_TOPIC_LEN },
  };
  
  uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

  MenuItem myMenuItems [] = {};
  
  uint16_t NUM_MENU_ITEMS = 0;
#endif

/////// // End dynamic Credentials ///////////

```
- If you don't need to add dynamic parameters, use the following in sketch

```
#define USE_DYNAMIC_PARAMETERS     false
```

---

### Important Notes for using Dynamic Parameters' ids

1. These ids (such as "mqtt" in example) must be **unique**.

Please be noted that the following **reserved names are already used in library**:

```
"ip"    for Static IP Address
"nm"    for Board Name
```

---
---

### Examples

 1. [AM2315_Ethernet](examples/AM2315_Ethernet)
 2. [DHT11_Ethernet](examples/DHT11_Ethernet)
 3. [Ethernet_Generic](examples/Ethernet_Generic) 
 4. [Ethernet_nRF52](examples/Ethernet_nRF52)
 5. [Ethernet_SAMD](examples/Ethernet_SAMD)
 6. [Ethernet_SAM_DUE](examples/Ethernet_SAM_DUE)
 7. [Ethernet_Teensy](examples/Ethernet_Teensy)
 8. [**MQTT_ThingStream_Ethernet_Generic**](examples/MQTT_ThingStream_Ethernet_Generic). **New**
 9. [**MQTT_ThingStream_Ethernet_nRF52**](examples/MQTT_ThingStream_Ethernet_nRF52). **New**
10. [**MQTT_ThingStream_Ethernet_SAMD**](examples/MQTT_ThingStream_Ethernet_SAMD). **New**
11. [**MQTT_ThingStream_Ethernet_SAM_DUE**](examples/MQTT_ThingStream_Ethernet_SAM_DUE). **New**
12. [**MQTT_ThingStream_Ethernet_Teensy**](examples/MQTT_ThingStream_Ethernet_Teensy). **New**

---
---

## So, how it works?

If no valid config data are stored in EEPROM, it will switch to `Configuration Mode`. Connect to access point at the IP address displayed on Terminal or Router's DHCP server as in the following picture:

<p align="center">
    <img src="https://github.com/khoih-prog/Ethernet_Manager/blob/main/pics/ConfigPortal.png">
</p>

After you connected to, for example, `192.168.2.86`, the Browser will display the following picture:

<p align="center">
    <img src="https://github.com/khoih-prog/Ethernet_Manager/blob/main/pics/ConfigPortal_DUE.png">
</p>

Enter your credentials (Blynk Servers/Tokens and Port). If you prefer static IP, input it (for example `192.168.2.220`) in the corresponding field. Otherwise, just leave it `blank` or `nothing` to use auto IP assigned by DHCP server.

<p align="center">
    <img src="https://github.com/khoih-prog/Ethernet_Manager/blob/main/pics/ConfigPortal_DUE.png">
</p>

Then click `Save`. After the  board auto-restarted, you will see if it's connected to your Blynk server successfully as in  the following picture:

<p align="center">
    <img src="https://github.com/khoih-prog/Ethernet_Manager/blob/main/pics/Saved.png">
</p>

This `ethernet_manager.run()` is not a blocking call, so you can use it for critical functions requiring in loop(). 

In operation, if Ethernet or connection is lost, `ethernet_manager.run()` will try reconnecting automatically. Therefore, `ethernet_manager.run()` must be called in the `loop()` function.

```cpp
void loop()
{
  ethernet_manager.run();
  ...
}
```

---
---

### Example [Ethernet_SAMD](examples/Ethernet_SAMD)

#### 1. File [W5500_Blynk](examples/Ethernet_SAMD/Ethernet_SAMD.ino)

```
#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"

Ethernet_Manager ethernet_manager;

IPAddress localEthernetIP;

// Use to detect W5100 shield. The linkStatus() is not working with W5100 
// in Ethernet and EthernetLarge libraries
bool isW5500 = true;

void heartBeatPrint()
{
  static int num        = 1;
  static int linkStatus = 0;
  
  localEthernetIP = Ethernet.localIP();
  
#if (USE_ETHERNET2 || USE_ETHERNET3)
  // To modify Ethernet2 library
  linkStatus = Ethernet.link();
  ET_LOGINFO3("localEthernetIP = ", localEthernetIP, ", linkStatus = ", (linkStatus == 1) ? "LinkON" : "LinkOFF" );
  
  if ( ( linkStatus == 1 ) && ((uint32_t) localEthernetIP != 0) )
#else

  // The linkStatus() is not working with W5100. Just using IP != 0.0.0.0
  // Better to use ping for W5100
  linkStatus = (int) Ethernet.linkStatus();
  ET_LOGINFO3("localEthernetIP = ", localEthernetIP, ", linkStatus = ", (linkStatus == LinkON) ? "LinkON" : "LinkOFF" );
  
  if ( ( (linkStatus == LinkON) || !isW5500 ) && ((uint32_t) localEthernetIP != 0) )
#endif
  {
    Serial.print(F("H"));
  }
  else
    Serial.print(F("F"));  

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(F(" "));
  }
}

void check_status()
{
  #define STATUS_CHECK_INTERVAL     10000L
  
  static unsigned long checkstatus_timeout = STATUS_CHECK_INTERVAL;

  // Send status report every STATUS_REPORT_INTERVAL (60) seconds: we don't need to send updates frequently if there is no status change.
  if ((millis() > checkstatus_timeout))
  {
    heartBeatPrint();
    checkstatus_timeout = millis() + STATUS_CHECK_INTERVAL;
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  while (!Serial);

  Serial.println("\nStart Ethernet_SAMD on " + String(BOARD_NAME)); 
  Serial.println("Ethernet Shield type : " + String(SHIELD_TYPE));
  Serial.println(ETHERNET_MANAGER_VERSION);

  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card


#if USE_ETHERNET_WRAPPER

  EthernetInit();

#else

  #if ( defined(USE_UIP_ETHERNET) && USE_UIP_ETHERNET )
    ET_LOGWARN(F("======== USE_UIP_ETHERNET ========"));
  #elif USE_NATIVE_ETHERNET
    ET_LOGWARN(F("======== USE_NATIVE_ETHERNET ========"));
  #elif USE_ETHERNET
    ET_LOGWARN(F("=========== USE_ETHERNET ==========="));
  #elif USE_ETHERNET2
    ET_LOGWARN(F("=========== USE_ETHERNET2 ==========="));
  #elif USE_ETHERNET3
    ET_LOGWARN(F("=========== USE_ETHERNET3 ==========="));
  #elif USE_ETHERNET_LARGE
    ET_LOGWARN(F("=========== USE_ETHERNET_LARGE ==========="));
  #elif USE_ETHERNET_ESP8266
    ET_LOGWARN(F("=========== USE_ETHERNET_ESP8266 ==========="));
  #elif USE_ETHERNET_ENC
    ET_LOGWARN(F("=========== USE_ETHERNET_ENC ==========="));  
  #else
    ET_LOGWARN(F("========================="));
  #endif
  
  ET_LOGWARN(F("Default SPI pinout:"));
  ET_LOGWARN1(F("MOSI:"), MOSI);
  ET_LOGWARN1(F("MISO:"), MISO);
  ET_LOGWARN1(F("SCK:"),  SCK);
  ET_LOGWARN1(F("SS:"),   SS);
  ET_LOGWARN(F("========================="));
  
  
  // unknown board, do nothing, use default SS = 10
  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   10    // For other boards
  #endif
  
  #if defined(BOARD_NAME)
    ET_LOGWARN3(F("Board :"), BOARD_NAME, F(", setCsPin:"), USE_THIS_SS_PIN);
  #else
    ET_LOGWARN1(F("Unknown board setCsPin:"), USE_THIS_SS_PIN);
  #endif
  
  // For other boards, to change if necessary
  #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2  || USE_ETHERNET_ENC || USE_NATIVE_ETHERNET )
    // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries
  
    Ethernet.init (USE_THIS_SS_PIN);
  
  #elif USE_ETHERNET3
    // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
    #ifndef ETHERNET3_MAX_SOCK_NUM
      #define ETHERNET3_MAX_SOCK_NUM      4
    #endif
  
    Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
  
  #elif USE_CUSTOM_ETHERNET
  
    // You have to add initialization for your Custom Ethernet here
    // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
    Ethernet.init(USE_THIS_SS_PIN);
    
  #endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )
  
#endif  //USE_ETHERNET_WRAPPER

  // Just info to know how to connect correctly
  ET_LOGWARN(F("========================="));
  ET_LOGWARN(F("Currently Used SPI pinout:"));
  ET_LOGWARN1(F("MOSI:"), MOSI);
  ET_LOGWARN1(F("MISO:"), MISO);
  ET_LOGWARN1(F("SCK:"), SCK);
  ET_LOGWARN1(F("SS:"), SS);
  
#if USE_ETHERNET3
  ET_LOGWARN1(F("SPI_CS:"), SPI_CS);
#endif
  ET_LOGWARN(F("========================="));
 
  ethernet_manager.begin();

  localEthernetIP = Ethernet.localIP();

#if (USE_ETHERNET2 || USE_ETHERNET3)
  // To modify Ethernet2 library
  if ( (uint32_t) localEthernetIP != 0 )
#else
  if ( (uint32_t) localEthernetIP != 0 )
#endif
  {
    Serial.print(F("Connected! IP address: "));
    Serial.println(localEthernetIP);
  }
  else
  {
    Serial.println(F("Ethernet not Connected! Please check."));
  }

  // Detect W5100 only in Ethernet and EthernetLarge libraries
#if ( USE_ETHERNET || USE_ETHERNET_LARGE)
  isW5500 = (Ethernet.hardwareStatus() == EthernetW5500);
  Serial.print(F("Ethernet type is "));
  Serial.println(isW5500 ? "W5500" : "W5100");
#endif
}

#if (USE_DYNAMIC_PARAMETERS)
void displayCredentials()
{
  Serial.println("\nYour stored Credentials :");

  for (int i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.println(String(myMenuItems[i].displayName) + " = " + myMenuItems[i].pdata);
  }
}

void displayCredentialsOnce()
{
  static bool displayedCredentials = false;

  if (!displayedCredentials)
  {
    for (int i = 0; i < NUM_MENU_ITEMS; i++)
    {
      if (!strlen(myMenuItems[i].pdata))
      {
        break;
      }

      if ( i == (NUM_MENU_ITEMS - 1) )
      {
        displayedCredentials = true;
        displayCredentials();
      }
    }
  }
}
#endif

void loop()
{
  ethernet_manager.run();
  
  check_status();

#if (USE_DYNAMIC_PARAMETERS)
  displayCredentialsOnce();
#endif  
}
```

#### 2. File [defines.h](examples/Ethernet_SAMD/defines.h)

```
#ifndef defines_h
#define defines_h

#if ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__) || defined(__SAMD51P19A__) || defined(__SAMD21G18A__) )
  #if defined(ETHERNET_USE_SAMD)
    #undef ETHERNET_USE_SAMD
  #endif
  #define ETHERNET_USE_SAMD           true
  #define USE_DYNAMIC_PARAMETERS      true
#else
  #error This code is designed to run on SAMD21/SAMD51 platform! Please check your Tools->Board setting.    
#endif

/* Comment this out to disable prints and save space */
#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       0
#define _ETHERNET_MANAGER_LOGLEVEL_         2

#define DRD_GENERIC_DEBUG                   true

// For SAMD
// Default pin 10 to SS/CS
#define USE_THIS_SS_PIN       10

#if ( defined(ARDUINO_SAMD_ZERO) && !defined(SEEED_XIAO_M0) )
  #define BOARD_TYPE      "SAMD Zero"
#elif defined(ARDUINO_SAMD_MKR1000)
  #define BOARD_TYPE      "SAMD MKR1000"
#elif defined(ARDUINO_SAMD_MKRWIFI1010)
  #define BOARD_TYPE      "SAMD MKRWIFI1010"
#elif defined(ARDUINO_SAMD_NANO_33_IOT)
  #define BOARD_TYPE      "SAMD NANO_33_IOT"
#elif defined(ARDUINO_SAMD_MKRFox1200)
  #define BOARD_TYPE      "SAMD MKRFox1200"
#elif ( defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) )
  #define BOARD_TYPE      "SAMD MKRWAN13X0"
#elif defined(ARDUINO_SAMD_MKRGSM1400)
  #define BOARD_TYPE      "SAMD MKRGSM1400"
#elif defined(ARDUINO_SAMD_MKRNB1500)
  #define BOARD_TYPE      "SAMD MKRNB1500"
#elif defined(ARDUINO_SAMD_MKRVIDOR4000)
  #define BOARD_TYPE      "SAMD MKRVIDOR4000"
#elif defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS)
  #define BOARD_TYPE      "SAMD ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS"
#elif defined(ADAFRUIT_FEATHER_M0_EXPRESS)
  #define BOARD_TYPE      "SAMD21 ADAFRUIT_FEATHER_M0_EXPRESS"
#elif defined(ADAFRUIT_METRO_M0_EXPRESS)
  #define BOARD_TYPE      "SAMD21 ADAFRUIT_METRO_M0_EXPRESS"
#elif defined(ADAFRUIT_CIRCUITPLAYGROUND_M0)
  #define BOARD_TYPE      "SAMD21 ADAFRUIT_CIRCUITPLAYGROUND_M0"
#elif defined(ADAFRUIT_GEMMA_M0)
  #define BOARD_TYPE      "SAMD21 ADAFRUIT_GEMMA_M0"
#elif defined(ADAFRUIT_TRINKET_M0)
  #define BOARD_TYPE      "SAMD21 ADAFRUIT_TRINKET_M0"
#elif defined(ADAFRUIT_ITSYBITSY_M0)
  #define BOARD_TYPE      "SAMD21 ADAFRUIT_ITSYBITSY_M0"
#elif defined(ARDUINO_SAMD_HALLOWING_M0)
  #define BOARD_TYPE      "SAMD21 ARDUINO_SAMD_HALLOWING_M0"
#elif defined(ADAFRUIT_METRO_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_METRO_M4_EXPRESS"
#elif defined(ADAFRUIT_GRAND_CENTRAL_M4)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_GRAND_CENTRAL_M4"
#elif defined(ADAFRUIT_FEATHER_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_FEATHER_M4_EXPRESS"
#elif defined(ADAFRUIT_ITSYBITSY_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_ITSYBITSY_M4_EXPRESS"
  #define USE_THIS_SS_PIN       10
#elif defined(ADAFRUIT_TRELLIS_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_TRELLIS_M4_EXPRESS"
#elif defined(ADAFRUIT_PYPORTAL)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYPORTAL"
#elif defined(ADAFRUIT_PYPORTAL_M4_TITANO)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYPORTAL_M4_TITANO"
#elif defined(ADAFRUIT_PYBADGE_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYBADGE_M4_EXPRESS"
#elif defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_METRO_M4_AIRLIFT_LITE"
#elif defined(ADAFRUIT_PYGAMER_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYGAMER_M4_EXPRESS"
#elif defined(ADAFRUIT_PYGAMER_ADVANCE_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYGAMER_ADVANCE_M4_EXPRESS"
#elif defined(ADAFRUIT_PYBADGE_AIRLIFT_M4)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYBADGE_AIRLIFT_M4"
#elif defined(ADAFRUIT_MONSTER_M4SK_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_MONSTER_M4SK_EXPRESS"
#elif defined(ADAFRUIT_HALLOWING_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_HALLOWING_M4_EXPRESS"
#elif defined(SEEED_WIO_TERMINAL)
  #define BOARD_TYPE      "SAMD SEEED_WIO_TERMINAL"
#elif defined(SEEED_FEMTO_M0)
  #define BOARD_TYPE      "SAMD SEEED_FEMTO_M0"
#elif defined(SEEED_XIAO_M0)
  #define BOARD_TYPE      "SAMD SEEED_XIAO_M0"
  #ifdef USE_THIS_SS_PIN
    #undef USE_THIS_SS_PIN
  #endif
  #define USE_THIS_SS_PIN       A1
  #warning define SEEED_XIAO_M0 USE_THIS_SS_PIN == A1
#elif defined(Wio_Lite_MG126)
  #define BOARD_TYPE      "SAMD SEEED Wio_Lite_MG126"
#elif defined(WIO_GPS_BOARD)
  #define BOARD_TYPE      "SAMD SEEED WIO_GPS_BOARD"
#elif defined(SEEEDUINO_ZERO)
  #define BOARD_TYPE      "SAMD SEEEDUINO_ZERO"
#elif defined(SEEEDUINO_LORAWAN)
  #define BOARD_TYPE      "SAMD SEEEDUINO_LORAWAN"
#elif defined(SEEED_GROVE_UI_WIRELESS)
  #define BOARD_TYPE      "SAMD SEEED_GROVE_UI_WIRELESS"
#elif defined(__SAMD21E18A__)
  #define BOARD_TYPE      "SAMD21E18A"
#elif defined(__SAMD21G18A__)
  #define BOARD_TYPE      "SAMD21G18A"
#elif defined(__SAMD51G19A__)
  #define BOARD_TYPE      "SAMD51G19A"
#elif defined(__SAMD51J19A__)
  #define BOARD_TYPE      "SAMD51J19A"
#elif defined(__SAMD51J20A__)
  #define BOARD_TYPE      "SAMD51J20A"
#elif defined(__SAM3X8E__)
  #define BOARD_TYPE      "SAM3X8E"
#elif defined(__CPU_ARC__)
  #define BOARD_TYPE      "CPU_ARC"
#elif defined(__SAMD51__)
  #define BOARD_TYPE      "SAMD51"
#else
  #define BOARD_TYPE      "SAMD Unknown"
#endif

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

#include <SPI.h>

//#define USE_ETHERNET_WRAPPER    true
#define USE_ETHERNET_WRAPPER    false

// Use true  for ENC28J60 and UIPEthernet library (https://github.com/UIPEthernet/UIPEthernet)
// Use false for W5x00 and Ethernetx library      (https://www.arduino.cc/en/Reference/Ethernet)

//#define USE_UIP_ETHERNET   true
#define USE_UIP_ETHERNET   false

// Note: To rename ESP628266 Ethernet lib files to Ethernet_ESP8266.h and Ethernet_ESP8266.cpp
// In order to USE_ETHERNET_ESP8266
#if ( !defined(USE_UIP_ETHERNET) || !USE_UIP_ETHERNET )

  // To override the default CS/SS pin. Don't use unless you know exactly which pin to use
  // You can define here or customize for each board at same place with BOARD_TYPE
  // Check @ defined(SEEED_XIAO_M0)
  //#define USE_THIS_SS_PIN   22  //21  //5 //4 //2 //15
  
  // Only one if the following to be true
  #define USE_ETHERNET          true
  #define USE_ETHERNET2         false
  #define USE_ETHERNET3         false
  #define USE_ETHERNET_LARGE    false
  #define USE_ETHERNET_ESP8266  false 
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false
  
#elif USE_UIP_ETHERNET

  #warning Using UIPEthernet library
  #define SHIELD_TYPE           "ENC28J60 using UIPEthernet Library"
#endif      // #if !USE_UIP_ETHERNET

//////////////////////////////////////////

#define EEPROM_SIZE    (2 * 1024)
// EEPROM_START + CONFIG_DATA_SIZE must be <= EEPROM_SIZE
#define EEPROM_START   0

//////////////////////////////////////////

//#define USE_SSL   true
#define USE_SSL   false

#if USE_SSL
  // Need ArduinoECCX08 and ArduinoBearSSL libraries
  // Currently, error not enough memory for UNO, Mega2560. Don't use
  #include <EthernetSSL_Manager.h>
#else
  #include <Ethernet_Manager.h>
#endif

#ifndef SHIELD_TYPE
  #define SHIELD_TYPE     "Unknown Ethernet shield/library" 
#endif

#define W5100_CS        10
#define SDCARD_CS       4

#define ETHERNET_HOST_NAME   "SAMD-Ethernet"

#endif      //defines_h
```

#### 3. File [Credentials.h](examples/Ethernet_SAMD/Credentials.h)

```
#ifndef Credentials_h
#define Credentials_h

#include "defines.h"

/// Start Default Config Data //////////////////

/*
typedef struct Configuration
{
  char header         [16];
  char static_IP      [16];
  char board_name     [24];
  int  checkSum;
} Ethernet_Configuration;
*/

#define TO_LOAD_DEFAULT_CONFIG_DATA      true

#if TO_LOAD_DEFAULT_CONFIG_DATA

bool LOAD_DEFAULT_CONFIG_DATA = false;

Ethernet_Configuration defaultConfig =
{
  //char header[16], dummy, not used
#if USE_SSL
  "Eth_SSL",
#else
  "Eth_NonSSL",
#endif

  // char static_IP      [16];
  //"192.168.2.230",
  // Use dynamic DHCP IP
  "",
  //char board_name     [24];
  "SAMD-Ethernet",
  // terminate the list
  //int  checkSum, dummy, not used
  0
  /////////// End Default Config Data /////////////
};

#else

bool LOAD_DEFAULT_CONFIG_DATA = false;

Ethernet_Configuration defaultConfig;

#endif    // TO_LOAD_DEFAULT_CONFIG_DATA

/////////// End Default Config Data /////////////

#endif    //Credentials_h
```

#### 4. File [dynamicParams.h](examples/Ethernet_SAMD/dynamicParams.h)

```
#ifndef dynamicParams_h
#define dynamicParams_h

#include "defines.h"

#define USE_DYNAMIC_PARAMETERS      true

/////////////// Start dynamic Credentials ///////////////

/**************************************
  #define MAX_ID_LEN                5
  #define MAX_DISPLAY_NAME_LEN      16

  typedef struct
  {
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
  } MenuItem;
**************************************/

#if USE_DYNAMIC_PARAMETERS

  #define MAX_MQTT_SERVER_LEN      34
  char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "default-mqtt-server";
  
  #define MAX_MQTT_PORT_LEN        6
  char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "1883";
  
  #define MAX_MQTT_USERNAME_LEN      34
  char MQTT_UserName  [MAX_MQTT_USERNAME_LEN + 1]   = "default-mqtt-username";
  
  #define MAX_MQTT_PW_LEN        34
  char MQTT_PW   [MAX_MQTT_PW_LEN + 1]  = "default-mqtt-password";
  
  #define MAX_MQTT_SUBS_TOPIC_LEN      34
  char MQTT_SubsTopic  [MAX_MQTT_SUBS_TOPIC_LEN + 1]   = "default-mqtt-SubTopic";
  
  #define MAX_MQTT_PUB_TOPIC_LEN       34
  char MQTT_PubTopic   [MAX_MQTT_PUB_TOPIC_LEN + 1]  = "default-mqtt-PubTopic";
  
  MenuItem myMenuItems [] =
  {
    { "mqtt", "MQTT Server",      MQTT_Server,      MAX_MQTT_SERVER_LEN },
    { "mqpt", "Port",             MQTT_Port,        MAX_MQTT_PORT_LEN   },
    { "user", "MQTT UserName",    MQTT_UserName,    MAX_MQTT_USERNAME_LEN },
    { "mqpw", "MQTT PWD",         MQTT_PW,          MAX_MQTT_PW_LEN },
    { "subs", "Subs Topics",      MQTT_SubsTopic,   MAX_MQTT_SUBS_TOPIC_LEN },
    { "pubs", "Pubs Topics",      MQTT_PubTopic,    MAX_MQTT_PUB_TOPIC_LEN },
  };
  
  uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

  MenuItem myMenuItems [] = {};
  
  uint16_t NUM_MENU_ITEMS = 0;
#endif

/////// // End dynamic Credentials ///////////

#endif      //dynamicParams_h
```

---
---

### Debug Termimal Output Samples

1. This is the terminal output of an NRF52840_FEATHER board with W5500 Ethernet shield using Ethernet2 Library, running [Ethernet_nRF52](examples/Ethernet_nRF52) example when **no doubleResetDetected**.

#### 1. Normal run

```
Start Ethernet_nRF52 on NRF52840_FEATHER
Ethernet Shield type W5x00 using Ethernet2 Library
Ethernet_Manager v1.1.0
[ETHERNET_WEBSERVER] =========== USE_ETHERNET2 ===========
[ETHERNET_WEBSERVER] Default SPI pinout:
[ETHERNET_WEBSERVER] MOSI: 25
[ETHERNET_WEBSERVER] MISO: 24
[ETHERNET_WEBSERVER] SCK: 26
[ETHERNET_WEBSERVER] SS: 5
[ETHERNET_WEBSERVER] =========================
[ETHERNET_WEBSERVER] Board : NRF52840_FEATHER , setCsPin: 10
[ETHERNET_WEBSERVER] =========================
[ETHERNET_WEBSERVER] Currently Used SPI pinout:
[ETHERNET_WEBSERVER] MOSI: 25
[ETHERNET_WEBSERVER] MISO: 24
[ETHERNET_WEBSERVER] SCK: 26
[ETHERNET_WEBSERVER] SS: 5
[ETHERNET_WEBSERVER] =========================
[ETM] ======= Start Default Config Data =======
[ETM] Header= Eth_NonSSL , BoardName= Air-Control
[ETM] StaticIP= 
[ETM] i= 0 ,id= mqtt
[ETM] data= default-mqtt-server
[ETM] i= 1 ,id= mqpt
[ETM] data= 1883
[ETM] i= 2 ,id= user
[ETM] data= default-mqtt-username
[ETM] i= 3 ,id= mqpw
[ETM] data= default-mqtt-password
[ETM] i= 4 ,id= subs
[ETM] data= default-mqtt-SubTopic
[ETM] i= 5 ,id= pubs
[ETM] data= default-mqtt-PubTopic
[ETM] LoadCfgFile 
[ETM] OK
[ETM] LoadCredFile 
[ETM] ChkCrR: Buffer allocated, Sz= 35
[ETM] ChkCrR:pdata= new-mqtt-server ,len= 34
[ETM] ChkCrR:pdata= 1883 ,len= 6
[ETM] ChkCrR:pdata= new-mqtt-username ,len= 34
[ETM] ChkCrR:pdata= old-mqtt-password ,len= 34
[ETM] ChkCrR:pdata= old-mqtt-SubTopic ,len= 34
[ETM] ChkCrR:pdata= old-mqtt-PubTopic ,len= 34
[ETM] OK
[ETM] CrCCSum=0x 217e ,CrRCSum=0x 217e
[ETM] Buffer freed
[ETM] CCSum=0x 6e7 ,RCSum=0x 6e7
[ETM] LoadCredFile 
[ETM] CrR:pdata= new-mqtt-server ,len= 34
[ETM] CrR:pdata= 1883 ,len= 6
[ETM] CrR:pdata= new-mqtt-username ,len= 34
[ETM] CrR:pdata= old-mqtt-password ,len= 34
[ETM] CrR:pdata= old-mqtt-SubTopic ,len= 34
[ETM] CrR:pdata= old-mqtt-PubTopic ,len= 34
[ETM] OK
[ETM] CrCCSum=0x 217e ,CrRCSum=0x 217e
[ETM] Valid Stored Dynamic Data
[ETM] ======= Start Stored Config Data =======
[ETM] Header= nRF52 , BoardName= nRF52_W5500
[ETM] StaticIP= 192.168.2.222
[ETM] i= 0 ,id= mqtt
[ETM] data= new-mqtt-server
[ETM] i= 1 ,id= mqpt
[ETM] data= 1883
[ETM] i= 2 ,id= user
[ETM] data= new-mqtt-username
[ETM] i= 3 ,id= mqpw
[ETM] data= old-mqtt-password
[ETM] i= 4 ,id= subs
[ETM] data= old-mqtt-SubTopic
[ETM] i= 5 ,id= pubs
[ETM] data= old-mqtt-PubTopic
[ETM] Start connectEthernet using Static IP = 192.168.2.222
[ETM] MAC:FE-9F-FA-D8-DC-BA
[ETM] IP: 192.168.2.222
[ETM] begin:Ethernet Connected.
Connected! IP address: 192.168.2.222
H
Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = new-mqtt-username
MQTT PWD = old-mqtt-password
Subs Topics = old-mqtt-SubTopic
Pubs Topics = old-mqtt-PubTopic
```


#### 2. DoubleResetDetected

```cpp
Start Ethernet_nRF52 on NRF52840_FEATHER
Ethernet Shield type : W5x00 using Ethernet2 Library
Ethernet_Manager v1.1.0
[ETHERNET_WEBSERVER] =========== USE_ETHERNET2 ===========
[ETHERNET_WEBSERVER] Default SPI pinout:
[ETHERNET_WEBSERVER] MOSI: 25
[ETHERNET_WEBSERVER] MISO: 24
[ETHERNET_WEBSERVER] SCK: 26
[ETHERNET_WEBSERVER] SS: 5
[ETHERNET_WEBSERVER] =========================
[ETHERNET_WEBSERVER] Board : NRF52840_FEATHER , setCsPin: 10
[ETHERNET_WEBSERVER] =========================
[ETHERNET_WEBSERVER] Currently Used SPI pinout:
[ETHERNET_WEBSERVER] MOSI: 25
[ETHERNET_WEBSERVER] MISO: 24
[ETHERNET_WEBSERVER] SCK: 26
[ETHERNET_WEBSERVER] SS: 5
[ETHERNET_WEBSERVER] =========================
LittleFS Flag read = 0xd0d01234
Flag read = 0xd0d01234
doubleResetDetected
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
[ETM] =====================
[ETM] DRD. Run ConfigPortal
[ETM] =====================
[ETM] ======= Start Default Config Data =======
[ETM] Header= Eth_NonSSL , BoardName= Air-Control
[ETM] StaticIP= 
[ETM] i= 0 ,id= mqtt
[ETM] data= default-mqtt-server
[ETM] i= 1 ,id= mqpt
[ETM] data= 1883
[ETM] i= 2 ,id= user
[ETM] data= default-mqtt-username
[ETM] i= 3 ,id= mqpw
[ETM] data= default-mqtt-password
[ETM] i= 4 ,id= subs
[ETM] data= default-mqtt-SubTopic
[ETM] i= 5 ,id= pubs
[ETM] data= default-mqtt-PubTopic
[ETM] LoadCfgFile 
[ETM] OK
[ETM] LoadCredFile 
[ETM] ChkCrR: Buffer allocated, Sz= 35
[ETM] ChkCrR:pdata= new-mqtt-server ,len= 34
[ETM] ChkCrR:pdata= 1883 ,len= 6
[ETM] ChkCrR:pdata= new-mqtt-username ,len= 34
[ETM] ChkCrR:pdata= old-mqtt-password ,len= 34
[ETM] ChkCrR:pdata= old-mqtt-SubTopic ,len= 34
[ETM] ChkCrR:pdata= old-mqtt-PubTopic ,len= 34
[ETM] OK
[ETM] CrCCSum=0x 217e ,CrRCSum=0x 217e
[ETM] Buffer freed
[ETM] CCSum=0x 6e7 ,RCSum=0x 6e7
[ETM] LoadCredFile 
[ETM] CrR:pdata= new-mqtt-server ,len= 34
[ETM] CrR:pdata= 1883 ,len= 6
[ETM] CrR:pdata= new-mqtt-username ,len= 34
[ETM] CrR:pdata= old-mqtt-password ,len= 34
[ETM] CrR:pdata= old-mqtt-SubTopic ,len= 34
[ETM] CrR:pdata= old-mqtt-PubTopic ,len= 34
[ETM] OK
[ETM] CrCCSum=0x 217e ,CrRCSum=0x 217e
[ETM] Valid Stored Dynamic Data
[ETM] ======= Start Stored Config Data =======
[ETM] Header= nRF52 , BoardName= nRF52_W5500
[ETM] StaticIP= 192.168.2.222
[ETM] i= 0 ,id= mqtt
[ETM] data= new-mqtt-server
[ETM] i= 1 ,id= mqpt
[ETM] data= 1883
[ETM] i= 2 ,id= user
[ETM] data= new-mqtt-username
[ETM] i= 3 ,id= mqpw
[ETM] data= old-mqtt-password
[ETM] i= 4 ,id= subs
[ETM] data= old-mqtt-SubTopic
[ETM] i= 5 ,id= pubs
[ETM] data= old-mqtt-PubTopic
[ETM] Start connectEthernet using Static IP = 192.168.2.222
[ETM] MAC:FE-99-F8-DF-DA-BA
[ETM] IP: 192.168.2.222
[ETM] begin:Stay in CfgPortal: DRD
[ETM] CfgIP= 192.168.2.222
Connected! IP address: 192.168.2.222
H
Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = new-mqtt-username
MQTT PWD = old-mqtt-password
Subs Topics = old-mqtt-SubTopic
Pubs Topics = old-mqtt-PubTopic
HHHH

Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = new-mqtt-username
MQTT PWD = old-mqtt-password
Subs Topics = old-mqtt-SubTopic
Pubs Topics = old-mqtt-PubTopic
HHHH
```
#### 3. Config Portal started

```
[ETM] h:Repl: <!DOCTYPE html><html><head><title>Ethernet_NRF52_Manager</title><style>div,input{padding:2px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.5rem;margin:0px;}</style></head><div style='text-align:left;display:inline-block;min-width:260px;'><fieldset><div><label>StaticIP</label><input value='[[ip]]'id='ip'><div></div></div></fieldset><fieldset><div><label>Board Name</label><input value='[[nm]]'id='nm'><div></div></div></fieldset><fieldset><div><label>MQTT Server</label><input value='[[mqtt]]'id='mqtt'><div></div></div><div><label>Port</label><input value='[[mqpt]]'id='mqpt'><div></div></div><div><label>MQTT UserName</label><input value='[[user]]'id='user'><div></div></div><div><label>MQTT PWD</label><input value='[[mqpw]]'id='mqpw'><div></div></div><div><label>Subs Topics</label><input value='[[subs]]'id='subs'><div></div></div><div><label>Pubs Topics</label><input value='[[pubs]]'id='pubs'><div></div></div></fieldset><button onclick="sv()">Save</button></div><script id="jsbin-javascript">function udVal(key,val){var request=new XMLHttpRequest();var url='/?key='+key+'&value='+encodeURIComponent(val);request.open('GET',url,false);request.send(null);}function sv(){udVal('ip',document.getElementById('ip').value);udVal('nm',document.getElementById('nm').value);udVal('mqtt',document.getElementById('mqtt').value);udVal('mqpt',document.getElementById('mqpt').value);udVal('user',document.getElementById('user').value);udVal('mqpw',document.getElementById('mqpw').value);udVal('subs',document.getElementById('subs').value);udVal('pubs',document.getElementById('pubs').value);alert('Updated');}</script></html>
[ETM] h1:myMenuItems[ 0 ]= new-mqtt-server
[ETM] h1:myMenuItems[ 1 ]= 1883
[ETM] h1:myMenuItems[ 2 ]= new-mqtt-username
[ETM] h1:myMenuItems[ 3 ]= old-mqtt-password
[ETM] h1:myMenuItems[ 4 ]= old-mqtt-SubTopic
[ETM] h1:myMenuItems[ 5 ]= old-mqtt-PubTopic
HHHHH HHHHHHH
```

#### 4. Credentials entered and Saved

```
[ETM] h:items updated = 0
[ETM] h:key = ip , value = 192.168.2.223
[ETM] h:ip
[ETM] h:items updated = 1
[ETM] h:key = nm , value = nRF52_W5500
[ETM] h:nm
[ETM] h:items updated = 2
[ETM] h:key = mqtt , value = new-mqtt-server
[ETM] h2:myMenuItems[ 0 ]= new-mqtt-server
[ETM] h:items updated = 3
[ETM] h:key = mqpt , value = 1883
[ETM] h2:myMenuItems[ 1 ]= 1883
[ETM] h:items updated = 4
[ETM] h:key = user , value = new-mqtt-username
[ETM] h2:myMenuItems[ 2 ]= new-mqtt-username
[ETM] h:items updated = 5
[ETM] h:key = mqpw , value = old-mqtt-password
[ETM] h2:myMenuItems[ 3 ]= old-mqtt-password
[ETM] h:items updated = 6
[ETM] h:key = subs , value = old-mqtt-SubTopic
[ETM] h2:myMenuItems[ 4 ]= old-mqtt-SubTopic
[ETM] h:items updated = 7
[ETM] h:key = pubs , value = old-mqtt-PubTopic
[ETM] h2:myMenuItems[ 5 ]= old-mqtt-PubTopic
[ETM] h:Updating EEPROM. Please wait for reset
[ETM] SaveCfgFile 
[ETM] WCSum=0x 6e8
[ETM] OK
[ETM] SaveBkUpCfgFile 
[ETM] OK
[ETM] SaveCredFile 
[ETM] CW1:pdata= new-mqtt-server ,len= 34
[ETM] CW1:pdata= 1883 ,len= 6
[ETM] CW1:pdata= new-mqtt-username ,len= 34
[ETM] CW1:pdata= old-mqtt-password ,len= 34
[ETM] CW1:pdata= old-mqtt-SubTopic ,len= 34
[ETM] CW1:pdata= old-mqtt-PubTopic ,len= 34
[ETM] OK
[ETM] CrWCSum= 217e
[ETM] SaveBkUpCredFile 
[ETM] CW2:pdata= new-mqtt-server ,len= 34
[ETM] CW2:pdata= 1883 ,len= 6
[ETM] CW2:pdata= new-mqtt-username ,len= 34
[ETM] CW2:pdata= old-mqtt-password ,len= 34
[ETM] CW2:pdata= old-mqtt-SubTopic ,len= 34
[ETM] CW2:pdata= old-mqtt-PubTopic ,len= 34
[ETM] OK
[ETM] h:Rst

```

---

2. This is the terminal output of an SeeedStudio SAMD21 SEEED_XIAO_M0 board with W5500 Ethernet shield using Ethernet2 Library, running [Ethernet_SAMD](examples/Ethernet_SAMD) example when **no doubleResetDetected**.

```
Start Ethernet_SAMD on SEEED_XIAO_M0
Ethernet Shield type : W5x00 using Ethernet Library
Ethernet_Manager v1.1.0
Flag read = 0xffffffff
No doubleResetDetected
SetFlag write = 0xd0d01234
[ETM] ======= Start Default Config Data =======
[ETM] Header= Eth_NonSSL , BoardName= Air-Control
[ETM] StaticIP= 
[ETM] i= 0 ,id= mqtt
[ETM] data= default-mqtt-server
[ETM] i= 1 ,id= mqpt
[ETM] data= 1883
[ETM] i= 2 ,id= user
[ETM] data= default-mqtt-username
[ETM] i= 3 ,id= mqpw
[ETM] data= default-mqtt-password
[ETM] i= 4 ,id= subs
[ETM] data= default-mqtt-SubTopic
[ETM] i= 5 ,id= pubs
[ETM] data= default-mqtt-PubTopic
[ETM] ChkCrR:CrCCSum=0x af50 ,CrRCSum=0x ffffffff
[ETM] CCSum=0x 0 ,RCSum=0x 0
[ETM] Invalid Stored Dynamic Data. Load default from Sketch
[ETM] SaveEEPROM,Sz= 1024
[ETM] DataSz= 0 ,WCSum=0x 71e
[ETM] pdata= default-mqtt-server ,len= 34
[ETM] pdata= 1883 ,len= 6
[ETM] pdata= default-mqtt-username ,len= 34
[ETM] pdata= default-mqtt-password ,len= 34
[ETM] pdata= default-mqtt-SubTopic ,len= 34
[ETM] pdata= default-mqtt-PubTopic ,len= 34
[ETM] CrCCSum=0x 29a6
[ETM] Header= SAMD , BoardName= Air-Control
[ETM] StaticIP= 
[ETM] i= 0 ,id= mqtt
[ETM] data= default-mqtt-server
[ETM] i= 1 ,id= mqpt
[ETM] data= 1883
[ETM] i= 2 ,id= user
[ETM] data= default-mqtt-username
[ETM] i= 3 ,id= mqpw
[ETM] data= default-mqtt-password
[ETM] i= 4 ,id= subs
[ETM] data= default-mqtt-SubTopic
[ETM] i= 5 ,id= pubs
[ETM] data= default-mqtt-PubTopic
[ETM] Start connectEthernet using DHCP
[ETM] MAC:FE-9A-F4-DB-DC-BA

W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 1
W5100::init: W5500, SSIZE =4096
Done
[ETM] IP: 192.168.2.199
[ETM] begin:Stay in CfgPortal: No CfgDat
[ETM] CfgIP= 192.168.2.199
Connected! IP address: 192.168.2.199

Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
HStop doubleResetDetecting
ClearFlag write = 0xd0d04321
```

---

3. This is the terminal output of an Arduino SAM DUE board with W5100 Ethernet shield using EthernetLarge Library, running [Ethernet_SAM_DUE](examples/Ethernet_SAM_DUE) example when **no doubleResetDetected**.

```

Start Ethernet_SAM_DUE on SAM DUE
Ethernet Shield type : W5x00 using EthernetLarge Library
Ethernet_Manager v1.1.0
Flag read = 0xd0d01234
doubleResetDetected
ClearFlag write = 0xd0d04321
[ETM] =====================
[ETM] DRD. Run ConfigPortal
[ETM] =====================
[ETM] ======= Start Default Config Data =======
[ETM] Header=  , BoardName= 
[ETM] StaticIP= 
[ETM] Invalid Stored Dynamic Data. Load default from Sketch
[ETM] Header= SAMDUE , BoardName= 
[ETM] StaticIP= 
[ETM] Start connectEthernet using DHCP
[ETM] MAC:FE-9A-FD-DB-DE-BA
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 10
W5100::init: W5100, SSIZE =4096
[ETM] IP: 192.168.2.228
[ETM] begin:Stay in CfgPortal: DRD
[ETM] CfgIP= 192.168.2.228
Connected! IP address: 192.168.2.228
Ethernet type is W5100

Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
HHH[ETM] h:Updating EEPROM. Please wait for reset
⸮
Start Ethernet_SAM_DUE on SAM DUE
Ethernet Shield type : W5x00 using EthernetLarge Library
Ethernet_Manager v1.1.0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[ETM] ======= Start Default Config Data =======
[ETM] Header=  , BoardName= 
[ETM] StaticIP= 
[ETM] Header= SAMDUE , BoardName= DUE_ETM
[ETM] StaticIP= 192.168.2.222
[ETM] Start connectEthernet using Static IP = 192.168.2.222
[ETM] MAC:FE-9A-FD-DD-D9-BA

W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 10
W5100::init: W5100, SSIZE =4096
[ETM] IP: 192.168.2.222
[ETM] begin:Ethernet Connected.
Connected! IP address: 192.168.2.222
Ethernet type is W5100

Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH

```

---

4. This is the terminal output of ESP8266_NODEMCU board with W5x00 using Ethernet2 Library, running complex [MQTT_ThingStream_Ethernet_Generic](examples/MQTT_ThingStream_Ethernet_Generic) example to demonstrate how to use dynamic parameters, entered via Config Portal, to connect to [**ThingStream MQTT Server**](mqtt.thingstream.io).

#### 1.Normal run without correct ThingStream MQTT Credentials

If no valid config data are stored in EEPROM, it will switch to `Configuration Mode`. Connect to access point at the IP address displayed on Terminal or Router's DHCP server as in the following picture:

<p align="center">
    <img src="https://github.com/khoih-prog/Ethernet_Manager/blob/main/pics/MQTT_ConfigPortal_blank.png">
</p>


```
Start MQTT_ThingStream_Ethernet_Generic using LittleFS on ESP8266_NODEMCU
Ethernet Shield type : W5x00 using Ethernet2 Library
Ethernet_Manager v1.1.0
=========================
Currently Used SPI pinout:
MOSI:13
MISO:12
SCK:14
SS:15
=========================
LittleFS Flag read = 0xd0d04321
No doubleResetDetected
Saving config file...
Saving config file OK
[ETM] ======= Start Default Config Data =======
[ETM] Header= Eth_NonSSL , BoardName= Generic-Ethernet
[ETM] StaticIP= 
[ETM] CCSum=0x 9a7 ,RCSum=0x 9a7
[ETM] Invalid Stored Dynamic Data. Load default from Sketch
[ETM] Header= ESP8266 , BoardName= Generic-Ethernet
[ETM] StaticIP= 
[ETM] Start connectEthernet using DHCP
[ETM] MAC:FE-AB-CD-EF-ED-BA
[ETM] IP: 192.168.2.62
[ETM] begin:Stay in CfgPortal: No CfgDat
[ETM] CfgIP= 192.168.2.62
Connected! IP address: 192.168.2.62
***************************************
esp32-sniffer/12345678/ble
***************************************
Stop doubleResetDetecting
Saving config file...
Saving config file OK
[ETM] h:Updating LittleFS: /etm_config.dat
[ETM] h:Rst
```


#### 2. Got correct ThingStream MQTT Credentials from Config Portal

Enter your credentials (Blynk Servers/Tokens and Port). If you prefer static IP, input it (for example `192.168.2.220`) in the corresponding field. Otherwise, just leave it `blank` or `nothing` to use auto IP assigned by DHCP server.

<p align="center">
    <img src="https://github.com/khoih-prog/Ethernet_Manager/blob/main/pics/MQTT_ConfigPortal_ESP8266.png">
</p>

```
Start MQTT_ThingStream_Ethernet_Generic using LittleFS on ESP8266_NODEMCU
Ethernet Shield type : W5x00 using Ethernet2 Library
Ethernet_Manager v1.1.0
=========================
Currently Used SPI pinout:
MOSI:13
MISO:12
SCK:14
SS:15
=========================
LittleFS Flag read = 0xd0d04321
No doubleResetDetected
Saving config file...
Saving config file OK
[ETM] ======= Start Default Config Data =======
[ETM] Header= Eth_NonSSL , BoardName= Generic-Ethernet
[ETM] StaticIP= 
[ETM] CCSum=0x 975 ,RCSum=0x 975
[ETM] ======= Start Stored Config Data =======
[ETM] Header= ESP8266 , BoardName= ESP8266-Ethernet
[ETM] StaticIP= 192.168.2.222
[ETM] Start connectEthernet using Static IP = 192.168.2.222
[ETM] MAC:FE-AB-CD-EF-ED-BA
[ETM] IP: 192.168.2.222
[ETM] begin:Ethernet Connected.
Connected! IP address: 192.168.2.222
***************************************
esp32-sniffer/12345678/ble
***************************************
Attempting MQTT connection to mqtt.thingstream.io
...connected
Published connection message successfully!
Subcribed to: esp32-sniffer/12345678/ble

Your stored Credentials :
MQTT Server = mqtt.thingstream.io
Port = 1883
MQTT UserName = user_name
MQTT PWD = user_pwd
Client ID = client_ID
HStop doubleResetDetecting
Saving config file...
Saving config file OK

MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTT_ThingStream on ESP8266_NODEMCU with W5x00 using Ethernet2 Library
H
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTT_ThingStream on ESP8266_NODEMCU with W5x00 using Ethernet2 Library
H
```

---

5. This is the terminal output of NRF52840_FEATHER board with ENC28J60 using EthernetENC Library, running complex [MQTT_ThingStream_Ethernet_Generic](examples/MQTT_ThingStream_Ethernet_Generic) example to demonstrate how to use dynamic parameters, entered via Config Portal, to connect to [**ThingStream MQTT Server**](mqtt.thingstream.io).

#### 1.Normal run without correct ThingStream MQTT Credentials

```
Start MQTT_ThingStream_Ethernet_Generic on NRF52840_FEATHER
Ethernet Shield type : ENC28J60 using EthernetENC Library
Ethernet_Manager v1.1.0
LittleFS Flag read = 0xd0d01234
Flag read = 0xd0d01234
doubleResetDetected
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
[ETM] =====================
[ETM] DRD. Run ConfigPortal
[ETM] =====================
[ETM] ======= Start Default Config Data =======
[ETM] Header= Eth_NonSSL , BoardName= nRF52-Ethernet
[ETM] StaticIP= 
[ETM] CCSum=0x 7a6 ,RCSum=0x 7a6
[ETM] ======= Start Stored Config Data =======
[ETM] Header= nRF52 , BoardName= nRF52-Ethernet
[ETM] StaticIP= 
[ETM] Start connectEthernet using DHCP
[ETM] MAC:FE-33-78-EF-ED-BA
[ETM] IP: 192.168.2.89
[ETM] begin:Stay in CfgPortal: DRD
[ETM] CfgIP= 192.168.2.89
Connected! IP address: 192.168.2.89
***************************************
esp32-sniffer/12345678/ble
***************************************
[ETM] h:Updating EEPROM. Please wait for reset
[ETM] h:Rst

```

#### 2. Got correct ThingStream MQTT Credentials from Config Portal

```
Start MQTT_ThingStream_Ethernet_Generic on NRF52840_FEATHER
Ethernet Shield type : ENC28J60 using EthernetENC Library
Ethernet_Manager v1.1.0
LittleFS Flag read = 0xd0d04321
Flag read = 0xd0d04321
No doubleResetDetected
Saving DOUBLERESETDETECTOR_FLAG to DRD file : 0xd0d01234
Saving DRD file OK
SetFlag write = 0xd0d01234
[ETM] ======= Start Default Config Data =======
[ETM] Header= Eth_NonSSL , BoardName= nRF52-Ethernet
[ETM] StaticIP= 
[ETM] CCSum=0x 8d3 ,RCSum=0x 8d3
[ETM] ======= Start Stored Config Data =======
[ETM] Header= nRF52 , BoardName= nRF52-Ethernet
[ETM] StaticIP= 192.168.2.222
[ETM] Start connectEthernet using Static IP = 192.168.2.222
[ETM] MAC:FE-33-78-EF-ED-BA
[ETM] IP: 192.168.2.222
[ETM] begin:Ethernet Connected.
Connected! IP address: 192.168.2.222
***************************************
esp32-sniffer/12345678/ble
***************************************
Attempting MQTT connection to mqtt.thingstream.io
...connected
Published connection message successfully!
Subcribed to: esp32-sniffer/12345678/ble

Your stored Credentials :
MQTT Server = mqtt.thingstream.io
Port = 1883
MQTT UserName = I7UPHZWCKHZASRDIOME9
MQTT PWD = k8UJuIOtke4yXeF1lY9mXbbCxTovHAAgE3CViJ/4
Client ID = device:352fc9a7-3211-4e46-8a9a-a390f2e4ca86
HStop doubleResetDetecting
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321

MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTT_ThingStream on NRF52840_FEATHER with ENC28J60 using EthernetENC Library
H
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTT_ThingStream on NRF52840_FEATHER with ENC28J60 using EthernetENC Library
H
```
---
---

### Releases v1.1.0

1. Add support to ESP32 and ESP8266 using EEPROM, SPIFFS or LittleFS
2. Add many complex MQTT Examples to demonstrate how to use the dynamic parameters, entered via Config Portal, to connect to **ThingStream MQTT Server** at `mqtt.thingstream.io`.


### Releases v1.0.0

1. Initial coding to support SAMD21/SAMD51, nRF52, SAM DUE, Teensy.
2. Provide support to W5x00, ENC28J60 and Teensy 4.1 NativeEthernet.
3. Supporting Ethernet, EthernetLarge, Ethernet2, Ethernet3, EthernetENC, UIPEthernet and Teensy NativeEthernet Libraries

---

#### Supporting Boards

This [**Ethernet_Manager** library](https://github.com/khoih-prog/Ethernet_Manager) currently supports these following boards:

 1. **nRF52 boards**, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**
 2. **SAM DUE**
 3. **SAMD21**
  - Arduino SAMD21: ZERO, MKRs, NANO_33_IOT, etc.
  - Adafruit SAMD21 (M0): ItsyBitsy M0, Feather M0, Feather M0 Express, Metro M0 Express, Circuit Playground Express, Trinket M0, PIRkey, Hallowing M0, Crickit M0, etc.
  - Seeeduino:  LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, etc.
  
 4. **SAMD51**
  - Adafruit SAMD51 (M4): Metro M4, Grand Central M4, ItsyBitsy M4, Feather M4 Express, Trellis M4, Metro M4 AirLift Lite, MONSTER M4SK Express, Hallowing M4, etc.
  - Seeeduino: Wio Terminal, Grove UI Wireless
  
 5. **Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC)**
 6. ESP32
 7. ESP8266
 
#### Supporting Ethernet shields/modules:

1. W5x00 using [`Ethernet`](https://www.arduino.cc/en/Reference/Ethernet), [`EthernetLarge`](https://github.com/OPEnSLab-OSU/EthernetLarge), [`Ethernet2`](https://github.com/adafruit/Ethernet2) or [`Ethernet3`](https://github.com/sstaub/Ethernet3) library
2. ENC28J60 using [`EthernetENC`](https://github.com/jandrassy/EthernetENC) or [`UIPEthernet`](https://github.com/UIPEthernet/UIPEthernet) library
3. Teensy 4.1 NativeEthernet using [`NativeEthernet Library version stable111+`](https://github.com/vjmuzik/NativeEthernet).

---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level from 0 to 4

```cpp
/* Comment this out to disable prints and save space */
#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       0
#define _ETHERNET_MANAGER_LOGLEVEL_         2
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.


### Issues ###

Submit issues to: [Ethernet_Manager issues](https://github.com/khoih-prog/Ethernet_Manager/issues)

---

### TO DO

1. Same features for other boards with new Ethernet shields.
2. Add SSL/TLS feature.
3. Bug Searching and Killing
4. Support more non-compatible Ethernet Libraries such as Ethernet_Shield_W5200, EtherCard, EtherSia.

### DONE

 1. Permit EEPROM size and location configurable to avoid conflict with others.
 2. More flexible to configure reconnection timeout.
 3. For fresh config data, don't need to wait for connecting timeout before entering config portal.
 4. If the config data not entered completely (Serves, HardwarePort and Blynk tokens), entering config portal
 5. Change Synch XMLHttpRequest to Async
 6. Reduce memory usage.
 7. Support ENC28J60 as well as W5100/W5200/W5500 Ethernet shields
 8. Add checksums
 9. Support SAM DUE, SAMD, Teensy boards
10. Easy-to-use **Dynamic Parameters** without the necessity to write complicated ArduinoJSon functions
11. Permit to input special chars such as **%** and **#** into data fields.
12. Support more types of boards using Ethernet shields : **nRF52** boards, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, etc.**
Default Credentials and dynamic parameters
13. **DoubleDetectDetector** to force Config Portal when double reset is detected within predetermined time, default 10s.
14. Configurable Config Portal Title
15. Re-structure all examples to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device.
16. Add **LittleFS** support to ESP8266 as SPIFFS deprecated since **ESP8266 core 2.7.1.**
17. Add support to new [**`EthernetENC library`**](https://github.com/jandrassy/EthernetENC) for ENC28J60.
18. Add support to new [`NativeEthernet Library version stable111+`](https://github.com/vjmuzik/NativeEthernet) for Teensy 4.1.
19. Add support ESP32/ESP8266 boards
---

### Contributions and Thanks

1. Thanks to [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing.

<table>
  <tr>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>⭐️ Miguel Wisintainer</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/Ethernet_Manager/blob/main/LICENSE)

---

### Copyright

Copyright 2020- Khoi Hoang
