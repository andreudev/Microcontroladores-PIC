#include "mcc_generated_files/mcc.h"
#include "dht11.h"

float temp, hume,adc_conv;
short ok_dht;
float ;int flag,leda,ledb,ledc,m_der,m_izq,m_stop;
unsigned int distancia;

unsigned int getDistancia(){
    unsigned int contador=0;
    TRIG_PORT = 1;
    __delay_us(10);
    TRIG_PORT = 0;
    while (ECHO_PORT==0);
    while (ECHO_PORT==1){
        contador++;
        __delay_us(58);
    }
    return (contador);
    }

    
void main(void)
{
    
    SYSTEM_Initialize();


    while (1)
    {
        if(G_DER_GetValue()==0){
            while(G_DER_GetValue()==0);
            M_1_LAT = 0;
            M_2_LAT = 1;
            m_der = 1;
            m_izq = 0;
            m_stop = 0;
        }
        if(G_IZQ_GetValue()==0){
            while(G_IZQ_GetValue()==0);
            M_1_LAT = 1;
            M_2_LAT = 0;
            m_der = 0;
            m_izq = 1;
            m_stop = 0;
        }
        if(G_STOP_GetValue()==0){
            while(G_STOP_GetValue()==0);
            M_1_LAT = 1;
            M_2_LAT = 1;
            m_der = 0;
            m_izq = 0;
            m_stop = 1;
        }
        if(BTNA_PORT==0){
            while(BTNA_PORT==0);
            LEDA_Toggle();
        }
        if(BTNB_PORT==0){
            while(BTNB_PORT==0);
            LEDB_Toggle();
        }
        if(BTNC_PORT==0){
            while(BTNC_PORT==0);
            LEDC_Toggle();
        }
        
        
        leda = LEDA_PORT;
        ledb = LEDB_PORT;
        ledc = LEDC_PORT;
        
        adc_conv = ADCC_GetSingleConversion(0)*0.001221;
        distancia = getDistancia();
        flag = get_DHT();
        
        if(flag==1){
            flag=0;
            DHT11_Read_Data(&temp,&hume);
        }
        printf("#%0.1f/%0.1f/%0.1f/%04d/%d/%d/%d/%d/%d/%d*",
                hume,temp,adc_conv,distancia,leda,ledb,ledc,m_izq,m_stop,m_der);
        
        __delay_ms(30);
   }                                                                                             
}