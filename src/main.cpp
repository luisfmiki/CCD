#include <Arduino.h>
#include "Timers.h"
#include "ADC.h"
#define SIZE 128  // buffer circular 128 pixels
#define fCLK 9600 // frequencia do ADC
#define SERIAL_TX_BUFFER_SIZE 128

/* armazenamento dos dados, ToDo: tratamento dos dados */
uint16_t amostras[SIZE];
volatile uint16_t amostraIndex = 0;

/* varaiveis de controle das formas de onda */
bool pulsoSI = false;
bool risingCLK = false;


/* bloco de interrupcoes ------------------------------------------- */
ISR(TIMER2_COMPB_vect){
    risingCLK = !risingCLK;
    TCNT2 = 0;
}
ISR(TIMER1_COMPA_vect){
    if(pulsoSI) {
        OCR1A = 6250;   // 100ms, duracao maxima entre cada pulso SI
        pulsoSI = false;
        TCNT1 = 0;
    } else {
        OCR1A = 9;      // 144us, duracao do pulso SI no caso de CLK de 7375Hz
        pulsoSI = true;
        TCNT1 = 0;
    }
}
ISR(ADC_vect){
    if (risingCLK)
    {
        amostras[amostraIndex] = ADC;
        amostraIndex++;
        ADCSRA &= ~_BV(ADIE);

        /* desativa os timers */
        if (amostraIndex > 127) {
            TIMSK1 = 0;
            TIMSK2 = 0;
            TCCR1B = 0;
            TCCR2B = 0;
        }
    }
}
/* fim do bloco de interrupcoes ------------------------------------------- */



void setup()
{
    TIMSK0 = 0; // desativa ints do timer0

    int tINT;
    Serial.begin(115200);
    Serial.print("Entre com o tempo de integracao desejado em ms(11ms < t < 100ms): ");
    tINT = Serial.read();
    while (tINT < 11 || tINT > 100)
    {
        Serial.println("Valor invalido");
        Serial.print("Entre com o tempo de integracao desejado em ms(11ms < t < 100ms): ");
        tINT = Serial.read();
    }

    cli();
    cfgADC();
    cfgTimerCLK();
    cfgTimerSI(0);
    sei();

}

void loop()
{
    



    // while (ADCSRA & _BV(ADIE))
    //     ; // Wait for audio sampling to finish
    // cli();
    
    //     ADCSRA |= _BV(ADIE); // Resume sampling interrupt
    //     sei();
}