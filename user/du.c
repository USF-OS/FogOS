#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

#define MAX 512

void print_size(int size) {
  if (size < 1024) {
    printf("%d B\n", size);
  } else if (size < 1024 * 1024) {
    printf("%d KB\n", size / 1024);
  } else {
    printf("%d MB\n", size / (1024 * 1024));
  }
}

void du(const char *path) {
  int fd;
  struct stat st;
  struct dirent de;

  if ((fd = open(path, 0)) < 0) {
    fprintf(2, "du: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0) {
    fprintf(2, "du: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch (st.type) {
  case T_FILE:
    printf("%s ", path);
    print_size(st.size);
    break;
  case T_DIR:
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof path) {
      printf("du: path too long\n");
      break;
    }
    char buf[MAX];
    strcpy(buf, path);
    char *p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0) continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if (stat(buf, &st) < 0) {
        printf("du: cannot stat %s\n", buf);
        continue;
      }
      printf("%s ", buf);
      print_size(st.size);
    }
    break;
  }
  close(fd);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: du [directory]\n");
    exit(0);
  }
  du(argv[1]);
  exit(0);
}
