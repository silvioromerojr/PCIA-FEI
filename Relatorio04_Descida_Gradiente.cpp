/*PROGRAMACAO CIENTIFICA - PEL216
 ALUNO: Silvio Romero de Araujo Junior  RA: 118324-3
 PROFESSOR: Reinaldo Bianchi
 RELATORIO 4 - Metodos Numericos: Descida de Gradiente
 PROGRAMA PARA O METODO DE DESCIDA DE GRADIENTE*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#define MAX_ITERA 100   // Numero maximo de iteracoes
#define ALFA 0.01       // Criterio de convergencia

//Funcao que se deseja encontrar o minimo
double f(double x){
    //return ((x * x * x) - (2 * x * x) + 2);
    return x * x;
}

//Derivada da Funcao
double df(double x){
    //return ((3 * x * x) - (4 * x));
    return 2 * x;
}

int main(){
    double x[MAX_ITERA] = {2};  // Ponto de inicio da avaliacao da funcao (x0)
    double grad[MAX_ITERA];     // Valor do Gradiente no ponto xi
    double y[MAX_ITERA];        // Valor da funcao no ponto xi
    double beta=0.1;            // Taxa de aprendizagem (beta)
    int i;                      // Numero de iteracoes
    cout << "Ponto Inicial (x0): 2\n";
    
    
    //Loop incremento da taxa de aprendizagem (beta)
    for (beta=0.1 ; beta <= 1.0 ; beta += 0.1){
            cout << "\nTaxa de Aprendizagem (Beta): " <<  beta;
        
            //Loop para calculo iterativo dos minimos locais
            for(i = 0; i < MAX_ITERA ; i++){
                grad[i] = df(x[i]);  // Calculo do Gradiente no Ponto xi
                y[i] = f(x[i]);      //
                cout << fixed;
                //Testa o criterio convergencia
                if(abs(grad[i]) < ALFA){
                    break;
                }
            
                x[i+1] = x[i] - beta * grad[i]; //Avaliacao de f(x) no novo ponto x(i + 1)
            
        }
        
        //Testa se foi possivel encontrar o minimo local com o numero de iteracoes definido em MAX_ITERA
        if(i == MAX_ITERA){
            
            cout << "\nNao foi possivel encontrar o minimo da funcao com o numero de iteracoes definido.\n\n";
        }
        
        else{
            
            cout << "\nMinimo Local = " << y[i] << "\t" << "No ponto: " << x[i] << "\nEncontrado na iteracao: "  << i + 1 << endl;
        }
    }
    system ("pause");
    return 0;
    
}
