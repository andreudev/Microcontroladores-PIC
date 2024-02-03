#ifndef DHT11_H
#define	DHT11_H

#define TRIS_DHT11 TRISCbits.TRISC0 //configuro el registro del bit donde esta conectado el DHT11                                                              
#define PORT_DHT11 PORTCbits.RC0                                                                                                                                                         
#define LAT_DHT11  LATCbits.LATC0    //configuro el pin donde conectare el DHT11

uint8_t check;                         //creo una variable q solo sirve para ver si el dht11 respondio o esta teniendo problemas                                   //

void StartSignal(void);                                                                                                                                                                                                                                           
void CheckResponse(void);
uint8_t ReadData(void);                                                                                                               
void Leer_DHT11(uint8_t *temperatura, uint8_t *humedad);

#endif	/* DHT11_H */
