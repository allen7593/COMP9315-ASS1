//
// Created by allen on 8/18/2018.
//
#include <stdio.h>
#include <stdlib.h>
#include "stringutils.h"

void testValidateIntSetRawValueValid();

void testValidateIntSetRawValueInvalid();

void testSplitStringAndSize();

void printList(char **list);


int main() {
    testValidateIntSetRawValueValid();
    testValidateIntSetRawValueInvalid();
    testSplitStringAndSize();
    return 0;
}

void testSplitStringAndSize() {
    char testStr1[] = "{ }";
    char testStr2[] = "{2,3,1}";
    char testStr3[] = "{6,6,6,6,6,6}";
    char testStr4[] = "{10, 9, 8, 7, 6,5,4,3,2,1}";
    char testStr5[] = "{1, 999, 13, 666, -5}";
    char testStr6[] = "{    1  ,  3  ,  5 , 7,9 }";
    char testStr7[] = "{    1  ,  3  ,  -5 , 7,9 }";
    int size = 0;

    printf("Testing: %s\n", testStr1);
    removeBraces(testStr1);
    removeSpaces(testStr1);
    char **list1 = splitCharStr(testStr1);
    size = getIntSetSize(list1);
    printf("Size= %i\n", size);
    printList(list1);

    printf("Testing: %s\n", testStr2);
    removeBraces(testStr2);
    removeSpaces(testStr2);
    char **list2 = splitCharStr(testStr2);
    size = getIntSetSize(list2);
    printf("Size= %i\n", size);
    printList(list2);

    printf("Testing: %s\n", testStr3);
    removeBraces(testStr3);
    removeSpaces(testStr3);
    char **list3 = splitCharStr(testStr3);
    size = getIntSetSize(list3);
    printf("Size= %i\n", size);
    printList(list3);

    printf("Testing: %s\n", testStr4);
    removeBraces(testStr4);
    removeSpaces(testStr4);
    char **list4 = splitCharStr(testStr4);
    size = getIntSetSize(list4);
    printf("Size= %i\n", size);
    printList(list4);

    printf("Testing: %s\n", testStr5);
    removeBraces(testStr5);
    removeSpaces(testStr5);
    char **list5 = splitCharStr(testStr5);
    size = getIntSetSize(list5);
    printf("Size= %i\n", size);
    printList(list5);

    printf("Testing: %s\n", testStr6);
    removeBraces(testStr6);
    removeSpaces(testStr6);
    char **list6 = splitCharStr(testStr6);
    size = getIntSetSize(list6);
    printf("Size= %i\n", size);
    printList(list6);

    printf("Testing: %s\n", testStr7);
    removeBraces(testStr7);
    removeSpaces(testStr7);
    char **list7 = splitCharStr(testStr7);
    size = getIntSetSize(list7);
    printf("Size= %i\n", size);
    printList(list7);
}

void printList(char **list) {
    char **testList = list;
    while (*testList != NULL) {
        printf("List Item: [%s]\n", *testList);
        testList++;
    }
}

void testValidateIntSetRawValueValid() {
    char testStr1[] = "{ }";
    char testStr2[] = "{2,3,1}";
    char testStr3[] = "{6,6,6,6,6,6}";
    char testStr4[] = "{10, 9, 8, 7, 6,5,4,3,2,1}";
    char testStr5[] = "{1, 999, 13, 666, -5}";
    char testStr6[] = "{    1  ,  3  ,  5 , 7,9 }";
    char testStr7[] = "{    1  ,  3  ,  -5 , 7,9 }";
    if (validateIntSetRawValue(testStr1) != 0) {
        printf("String %s valid failed\n", testStr1);
    }
    if (validateIntSetRawValue(testStr2) != 0) {
        printf("String %s valid failed\n", testStr2);
    }
    if (validateIntSetRawValue(testStr3) != 0) {
        printf("String %s valid failed\n", testStr3);
    }
    if (validateIntSetRawValue(testStr4) != 0) {
        printf("String %s valid failed\n", testStr4);
    }
    if (validateIntSetRawValue(testStr5) != 0) {
        printf("String %s valid failed\n", testStr5);
    }
    if (validateIntSetRawValue(testStr6) != 0) {
        printf("String %s valid failed\n", testStr6);
    }
    if (validateIntSetRawValue(testStr7) != 0) {
        printf("String %s valid failed\n", testStr7);
    }
}

void testValidateIntSetRawValueInvalid() {
    char testStr1[] = "{a,b,c}";
    char testStr2[] = "{ a, b, c }";
    char testStr3[] = "{1, 2.0, 3}";
    char testStr4[] = "{{1, {2,3}, 4}";
    char testStr5[] = "{1, 2, 3, 4, five}";
    char testStr6[] = "{ 1 2 3 4 }";
    char testStr7[] = "{ 1, .2, 3, 4 }";
    if (validateIntSetRawValue(testStr1) != -1) {
        printf("String %s valid failed\n", testStr1);
    }
    if (validateIntSetRawValue(testStr2) != -1) {
        printf("String %s valid failed\n", testStr2);
    }
    if (validateIntSetRawValue(testStr3) != -1) {
        printf("String %s valid failed\n", testStr3);
    }
    if (validateIntSetRawValue(testStr4) != -1) {
        printf("String %s valid failed\n", testStr4);
    }
    if (validateIntSetRawValue(testStr5) != -1) {
        printf("String %s valid failed\n", testStr5);
    }
    if (validateIntSetRawValue(testStr6) != -1) {
        printf("String %s valid failed\n", testStr6);
    }
    if (validateIntSetRawValue(testStr7) != -1) {
        printf("String %s valid failed\n", testStr6);
    }
}