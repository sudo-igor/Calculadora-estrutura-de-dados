#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "expressao.h"

#define MAX 100

typedef struct {
    double items[MAX];
    int top;
} Pilha;

typedef struct {
    char items[MAX][MAX];
    int top;
} StringPilha;

void initPilha(Pilha *pilha) { pilha->top = -1; }
void push(Pilha *pilha, double value) { pilha->items[++pilha->top] = value; }
double pop(Pilha *pilha) { return pilha->items[pilha->top--]; }

void initStringPilha(StringPilha *pilha) { pilha->top = -1; }
void pushString(StringPilha *pilha, const char *value) { strcpy(pilha->items[++pilha->top], value); }
char* popString(StringPilha *pilha) { return pilha->items[pilha->top--]; }

int isOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int isOperadorUnario(const char *str) {
    return (strcmp(str, "sqrt") == 0 || strcmp(str, "sen") == 0 ||
        strcmp(str, "cos") == 0 || strcmp(str, "log") == 0 || 
        strcmp(str, "tg") == 0 || strcmp(str, "raiz") == 0);
}

void postfixToInfix(const char *expressao, char *resultadoInfix) {
    StringPilha pilha;
    initStringPilha(&pilha);

    const char *token = expressao;
    char buffer[MAX], operando1[MAX], operando2[MAX], resultado[MAX*4];
    int i;

    while (*token) {
        if (isspace(*token)) {
            token++;
            continue;
        }

        i = 0;
        while (*token && !isspace(*token)) {
            buffer[i++] = *token++;
        }
        buffer[i] = '\0';

        if (isdigit(buffer[0]) || (buffer[0] == '-' && isdigit(buffer[1]))) {
            pushString(&pilha, buffer);
        } else {
            if (isOperadorUnario(buffer)) {
                // Operações com um operando
                char operando[MAX];
                strcpy(operando, popString(&pilha));
                sprintf(resultado, "(%s %s)", buffer, operando);
            } else {
                // Operações com dois operandos
                strcpy(operando2, popString(&pilha));
                strcpy(operando1, popString(&pilha));
                sprintf(resultado, "(%s %s %s)", operando1, buffer, operando2);
            }
            pushString(&pilha, resultado);
        }
    }

    strcpy(resultadoInfix, popString(&pilha));
}

double evaluatePostfix(const char *expressao) {
    Pilha pilha;
    initPilha(&pilha);

    const char *token = expressao;
    char buffer[MAX];
    int i;

    while (*token) {
        if (isspace(*token)) {
            token++;
            continue;
        }
        i = 0;
       
        while (*token && !isspace(*token)) {
            buffer[i++] = *token++;
        }
        buffer[i] = '\0';
       
        if (isdigit(buffer[0]) || (buffer[0] == '-' && isdigit(buffer[1]))) {
            push(&pilha, atof(buffer));
        } else if (strcmp(buffer, "+") == 0) {
            double b = pop(&pilha);
            double a = pop(&pilha);
            push(&pilha, a + b);
        } else if (strcmp(buffer, "-") == 0) {
            double b = pop(&pilha);
            double a = pop(&pilha);
            push(&pilha, a - b);
        } else if (strcmp(buffer, "*") == 0) {
            double b = pop(&pilha);
            double a = pop(&pilha);
            push(&pilha, a * b);
        } else if (strcmp(buffer, "/") == 0) {
            double b = pop(&pilha);
            if (b == 0) {
                printf("Erro: Divisão por zero!\n");
                exit(1);
            }
            double a = pop(&pilha);
            push(&pilha, a / b);
        } else if (strcmp(buffer, "^") == 0) {
            double b = pop(&pilha);
            double a = pop(&pilha);
            push(&pilha, pow(a, b));
        } else if (strcmp(buffer, "raiz") == 0) {
            double a = pop(&pilha);
            if (a < 0) {
                printf("Erro: Raiz quadrada de número negativo!\n");
                exit(1);
            }
            push(&pilha, sqrt(a));
        } else if (strcmp(buffer, "sen") == 0) {
            double a = pop(&pilha);
            a = fmod(a, 360.0);
            double rad = a * M_PI / 180.0;
            double resultado = sin(rad);
           
            if (fabs(resultado) < 1e-6) {
                resultado = 0.0;
            }
            push(&pilha, resultado);
        } else if (strcmp(buffer, "cos") == 0) {
            double a = pop(&pilha);
            a = fmod(a, 360.0);
            double rad = a * M_PI / 180.0;
            double resultado = cos(rad);
   
            if (fabs(resultado) < 1e-6) {
                resultado = 0.0;
            }
            push(&pilha, resultado);
        } else if (strcmp(buffer, "tg") == 0) {
            double a = pop(&pilha);
            if (fmod(a, 180.0) == 90.0 || fmod(a, 180.0) == 270.0) {
                printf("Erro: Tangente indefinida para %g graus!\n", a);
                exit(1);
            }
            push(&pilha, tan(a * M_PI / 180.0));
        } else if (strcmp(buffer, "log") == 0) {
            double a = pop(&pilha);
            if (a <= 0) {
                printf("Erro: Logaritmo de número menor ou igual a zero!\n");
                exit(1);
            }
            push(&pilha, log10(a));
        } else {
            printf("Erro: Operador desconhecido '%s'!\n", buffer);
            exit(1);
        }
    }
    return pop(&pilha);
}

int validarExpressaoPostfixada(const char *expressao) {
    int operandoCount = 0;
    int operadorCount = 0;
    int encontrouEspaco = 0; // Para verificar se há espaços

    const char *token = expressao;
    char buffer[MAX];
    int i;

    while (*token) {
        if (isspace(*token)) {
            encontrouEspaco = 1; // Há pelo menos um espaço
            token++;
            continue;
        }

        i = 0;
        while (*token && !isspace(*token)) {
            buffer[i++] = *token++;
        }
        buffer[i] = '\0';

        if (isdigit(buffer[0]) || (buffer[0] == '-' && isdigit(buffer[1]))) {
            operandoCount++;
        } else if (isOperador(buffer[0]) || isOperadorUnario(buffer)) {
            operadorCount++;
            if (isOperadorUnario(buffer)) {
                if (operandoCount < 1) {
                    printf("Erro: Operador unário '%s' sem operandos suficientes.\n", buffer);
                    return 0;
                }
            } else {
                if (operandoCount < 2) {
                    printf("Erro: Operador binário '%s' sem operandos suficientes.\n", buffer);
                    return 0;
                }
                operandoCount--; // Dois operandos viram um na pilha
            }
        } else {
            printf("Erro: Token inválido encontrado '%s'.\n", buffer);
            return 0;
        }
    }

    // Verifica se há espaços na expressão
    if (!encontrouEspaco) {
        printf("Erro: A expressão deve conter espaços para separar operandos e operadores.\n");
        return 0;
    }

    return (operandoCount == 1); // Deve restar exatamente um operando na pilha
}

char *getFormaInFixa(char *Str) {
    static char resultado[512];
    char tempExpressao[512];
    strcpy(tempExpressao, Str);
    postfixToInfix(tempExpressao, resultado);
    return resultado;
}

float getValor(char *Str) {
    char tempExpressao[512];
    strcpy(tempExpressao, Str);
    return (float) evaluatePostfix(tempExpressao);
}
