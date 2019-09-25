/*PROGRAMACAO CIENTIFICA - PEL216
 ALUNO: Silvio Romero de Araújo Junior  RA: 118324-3
 PROFESSOR: Reinaldo Bianchi
 RELATORIO Final
 Algoritmo de Dijkstra com o OpenMP*/

#include <stdio.h>

#define LARGEINT 2<<30-1  // "infinito"
#define NV 6

// variaveis globais, todas compartilhadas pelas threads por padrão

int ohd[NV][NV],  // Distancias de 1 salto entre vértices
mind[NV],  // distancias minimas encontradas ate o momento
notdone[NV], // vertices ainda nao verificados
nth,  // numer de threads
chunk,  // numero de vertices manipulados por cada thread
md,  // minimo atual sobre todos as threads
mv;  // vertice que atinge o minimo

void init(int ac, char **av)
{  int i,j;
    for (i = 0; i < NV; i++)
        for (j = 0; j < NV; j++)  {
            if (j == i) ohd[i][i] = 0;
            else ohd[i][j] = LARGEINT;
        }
    ohd[0][1] = ohd[1][0] = 40;
    ohd[0][2] = ohd[2][0] = 15;
    ohd[1][2] = ohd[2][1] = 20;
    ohd[1][3] = ohd[3][1] = 10;
    ohd[1][4] = ohd[4][1] = 25;
    ohd[2][3] = ohd[3][2] = 100;
    ohd[1][5] = ohd[5][1] = 6;
    ohd[4][5] = ohd[5][4] = 8;
    for (i = 1; i < NV; i++)  {
        notdone[i] = 1;
        mind[i] = ohd[0][i];
    }
}

// encontra o mais proximo de 0 entre nao concluidos, entre s e e
void findmymin(int s, int e, int *d, int *v)
{  int i;
    *d = LARGEINT;
    for (i = s; i <= e; i++)
        if (notdone[i] && mind[i] < *d)  {
            *d = ohd[0][i];
            *v = i;
        }
}

// para cada i em [s, e], pergunte se existe um caminho mais curto para i
void updateohd(int s, int e)
{  int i;
    for (i = s; i <= e; i++)
        if (mind[mv] + ohd[mv][i] < mind[i])
            mind[i] = mind[mv] + ohd[mv][i];
}

void dowork()
{
#pragma omp parallel
    {  int startv,endv,  // vertices de inicio e fim para esta thread
        step,  //
        mymd,  // valor minimo encontrado por esta thread
        mymv,  // vertice que atinge esse valor
        me = omp_get_thread_num();  // numero da thread
#pragma omp single
        {  nth = omp_get_num_threads();  chunk = NV/nth;
            printf("there are %d threads\n",nth);  }
        // Note 3
        startv = me * chunk;
        endv = startv + chunk - 1;
        for (step = 0; step < NV; step++)  {
            // encontre o vertice mais próximo de 0 entre os não executados
#pragma omp single
            {  md = LARGEINT; mv = 0;  }
            findmymin(startv,endv,&mymd,&mymv);
#pragma omp critical  // Note 4
            {  if (mymd < md)
            {  md = mymd; mv = mymv;  }
            }
            // marcar novo vertice como executado
#pragma omp single
            {  notdone[mv] = 0;  }
            
            updateohd(startv,endv);
#pragma omp barrier
        }
    }
}

int main(int argc, char **argv)
{  int i;
    init(argc,argv);
    dowork();
    //voltar para thread unica
    printf("minimum distances:\n");
    for (i = 1; i < NV; i++)
        printf("%d\n",mind[i]);
}

