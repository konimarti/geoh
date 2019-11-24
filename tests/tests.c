#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include cmocka */
#include <cmocka.h>

/* geoh */
#include "geoh.h"

/* define numbers for testing */
const double latitude = 42.1111;
const double longitude = 8.9999;

const unsigned short precision = 6;

const double latitude_decoded = 42.11334229;
const double longitude_decoded = 9.00329590;

/* geohash for above coordinates*/
const char *geohash = "spqrsf";

/* structs to work with */
struct geoh_position coords;
struct geoh_hash hash_empty;
struct geoh_hash hash_encoded;

static void TEST__init_position(void **state) {
	/* test if encode algorithm works */
	assert_true(geoh_init_position(&coords, latitude, longitude) ==
		    GEOH_RETURN_OK);
}

static void TEST__init_hash_empty(void **state) {
	/* test if encode algorithm works */
	assert_true(geoh_init_empty_hash(&hash_empty, precision) ==
		    GEOH_RETURN_OK);

	/* test if precision is correct */
	assert_true(hash_empty.precision == precision);
}

static void TEST__init_hash_encoded(void **state) {
	/* test if encode algorithm works */
	assert_true(geoh_init_encoded_hash(&hash_encoded, geohash) ==
		    GEOH_RETURN_OK);

	/* test if returned hash has correct value */
	assert_true(strcmp(hash_encoded.hash, geohash) == 0);
}

static void TEST__encode(void **state) {
	/* test if encode algorithm works */
	assert_true(geoh_encode(&hash_empty, &coords) == GEOH_RETURN_OK);

	/* test if returned hash status is encoded */
	assert_true(hash_empty.status == GEOH_STATUS_ENCODED);

	/* test if returned hash has correct length */
	assert_true(strlen(hash_empty.hash) == hash_empty.precision);

	/* test if returned hash has correct value */
	assert_true(strcmp(hash_empty.hash, geohash) == 0);
}

static void TEST__decode(void **state) {
	/* prepare encoded hash */
	geoh_init_encoded_hash(&hash_encoded, geohash);

	/* test if decode algorithm works */
	assert_true(geoh_decode(&coords, &hash_encoded) == GEOH_RETURN_OK);

	/* test if decoded latitude is correct */
	assert_float_equal(coords.lat, latitude_decoded, 1e-6);

	/* test if decoded longitude is correct */
	assert_float_equal(coords.lng, longitude_decoded, 1e-6);
}

int main(int argc, const char *argv[]) {
	int failed = 0;

	printf("Starting Geohash unit-tests.\n");

	printf("[GEOH Tests]\n");
	const struct CMUnitTest tests[] = {
	    cmocka_unit_test(TEST__init_position),
	    cmocka_unit_test(TEST__init_hash_empty),
	    cmocka_unit_test(TEST__init_hash_encoded),
	    cmocka_unit_test(TEST__encode),
	    cmocka_unit_test(TEST__decode),
	};

	failed = cmocka_run_group_tests(tests, NULL, NULL);

	return failed;
}
