# Hunaccent

Accentize Hungarian text. Please note that this libarary **does not** use a vocabulary and it may generate non-existant words.

## Compiling

    g++ hunaccent.cpp -std=c++11 -O3 -Wall -pedantic -o hunaccent

## Compiling to Javascript

Install Emscripten. Set

    #define TARGET_EMSCRIPTEN

at the beginning of `hunaccent.cpp` by removing the double slash, then run

    emcc -std=c++11 --bind -s WASM=0 hunaccent.cpp -o hunaccent.js --embed-file tree

The `hunaccent.js` and `hunaccent.html` files are all that is needed, the asset is compiled into the
js file by Emscripten.

## Usage

    $ echo arvizturo tukorfurogep | ./hunaccent
    árvíztűrő tükörfúrógép

If you call the binary from a different directory, you need to specify the location of the trees:

    $ echo arvizturo tukorfurogep | ./hunaccent/hunaccent hunaccent/tree/
    árvíztűrő tükörfúrógép

## Deaccentize input

    $ echo árvíztűrő tükörfúrógép | ./deaccentize.py
    arvizturo tukorfurogep


Accentizing again:

    $ echo árvíztűrő tükörfúrógép | ./deaccentize.py | ./hunaccent 
    árvíztűrő tükörfúrógép

## Note

Hunaccent is still under development, meaning I might change the tree files for better ones anytime.

## Citation

Please cite this paper if you use hunaccent in your research:

~~~
@article{Acs:2016,
  title={Hunaccent: Small Footprint Diacritic Restoration for Social Media},
  author={Acs, Judit and Halmi, J{\'o}zsef},
  booktitle={Normalisation and Analysis of Social Media Texts (NormSoMe) Workshop},
  year=2016,
}
~~~


