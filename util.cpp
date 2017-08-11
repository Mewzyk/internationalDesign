/* until.cpp 
 * file for commandline and file management
 *
 * last edit:
 * 8/11 Bre
 */

#include <iostream>
#include <getopt.h>
#include "util.h"
#include <cstdio>

using namespace std;


//static int verboseFlag;

//parseCL
int parseCL(int argc, char** argv){
	int c; 
	int returnVal = CL_SUCCESS; //assume success
	static struct option long_options[] = {
	       	/* These options set a flag. 
		 * Keeping this commented in case we have arguments to set flags for*/ 
		//{"verbose", no_argument,       &verboseFlag, 1},
		//{"brief",   no_argument,       &verboseFlag, 0},
		/* These options don’t set a flag.
		*              We distinguish them by their indices. */
		{"help",    no_argument,       0, 'h'},
		{"new",     no_argument,       0, 'n'},
		//{"delete",  required_argument, 0, 'd'},
		{0, 0, 0, 0}
	};
	int optionIndex = 0;

	//getopt returns -1 when done, 0 if a flag needs to be set
	while((c = getopt_long(argc, argv, "hn", long_options, &optionIndex)) != -1){	

		switch (c) {
			case 0:
				/* If this option set a flag, do nothing else now. */
			        if (long_options[optionIndex].flag != 0)
					break;
				printf ("option %s", long_options[optionIndex].name);
			        if (optarg)
					printf (" with arg %s", optarg);
				printf("\n");
				break;	  
			case 'h':
				cout << "Need Help? Here are the available options:" << endl 
					<< "-h	--help		prints available options and useful information." << endl
					<< "-n	--new-game	begins new game." << endl;
			       			       
				break;

		        case 'n':
				returnVal = CL_NEWGAME;
				break;
		        case '?':												         
				/* getopt_long already printed an error message. */
				cout << "Oops! Need help? Use the -h or --help option for more info" << endl;	
				returnVal = CL_ERROR;
				break;
	    	        default:
				cout << "Something went wrong" << endl;
				returnVal = CL_ERROR;
				break;
		}
	}

	  /* Instead of reporting ‘--verbose’
	   *      and ‘--brief’ as they are encountered,
	   *           we report the final status resulting from them. */
	 // if (verbose_flag)
	//	      puts ("verbose flag is set");

	/* Print any remaining command line arguments (not options). */
	if (optind < argc){
		printf ("non-useful ARGV-elements: ");
		while (optind < argc){
			printf ("%s ", argv[optind++]);
		}
		putchar ('\n');
	}
	if (argc == 1){
		cout << "Please enter a command" << endl;
		cout << "Oops! Need help? Use the -h or --help option for more info" << endl;	
		returnVal = CL_ERROR;
	}
	return returnVal;
}
