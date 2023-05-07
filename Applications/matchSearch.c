/**
 * Your program will launched from the command line with three arguments:
1. the path to an image file in the uncompressed TGA file format;
2. thepathtoa“search”foldercontainingimages(possiblyamongotherfiles)inthesameTGA file format;
3. the path to an output folder.
*  look, for any image file in the search folder, for possible matches
* write in the output folder a text file giving the list of matches found
*/

#include "./include/matchSearch.h"

// search for images with the .tga extension in a directory, comparing them to another image provided as an argument, and writing the names of matching images to a text file.
char* matchSearch(char* dirPath, char* imgPath1, char* str);

// takes two arguments: path is the path of the file to write, and lines is the string to write to the file
void writeToDir(char* path, char* lines);

int main(int argc, char* argv[]){
    if (argc != 4) {

        exit(2);
    }
    char* str = (char*) calloc(600, 1);
    char* fname = argv[1];
    char* searchfname = argv[2];

    sprintf(str, "%s\n%s\n", fname, searchfname);

    char* lines = matchSearch(searchfname, argv[1], str);

    char* outputDir = argv[3];
    char* cutFname = getFileName(fname);

    char* txtPath = (char*) calloc(strlen(outputDir) + strlen(cutFname) + 1, 1);
    sprintf(txtPath, "%s/%s.txt", outputDir, cutFname);
    
    writeToDir(txtPath, lines);
    
    free(str);
    return 0;
}

char* matchSearch(char* dirPath, char* imgPath1, char* str) {
    DIR* dir;
    dir = opendir(dirPath);
    struct dirent* entry;


    int counter = 0;
    char* list = (char*) calloc(300, 1);

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name + strlen(entry->d_name) - 4, ".tga") == 0) {

            pid_t pid = fork();

            if (pid == 0) {
                char* imgPath = (char*) calloc(strlen(dirPath) + strlen(entry->d_name) + 1, 1);
                sprintf(imgPath, "%s/%s", dirPath, entry->d_name);
                int returned = execl("./compare", "./compare", imgPath1, imgPath, NULL);
                free(imgPath);
                if (returned == -1 ) { exit(EXIT_FAILURE); }
            }
            else if (pid > 0) {
                int status;
                waitpid(pid, &status, 0);

                if (WIFEXITED(status) && WEXITSTATUS(status) == 1) {
                    counter++;
                    strcat(list, entry->d_name);
                    strcat(list, " ");
                }
            }else { exit(EXIT_FAILURE); }
        }  
    }
    char* result = (char*) calloc(300, 1);
    sprintf(result, "%d %s", counter, list);
    strcat(str, result);

    free(list);
    free(result);
    closedir(dir);
    return str;
}

void writeToDir(char* path, char* lines) {
    FILE* fp = fopen(path, "w");
    fputs(lines, fp);
    fclose(fp);
}
