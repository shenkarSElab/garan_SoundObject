
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

const char singleplay[]={0x24, 0x07, 0x06, 0x01, 0x31, 0x2E, 0x6D, 0x70, 0x33, 0x31};
const char stopy[]={0x24, 0x02, 0x07, 0x00 ,0x05};
unsigned char commandBuff[13];

void setup() 
{
    Serial.begin(9600);
    Serial.println("restart");

    
    mySerial.begin(9600);
    commandBuff[2] = 1;

    singleLoopPlay(1);  delay(10000);
 /*
 for(int iii=15; iii>=0; iii--){
    setVolume(iii);
    delay(500);
 }
*/

}
void loop(){
    setVolume(random(15));
    delay(500);
}


void sendCommand(uint8_t command[])  {
    uint8_t checksum = 0;

    mySerial.write(0x24);
    for (uint16_t i = 0; i <= command[0]; i++) {
        mySerial.write(command[i]);
        checksum ^= command[i];
    }

    mySerial.write(checksum);
}

void buildHead(uint8_t len, uint8_t cmd)  {
    commandBuff[0] = len;
    commandBuff[1] = cmd;
}

void singleLoopPlay(uint16_t number)  {
    buildHead(0x04, 0x02);
    commandBuff[3] = (uint8_t)(number >> 8);
    commandBuff[4] = (uint8_t)number;

    sendCommand(commandBuff);
}

void stop()  {
    mySerial.write(stopy,sizeof(stopy));
    //sendCommand((uint8_t *)STOP);
}

void setVolume(uint8_t volume)  {
    buildHead(0x03, 0x0D);
    commandBuff[3] = volume;

    sendCommand(commandBuff);
}

