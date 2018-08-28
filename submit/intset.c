/*
 * src/tutorial/complex.c
 *
 ******************************************************************************
  This file contains routines that can be bound to a Postgres backend and
  called by the backend in the process of processing queries.  The calling
  format for these routines is dictated by Postgres architecture.
******************************************************************************/

#include "postgres.h"

#include "fmgr.h"
#include "c.h"

typedef struct IntSet {
    int val;
} IntSet;

int validateIntSetRawValue(char *rawStr);

int getIntSetSize(char **rawValue);

int strIn(char **str, const char *target);

int *convertCharArrToIntArr(char **str);

char *convertIntArrToCharArr(int *intset, int size);

int countDigit(int num);

int *splitCharStr(char *str, int *size);

void removeSpaces(char *str);

int countSpace(char *str);

char *removeBraces(char *str);

void initEmptyCharPtr(char *str, int size);

int *convertIntSetArrToIntArr(struct IntSet *intSet, int *size);

void printList(int *list, int size);

char *addBraces(char *result, int accumSize);

int listIn(int *list, int listSize, int target);

int *getUniqueItems(int *rawValue, int *size);

PG_MODULE_MAGIC;

/*****************************************************************************
 * Input/Output functions
 *****************************************************************************/

PG_FUNCTION_INFO_V1(intset_in);

Datum
intset_in(PG_FUNCTION_ARGS) {
    char *str = PG_GETARG_CSTRING(0);
    int size = 0;
    int *charlist = NULL;
    int *intlist = NULL;
    int i = 0;
    char *tmpStr = palloc(strlen(str));
    strcpy(tmpStr, str);

    int test = validateIntSetRawValue(tmpStr);
    if (test != 0)
        ereport(ERROR,
                (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
                        errmsg("invalid input syntax for intset: \"%s\" %i",
                               tmpStr, test)));
    tmpStr = removeBraces(tmpStr);
    removeSpaces(tmpStr);
    intlist = splitCharStr(tmpStr, &size);
    intlist = getUniqueItems(intlist, &size);
    struct varlena *result = (struct varlena *) palloc((size + 1) * sizeof(struct IntSet) + 4);
    SET_VARSIZE(result, (size + 1) * sizeof(struct IntSet));

    IntSet *a = (IntSet *) ((int32_t) result + 4);
    for (i = 0; i < size; i++, intlist++) {
        a[i].val = *intlist;
    }
    a[size].val = 0;

    PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(intset_out);

Datum
intset_out(PG_FUNCTION_ARGS) {
    struct varlena *b = PG_GETARG_VARLENA_P(0);

    IntSet *c = VARDATA(b);
    char *result;
    int n = VARSIZE(b) / sizeof(struct IntSet);

    int *intArr = convertIntSetArrToIntArr(c, &n);

    char *charlist = convertIntArrToCharArr(intArr, n);
    PG_RETURN_CSTRING(charlist);
}

void printList(int *list, int size) {
    int *testList = list;
    int i = 0;
    for (i = 0; i < size; i++) {
        ereport(NOTICE, (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION), errmsg("List Item: [%i]", *(testList + i))));
    }
}

int *convertIntSetArrToIntArr(struct IntSet *intSet, int *size) {
    (*size)--;
    int *intArr = palloc((*size) * sizeof(int));
    int i = 0;
    for (i = 0; i < *size; i++) {
        intArr[i] = intSet[i].val;
    }
    return intArr;
}

int *splitCharStr(char *str, int *size) {
    char *iter = str;
    char *p = NULL;
    int *intList = NULL;
    int *tmpList = NULL;
    p = strtok(iter, ",");
    *size = 0;
    while (p) {
        ++(*size);
        if (*size == 1) {
            tmpList = palloc(sizeof(int) * (*size));
        } else {
            tmpList = repalloc(intList, sizeof(int) * (*size));
        }
        intList = tmpList;
        *(intList + *size - 1) = atoi(p);
        p = strtok(NULL, ",");
    }
    return intList;
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
    char *newStr = NULL;
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
    int *intset = palloc((size + 1) * sizeof(int));
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
    int i = 0, digits = 0, memToSet = 0, accmSize = 0;
    char *finalResult = NULL, *tmpResult = NULL, *separator = NULL, *tmpNum = NULL, *midStr = NULL;
    for (i = 0; i < size; i++) {
        // Setup separator
        if (separator == NULL && i == 0) {
            separator = malloc(1);
            strcpy(separator, " ");
        } else if (strcmp(separator, " ") == 0 && i > 0) {
            strcpy(separator, ",");
        }

        // calculate mem allocation size
        digits = countDigit(*(intset + i)) + 1;
        memToSet = digits + 1;
        accmSize += memToSet;

        // allocate mem for final result
        if (i == 0 && finalResult == NULL) {
            tmpResult = malloc(accmSize * sizeof(char));
        } else {
            tmpResult = realloc(finalResult, accmSize * sizeof(char));
        }

        // Allocation failed
        if (tmpResult != NULL) {
            finalResult = tmpResult;
        } else {
            printf("Error");
            return NULL;
        }

        // tmpNum
        tmpNum = malloc(digits * sizeof(char));
        // midStr
        midStr = malloc(memToSet * sizeof(char));

        strcpy(midStr, separator);
        sprintf(tmpNum, "%i", *(intset + i));
        strcat(midStr, tmpNum);

        if (i == 0) {
            strcpy(finalResult, midStr);
        } else {
            strcat(finalResult, midStr);
        }

        free(tmpNum);
        free(midStr);

        digits = 0;
        memToSet = 0;
    }
    removeSpaces(finalResult);
    finalResult = addBraces(finalResult, strlen(finalResult));
    return finalResult;
}

char *addBraces(char *result, int accumSize) {
    int newSize = accumSize + 2;
    char *newStr = malloc(newSize);
    int i = 0;
    strcpy(newStr, "{");
    newStr = strcat(newStr, result);
    strcat(newStr, "}");
    return newStr;
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
    char *a = palloc(size - spaceNum + 1 * sizeof(char));
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

char *removeBraces(char *str) {
    int size = strlen(str);
    // TODO: use pmalloc instaad
    char *i = palloc((size - 1) * sizeof(char));
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

int *getUniqueItems(int *rawValue, int *size) {
    int *finalList = NULL, *tmpList = NULL;
    int i = 0;
    int newSize = 0;
    for (i = 0; i < *size; i++) {
        if (newSize == 0) {
            tmpList = malloc(sizeof(int));
            newSize++;
            tmpList[0] = *(rawValue + i);
        } else if (listIn(finalList, newSize, *(rawValue + i))) {
            tmpList = realloc(finalList, (++newSize) * sizeof(int));
            *(tmpList + newSize - 1) = *(rawValue + i);
        }
        finalList = tmpList;
    }
    *size = newSize;
    return finalList;
}

int listIn(int *list, int listSize, int target) {
    int *listHead = list;
    int i = 0;
    for (i = 0; i < listSize; i++) {
        if (*(listHead + i) == target) {
            return 0;
        }
    }
    return 1;
}