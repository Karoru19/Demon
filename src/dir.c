#include "dir.h"

bool isDirectory(const char* path)
{
  DIR           *d = opendir(path);
  if (d) return true;
  else return false;
}

int getFileType (const char* path) {
    struct stat st;
    stat(path,&st);
    if (S_ISDIR(st.st_mode)) return DIRECTORY;
    else if (S_ISREG(st.st_mode)) return REGULAR;
    else return UNKNOWN;
}

void checkDirectory (const char* path, bool recursive) {
    DIR           *dir = opendir(path);
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (compare(entry->d_name,".") || compare(entry->d_name,"..")) continue;
        int len = strlen(entry->d_name);
        len += strlen(path) + 2;
        char final[len];
        snprintf(final, len, "%s/%s", path, entry->d_name);
        int type = getFileType(final);
        if (type == REGULAR) printf("FILE %s/%s\n", path, entry->d_name);
        if (type == DIRECTORY && recursive == true){
            printf("DIRECTORY %s: \n", final);
            checkDirectory(final, recursive);
            free(final);
        }
    }
    closedir(dir);
}
