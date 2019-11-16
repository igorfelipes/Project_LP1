#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXCHAR 100

int callNumbers(){

  FILE *file_calls;
  char txt[MAXCHAR];
  int qtd;

  file_calls = fopen("search_files.txt", "r");

  if (file_calls){

    while (fscanf(file_calls, " %1023s", txt) != EOF)
    {

      if(strcmp("qtd_de_chamados:", txt) == 0 ){                      //verifica que leu a palavra Quantidade de chamados
           fscanf(file_calls, " %1023s", txt);                  //le a proxima coisa, que deve ser um numero
           qtd = atoi(txt);                              //passa pra inteiro
           printf("Quantidade de chamados: %d\n", qtd);                              //printa ele
      }
    }
    fclose(file_calls);
  }
  return 0;
}

int main(){
  callNumbers();

  return 0;
}
