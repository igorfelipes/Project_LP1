#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>

#define BUFFER_SIZE 1000
#define MAXCHAR 100


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


int temp;
void replaceCallNumbers(){

    FILE * file_calls;
    FILE * file_temp;
    char path[100];

    char buffer[BUFFER_SIZE];
    char newline[BUFFER_SIZE] = "Status do chamado: 0\n";
    //char temp_char[10];//variavel temporaria de char
    char temp_str[10];
    int count, n, line = 8;
    temp = callNumbers() + 1;
    printf("retorno de callNumbers: %d\n",temp); // até aqui ta dando certo
    tostring(temp_str, temp);   //VERIFICAR AQUI - FUI DORMIR

    if(temp_str[1] == NULL){
      printf("Deu certo a comparação de Nulo\n");
      temp_str[1] = '\n';
      newline[19] = NULL;
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

int main(){
    callNumbers();
  return 0;
}
