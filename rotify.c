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
			"  -n, --range-number\tdecodes the given rot in the given range example 2\n"
			"  -a, --auto-solve\tautomatically solve the rot only works when you are decoding\n"
			"  -h, --help\tdisplay this help and exit\n";
	for(int i=0;i<argc;i++) {
		if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			fprintf(stderr, format, argv[0]);
			exit(0);
		}
	}
	if(argc < 2) { fprintf(stderr, format, argv[0]); exit(0); }
}

int parse_intarg(char** argv, char c) {
	int i=0;
	while(optarg[i]) {
		if(!isdigit(optarg[i])) {
			fprintf(stderr, "%s: option '-%c': argument '%s' must be a positive integer\n", argv[0], c, optarg);
			return 0;
		}
		i++;
	}
	return 1;
}

int main(int argc, char** argv) {
	struct option options[] = {
		{"decode", no_argument, 0, 'd'},
		{"encode", no_argument, 0, 'e'},
		{"rot", required_argument, 0, 'r'},
		{"text", required_argument, 0, 't'},
		{"auto-solve", no_argument, 0, 'a'},
		{"range-number", required_argument, 0, 'n'},
		{0, 0, 0, 0}
	};
	usage(argc, argv);
	int option_idx, c, opr_type = 0, rt = 0, range = 0, auto_solve = 0;
	char* text = NULL;
	while((c = getopt_long(argc, argv, "der:t:n:a", options, &option_idx)) != -1) {
		switch(c) {
			case 'd': opr_type = 1; break;
			case 'e': opr_type = 0; break;
			case 'r': {
				(parse_intarg(argv, c)) ? 0 : exit(0);
				rt = atoi(optarg); break;
			}
			case 't': text = optarg; break;
			case 'n': {
				(parse_intarg(argv, c)) ? 0 : exit(0);
				range = atoi(optarg);
				break;
			}
			case 'a': auto_solve = 1; break;
			case '?': exit(0);
		}
	}

	if(text != NULL) {
		if(auto_solve) {
			for(int i=0;;i++) { printf("rot %d: ", i); rot_decode(text, i); }
		} else if(range > 0) {
			for(int i=0;i<=range;i++) { printf("rot %d: ", i); rot_decode(text, i); }
		} else { (!opr_type) ? rot_encode(text, rt) : rot_decode(text, rt); }
	}
	return 0;
}
