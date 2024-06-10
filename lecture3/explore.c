#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>


void travel(char *path)
{
    DIR *dir;
	char *childPath;
	int fd;
	struct dirent *entry;
	struct stat properties;
	int status;

	if(path == NULL){
		fprintf(stderr, "Error: path is NULL\n");
		exit(1);
	}

	dir = opendir(path);
	if(dir == NULL){
		fprintf(stderr, "Error: cannot open directory %s\n", path);
		exit(1);
	}

	entry = readdir(dir);
	while(entry != NULL){
			// skip the current and parent directory
			if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
				childPath = (char *)malloc(strlen(path) + strlen(entry->d_name) + 2);
				if(childPath == NULL){
					fprintf(stderr, "Error: cannot allocate memory\n");
					exit(1);
				}

				//use sprintf to concatenate the path
				sprintf(childPath, "%s/%s", path, entry->d_name);
				printf("%s\n", childPath);

				// read metadata of the file
				status = stat(childPath, &properties);
				if(status == -1){
					fprintf(stderr, "Error: cannot get properties of %s\n", childPath);
					exit(1);
				}

				if(S_ISDIR(properties.st_mode)){
					//travel(childPath);
				}
				free(childPath);
			}
			// why do we need to read the next entry?
			// because the current entry is not NULL
			// so we need to read the next entry
			// otherwise, the loop will never end
			// and the program will be stuck in the loop
			// forever	
			// so we need to read the next entry
			// to make the loop end
			// and the program can continue to run
			printf("in while loop entry is %s\n", entry->d_name);
			entry = readdir(dir);	
	}
	status = closedir(dir);
	if(status == -1){
		fprintf(stderr, "Error: cannot close directory %s\n", path);
		exit(1);
	}

}

//explore the directory as arg[1]
void main(int argc, char *argv[])
{
	if(argc != 2){
		fprintf(stderr, "Usage: %s <path>\n", argv[0]);
		exit(1);
	}	

	travel(argv[1]);		

}	
