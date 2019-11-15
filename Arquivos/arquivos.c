#include <stdio_ext.h> // Se estiver utilizando sistemas Linux habilite essa biblioteca, caso não esteja comente essa linha de código
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

void clearBuffer(){
  //fpurge(stdin); //Limpeza de buffer em Sistemas Linux
  setbuf(stdin, NULL); // Se estiver utilizando Windows, comente a linha de código a cima e utilize essa */
}

int main(){

  FILE *storage_call;

  storage_call = fopen("search_files.txt", "r+");

  if(storage_call==NULL){
    printf("Erro ao abrir o arquivo\n");
  }
  char descricao[20] = "ID:";
  int count, count_line, n;
  char line[1000], teste[2], temp, *lp;

clearBuffer();
while (fgets(line, 1000, storage_call)!= NULL) {
    //
    count_line++;
     /*Lê o arquivo até que não tenha mais nada para ler, se utilizar apenas o fgets,
     lê até a primeira quebra de linha*/
     printf("%s\n", line);
     if (strstr(line, descricao)){
       count++;
       printf("Referencia: linha %d\n\n",  count_line);
       // Read until newline is hit or buffer size exceeded.
       for (lp = line; *lp != '\n' && (lp - line) < 1000; lp++) {

         // If encounter colon and sccanf reads at least 1 integer..
         if (*lp == ':' && sscanf(lp + 1, "%1023s", teste) == 1) {

           n = atoi(teste);
           fprintf(stdout, "%c\n", teste[1]);
          break;
      }
    }

     }



     clearBuffer();
 }

  fclose(storage_call);




  return 0;
}
