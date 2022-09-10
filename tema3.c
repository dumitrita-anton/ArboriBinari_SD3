/* Anton Dumitrita 324CB */
#include "arb.h"

#define MAX_INPUT_LINE_SIZE 100
#define MAX_NAME 25

void touch(Dir* parent, char* name) {

	/*check if a directory with the given name already exist*/
	if(searchDir(parent->directories, name) == 0) {
		printf("Directory %s already exists!\n", name);
		return;
	}

	/*check if a file with the given name already exits*/
	if(searchFile(parent->files, name) == 0) {
		printf("File %s already exists!\n", name);
		return;
	}

	/*create file node with given name*/
	if(parent->files == NULL) {
		File * aux = alocFile(name);

		if(aux == NULL) 
			return;

		aux->parent = parent;
		aux->left = NULL;
		aux->right = NULL;
		parent->files = aux;
	}
	else {
		/*insert into parent->files in order*/
		InsertFile(parent->files, name);
	}

}

void mkdir(Dir* parent, char * name) {
	/*check if a directory with the given name already exist*/
	if(searchDir(parent->directories, name) == 0) {
		printf("Directory %s already exists!\n", name);
		return;
	}

	/*check if a file with the given name already exits*/
	if(searchFile(parent->files, name) == 0) {
		printf("File %s already exists!\n", name);
		return;
	}

	/*create dir node with given name*/
	if(parent->directories == NULL) {
		Dir * aux = alocDir(name);

		if(aux == NULL) {
			return;
		}
		aux->left = NULL;
		aux->right = NULL;
		aux->parent = parent;
		aux->directories = NULL;
		aux->files = NULL;
		parent->directories = aux;
	} else {
		/*insert into parent->directories in order*/
		InsertDir(parent->directories, name);
	}
}

void ls (Dir* parent) {
	File * headF = parent->files;
	Dir * headD = parent->directories;

	/*print tree of directories*/
	if(headD) {
		printDirs(headD);
	}

	/*print tree of files*/
	if(headF) {
		printFiles(headF);
	}

	printf("\n");
}

void rm (Dir * parent, char * name) {
	/*check if file exists*/
	if(searchFile(parent->files, name) == 1) {
		printf("File %s doesn't exist!\n", name);
		return;
	}

	/*delete node from tree of files*/
	File * headF = parent->files;
	if(headF) {
		parent->files = deleteFile(parent->files, name);
		
	}
}

void rmdir(Dir *parent, char * name) {
	/*check if directory exits*/
	if(searchDir(parent->directories, name) == 1) {
		printf("Directory %s doesn't exist!\n", name);
		return;
	}

	/*delete node from tree of directories*/
	Dir * headD = parent->directories;
	if(headD) {
		parent->directories = deleteDir(parent->directories, name);
	}
}

void cd (Dir **target, char * name) {
	
	/* ".." case*/
	if(strcmp(name, "..") == 0) {
		if((*target)->parent == NULL)
			return;
		else {
			(*target) = (*target)->parent;
			return;
		}
	}

	Dir *headD = (*target)->directories;
	if(headD == NULL || (searchHelperDir(headD, name) == NULL)) {
		printf("Directory not found!\n");
		return;
	}

	(*target) = searchHelperDir(headD, name);

}

char *pwd (Dir* target) {
	char * path = (char *)malloc(sizeof(MAX_INPUT_LINE_SIZE));
	int contor = 0;
	/*add root as first director of the path*/
	strcpy(path, "/root");

	/*count all directories of the path*/
	Dir * p;
	for(p = target; p != NULL; p = p->parent) {
		contor++;
	}

	/*substract root*/
	contor--;

	/*store name of all directories of path*/
	char **pathContent = malloc(contor * sizeof(char *));
	int i;
	for(i = 0; i < contor; i++)
		pathContent[i] = malloc(MAX_NAME * sizeof(char));

	for(i = 0 ;target->parent != NULL; target = target->parent) {
		strcpy(pathContent[i], target->name);
		i++;
	}

	/*create variable path with values stored earlier*/
	for(i = contor - 1; i >= 0; i--)
	{
		strcat(path, "/");
		strcat(path, pathContent[i]);
	}

	// for(i = 0; i < contor; i++)
	// 	free(pathContent[i]);	
	// free(pathContent);

	return path;
	
}

int main() {
    
    char *line = (char *)calloc(MAX_INPUT_LINE_SIZE, sizeof(char)); 
	char *command;
	fgets(line, MAX_INPUT_LINE_SIZE, stdin);

	/*create root directory*/
    Dir *root = alocDir((char *)"root");
    root->parent = NULL;
    root->left = NULL;
    root->right = NULL;
	root->directories = NULL;
	root->files = NULL;

	/*init current directory*/
    Dir* crt_dir = root;

   /*read and execute commands*/
    do
	{
		command = strtok(line, " ");

		/*touch*/
		if(strcmp(command, "touch") == 0) {
			command = strtok(NULL, "\n");
			touch(crt_dir, command);
		}

		/*mkdir*/
		if(strcmp(command, "mkdir") == 0) {
			command = strtok(NULL, "\n");
			mkdir(crt_dir, command);
		}

		/*rm*/
		if(strcmp(command, "rm") == 0) {
			char *name = strtok(NULL, "\n");
			rm(crt_dir, name);
		}

		/*ls*/
		if(strcmp(command, "ls\n") == 0) {
			ls(crt_dir);
		}

		/*rmdir*/
		if(strcmp(command, "rmdir") == 0) {
			char *name = strtok(NULL, "\n");
			rmdir(crt_dir, name);
		}

		/*cd*/
		if(strcmp(command, "cd") == 0) {
			char * name = strtok(NULL, "\n");
		 	cd(&crt_dir, name);
		 }

		/*pwd*/
		if(strcmp(command, "pwd\n") == 0) {
			char * path = pwd(crt_dir);
			printf("%s\n", path);
			//free(path);
		}

		/*quit*/
		if(strcmp(command, "quit\n") == 0){
			break;
		}
		
		fgets(line, MAX_INPUT_LINE_SIZE, stdin);
	} while (1);

	free(line);
	freeTreeDir(&root->directories);
	freeTreeFile(&root->files);
	free(root->name);
	free(root);
    
    return 0;
}

