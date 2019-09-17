/*PROGRAMACAO CIENTIFICA - PEL216
 ALUNO: Silvio Romero de Araújo Junior  RA: 118324-3
 PROFESSOR: Reinaldo Bianchi
 RELATORIO 6 - Metodos Numericos: Metodo de Monte Carlo
 PROGRAMA PARA O CALCULO DO TOROIDE*/
#include <iostream>
#include <random>
#include <chrono>
#include <math.h>
using namespace std;

//Linhas 7 - 21 Implementa o algoritmo de Mersenne Twister
namespace MyRandom {
    std::mt19937_64 seed {
        static_cast <std::mt19937_64::result_type> (std::time (nullptr))
    };
}
float getRandom (float min, float max) {
    std::mt19937_64 seed {
        static_cast <std::mt19937_64::result_type> (std::time (nullptr))
    };
    
    std::uniform_real_distribution <> realNumber (min, max);
    return realNumber (MyRandom::seed);
}


//Calcula o valor da função
float funcao(float x, float y, float z) {
    return pow(z, 2) + pow(sqrt(pow(x, 2) + pow(y, 2)) - 3, 2);
}

int main() {
    //Numero de iteracoes do laco for
    long int iteracoes = 0;
    float total = 0;
    // Limites de Integracoes
    float xinf = 1  , xsup = 4;
    float yinf = -3 , ysup = 4;
    float zinf = -1 , zsup = 1;
    
    cout << "Digite o numero de iteracoes desejado: ";
    cin >> iteracoes;
    
    //Laco para calculo dos pontos baseado na funcao aleatoria
    for (int i = 0; i <= iteracoes; i++) {
        float x = getRandom(xinf, xsup);
        float y = getRandom(yinf, ysup);
        float z = getRandom(zinf, zsup);
        
        float resultado = funcao(x, y, z);
        
        //Verifica se o valor calculado é um ponto dentro do Toroide
        if (resultado <= 1) {
            total += 1;
            
        }
    }
    
    //Calculo do Volume
    float V = (xsup - xinf) * (ysup - yinf) * (zsup - zinf);
    float resultado = V * (total / iteracoes);
    
    cout.precision(6);
    cout.setf(ios::fixed | ios::showpoint);
    cout << "Pontos: " << iteracoes << endl;
    cout << "Area da figura: " << resultado << endl;
    cout << "Valor teorico: 22.080000" << endl;
    
    return 0;
}

