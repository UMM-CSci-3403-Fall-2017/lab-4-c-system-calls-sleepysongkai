#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;

bool is_dir(const char* path) {
  /*
   * Use the stat() function (try "man 2 stat") to determine if the file
   * referenced by path is a directory or not.  Call stat, and then use
   * S_ISDIR to see if the file is a directory. Make sure you check the
   * return value from stat in case there is a problem, e.g., maybe the
   * the file doesn't actually exist.
   */
	int s;
	struct stat buf;
	s=stat(path,&buf);
	
	if (s!=0){
		return false;
	}else{
		return (S_ISDIR(buf.st_mode));
	}
		
}

/* test_data/loads_o_files/
 * I needed this because the multiple recursion means there's no way to
 * order them so that the definitions all precede the cause.
 */
void process_path(const char*);

void process_directory(const char* path) {
  /*
   * Update the number of directories seen, use opendir() to open the
   * directory, and then use readdir() to loop through the entries
   * and process them. You have to be careful not to process the
   * "." and ".." directory entries, or you'll end up spinning in
   * (infinite) loops. Also make sure you closedir() when you're done.
   *
   * You'll also want to use chdir() to move into this new directory,
   * with a matching call to chdir() to move back out of it when you're
   * done.
   */
	DIR *dp;
	struct dirent *entry;
	
	dp = opendir(path);             //get a directory based on path 
	if(dp == NULL){                 //if the dirctory is empty
		return;                 //return
	}	
	chdir(path);                    
	num_dirs = num_dirs+1;          //increase the directory number
	entry = readdir(dp);		
	while(entry != NULL){           //go down to the sub-directory
		if (strcmp(".",entry->d_name)!=0&&strcmp("..",entry->d_name)!=0){ //check "." and "..", in case we fall into infinite loop.
			process_path(entry->d_name);
		}
		entry = readdir(dp);  
	
	}
	//return to the previous directory and close now dirctory
	chdir("..");
	closedir(dp);
	

}

void process_file(const char* path) {
  /*
   * Update the number of regular files.
   */
	num_regular = num_regular+1;
}

void process_path(const char* path) {
  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  process_path(argv[1]);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
