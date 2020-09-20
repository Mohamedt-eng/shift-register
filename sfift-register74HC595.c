sbit DATA_pin at  PORTA.B0;
sbit CLCOK_pin at PORTA.B1;
sbit LATCH_pin at PORTA.B2;

void clock_signal(void){
    CLCOK_pin = 1;
    delay_us(200);
    CLCOK_pin = 0;
    delay_us(200);
}
void latch_enable(void)
   {
    LATCH_pin = 1;
    delay_us(200);
    LATCH_pin = 0;
    }
void send_data(unsigned int data_out)
{
    int i;
    unsigned hold;
    for (i=0 ; i<16 ; i+=1)
    {
        DATA_pin = (data_out >> i) & (0x01);
        clock_signal();
    }
    latch_enable(); // Data finally submitted
}
void codFar(){ 
        send_data(0b1111111111111111);PORTB.B0=1;PORTB.B1=1;
}
void shutdown(){
  send_data(0b0000000000000000);PORTB.B0=0;PORTB.B1=0;
}
void func_green(){
 while(1){
        send_data(0b0000000000001100);
        PORTB.B0=0;
        PORTB.B1=0;
        delay_ms(50);
        send_data(0b0000000000110000);
        PORTB.B0=0;
        PORTB.B1=0;
        delay_ms(50);
        send_data(0b0000000011000000);
        PORTB.B0=0;
        PORTB.B1=0;
        delay_ms(50);
         send_data(0b000000000110000);
        PORTB.B0=0;
        PORTB.B1=0;
        delay_ms(50);
        send_data(0b000000000001100);
        PORTB.B0=0;
        PORTB.B1=0;
        delay_ms(50);

  }
}
void Interrupt() {
         }
         if (INTCON.RBIF) {
              if(PORTB.B4==0){            //Button RB4
                   delay_ms(50);
                   while(1) {
                        PORTB.B2=1;
                        delay_ms(150);
                        PORTB.B2=0;
                        delay_ms(150);
                        if(PORTB.B4==0) {
                              break;
                         }
                   }
              }
              if(PORTB.B5==0){         //bUTTON RB5
                  delay_ms(50);
                  while(1){
                       PORTB.B3=1;
                       delay_ms(150);
                       PORTB.B3=0;
                       delay_ms(150);
                       if(PORTB.B5==0){
                            break;
                       }
                  }
              }
              if(PORTB.B6==0){             //BUTTON RB6
                  delay_ms(60);
                  while(1){
                        send_data(0b0000000000000000);
                        PORTB.B0=0;
                        PORTB.B1=0;
                        delay_ms(100);
                        send_data(0b0000111100000000);
                        PORTB.B0=1;
                        PORTB.B1=1;
                        delay_ms(100);
                        send_data(0b0000000011111100);
                        PORTB.B0=0;
                        PORTB.B1=0;
                        delay_ms(100);
                        send_data(0b1111000000000011);
                        PORTB.B0=0;
                        PORTB.B1=0;
                        delay_ms(100);
                        if(PORTB.B6==0){
                            delay_ms(50);
                            send_data(0b0000000000000000);
                            PORTB.B0=0;
                            PORTB.B1=0  ;
                            break ;
                        }
                  }
              }
              if(PORTB.B7==0){           //BUTTON RB7
                  delay_ms(100);
                  codFar();

               }
         }
         INTCON.RBIF=0;


}
void main(){
    TRISA.B0 = 0; // Set  DATA_pin as output pin
    TRISA.B1 = 0; // Set  CLCOK_pin as output pin
    TRISA.B2 = 0; // Set LATCH_pin as output pin

    TRISB = 0B11110000;
    PORTB = 0B11110000;
    INTCON = 0B10100000;
    OPTION_REG = 0B00000111;
    //TMR0=22;


}
