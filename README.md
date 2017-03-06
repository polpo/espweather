# espweather #

![Weather icons](https://polpo.org/espweather/montage.png)

Cute weather station for the ESP8266 WiFi microcontroller, written with Arduino/C++. [Powered by Dark Sky](https://darksky.net/poweredby).

## requirements ##

Hardware

- An ESP8266
- A [Crystalfontz CFA632](https://www.crystalfontz.com/product/cfa632ydikn-uart-lcd-character-display-16x2) LCD display on UART0
  - The CFA632 should be configured for Inverted TTL serial (bridge JPB and JPE)

Software

- Arduino
- [json-streaming-parser](https://github.com/squix78/json-streaming-parser)

## configuration ##

Edit `constants.h` and put in your WiFi info, [Dark Sky API key](https://darksky.net/dev/), and lat/long.

## weather icons ##

The weather icons are 24x16 pixels. In the `png2h/images` directory you will find them, and they can be converted to the format expected by the CFA632 with the `png2h/png2h.py` script.

## screenshots ##

Instead of screenshots, how about a GIF?

![Animated GIF of espweather](https://polpo.org/espweather/espweather.gif)
