#include <geoh.h>
#include <stdlib.h>
#include <string.h>

/*
 *
 *  Algorithms used in this implementation of geohashes inspired by
 *  - Derek Smith (http://github.com/simplegeo/libgeohash)
 *  - Dave Troy (http://github.com/davetroy/geohash-js)
 *
 * */

/* internal struct for encoding and decoding */
struct __range {
	double low;
	double high;
};

/* define characer set for geohashing */
const char character_set[32] = "0123456789bcdefghjkmnpqrstuvwxyz";

/* initialize struct geoh_position with the given coordinates (optional) */
enum geoh_return_code geoh_init_position(struct geoh_position *coords,
					 double lat, double lng) {
	if (coords == NULL) return GEOH_RETURN_ERR;

	coords->lat = lat;
	coords->lng = lng;
	return GEOH_RETURN_OK;
}

/* initialize struct geoh_hash with the given precision */
enum geoh_return_code geoh_init_empty_hash(struct geoh_hash *hash,
					   unsigned short precision) {
	if (hash == NULL) return GEOH_RETURN_ERR;

	hash->hash = (char *)malloc(sizeof(char) * (precision + 1));
	hash->hash[precision] = '\0';
	hash->precision = precision;
	hash->status = GEOH_STATUS_INIT;
	return GEOH_RETURN_OK;
}

/* free struct geoh_hash */
enum geoh_return_code geoh_free_hash(struct geoh_hash *hash) {
	if (hash == NULL) return GEOH_RETURN_ERR;

	if (hash->hash != NULL) free(hash->hash);
	hash->status = GEOH_STATUS_INIT;
	return GEOH_RETURN_OK;
}

/* initialize struct geoh_hash encoded hash*/
enum geoh_return_code geoh_init_encoded_hash(struct geoh_hash *hash,
					     const char *geohash) {
	if (hash == NULL || geohash == NULL) return GEOH_RETURN_ERR;

	hash->hash = (char *)geohash;
	hash->precision = (unsigned short)strlen(geohash);
	hash->status = GEOH_STATUS_ENCODED;
	return GEOH_RETURN_OK;
}

/* geoh_encode encodes the coordinates in struct geohash_position to a struct
 * geohash_hash */
enum geoh_return_code geoh_encode(struct geoh_hash *hash,
				  struct geoh_position *coords) {
	if (hash == NULL || coords == NULL) return GEOH_RETURN_ERR;

	if ((hash->precision) < 1 || (hash->precision) > 12)
		return GEOH_RETURN_PRECISION_OUT_OF_BOUNDS;

	if (coords->lat > MAX_LAT || coords->lat < MIN_LAT)
		return GEOH_RETURN_LAT_OUT_OF_BOUNDS;

	if (coords->lng > MAX_LNG || coords->lng < MIN_LNG)
		return GEOH_RETURN_LNG_OUT_OF_BOUNDS;

	unsigned short length = 5.0 * hash->precision;

	struct __range range_lat = {MIN_LAT, MAX_LAT};
	struct __range range_lng = {MIN_LNG, MAX_LNG};
	struct __range *rng;

	double coord, mid;
	unsigned int hashChar = 0;
	for (int i = 0; i < length; i++) {
		if (i % 2 == 0) {
			rng = &range_lng;
			coord = coords->lng;

		} else {
			rng = &range_lat;
			coord = coords->lat;
		}

		mid = (rng->low + rng->high) / 2.0;
		hashChar = hashChar << 1;

		if (coord > mid) {
			rng->low = mid;
			hashChar |= 0x01;

		} else
			rng->high = mid;

		if (!((i + 1) % 5)) {
			hash->hash[i / 5] = character_set[hashChar];
			hashChar = 0;
		}
	}

	/* update hash status */
	hash->status = GEOH_STATUS_ENCODED;

	return GEOH_RETURN_OK;
}

/* helper function */
int char_set_idx(char c, const char *char_set) {
	for (int i = 0; i < (int)strlen(char_set); i++) {
		if (c == char_set[i]) return i;
	}
	return -1;
}

/* geoh_decode decodes the struct geoh_hash to struct geohash_position */
enum geoh_return_code geoh_decode(struct geoh_position *coords,
				  struct geoh_hash *hash) {
	if (hash == NULL || coords == NULL) return GEOH_RETURN_ERR;

	if (hash->status != GEOH_STATUS_ENCODED)
		return GEOH_RETURN_HASH_NOT_ENCODED;

	struct __range range_lat = {MIN_LAT, MAX_LAT};
	struct __range range_lng = {MIN_LNG, MAX_LNG};
	struct __range *rng;

	int char_mapIndex;

	int is_even = 1;
	double delta;
	for (int i = 0; i < hash->precision; i++) {
		char_mapIndex =
		    char_set_idx(hash->hash[i], (char *)character_set);
		if (char_mapIndex < 0) return GEOH_RETURN_ERR;

		// Interpret the last 5 bits of the integer
		for (int j = 0; j < 5; j++) {
			rng = is_even ? &range_lng : &range_lat;

			delta = (rng->high - rng->low) / 2.0;

			if ((char_mapIndex << j) & 0x0010)
				rng->low += delta;
			else
				rng->high -= delta;

			is_even = !is_even;
		}
	}

	/* calculate coords */
	coords->lat = range_lat.high - ((range_lat.high - range_lat.low) / 2.0);
	coords->lng = range_lng.high - ((range_lng.high - range_lng.low) / 2.0);

	return GEOH_RETURN_OK;
}

