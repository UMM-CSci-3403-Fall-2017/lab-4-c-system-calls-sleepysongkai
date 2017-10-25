#include <stdio.h>
#include <sys/stat.h> 
#include <stdbool.h> 
#include <stdlib.h>
#include <dirent.h> 
#include <unistd.h>
#include <string.h>
#include <ftw.h>


static int num_dirs, num_regular;


static int callback(const char *fpath, const struct stat *sb, int typeflag) {
    // Define stuff here
    

    if (typeflag == FTW_F){                 //if the pointer points a regular file
    	num_regular = num_regular+1;}       //increase the number of file
    if (typeflag == FTW_D){                 //if we get a directory
	num_dirs = num_dirs +1;             //increase the number of directory
    }
    return 0;
}

#define MAX_FTW_DEPTH 16

int main(int argc, char** argv) {
    // Check arguments and set things up
    if (argc == 2) {
        printf ("Usage: %s <path>\n", argv[0]);
        printf ("       where <path> is the file or root of the tree you want to summarize.\n");
        return 1;
    }

    num_dirs = 0;
    num_regular = 0;

    ftw(argv[1], callback, MAX_FTW_DEPTH);
    
    // Print out the results
     printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_regular);

    return 0;
}
