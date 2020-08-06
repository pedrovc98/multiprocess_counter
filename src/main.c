#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h> /* exit() */
#include <sys/types.h> /* define pid_t */
#include <sys/wait.h>
#include <unistd.h> /* fork() */

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
  int counter = 0;
  pid_t filho1, filho2, filho3;
 
/* Passo 1: Ler a string */ 
  fgets(str, sizeof(str), stdin);

/* Passo 2: Extrair valores da string */

  for(i=0; str[i]!='\n'; i++){
    if(digit(str[i])!=-1){ /*Adiciona digitos */
      n = n*10 + digit(str[i]);
      /* printf("Adicionei dígito\n"); */
    }
    if(digit(str[i])!=-1 && digit(str[i+1])==-1){
      numbers[j] = n; /*guarda o numero encontrado */
      /* printf("Guardei número: %d\n", n); */
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

/* Passo 3: Verificar se são primos em um máximo de 4 processos simultâneos */

 /* Definir flags de protecao e visibilidade de memoria */
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANON;

  /* Criar area de memoria compartilhada */
  int *p;
  p = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
  if ((long int)p==-1) printf("Erro de alocacao!\n");
  (*p)=0;

  if(j>=2) filho1 = fork();
  if(j>=3) filho2 = fork();
  if(j>=4) filho3 = fork();

  if(filho1==0 && filho2 != 0 && filho3 !=0) printf("Filho 1 aqui!\n");
  else if(filho1!=0 && filho2 == 0 && filho3 !=0) printf("Filho 2 aqui!\n");
  else if(filho1!=0 && filho2 != 0 && filho3 ==0) printf("Filho 3 aqui!\n");
  else if(filho1!=0 && filho2 != 0 && filho3 !=0) printf("Eu sou o pai!\n");

















/*

  for(i=0; i<j; i++){
    if(prime(numbers[i])){
      printf("%d é primo\n", numbers[i]);
      counter++;
    }
    else{
      printf("%d não é primo\n", numbers[i]);
    } 
  }

  printf("Encontrei %d números\n", j);
  printf("%d são primos\n", counter);

  while(1);
  */

  return 0;
}
