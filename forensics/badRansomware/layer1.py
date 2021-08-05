#!/bin/python3

import sys, string, base64

from icecream import ic
ic.configureOutput(prefix='Debug | ')
#ic.disable()

str1 = ""
str2 = ""
# enc_string = ""

with open("pelxcitrdd.txt") as f1:
    str1 = f1.read().strip()

with open("adaopiwer.txt") as f2:
    str2 = f2.read().strip()

ascii_codes = (str2 + str1).split('@@@')
enc_string = "".join([chr(int(c)) for c in ascii_codes]).rstrip("x")

# for c in ascii_codes:
#     enc_string += chr(int(c))

command = base64.b64decode("IAB" + enc_string).decode("utf-8")

print(command)
