#ifndef EXPRESSAO_H
#define EXPRESSAO_H

typedef struct {
char posFixa[512]; // Express�o na forma pos fixa, como 3 12 4 + *
char inFixa[512]; // Express�o na forma pos fixa, como 3 * (12 + 4)
float Valor; // Valor num�rico da express�o
} Expressao;

char *getFormaInFixa(char *Str); // Retorna a forma inFixa de Str (posFixa)
float getValor(char *Str); // Calcula o valor de Str (na forma posFixa)

#endif
