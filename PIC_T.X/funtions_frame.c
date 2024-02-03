#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "funtions_frame.h"
#include "mcc_generated_files/uart1.h"

int splitString(const char* str, char delimiter, char* tokens[]) {
    char* token;
    int tokenCount = 0;

    token = strtok(str, "#");
    while (token != NULL && tokenCount < MAX_TOKENS) {
        tokens[tokenCount] = token;
        tokenCount++;
        token = strtok(NULL, "#");
    }

    return tokenCount;
}

void extraerPartes(const char *cadena, char *parteAlfabetica, float *parteFlotante) {
    char parteNumerica[MAX_SIZE];
    int i = 0;
    int j = 0;

    // Copiar la parte alfabética
    while (cadena[i] != '=' && cadena[i] != '\0'){
        parteAlfabetica[j++] = cadena[i++];
    }
    parteAlfabetica[j] = '\0';

    // Avanzar hasta la parte numérica
    while (cadena[i] != '=' && cadena[i] != '\0') {
        i++;
    }
    i++; // Avanzar después del '='

    // Copiar la parte numérica
    j = 0;
    while (cadena[i] != '\0' && (cadena[i] >= '0' && cadena[i] <= '9' || cadena[i] == ',' || cadena[i] == '.')) {
        parteNumerica[j++] = cadena[i++];
    }
    parteNumerica[j] = '\0';

    // Reemplazar la coma por un punto decimal
    for (int k = 0; k < j; k++) {
        if (parteNumerica[k] == ',') {
            parteNumerica[k] = '.';
            break;
        }
    }

    // Convertir la parte numérica a un valor flotante utilizando la función atof
    float resultado = atof(parteNumerica);


    *parteFlotante = resultado;
}
