# Accentizer

Accentize Hungarian text.

## Compiling

    g++ accentizer.cpp -std=c++11 -O3 -Wall -pedantic -o accentizer

## Usage

    $ echo arvizturo tukorfurogep | ./accentizer
    árvíztűrő tükörfúrógép

## Deaccentize input

    $ $ echo árvíztűrő tükörfúrógép | ./deaccentize.py
    arvizturo tukorfurogep


Accentizing again:

    $ echo árvíztűrő tükörfúrógép | ./deaccentize.py | ./accentizer 
    árvíztűrő tükörfúrógép

