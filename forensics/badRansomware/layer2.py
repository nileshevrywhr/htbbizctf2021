#!/bin/python3

import re

with open("buffer") as f:
    payload = f.read()

ascii_codes = re.split('X|w|c|I|M|p|}|U|R|%', payload)
command = "".join([chr(int(c)) for c in ascii_codes])

print(command)
