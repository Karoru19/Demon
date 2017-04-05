#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include "config.h"
#include <dirent.h>
#include "bool.h"
#include "cstring.h"
#include <stdlib.h>

bool isDirectory(string path)
{
  DIR           *d;
  struct dirent *dir;
  d = opendir(path);
  dir = readdir(d);
  closedir(d);
  if(dir == NULL)
  {
      return false;
  }
  else if(dir->d_type == DT_DIR)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void sync (string source, string target)  //todo
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

  unsigned int syncTime = 300;
/*
    if (argc > 1)
    {
      DIR           *d;
      struct dirent *dir;
      d = opendir(argv[1]);

      if (d)
      {
        while ((dir = readdir(d)) != NULL)
        {
          printf("%s\t%s\n", dir->d_type == DT_DIR ? "DIRECTORY:":"FILE:",dir->d_name);
        }
      closedir(d);
      }
      else
      {
        printf("Error while opening directory!\n");
      }
      exit(EXIT_SUCCESS);
    }
*/
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
      syncTime = arg;

      printf("Synctime: %d\n", syncTime);
    }
    else
    {
      printf("Too few arguments !\n");
      exit(EXIT_FAILURE);
    }

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
            sleep(syncTime);
    }

    fclose (log);
    exit(EXIT_SUCCESS);
}
