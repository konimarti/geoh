# geoh
Idiomatic C Geohash library and tools

# Installation

``
git clone http://github.com/konimarti/geoh
``

``
make 
``

``
make test
``

``
sudo make install
``

# Geohash tools

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
