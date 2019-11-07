#include <stdio_ext.h> // Se estiver utilizando sistemas Linux
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>


#define MAX_200 200
#define MAX_20 20
#define MAX_40 40

int id_temp = 0;

typedef struct calls{
    char title_calls[MAX_40];
    char type_calls[MAX_40];
    char descr[MAX_200];
    char status[MAX_20];
    char author[MAX_20];
}Calls;


int main(){

  setlocale(LC_ALL,"Portuguese");

  //Organizando o uso de data e hora da biblioteca time.h
  int hours, minutes, seconds, day, month, year;

  time_t now_time;
  time(&now_time);
  struct tm *info_time = localtime(&now_time);

  hours = info_time->tm_hour;
  minutes = info_time->tm_min;
  seconds = info_time->tm_sec;

  day = info_time->tm_mday;
  month = info_time->tm_mon + 1;
  year = info_time->tm_year + 1900;



  char menu_option;
  char serv_rede[MAX_20] = "Serviço de rede\0";
  Calls calls; //struct com variáveis que servem como informação necessária para um chamado

  FILE *file_calls;

  file_calls = fopen("calls.txt", "a");

  if(file_calls == NULL){
    printf("File couldn't be opened\n");
    return 0;
  }


  do{
    printf("  ________________________________________________\n"
            " /                                                \\\n"
             "|    _________________________________________     |\n"
             "|   |                                         |    |\n"
             "|   |          ALANA'S CORPORATION            |    |\n"
             "|   |                                         |    |\n"
             "|   |  1-Criar Chamado                        |    |\n"
             "|   |  2-Histórico de chamados                |    |\n"
             "|   |  3-Enviar Mensagem                      |    |\n"
             "|   |  4-Sair                                 |    |\n"
             "|   |                                         |    |\n"
             "|   |                                         |    |\n"
             "|   |                                         |    |\n"
             "|   |                                         |    |\n"
             "|   |                                         |    |\n"
             "|   |_________________________________________|    |\n"
             "|                                                  |\n"
            "\\__________________________________________________/\n"
          "        \\___________________________________/\n"
              "    ___________________________________________\n\n");
      printf("Insira sua opção: ");

      menu_option = getchar(); //Pega a opção do usuário
      __fpurge(stdin); //Limpeza de buffer em Sistemas Linux
      /*setbuf(stdin, NULL); // Se estiver utilizando Windows, comente a linha de código a cima e utilize essa */

      switch(menu_option){

          case '1':   //Menu_option = Criar chamados

                do{
                  printf("\n\n");
                  printf("  ________________________________________________\n"
                          " /                                                \\\n"
                           "|    _________________________________________     |\n"
                           "|   |                                         |    |\n"
                           "|   |         ALANA'S CORPORATION             |    |\n"
                           "|   |                                         |    |\n"
                           "|   |            -CHAMADOS-                   |    |\n"
                           "|   |  1-Serviço de rede                      |    |\n"
                           "|   |  2-Internet, problemas com a conexão    |    |\n"
                           "|   |  3-Voltar                               |    |\n"
                           "|   |                                         |    |\n"
                           "|   |                                         |    |\n"
                           "|   |                                         |    |\n"
                           "|   |                                         |    |\n"
                           "|   |                                         |    |\n"
                           "|   |_________________________________________|    |\n"
                           "|                                                  |\n"
                          "\\__________________________________________________/\n"
                        "        \\___________________________________/\n"
                            "    ___________________________________________\n\n");
                    printf("Insira sua opção: ");
                    __fpurge(stdin);
                    menu_option = getchar();
                    //setbuf(stdin, NULL);
                    __fpurge(stdin);
                    //setbuf(stdin, NULL);

                    switch (menu_option) {

                      case '1':  //Chamados relacionados a serviço de internet
                      printf("Opção 1 de chamados acionado\n");
                      printf("\n\n");
                      printf("  ________________________________________________\n"
                              " /                                                \\\n"
                               "|    _________________________________________     |\n"
                               "|   |                                         |    |\n"
                               "|   |         ALANA'S CORPORATION             |    |\n"
                               "|   |                                         |    |\n"
                               "|   |            -CHAMADOS-                   |    |\n"
                               "|   |  Tipo do chamado: Serviço de rede       |    |\n"
                               "|   |  Título:                                |    |\n"
                               "|   |  Descrição:                             |    |\n"
                               "|   |  Autor:                                 |    |\n"
                               "|   |                                         |    |\n"
                               "|   |                                         |    |\n"
                               "|   |                                         |    |\n"
                               "|   |                                         |    |\n"
                               "|   |_________________________________________|    |\n"
                               "|                                                  |\n"
                              "\\__________________________________________________/\n"
                            "        \\___________________________________/\n"
                                "    ___________________________________________\n\n");
                      printf("Digite o Título do chamado: ");
                      __fpurge(stdin);
                      fgets(calls.title_calls, MAX_40, stdin);
                      //setbuf(stdin, NULL);
                      __fpurge(stdin);
                      printf("Digite a descrição do chamado: ");
                      fgets(calls.descr, MAX_200, stdin);
                      __fpurge(stdin);
                      printf("Digite seu nome: ");
                      fgets(calls.author, MAX_200, stdin);


                      fprintf(file_calls, "ID: %i\n", id_temp);
                      fprintf(file_calls, "Tipo do chamado: %s\n", serv_rede);
                      fprintf(file_calls, "Título: %s", calls.title_calls);
                      fprintf(file_calls, "Descrição: %s", calls.descr );
                      fprintf(file_calls, "Autor: %s",calls.author);
                      fprintf(file_calls, "Data e hora: %d/%d/%d - %d:%d:%d\n\n", day, month, year, hours, minutes, seconds);
                      fprintf(file_calls, "-----------------------------------------------------------------------------------------------------------------------\n\n" );
                      //setbuf(stdin, NULL);


                      break;

                      case '2':
                      printf("Opção 2 de chamados acionado\n");
                      printf("\n\n");
                      printf("  ________________________________________________\n"
                              " /                                                \\\n"
                               "|    _________________________________________     |\n"
                               "|   |                                         |    |\n"
                               "|   |         ALANA'S CORPORATION             |    |\n"
                               "|   |                                         |    |\n"
                               "|   |            -CHAMADOS-                   |    |\n"
                               "|   |  Tipo do chamado: Serviço de internet   |    |\n"
                               "|   |  Título:                                |    |\n"
                               "|   |  Descrição:                             |    |\n"
                               "|   |  Data:                                  |    |\n"
                               "|   |  Autoria:                               |    |\n"
                               "|   |                                         |    |\n"
                               "|   |                                         |    |\n"
                               "|   |                                         |    |\n"
                               "|   |_________________________________________|    |\n"
                               "|                                                  |\n"
                              "\\__________________________________________________/\n"
                            "        \\___________________________________/\n"
                                "    ___________________________________________\n\n");
                      printf("Digite o Título do chamado: ");
                      __fpurge(stdin);
                      //setbuf(stdin, NULL);
                      __fpurge(stdin);
                      //setbuf(stdin, NULL);
                      break;

                      case '3':
                      break;

                      default:
                      printf("Invalid Option\n");
                      break;
                    }
                }
                while (menu_option != '3');

                //EM ANDAMENTO
          break;

          case '2':
              printf("Histórico de chamados\n");
          break;

          case'3':
              printf("Enviar Mensagem\n");
          break;

          case'4':
          break;

          default:
            printf("\n\ninvalid input\n");
          break;
        }

  }while(menu_option !='4'); // Com a utilização do Do While, da para incorporar o tratamento de erros

//outro teste de ramo, tou no master agr

  return 0;
}
