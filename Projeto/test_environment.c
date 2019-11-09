#include <stdio_ext.h> // Se estiver utilizando sistemas Linux
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

// Constantes para manusear o valor das variáveis
#define MAX_200 200
#define MAX_20 20
#define MAX_40 40


int id_temp = 0;


// estrutura de informações contidas dentro de um chamado
typedef struct calls{
    char title_calls[MAX_40];
    char type_calls[MAX_40];
    char descr[MAX_200];
    char status[MAX_20];
    char author[MAX_20];
}Calls; // declarando a estrutura como Calls, para faciliar o manuseio

//variável para guardar a mensagem do usuario - global
char msg[400];



//Funções

//Função de limpeza de buffer do teclado - Linux/Windows
void clearBuffer(){
  __fpurge(stdin); //Limpeza de buffer em Sistemas Linux
  /*setbuf(stdin, NULL); // Se estiver utilizando Windows, comente a linha de código a cima e utilize essa */

}

//função principal
int main(){

  setlocale(LC_ALL,"Portuguese");

  //Organizando o uso de data e hora da biblioteca time.h
  int hours, minutes, seconds, day, month, year;

  // declarando as estruras da biblioteca time.h
  time_t now_time;
  time(&now_time); // retorna a as horas em segundos
  struct tm *info_time = localtime(&now_time); // converte de segundos para o sistema local, retornando um ponteiro de tipo tm

  hours = info_time->tm_hour;
  minutes = info_time->tm_min;
  seconds = info_time->tm_sec;

  day = info_time->tm_mday;
  month = info_time->tm_mon + 1; // retorna a quantidade de meses a partir 0
  year = info_time->tm_year + 1900; // retorn a quantidade de anos depois de 1900


  //Variáveis

  char menu_option; // guarda a opção escolhida pelo usuário
  char serv_rede[MAX_20] = "Serviço de rede\0"; // chamado relacionados a serviço de rede
  char serv_internet[MAX_40] = "Serviço de Internet\0"; // chamado relacionados a serviço de de internet

  Calls calls; //struct com variáveis que servem como informação necessária para um chamado

  strcpy(calls.status, " Em aberto ");

 //Ponteiros de arquivos
  FILE *file_calls;
  FILE *msg_feedback;


  file_calls = fopen("calls.txt", "a");
  msg_feedback = fopen("msg_feedback.txt", "a");


  // Verificação da abertura dos dois arquivos de armazenamento

  // Arquivo de chamados
  if(file_calls == NULL){
    printf("File couldn't be opened calls.txt\n");
    return 0;
  }
  // Arquivp de mensagens
  if(msg_feedback == NULL){
    printf("File couldn't be opened msg_feedback.txt\n");
    return 0;
  }


 // Menu de opções do sistema
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
      clearBuffer();



      switch(menu_option){

          //Opção 1 - ABRIR CHAMADO
          case '1':

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
                    clearBuffer();



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
                        clearBuffer();


                        fgets(calls.title_calls, MAX_40, stdin);
                        clearBuffer();

                        printf("Digite a descrição do chamado: ");
                        fgets(calls.descr, MAX_200, stdin);
                        clearBuffer();


                        printf("Digite seu nome: ");
                        fgets(calls.author, MAX_200, stdin);

                        // Formata o armazenamento dos chamados
                        fprintf(file_calls, "ID: %i\n", id_temp);
                        fprintf(file_calls, "Autor: %s",calls.author);
                        fprintf(file_calls, "Status do chamado: %s\n", calls.status);
                        fprintf(file_calls, "Tipo do chamado: %s\n", serv_rede);
                        fprintf(file_calls, "Título: %s", calls.title_calls);
                        fprintf(file_calls, "Descrição: %s", calls.descr );
                        fprintf(file_calls, "Data e hora: %02d/%02d/%02d - %02d:%02d:%02d\n\n", day, month, year, hours, minutes, seconds);
                        fprintf(file_calls, "-----------------------------------------------------------------------------------------------------------------------\n\n" );



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
                        clearBuffer();


                        fgets(calls.title_calls, MAX_40, stdin);
                        clearBuffer();


                        printf("Digite a descrição do chamado: ");
                        fgets(calls.descr, MAX_200, stdin);
                        clearBuffer();


                        printf("Digite seu nome: ");
                        fgets(calls.author, MAX_200, stdin);

                        // Formata o armazenamento dos chamados
                        fprintf(file_calls, "ID: %i\n", id_temp);
                        fprintf(file_calls, "Autor: %s",calls.author);
                        fprintf(file_calls, "Status do chamado: %s\n", calls.status);
                        fprintf(file_calls, "Tipo do chamado: %s\n", serv_internet);
                        fprintf(file_calls, "Título: %s", calls.title_calls);
                        fprintf(file_calls, "Descrição: %s", calls.descr );
                        fprintf(file_calls, "Data e hora: %02d/%02d/%02d - %02d:%02d:%02d\n\n", day, month, year, hours, minutes, seconds);
                        fprintf(file_calls, "-----------------------------------------------------------------------------------------------------------------------\n\n" );


                      break;

                      //Retorna para o menu anterior
                      case '3':
                      break;

                      default:
                      printf("Invalid Option\n");
                      break;
                    }
                }
                while (menu_option != '3');

          break;

          //Opção 2 - Histórico de chamados
          case '2':
              printf("Histórico de chamados\n");
          break;

          //Opção 3 - Enviar Mensagem
          case'3':
              printf("opção 3 - Enviar Mensagem acionado\n");
              printf("\n\n");
              printf("  ________________________________________________\n"
                      " /                                                \\\n"
                       "|    _________________________________________     |\n"
                       "|   |                                         |    |\n"
                       "|   |         ALANA'S CORPORATION             |    |\n"
                       "|   |                                         |    |\n"
                       "|   |          -MENSAGEM-FEEDBACK-            |    |\n"
                       "|   |                                         |    |\n"
                       "|   |                                         |    |\n"
                       "|   |                                         |    |\n"
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
              printf("Digite sua mensagem: ");
              __fpurge(stdin);
              fgets(msg, 400, stdin);
              clearBuffer();

              fprintf(msg_feedback, "Autor: %s\n",calls.author);
              fprintf(msg_feedback, "Mensagem: %s\n", msg);
              fprintf(msg_feedback, "-----------------------------------------------------------------------------------------------------------------------\n\n" );

          break;

          //Opção 2 - SAIR
          case'4':
          break;

          default:
            printf("\n\ninvalid input\n");
          break;
        }

  }while(menu_option !='4'); // Com a utilização do Do While, da para incorporar o tratamento de erros




  return 0;
}
