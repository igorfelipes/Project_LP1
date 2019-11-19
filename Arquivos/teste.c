#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXCHAR 100
#define MAX_LINE 1000

int searchStatus(int cod_status){

  FILE *file_calls;

  char txt[MAXCHAR];
  char line[MAX_LINE];
  int status; // revebe a conversão de str para int de cada status
  //int ids[50]; // armazena os ID's que possuem o codigo do status procurado
  int id_count =0; // Recebe o ID do chamado
  int count_status = 0; //faz a contagem do número de id's que possui o codigo do status procurado
  int first_line = 1, last_line, count_line = 0; // contagem de linhas, primeira e ultima linha de cada chamado
  int rangef[50], rangl[50]; //guarda a primeira e ultima linha de cada chamado  - o indice refere-se a variavel count_status

  file_calls = fopen("calls.txt", "r");

  if (file_calls){

    while (fscanf(file_calls, " %99s", txt) != EOF)
    {

      if(strcmp("Status", txt) == 0 ){                      //verifica que leu a palavra Status

            first_line += 9;
            last_line = first_line + 6;
            //id_count ++;
           fscanf(file_calls, " %1023s", txt);              //Passa para a palavra seguinte
           fscanf(file_calls, " %1023s", txt);
           fscanf(file_calls, " %1023s", txt);
           status = atoi(txt);                              //Converte para inteiro

           //printf("id: %d - status: %d - range-line: %d -%d\n",id_count, status, first_line, last_line);

           //Verifica se o status de cada chamado é igual ao selecionado pelo gerente ( aberto/ fechado)
           if(status == cod_status){
             //ids[count_status] = id_count;
             rangef[count_status] = first_line; // Armazena a primeira linha do chamado
             rangl[count_status] = last_line; // Armazena a útima linha do chamado
             count_status ++; //passa para o proximo índice
           }
      }
    }
    int i;

    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("|                                                                                                                 |\n");
    printf("|                                          ALANA'S CORPORATION Ⓡ                                                  |\n");
    printf("|                                                                                                                 |\n");
    printf("|                                          HISTÓRICO DE CHAMADOS                                                  |\n");
    printf("-------------------------------------------------------------------------------------------------------------------\n\n\n");

    //Faz uma varredura na quantidade de chamados com o status selecionado pelo gerente
    for(i =0; i < count_status; i++){

        //printf("ID: %d  - range_line: %d-%d\n", ids[i], rangef[i], rangl[i]);
        printf("-------------------------------------------------------------------------------\n");
        file_calls = fopen("calls.txt", "r");

        //Imprime cada chamado separadamente
        while (fgets(line, MAX_LINE, file_calls)) {
          count_line++;
          if( count_line >=rangef[i] && count_line <= rangl[i]){
            printf("%s\n",line );
          }
        }
        count_line = 0;

    }

    fclose(file_calls);
    return status;
  }
  else{
    return 0;
  }
}

int main(){

  searchStatus(2);
  return 0;
}
