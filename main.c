#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include "config.h"
#include "dir.h"
#include "list.h"

void sync_dir (string source, string target)  //todo
{
  DIR           *ds,*dt;
  struct dirent *dirS,*dirT;
  ds = opendir(source);
  dt = opendir(target);

  dirT = readdir(dt);

  while((dirS = readdir(ds)) != NULL)
  {

  }
}

int main(int argc, char* argv[]) {

    el_listy *root;
        root = malloc(sizeof(el_listy));
        root->name = "test5";
        root->path = "test6";
        root->next = NULL;
        addToList("test", "test2", root);
        showList(root);

//    if (argc > 1)
//    {
//        check_directory(argv[1], true);
//        exit(EXIT_SUCCESS);
//    }

    config Config = default_config();
    Config.pathFrom = argv[1];
    Config.pathTo = argv[2];

    if (argc == 3)
    {
      if(isDirectory(argv[1]) == true && isDirectory(argv[2]) == true)
      {
        printf("ok\n");
      }
      else
      {
        printf("Paths must lead to directories !\n");
        exit(EXIT_FAILURE);
      }
    }
    else if (argc == 4)
    {
      char* p;
      errno = 0;
      int arg = strtol(argv[3], &p, 10);  //convert char->int
      if (*p != '\0' || errno != 0) return 1; //check for correct value
      Config.time = arg;

      printf("Synctime: %d\n", Config.time);
    }
    else
    {
      printf("Too few arguments !\n");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);

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
            sleep(30); /* wait 30 seconds */
    }

    fclose (log);
    exit(EXIT_SUCCESS);
}
