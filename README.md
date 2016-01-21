# Accentizer

Accentize Hungarian text.

## Compiling

    g++ accentizer.cpp -std=c++11 -O3 -Wall -pedantic -o accentizer

## Usage

    $ echo arvizturo tukorfurogep | ./accentizer
    árvíztűrő tükörfúrógép

If you call the binary from a different directory, you need to specify the location of the trees:

    $ echo arvizturo tukorfurogep | ./accentizer/accentizer accentizer/tree/
    árvíztűrő tükörfúrógép

## Deaccentize input

    $ echo árvíztűrő tükörfúrógép | ./deaccentize.py
    arvizturo tukorfurogep


Accentizing again:

    $ echo árvíztűrő tükörfúrógép | ./deaccentize.py | ./accentizer 
    árvíztűrő tükörfúrógép

