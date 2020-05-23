#include "cargs.h"
#include "flagLinkedList.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct flagLinkedNode* cargs_flags_list = NULL;

void addFlag(char flagCharacter, char* verboseFlag, bool required, bool* set, char** argument) {
    struct flag flag = {
        flagCharacter,
        verboseFlag,
        required,
        set,
        argument
    };
    
    // initialize
    *(flag.set) = false;

    addFlagLinkedNode(&cargs_flags_list, flag);
}

// * if the last flag expects an argument, pass it in without considering if it is a flag
// * quotes don't appear in argv
bool parseArguments(int argc, char const *argv[]) {
    char* clArg;
    bool success = true;
    bool flagArgumentNext = false;

    // stores the ndoe of the current flag being read
    // if the flag required an argument, [flagNode] would retain its value
    // so that an argument can be matched to it on the next iteration
    struct flagLinkedNode* flagNode = NULL;

    for(int i = 1; i < argc; i++) {
        clArg = argv[i];
        if(flagArgumentNext) {
            // the last flag that was parsed takes an argument
            *(flagNode->flag.argument) = clArg;
            // ? should we check, after the loop, if the last flag expected an argument and
            // ? if it was not set then set the "set" flag for that flag to false

            flagArgumentNext = false;
        } else {
            if(strlen(clArg) > 2 && clArg[0] == '-' && clArg[1] == '-') {
                // verbose flag
                // TODO match verbose flags
            } else if(clArg[0] == '-') {
                // normal flag

                if(strlen(clArg) != 2) {
                    success = false;
                }

                char flagCharacter = clArg[1];
                flagNode = findNodeFromFlagCharacter(cargs_flags_list, flagCharacter);
                if(flagNode == NULL) {
                    // unknown flag
                    success = false;
                } else {
                    *(flagNode->flag.set) = true;
                    flagArgumentNext = flagNode->flag.argument != NULL;
                }
            } else {
                // non flag argument
                // could register these under the '.' flag
                // order is determined by the onder in which the flags were
                // registered
            }
        }
    }

    // TODO check if any required flags were not set
    // TODO check if any flags which requried an argument were set but were not given an argument

    freeFlagLinkedNode(cargs_flags_list);
    return success;

}
