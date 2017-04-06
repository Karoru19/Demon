#include "dir.h"

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
                string tmp;
                int len = strlen(argv) + strlen(dir->d_name) + 2;
                tmp=malloc(sizeof * tmp * len);
                snprintf(tmp, len, "%s%s/", argv, dir->d_name);
                printf("DIRECTORY %s: \n", tmp);
                check_directory(tmp, recursive);
                free(tmp);
            }
            else if (dir->d_type != DT_DIR) {
                printf("FILE %s%s\n", argv, dir->d_name);
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
