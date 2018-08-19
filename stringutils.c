//
//
// Created by allen on 8/18/2018.
//
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include "stringutils.h"

char **splitCharStr(char *str) {
    char *iter = str;
    char **strList = NULL;
    char *p = NULL;
    p = strtok(iter, ",");
    int size = 0;

    while (p) {
        strList = realloc(strList, sizeof(char *) * ++size);
        strList[size - 1] = malloc(sizeof(char) * (strlen(strcat(p, "\0")) + 1));
        strcpy(strList[size - 1], strcat(p, "\0"));
        p = strtok(NULL, ",");
    }

    strList = realloc(strList, sizeof(char *) * size);
    strList[size] = NULL;
    return strList;
}

int validateIntSetRawValue(char *rawStr) {
    /*
     * The purpose of this check is to filter out the invalid raw input string
     * The logic of this check is after we find the first digit, to check if the follow char is either digit/space/comma.
     * Apart from all three types listed above, the other types are all invalid.
     *
     * This check will ignore special chars space , '- ' and ',' before digits
     * This Check only works for ASCII based string
     * */
    char *iter = rawStr;
    int valid = 0;
    int find = 0;
    if (iter[0] == '{' && iter[strlen(rawStr) - 1] == '}') {
        valid = 0;
    } else {
        valid = -1;
    }
    removeBraces(rawStr);
    while (*iter != '\0' && valid == 0) {
        if (isalpha((int) *iter)) { // If current char is not alphabet
            valid = -1;
        } else if (find == 0 && !(*iter == '-' || *iter == ' ' || *iter == ',' ||
                                  isdigit((int) *iter))) { // When we not find any digit, if current char is special char other than ' ', '-', ',' and digit
            valid = -1;
        } else if (isdigit((int) *iter) && isdigit((int) *(iter - 1)) &&
                   find == 1) { // When a digit found, current and previous char are all digits
            valid = 0;
        } else if (find == 0 && isdigit((int) *iter)) { // When current char is a digit, check find flag
            find = 1;
        } else if (find == 1 && *iter != ' ' &&
                   *iter != ',') { // When a digit found, current char is not space and comma
            valid = -1;
        } else if (*iter == ',') { // current char is a comma, uncheck check flag
            find = 0;
        }
        iter++;
    }
    return valid;
}

int getIntSetSize(char **rawValue) {
    int size = 0;
    char **iter = rawValue;
    while (*iter != NULL) {
        size++;
        iter++;
    }
    return size;
}

char **getUniqueItems(char **rawValue) {
    return NULL;
}

int strIn(char **str, char *target) {
    return 0;
}

int *convertCharToIntArray(char **str) {
    return NULL;
}

void removeSpaces(char *str) {
    int size = strlen(str);
    int spaceNum = countSpace(str);
    char *a = malloc(size - spaceNum + 1 * sizeof(char));
    char *i = a;
    char *j = str;
    while (*j != '\0') {
        *i = *j++;
        if (*i != ' ') {
            i++;
        }
    }
    *i = '\0';
    strcpy(str, a);
    free(a);
}

int countSpace(char *str) {
    int spaceNum = 0;
    char *iter = str;
    while (*iter) {
        if (*iter == ' ') {
            spaceNum++;
        }
        iter++;
    }
    return spaceNum;
}

void removeBraces(char *str) {
    int size = strlen(str);
    char *i = malloc((size - 1) * sizeof(char));
    initEmptyCharPtr(i, size - 1);
    char *j = str;
    int i_start = 0;
    int j_start = 1;
    int j_end = size - 1;

    for (; j_start < j_end; i_start++, j_start++) {
        i[i_start] = j[j_start];
    }
    i[i_start] = '\0';
    strcpy(str, i);
    free(i);
}

void initEmptyCharPtr(char *str, int size) {
    int i = 0;
    for (i = 0; i < size; i++) {
        str[i] = '\0';
    }
}