# geoh
Idiomatic C Geohash library and tools

## Installation

``
$ git clone http://github.com/konimarti/geoh
$ make 
$ sudo make install
``

## Getting started

To calculate a geohash from coordinates, you first initiate a ```nstruct geoh_position``` and ```nstruct geoh_hash``` and initialize the hash with the required precision using ```geoh_init_hash()``` function.
```c
	struct geoh_position coords = {.lat = 41.1234, .lng = 9.5678};
	struct geoh_hash hash;
	geoh_init_hash(&hash, 6);
```

Once initialized, call the ```geoh_encode()``` function.
```c
	geoh_encode(&hash, &coords);
	printf("Geohash: %s\n", hash->hash);
```

After you are done, don't forget to release the hash resources.
```c
	geoh_free(&hash);
```

## Geohash tools usage

* ``encode [precision]`` reads in latitude and longitude and calculates the geohash for the given precision:
	```
	$ echo "41.1234 9.5678" | bin/encode 6 
	$ spqccw
	$ echo "41.1234 9.5678" | bin/encode 12 
	$ spqccwr11vku
	```

* ``decode`` reads a geohash and prints the corresponding latitude and longitude:
	```
	echo "spqccwr11vku" | bin/decode 
	41.123400 9.567800
	```

## Unit Testing

The unit tests use the [cmocka](http://cmocka.org) unit testing framework. To run the test, [cmocka](http://cmocka.org) needs to be installed on your machine to build and run the unit tests.

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
