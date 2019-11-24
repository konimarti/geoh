#include <geoh.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 128

void usage(char* prog) { printf("Usage: %s [precision]\n", prog); }

int main(int argc, char* argv[]) {
	if (argc != 2) {
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	/* read precision parameter form command line */
	unsigned short precision = atoi(argv[1]);
	if (precision < 1 || precision > 12) {
		printf(
		    "Error: precision parameters needs to be between 1 and "
		    "12.");
		exit(EXIT_FAILURE);
	}

	struct geoh_position coord;
	struct geoh_hash hash;

	double lat, lng;

	char* buf = NULL;
	size_t len = 0;
	ssize_t nread;

	/* loop over input lines expecting two floats: [latitute] [longitude] */
	while ((nread = getline(&buf, &len, stdin)) > 0) {
		if (len > 0 &&
		    sscanf(buf, "%lf %lf", &coord.lat, &coord.lng) == 2) {
			if (geoh_init_empty_hash(&hash, precision) !=
			    GEOH_RETURN_OK) {
				printf("failed to init hash");
				continue;
			}
			if (geoh_encode(&hash, &coord) == GEOH_RETURN_OK) {
				printf("%s\n", hash.hash);
			}
		}
		free(buf);
		buf = NULL;
	}
	if (buf != NULL) free(buf);

	exit(EXIT_SUCCESS);
}