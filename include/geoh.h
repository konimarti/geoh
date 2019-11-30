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

/* struct declarations */
struct geoh_hash {
	char hash[12 + 1];
	unsigned short precision;
};

/* data for encoding and decoding */
extern const char character_set[32];

/* function prototypes */
int geoh_init_hash(struct geoh_hash *hash, unsigned short precision);
int geoh_set_hash(struct geoh_hash *hash, const char *geohash);

int geoh_encode(struct geoh_hash *hash, double lat, double lng);
int geoh_decode(struct geoh_hash *hash, double *lat, double *lng);
