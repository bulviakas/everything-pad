# Everything pad - Custom macropad
A macropad project for the __Blueprint program__ by [Hack Club](https://hackclub.com/). 

The mini-keyboard features: 
  * 6 programmable keys
  * Rotary encoder
  * 8 RGB LEDs for backlight
  * OLED display

Designed to be a helpful tool while editing, gaming or just deep in flow state. ***The main goal - versatility***: multiple modes for every needed occasion (system sound control, application shortcuts, backlight configuration).

![Latest full version of the Everything pad](/assets/overall_macropad.png)

### Tools

* **PCB**: Custom-designed using **KiCad**
* **Case**: Modeled in **SolidWorks**
* **Firmware**: Built with **QMK**, supporting multiple layers, RGB lighting, encoder input, and OLED display

### Status
(2026-03-31) Project still in progress - no physical testing yet!

## PCB
### Schematic view

The keys and the rotary encoder are connected in a matrix.

![Scematic view of the Everything Pad](/assets/schematic.png)

### The product itself

A personal character Steve was made with **Inkscape**. Everyting is connected over 2 layers, with 0.4mm traces and GND fields. SK6812-MINI-E LED footprints were modified due to clearance errors.

![PCB view of the project](/assets/pcb_view.png)

## CAD model

The assembly process is quite simple - the PCB is mounted onto the bottom part of the case with 2 M3 bolts and heatset inserts. Top cover just slides in from the top.

![Assembly view of the case](/assets/case_assembly.png)

## Firmware

As of now, the code is purely theoretical, since there is no way to test it. However, _in theory_, the keyboard has 3 modes:
* **System sound control** - play/pause music, increase/decrease volume, mute, etc.
* **Application shortcuts** - case-specific keybinds, eg. Discord toggle mute, toggle camera
* **RBG backlight configuration** - increase/decrease brightness, hue, etc.

The colour of the RBG backlight shows the currently active mode (SSC - Blue, Apps - Green, etc.). OLED display serves as the main info output when switching modes. Since the macropad cannot read real system sound values, it stores simulated volume and displays a simple bar on-screen when relevant.

## BOM
 A list of everything used to make this masterpiece:
 * 1x Seeed XIAO RP2040
 * 7x through-hole 1N4148 Diodes
 * 6x MX-Style switches
 * 1x EC11 Rotary encoder
 * 1x 0.91 inch OLED display (GND-VCC-SCL-SDA)
 * 6x white blank DSA keycaps
 * 8x SK6812 MINI-E LEDs
 * 2x M3x16mm screws
 * 2x M3x5mx4mm heatset inserts
 * 1x case (2 printed parts)
 * 1x printed knob for the encoder
 * Some joy and whimsy~
