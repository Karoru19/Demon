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

list *checkDirectory (char* path, bool recursive, list* first) {
    DIR *dir = opendir(path);
    if (!dir) return first;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (compare(entry->d_name,".") || compare(entry->d_name,"..")) continue;
        int len = strlen(entry->d_name);
        len += strlen(path) + 2;
        char final[len];
        snprintf(final, len, "%s/%s", path, entry->d_name);
        int type = getFileType(final);
        if (type == REGULAR) {
            addToList(entry->d_name, path, REGULAR, first);
        }
        else if (type == DIRECTORY && recursive == true){
            addToList(entry->d_name, path, DIRECTORY, first);
            checkDirectory(final, recursive, first);
        }
    }
    closedir(dir);
    return first;
}

void deleteFiles(config Conf) {
    list *first = createList();
    checkDirectory(Conf.pathTo, Conf.recursive, first);
    list *reverse = reverseList(first);
    deleteList(first);
    while (reverse->next != NULL) {
        int len = strlen(reverse->name) + strlen(reverse->path);
        len -= strlen(Conf.pathTo);
        len += strlen(Conf.pathFrom) + 2;
        char source[len];
        snprintf(source, len, "%s%s/%s", Conf.pathFrom, reverse->path + strlen(Conf.pathTo), reverse->name);
        len = strlen(reverse->path) + strlen(reverse->name)+2;
        char target[len];
        snprintf(target, len, "%s/%s", reverse->path, reverse->name);

        if (access(source, F_OK) == -1) {
            if (reverse->type == DIRECTORY) rmdir(target);
            else remove(target);
        }
        reverse = reverse->next;
    }
}
