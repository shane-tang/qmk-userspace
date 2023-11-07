# shane-tang's QMK Userspace
My personal QMK userspace to share firmware changes for [qmk/qmk_firmware](https://github.com/qmk/qmk_firmware). I'm currently only using a [3x6 Corne keyboard](https://github.com/foostan/crkbd). I use [VIA](https://usevia.app) for my layouts.

## Features
### Keypress Bongo Cat
Most QMK Bongo Cat implementations I found were based on WPM, but I wanted Bongo Cat's taps to map 1:1 with each keypress. I modified [customMK's Bongo-on-a-Budget](https://www.reddit.com/r/MechanicalKeyboards/comments/t6gux6/bongo_catonabudget_it_uses_only_15kb_memory_and/) to respond to keypresses better and work with a basic Corne keyboard with no encoder.

## Credits
* [qmk/qmk_firmware](https://github.com/qmk/qmk_firmware) for...well, QMK firmware
* customMK's original compressed EVO70 keypress Bongo Cat implementation
  * [Reddit thread](https://www.reddit.com/r/MechanicalKeyboards/comments/t6gux6/bongo_catonabudget_it_uses_only_15kb_memory_and/)
  * [EVO70 Bongo Cat code](https://github.com/customMK/qmk_firmware/commit/830c6ab6905004c645fa824691c59463b152b721)
