#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 32

void win() {
  printf("You win if you can print me");
  exit(1);
}

void vuln(){
  char buf[BUFSIZE];
  gets(buf);
  printf("You type %s\n", buf);
}

int main(int argc, char **argv){
  puts("Please enter your string: ");
  vuln();
  return 0;
}
