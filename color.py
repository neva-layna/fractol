from PIL import Image
import numpy

im = Image.open('color6.png')
im = im.convert('RGB')
pixels = list(im.getdata())

i = 0
while (i < 256):
    string = str(pixels[i])
    string = string.replace("(", "")
    string = string.replace(")", "")
    string = string.split(",")
    color = ((int(string[0]) & 0x0FF) << 16) | ((int(string[1]) & 0x0FF) << 8) | ((int(string[2]) & 0x0FF))
    res = str(color)
    print(res, file=open("color5.txt", "a"))
    i += 1
