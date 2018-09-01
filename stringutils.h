//
// Created by allen on 8/18/2018.
//

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

typedef struct IntSet {
    int val;
} IntSet;

int validateIntSetRawValue(char *rawStr);

//TODO: Need to be implemented
int *getUniqueItems(int *rawValue, int *size);

int listIn(int *list, int listSize, int target);

int strIn(char **str, const char *target);

char *convertIntArrToCharArr(int *intset, int size);

int countDigit(int num);

int *splitCharStr(char *str, int *size);

void removeSpaces(char *str);

int countSpace(char *str);

char *removeBraces(char *str);

void initEmptyCharPtr(char *str, int size);

int intset_binary_search(int *list, int size, int target);

#endif //STRINGUTILS_H
