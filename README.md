# geoh
Idiomatic C Geohash library and tools

## Installation

``
git clone http://github.com/konimarti/geoh
``

``
make 
``

``
sudo make install
``

## Geohash tools

* ``encode [precision]`` reads in latitude and longitue and calculates geohash for the given precision:
	```
	$ echo "41.1234 9.5678" | bin/encode 6 
	$ spqccw
	$ echo "41.1234 9.5678" | bin/encode 12 
	$ spqccwr11vku
	```

* ``decode`` reads a geohash and prints the corresponding latitude and longitue:
	```
	echo "spqccwr11vku" | bin/decode 
	41.123400 9.567800
	```

## Unit Testing

```
$ make test

Starting Geohash unit-tests.
[GEOH Tests]
[==========] Running 5 test(s).
[ RUN      ] TEST__init_position
[       OK ] TEST__init_position
[ RUN      ] TEST__init_hash_empty
[       OK ] TEST__init_hash_empty
[ RUN      ] TEST__init_hash_encoded
[       OK ] TEST__init_hash_encoded
[ RUN      ] TEST__encode
[       OK ] TEST__encode
[ RUN      ] TEST__decode
[       OK ] TEST__decode
[==========] 5 test(s) run.
[  PASSED  ] 5 test(s).

```
