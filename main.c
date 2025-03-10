#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexical.c"
#include "syntaxique.c"

int main() {
	/* ouverture de fichier à programme */
	FILE * file = fopen("main.hoby", "r");
    if(file == NULL){
        perror("Error while opening the file");
        exit(1);
    }
   /* analyse lexicale */
   if (analyse_lexicale(file)){
  	    /* analyse syntaxique */
  	    analyse_syntaxique(file);
  	return 1;
  }
  return 0;
}
