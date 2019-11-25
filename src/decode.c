#include <geoh.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 128

void usage(char* prog) { printf("Usage: %s\n", prog); }

int main(int argc, char* argv[]) {
	char* buf;
	size_t len = 0;
	ssize_t nread;

	char geohash[12];

	if (argc != 1) {
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	/* create data structure */
	struct geoh_position coord;
	struct geoh_hash hash;

	/* loop over input lines expecting a geohash string: [geohash] */
	while ((nread = getline(&buf, &len, stdin)) > 0) {
		if (len > 0 && sscanf(buf, "%s", geohash) == 1) {
			if (geoh_init_hash(&hash, strlen(geohash)) !=
			    GEOH_RETURN_OK) {
				printf("failed to init hash");
			}
			if (geoh_set_hash(&hash, geohash) != GEOH_RETURN_OK) {
				printf("failed to set hash");
			}
			if (geoh_decode(&coord, &hash) == GEOH_RETURN_OK) {
				printf("%f %f\n", coord.lat, coord.lng);
			}
			if (geoh_free_hash(&hash) != GEOH_RETURN_OK) {
				printf("failed to free hash");
			}
		}
		free(buf);
		buf = NULL;
	}
	if (buf != NULL) free(buf);

	exit(EXIT_SUCCESS);
}
