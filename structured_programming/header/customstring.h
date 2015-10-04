/*
 * string.h
 *
 *  Created on: 2014. 10. 27.
 *      Author: suandkyu
 */

#ifndef STRING_H_
#define STRING_H_

//#define DEBUG_STRING 1

typedef struct _tag_STRING STRING;

typedef struct _tag_STRING {
	char *buffer;
	int length;
} STRING;

void createString(STRING *self);
void destroyString(STRING *self);
void setString(STRING *self, char *string);
char* getString(STRING *self);
void appendString(STRING *self, char *string);
void eraseString(STRING *self);
int getLengthString(STRING *self);
int findCharString(STRING *self, char letter);
char* findString(STRING *self, char *string);
int compareString(STRING *self, char *string);
char viewAtString(STRING *self, int index);

#endif /* STRING_H_ */
