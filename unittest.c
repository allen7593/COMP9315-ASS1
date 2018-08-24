//
// Created by allen on 8/18/2018.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringutils.h"

void testValidateIntSetRawValueValid();

void testValidateIntSetRawValueInvalid();

void testSplitStringAndSize();

void printList(char **list);

void testStrIn();

void testConvertCharArrToIntArr();

void testCountDigits();

void testConvertIntArrToCharArr();

void testIntegrate();

int main() {
    testValidateIntSetRawValueValid();
    testValidateIntSetRawValueInvalid();
    testSplitStringAndSize();
    testStrIn();
    testConvertCharArrToIntArr();
    testCountDigits();
    testConvertIntArrToCharArr();
    testIntegrate();
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

//    free(list1);;
//    free(list2);
//    free(list3);
//    free(list4);
//    free(list5);
//    free(list6);
//    free(list7);
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
    char testStr8[] = "{ 1, ,,, 4 }";
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
        printf("String %s valid failed\n", testStr7);
    }
    if (validateIntSetRawValue(testStr8) != -1) {
        printf("String %s valid failed\n", testStr8);
    }
}

void testStrIn() {
    char **charlist = malloc(4 * sizeof(char *));
    int i = 0;
    for (i = 0; i < 3; i++) {
        charlist[i] = malloc(5 * sizeof(char));
        sprintf(charlist[i], "%d", i);
    }
    charlist[i] = NULL;

    if (strIn(charlist, "0") != 0) {
        printf("String not contain: %s", "0");
    }
    if (strIn(charlist, "1") != 0) {
        printf("String not contain: %s", "1");
    }
    if (strIn(charlist, "2") != 0) {
        printf("String not contain: %s", "2");
    }
    if (strIn(charlist, "4") == 0) {
        printf("String contain: %s", "4");
    }
}

void testConvertCharArrToIntArr() {
    char **charlist = malloc(3 * sizeof(char *));
    int i = 0;
    for (i = 0; i < 3; i++) {
        charlist[i] = malloc(5 * sizeof(char));
        sprintf(charlist[i], "%d", i);
    }
    charlist[i] = NULL;
    // Size of the array is important
    int size = getIntSetSize(charlist);

    int *intset = convertCharArrToIntArr(charlist);
    int *inthead = intset;
    int *intend = inthead + size;
    printf("Test Convert CharArr To IntArr----- \n");
    while (inthead < intend) {
        printf("List Item:[%i]\n", *inthead);
        inthead++;
    }
//    free(charlist);
//    free(intset);
}

void testCountDigits() {
    int test1 = 1234;
    int test2 = 1;
    int test3 = 1234567;
    int test4 = -234;
    int testValue = 0;
    int failCount = 0;
    printf("Start testing count digits---------------\n");
    if (countDigit(testValue) != 1) {
        failCount++;
        printf("%i, digits count incorrect", testValue);
    }
    testValue = test1;
    if (countDigit(testValue) != 4) {
        failCount++;
        printf("%i, digits count incorrect", testValue);
    }
    testValue = test2;
    if (countDigit(testValue) != 1) {
        failCount++;
        printf("%i, digits count incorrect", testValue);
    }
    testValue = test3;
    if (countDigit(testValue) != 7) {
        failCount++;
        printf("%i, digits count incorrect", testValue);
    }
    testValue = test4;
    if (countDigit(testValue) != 4) {
        failCount++;
        printf("%i, digits count incorrect", testValue);
    }
    printf("End testing count digits---------------\n");
    printf("Fail Count: %i\n", failCount);
}

void testConvertIntArrToCharArr() {
    int test1[] = {1, 2, 3, 4, 5, 6};
    int test2[] = {1, 22, 333, 4444, 5555, 666666};
    int test3[] = {0, -22, 333, 4444, 5555, 666666};
    int test4[] = {0, -22, 333, 4444, 5555, 666666, 7777777};
    int test5[] = {};
    char *testResult = NULL;

    printf("Start testing IntArrToCharArr---------------\n");
    testResult = convertIntArrToCharArr(test1, 6);
    printf("Test1 Result: %s\n", testResult);

    testResult = convertIntArrToCharArr(test2, 6);
    printf("Test2 Result: %s\n", testResult);

    testResult = convertIntArrToCharArr(test3, 6);
    printf("Test3 Result: %s\n", testResult);

    testResult = convertIntArrToCharArr(test4, 7);
    printf("Test4 Result: %s\n", testResult);

    testResult = convertIntArrToCharArr(test5, 0);
    printf("Test5 Result: %s\n", testResult);
    printf("End testing IntArrToCharArr---------------\n");
}

void testIntegrate() {
    char *str = NULL;
    int size = 0;
    char **charlist = NULL;
    int *intlist = NULL;
    int i = 0;

    str = malloc(5);
    strcpy(str, "{1,2,3}");

    if (validateIntSetRawValue(str) != 0)
        printf("Error");

    str = removeBraces(str);
    printf("%s\n", str);
    removeSpaces(str);
    printf("%s\n", str);
    charlist = splitCharStr(str);
    printList(charlist);
    size = getIntSetSize(charlist);
    printf("%i\n", size);
    intlist = convertCharArrToIntArr(charlist);

    IntSet *result = malloc(size * sizeof(IntSet));
    for (i = 0; i < size; i++, intlist++) {
        result[i].val = *intlist;
    }
}
