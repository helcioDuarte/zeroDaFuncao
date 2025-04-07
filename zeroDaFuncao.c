#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_ITER 1000

typedef enum { A, B, C } TipoFuncao;

double f(double x, TipoFuncao tipo) {
    switch (tipo) {
        case A:
            return pow(x, 5) - 2*pow(x, 4) - 9*pow(x, 3) + 22*pow(x, 2) + 4*x - 24;
        case B:
            return sqrt(x) - cos(x);
        case C:
            return (sqrt(x) - 5) * exp(-x);
        default:
            return 0;
    }
}


double f(double x, TipoFuncao tipo);


int bissecao(double a, double b, double eps, TipoFuncao tipo, double *raiz, int *iteracoes);

int secante(double x0, double x1, double eps, TipoFuncao tipo, double *raiz, int *iteracoes);

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Uso: %s <metodo: bs|sc> <eps> <x0> <x1> <funcao: a|b|c>\n", argv[0]);
        return 1;
    }

    char *metodo = argv[1];
    double eps = atof(argv[2]);
    printf("eps: %.15lf\n", eps);
    double x0 = atof(argv[3]);
    double x1 = atof(argv[4]);
    char funcao_id = argv[5][0];

    TipoFuncao tipo;
    if (funcao_id == 'a') tipo = A;
    else if (funcao_id == 'b') tipo = B;
    else if (funcao_id == 'c') tipo = C;
    else {
        printf("Função inválida. Use 'a', 'b' ou 'c'.\n");
        return 1;
    }

    double raiz;
    int iter;
    int convergiu = 0;

    if (strcmp(metodo, "bs") == 0) {
        convergiu = bissecao(x0, x1, eps, tipo, &raiz, &iter);
    } else if (strcmp(metodo, "sc") == 0) {
        convergiu = secante(x0, x1, eps, tipo, &raiz, &iter);
    } else {
        printf("Método inválido. Use 'bs' para bisseção ou 'sc' para secante.\n");
        return 1;
    }
    
    if (convergiu == 1) {
        printf("Valor de x é %.15lf - passos de iteração %d\n", raiz, iter);
    } else if (convergiu == 0) {
        printf("Método não convergiu no número máximo de iterações.\n");
    } else{
        return 1;
    }

    return 0;
}


int bissecao(double a, double b, double eps, TipoFuncao tipo, double *raiz, int *iteracoes) {
    if (f(a, tipo) * f(b, tipo) >= 0) {
        printf("Erro: f(a) e f(b) devem ter sinais opostos.\n");
        return 2;
    }

    double c;
    *iteracoes = 0;

    while ((b - a) / 2 > eps && *iteracoes < MAX_ITER) {
        c = (a + b) / 2;
        if (f(c, tipo) == 0.0) {
            break; 
        } else if (f(c, tipo) * f(a, tipo) < 0) {
            b = c;
        } else {
            a = c;
        }
        (*iteracoes)++;
    }

    *raiz = c;
    return (*iteracoes < MAX_ITER);
}
int secante(double x0, double x1, double eps, TipoFuncao tipo, double *raiz, int *iteracoes) {
    double x2;
    *iteracoes = 0;

    while (fabs(x1 - x0) > eps && *iteracoes < MAX_ITER) {
        if (f(x1, tipo) - f(x0, tipo) == 0) {
            printf("Erro: divisão por zero na secante.\n");
            return 0;
        }
        x2 = x1 - f(x1, tipo) * (x1 - x0) / (f(x1, tipo) - f(x0, tipo));
        x0 = x1;
        x1 = x2;
        (*iteracoes)++;
    }

    *raiz = x2;
    return (*iteracoes < MAX_ITER);
}