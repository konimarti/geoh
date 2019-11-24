#include <geoh.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 128

void usage(char* prog) { printf("Usage: %s\n", prog); }

int main(int argc, char* argv[]) {
	if (argc != 1) {
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	struct geoh_position coord;
	struct geoh_hash hash;

	char geohash[12];

	char* buf;
	size_t len = 0;
	ssize_t nread;

	/* loop over input lines expecting a geohash string: [geohash] */
	while ((nread = getline(&buf, &len, stdin)) > 0) {
		if (len > 0 && sscanf(buf, "%s", geohash) == 1) {
			if (geoh_init_encoded_hash(&hash, geohash) !=
			    GEOH_RETURN_OK) {
				printf("failed to init encoded hash");
				continue;
			}
			if (geoh_decode(&coord, &hash) == GEOH_RETURN_OK) {
				printf("%f %f\n", coord.lat, coord.lng);
			}
		}
		free(buf);
		buf = NULL;
	}
	if (buf != NULL) free(buf);

	exit(EXIT_SUCCESS);
}