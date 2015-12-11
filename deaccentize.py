#!/usr/bin/env python
# -*- coding: utf-8 -*-
from sys import argv, stdin


def read_accent_map(map_str):
    m = map_str.decode('utf8')
    d = {}
    for i in xrange(0, len(m), 2):
        d[m[i]] = m[i + 1]
        d[m[i].upper()] = m[i + 1].upper()
    return d


def main():
    if len(argv) > 1:
        accent_map = read_accent_map(argv[1])
    else:
        accent_map = read_accent_map('áaéeíióoöoőoúuüuűu')
    for l in stdin:
        print(''.join(accent_map.get(c, c) for c in l.decode('utf8')).encode('utf8').rstrip('\n'))

if __name__ == '__main__':
    main()
