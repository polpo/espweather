#!/usr/bin/env python3

# Converts a directory of 24x16 .png files to a format appropriate for loading
# as custom characters on a Crystalfontz CFA632 LCD display.

from glob import glob
from os.path import splitext, basename

from PIL import Image


for img_file in glob('images/*.png'):
    print('const uint8_t {}[] = {{'.format(splitext(basename(img_file))[0]));
    img = Image.open(img_file)

    for j in range(0, img.size[1], 8):
        for i in range(0, img.size[0], 6):
            for jp in range(0, 8):
                bits = 0
                for ip in range(0, 6):
                    bits = bits << 1 | int(bool(img.getpixel((i+ip, j+jp))))
                print('    {},'.format(bits), end='')
            print();
    print('};');
    print();

