#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXCHAR 100

int main(void)
{
  FILE *input;
  char txt[MAXCHAR];

  input = fopen("search_files.txt", "r");
  if (input)
  {

    while (fscanf(input, " %1023s", txt) != EOF)
    {
      if(strcmp("Quantidade de chamados: ", txt) == 0 ){                      //verifica que leu a palavra ID
           fscanf(input, " %1023s", txt );                  //le a proxima coisa, que deve ser um numero
           int id = atoi(txt);                              //passa pra inteiro
           printf("%d\n", id);                              //printa ele
      }
    }
    fclose(input);
  }
  return 0;
}
