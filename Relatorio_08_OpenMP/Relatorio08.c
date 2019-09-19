/*PROGRAMACAO CIENTIFICA - PEL216
 ALUNO: Silvio Romero de Araújo Junior  RA: 118324-3
 PROFESSOR: Reinaldo Bianchi
 RELATORIO 6 - Metodos Numericos: Metodo de Monte Carlo
 Para compilar: gcc -g -Wall -fopenmp -o Relatorio08 Relatorio08.cpp
 Para executar:   ./omp_trap1 <numero de threads threads>
 PROGRAMA PARA O CALCULO DE INTEGRAIS - METODO DO TRAPEZIO - OPENMP*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
//Prototipos das Funcos do Programa
void Usage(char* prog_name);
double f(double x);
void Trap(double a, double b, int n, double* global_result_p);

int main(int argc, char* argv[]) {
   double  global_result = 0.0;  //Armazena o resultado
   double  a, b;                 //limites de integracao a(inf) b(sup)
   int     n;                    // Numero de trapezios
   int     thread_count;         //Numero de Threads

   if (argc != 2) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
   printf("Entre com  a, b, and n\n");
   scanf("%lf %lf %d", &a, &b, &n);
   if (n % thread_count != 0) Usage(argv[0]);
#  pragma omp parallel num_threads(thread_count) 
   Trap(a, b, n, &global_result);

   printf("COm n = %d trapezios, a estimativa eh:\n", n);
   printf("da integral de %f a %f = %.14e\n", a, b, global_result);
   return 0;
}

//Funcao para tratamento de erro
void Usage(char* prog_name) {

   fprintf(stderr, "uso %s numero de threads\n", prog_name);
   fprintf(stderr, "   numero de trapezios deve ser divisivel pelo\n");
   fprintf(stderr, "   numero de threads\n");
   exit(0);
}  /* Usage */

// Funcao a ser integrada
double f(double x) {
   double return_val;

   return_val = x*x;
   return return_val;
}

//Funcao para calcular a integral pelo metodo do trapezio
void Trap(double a, double b, int n, double* global_result_p) {
   double  h, x, my_result;
   double  local_a, local_b;
   int  i, local_n;
   int my_rank = omp_get_thread_num();
   int thread_count = omp_get_num_threads();

   h = (b-a)/n; 
   local_n = n/thread_count;  
   local_a = a + my_rank*local_n*h; 
   local_b = local_a + local_n*h; 
   my_result = (f(local_a) + f(local_b))/2.0; 
   for (i = 1; i <= local_n-1; i++) {
     x = local_a + i*h;
     my_result += f(x);
   }
   my_result = my_result*h; 

#  pragma omp critical 
   *global_result_p += my_result; 
}
