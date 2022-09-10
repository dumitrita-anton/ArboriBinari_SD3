/* Anton Dumitrita 324CB */
#include "arb.h"


Dir* alocDir(char * name) {
    Dir * dir = (Dir *)calloc(1, sizeof(Dir));

    if(!dir) {
        return NULL;
    }

    dir->name = (char *)malloc(sizeof(name));
    strcpy(dir->name, name);
    return dir;
}

File* alocFile(char* name) {
    File *file = (File *)calloc(1, sizeof(File));

    if(!file) {
        return NULL;
    }

    file->name = (char *)malloc(sizeof(name));
    strcpy(file->name, name);
    return file;
}

int searchDir(Dir * dir, char * name) {
    if(dir == NULL)
        return 1;

    if(strcmp(dir->name, name) == 0) 
        return 0;
    
    if(strcmp(dir->name, name) > 0) {
        return searchDir(dir->left, name);
    }
    else {
        return searchDir(dir->right, name);
    }
}

int searchFile(File * file, char * name) {
    if(file == NULL)
        return 1;

    if(strcmp(file->name, name) == 0) 
        return 0;
    
    if(strcmp(file->name, name) > 0) {
        return searchFile(file->left, name);
    }
    else {
        return searchFile(file->right, name);
    }
}

Dir* searchHelperDir(Dir * dir, char * name) {
	if(dir == NULL)
        return NULL;

    if(strcmp(dir->name, name) == 0) 
        return dir;
    
    if(strcmp(dir->name, name) > 0) {
        return searchHelperDir(dir->left, name);
    }
    else {
        return searchHelperDir(dir->right, name);
    }
}

Dir* searchHelperFile(File * file, char * name) {
	if(file == NULL)
        return NULL;

    if(strcmp(file->name, name) == 0) 
        return file->parent;
    
    if(strcmp(file->name, name) > 0) {
        return searchHelperFile(file->left, name);
    }
    else {
        return searchHelperFile(file->right, name);
    }
}

/*iterative function to insert file into bst*/
void InsertFile(File *file, char * name) {
    File *aux, *parent, *crt;
    /*create new node*/
    aux = alocFile(name);
    aux->left = NULL;
    aux->right = NULL;
    aux->parent = file->parent;
    
    /*init pointers for crossing file tree*/
    parent = NULL;
    crt = file;
    
    /*traverse tree to find parent of the node with the given name*/
    while(crt != NULL) {
        parent = crt;
        if(strcmp(name, crt->name) < 0) {
            crt = crt->left;
        }
        else {
            crt = crt->right;
        }
    }

    /*insert new node*/
    if(strcmp(name, parent->name) < 0) {
        parent->left = aux;
    }
    else {
        parent->right = aux;
    }
}

/*iterative function to insert directory into bst*/
void InsertDir(Dir *dir, char * name) {
    Dir * aux, *parent, *crt;

    /*create new node*/
    aux = alocDir(name);
    aux->left = NULL;
    aux->right = NULL;
    aux->parent = dir->parent;
    aux->directories = NULL;
    aux->files = NULL;
    
    /*init pointers for crossing dir tree*/
    parent = NULL;
    crt = dir;

    /*traverse tree to find parent of the node with the given name*/
    while(crt != NULL) {
        parent = crt;
        if(strcmp(name, crt->name) < 0) {
            crt = crt->left;
        }
        else {
            crt = crt->right;
        }
    }

    /*insert new node*/
    if(strcmp(name, parent->name) < 0) {
        parent->left = aux;
    }
    else {
        parent->right = aux;
    }

}

/*inorder print of files data*/
void printFiles(File * file) {
    if(file == NULL)
        return;
    
    printFiles(file->left);
        printf("%s ", file->name);
    printFiles(file->right);
}

/*inorder print of dirs data*/
void printDirs(Dir * dir) {
    if(dir == NULL)
        return;
    
    printDirs(dir->left);
        printf("%s ", dir->name);
    printDirs(dir->right);
}

File * minFile(File * file) {
    File * crt = file;
    while(crt && crt->left != NULL)
        crt = crt->left;
    
    return crt;
}

File* deleteFile(File* file, char * name) {

    if(file == NULL) {
        return NULL;
    }

    if(strcmp(name, file->name) < 0) {
        file->left = deleteFile(file->left, name);
    } else if (strcmp(name, file->name) > 0) {
        file->right = deleteFile(file->right, name);
    }
    else {
        if(file->left == NULL) {
            File * aux = file->right;
            freeFile(&file);
            return aux;
        }
        else if(file->right == NULL) {
            File * aux = file->left;
            freeFile(&file);
            return aux;
        } 

        File * aux = minFile(file->right);
        file->name = aux->name;
        file->right = deleteFile(file->right, aux->name);
        
    }
    return file;
}

Dir* minDir(Dir * dir) {
    Dir * crt = dir;
    while(crt->left != NULL)
        crt = crt->left;
    
    return crt;
}

Dir* deleteDir(Dir* dir, char* name) {
    if(dir == NULL) {
        return NULL;
    }

    if(strcmp(name, dir->name) < 0) {
        dir->left = deleteDir(dir->left, name);
    } else if (strcmp(name, dir->name) > 0) {
        dir->right = deleteDir(dir->right, name);
    }
    else {

         if(dir->left == NULL) {
            Dir * aux = dir->right;
            freeDir(&dir);
            return aux;
        }
        else if(dir->right == NULL) {
            Dir * aux = dir->left;
            freeDir(&dir);
            return aux;
        } 
        Dir * aux = minDir(dir->right);
        dir->name = aux->name;
        dir->right = deleteDir(dir->right, aux->name);
        
    }
    return dir;

}

void freeDir(Dir** dir) {
    Dir * aux = (*dir);
    aux->directories = NULL;
    aux->files = NULL;
    free(aux->name);
    free(aux);
}

void freeFile(File** file) {
    File * aux = (*file);
    free(aux->name);
    free(aux);
}

void freeTreeFile(File** file) {
    File *aux = (*file);
    if(aux == NULL) return;

    freeTreeFile(&aux->left);
    freeTreeFile(&aux->right);
    free(aux->name);
    free(aux);
}

void freeTreeDir(Dir** dir) {
    Dir *aux = (*dir);
    if(aux == NULL) return;

    freeTreeDir(&aux->left);
    freeTreeDir(&aux->right);

        freeTreeFile(&aux->files);
        freeTreeDir(&aux->directories);
        free(aux->name);
        free(aux);
}









