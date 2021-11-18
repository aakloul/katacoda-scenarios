#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void sigsegv_handler(int sig) {
  char * msg = "I will be printed only when a Segmentation Fault occures";
  fprintf(stderr, "%s\n", msg);
  fflush(stderr);
  exit(1);
}

void say(char *input){
  char buf[2048];
  strcpy(buf, input);
  printf("%s\n", buf); 
}

void secretHiddenFunction(){
  char * superSecretPassword = "ch4%6jjqw^&$h";
  printf("This function is never called, so it is safe to hardcode this password: %s\n", superSecretPassword);
  exit(1);
}

int main(int argc, char **argv){
  
  //signal(SIGSEGV, sigsegv_handler);
  
  if (argc > 1) {
    say(argv[1]);
  }
  else
    printf("This program takes 1 argument.\n");
  return 0;
}
