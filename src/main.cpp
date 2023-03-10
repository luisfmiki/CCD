#include <Arduino.h>
#include "Timers.h"
#include "ADC.h"
#define SIZE 128  // buffer circular 128 pixels
//#define fCLK 9600 // frequencia do ADC
//#define SERIAL_TX_BUFFER_SIZE 128

/* armazenamento dos dados, ToDo: tratamento dos dados */
int amostras[SIZE];
volatile uint16_t amostraIndex;
//uint8_t cnt = 0;
bool ctr = false;
uint8_t cnt = 0;

/* bloco de interrupcoes ------------------------------------------- */
ISR(TIMER1_OVF_vect){ 
TCNT0 = 49; // reset timer0 
TCCR0B = 0x2; // calibra o prescale (ativa o timer0 -> CLK)
cnt++;
}

ISR(TIMER0_COMPA_vect) {
        amostras[amostraIndex] = analogRead(A0);
        amostraIndex++;
        //amostras[amostraIndex-1] = ADC;
        if (amostraIndex > 127) {
            TCCR0B = 0; // desabilida o timer0 (CLK)
            amostraIndex = 0;
        }

}

// ISR(ADC_vect){ 
//     amostras[amostraIndex] = ADC; 
//     amostraIndex++; 
//     if (amostraIndex > 127) {  
//         TCCR0B = 0; // desabilida o timer0 (CLK) 
//         amostraIndex = 0; 
//     } 
// } 

void setup(){ 
    amostraIndex = 0;
    TCCR0B = 0; // desativa o timer0
    pinMode(9, OUTPUT); 
    pinMode(5, OUTPUT); 

    cfgADC(); 
    cfgTimerCLK(); 
    cfgTimerSI(30);

} 

void loop(){
        // if (amostraIndex > 127) {
        //     TCCR0B = 0; // desabilida o timer0 (CLK)
        //     TCCR1B = 0;
        //     //ready = true;
        //     amostraIndex = 0;
        //     Serial.begin(115200);
        //     for (int i=0;i<128;i++) {
        //         // if (i % 128 == 0) {
        //         //     Serial.println("----------------");
        //         // }
        //         Serial.print(i);
        //         Serial.print(" --> ");
        //         Serial.println(amostras[i]);
        //     }
        // }
    //cnt++;
    // if (ready) {
    //     Serial.begin(115200);
    //     for (int i=0;i<640;i++) {
    //         if (i % 128 == 0) {
    //             Serial.println("----------------");
    //         }
    //         Serial.print(i);
    //         Serial.print(" --> ");
    //         Serial.println(amostras[i]);
    //     }
    //     ready = false;
        
    // }
    if (cnt > 80) {
        TCCR0B = 0;
        TCCR1B = 0;
        TCCR0A = 0;
        TCCR1A = 0;
        
        Serial.begin(115200);
        for (int i=0;i<128;i++) {
            // if (i % 128 == 0) {
            //     Serial.println("----------------");
            // }
            Serial.print(i);
            Serial.print(",");
            Serial.println(amostras[i]);
        }
        Serial.end();
        cnt = 0;
        amostraIndex = 0;
        cfgTimerCLK(); 
        cfgTimerSI(30);
    }
} 
