#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h> /* exit() */
#include <sys/types.h> /* define pid_t */
#include <sys/wait.h>
#include <unistd.h> /* fork() */

int digit(char a){ /* função que converte digito (em char) para int */
  int b = a - '0';
  if(b >=0 && b<=9) {
    return b;
  }
  else{
    return -1;
  } 
}

int prime(int a){ /*função que verifica se um número é primo */
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
  unsigned long int numbers[100];
  unsigned long int n = 0;
  int i, j = 0;
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

/* --------------------------------------------- */

/* Primeiros testes para criação de processos filhos */
/* 
  if(j>=2) filho1 = fork();
  if(j>=3 && filho1 != 0) filho2 = fork();
  if(j>=4 && filho1 != 0 && filho2 != 0 ) filho3 = fork();


  if(filho1==0){ 
    printf("Filho 1 aqui!\n"); *p = *p + 1;
    exit(0);
    }
  else if(filho2==0){ 
    printf("Filho 2 aqui!\n"); *p = *p + 1;
    exit(0);
    }
  else if(filho3==0){ 
    printf("Filho 3 aqui!\n"); *p = *p + 1;
    exit(0);
    }
  else{
    waitpid(filho1, NULL, 0);
    waitpid(filho2, NULL, 0);
    waitpid(filho3, NULL, 0);
    printf("Eu sou o pai!\n");
    printf("%d\n", *p);
  }

/* --------------------------------------------- */

  i = j;
  while(i>0){ /* i representa os números restante para analisar */
    
    /* As operações de fork só são feitas no processo pai */
    if(i>=2) filho1 = fork();
    if(i>=3 && filho1 != 0) filho2 = fork();
    if(i>=4 && filho1 != 0 && filho2 != 0 ) filho3 = fork();

    /* Cada processo analisa uma posição do vetor de números paralelamente */

    if(filho1==0){ 
      /* printf("Filho 1 aqui!\n"); */
      if(prime(numbers[i-2])) *p = *p + 1; 
      exit(0);
      }
    else if(filho2 == 0){ 
      /* printf("Filho 2 aqui!\n"); *p = *p + 1; */
      if(prime(numbers[i-3])) *p = *p + 1;
      exit(0); 
      }
    else if(filho3 == 0){ 
      /* printf("Filho 3 aqui!\n"); *p = *p + 1; */
      if(prime(numbers[i-4])) *p = *p + 1;
      exit(0); 
      }
    else{
      if(prime(numbers[i-1])) *p = *p + 1; 
      waitpid(filho1, NULL, 0);
      waitpid(filho2, NULL, 0);
      waitpid(filho3, NULL, 0);

      /* printf("Eu sou o pai!\n"); */
    }

    i = i-4;

  }

  /* Passo 4 - imprimir resultado */
  
  printf("%d\n", *p); /* Imprime a quantidade identificada de números primos */


  return 0;
}
