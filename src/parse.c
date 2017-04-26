#include "parse.h"

bool parse (int argc, char* argv[], config *Config) {
    if (argc < 3) {
        printf("Too few arguments.\n");
        return false;
    }
    else {
        int i, c=0;
        for (i=1; i<argc; i++) {
            if(isDirectory(argv[i]) == true){
                if (c == 0) {
                    Config->pathFrom = argv[i];
                    c++;
                }
                else if (c == 1) {
                    Config->pathTo = argv[i];
                    c++;
                }
            }
            else {
                int x=1;
                if (argv[i][1] == '-') x=2;
                switch (argv[i][x]) {
                case 't':
                    if (x == 2 && compare(argv[i],"--time") == false) {
                        printf("Option ERROR!\n");
                        return false;
                    }
                    if (x == 1 && compare(argv[i],"-t") == false) {
                        printf("Option ERROR!\n");
                        return false;
                    }
                    if (argc >= i+1) {
                        int len=strlen(argv[i+1])-1, j, v=0;
                        switch (argv[i+1][len]) {
                        case 'S':
                            Config->time = 1;
                            break;
                        case 's':
                            Config->time = 1;
                            break;
                        case 'M':
                            Config->time = minute;
                            break;
                        case 'm':
                            Config->time = minute;
                            break;
                        case 'H':
                            Config->time = hour;
                            break;
                        case 'h':
                            Config->time = hour;
                            break;
                        default:
                            break;
                        }
                        for (j = len-1; j >= 0; j--) {
                            if (isdigit(argv[i+1][j])){
                                char tmp = argv[i+1][j];
                                v*=10;
                                v+=tmp-'0';
                            }
                            else {
                                printf("Option ERROR!\n");
                                return false;
                            }
                        }
                        Config->time *= v;
                        i++;
                    }
                    else {
                        printf("Option ERROR!\n");
                        return false;
                    }
                    break;
                case 'r':
                    if (x == 2 && compare(argv[i],"--recursive") == false) {
                        printf("Option ERROR!\n");
                        return false;
                    }
                    if (x == 1 && compare(argv[i],"-r") == false) {
                        printf("Option ERROR!\n");
                        return false;
                    }
                    Config->recursive=true;
                    break;
                case 'b':
                    if (x == 2 && compare(argv[i],"--byte") == false) {
                        printf("Option ERROR!\n");
                        return false;
                    }
                    if (x == 1 && compare(argv[i],"-b") == false) {
                        printf("Option ERROR!\n");
                        return false;
                    }
                    if (argc >= i+1) {
                        int len=strlen(argv[i+1])-1, j, v=0;
                        switch (argv[i+1][len]) {
                        case 'B':
                            Config->byte = 1;
                            break;
                        case 'b':
                            Config->byte = 1;
                            break;
                        case 'K':
                            Config->byte = kB;
                            break;
                        case 'k':
                            Config->byte = kB;
                            break;
                        case 'M':
                            Config->byte = MB;
                            break;
                        case 'm':
                            Config->byte = MB;
                            break;
                        case 'G':
                            Config->byte = GB;
                            break;
                        case 'g':
                            Config->byte = GB;
                            break;
                        default:
                            break;
                        }
                        for (j = 0; j < len; j++) {
                            if (isdigit(argv[i+1][j])){
                                char tmp = argv[i+1][j];
                                v*=10;
                                v+=tmp-'0';
                            }
                            else {
                                printf("Option ERROR!\n");
                                return false;
                            }
                        }
                        Config->byte *= v;
                        i++;
                    }
                    else {
                        printf("Option ERROR!\n");
                        return false;
                    }
                    break;
                default:
                    break;
                }
            }
        }
        if (c < 2) return false;
    }
    return true;
}
