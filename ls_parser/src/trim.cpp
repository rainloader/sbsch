/*
 * trim.cpp
 *
 *  Created on: 2013. 4. 15.
 *      Author: ÇÃ·§Æû¿î¿µÆÀ
 */

#include "trim.h"
#include <string.h>

char* trim(char* string){
	return lTrim(rTrim(string));
}

char* lTrim(char* string){
	int stringLen = strlen(string);
	int i;
	for(i=0; i<stringLen && string[i] == ' '; i++);
	return string+i;
}

char* rTrim(char* string){
	int stringLen = strlen(string);
	int i;
	for(i=stringLen-1; i>=0 && string[i] == ' '; i--);
	string[i+1] = 0;
	return string;
}
