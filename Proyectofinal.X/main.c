#include <xc.h>
#include "config.h"
#include "UART_LIB.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LCD_LIB.h"
#include "DHT11.h"
#include "ADC_LIB.h"
#include "PWM_LIB.h"

//Macros
#define delay_ms(x)    __delay_ms(x)
//Configuración I/O
#define BTN_UP_DIR     TRISDbits.TRISD0
#define BTN_DOWN_DIR   TRISDbits.TRISD1
#define BTN_SEL_DIR    TRISDbits.TRISD2
#define SENAL1_DIR     TRISBbits.TRISB0
#define ALARMA_DIR     TRISCbits.TRISC1
#define SENSORH_DIR    TRISAbits.TRISA6
#define PUERTA0_DIR    TRISAbits.TRISA5
#define PUERTA1_DIR    TRISBbits.TRISB3
#define RIEGO_DIR      TRISCbits.TRISC4

//Analogico o digital
#define BTN_ANSEL_UP   ANSELDbits.ANSELD0
#define BTN_ANSEL_DOWN ANSELDbits.ANSELD1
#define BTN_ANSEL_SEL  ANSELDbits.ANSELD2
#define SENAL1_ANSEL   ANSELBbits.ANSELB0
#define ALARMA_ANSEL   ANSELCbits.ANSELC1
#define SENSORH_ANSEL  ANSELAbits.ANSELA6
#define PUERTA0_ANSEL  ANSELAbits.ANSELA5 
#define PUERTA1_ANSEL  ANSELBbits.ANSELB3 
#define RIEGO_ANSEL    ANSELCbits.ANSELC4

//Lectura o escritura
#define BTN_PORT_UP    PORTDbits.RD0
#define BTN_PORT_DOWN  PORTDbits.RD1
#define BTN_PORT_SEL   PORTDbits.RD2
#define ALARMA_PORT    PORTCbits.RC1
#define PUERTA0_PORT   PORTAbits.RA5
#define PUERTA1_PORT   PORTBbits.RB3
#define RIEGO_PORT     PORTCbits.RC4

//Resistencias de pull up
#define BTN_WPU_UP    WPUDbits.WPUD0
#define BTN_WPU_DOWN  WPUDbits.WPUD1
#define BTN_WPU_SEL   WPUDbits.WPUD2

void Config();
void MenuPrincipal(void);
void MenuLogin(void);
void MenuLogin2(void);
void MenuPassword(void);
void MenuPassword2(void);
void MenuPassword3(void);
void MenuPasswordCon(void);
void MenuPasswordCon2(void);
void MenuCuenta(void);
void MenuCambioPass(void);
void MenuTemperaturas(void);
void MenuSeguridad(void);
void MenuAlerta(void);
void MenuBluetooth(char letra);
void MenuAlertaBluetooth(void);
void MenuPlantas(void);
void MenuActuadores(void);
void MenuVentiladores(void);
void MenuVelocidades(void);
void MenuPuerta(void);
void MenuLuces(void);
void MenuRiego(void);
void MenuConfigRiego(void);


enum{
    menu_principal,
    menu_login,
    menu_login2,
    menu_password,
    menu_password2,
    menu_password3,
    menu_passwordcon,
    menu_passwordcon2,
    menu_cuenta,
    menu_cambiopass,
    menu_temperaturas,
    menu_seguridad,
    menu_alerta,
    menu_plantas,
    menu_actuadores,
    menu_ventiladores,
    menu_luces,
    menu_puerta,
    menu_velocidades,
    menu_riego,
    menu_configriego,
};

char a  , flagalerta=0 , Rxflag=0, trama[20]=" " , buffer[20]=" ",auxStr[20]=" ",
     i =0, j , incorrect=0 , cont=0 , t;

signed char duty;

int contalerta=0, contaoff=0, contriego=0, tiemporiego=1, contriegooff;
float valoradc , hump;

char temp , hum;

char seg=0 , flagseg=0,flagriego=0;

char menuOp = menu_principal, opSel=1 ,bandera=0;

int passdefault[5]={0,0,0,0,0}, pass[5];

signed char num=0;

void __interrupt (irq(IRQ_TMR0)) timer(void){
    PIR3bits.TMR0IF = 0;
    TMR0L  = 0x3C;
    cont++;
    if(flagriego==1){
    contriego++;
    contriegooff;
        if(contriego==(600*tiemporiego)){
            RIEGO_PORT = 1;
        }
    if(RIEGO_PORT==1){
        PWM1_Set_Duty(50);
        contriegooff++;
                if(contriegooff==20){
                    PWM1_Set_Duty(0);
                    contriego=0;
                    contriegooff=0;
                    RIEGO_PORT=0;
                }
    }
    }
    
    if(cont==12){
        cont=0;
        valoradc = ADC_Read(ANA6);
        hump = (-0.038417*valoradc) + 157.32;
        Leer_DHT11(&temp, &hum);
        printf("*t%d",temp);
        printf("*H%d",hum);
        if(temp>25){
            PWM2_Set_Duty(100);
        } else{
            PWM2_Set_Duty(0);
        }
    }
    if(flagalerta==1){
        contalerta++;
        contaoff++;
        if(contalerta==300){
            ALARMA_PORT=0;
        }
        if(contaoff==400){
            ALARMA_PORT=1;
            contalerta=0;
            contaoff=0;
        }
    }
}

void __interrupt (irq(IRQ_INT0)) seguridad(void){
    PIR1bits.INT0IF = 0;
    if(seg==1){
        ALARMA_PORT = 1;
        flagalerta=1;
        lcd_clear();
        j=3;
        menuOp = menu_alerta;
    }
    
}


void __interrupt(irq(IRQ_U1RX)) RxFrames(void){
    
        a = UART1_Read();
        flagseg=1;
        MenuBluetooth(a);
}


int main(void) {
    
    Config();
    
    while(1){ 
        
        switch(menuOp){
            
            case menu_principal          :   MenuPrincipal(); break;
            case menu_login              :   MenuLogin(); break;
            case menu_login2             :   MenuLogin2(); break;
            case menu_password           :   MenuPassword(); break;
            case menu_password2          :   MenuPassword2(); break;
            case menu_password3          :   MenuPassword3(); break;
            case menu_passwordcon        :   MenuPasswordCon(); break;
            case menu_passwordcon2       :   MenuPasswordCon2(); break;
            case menu_cuenta             :   MenuCuenta(); break;
            case menu_cambiopass         :   MenuCambioPass(); break;
            case menu_temperaturas       :   MenuTemperaturas(); break;
            case menu_seguridad          :   MenuSeguridad(); break;
            case menu_alerta             :   MenuAlerta(); break;
            case menu_plantas            :   MenuPlantas(); break;
            case menu_actuadores         :   MenuActuadores(); break;
            case menu_ventiladores       :   MenuVentiladores(); break;
            case menu_velocidades        :   MenuVelocidades(); break;
            case menu_puerta             :   MenuPuerta(); break;
            case menu_luces              :   MenuLuces(); break;
            case menu_riego              :   MenuRiego(); break;
            case menu_configriego        :   MenuConfigRiego(); break;
        }
        MenuAlertaBluetooth();
    }
    return EXIT_SUCCESS;
}

void MenuBluetooth(char letra){
    
    
    switch(letra){
            case 't':
                lcd_clear();
                menuOp = menu_temperaturas; 
                break;
            case 'h': 
                lcd_clear();
                menuOp = menu_cuenta;    
                break;
            case 's': 
                lcd_clear();
                menuOp = menu_seguridad;    
                break;
            case 'p': 
                lcd_clear();
                menuOp = menu_plantas;    
                break;
            case 'r': 
                lcd_clear();
                menuOp = menu_configriego;    
                break;
            case 'L': 
                lcd_clear();
                menuOp = menu_luces;    
                break;
            case 'A': 
                lcd_clear();
                menuOp = menu_ventiladores;    
                break;
            case 'P': 
                lcd_clear();
                menuOp = menu_puerta;    
                break;
            case 'V': 
                lcd_clear();
                menuOp = menu_velocidades;    
                break;
            case 'O': 
                duty=100;
                PWM2_Set_Duty(duty);
                break;
            case 'F':
                duty=0;
                PWM2_Set_Duty(duty);
                break;
            case 'U': 
                if(duty<100){
                duty+=10;
                }
                PWM2_Set_Duty(duty);
                break;
            case 'D':
                if(duty>0){
                duty-=10;
                }
                PWM2_Set_Duty(duty);
                break; 
            case 'X': 
                PUERTA0_PORT = 0;
                PUERTA1_PORT = 1;
                PWM3_Set_Duty(50);
                delay_ms(1000);
                PWM3_Set_Duty(0);
                break;
            case 'Y':
                PUERTA0_PORT = 1;
                PUERTA1_PORT = 0;
                PWM3_Set_Duty(50);
                delay_ms(1000);
                PWM3_Set_Duty(0);
                break;
                
        }
    if(menuOp == menu_configriego){
        switch (letra){
            case 'u':
                if(flagriego==0){
                tiemporiego++;
                } 
                break;
            case 'b':
                if(flagriego==0){
                tiemporiego--;
                }
                break;
        }
    }
    if(flagseg==1 && menuOp== menu_seguridad){
        switch(letra){
            case 'o': 
                seg = 1;
                break;
            case 'f': 
                seg = 0;
                break;
            }
            flagseg=0;
         }
    if(flagalerta ==1 && menuOp == menu_alerta){
       if(letra=='d'){
                lcd_clear();
                opSel = 1;
                ALARMA_PORT = 0;
                flagalerta  = 0;
                contalerta=0;
                contaoff=0;
                menuOp = menu_cuenta;
       } 
    }
    
}

void Config(){
    
    
    Clock_Init();
    PWM1_Init(1000);
    PWM2_Init(1000);
    PWM3_Init(1000);
    UART1_Init(9600);
    PWM1_Start();
    lcd_init();
    ADC_Init();
    
    PIE4bits.U1IE       = 1;
    PIE4bits.U1RXIE     = 1;
    PIE1bits.INT0IE     = 1;
    PIR1bits.INT0IF     = 0;
    INTCON0bits.INT0EDG = 0;
    
    //Timer0
    
    T0CON0bits.MD16  = 0;
    T0CON0bits.OUTPS = 0;
    T0CON1bits.CS    = 0b010;
    T0CON1bits.CKPS  = 0b1101;
    T0CON1bits.ASYNC = 0;
    
    TMR0L  = 0x3C;
    
    PIE3bits.TMR0IE = 1;
    PIR3bits.TMR0IF = 0;
    T0CON0bits.EN = 1;
    
    //habilitadores interrupciones
    INTCON0bits.GIE     = 1;
    INTCON0bits.IPEN    = 0;

    
    
    lcd_disable_blink();
    lcd_disable_cursor();
    
    //Config A/D
    SENSORH_ANSEL  = 1;
    SENAL1_ANSEL   = 0;
    BTN_ANSEL_UP   = 0;
    BTN_ANSEL_DOWN = 0;
    BTN_ANSEL_SEL  = 0;
    ALARMA_ANSEL   = 0;
    ANSELCbits.ANSELC0 = 0;
    PUERTA0_ANSEL  = 0;
    PUERTA1_ANSEL  = 0;
    RIEGO_ANSEL    = 0;
    ANSELDbits.ANSELD7 = 0;
    ANSELDbits.ANSELD6 = 0;
    ANSELDbits.ANSELD5 = 0;
    
    //Config I/O
    SENSORH_DIR    = 1;
    SENAL1_DIR     = 1;
    BTN_UP_DIR     = 1;
    BTN_DOWN_DIR   = 1;
    BTN_SEL_DIR    = 1;
    ALARMA_DIR     = 0;
    PUERTA0_DIR    = 0;
    PUERTA1_DIR    = 0;
    RIEGO_DIR      = 0;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD7 = 0;
    
    //Config R-pull up
    BTN_WPU_UP   = 1;
    BTN_WPU_DOWN = 1;
    BTN_WPU_SEL  = 1;
    
    ALARMA_PORT = 0;
    RIEGO_PORT =  0;
    PORTDbits.RD7 =0;
    PORTDbits.RD6 =0;
    PORTDbits.RD5 =0;
}


void MenuPrincipal(void){
    
    lcd_out(1,1,"      HOME      ");
    
    if(BTN_PORT_UP == 0){
        while(BTN_PORT_UP == 0);
        opSel++;
        if(opSel>2){
        opSel=1;
        }
    }
    
    if(BTN_PORT_DOWN == 0){
        while(BTN_PORT_DOWN == 0);
        opSel--;
        if(opSel<1){
           opSel = 2;
        }
    }
    switch(opSel){
        case 1:            
            lcd_out(2,1,"    1.LOGIN     ");
            break;
            
        case 2:
            lcd_out(2,1,"    2.C-PASS    ");
            break;
        
    }
    
    if(BTN_PORT_SEL == 0){
        lcd_clear();
               
        switch(opSel){
            case 1: 
               menuOp = menu_login;
               j=3;
               break;
               
            case 2: 
               menuOp = menu_login2;
               j=3;
               break;
        }
        opSel = 1;
    }
    }

void MenuLogin(void){
    
    menuOp = menu_login;
    while(BTN_PORT_SEL == 0);
    lcd_out(1,1,"INGRESA PASSWORD");
    lcd_out(2,1,"->");
    sprintf(auxStr,"%d",num);
    lcd_out(2,j,auxStr);
    sprintf(auxStr,"%d",incorrect);
    lcd_out(2,16,auxStr);
    
    if(BTN_PORT_UP == 0){
      while(BTN_PORT_UP == 0);
      num++;
      if(num>9){
          num=0;
      }
      } 
    if(BTN_PORT_DOWN == 0){
      while(BTN_PORT_DOWN == 0);
       num--;
       if(num<0){
           num=9;
       }
      }
    if(BTN_PORT_SEL == 0){
        while(BTN_PORT_SEL == 0);
        pass[j-3] = num;
        j++;
        if(j>7){
            lcd_clear();
            menuOp = menu_password;
            j=3;
            opSel = 1;
        }
                
    }
}

void MenuLogin2(void){
    
    menuOp = menu_login2;
    while(BTN_PORT_SEL == 0);
    lcd_out(1,1," OLD   PASSWORD");
    lcd_out(2,1,"->");
    sprintf(auxStr,"%d",num);
    lcd_out(2,j,auxStr);
    sprintf(auxStr,"%d",incorrect);
    lcd_out(2,16,auxStr);
    
    if(BTN_PORT_UP == 0){
      while(BTN_PORT_UP == 0);
      num++;
      if(num>9){
          num=0;
      }
      } 
    if(BTN_PORT_DOWN == 0){
      while(BTN_PORT_DOWN == 0);
       num--;
       if(num<0){
           num=9;
       }
      }
    if(BTN_PORT_SEL == 0){
        while(BTN_PORT_SEL == 0);
        pass[j-3] = num;
        j++;
        if(j>7){
            lcd_clear();
            menuOp = menu_password2;
            j=3;
            opSel = 1;
        }
                
    }
}

void MenuPassword(void){
    
    lcd_out(1,1,"P:              ");
    for(i=0;i<=4;i++){
    sprintf(auxStr,"%d",pass[i]);
    lcd_out(1,i+3,auxStr);
    }
    lcd_out(2,1,"  YES      NO  ");
    
    if(BTN_PORT_UP == 0){
       while(BTN_PORT_UP == 0);
       opSel++;
       if(opSel>2){
           opSel = 1;
       }
    } 
    if(BTN_PORT_DOWN == 0){
       while(BTN_PORT_DOWN == 0);
       opSel--;
       if(opSel<1){
           opSel = 2;
       }
    }
    
    switch(opSel){
        case 1: lcd_char(2,6,'<');
                lcd_char(2,14,' ');
            break;
        case 2: lcd_char(2,6,' ');
                lcd_char(2,14,'<');
            break;
    }
    
    if(BTN_PORT_SEL == 0){
        lcd_clear();
        switch(opSel){
            case 1: menuOp = menu_passwordcon; break;
            case 2: menuOp = menu_login; break;
        }
        opSel = 1;
    }
}

void MenuPassword2(void){
    
    lcd_out(1,1,"P:              ");
    for(i=0;i<=4;i++){
    sprintf(auxStr,"%d",pass[i]);
    lcd_out(1,i+3,auxStr);
    }
    lcd_out(2,1,"  YES      NO  ");
    
    if(BTN_PORT_UP == 0){
       while(BTN_PORT_UP == 0);
       opSel++;
       if(opSel>2){
           opSel = 1;
       }
    } 
    if(BTN_PORT_DOWN == 0){
       while(BTN_PORT_DOWN == 0);
       opSel--;
       if(opSel<1){
           opSel = 2;
       }
    }
    
    switch(opSel){
        case 1: lcd_char(2,6,'<');
                lcd_char(2,14,' ');
            break;
        case 2: lcd_char(2,6,' ');
                lcd_char(2,14,'<');
            break;
    }
    
    if(BTN_PORT_SEL == 0){
        lcd_clear();
        switch(opSel){
            case 1: menuOp = menu_passwordcon2; break;
            case 2: menuOp = menu_login2; break;
        }
        opSel = 1;
    }
}

void MenuPassword3(void){
    
    lcd_out(1,1,"N-P:              ");
    for(i=0;i<=4;i++){
    sprintf(auxStr,"%d",pass[i]);
    lcd_out(1,i+5,auxStr);
    }
    lcd_out(2,1,"  YES      NO  ");
    
    if(BTN_PORT_UP == 0){
       while(BTN_PORT_UP == 0);
       opSel++;
       if(opSel>2){
           opSel = 1;
       }
    } 
    if(BTN_PORT_DOWN == 0){
       while(BTN_PORT_DOWN == 0);
       opSel--;
       if(opSel<1){
           opSel = 2;
       }
    }
    
    switch(opSel){
        case 1: lcd_char(2,6,'<');
                lcd_char(2,14,' ');
            break;
        case 2: lcd_char(2,6,' ');
                lcd_char(2,14,'<');
            break;
    }
    
    if(BTN_PORT_SEL == 0){
        while(BTN_PORT_SEL == 0);
        lcd_clear();
        switch(opSel){
            case 1: 
                
                lcd_out(1,1,"   SUCCESSFUL   ");
                lcd_out(2,1,"     CHANGE     ");
                delay_ms(1000);
                lcd_clear();
                menuOp = menu_principal; break;
                
            case 2: menuOp = menu_cambiopass; break;
        }
        opSel = 1;
    }
}

void MenuPasswordCon(void){
    
    if(passdefault[0]== pass[0] && passdefault[1]== pass[1] && passdefault[2]== pass[2]&&passdefault[3]== pass[3]
       && passdefault[4]== pass[4]){
        lcd_out(1,1,"    CORRECT     ");
        lcd_out(2,1,"    PASSWORD    ");
        delay_ms(1000);
        incorrect=0;
        lcd_clear();
        menuOp = menu_cuenta;
    }
    else{
        lcd_out(1,1,"   INCORRECT    ");
        lcd_out(2,1,"    PASSWORD    ");
        delay_ms(1000);
        lcd_clear();
        menuOp = menu_login;
        incorrect++;
        opSel = 1;
    }
}

void MenuPasswordCon2(void){
    
    if(passdefault[0]== pass[0] && passdefault[1]== pass[1] && passdefault[2]== pass[2]&&passdefault[3]== pass[3]
       && passdefault[4]== pass[4]){
        lcd_out(1,1,"    CORRECT     ");
        lcd_out(2,1,"    PASSWORD    ");
        delay_ms(1000);
        incorrect=0;
        lcd_clear();
        menuOp = menu_cambiopass;
    }
    else{
        lcd_out(1,1,"   INCORRECT    ");
        lcd_out(2,1,"    PASSWORD    ");
        delay_ms(1000);
        lcd_clear();
        menuOp = menu_login2;
        incorrect++;
        opSel = 1;
    }
}

void MenuCuenta(void){
    
    lcd_out(1,1,"      HOME      ");
    
    if(BTN_PORT_UP == 0){
        while(BTN_PORT_UP == 0);
        opSel++;
        if(opSel>5){
        opSel=1;
        }
    }
    
    if(BTN_PORT_DOWN == 0){
        while(BTN_PORT_DOWN == 0);
        opSel--;
        if(opSel<1){
           opSel = 5;
        }
    }
    
    switch(opSel){
        case 1:     lcd_out(2,1,"   1.SEGURIDAD  "); break;
        case 2:     lcd_out(2,1,"    2.PLANTAS   "); break;
        case 3:     lcd_out(2,1,"   3.ACTUADORES "); break;
        case 4:     lcd_out(2,1,"    4.SENSORES  "); break;
        case 5:     lcd_out(2,1,"    5.SIGN OUT  "); break;

    }
    
    if(BTN_PORT_SEL == 0){
        while(BTN_PORT_SEL == 0 );
        lcd_clear();
        switch(opSel){
            case 1: 
                menuOp = menu_seguridad;
                break;
            case 2:
                menuOp = menu_plantas;
                break;
            case 3:
                menuOp = menu_actuadores;
                break;
            case 4: 
                menuOp = menu_temperaturas;
                break;
            case 5: 
                lcd_out(1,1,"    SIGNING     ");
                lcd_out(2,1,"      OUT...    "); 
                delay_ms(1000);
                lcd_clear();
                menuOp = menu_principal; 
                break;
        }
        opSel = 1;
    }
}


void MenuCambioPass(void){
    
    while(BTN_PORT_SEL == 0);
    lcd_out(1,1," NEW   PASSWORD");
    lcd_out(2,1,"->");
    sprintf(auxStr,"%d",num);
    lcd_out(2,j,auxStr);
    
    if(BTN_PORT_UP == 0){
      while(BTN_PORT_UP == 0);
      num++;
      if(num>9){
          num=0;
      }
      } 
    if(BTN_PORT_DOWN == 0){
      while(BTN_PORT_DOWN == 0);
       num--;
       if(num<0){
           num=9;
       }
      }
    if(BTN_PORT_SEL == 0){
        while(BTN_PORT_SEL == 0);
        passdefault[j-3] = num;
        j++;
        if(j>7){
            lcd_clear();
            menuOp = menu_password3;
            j=3;
            opSel = 1;
        }
                
    }
}
void MenuTemperaturas(void){
    
    lcd_out(1,1,"   TEMP Y HUM   ");
    
    switch(opSel){
        case 1:
        sprintf(auxStr,"T:%d",temp);
        lcd_out(2,5,"C");
        lcd_out(2,1,auxStr);
        sprintf(auxStr,"H:%d",hum);
        lcd_out(2,8,auxStr);
        lcd_char(2,12,'%');
        printf("*t%d",temp);
        printf("*H%d",hum);
        break;
    }
    
    if(BTN_PORT_SEL == 0){
        while(BTN_PORT_SEL == 0 );
        lcd_clear();
        switch(opSel){
            case 1: 
                menuOp = menu_cuenta;
                break;              
        }
        
    }
}

void MenuSeguridad(void){
    
    lcd_out(1,1,"    SEGURIDAD   "); 
    
    switch(opSel){
        case 1:
            lcd_out(2,1,"    ENCENDIDA   ");
            break;
        case 2:
            lcd_out(2,1,"     APAGADA    ");
            break;
        case 3:
            lcd_out(2,1,"      SALIR     ");
            break;
    }
    
    if(BTN_PORT_UP == 0){
        while(BTN_PORT_UP == 0);
        opSel++;
        if(opSel>3){
        opSel=1;
        }
    }
    
    if(BTN_PORT_DOWN == 0){
        while(BTN_PORT_DOWN == 0);
        opSel--;
        if(opSel<1){
           opSel = 3;
        }
    }
    
    
    if(BTN_PORT_SEL ==0){
        while(BTN_PORT_SEL == 0);
        switch(opSel){
            case 1: 
                seg = 1;          
                break;
            case 2: 
                seg = 0;
                break;
            case 3: 
                menuOp = menu_cuenta;
                opSel = 1;
                break;
        }
    }
    
    switch(seg){
        case 1:
            printf("*LR0G255B0*");
            break;
        case 0:
            printf("*LR255G0B0*");
            break;
    }
}

void MenuAlerta(void){
    
    lcd_out(1,1,"ALERTA  PUT-PASS");
    lcd_out(2,1,"->");
    sprintf(auxStr,"%d",num);
    lcd_out(2,j,auxStr);
    sprintf(auxStr,"%d",incorrect);
    lcd_out(2,16,auxStr);
    
    if(BTN_PORT_UP == 0){
      while(BTN_PORT_UP == 0);
      num++;
      if(num>9){
          num=0;
      }
      } 
    if(BTN_PORT_DOWN == 0){
      while(BTN_PORT_DOWN == 0);
       num--;
       if(num<0){
           num=9;
       }
      }
    if(BTN_PORT_SEL == 0){
        while(BTN_PORT_SEL == 0);
        pass[j-3] = num;
        j++;
        if(j>7){
            if(passdefault[0]== pass[0] && passdefault[1]== pass[1] && passdefault[2]== pass[2]&&passdefault[3]== pass[3]
               && passdefault[4]== pass[4]){
                lcd_out(1,1,"    CORRECT     ");
                lcd_out(2,1,"    PASSWORD    ");
                delay_ms(1000);
                incorrect=0;
                lcd_clear();
                opSel = 1;
                ALARMA_PORT = 0;
                flagalerta  = 0;
                contalerta=0;
                contaoff=0;
                menuOp = menu_cuenta;
            }else{
                lcd_clear();
                j=3;
            }    
        }
       }
    
}

void MenuAlertaBluetooth(void){
    switch(flagalerta){
        case 0:
            printf("*aR0G0B0*");
            break;
        case 1:
            printf("*aR255G0B0*");
            break;
    }
}

void MenuPlantas(void){
    lcd_out(1,1,"   TEMP Y HUM   ");
    
    if(BTN_PORT_UP == 0){
        while(BTN_PORT_UP == 0);
        opSel++;
        lcd_clear();
        if(opSel>3){
        opSel=1;
        }
    }
    
    if(BTN_PORT_DOWN == 0){
        while(BTN_PORT_DOWN == 0);
        opSel--;
        lcd_clear();
        if(opSel<1){
           opSel = 3;
        }
    }
    
    switch(opSel){
        case 1:           
            sprintf(auxStr,"H: %0.0f",hump);
            lcd_out(2,1,auxStr);
            delay_ms(200);
            break;
        case 2:
            lcd_out(2,1,"CONFIG RIEGO");
            break;
        case 3:
            lcd_out(2,1,"    SALIR   ");
            break;
    }
    
    if(BTN_PORT_SEL == 0){
        while(BTN_PORT_SEL == 0 );
        lcd_clear();
        switch(opSel){
            case 2: 
                menuOp = menu_riego;
                break;
            case 3: 
                menuOp = menu_cuenta;
                break;
        }
        opSel = 1;
    }
}

void MenuActuadores(void){
    
    lcd_out(1,1,"   ACTUADORES    ");
    
    if(BTN_PORT_UP == 0){
        while(BTN_PORT_UP == 0);
        opSel++;
        if(opSel>4){
        opSel=1;
        }
    }
    
    if(BTN_PORT_DOWN == 0){
        while(BTN_PORT_DOWN == 0);
        opSel--;
        if(opSel<1){
           opSel = 4;
        }
    }
    
    switch(opSel){
        case 1:     lcd_out(2,1,"    1.PUERTA  "); break;
        case 2:     lcd_out(2,1," 2.VENTILADOR "); break;
        case 3:     lcd_out(2,1,"    3.LUCES   "); break;
        case 4:     lcd_out(2,1,"    4.SALIR   "); break;


    }
    
    if(BTN_PORT_SEL == 0){
        while(BTN_PORT_SEL == 0 );
        lcd_clear();
        switch(opSel){
            case 1: 
                menuOp = menu_puerta;
                break;
            case 2:
                menuOp = menu_ventiladores;
                break;
            case 3: 
                menuOp = menu_luces;
                break;
            case 4: 
                menuOp = menu_cuenta;
                break;
        }
        opSel = 1;
    }
}

void MenuVentiladores(void){
    
    lcd_out(1,1,"  VENTILADORES   ");
    
    if(BTN_PORT_UP == 0){
        while(BTN_PORT_UP == 0);
        opSel++;
        if(opSel>4){
        opSel=1;
        }
    }
    
    if(BTN_PORT_DOWN == 0){
        while(BTN_PORT_DOWN == 0);
        opSel--;
        if(opSel<1){
           opSel = 4;
        }
    }
    
    switch(opSel){
        case 1:     lcd_out(2,1,"   ENCENDER   "); break;
        case 2:     lcd_out(2,1,"    APAGAR    "); break;
        case 3:     lcd_out(2,1,"  VELOCIDAD   "); break;
        case 4:     lcd_out(2,1,"    SALIR     "); break;


    }

    if(BTN_PORT_SEL == 0){
        while(BTN_PORT_SEL == 0 );
        lcd_clear();
        switch(opSel){
            case 1: 
                duty=100;
                PWM2_Set_Duty(duty);
                break;
            case 2:
                duty=0;
                PWM2_Set_Duty(duty);
                break;
            case 3:
                opSel = 1;
                menuOp= menu_velocidades;
                break;
            case 4:
                opSel = 1;
                menuOp = menu_cuenta;
                break;
        }
        
    }
}

void MenuVelocidades(void){
    
    lcd_out(1,1,"VELOCIDADES   ");
    sprintf(auxStr,"%d",duty);
    lcd_out(1,14,auxStr);
    printf("*V%d",duty);
    
    if(BTN_PORT_UP == 0){
        while(BTN_PORT_UP == 0);
        opSel++;
        if(opSel>3){
        opSel=1;
        }
    }
    
    if(BTN_PORT_DOWN == 0){
        while(BTN_PORT_DOWN == 0);
        opSel--;
        if(opSel<1){
           opSel = 3;
        }
    }
    
    switch(opSel){
        case 1:     lcd_out(2,1,"   SUBIR-V    "); break;
        case 2:     lcd_out(2,1,"   BAJAR-V    "); break;
        case 3:     lcd_out(2,1,"    SALIR     "); break;

    }
    
    if(BTN_PORT_SEL == 0){
        while(BTN_PORT_SEL == 0 );
        lcd_clear();
        switch(opSel){
            case 1: 
                if(duty<100){
                duty+=10;
                }
                PWM2_Set_Duty(duty);
                break;
            case 2:
                if(duty>0){
                duty-=10;
                }
                PWM2_Set_Duty(duty);
                break;
            case 3:
                opSel = 1;
                menuOp = menu_cuenta;
                break;                
        }
        
    }
}


void MenuPuerta(void){
    lcd_out(1,1,"PUERTA   ");
    
    if(BTN_PORT_UP == 0){
        while(BTN_PORT_UP == 0);
        opSel++;
        if(opSel>3){
        opSel=1;
        }
    }
    
    if(BTN_PORT_DOWN == 0){
        while(BTN_PORT_DOWN == 0);
        opSel--;
        if(opSel<1){
           opSel = 3;
        }
    }
    
    switch(opSel){
        case 1:     lcd_out(2,1,"   SUBIR-G    "); break;
        case 2:     lcd_out(2,1,"   BAJAR-G    "); break;
        case 3:     lcd_out(2,1,"    SALIR     "); break;

    }
    
    if(BTN_PORT_SEL == 0){
        while(BTN_PORT_SEL == 0 );
        lcd_clear();
        switch(opSel){
            case 1: 
                PUERTA0_PORT = 0;
                PUERTA1_PORT = 1;
                PWM3_Set_Duty(50);
                delay_ms(1000);
                PWM3_Set_Duty(0);
                break;
            case 2:
                PUERTA0_PORT = 1;
                PUERTA1_PORT = 0;
                PWM3_Set_Duty(50);
                delay_ms(1000);
                PWM3_Set_Duty(0);
                break;
            case 3:
                opSel = 1;
                menuOp = menu_cuenta;
                break;                
        }
        
    }
}

void MenuLuces(void){
    
    lcd_out(1,1,"   LUCES   ");
    
    if(BTN_PORT_UP == 0){
        while(BTN_PORT_UP == 0);
        opSel++;
        if(opSel>4){
        opSel=1;
        }
    }
    
    if(BTN_PORT_DOWN == 0){
        while(BTN_PORT_DOWN == 0);
        opSel--;
        if(opSel<1){
           opSel = 4;
        }
    }
    
    switch(opSel){
        case 1:     lcd_out(2,1,"   GARAJE    "); break;
        case 2:     lcd_out(2,1,"   COCINA     "); break;
        case 3:     lcd_out(2,1,"    SALA      "); break;
        case 4:     lcd_out(2,1,"    SALIR      "); break;

    }
    
    if(BTN_PORT_SEL == 0){
        while(BTN_PORT_SEL == 0 );
        
        switch(opSel){
            case 1: 
                    if(PORTDbits.RD7==0){
                        PORTDbits.RD7 =1;
                    }
                    if(PORTDbits.RD7==1){
                        PORTDbits.RD7 =0;
                    }
                break;
            case 2:
                if(PORTDbits.RD5==0){
                        PORTDbits.RD5 =1;
                    }
                    if(PORTDbits.RD5==1){
                        PORTDbits.RD5 =0;
                    }
                break;
            case 3:
                if(PORTDbits.RD6==0){
                        PORTDbits.RD6 =1;
                    }
                    if(PORTDbits.RD6==1){
                        PORTDbits.RD6 =0;
                    }
                
                break;
            case 4:
                lcd_clear();
                opSel = 1;
                menuOp = menu_cuenta;
                break;  
        }
        
    }
    
    switch(a){
            case '1': 
                delay_ms(100);
                    if(PORTDbits.RD7==0){
                        PORTDbits.RD7 =1;
                    }
                    if(PORTDbits.RD7==1){
                        PORTDbits.RD7 =0;
                    }
                break;
            case '2':
                if(PORTDbits.RD5==0){
                        PORTDbits.RD5 =1;
                    }
                    if(PORTDbits.RD5==1){
                        PORTDbits.RD5 =0;
                    }
                break;
            case '3':
                if(PORTDbits.RD6==0){
                        PORTDbits.RD6 =1;
                    }
                    if(PORTDbits.RD6==1){
                        PORTDbits.RD6 =0;
                    }
                
                break; 
        }
}



void MenuRiego(void){
    lcd_out(1,1,"   RIEGO   ");
    
    if(BTN_PORT_UP == 0){
        while(BTN_PORT_UP == 0);
        opSel++;
        if(opSel>4){
        opSel=1;
        }
    }
    
    if(BTN_PORT_DOWN == 0){
        while(BTN_PORT_DOWN == 0);
        opSel--;
        if(opSel<1){
           opSel = 4;
        }
    }
    
    switch(opSel){
        case 1:     lcd_out(2,1,"   ENCENDER    "); break;
        case 2:     lcd_out(2,1,"    APAGAR     "); break;
        case 3:     lcd_out(2,1,"    CONFIG      "); break;
        case 4:     lcd_out(2,1,"    SALIR      "); break;

    }
    
    if(BTN_PORT_SEL == 0){
        while(BTN_PORT_SEL == 0 );
        lcd_clear();
        switch(opSel){
            case 1: 
                flagriego = 1;
                break;
            case 2: 
                flagriego = 0;
                break;
            case 3: 
                menuOp = menu_configriego;
                break;                
            case 4:
                menuOp = menu_cuenta;
                break;                
        }
        
    }
}

void MenuConfigRiego(void){
    lcd_out(1,1,"TIEMPO-RIEGO  ");
    sprintf(auxStr,"%d",tiemporiego);
    lcd_out(1,14,auxStr);
    printf("*c%d",tiemporiego);
    
    if(BTN_PORT_UP == 0){
        while(BTN_PORT_UP == 0);
        opSel++;
        if(opSel>4){
        opSel=1;
        }
    }
    
    if(BTN_PORT_DOWN == 0){
        while(BTN_PORT_DOWN == 0);
        opSel--;
        if(opSel<1){
           opSel = 4;
        }
    }
    
    switch(opSel){
        case 1:     lcd_out(2,1,"   SUBIR-T     "); break;
        case 2:     lcd_out(2,1,"   BAJAR-T     "); break;
        case 3:     lcd_out(2,1,"   RESERVED      "); break;
        case 4:     lcd_out(2,1,"    SALIR      "); break;

    }
    
    if(BTN_PORT_SEL == 0){
        while(BTN_PORT_SEL == 0 );
        lcd_clear();
        switch(opSel){
            case 1:
                if(flagriego==0){
                tiemporiego++;
                }
                break;
            case 2: 
                if(flagriego==0){
                tiemporiego--;
                }
                break;
            case 3: 
                break;                
            case 4:
                menuOp = menu_cuenta;
                break;                
        }
        
    }
    
    
}
