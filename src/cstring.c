#include "cstring.h"

bool compare (char* str1, char* str2) {
    int i, len = strlen(str1);
    if( len == strlen(str2) ) {
        for( i = 0; i < len; i++ ) if( str1[i] != str2[i] ) return false;
        return true;
    }
    return false;
}
