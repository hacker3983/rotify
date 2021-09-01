#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "rot.h"

void usage(int argc, char** argv) {
	char* format =  "Usage: %s [option]...\n" "Encodes or decodes the given rot cipher\n"
			"  -t, --text\ttext to encode or decode\n"
			"  -r, --rot\tnumber for the rot cipher example a number 13\n"
			"  -d, --decode\tdecode's the given text in the specified rot cipher number\n"
			"  -e, --encode\tencode's the given text in the specified rot cipher number\n"
			"  -h, --help\tdisplay this help and exit\n";
	for(int i=0;i<argc;i++) {
		if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			fprintf(stderr, format, argv[0]);
			exit(0);
		}
	}
	if(argc < 2) { fprintf(stderr, format, argv[0]); exit(0); }
}

int main(int argc, char** argv) {
	struct option options[] = {
		{"--decode", no_argument, 0, 'd'},
		{"--encode", no_argument, 0, 'e'},
		{"--rot", required_argument, 0, 'r'},
		{"--text", required_argument, 0, 't'}
	};
	usage(argc, argv);
	int option_idx, c, opr_type = 0, rt = 0;
	char* text = NULL;
	while((c = getopt_long(argc, argv, "der:t:", options, &option_idx)) != -1) {
		switch(c) {
			case 'd': opr_type = 1; break;
			case 'e': opr_type = 0; break;
			case 'r': rt = atoi(optarg); break;
			case 't': text = optarg; break;
			case '?': exit(0);
			default: fprintf(stderr, "%s: Invalid option or argument '%c'\n", argv[0], c); exit(0);
		}
	}

	if(text != NULL) {
		(!opr_type) ? rot_encode(text, rt) : rot_decode(text, rt);
	}
	return 0;
}
