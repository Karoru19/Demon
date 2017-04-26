#include "modtime.h"

bool compareTime(char *source, char *target) {
    struct stat stS, stT;
    stat(source, &stS);
    stat(target, &stT);
    if (stS.st_atim.tv_sec == stT.st_atim.tv_sec)
        if (stS.st_mtim.tv_sec == stT.st_mtim.tv_sec)
            return true;
    return false;
}

void setTime(char* source, char* target){
    struct stat st;
    struct utimbuf time;
    stat(source, &st);
    time.actime = st.st_atim.tv_sec;
    time.modtime = st.st_mtim.tv_sec;
    utime(target, &time);
    chmod(target, st.st_mode);
}
