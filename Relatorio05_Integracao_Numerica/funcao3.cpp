/*PROGRAMACAO CIENTIFICA - PEL216
 ALUNO: Silvio Romero de Araujo Junior  RA: 118324-3
 PROFESSOR: Reinaldo Bianchi
 RELATORIO 5 - Metodos Numericos: Integracao Numerica (Retangulo, Trapezio, Simpson e Quadratura                Adaptaviva
 PROGRAMA PARA A FUNCAO 3 e^-(x^2)*/
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include "QuadAdapt.hpp"
using namespace std;

//FUNCAO QUE DESEJAMOS CALCULAR A INTEGRAL NUMERICAMENTE
double f1(double x)
{
    return exp(- pow(x , 2.0));
    
}

//Derivada de segunda ordem da funcao para calculo do erro
float DerivSegF1(float x)
{
    return ((4 * pow (x, 2)) * exp(- pow(x ,2))) - (2 * exp(- pow(x ,2)));
    
}

//Derivada de quarta ordem da funcao para calculo do erro

float DerivQuaF1(float x)
{
    return ((16 * pow (x, 4)) * exp(- pow(x ,2))) - ((48 * pow (x, 2)) * exp(- pow(x ,2))) +
    (12 * exp(- pow(x ,2)));
}

//Funcao para calculo do erro - Retangulo
float ErroRet (float a, float b)
{
    return -((pow((b - a), 3) / 24) * DerivSegF1(a + ((b - a) / 2)));
}

//Funcao para calculo do erro - Trapezio
float ErroTrap (float a, float b)
{
    
    return -((pow((b - a), 3) / 12) * DerivSegF1(a + ((b - a) / 2))) ;
    
    //Funcao para calculo do erro - Simpson
}

float ErroSim (float a, float b)
{
    return -((pow((b - a), 5) / 2880) * DerivQuaF1(a + ((b - a) / 2)));
    
}

int main()
{
    int n = 1;            //Numero de Segmentos
    int i = 0;            //Contador para o laco for
    double area1 = 0;     //Variavel para manter o valor calculado da area (metodo retangular)
    double area2 = 0;     //Variavel para manter o valor calculado da area (metodo trapezoidal)
    double area3 = 0;     //Variavel para manter o valor calculado da area (metodo de Simpson)
    double x1 = 0.0;      //Limite inferior de integracao
    double x2 = 1.0;      //Limite superior de integracao
    
    double base = (x2 - x1)/(float)n;   //Base do retangulo para calculo da area
    
    double a;          /* a and b are the endpoints for each segment */
    double b;
    
    for (i = 0; i < n; ++i) //Laco for para calculo da integral metodo do retangulo
    {
        a = x1 + i * base;
        b = x1 + (i + 1) * base;
        //Formula basica do metodo do retangulo
        area1 = area1 + ((b-a)) * (f1(a + (b - a)/2.0));
    }
    
    for (i = 0; i < n; ++i) //Laco for para calculo da integral metodo do trapezio
    {
        a = x1 + i * base;
        b = x1 + (i + 1) * base;
        //Formula basica do metodo do trapezio
        area2 = area2 + ((b-a)/2.0) * (f1(a + 0.0 * (b - a)/1.0) + f1(a + 1.0 * (b - a)/1.0));
        
    }
    
    for (i = 0; i < n; ++i) //Formula basica do metodo de Simpson
    {
        a = x1 + i * base;
        b = x1 + (i + 1) * base;
        //Laco for para calculo da integral metodo de Simpson
        area3 = area3 + ((b - a) / 6.0) * (f1(a) + 4.0 * f1((a + b) / 2.0) + f1(b));
        
    }
    
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(6);
    cout << "*** Valores Metodo Retangulo ***" << endl;
    cout << "Valor calculado:     " << area1<< endl;
    cout << "Erro:                " << ErroRet(0.0 , 1.0) << endl;
    cout << "Solucao analitica:   0.746824\n" << endl;
    cout << "*** Valores Metodo Trapezio ***" << endl;
    cout << "Valor calculado:     " << area2 << endl;
    cout << "Erro:                " << ErroTrap(0.0 , 1.0) << endl;
    cout << "Solucao analitica:   0.746824\n" << endl;
    cout << "*** Valores Metodo Simpson ***" << endl;
    cout << "Valor calculado:     " << area3 << endl;
    cout << "Erro:                " << ErroSim(0.0 , 1.0) << endl;
    cout << "Solucao analitica:   0.746824\n" << endl;
    // chamada para funcao quadratura adaptativa
    double I = adaptiveSimpsons(f1, 0, 1, 0.000000001, 100);
    cout << "*** Valores Quadratura Adaptativa ***" << endl;
    cout << "Valor calculado:     " << I << endl;
    return 0;
    
}


