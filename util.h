#ifndef UTIL_H
#define UTIL_H

using namespace std;

//#defines for commandline and errors
#define CL_ERROR -1
#define CL_SUCCESS 0 
#define CL_HELP 1
#define CL_NEWGAME 2
#define CL_MAKE_MOVE 3

//function to parse commandline entry. returns one of the above commandline #defs 
int parseCL(int argc, char** argv);

#endif //UTIL_H
