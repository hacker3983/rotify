#ifndef _ROT_H
#define _ROT_H
#include <string.h>
#include <ctype.h>
#define alphabet "abcdefghijklmnopqrstuvwxyz"
/* Hello in rot 13
   For each characters in a given text
   if it is a letter of the alphabet we keep adding 1 n(13) times
   if it is not a letter we just print it
*/
// encode the given text in the specifed rot
void rot_encode(char* text, int rot) {
	for(int i=0;i<strlen(text);i++) {
		int found = 0, c = tolower(text[i]);
		for(int x=0;x<26;x++) {
			if(tolower(text[i]) == alphabet[x]) {
				/*for(int j=0;j<rot;j++) {
					x++;
					if(x > 25) {
						x = 0;
					}
				}*/
				x += rot; if(x > 25) x = (x-1) % 25;
				(isupper(text[i])) ? printf("%c", toupper(alphabet[x])) : printf("%c", alphabet[x]);
				found = 1;
				break;
			}
		}
		if(!found) { printf("%c", text[i]); }
	}
	printf("\n");
}
/* V: w x y z a b c d e f g h i j
   X: w v u t s r q o p n m l k j
   c: b a z y x w v u t s r q p o
   to decode a rot (n) just keep subtracting by 1 n amount of times
   for each letter in the text
   if while subtracting by 1 the difference is less than 0
   just set d(difference) to 25
*/
// decode the given text in the specified rot
void rot_decode(char* text, int rot) {
	for(int i=0;i<strlen(text);i++) {
		int found = 0, c = tolower(text[i]);
		for(int x=0;x<26;x++) {
			if(tolower(text[i]) == alphabet[x]) {
				for(int j=0;j<rot;j++) {
					x--;
					if(x < 0) {
						x = 25;
					}
				}
				(isupper(text[i])) ? printf("%c", toupper(alphabet[x])) : printf("%c", alphabet[x]);
				found = 1;
				break;
			}
		}
		if(!found) { printf("%c", text[i]); }
	}
	printf("\n");
}
#endif
