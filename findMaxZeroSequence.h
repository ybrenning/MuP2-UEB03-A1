#ifndef FINDMAXZEROSEQUENCE_H
#define FINDMAXZEROSEQUENCE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

const unsigned short bit_count = 32;

int convertDezToDualString(const int64_t number, char *stringDualNumber);
void createComplementOnTwo(char *stringDualNumber);
unsigned short countMaxZeroSequence(const char *stringDualNumber);
void printDualString(const char *stringDualNumber);

#endif //FINDMAXZEROSEQUENCE_H
