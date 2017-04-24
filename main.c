#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include "config.h"
#include "dir.h"
#include "list.h"
#include "parse.h"

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

    list *root;
        root = malloc(sizeof(list));
        root->name = "test5";
        root->path = "test6";
        root->next = NULL;
        addToList("test", "test2", root);
        showList(root);
        listSize(root);
        deleteItem(root, "test2");
        printf("\n");
        showList(root);
        printf("List size: %d\n", listSize(root));

        check_directory(argv[1], true);

//    if (argc > 1)
//    {
//        check_directory(argv[1], true);
//        exit(EXIT_SUCCESS);
//    }

    config Config = default_config();

    if (parse(argc, argv, &Config) == false) {
        printf("Parsing failure!\n");
        exit(EXIT_FAILURE);
    }
    printf("%s\n",Config.pathFrom);
    printf("%s\n",Config.pathTo);
    printf("%s\n",Config.recursive == 1 ? "recursive":"not recursive");
    printf("%zd\n",Config.byte);
    printf("%d\n",Config.time);

    if (argc == 4)
    {
      char* p;
      errno = 0;
      int arg = strtol(argv[3], &p, 10);  //convert char->int
      if (*p != '\0' || errno != 0) {printf("lolxd\n");return 1;} //check for correct value
      Config.time = arg;

      printf("Synctime: %d\n", Config.time);
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
