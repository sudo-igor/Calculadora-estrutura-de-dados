#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "expressao.h"

int validarExpressaoPostfixada(const char *expressao);

char *formatResult(double resultado) {
    char *resultadoStr = (char *)malloc(100);

    // Se o resultado for um nÃºmero inteiro, exibe sem casas decimais
    if (resultado == (int)resultado) {
        sprintf(resultadoStr, "%.0f", resultado);
    } else {
        // Exibe resultado com 2 casas decimais sem arredondamento
        sprintf(resultadoStr, "Aprox. %.2f", resultado);
    }

    return resultadoStr;
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    setlocale(LC_NUMERIC, "C");

    Expressao expressao;  
    char continuar = 'S';

    printf("==================================================================\n");
    printf("   ____        _               _             _                    \n");
    printf("  / ___| __ _ | |  ___  _   _ | |  __ _   __| |  ___   _ __  __ _ \n");
    printf(" | |    / _` || | / __|| | | || | / _` | / _` | / _ \\ | '__|/ _` |\n");
    printf(" | |___| (_| || || (__ | |_| || || (_| || (_| || (_) || |  | (_| |\n");
    printf("  \\____|\\__,_||_| \\___| \\__,_||_| \\__,_| \\__,_| \\___/ |_|   \\__,_|\n");
    printf("                                                                  \n");
    printf("          Bem-vindo à Calculadora de Expressões pós-fixadas!      ");

    do {
        printf("\n==================================================================\n");
        printf("\nDigite a expressão em notação pós-fixada: ");
        fgets(expressao.posFixa, sizeof(expressao.posFixa), stdin);
        expressao.posFixa[strcspn(expressao.posFixa, "\n")] = '\0';  

        if (strlen(expressao.posFixa) == 0) {
            break;
        } else if (!validarExpressaoPostfixada(expressao.posFixa)) {
            printf("\nExpressão pós-fixa inválida! Tente novamente.\n");
        } else {
            strcpy(expressao.inFixa, getFormaInFixa(expressao.posFixa));
            expressao.Valor = getValor(expressao.posFixa);
//            printf("\nResultados:\n");
            printf("\nExpressão infixa: %s\n", expressao.inFixa);  
            printf("Resultado: %s\n", formatResult(expressao.Valor));
        }

        printf("\nDeseja realizar outra operação? (S/N): ");
        scanf(" %c", &continuar);
        getchar();  
    } while (toupper(continuar) == 'S');
   
    printf("\nCalculadora finalizando...\n");

    return 0;
}
