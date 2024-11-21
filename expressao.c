#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "expressao.h"

// Função para avaliar a expressão na notação pós-fixada
float getValor(char *Str) {
    float stack[512];
    int top = -1;
    char *token = strtok(Str, " ");

    while (token != NULL) {
        if (sscanf(token, "%f", &stack[top + 1]) == 1) {
            // Se é um número, empilha
            top++;
        } else {
            // Se é um operador, desempilha e calcula
            if (top < 1) {
                fprintf(stderr, "Erro: Expressão inválida. Operador sem operandos.\n");
                exit(EXIT_FAILURE);
            }
            float b = stack[top--];
            float a;
            if (strcmp(token, "raiz") == 0) {
                if (b < 0) {
                    fprintf(stderr, "Erro: Raiz quadrada de número negativo.\n");
                    exit(EXIT_FAILURE);
                }
                stack[++top] = sqrt(b);
            } else {
                a = stack[top--];
                if (strcmp(token, "+") == 0) {
                    stack[++top] = a + b;
                } else if (strcmp(token, "-") == 0) {
                    stack[++top] = a - b;
                } else if (strcmp(token, "*") == 0) {
                    stack[++top] = a * b;
                } else if (strcmp(token, "/") == 0) {
                    if (b == 0) {
                        fprintf(stderr, "Erro: Divisão por zero.\n");
                        exit(EXIT_FAILURE);
                    }
                    stack[++top] = a / b;
                } else if (strcmp(token, "^") == 0) {
                    stack[++top] = pow(a, b);
                } else if (strcmp(token, "sen") == 0) {
                    stack[++top] = sin(b * M_PI / 180);
                } else if (strcmp(token, "cos") == 0) {
                    stack[++top] = cos(b * M_PI / 180);
                } else if (strcmp(token, "tg") == 0) {
                    stack[++top] = tan(b * M_PI / 180);
                } else if (strcmp(token, "log") == 0) {
                    if (b <= 0) {
                        fprintf(stderr, "Erro: Logaritmo de número não positivo.\n");
                        exit(EXIT_FAILURE);
                    }
                    stack[++top] = log10(b);
                } else {
                    fprintf(stderr, "Erro: Operador desconhecido: %s\n", token);
                    exit(EXIT_FAILURE);
                }
            }
        }
        token = strtok(NULL, " ");
    }
    if (top != 0) {
        fprintf(stderr, "Erro: Expressão inválida. Verifique a quantidade de operandos e operadores.\n");
        exit(EXIT_FAILURE);
    }
    return stack[top]; // Retorna o resultado final
}

// Função para converter a notação pós-fixada para infixa
char *getFormaInFixa(char *Str) {
    char *stack[512];
    int top = -1;
    char *token = strtok(Str, " ");

    while (token != NULL) {
        if (sscanf(token, "%f", &((float){0})) == 1) {
            // Se é um número, empilha
            stack[++top] = strdup(token);
        } else {
            // Se é um operador, desempilha e forma a expressão
            if (top < 1) {
                fprintf(stderr, "Erro: Expressão inválida. Operador sem operandos.\n");
                exit(EXIT_FAILURE);
            }
            char *b = stack[top--];
            char *a = stack[top--];
            char *expr = (char *)malloc(512);
            snprintf(expr, 512, "(%s %s %s)", a, token, b);
            stack[++top] = expr;
            free(a);
            free(b);
        }
        token = strtok(NULL, " ");
    }
    if (top != 0) {
        fprintf(stderr, "Erro: Expressão inválida. Verifique a quantidade de operandos e operadores.\n");
        exit(EXIT_FAILURE);
    }
    return stack[top]; // Retorna a expressão infixa
}