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

const char *geohash = "spqrsf";

const double latitude_decoded = 42.11334229;
const double longitude_decoded = 9.00329590;

/* test routines*/

static void TEST__init_position(void **state) {
	struct geoh_position coords;
	/* test if encode algorithm works */
	assert_true(geoh_init_position(&coords, latitude, longitude) ==
		    GEOH_RETURN_OK);
}

static void TEST__init_hash(void **state) {
	struct geoh_hash hash;

	/* test if encode algorithm works */
	assert_true(geoh_init_hash(&hash, precision) == GEOH_RETURN_OK);

	/* test if precision is correct */
	assert_true(hash.precision == precision);

	geoh_free_hash(&hash);
}

static void TEST__set_hash(void **state) {
	struct geoh_hash hash;
	geoh_init_hash(&hash, strlen(geohash));

	/* test if encode algorithm works */
	assert_true(geoh_set_hash(&hash, geohash) == GEOH_RETURN_OK);

	/* test if returned hash has correct value */
	assert_true(strcmp(hash.hash, geohash) == 0);

	geoh_free_hash(&hash);
}

static void TEST__encode(void **state) {
	struct geoh_position coords;
	struct geoh_hash hash;

	geoh_init_position(&coords, latitude, longitude);
	geoh_init_hash(&hash, precision);

	/* test if encode algorithm works */
	assert_true(geoh_encode(&hash, &coords) == GEOH_RETURN_OK);

	/* test if returned hash has correct length */
	assert_true(strlen(hash.hash) == hash.precision);

	/* test if returned hash has correct value */
	assert_true(strcmp(hash.hash, geohash) == 0);

	geoh_free_hash(&hash);
}

static void TEST__decode(void **state) {
	struct geoh_position coords;
	struct geoh_hash hash;

	geoh_init_hash(&hash, strlen(geohash));
	geoh_set_hash(&hash, geohash);

	/* test if decode algorithm works */
	assert_true(geoh_decode(&coords, &hash) == GEOH_RETURN_OK);

	/* test if decoded latitude is correct */
	assert_float_equal(coords.lat, latitude_decoded, 1e-6);

	/* test if decoded longitude is correct */
	assert_float_equal(coords.lng, longitude_decoded, 1e-6);

	geoh_free_hash(&hash);
}

int main(int argc, const char *argv[]) {
	int failed = 0;

	printf("Starting Geohash unit-tests.\n");

	printf("[GEOH Tests]\n");
	const struct CMUnitTest tests[] = {
	    cmocka_unit_test(TEST__init_position),
	    cmocka_unit_test(TEST__init_hash),
	    cmocka_unit_test(TEST__set_hash),
	    cmocka_unit_test(TEST__encode),
	    cmocka_unit_test(TEST__decode),
	};

	failed = cmocka_run_group_tests(tests, NULL, NULL);

	return failed;
}
