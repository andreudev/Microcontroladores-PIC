#include <xc.h>
#define _XTAL_FREQ 64000000UL

#define DHT11_PIN_PORT 	PORTEbits.RE0 
#define DHT11_PIN_LAT 	LATEbits.LATE0
#define DHT11_PIN_DIR 	TRISEbits.TRISE0

void DHT11_Start(void);
void DHT11_Response(void);
int DHT11_Read_Byte(void);
short DHT11_Read_Data(float *temp, float *hum);
unsigned DHT11_Join_Data(unsigned h, unsigned l);