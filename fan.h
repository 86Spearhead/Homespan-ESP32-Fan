struct ESP32Fan : Service::Fan {

  const int freq = 30000;
  const int resolution = 8;
  int dutyCycle = 255;

  int pinA;
  int pinB;
  SpanCharacteristic *power;
  SpanCharacteristic *speed;
  SpanCharacteristic *direction;

  ESP32Fan(int pinA, int pinB) : Service::Fan(){

    power=new Characteristic::Active();
    speed=new Characteristic::RotationSpeed();
    speed->setRange(0, 100, 25);
    direction=new Characteristic::RotationDirection(); 

    this->pinA=pinA;
    this->pinB=pinB;

    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    ledcAttach(pinA, freq, resolution);
    ledcAttach(pinB, freq, resolution);
  }

  boolean update(){

    if (power->getNewVal() == 1) {
      if (speed->getNewVal() == 25) {
        dutyCycle = 220;
      } else if (speed->getNewVal() == 50) {
        dutyCycle = 230;
      } else if (speed->getNewVal() == 75) {
        dutyCycle = 240;
      } else if (speed->getNewVal() == 100) {
        dutyCycle = 255;
      } else {
        dutyCycle = 0;
      }
    } else {
      dutyCycle = 0;
    }

    if (direction->getNewVal() == 0){
      ledcWrite(pinA, 0);
      ledcWrite(pinB, dutyCycle);
    } else if (direction->getNewVal() == 1){
      ledcWrite(pinA, dutyCycle);
      ledcWrite(pinB, 0);
    }

    return(true);

  }

};
