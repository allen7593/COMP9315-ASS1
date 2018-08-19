//
// Created by allen on 8/18/2018.
//

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

int validateIntSetRawValue(char *rawStr);

int getIntSetSize(char **rawValue);

//TODO: Need to be implemented
char **getUniqueItems(char **rawValue);

//TODO: Need to be implemented
int strIn(char **str, char *target);

//TODO: Need to be implemented
int *convertCharToIntArray(char **str);

char **splitCharStr(char *str);

void removeSpaces(char *str);

int countSpace(char* str);

void removeBraces(char *str);

void initEmptyCharPtr(char* str, int size);
#endif //STRINGUTILS_H
