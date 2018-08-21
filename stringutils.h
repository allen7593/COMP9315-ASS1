//
// Created by allen on 8/18/2018.
//

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

int validateIntSetRawValue(char *rawStr);

int getIntSetSize(char **rawValue);

//TODO: Need to be implemented
char **getUniqueItems(char **rawValue);

int strIn(char **str, const char *target);

int *convertCharArrToIntArr(char **str);

char *convertIntArrToCharArr(int *intset, int size);

int countDigit(int num);

char **splitCharStr(char *str);

void removeSpaces(char *str);

int countSpace(char *str);

void removeBraces(char *str);

void initEmptyCharPtr(char *str, int size);

#endif //STRINGUTILS_H
