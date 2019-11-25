#define MAX_LAT 90.0
#define MIN_LAT -90.0

#define MAX_LNG 180.0
#define MIN_LNG -180.0

/* enum declarations */

enum geoh_return_code {
	GEOH_RETURN_OK = 0,
	GEOH_RETURN_ERR,
	GEOH_RETURN_PRECISION_OUT_OF_BOUNDS,
	GEOH_RETURN_LAT_OUT_OF_BOUNDS,
	GEOH_RETURN_LNG_OUT_OF_BOUNDS,
	GEOH_RETURN_HASH_NOT_ENCODED,
};

enum geoh_status_hash {
	GEOH_STATUS_INIT = 0,
	GEOH_STATUS_ENCODED,
	GEOH_STATUS_DECODED,
	GEOH_STATUS_ERR,
};

/* struct declarations */
struct geoh_position {
	double lat;
	double lng;
};

struct geoh_hash {
	char *hash;
	unsigned short precision;
	enum geoh_status_hash status;
};

/* data for encoding and decoding */
extern const char character_set[32];

/* function prototypes */
enum geoh_return_code geoh_init_position(struct geoh_position *coords,
					 double lat, double lng);
enum geoh_return_code geoh_init_empty_hash(struct geoh_hash *hash,
					   unsigned short precision);
enum geoh_return_code geoh_init_encoded_hash(struct geoh_hash *hash,
					     const char *geohash);
enum geoh_return_code geoh_free_hash(struct geoh_hash *hash);
enum geoh_return_code geoh_encode(struct geoh_hash *hash,
				  struct geoh_position *coords);
enum geoh_return_code geoh_decode(struct geoh_position *coords,
				  struct geoh_hash *hash);
