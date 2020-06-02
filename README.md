# CARGS
A light, dependency free, command line argument passing library in C.
## Usage
Include the library using  
`#include "cargs/cargs.h"`  
cargs exposes just two functions.  
### `cargsAddFlag`. Used to register a flag.
Arguments in order:  
- `flagCharacter` - The character that the flag would be set with. Can be set to '.' if you want to accept an argument without an accompanying flag.
- `verboseFlag` - An optional longer form for the flag. Can be set to NULL if you don't want it.
- `required` - If the flag is required. `cargsParseArguments` will return false if a required flag was not set or missing its argument.
- `set` - Pointer to a bool which would be set to true or false depending on wether the flag was set or not.
- `argument` - Set if the flag takes an additional argument, otherwise set to NULL. Pointer to a char pointer that will be set to the argv element that contains the flag's argument. If an argument wasn't provided, the pointer would be set to NULL.
### `cargsParseArguments`. Needs to be called once all flags have been registered.
## Example
<!-- TODO add examples -->