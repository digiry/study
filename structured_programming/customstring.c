/*
 * string.c
 *
 *  Created on: 2014. 10. 27.
 *      Author: suandkyu
 */

#include "header/customstring.h"
#include <string.h>

#define TRUE 1
#define FALSE 0

#ifdef DEBUG_STRING

int main(void) {
	STRING *testString;

	testString = (STRING *)malloc(sizeof(STRING));

	createString(testString);

	setString(testString, "hello");
	appendString(testString, " world!");

	printf("debug:%s\n", getString(testString));

	printf("debug:find 'w':%d\n", findCharString(testString,'w'));
	printf("debug:find 'llo':%d\n", findString(testString,"llo"));

	eraseString(testString);
	printf("debug:erase :--%s--\n", getString(testString));

	destroyString(testString);

	return 0;
}

#endif // DEBUG_STRING

void createString(STRING *self) {
	self->buffer = (char*)calloc(1, sizeof(char));
	self->buffer[0] = '\0';
	self->length = 0;
}

void destroyString(STRING *self) {
	if ( self->length > 0 ) {
		free(self->buffer);
	}
	self->length = 0;
}

void setString(STRING *self, char *string) {
	int length = 0;

	length = strlen(string);

	if ( self->length > 0 ) {
		free(self->buffer);
	}

	self->buffer = (char *)calloc(length + 1,sizeof(char));
	strcpy(self->buffer, string);
	self->length = length;
}

char* getString(STRING *self) {
	return self->buffer;
}

void appendString(STRING *self, char *string) {
	char *copy;
	int fullLength = 0;

	fullLength = self->length + strlen(string);

	if ( self->length != 0 ) {
		copy = (char *)calloc(self->length + 1, sizeof(char));
		strcpy(copy, self->buffer);
		free(self->buffer);
	} else {
		copy = (char *)calloc(1, sizeof(char));
		strcpy(copy, '\0');
	}

	self->buffer = (char *)calloc(fullLength + 1, sizeof(char));
	strcpy(self->buffer, copy);
	strcat(self->buffer, string);
	self->length = fullLength;

	free(copy);
}

void eraseString(STRING *self) {
	if ( self->length > 0 ) {
		free(self->buffer);
		self->buffer = (char*)calloc(1, sizeof(char));
		self->buffer[0] = '\0';
		self->length = 0;
	}
}

int getLengthString(STRING *self) {
	return self->length;
}

int findCharString(STRING *self, char letter) {
	int index = 0;
	int isFound = FALSE;

	for ( index = 0; index < self->length; index++ ) {
		if ( self->buffer[index] == letter ) {
			isFound = TRUE;
			break;
		}
	}

	if ( isFound == FALSE ) {
		index = -1;
	}

	return index;
}

char* findString(STRING *self, char *string) {
	int src_index = 0;
	int comp_index = 0;
	int foundIndex = -1;
	int matchLength = 0;
	int fullMatched = FALSE;

	while ( src_index < self->length ) {
		while ( comp_index < strlen(string) ) {
			if ( self->buffer[src_index] == string[comp_index] ) {
				if ( foundIndex == -1 ) {
					foundIndex = src_index;
				}
				matchLength++;
				comp_index++;
			}
			src_index++;
			if ( src_index >= (self->length - 1) ) {
				break;
			}
			if ( matchLength == strlen(string) ) {
				fullMatched = TRUE;
				break;
			}
		}
		if ( fullMatched == TRUE ) {
			break;
		}
	}

	return foundIndex;
}
int compareString(STRING *self, char *string) {
	int cmpResult;

	if ( self->length > 0 ) {
		cmpResult = strcmp(self->buffer, string);
	}

	return cmpResult;
}

char viewAtString(STRING *self, int index) {
	char found = '\0';

	if ( self->length > 0 && index < self->length ) {
		found = self->buffer[index];
	}

	return found;
}
