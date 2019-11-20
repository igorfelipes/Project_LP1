#include <stdio_ext.h> // Se estiver utilizando sistemas Linux habilite essa biblioteca, caso não esteja comente essa linha de código
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>



/*
 *  Foi definida as constantes abaixo para ficar mais fácil de manusear
 *  as variáveis do tipo String do codigo
 */

#define MAX_200 200
#define MAX_20 20
#define MAX_40 40
#define MAX_LINE 1000
#define BUFFER_SIZE 1000
#define MAXCHAR 100



/*               Estrutura de informações contidas dentro de um chamado
 *
 *      Struct calls armazena os dados contidos dentro de um chamado, Título,
 *      Descrição, status ( 0- em aberto, 1- em atendimento , 2- em atendimento - visita técnica,
 *      3-concluído e 4- não resolvido), e o autor do chamado
 */

typedef struct calls{
    char title_calls[MAX_40];
    char descr[MAX_200];
    char status[MAX_20];
    char author[MAX_20];
}Calls;

// Estrutura para armazenar os usuários cadastrados no Sistema

typedef struct managers{
    char login[10];
    char password[10];
    char name[10];
}Managers;

typedef struct customers{
    char login[10];
    char password[10];
}Customers;



// Variáveis globais
int id_call; //recebe o id de cada chamado, que é gerado pela função callNumbers(+1)
int id_search_temp; // ID do chamado que deseja procurar
int new_status; // Status que deverá substituir
int menu_option; //recebe a escolha do usuário após a conversão de string para int
char temp[3];
char msg[400]; //variável para guardar a mensagem do usuario
char menu_option_str[MAX_20]; // guarda a opção escolhida pelo usuário
char line[MAX_LINE]; //recebe cada linha para a impressao de historico de chamados
char serv_rede[MAX_20] = "Serviço de rede\0"; // chamado relacionados a serviço de rede
char serv_internet[MAX_40] = "Serviço de Internet\0"; // chamado relacionados a serviço de de internet




//declaração da struct calls
Calls calls; //struct com variáveis que servem como informação necessária para um chamado
Customers customers;
Managers managers;




/* Funções */

//Função de limpeza de buffer do teclado - Linux/Windows
void clearBuffer(){
  __fpurge(stdin); //Limpeza de buffer em Sistemas Linux
  //setbuf(stdin, NULL); /*Se estiver utilizando Windows, comente a linha de código a cima e utilize essa/*


//Função get_option faz a limpeza do buffer de teclado, pega a opção escolhida pelo usuário e armazena nas variáveis globais
void get_option(){
  clearBuffer();
  fgets(menu_option_str, MAX_40, stdin);
  menu_option = atoi(menu_option_str);
  clearBuffer();
}


//Funções para ID do chamado e mudança de arquivo


/* Função de conversão de int para String */
void tostring(char str[], int num)
{
    int i, rem, len = 0, n;

    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}


/* Retorna o número de chamados do sistema*/
int callNumbers(){

  FILE *file_calls;
  char txt[MAXCHAR];
  int qtd;

  file_calls = fopen("calls.txt", "r");

  if (file_calls){

    while (fscanf(file_calls, " %99s", txt) != EOF)
    {

      if(strcmp("qtd_de_chamados:", txt) == 0 ){                      //verifica que leu a palavra Quantidade de chamados
           fscanf(file_calls, " %1023s", txt);                  //le a proxima coisa, que deve ser um numero
           qtd = atoi(txt);                              //passa pra inteiro
           printf("Quantidade de chamados: %d\n", qtd);                              //printa ele
      }
    }
    fclose(file_calls);
    return qtd;
  }
  else{
    return 0;
  }
}


//Modifica o número de chamados do sistema
void replaceCallNumbers(){

    FILE * file_calls;
    FILE * file_temp;
    char path[100];

    char buffer[BUFFER_SIZE];
    char newline[BUFFER_SIZE] = "qtd_de_chamados: 0\n";
    //char temp_char[10];//variavel temporaria de char
    char temp_str[10];
    int count, n, line = 8;
    id_call = callNumbers() + 1;
    printf("retorno de callNumbers: %d\n",id_call); // até aqui ta dando certo
    tostring(temp_str, id_call);   //VERIFICAR AQUI - FUI DORMIR

    if(!(temp_str[1])){
      printf("Deu certo a comparação de Nulo\n");
      temp_str[1] = '\n';
      newline[19] = 0;
    }
    else{
      newline[19] = '\n';
    }
    printf("Numero convertido: %c\n", temp_str[0]);
    newline[17] = temp_str[0];
    newline[18] = temp_str[1];


    printf("%s\n",newline);


    printf("deu certo\n");



    /* files */
    file_calls  = fopen("calls.txt", "r");
    file_temp = fopen("replace_temp.txt", "w");


    /* Verifica a abertura dos arquivos */
    if (file_calls == NULL || file_temp == NULL)
    {
        printf("\nFile couldn't be opened\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        return;
    }


    /*
     *  Lê a linha do arquivo fonte e escreve para o destino
     * do arquivo e modifica a linha.
     */
    count = 0;
    while ((fgets(buffer, BUFFER_SIZE, file_calls)) != NULL)
    {
        count++;

        /* verifica se a linha atual é a linha que será modificada*/
        if (count == line)
            fputs(newline, file_temp);
        else
            fputs(buffer, file_temp);
    }


    /* Fecha todos os arquivos e salva as mudanças */
    fclose(file_calls);
    fclose(file_temp);


    /* Deleta o arquivo original*/
    remove("calls.txt");

    /* Renomeia o temporario para o original*/
    rename("replace_temp.txt", "calls.txt");

    printf("\nSuccessfully replaced '%d' line with '%s'.", line, newline);

}

//Retorna a linha do ID do chamado procurado
int searchCall(int search_id){

  FILE *file_calls;
  char txt[MAXCHAR];
  int id, cont = 1;
  int line_id = 0, search = 0;

  file_calls = fopen("calls.txt", "r");

  if (file_calls){

    while (fscanf(file_calls, " %99s", txt) != EOF) //Verifica o arquivo completo
    {

      if(strcmp("ID:", txt) == 0 ){                      //Verifica os ID's dos chamados
            cont +=9;                                    //contagem da linha específica de cada id
           fscanf(file_calls, " %1023s", txt);                  //le a numeração do ID
           id = atoi(txt);                              //Converte o id para inteiro

           if(search_id == id){ //Verifica se o id procurado está contido no arquivo
             line_id = cont;   // guarda a linha específica do id procurado
             printf("ID: %d achado - linha %d\n", id, line_id);
             search = 1;
           }
      }
    }
    (search == 0) ? printf("ID não encontrado\n"): printf("ID Encontrado\n");
    fclose(file_calls);
    return line_id;
  }
  else{
    return 0;
  }
}



//Modifica o status do chamado
void replaceStatus(int new_status){

    FILE * file_calls;
    FILE * file_temp;

    //Variáveis de buffer para mundaça de linha
    char buffer[BUFFER_SIZE];
    char newline[BUFFER_SIZE] = "Status do chamado: 0\n";


    char temp_str[2]; //variável temporaria que receberá a conversão do status de inteiro para string
    int count, line;
    line = searchCall(id_search_temp) + 2; //linha do id do chamado
    tostring(temp_str, new_status); // função de conversão para string

    newline[19] = temp_str[0]; //modificando o status do chamado
    newline[20] = '\n';

    if(line == 2){
      return;
    }


    /* files */
    file_calls  = fopen("calls.txt", "r");
    file_temp = fopen("replace_temp.txt", "w");


    /* Verifica a abertura dos arquivos */
    if (file_calls == NULL || file_temp == NULL)
    {
        printf("\nFile couldn't be opened\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        return;
    }


    /*
     *  Lê a linha do arquivo fonte e escreve para o destino
     * do arquivo e modifica a linha.
     */
    count = 0;
    while ((fgets(buffer, BUFFER_SIZE, file_calls)) != NULL)
    {
        count++;

        /* verifica se a linha atual é a linha que será modificada*/
        if (count == line)
            fputs(newline, file_temp);
        else
            fputs(buffer, file_temp);
    }


    /* Fecha todos os arquivos e salva as mudanças */
    fclose(file_calls);
    fclose(file_temp);


    /* Deleta o arquivo original*/
    remove("calls.txt");

    /* Renomeia o temporario para o original*/
    rename("replace_temp.txt", "calls.txt");

    printf("\nSuccessfully replaced '%d' line with '%s'.", line, newline);

}



// Função principal
int main(){

  setlocale(LC_ALL,"Portuguese"); // habilitando o uso de Ç e acentos no código


  //Organizando o uso de data e hora da biblioteca time.h

  int hours, minutes, seconds, day, month, year;

  // declarando as estruras da biblioteca time.h
  time_t now_time;
  time(&now_time); // retorna as horas em segundos
  struct tm *info_time = localtime(&now_time); // converte de segundos para o sistema local, retornando um ponteiro de tipo tm

  hours = info_time->tm_hour;
  minutes = info_time->tm_min;
  seconds = info_time->tm_sec;

  day = info_time->tm_mday;
  month = info_time->tm_mon + 1; // retorna a quantidade de meses a partir 0
  year = info_time->tm_year + 1900; // retorn a quantidade de anos depois de 1900


  strcpy(calls.status, "0"); // Todos os chamados inicializão Em aberto

  strcpy(calls.author, "Jose da Silva\n");

  strcpy(managers.name, "Igor\n");

  strcpy(managers.login, "admin\n");
  strcpy(managers.password, "admin\n");
  strcpy(customers.login, "cliente\n");
  strcpy(customers.password, "1234\n");

 //printf("%s \n",customers.login);
 //Ponteiros de arquivos
  FILE *file_calls;
  FILE *msg_feedback;

  //Variaveis para armazenar o login e senha
  char login[10];
  char password[10];

  int option_access = 0;

/*
 *   Para armazenar as mensagens de feedback e os chamados
 *   abertos pelo cliente foram criados os arquivos .txt abaixo
 */

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





  while ( option_access == 0) {

    printf("  ________________________________________________\n"
            " /                                                \\\n"
             "|    _________________________________________     |\n"
             "|   |                                         |    |\n"
             "|   |          ALANA'S CORPORATION            |    |\n"
             "|   |                                         |    |\n"
             "|   | Login:                                  |    |\n"
             "|   | Senha:                                  |    |\n"
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
    printf("Login: ");
    clearBuffer();
    fgets(login, 10, stdin);
    printf("Password: ");
    clearBuffer();
    fgets(password, 10, stdin);

    if((strcmp(login, customers.login) == 0) && (strcmp(password, customers.password) == 0)){
      option_access = 1;
      printf("Deu certo\n");}
    else if((strcmp(login, managers.login) == 0) && (strcmp(password, managers.password) == 0)){
      option_access = 2;
    }else
      option_access = 0;


    switch (option_access) {
      case 1:
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
                  "|   |  4-Mensagens Recebidas                  |    |\n"
                  "|   |  5-Sair                                 |    |\n"
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
           get_option();



           switch(menu_option){

               //Opção 1 - Abrir chamado
               case 1:

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
                         get_option();



                         switch (menu_option) {


                           //Chamados relacionados a serviço de rede
                           case 1:
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


                             //printf("Digite seu nome: ");
                             //fgets(calls.author, MAX_200, stdin);

                             // Formata o armazenamento dos chamados
                             replaceCallNumbers();
                             file_calls = fopen("calls.txt", "a");
                             fprintf(file_calls, "ID: %i\n", id_call);
                             fprintf(file_calls, "Autor: %s",calls.author);
                             fprintf(file_calls, "Status do chamado: %s\n", calls.status);
                             fprintf(file_calls, "Tipo do chamado: %s\n", serv_rede);
                             fprintf(file_calls, "Título: %s", calls.title_calls);
                             fprintf(file_calls, "Descrição: %s", calls.descr );
                             fprintf(file_calls, "Data e hora: %02d/%02d/%02d - %02d:%02d:%02d\n\n", day, month, year, hours, minutes, seconds);
                             fprintf(file_calls, "-----------------------------------------------------------------------------------------------------------------------\n" );
                             fclose(file_calls);



                           break;

                           //Chamados relacionados a serviço de internet
                           case 2:
                             printf("Opção 2 de chamados acionado\n");
                             printf("\n\n");
                             printf("  ________________________________________________\n"
                                     " /                                                \\\n"
                                      "|    _________________________________________     |\n"
                                      "|   |                                         |    |\n"
                                      "|   |         ALANA'S CORPORATION             |    |\n"
                                      "|   |                                         |    |\n"
                                      "|   |            -CHAMADOS-                   |    |\n"
                                      "|   |  Tipo do chamado: Serviço de Internet   |    |\n"
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


                            // printf("Digite seu nome: ");
                             //fgets(calls.author, MAX_200, stdin);

                             // Formata o armazenamento dos chamados
                             replaceCallNumbers();
                             file_calls = fopen("calls.txt", "a");
                             fprintf(file_calls, "ID: %i\n", id_call);
                             fprintf(file_calls, "Autor: %s",calls.author);
                             fprintf(file_calls, "Status do chamado: %s\n", calls.status);
                             fprintf(file_calls, "Tipo do chamado: %s\n", serv_internet);
                             fprintf(file_calls, "Título: %s", calls.title_calls);
                             fprintf(file_calls, "Descrição: %s", calls.descr );
                             fprintf(file_calls, "Data e hora: %02d/%02d/%02d - %02d:%02d:%02d\n\n", day, month, year, hours, minutes, seconds);
                             fprintf(file_calls, "-----------------------------------------------------------------------------------------------------------------------\n" );
                             fclose(file_calls);


                           break;

                           //Retorna para o menu anterior
                           case 3:
                           break;

                           //Entrada inválida, tratamento de erro
                           default:
                           printf("Invalid Option\n");
                           break;
                         }
                     }
                     while (menu_option != 3);

               break;

               //Opção 2 - Histórico de chamados
               case 2:
                   fclose(file_calls);
                   file_calls = fopen("calls.txt", "r");
                   while (fgets(line, MAX_LINE, file_calls)) {
                     printf("%s\n",line );
                   }
                   fclose(file_calls);
                   file_calls = fopen("calls.txt", "a");

               break;

               //Opção 3 - Enviar Mensagem
               case 3:
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
                   clearBuffer();
                   fgets(msg, 400, stdin);
                   clearBuffer();

                   fprintf(msg_feedback, "Autor: %s\n",calls.author);
                   fprintf(msg_feedback, "Mensagem: %s\n", msg);
                   fprintf(msg_feedback, "-----------------------------------------------------------------------------------------------------------------------\n\n" );

               break;

               case 4:
                msg_feedback = fopen("managers_msg.txt", "r");
                while (fgets(line, MAX_LINE, msg_feedback)) {
                  printf("%s\n",line );
                }
                fclose(msg_feedback);
               break;

               case 5:
                option_access = 1;
               break;

               default:
                 printf("\n\ninvalid input\n");
               break;
             }

       }while(menu_option != 5); // Com a utilização do Do While, da para incorporar o tratamento de erros



      break;

      case 2:
        printf("Deu certo: login adm\n");
        do{
          printf("  ________________________________________________\n"
                  " /                                                \\\n"
                   "|    _________________________________________     |\n"
                   "|   |                                         |    |\n"
                   "|   |          ALANA'S CORPORATION            |    |\n"
                   "|   |                                         |    |\n"
                   "|   |  1-Visualizar Chamados                  |    |\n"
                   "|   |  2-Mudar Status dos chamados            |    |\n"
                   "|   |  3-Gerar relatorio                      |    |\n"
                   "|   |  4-Enviar mensagem                      |    |\n"
                   "|   |  5-Sair                                 |    |\n"
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
            get_option();
            switch (menu_option) {

              case 1:
                do {
                printf("Opção 1\n");
                printf("  ________________________________________________\n"
                        " /                                                \\\n"
                         "|    _________________________________________     |\n"
                         "|   |                                         |    |\n"
                         "|   |          ALANA'S CORPORATION            |    |\n"
                         "|   |                                         |    |\n"
                         "|   |  1-Visualizar Chamados Abertos          |    |\n"
                         "|   |  2-Visualizar Chamados Fechados         |    |\n"
                         "|   |  3-Voltar                               |    |\n"
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
                  printf("Insira sua opção: ");
                  get_option();
                }while(menu_option != 3);
              break;


              case 2:
                printf("Opção 2\n");

                printf("  ________________________________________________\n"
                        " /                                                \\\n"
                         "|    _________________________________________     |\n"
                         "|   |                                         |    |\n"
                         "|   |          ALANA'S CORPORATION            |    |\n"
                         "|   |                                         |    |\n"
                         "|   |       Mudar de Status dos chamados      |    |\n"
                         "|   |                                         |    |\n"
                         "|   |  ID do chamado:                         |    |\n"
                         "|   |  Novo status:                           |    |\n"
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
                  printf("Insira o ID do chamado que deseja modifcar: ");
                  clearBuffer();
                  fgets(temp, 3, stdin); // joga a entrada do usuario na variavel temporaria
                  id_search_temp = atoi(temp); //converte a entrada do usuario para inteiro e poder ser procurado o id na função searchCall
                  printf("Insira o codigo do novo status: \n");
                  clearBuffer();
                  fgets(temp, 3, stdin);
                  new_status = atoi(temp); //converte a entrada do usuario para inteiro e poder ser procurado o id na função replaceStatus
                  searchCall(id_search_temp);
                  replaceStatus(new_status);

              break;


              case 3:
                printf("Opção 3\n");
                file_calls = fopen("calls.txt", "r");
                while (fgets(line, MAX_LINE, file_calls)) {
                  printf("%s\n",line );
                }
                fclose(file_calls);
              break;

              case 4:
                printf("opção 4 - Enviar Mensagem acionado\n");
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
                clearBuffer();
                fgets(msg, 400, stdin);
                clearBuffer();

                msg_feedback = fopen("managers_msg.txt", "a");
                fprintf(msg_feedback, "Autor: %s\n", managers.name);
                fprintf(msg_feedback, "Mensagem: %s\n", msg);
                fprintf(msg_feedback, "-----------------------------------------------------------------------------------------------------------------------\n\n" );

              break;

              case 5:
                printf("Opção 5\n");
              break;

              default:
                printf("Invalid input\n");
              break;
            }
          }while(menu_option != 5);
      break;


      default:
        printf("\n\n Login ou senha incorretos\n\n");
      break;
    }
  }


  return 0;
}
