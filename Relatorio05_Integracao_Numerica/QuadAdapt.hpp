/*PROGRAMACAO CIENTIFICA - PEL216
 ALUNO: Silvio Romero de Araujo Junior  RA: 118324-3
 PROFESSOR: Reinaldo Bianchi
 RELATORIO 5 - Funcao para a Quadratura Adaptaviva */

#ifndef QuadAdapt_hpp
#define QuadAdapt_hpp


double adaptiveSimpsonsAux(double (*f)(double), double a, double b, double epsilon,
                           double S, double fa, double fb, double fc, int bottom);
double adaptiveSimpsons(double (*f)(double),   // ptr para a função
                        double a, double b,  // intervalo [a,b]
                        double epsilon,  // tolerancia de erro
                        int maxRecursionDepth);
#endif /* QuadAdapt_hpp */
