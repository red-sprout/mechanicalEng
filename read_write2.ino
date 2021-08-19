/*
  Motor : XL320

  DEVICENAME "1" -> Serial1
  DEVICENAME "2" -> Serial2
  DEVICENAME "3" -> Serial3
*/

#include <DynamixelSDK.h>
#define _TASK_SLEEP_ON_IDLE_RUN
#define _TASK_PRIORITY
#define _TASK_WDT_IDS
#define _TASK_TIMECRITICAL
#include <TaskScheduler.h>

Scheduler Print_Priority;
Scheduler Control_Priority;


#define BOARD_BUTTON_PIN                16
#define BOARD_BUTTON_PIN2               17

// Control table address (XL320)
#define ADDR_PRO_TORQUE_ENABLE          64                 // Control table address is different in Dynamixel model
#define ADDR_PRO_GOAL_POSITION          116
#define ADDR_PRO_GOAL_CURRENT           102
#define ADDR_PRO_PRESENT_POSITION       132

// Protocol version
#define PROTOCOL_VERSION                2.0                 // See which protocol version is used in the Dynamixel

// Default setting
//#define DXL_ID                          1                   // Dynamixel ID: 1
//#define BAUDRATE                        2000000
#define DEVICENAME                      "3"                 // Check which port is being used on your controller
                                                            // ex) Windows: "COM1"   Linux: "/dev/ttyUSB0"

#define TORQUE_ENABLE                   1                   // Value for enabling the torque
#define TORQUE_DISABLE                  0                   // Value for disabling the torque
#define DXL_MINIMUM_POSITION_VALUE      0                 // Dynamixel will rotate between this value
#define DXL_MAXIMUM_POSITION_VALUE      4095                 // and this value (note that the Dynamixel would not move when the position value is out of movable range. Check e-manual about the range of the Dynamixel you use.)
#define DXL_MOVING_STATUS_THRESHOLD     20                  // Dynamixel moving status threshold

#define ESC_ASCII_VALUE                 0x1b
volatile int state = LOW;
int DXL_MAXIMUM_CURRENT_VALUE = 1;
int btn_value=0;
void btn_IQR(){btn_value+=(digitalRead(BOARD_BUTTON_PIN)==HIGH)?10:-10;  }

Task Control_Task(10, TASK_FOREVER, &fControl, &Control_Priority);
Task Print_Task(100, TASK_FOREVER, &fPrint, &Print_Priority);

void fControl(){
    
}

int incomingByte=0;// for incoming serial data
void fPrint(){
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.parseInt();
    Serial.println(incomingByte);
  }
}

void setup(){

  pinMode(BOARD_BUTTON_PIN, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(BOARD_BUTTON_PIN),btn_IQR,RISING);
  pinMode(BOARD_BUTTON_PIN2, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(BOARD_BUTTON_PIN2),btn_IQR,RISING);
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  Control_Task.setId(10);
  Print_Task.setId(20);
  Print_Priority.setHighPriorityScheduler(&Control_Priority);
  Print_Priority.enableAll(true);
}


void loop() {
  Print_Priority.execute();
}
