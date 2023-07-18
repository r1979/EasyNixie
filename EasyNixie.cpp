#include "EasyNixie.h"

EasyNixie::EasyNixie(uint8_t outputEnable,uint8_t shcp, uint8_t stcp, uint8_t dsin):
        outputEnable(outputEnable),
        shcp(shcp),
        stcp(stcp),
        dsin(dsin)
{
    pinMode(outputEnable, OUTPUT);  
    pinMode(shcp, OUTPUT);
    pinMode(stcp, OUTPUT);
    pinMode(dsin, OUTPUT);
}

void EasyNixie::shiftNumber(uint8_t number,uint8_t color,bool voltage){
    uint8_t secondShiftRegisterData=0b00011100;
    if(number==8)secondShiftRegisterData|=0b00000001;
    if(number==9)secondShiftRegisterData|=0b00000010;
    if(color==EASY_NIXIE_BLUE)secondShiftRegisterData&=0b11111011;
    if(color==EASY_NIXIE_GREEN)secondShiftRegisterData&=0b11110111;
    if(color==EASY_NIXIE_RED)secondShiftRegisterData&=0b11101111;
    if(color==EASY_NIXIE_WHITE)secondShiftRegisterData&=0b11100011;
    if(voltage)secondShiftRegisterData|=0b00100000;
    shiftOut(dsin, shcp, MSBFIRST, secondShiftRegisterData);
    if(number<8)shiftOut(dsin, shcp, MSBFIRST, (uint8_t)(1<<number));
    else shiftOut(dsin, shcp, MSBFIRST, 0);
}


void EasyNixie::latch(void){
    digitalWrite(stcp, LOW);
    delay(1);
    digitalWrite(stcp, HIGH);
}


