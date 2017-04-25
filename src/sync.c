#include "sync.h"

list *sourceF;
list *targetF;

//good list sizes
int sSize = 0;
int tSize = 0;

config *Config;

//get initial data about files in source/target folders
bool initSync(config *conf)
{

  sourceF = malloc(sizeof(list));
  targetF = malloc(sizeof(list));

  Config = conf;

  string source = Config->pathFrom;
  string target = Config->pathTo;

  bool s = false, t = false;

  DIR           *ds,*dt;
  struct dirent *dirS,*dirT;
  string slash = "/";

  ds = opendir(source);
  dt = opendir(target);

  dirT = readdir(dt);

  if(!ds || !dt)
    return false;

  while((dirS = readdir(ds)) != NULL)
  {
      if(dirS->d_type != DT_DIR)
      {
        string dirName = dirS->d_name;
        string path = (string)malloc(1+strlen(source)+strlen(slash)+strlen(dirName));
        strcpy(path, source);
        strcat(path, slash);
        strcat(path, dirName);
        addToList(dirName, path, sourceF);
        sSize++;
      }
  }

  while((dirT = readdir(dt)) != NULL)
  {
      if(dirT->d_type != DT_DIR)
      {
        string dirName = dirT->d_name;
        string path = (string)malloc(1+strlen(target)+strlen(slash)+strlen(dirName));
        strcpy(path, target);
        strcat(path, slash);
        strcat(path, dirName);
        addToList(dirName, path, targetF);
        tSize++;
      }
  }

  printf("Source files:\n");
  printf("Size: %d\n", sSize);
  printf("\n");
  printf("Target files:\n");
  printf("Size: %d\n", tSize);

  return true;

}

void copyFile(string source, string target)
{
		FILE  *original, *copy;
		int  a;

		original = fopen(source, "rb");
		copy = fopen(target, "wb");

		while(1)
		{
			a  =  fgetc(original);

			if(!feof(original))
				fputc(a, copy);
			else
				break;
		}

		fclose(copy);
		fclose(original);

}

void removeFile(string file)
{
    remove(file);
}

bool syncDir ()
{

  if(sSize > tSize)
  {
    list *s = sourceF;
    list *t = targetF;
    int i;
    string slash = "/";

    for(i = 0; i<sSize; i++)
    {
      if(s->name != t->name)
      {
        string target = (string)malloc(1+strlen(Config->pathTo)+strlen(slash)+strlen(s->name));
        strcpy(target, Config->pathTo);
        strcat(target, slash);
        strcat(target, s->name);

        copyFile(s->path, target);

        addToList(s->name, target, targetF);

        if(s->next != NULL)
          s = s->next;
        else
          break;
        if(tSize > 0)
          t = t->next;
        tSize++;
      }
    }
  }
  else if(sSize < tSize)
  {
    list *s = sourceF;
    list *t = targetF;
    int i;
    string slash = "/";

    //todo funkcja która znajduje różnice między dwoma listami i zwraca ją jako liste


  }




}
