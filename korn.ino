#include <Conceptinetics.h>
#include <AccelStepper.h>

const uint8_t stepPulse = 10;
const uint8_t stepDir = 8;
const uint8_t stepEnable = 7;

AccelStepper stepper(1, stepPulse, stepDir);

long MAXSPEED = 3000;
long MAXACC = 1250;

#define DMX_SLAVE_CHANNELS   4

DMX_Slave dmx_slave ( DMX_SLAVE_CHANNELS );

const int ledPin = 13;

void setup() {
  delay(1000);

  pinMode(34, OUTPUT);
  pinMode(27, INPUT_PULLUP);


  dmx_slave.enable ();

  dmx_slave.setStartAddress (2);

  // Set led pin as output pin
  pinMode ( ledPin, OUTPUT );
  //Serial.begin(500000);

  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);

  if (!digitalRead(27)) {
    MAXSPEED = MAXSPEED * 4;
    MAXACC = MAXACC * 4;
  }
  

  stepper.setMaxSpeed(MAXSPEED);
  stepper.setAcceleration(MAXACC);
  stepper.setCurrentPosition(0);

}

int dmxMove;
int dmxBounce = 0;
int dmxConstOrario;
int dmxConstAnti;
bool once = false;

void loop()
{

  dmxMove = dmx_slave.getChannelValue(1);
  //dmxBounce = dmx_slave.getChannelValue(4);
  dmxConstOrario = dmx_slave.getChannelValue(2);
  dmxConstAnti = dmx_slave.getChannelValue(3);

  if (dmxMove > 10) {
    stepper.moveTo(map(dmxMove, 0, 255, 0, 800));

    if (dmxBounce > 10) {
      stepper.setCurrentPosition(0);
      stepper.moveTo(80);

      while (dmxBounce > 10) {
        dmxBounce = dmx_slave.getChannelValue(2);
        stepper.setMaxSpeed(map(dmxBounce, 0, 255, 0, 6000));
        stepper.setAcceleration(map(dmxBounce, 0, 255, 0, 5000));
        if (stepper.distanceToGo() == 0) {
          stepper.moveTo(-stepper.currentPosition());
        }
        digitalWrite(stepEnable, LOW);
        stepper.run();
      }
      stepper.setMaxSpeed(MAXSPEED);
      stepper.setAcceleration(MAXACC);
    }
    digitalWrite(stepEnable, LOW);
    stepper.run();
  }
  else if (dmxConstOrario > 10) {
    stepper.move(map(dmxConstOrario, 0, 255, 0, 400));
    digitalWrite(stepEnable, LOW);
    stepper.run();
  }
  else if (dmxConstAnti > 10) {
    stepper.move(map(dmxConstAnti, 0, 255, 0, -400));
    digitalWrite(stepEnable, LOW);
    stepper.run();
  }
  else {
    stepper.setCurrentPosition(0);
    digitalWrite(stepEnable, HIGH);
  }
  

  

}
