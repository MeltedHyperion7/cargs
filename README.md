# CARGS
A light, dependency free, command line argument passing library in C.
## Usage
Include the library using  
`#include "cargs/cargs.h"`  
cargs exposes just two functions.  
### `cargsAddFlag`.
Used to register a flag. Takes the following arguments in order:  
- `flagCharacter` - The character that the flag would be set with. Can be set to '.' if you want to accept an argument without an accompanying flag.
- `verboseFlag` - An optional longer form for the flag. Can be set to NULL if you don't want it.
- `required` - If the flag is required. `cargsParseArguments` will return false if a required flag was not set or missing its argument.
- `set` - Pointer to a bool which would be set to true or false depending on wether the flag was set or not.
- `argument` - Set if the flag takes an additional argument, otherwise set to NULL. Pointer to a char pointer that will be set to the argv element that contains the flag's argument. If an argument wasn't provided, the pointer would be set to NULL.
### `cargsParseArguments`
Needs to be called once all flags have been registered. Returns true if all required flags were set and an argument was provided to every flag which expected one. An unrecognised flag or argument would cause `cargsParseArguments` to return false. Takes `argc` and `argv` as arguments.
## Examples
```c
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "cargs/cargs.h"

int main(int argc, char const *argv[]) {
    bool oFlagSet, sFlagSet, filePathSet;
    char* oFlagArgument, filePath;

    // -o registered as a compulsary flag which also takes an argument. Can also be passed in as --output
    cargsAddFlag('o', "output", true, &oSet, &oArgument);

    // -s registered as an optional flag
    cargsAddFlag('s', NULL, false, &sFlagSet, NULL);

    // take another necessary argument, without any flag 
    cargsAddFlag('.', NULL, true, &filePathSet, &filePath);

    // 
    bool res = cargsParseArguments(argc, argv);

    if(filePathSet) {
        printf("File path: %s\n", filePath);
    }

    if(oFlagSet) {
        printf("The o flag was set. Argument: %s\n", oFlagArgument);
    }

    if(sFlagSet) {
        printf("The s flag was set.\n", oFlagArgument);
    }

    return 0;
}
```