#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expressao.h"

int main() {
    Expressao exp;

    // Testes
    const char *testes[][3] = {
        {"3 4 + 5 *", "(3 + 4) * 5", "35"},
        {"7 2 * 4 +", "7 * 2 + 4", "18"},
        {"8 5 2 4 + * +", "8 + ( 5 * (2 + 4))", "38"},
        {"6 2 / 3 + 4 *", "(6 / 2 + 3) * 4", "24"},
        {"9 5 2 8 * 4 + * + 9 +", "9 + (5 * (2 + 8 * 4))", "109"},
        {"2 3 + log 5 / log(2 + 3) / 5", "Aprox. 0.14", "Aprox. 0.14"},
        {"10 log 3 ^ 2 +", "(log10)^3 + 2", "3"},
        {"45 60 + 30 cos *", "(45 + 60) * cos(30)", "Aprox. 90.93"},
        {"0.5 45 sen 2 ^ +", "sen(45)^2 + 0.5", "1"}
    };

    printf("Teste | Notação Posfixa             | Notação Infixa                     | Valor\n");
    printf("-----------------------------------------------------------------------------------\n");

    for (int i = 0; i < sizeof(testes) / sizeof(testes[0]); i++) {
        strcpy(exp.posFixa, testes[i][0]);
        exp.Valor = getValor(exp.posFixa);
        char *infixa = getFormaInFixa(exp.posFixa);
        
        printf("%-5d | %-30s | %-30s | %.2f\n", i + 1, exp.posFixa, infixa, exp.Valor);
        
        free(infixa); // Libere a memória alocada para a expressão infixa
    }

    return 0;
}