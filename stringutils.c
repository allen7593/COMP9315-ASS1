//
//
// Created by allen on 8/18/2018.
//
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "stringutils.h"

char **splitCharStr(char *str) {
    char *iter = str;
    char **strList = NULL;
    char *p = NULL;
    p = strtok(iter, ",");
    int size = 0;

    while (p) {
        // TODO: use repalloc instaad
        strList = realloc(strList, sizeof(char *) * ++size);
        // TODO: use pmalloc instaad
        strList[size - 1] = malloc(strlen(strcat(p, "\0")) + 1);
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
    char* newStr= NULL;
    if (iter[0] == '{' && iter[strlen(rawStr) - 1] == '}') {
        valid = 0;
    } else {
        valid = -1;
    }
    newStr = removeBraces(rawStr);
    iter = newStr;
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

int strIn(char **str, const char *target) {
    char **head = str;
    while (*head != NULL) {
        if (strcmp(*head, target) == 0) {
            return 0;
        }
        head++;
    }
    return 1;
}

int *convertCharArrToIntArr(char **str) {
    int size = getIntSetSize(str);
    // TODO: use pmalloc instaad
    int *intset = malloc((size + 1) * sizeof(int));
    int *inthead = intset;
    char **head = str;

    while (*head != NULL) {
        *inthead = atoi(*head);
        inthead++;
        head++;
    }
    return intset;
}

char *convertIntArrToCharArr(int *intset, int size) {
    int *inthead = intset;
    int *intend = inthead + size;
    int digits = 0;
    int memToSet = 0;
    int accumSize = 0;
    int first = 1;
    char delimeter = ',';
    char *result = NULL;
    char *tmp = NULL;
    char *tmpNum = NULL;
    char *tmpReuslt = NULL;

    if (size == 0) {
        return NULL;
    }

    while (inthead < intend) {
        digits = countDigit(*inthead);
        memToSet = digits + 1;
        if (inthead == intset) {
            delimeter = ' ';
        }
        accumSize += memToSet;
        // TODO: use pmalloc instaad
        tmp = malloc(memToSet * sizeof(char));
        // TODO: use pmalloc instaad
        tmpNum = malloc(digits * sizeof(char));
        sprintf(tmpNum, "%d", *inthead);
        strcpy(tmp, strcat(&delimeter, tmpNum));
        if (result != NULL) {
            first = 0;
        }
        // TODO: use repalloc instaad
        tmpReuslt = realloc(result, sizeof(char) * accumSize);
        result = tmpReuslt;
        tmpReuslt = NULL;
        if (first == 0) {
            strcat(result, tmp);
        } else {
            strcpy(result, tmp);
        }

        tmp = NULL;
        tmpNum = NULL;

        digits = 0;
        delimeter = ',';
        inthead++;
    }
    removeSpaces(result);
    return result;
}

int countDigit(int num) {
    int target = num;
    int digits = 0;
    if (num < 0) {
        digits = 1;
        target = target * -1;
    } else if (num == 0) {
        return 1;
    }
    while (target != 0) {
        digits++;
        target /= 10;
    }
    return digits;
}

void removeSpaces(char *str) {
    int size = strlen(str);
    int spaceNum = countSpace(str);
    // TODO: use pmalloc instaad
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

char* removeBraces(char *str) {
    int size = strlen(str);
    // TODO: use pmalloc instaad
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
    return i;
}

void initEmptyCharPtr(char *str, int size) {
    int i = 0;
    for (i = 0; i < size; i++) {
        str[i] = '\0';
    }
}