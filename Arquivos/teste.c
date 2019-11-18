#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXCHAR 100

int callNumbers(){

  FILE *file_calls;
  char txt[MAXCHAR];
  int qtd, cont = 1, ids[50];

  file_calls = fopen("calls.txt", "r");

  if (file_calls){

    while (fscanf(file_calls, " %99s", txt) != EOF)
    {

      if(strcmp("ID:", txt) == 0 ){                      //verifica que leu a palavra Quantidade de chamados
            cont +=9;
           fscanf(file_calls, " %1023s", txt);                  //le a proxima coisa, que deve ser um numero
           qtd = atoi(txt);                              //passa pra inteiro
           printf("ID: %d - linha %d\n", qtd, cont);                              //printa ele
      }
    }
    fclose(file_calls);
    return qtd;
  }
  else{
    return 0;
  }
}

int main(){

  callNumbers();
  return 0;
}
