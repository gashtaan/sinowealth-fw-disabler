# SinoWealth Firmware Disabler
USB peripherals based on SinoWealth MCUs have built-in bootloader that is capable to run as a standalone USB device that exposes ICP support. Normally the bootloader immediately jumps to the device's firmware (if there is any) and it is up to the firmware whether or on what conditions it allows to switch to ICP to take over the USB connection. Therefore if the device's firmware doesn't have support for the mentioned switch, the ICP features are unavailable. Also if the device's firmware is corrupted or simply hangs during the development, there could be no way to do the switch and the device is bricked for good. In such cases the only way to re-flash the firmware is to use a special programmer device by connecting it directly to MCU's JTAG. Fortunately, there is an easier method to cope with such situations even without needing to dismantle the device...

After every reset, the bootloader, just before it jumps to the device's firmware, checks if a signal of special sequence is present on USB D+/D- pins. If it is, the bootloader disables the existing firmware, so after the next reset(s), the device will always start in USB ICP mode. Then nothing prevents us from using the ICP interface to program the device. Thanks to [@carlossless](https://github.com/carlossless) there is already nice tool for it:
https://github.com/carlossless/sinowealth-kb-tool

The signal has nothing to do with standard USB protocol therefore some gadget is needed to generate it. You can use whatever you have in the drawer, any board or bare MCU would do. As far I know many SinoWealth MCUs can run from 2V, so even 3.3V boards/MCUs should not be a problem for this tool.

## How to use
The code in this repository is standard Arduino IDE sketch, so it should be easily compiled to any compatible board. I've tested it on Arduino Nano 3.

At first, you need to connect USB connector to a board/MCU. Connect D2/D3 pins to the target device's USB D+/D- signal lines. If the target device doesn't draw too much current, it can be powered up from D4 pin to exploit the fact that these pins are next to GND so they match the USB connector pinout. Or power the device from the power rail, for example VIN or +5V pin on Arduino board, it doesn't really matter.

Proper would be to use weak pull-down (~100k) on USBP (D+) pin, but lazy way with direct connection also works OK for me.

If you have wiring done and sketch uploaded to the gadget, power it up and then connect the SinoWealth USB peripheral into the wired connector. If everything goes right, LED on the board will begin to blink continuously - that's the signal that the bootloader sends back to signalize successful operation.

&#9888; Note that some devices with SH68F881/BYK801 MCU has bug in the bootloader, so unfortunately this tool will not work with them. The bootloader accepts the signal, but it fails to disable the firmware, because it erases the incorrect sector in the flash memory. Actually it tries to erase sector that doesn't even exist in the memory, so at least it doesn't corrupt existing data.
If you wish to use this tool on affected MCUs, you'll need to program the fixed bootloader into them over the JTAG. I've made the tool also for this task: https://github.com/gashtaan/sinowealth-8051-bl-updater
