#include "copy.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	int infd = 0; // standard input
	int outfd = 1; // standard output

	if (argc > 1) {
		if (argc < 2) {
			fprintf(stderr, "Error: copycat needs either no or exactly two arguments!\n");
			// This is basically the same as `return EXIT_FAILURE` here,
			// since we are in main.
			exit(EXIT_FAILURE);
		}

		if (strcmp("-", argv[1])) {

			if ((infd = open(argv[1], O_RDONLY)) == -1) {
				perror("Error OPENing INPUT file");
				return EXIT_FAILURE;
			}
		}

		if (strcmp("-", argv[2])) {

			if ((outfd = open(argv[2], O_WRONLY)) == -1) {
				perror("Error OPENing OUTPUT file");
				return EXIT_FAILURE;
			}
		}
	}

	if (copyFds(infd, outfd) == -1) {
		perror("Error copying");
		return EXIT_FAILURE;
	}
	
	if (infd != 0 && close(infd) == -1) {
		perror("Error closing INPUT file");
		return EXIT_FAILURE;
	}	
	
	if (outfd != 1 && close(outfd) == -1) {
		perror("Error closing OUTPUT file");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
