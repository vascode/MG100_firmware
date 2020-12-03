[![Laird Connectivity](docs/images/LairdConnnectivityLogo_Horizontal_RGB.png)](https://www.lairdconnect.com/)
# MG100 demo with BeckettLink Tank Guage

## Table of contents  
1. **[Introduction](#introduction)**
2. **[Prerequisites](#prerequisites)**
3. **[Use binary for demo](#use-binary-for-demo)**
4. **[Clone firmware source](#clone-firmware-source)**
5. **[Build firmware](#build-firmware)**
6. **[Flash firmware](#flash-firmware)**
7. **[Connect to AWS account](#connect-to-aws-account)**
8. **[Development](#development)**
9. **[Change source code](#change-source-code)**

[Programming Guide](https://www.lairdconnect.com/documentation/user-guide-programming-mg100) 

## Introduction

This page is derived from https://github.com/LairdCP/MG100_firmware which is about MG100's LTE-M demo to work with Laird BLE sensors such as BT510 and BME280. The source code is modified here so that MG100 can detect BLE advert data from BeckettLink Tank Guage and push the data to AWS IoT account. 

Below, the term "firmware" refers to Zephyr firmware for running demo app, unless it is specifically stated HL7800 firmware.

Firmware can be flashed through UART, BLE or SWD (Serial Wire Debug) 

## Prerequisites
* [MG100](https://www.lairdconnect.com/iot-devices/iot-gateways/sentrius-mg100-gateway-lte-mnb-iot-and-bluetooth-5) with HL7800 firmware v4.3.14.0 or later
* [BeckettLink Tank Guage](https://www.beckettcorp.com/product/beckettlink-tank-gauge/)
* Micro USB cable
* If using SWD for firmware upgrade : 
  * [Segger J-Link debugger](https://www.segger.com/products/debug-probes/j-link/models/model-overview/) (The J-Link Base or J-Link Base Compact is recommended) 
  * Programming adapter ([Tag-Connect TC2030-IDC](https://www.tag-connect.com/product/tc2030-idc-6-pin-tag-connect-plug-of-nails-spring-pin-cable-with-legs) and [ARM20-CTX Adapter](https://www.tag-connect.com/product/arm20-ctx-20-pin-to-tc2030-idc-adapter-for-cortex) are recommended) 

## Use binary for demo

(place holder) a way to provide binary and use command like in https://github.com/LairdCP/MG100_firmware/releases? 
  
## Clone firmware source

This is a Zephyr `west` manifest repository. To learn more about `west` see [here](https://docs.zephyrproject.org/latest/guides/west/index.html).

To clone this repository properly use the `west` tool. To install `west` you will first need Python3.

Install `west` using `pip3`:

```
# Linux
pip3 install --user -U west

# macOS (Terminal) and Windows (cmd.exe)
pip3 install -U west
```

Once `west` is installed, clone this repository using `west init` and `west update`:

```
# Checkout the latest manifest on master
west init -m https://github.com/vascode/MG100_firmware_manifest.git

# Now, pull all the source described in the manifest
west update
```

## Build firmware

### Preparing to Build
If this is your first time working with a Zephyr project on your computer you should follow the [Zephyr getting started guide](https://docs.zephyrproject.org/latest/getting_started/index.html#) to install all the tools.

The OOB demo uses zephyr 2.3.x, so GCC 9 is recommended.
[GNU Arm Embedded Toolchain: 9-2019-q4-major](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) is recommended.

See here to [setup the GNU ARM Embedded tools](https://docs.zephyrproject.org/2.3.0/getting_started/toolchain_3rd_party_x_compilers.html#gnu-arm-embedded)

If using Linux, v0.11.3 of the Zephyr SDK is recommended.

### Build firmware (Zephyr app)

The firmware can be built to work with or without the mcuboot bootloader. Building without mcuboot is faster and easier for development and debug, but gives up the ability to update the Zephyr app via UART or BLE.

Issue these commands **from the mg100_firmware directory**.

Build without mcuboot:
```
# Linux and macOS

rm -f mg100/pm_static.yml && west build -b mg100 -d build/mg100_aws mg100

# Windows

del mg100\pm_static.yml && west build -b mg100 -d build\mg100_aws mg100
```

> **Note:** When switching between builds with or without mcuboot, be sure to delete the build directory before building.

Build with mcuboot:
```
# Linux and macOS

cp ../modules/zephyr_lib/mcuboot_config/pm_static.pinnacle100.yml mg100/pm_static.yml && west build -b mg100 -d build/mg100_aws mg100 -- -DOVERLAY_CONFIG="${PWD}/../modules/zephyr_lib/mcumgr_wrapper/config/overlay-mcuboot.conf" -Dmcuboot_CONF_FILE="${PWD}/../modules/zephyr_lib/mcuboot_config/mcuboot-qspi.conf ${PWD}/../modules/zephyr_lib/mcuboot_config/overlay-disable-hl7800-modem.conf ${PWD}/../modules/zephyr_lib/mcuboot_config/mcuboot-serial-pinnacle100_dvk.conf ${PWD}/../modules/zephyr_lib/mcuboot_config/disable-slot0-validate.conf"

# Windows

copy ..\modules\zephyr_lib\mcuboot_config\pm_static.pinnacle100.yml mg100\pm_static.yml && west build -b mg100 -d build\mg100_aws mg100 -- -DOVERLAY_CONFIG="%CD%\..\modules\zephyr_lib\mcumgr_wrapper\config\overlay-mcuboot.conf" -Dmcuboot_CONF_FILE="%CD%\..\modules\zephyr_lib\mcuboot_config\mcuboot-qspi.conf %CD%\..\modules\zephyr_lib\mcuboot_config\overlay-disable-hl7800-modem.conf %CD%\..\modules\zephyr_lib\mcuboot_config\mcuboot-serial-pinnacle100_dvk.conf %CD%\..\modules\zephyr_lib\mcuboot_config/disable-slot0-validate.conf"
```

## Flash firmware

If the MG100 is running v2.0.0 firmware or earlier, firmmare updates must be programmed via SWD(Serial Wire Debug). To do this, consult the [MG100 Hardware Guide](https://www.lairdconnect.com/documentation/mg100-gateway-hardware-guide) section 5.4.4 to learn how to connect a J-Link debugger to the board.

MG100 units with version 3.x or greater support firmware updates via UART, BLE or LTE.

### Flash firmware via SWD
After building the firmware, it can be flashed with the following command:
```
# Linux and macOS

west flash -d build/mg100_aws

# Windows

west flash -d build\mg100_aws
```

If the firmware was built with mcuboot, `west flash` will program merged.hex which contains the mcuboot bootloader and app combined. 

### Flash firmware via UART or BLE 

See [here](docs/firmware_update.md) for building firmware via UART or BLE 


## Connect to AWS account 

Read [here](docs/aws_iot.md) where you will set up AWS account and set its address in MG100 so that you can see data coming in from either BT510 or Beckett device 

## Development

### Development and Debug

See [here](docs/development.md) for details on developing and debugging this app.

### BLE Profiles

Details on the BLE profiles used to interface with the mobile app can be found [here](docs/ble.md)

## Change source code

To add your own BLE sensor for this demo, your own data format needs to be defined first and it sould be added to SensorTable. Also your own advert event hanlder needs to be created. Take a look at [this commit](https://github.com/vascode/MG100_firmware/commit/dd6405617c2779fe9539834c67d529bfac36b715) to see what's added from the original code.  For example, 
* BKAdEvent_t : BeckettLink Tank Gauge's data structure in advert. This is added to SensorEntry_t for SensorTable in sensor_table.c
* FindBKAdvertisement : Check if the advert is from BK by checking payload length and company ID
* BkAdEventHandler : copy BK advert data to Sensortable
* BkShadowMaker : Prepare shadow in json by referring data in SensorTable
