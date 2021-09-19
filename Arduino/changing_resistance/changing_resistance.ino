#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  90 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  485 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// our servo # counter
uint8_t servonum = 0;
float sensorValue;
void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");
  pinMode(A0, INPUT);

  pwm.begin();
  /*
   * In theory the internal oscillator (clock) is 25MHz but it really isn't
   * that precise. You can 'calibrate' this by tweaking this number until
   * you get the PWM update frequency you're expecting!
   * The int.osc. for the PCA9690 chip is a range between about 23-27MHz and
   * is used for calculating things like writeMicroseconds()
   * Analog servos run at ~50 Hz updates, It is importaint to use an
   * oscilloscope in setting the int.osc frequency for the I2C PCA9690 chip.
   * 1) Attach the oscilloscope to one of the PWM signal pins and ground on
   *    the I2C PCA9690 chip you are setting the value for.
   * 2) Adjust setOscillatorFrequency() until the PWM update frequency is the
   *    expected value (50Hz for most ESCs)
   * Setting the value here is specific to each individual I2C PCA9690 chip and
   * affects the calculations for the PWM update frequency. 
   * Failure to correctly set the int.osc value will cause unexpected PWM results
   */
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
}

// You can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. It's not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= SERVO_FREQ;   // Analog servos run at ~60 Hz updates
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert input seconds to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}
void High(){
    //왼쪽 앞 다리
  pwm.setPWM(0, 0, 287);
  pwm.setPWM(1, 0, 300);
  pwm.setPWM(2, 0, 287);

  //오른쪽 앞 다리
  pwm.setPWM(4, 0, 287);
  pwm.setPWM(5, 0, 300);
  pwm.setPWM(6, 0, 287);

  //왼쪽 뒷 다리
  pwm.setPWM(8, 0, 289);
  pwm.setPWM(9, 0, 300);
  pwm.setPWM(10, 0, 287);

  //오른쪽 뒷다리
  pwm.setPWM(12, 0, 287);
  pwm.setPWM(13, 0, 300);
  pwm.setPWM(14, 0, 287);
}

void Low(){
    //왼쪽 앞 다리
  pwm.setPWM(0, 0, 287);
  pwm.setPWM(1, 0, 485);
  pwm.setPWM(2, 0, 485);

  //오른쪽 앞 다리
  pwm.setPWM(4, 0, 290);
  pwm.setPWM(5, 0, 107);
  pwm.setPWM(6, 0, 90);

  //왼쪽 뒷 다리
  pwm.setPWM(8, 0, 289);
  pwm.setPWM(9, 0, 485);
  pwm.setPWM(10, 0, 485);

  //오른쪽 뒷다리
  pwm.setPWM(12, 0, 287);
  pwm.setPWM(13, 0, 110);
  pwm.setPWM(14, 0, 90);
}

void Leg(float *ptr){
    //왼쪽 앞 다리
  pwm.setPWM(0, 0, 287);
  pwm.setPWM(1, 0, int(-0.181*(*ptr)+485));
  pwm.setPWM(2, 0, int(-0.194*(*ptr)+485));

  //오른쪽 앞 다리
  pwm.setPWM(4, 0, 290);
  pwm.setPWM(5, 0, int(0.189*(*ptr)+107));
  pwm.setPWM(6, 0, int(0.193*(*ptr)+90));

  //왼쪽 뒷 다리
  pwm.setPWM(8, 0, 289);
  pwm.setPWM(9, 0, int(-0.181*(*ptr)+485));
  pwm.setPWM(10, 0, int(-0.194*(*ptr)+485));

  //오른쪽 뒷다리
  pwm.setPWM(12, 0, 287);
  pwm.setPWM(13, 0, int(0.186*(*ptr)+110));
  pwm.setPWM(14, 0, int(0.193*(*ptr)+90));
}

void loop() {
   float sensorValue = analogRead(A0);
  float percentage=sensorValue/1023*100;

Serial.print("sensorValue = ");
  Serial.print(sensorValue);
  Serial.print(" percentage = ");
  Serial.println(percentage);
  
//High(); delay(1000);
//Low(); delay(1000);
Leg( &sensorValue);
if(Serial.available()>0){
char c=Serial.read();
if(c=='h'){High(); delay(1000);}
else if(c=='l'){Low(); delay(1000);}
else c=0;}
}
