#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXCHAR 100

int main(void)
{
  FILE *input;
  char txt[MAXCHAR];
  int count_line, count_line_id;

  input = fopen("search_files.txt", "r");
  if (input)
  {

    while (fscanf(input, " %1023s", txt) != EOF)
    {
      while (fscanf(input, " %1023s", txt) != "\n")
      if(strcmp("ID:", txt) == 0 ){                      //verifica que leu a palavra ID
           count_line_id = count_line + 1;
           fscanf(input, " %s", txt );                  //le a proxima coisa, que deve ser um numero
           int id = atoi(txt);                              //passa pra inteiro
           printf("ID: %d - linha: %d\n", id, count_line_id);                              //printa ele
      }
    }
    fclose(input);
  }
  return 0;
}
