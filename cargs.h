#ifndef _CARGS_H
#define _CARGS_H

#include <stdbool.h>

#include "flagLinkedList.h"

void cargsAddFlag(char flagCharacter, char* verboseFlag, bool required, bool* set, char** argument);

bool cargsParseArguments(int argc, char const *argv[]);

#endif