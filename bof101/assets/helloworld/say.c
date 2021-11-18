#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void say(char *input){
  char buf[2048];
  strcpy(buf, input);
  printf("%s\n", buf);
}

int main(int argc, char **argv){
  if (argc > 1) {
    say(argv[1]);
  }
  else
    printf("This program takes 1 argument.\n");
  return 0;
}
