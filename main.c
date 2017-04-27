#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <stdio.h>
#include <signal.h>
#include "config.h"
#include "dir.h"
#include "list.h"
#include "parse.h"
#include "sync.h"

int processId;

int pidCheck(){
    FILE *pidId;
    int s;
    if ( !( pidId = fopen("/tmp/pidId.txt", "r"))){
        printf( "File could not be opened to retrieve your data from it.\n" );
    }
    else {
        fseek(pidId, 0, SEEK_END);
        unsigned long len = (unsigned long)ftell(pidId);
        if (len > 0) {  //check if the file is empty or not.
            rewind(pidId);
            fscanf( pidId, "%d", &s );
        }
        fclose( pidId );
    }
    return s;
}

void pidSave(int pid) {
    FILE *pidId;
    pidId = fopen("/tmp/pidId.txt", "w");
    fprintf(pidId, "%d\n", pid);
    fclose(pidId);
}

void wakeUp() {
    syslog(LOG_INFO, "Forcing to wake up.");
}

int main(int argc, char* argv[]) {

    signal(SIGUSR1, wakeUp);
    processId = pidCheck();

    if (argc == 2 && argv[1][0] == '-') {
        switch (argv[1][1]) {
        case 'W':
            syslog(LOG_INFO, "SIGUSR1 is send.");
            kill(processId, SIGUSR1);
            return EXIT_SUCCESS;
        case 'w':
            syslog(LOG_INFO, "SIGUSR1 is send.");
            kill(processId, SIGUSR1);
            return EXIT_SUCCESS;  
        case 'S':
            syslog(LOG_INFO, "SIGKILL is send.");
            syslog(LOG_INFO, "Shut Down demon.");
            kill(processId,SIGKILL);
            return EXIT_SUCCESS;
        case 's':
            syslog(LOG_INFO, "SIGKILL is send.");
            syslog(LOG_INFO, "Shut Down demon.");
            kill(processId,SIGKILL);
            return EXIT_SUCCESS;
        }
        return EXIT_FAILURE;
    }

    config Config = default_config();
    if (parse(argc, argv, &Config) == false) {
        syslog(LOG_CRIT,"Parsing failure!\n");
        exit(EXIT_FAILURE);
    }

    syslog(LOG_INFO, "Demon startup.");
    pid_t pid, sid;

    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        printf("Child process created: %d\n", pid);
        pidSave(pid);
        exit(EXIT_SUCCESS);
    }
    //exit(EXIT_SUCCESS);
    umask(0);

    sid = setsid();
    if (sid < 0) {
        syslog(LOG_CRIT,"Cannot set id session!\n");
        exit(EXIT_FAILURE);
    }

    if ((chdir("/")) < 0) {
        syslog(LOG_CRIT,"Cannot change working directory!\n");
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1) {
        syslog(LOG_INFO, "Synchornization START.");
        syncDir(Config);
        syslog(LOG_INFO, "Synchornization STOP.");
        sleep(Config.time);
    }

    exit(EXIT_SUCCESS);
}
