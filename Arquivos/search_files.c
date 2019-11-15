/**
 * C program to replace a specific line with another in a file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>

#define BUFFER_SIZE 1000
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
           //printf("Quantidade de chamados: %d\n", qtd);                              //printa ele
      }
    }
    fclose(file_calls);
  }
  return qtd;
}


int main(){

    FILE * file_calls;
    FILE * file_temp;
    char path[100];

    char buffer[BUFFER_SIZE];
    char newline[BUFFER_SIZE] = "qtd_de_chamados: 0\0";
    int count, n, line = 8;

    newline[19] = callNumbers() + 1;



    /* Remove extra new line character from stdin */
    //fpurge(stdin);
    setbuf(stdin, NULL);


  //  printf("Replace '%d' line with: ", line);
  //  fgets(newline, BUFFER_SIZE, stdin);


    /*  Open all required files */
    file_calls  = fopen("test_storage.txt", "r");
    file_temp = fopen("replace_temp.txt", "w");

    /* fopen() return NULL if unable to open file in given mode. */
    if (file_calls == NULL || file_temp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nFile couldn't be opened\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        return 0;
    }


    /*
     * Read line from source file and write to destination
     * file after replacing given line.
     */
    count = 0;
    while ((fgets(buffer, BUFFER_SIZE, file_calls)) != NULL)
    {
        count++;

        /* If current line is line to replace */
        if (count == line)
            fputs(newline, file_temp);
        else
            fputs(buffer, file_temp);
    }


    /* Close all files to release resource */
    fclose(file_calls);
    fclose(file_temp);


    /* Delete original source file */
    remove("search_files.txt");

    /* Rename temporary file as original file */
    rename("replace_temp.txt", "search_files.txt");

    printf("\nSuccessfully replaced '%d' line with '%s'.", line, newline);

    return 0;
}
