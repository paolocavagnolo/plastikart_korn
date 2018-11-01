#include <Conceptinetics.h>

#define DMX_SLAVE_CHANNELS   10

DMX_Slave dmx_slave ( DMX_SLAVE_CHANNELS );

const int ledPin = 13;

void setup() {    
  delay(1000);         
  
  dmx_slave.enable ();  
  
  dmx_slave.setStartAddress (5);
  
  // Set led pin as output pin
  pinMode ( ledPin, OUTPUT );
  //Serial.begin(500000);

}

int dmxValue;

void loop() 
{

  dmxValue = dmx_slave.getChannelValue(1);
  if (dmxValue > 127) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }

  
}
