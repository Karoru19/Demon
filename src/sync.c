#include "sync.h"

void syncDir (config Conf) {
    deleteFiles(Conf);

    list *first = createList();
    checkDirectory(Conf.pathFrom, Conf.recursive, first);
    list *flash = first;

    while (first->next != NULL) {
        first = first->next;
        bool mmap;

        int len = strlen(first->name) + strlen(first->path);
        len -= strlen(Conf.pathFrom);
        len += strlen(Conf.pathTo) + 2;
        char target[len];
        snprintf(target, len, "%s%s/%s", Conf.pathTo, first->path + strlen(Conf.pathFrom), first->name);
        len = strlen(first->path) + strlen(first->name) + 2;
        char source[len];
        snprintf(source, len, "%s/%s", first->path, first->name);

        struct stat st;
        stat(source, &st);
        int size = st.st_size;
        if(size >= Conf.byte) mmap = true;

        if (access(target, F_OK) == -1) {
            if (first->type == REGULAR) {
                if(!compareTime(source, target)) {
                    mmap == true ? copyMmap(source, target) : copyRW(source, target);
                    setTime(source, target);
                }
            }
            else if (first->type == DIRECTORY) {
                mkdir(target, 0700);
                setTime(source, target);
            }
        }
        else {
            if (first->type == DIRECTORY) {
                if (!compareTime(source, target)) setTime(source, target);
            }
            else if (first->type == REGULAR) {
                if(!compareTime(source, target)) {
                    remove(target);
                    mmap == true ? copyMmap(source, target) : copyRW(source, target);
                    setTime(source, target);
                }
            }
        }
    }
    deleteList(flash);
}
