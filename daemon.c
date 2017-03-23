#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int compare(char* v1, char* v2);

int main(int argc, char* argv[]) {
    pid_t pid, sid;
        
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    FILE *log;
    if((log = fopen("log","w"))==NULL) {
        printf("Cannot open log file!\n");
        exit(EXIT_FAILURE);
    }
                
    sid = setsid();
    if (sid < 0) {
        fprintf(log,"Cannot set id session!\n");
        exit(EXIT_FAILURE);
    }
        
    if ((chdir("/")) < 0) {
        fprintf(log,"Cannot change working directory!\n");
        exit(EXIT_FAILURE);
    }
        
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
        
    while (1) {
        char* s = "--eject ";
        if(strcmp(argv[1],s)) printf("XD\n");
        else if(!strcmp(argv[1],s)) printf("LOL\n");
        if (argc == 1) exit(EXIT_FAILURE);
        else if(argv[1] == "--eject"){
            system("eject");
            sleep(5);
            system("eject -t");
            sleep(30); /* wait 30 seconds */
        }
    }
    fclose (log);
    exit(EXIT_SUCCESS);
}

int compare(char* v1, char* v2) {
    if (sizeof(v1)!=sizeof(v2)) exit(EXIT_FAILURE);
}
