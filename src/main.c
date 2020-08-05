#include <stdio.h>

int digit(char a){ /* converte digito em char para int */
  int b = a - '0';
  if(b >=0 && b<=9) {
    return b;
  }
  else{
    return -1;
  } 
}

int prime(int a){ /*verifica se um número é primo */
  int b = a/2;
  int i = 2;
  int flag = 0;

  if(b < 2) flag = 1;
  else{
    for(i=2; i<=b && flag == 0; i++){
      if(a%i==0) flag = 1; /*número não é primo */
    }

    if(flag == 1) return 0; /* Não primo */
    else return 1; /* Primo */
    }
} 

int main() {

  char str[100];
  int numbers[100];
  int i, j = 0;
  int n = 0;
 
/* Passo 1: Ler a string */ 
  fgets(str, sizeof(str), stdin);

/* Passo 2: Extrair valores da string */

  for(i=0; str[i]!='\n'; i++){
    if(digit(str[i])!=-1){ /*Adiciona digitos */
      n = n*10 + digit(str[i]);
      printf("Adicionei dígito\n");
    }
    if(digit(str[i+1])==-1){
      numbers[j] = n; /*guarda o numero encontrado */
      printf("Guardei número\n");
      j++;
      n = 0;
    }
  }

/* Neste ponto, a variável j é a quantidade de 
        números armazenados */
/* Os valores a serem verificados estão no vetor numbers[] */
/* 
  for(i=0; i<j; i++){
    printf("%d\n", numbers[i]);
  } 
*/

/* Passo 3: Verificar se são primos */

if(prime(113)){printf("Primo\n");}

  return 0;
}
