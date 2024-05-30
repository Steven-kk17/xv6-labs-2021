#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

//./grade-lab-util find

char *
filename(char *path)
{
  static char buf[512];
  char *p;

  // Find first character after last slash.
  for (p = path + strlen(path); p >= path && *p != '/'; p--)
    ;
  p++; // p point to the first character after the last slash.
  memmove(buf, p, strlen(p));
  memset(buf + strlen(p), 0, 1);
  return buf;
}

void find(char *path, char *name)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if ((fd = open(path, 0)) < 0)
  {
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  // Get the file's status，and store it in st.
  if (fstat(fd, &st) < 0)
  {
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch (st.type)
  {
  case T_FILE:
    // printf("filename: %s\n", filename(path));
    if (strcmp(filename(path), name) == 0)
    {
      printf("%s\n", path);
    }
    break;

  case T_DIR:
    // printf("im in T_DIR\n");
    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
      if (de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
        continue;
      strcpy(buf, path);
      p = buf + strlen(buf);
      *p++ = '/';
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      // printf("buf: %s\n", buf);
      find(buf, name);
    }
    break;
  }
  close(fd);
}

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    fprintf(2, "Usage: find path name\n");
    exit(0);
  }
  else if (argc == 2)
  {
    find(".", argv[1]);
  }
  else if (argc == 3)
  {
    find(argv[1], argv[2]);
  }
  exit(0);
}