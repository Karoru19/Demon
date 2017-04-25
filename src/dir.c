#include "dir.h"

bool isDirectory(string path)
{
  DIR           *d;
  struct dirent *dir;
  d = opendir(path);
  if (d == NULL) return false;
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

void check_directory (string argv, bool recursive) {
    DIR           *d;
    struct dirent *dir;
    d = opendir(argv);

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (compare(dir->d_name,".") || compare(dir->d_name,"..")) continue;
            if (dir->d_type == DT_DIR && recursive == true) {
                string dirName = dir->d_name;
                string slash = "/";
                string final = (string) malloc(1+strlen(dirName)+strlen(slash)+strlen(argv));
                strcpy(final, argv);
                strcat(final, slash);
                strcat(final, dirName);
                printf("DIRECTORY %s: \n", final);
                check_directory(final, recursive);
                free(final);
            }
            else if (dir->d_type != DT_DIR) {
                printf("FILE %s/%s\n", argv, dir->d_name);
            }
        }
    closedir(d);
    }
    else
    {
      printf("Error while opening directory!\n");
    }
    return;
}
