#include <xc.h>
#include "config.h"
#include "LCD_LIB.h"
#include "ADC_LIB.h"
#include <stdio.h>
#include <stdint.h>

//Configuración I/O
#define BTN_UP_DIR     TRISDbits.TRISD0
#define BTN_DOWN_DIR   TRISDbits.TRISD1
#define BTN_SEL_DIR    TRISBbits.TRISB4
#define LED_DIR TRISA
#define CALENTADOR_DIR TRISFbits.TRISF3
#define MOTOR_DIR1     TRISEbits.TRISE0
#define MOTOR_DIR2     TRISCbits.TRISC1
#define PIN_ECHO_DIR   TRISCbits.TRISC3
#define PIN_TRIG_DIR   TRISCbits.TRISC2


//Analogico o digital
#define BTN_ANSEL_UP   ANSELDbits.ANSELD0
#define BTN_ANSEL_DOWN ANSELDbits.ANSELD1
#define BTN_ANSEL_SEL  ANSELBbits.ANSELB4
#define LED_ANSEL ANSELA
#define CALENTADOR_ANSEL ANSELFbits.ANSELF3
#define MOTOR_ANSEL1 ANSELEbits.ANSELE0
#define MOTOR_ANSEL2 ANSELCbits.ANSELC1
#define PIN_ECHO_ANSEL ANSELCbits.ANSELC3
#define PIN_TRIG_ANSEL ANSELCbits.ANSELC2

//Lectura o escritura
#define BTN_PORT_UP    PORTDbits.RD0
#define BTN_PORT_DOWN  PORTDbits.RD1
#define BTN_PORT_SEL   PORTBbits.RB4
#define LED_PORT PORTA
#define CALENTADOR_PORT PORTFbits.RF3
#define MOTOR_PORT1      PORTEbits.RE0
#define MOTOR_PORT2      PORTCbits.RC1
#define PIN_ECHO_PORT PORTCbits.RC3
#define PIN_TRIG_PORT PORTCbits.RC2


//Resistencias de pull up
#define BTN_WPU_UP    WPUDbits.WPUD0
#define BTN_WPU_DOWN  WPUDbits.WPUD1
#define BTN_WPU_SEL   WPUBbits.WPUB4




void MenuPrincipal(void);
void MenuPrincipalCon(void);
void MenuLed(void);
void MenuLedCon(void);
void Sec1Est(void);
void Sec2Est(void);
void Sec3Est(void);
void MenuCalentador(void);
void MenuMotor(void);
void MenuS(void);
void Advertencia(void);
void Advertencia2(void);
unsigned int ultrasonido;


enum{
    menu_principal,
    menu_principalcon,
    menu_led,
    menu_ledcon,
    menu_calentador,
    menu_motor,
    menu_sensores,
    usonido,
    advertencia,
    advertencia2
};

char fig1[] = {
  0b00100,
  0b01110,
  0b11111,
  0b01110,
  0b11111,
  0b11011,
  0b11011,
  0b00000
};
char fig2[] = {
  0b00100,
  0b00100,
  0b01100,
  0b01111,
  0b11110,
  0b00110,
  0b00100,
  0b00100
};

char state;
int menuOp=menu_principal, opSel=1;
unsigned int distancia;
float temp;
char auxStr[20]=" ";
char estado;

unsigned int getdistancia(){
    unsigned int cont = 0;
    PORTCbits.RC4 = 1;
    __delay_us(10);
    PORTCbits.RC4 = 0;
    while(PORTCbits.RC5==0);
    while(PORTCbits.RC5==1){
        cont++;
        __delay_us(58);
    }
    return(cont);

}

void main(){
    
//    ADCON1 = 0x0F;
//    OSCCON1 = 0b01100000;
//    OSCFRQ = 0b100;
//    OSCCON2 = 0b110<<4 | 0b0000;
    Clock_Init();
    //Config A/D
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSELB0 = 1;
    BTN_ANSEL_UP   = 0;
    BTN_ANSEL_DOWN = 0;
    BTN_ANSEL_SEL  = 0;
    LED_ANSEL = 0x00;
    ANSELF = 0x00;
    CALENTADOR_ANSEL = 0;
    MOTOR_ANSEL1 = 0;
    MOTOR_ANSEL2 = 0;
    PIN_ECHO_ANSEL = 0;
    PIN_TRIG_ANSEL = 0;
    TRISCbits.TRISC4 =0;
    TRISCbits.TRISC5 =1;
    ANSELCbits.ANSELC4=0;
    ANSELCbits.ANSELC5=0;
    
    //Config I/O
    PIN_TRIG_DIR = 0;
    PIN_ECHO_DIR = 1;
    BTN_UP_DIR     = 1;
    BTN_DOWN_DIR   = 1;
    BTN_SEL_DIR    = 1;
    LED_DIR = 0x00;
    CALENTADOR_DIR = 0;
    MOTOR_DIR1 = 0;
    MOTOR_DIR2 = 0;
    
    //Config R-pull up
    BTN_WPU_UP = 1;
    BTN_WPU_DOWN = 1;
    BTN_WPU_SEL = 1;
    
    lcd_init();
    ADC_Init();
    
    lcd_custom_char(0,fig1);
    lcd_custom_char(1,fig2);
    lcd_disable_blink();
    lcd_disable_cursor();
    

    while(1){
        
            float valoradc = ADC_Read(ANB0);
            temp = valoradc*0.09935;
            ultrasonido = getdistancia();
            if(ultrasonido<5){
                lcd_clear();
                CALENTADOR_PORT = 0;
                MOTOR_PORT1=0;
                MOTOR_PORT2=0;
                
                menuOp = advertencia2;
                
            }
            if(temp>70){
                lcd_clear();
                CALENTADOR_PORT = 0;
                MOTOR_PORT1=0;
                MOTOR_PORT2=0;
                
                menuOp = advertencia;
                
            }
            
        switch(menuOp){
             case menu_principal:     MenuPrincipal();     break;
             case menu_principalcon:     MenuPrincipalCon();     break;
             case menu_led:      MenuLed();      break;   
             case menu_ledcon:      MenuLedCon();      break;
             case menu_calentador:      MenuCalentador();      break;
             case menu_motor:      MenuMotor();      break;
             case menu_sensores: MenuS(); break;
             case usonido: getdistancia(); break;
             case advertencia: Advertencia(); break;
             case advertencia2: Advertencia2(); break;
         }   
        
        __delay_ms(150);
    }
    
    return;
}


void MenuPrincipal(void){
    lcd_out(1,1," MENU PRINCIPAL ");
    lcd_out(2,1,"1.LEDS  2.C   ->");
    MOTOR_PORT1 = 0;
    MOTOR_PORT2 = 0;
    LATA=0x00;
    
    if(BTN_PORT_UP == 0){
            while(BTN_PORT_UP == 0);
            opSel++;
        }

    if(BTN_PORT_DOWN == 0){
            while(BTN_PORT_DOWN == 0);
            opSel--;
            if(opSel<1){
                opSel=3;
            }
        }
    
    switch(opSel){
        case 1: lcd_char(2,7,'<');
                lcd_char(2,12,' ');
                break;
        case 2: lcd_char(2,7,' ');
                lcd_char(2,12,'<');
                break;
        case 3: while(opSel==3 && BTN_PORT_SEL == 1){
                lcd_char(2,7,' ');
                lcd_char(2,12,' ');
                
                lcd_char(2,15,' ');
                lcd_char(2,16,' ');
                __delay_ms(100);
                lcd_char(2,15,'-');
                lcd_char(2,16,'>');
                __delay_ms(100);
                
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
                        }
                    if(BTN_PORT_SEL == 0){
                        lcd_clear();
                        menuOp = menu_principalcon;
                        }
                }
                break;
    }
    
    if(BTN_PORT_SEL == 0){
        lcd_clear();
        switch(opSel){
            case 1: menuOp = menu_led; break;
            case 2: menuOp = menu_calentador; break;
        }
        opSel = 1;
    }
}

void MenuPrincipalCon(void){
    lcd_out(1,1," MENU PRINCIPAL ");
    lcd_out(2,1,"<- 3.MT  4.S    ");

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
            }
    
    switch(opSel){
        case 1: while(opSel==1 && BTN_PORT_SEL==1){
                lcd_char(2,1,'<');
                lcd_char(2,2,'-');
                __delay_ms(100);
                lcd_char(2,1,' ');
                lcd_char(2,2,' ');
                 __delay_ms(100);
                 
                lcd_char(2,8,' ');
                lcd_char(2,13,' ');
                
                    if(BTN_PORT_UP == 0){
                        while(BTN_PORT_UP == 0);
                        opSel++;
                    } 
                    if(BTN_PORT_DOWN == 0){
                        while(BTN_PORT_DOWN == 0);
                        opSel--;
                        if(opSel<1){
                            opSel=3;}
                    }
                
                    if(BTN_PORT_SEL == 0){
                        lcd_clear();
                        menuOp = menu_principal;
                        }
                }
                break;
                
        case 2: lcd_char(2,8,'<');
                lcd_char(2,13,' ');
                if(BTN_PORT_SEL==0){
                    lcd_clear();
                    menuOp= menu_motor;
                }
                break;
                
        case 3: lcd_char(2,8,' ');
                lcd_char(2,13,'<');     
                break;
    }
    
    if(BTN_PORT_SEL == 0){
        lcd_clear();
        switch(opSel){
            case 3: menuOp = menu_sensores;
        }
        opSel = 1;
    }
}

void MenuLed(void){
    lcd_out(1,1," MENU SECUENCIA ");
    lcd_out(2,1,"1.S1  2.S2    ->");
    
    if(BTN_PORT_UP == 0){
        while(BTN_PORT_UP == 0);
        opSel++;
    }
    
    if(BTN_PORT_DOWN == 0){
        while(BTN_PORT_DOWN == 0);
        opSel--;
        if(opSel<1){
            opSel=3;
        }
    }
    
    switch(opSel){
        case 1: lcd_char(2,5,'<');
                lcd_char(2,11,' ');
                if(BTN_PORT_SEL==0){
                    while(BTN_PORT_SEL==0);
                    state = 1;
                    while(state==1){
                    LATA = 0b00000000;
                    Sec1Est();
                    LATA = 0b10000001;
                    Sec1Est();
                    LATA = 0b11000011;
                    Sec1Est();
                    LATA = 0b11100111;
                    Sec1Est();
                    LATA = 0b111111111;
                    Sec1Est();
                    LATA = 0b11100111;
                    Sec1Est();
                    LATA = 0b11000011;
                    Sec1Est();
                    LATA = 0b100000001;
                    Sec1Est();
                    LATA = 0b00000000;
                    Sec1Est();
                    
                    }
                }
                break;
                
        case 2: lcd_char(2,5,' ');
                lcd_char(2,11,'<');
                if(BTN_PORT_SEL==0){
                    while(BTN_PORT_SEL==0);
                    state = 1;
                    while(state==1){
                    LATA = 0b10101010;
                    Sec2Est();
                    LATA = ~0b10101010;
                    Sec2Est();
                    LATA = 0b10101010;
                    Sec2Est();
                    LATA = ~0b10101010;
                    Sec2Est();
                    LATA = 0b10101010;
                    Sec2Est();
                    LATA = ~0b10101010;
                    Sec2Est();
                    LATA = 0b10101010;
                    Sec2Est();
                    LATA = ~0b10101010;
                    Sec2Est();
                    LATA = 0b10101010;
                    Sec2Est();
                    LATA = ~0b10101010;
                    Sec2Est();
                    }
                }
                break;
        case 3: while(opSel==3 && BTN_PORT_SEL==1){
                lcd_char(2,5,' ');
                lcd_char(2,11,' ');
                
                lcd_char(2,15,' ');
                lcd_char(2,16,' ');
                __delay_ms(100);
                lcd_char(2,15,'-');
                lcd_char(2,16,'>');
                __delay_ms(100);
                
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
                        }
                    if(BTN_PORT_SEL == 0){
                        lcd_clear();
                        menuOp = menu_ledcon;
                        }
                }
                break;
    }
    
    if(BTN_PORT_SEL == 0){
        lcd_clear();
        switch(opSel){
            case 1: break; 
            case 2: break; 
        }
        opSel = 1;
        
    }
}

void MenuLedCon(void){
    
    lcd_out(1,1," MENU SECUENCIA ");
    lcd_out(2,1,"<-    3.S3      ");
    lcd_char(2,16,0);
    
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
    }
    
    switch(opSel){
        case 1: while(opSel==1 && BTN_PORT_SEL==1){
                lcd_char(2,1,'<');
                lcd_char(2,2,'-');
                __delay_ms(100);
                lcd_char(2,1,' ');
                lcd_char(2,2,' ');
                 __delay_ms(100);
                 
                lcd_char(2,11,' ');
                
                    if(BTN_PORT_UP == 0){
                        while(BTN_PORT_UP == 0);
                        opSel++;
                    } 
                    if(BTN_PORT_DOWN == 0){
                        while(BTN_PORT_DOWN == 0);
                        opSel--;
                        if(opSel<1){
                            opSel=3;}
                    }
                
                    if(BTN_PORT_SEL == 0){
                        lcd_clear();
                        menuOp = menu_led;
                        }
                }
                break;
                
        case 2: lcd_char(2,11,'<');
        
                if(BTN_PORT_SEL==0){
                    while(BTN_PORT_SEL==0);
                    state = 1;
                    while(state==1){
                        
                    LATA=0b11000000;
                    Sec3Est();
                    LATA=0b11100000;
                    Sec3Est();
                    LATA=0b11110000;
                    Sec3Est();
                    LATA=0b11111000;
                    Sec3Est();
                    LATA=0b11111100;
                    Sec3Est();
                    LATA=0b11111110;
                    Sec3Est();
                    LATA=0b11111100;
                    Sec3Est();
                    LATA=0b11111000;
                    Sec3Est();
                    LATA=0b11110000;
                    Sec3Est();
                    LATA=0b11100000;
                    Sec3Est();
                    LATA=0b11000000;
                    Sec3Est();
                    LATA=0b10000000;
                    Sec3Est();
                    }
                }
                break;
                
        case 3: while(opSel==3 && BTN_PORT_SEL==1){
                lcd_char(2,11,' ');
                
                lcd_char(2,16,0);
                __delay_ms(100);
                lcd_char(2,16,' ');
                __delay_ms(100);
                
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
                        }
                    if(BTN_PORT_SEL == 0){
                        lcd_clear();
                        menuOp = menu_principal;
                        }
                }
                break;
    }
    
    if(BTN_PORT_SEL == 0){
        lcd_clear();
        switch(opSel){
            case 2:break; 
        }
        opSel = 1;
        
    }
}

void Sec1Est(void){
    if(BTN_PORT_SEL==0){
        while(BTN_PORT_SEL==0);
        state=0;
        LATA=0;
        }
    if(state==0){
        LATA=0;
    }
    lcd_char(2,5,'<');
    lcd_char(2,11,' ');
    __delay_ms(100);
    lcd_char(2,5,' ');
    lcd_char(2,11,' ');
    __delay_ms(100);
}
void Sec2Est(void){
    if(BTN_PORT_SEL==0){
        while(BTN_PORT_SEL==0);
        state=0;
        LATA=0;
        }
    if(state==0){
        LATA=0;
    }
    lcd_char(2,5,' ');
    lcd_char(2,11,' ');
    __delay_ms(100);
    lcd_char(2,5,' ');
    lcd_char(2,11,'<');
    __delay_ms(100);
}

void Sec3Est(void){
    if(BTN_PORT_SEL==0){
        while(BTN_PORT_SEL==0);
        state=0;
        LATA=0;
        }
    if(state==0){
        LATA=0;
    }
    lcd_char(2,11,' ');
    __delay_ms(100);
    lcd_char(2,11,'<');
    __delay_ms(100);
}

void MenuCalentador(void){
    lcd_out(1,1,"MENU  CALENTADOR");
    lcd_out(2,1,"1.ON  2.OFF     ");
    lcd_char(2,16,0);
    
    if(BTN_PORT_UP == 0){
            while(BTN_PORT_UP == 0);
            opSel++;
        }

    if(BTN_PORT_DOWN == 0){
            while(BTN_PORT_DOWN == 0);
            opSel--;
            if(opSel<1){
                opSel=3;
            }
        }
    
    switch(opSel){
        case 1: lcd_char(2,5,'<');
                lcd_char(2,12,' ');
                break;
        case 2: lcd_char(2,5,' ');
                lcd_char(2,12,'<');
                break;
        case 3: while(opSel==3 && BTN_PORT_SEL==1){
                
                lcd_char(2,16,0);
                __delay_ms(100);
                lcd_char(2,16,' ');
                __delay_ms(100);
                
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
                        }
                    if(BTN_PORT_SEL == 0){
                        lcd_clear();    
                        CALENTADOR_PORT = 0;
                        menuOp = menu_principal;
                        
                        }
                }
                break;
    }
    
    if(BTN_PORT_SEL == 0){
        switch(opSel){
            case 1: CALENTADOR_PORT = 1;
                    estado=1;
                    break;
            case 2: CALENTADOR_PORT = 0; 
                    estado=0;
                    break;
        }
    }
    if(estado==1){
        lcd_char(2,14,1);
    }
    if(estado==0){
        lcd_char(2,14," ");
    }
}

void MenuMotor(void){
    lcd_out(1,1,"   MENU MOTOR   ");
    lcd_out(2,1,"1.D  2.I  3.OFF ");
    lcd_char(1,16,0);
    
    if(BTN_PORT_UP == 0){
            while(BTN_PORT_UP == 0);
            opSel++;
        }

    if(BTN_PORT_DOWN == 0){
            while(BTN_PORT_DOWN == 0);
            opSel--;
            if(opSel<1){
                opSel=4;
            }
        }
    
    switch(opSel){
        case 1: lcd_char(2,4,'<');
                lcd_char(2,9,' ');
                break;
        case 2: lcd_char(2,4,' ');
                lcd_char(2,9,'<');
                break;
        case 3: lcd_char(2,16,'<');
                break;
        case 4: while(opSel==4 && BTN_PORT_SEL==1){
                
                lcd_char(1,16,0);
                __delay_ms(100);
                lcd_char(1,16,' ');
                __delay_ms(100);
                
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
                        }
                    if(BTN_PORT_SEL == 0){
                        lcd_clear();
                        MOTOR_PORT1 = 0;
                        MOTOR_PORT2 = 0;
                        menuOp = menu_principal;
                        
                        }
                }
                break;
    }
    
    if(BTN_PORT_SEL == 0){
        switch(opSel){
            case 1: MOTOR_PORT1=1;
                    MOTOR_PORT2=0;
                    break;
            case 2: MOTOR_PORT1=0;
                    MOTOR_PORT2=1;
                    break;
            case 3: MOTOR_PORT1=0;
                    MOTOR_PORT2=0;
                    break;
        }
    }
}

void MenuS(void){
    
    __delay_ms(100);
    lcd_out(1,1,"  MENU SENSORES ");
    lcd_char(2,16,0);
    
    sprintf(auxStr,"D: %03d",ultrasonido);
    lcd_out(2,1,auxStr);
    lcd_out(2,7,"cm");
    sprintf(auxStr,"T: %0.1f",temp);
    lcd_out(2,10,auxStr);
    
    if(BTN_PORT_SEL == 0){
        lcd_clear();
        opSel=1;
        menuOp = menu_principal;
    }

    }


void Advertencia(void){
    lcd_out(1,1,"TEMPERATURA");
    lcd_out(2,1,"ELEVADA");
    if(temp<70){
        menuOp = menu_principal;
    }
}
void Advertencia2(void){
    lcd_out(1,1,"HAY UN OBJETO");
    lcd_out(2,1,"MUY CERCANO  ");
    if(ultrasonido>5){
        menuOp = menu_principal;
    }
}
