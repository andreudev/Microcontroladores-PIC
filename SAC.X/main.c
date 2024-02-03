
#include "mcc_generated_files/mcc.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/uart1.h"
#include "funtions_frame.h"



/*
                         Main application
 */

extern char frame[RX_BUFFER_SIZE];
extern int index;



void main(void)
{
    
    // RECEPCIÓN DE DATOS E INTERPRETACIÓN
    
    char string[MAX_SIZE];
    char stringCiclo[MAX_SIZE];
    char stringRecipiente[MAX_SIZE];
    char stringPeso[MAX_SIZE];
    char parteAlfabetica[MAX_SIZE];
    char* tokens[MAX_TOKENS];
    
    float parteFlotante;
    uint16_t value_adc;
    
    SYSTEM_Initialize();
    while (1)
    {
    

        strcpy(string, frame);  // Copiar el contenido del arreglo en la cadena
        printf("Cadena: %s\n", string);  // Imprimir la cadena resultante
        extraerPartes(string, parteAlfabetica, &parteFlotante);
        printf("Parte alfabética: %s\n", parteAlfabetica);
        printf("Parte flotante: %f\n", parteFlotante);
        printf("Indice %d\n",index);
        
        int tokenCount = splitString(string, '#', tokens);
        // Imprimir los tokens
        for (int i = 0; i < tokenCount; i++) {
        printf("Token %d: %s\n", i, tokens[i]);
        }
        

        __delay_ms(1000);
    }
}

