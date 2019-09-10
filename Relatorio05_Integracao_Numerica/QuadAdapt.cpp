/*PROGRAMACAO CIENTIFICA - PEL216
 ALUNO: Silvio Romero de Araujo Junior  RA: 118324-3
 PROFESSOR: Reinaldo Bianchi
 RELATORIO 5 - Funcao para a Quadratura Adaptaviva */

#include "QuadAdapt.hpp"
#include <math.h>  // include file for fabs and sin
#include <stdio.h> // include file for printf

//
// Função recursiva auxiliar parar a função adaptiveSimpsons() abaixo
//
double adaptiveSimpsonsAux(double (*f)(double), double a, double b, double epsilon,
                           double S, double fa, double fb, double fc, int bottom) {
    double c = (a + b)/2, h = b - a;
    double d = (a + c)/2, e = (c + b)/2;
    double fd = f(d), fe = f(e);
    double Sleft = (h/12)*(fa + 4*fd + fc);
    double Sright = (h/12)*(fc + 4*fe + fb);
    double S2 = Sleft + Sright;
    if (bottom <= 0 || fabs(S2 - S) <= 15*epsilon)
        return S2 + (S2 - S)/15;
    return adaptiveSimpsonsAux(f, a, c, epsilon/2, Sleft,  fa, fc, fd, bottom-1) +
    adaptiveSimpsonsAux(f, c, b, epsilon/2, Sright, fc, fb, fe, bottom-1);
}

//
// Quadratura de Simpson Adaptativa
//
double adaptiveSimpsons(double (*f)(double),   // ptr para a função
                        double a, double b,  // intervalo [a,b]
                        double epsilon,  // tolerancia de erro
                        int maxRecursionDepth) {   // recursão cap
    double c = (a + b)/2, h = b - a;
    double fa = f(a), fb = f(b), fc = f(c);
    double S = (h/6)*(fa + 4*fc + fb);
    return adaptiveSimpsonsAux(f, a, b, epsilon, S, fa, fb, fc, maxRecursionDepth);
}
