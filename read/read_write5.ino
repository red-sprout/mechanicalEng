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
#define DEVICENAME                      "3"                 // Check which port is being used on your controller
                                                            // ex) Windows: "COM1"   Linux: "/dev/ttyUSB0"

#define TORQUE_ENABLE                   1                   // Value for enabling the torque
#define TORQUE_DISABLE                  0                   // Value for disabling the torque
#define DXL_MINIMUM_POSITION_VALUE      0                 // Dynamixel will rotate between this value
#define DXL_MAXIMUM_POSITION_VALUE      4095                 // and this value (note that the Dynamixel would not move when the position value is out of movable range. Check e-manual about the range of the Dynamixel you use.)
#define DXL_MAXIMUM_CURRENT_VALUE       2047
#define DXL_MOVING_STATUS_THRESHOLD     20                  // Dynamixel moving status threshold

#define ESC_ASCII_VALUE                 0x1b

// Initialize PortHandler instance
// Set the port path
// Get methods and members of PortHandlerLinux or PortHandlerWindows
dynamixel::PortHandler *portHandler;

// Initialize PacketHandler instance
// Set the protocol version
// Get methods and members of Protocol1PacketHandler or Protocol2PacketHandler
dynamixel::PacketHandler *packetHandler;

uint8_t dxl_error = 0;                          // Dynamixel error
int16_t dxl_present_position = 0;               // Present position

int DXL_ID=1;

int dxl_comm_result = COMM_TX_FAIL;             // Communication result
int dxl_goal_position[2] = {DXL_MINIMUM_POSITION_VALUE, DXL_MAXIMUM_POSITION_VALUE};         // Goal position
int dxl_goal_current = DXL_MAXIMUM_CURRENT_VALUE;
int target_position = 0;
int i = 0;

bool new_value_check;
void btn_IQR(){target_position+=(digitalRead(BOARD_BUTTON_PIN)==HIGH)?20:-20;  
  if(target_position<0)target_position=0;
  
  new_value_check = true;
}

Task Control_Task(1000, TASK_FOREVER, &fControl, &Control_Priority);
Task Print_Task(100, TASK_FOREVER, &fPrint, &Print_Priority);
int toggle = -1;
void fControl(){
  
}

int incomingByte=0;// for incoming serial data
void fPrint(){
  Serial.print("position : ");
  Serial.print(target_position);
  Serial.print("toggle : ");
  Serial.print(toggle);
  Serial.println("\n");
  

}

void setup(){
  int BAUD[4] = {9600,115200,1000000,2000000};
  int BAUDRATE;
  
  pinMode(BOARD_BUTTON_PIN, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(BOARD_BUTTON_PIN),btn_IQR,RISING);
  pinMode(BOARD_BUTTON_PIN2, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(BOARD_BUTTON_PIN2),btn_IQR,RISING);
  // put your setup code here, to run once:
  Serial.begin(115200);

  // put your setup code here, to run once:
  while(!Serial);
  Serial.println("Start..");
  portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
  packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);

  // Open port
  if (portHandler->openPort()){
    Serial.print("Succeeded to open the port!\n");
  }
  else{
    Serial.print("Failed to open the port!\n");
    Serial.print("Press any key to terminate...\n");
    return;
  }
  
  // find ID, baudrate
  BAUDRATE = BAUD[3];
  if (portHandler->setBaudRate(BAUDRATE)){
    Serial.print("Succeeded to change the baudrate!\n");
  }
  else{
    Serial.print("Failed to change the baudrate!\n");
    Serial.print("Press any key to terminate...\n");
  }

   
  Serial.print("DXL_ID is ");
  Serial.println(DXL_ID);
  
  Serial.print("BAUDRATE is ");
  Serial.println(BAUDRATE);
    // Disable Dynamixel Torque
  Serial.println("SEND  TORQUE");


  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_ID, ADDR_PRO_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
  Serial.println("SEND  TORQUE2");
  if (dxl_comm_result != COMM_SUCCESS)
  {
    packetHandler->getTxRxResult(dxl_comm_result);
  }
  else if (dxl_error != 0)
  {
    packetHandler->getRxPacketError(dxl_error);
  }

  
  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_ID, 11, 5, &dxl_error);
  if (dxl_comm_result != COMM_SUCCESS)
  {
    packetHandler->getTxRxResult(dxl_comm_result);
  }
  else if (dxl_error != 0)
  {
    packetHandler->getRxPacketError(dxl_error);
  }




 // Change Position P gain
  dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, DXL_ID, 84, 6000, &dxl_error);
  if (dxl_comm_result != COMM_SUCCESS)
  {
    packetHandler->getTxRxResult(dxl_comm_result);
  }
  else if (dxl_error != 0)
  {
    packetHandler->getRxPacketError(dxl_error);
  }
  else
  {
    Serial.print("Change P gain \n");
  }
  

    dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, DXL_ID, ADDR_PRO_GOAL_CURRENT, 500, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
    {
      packetHandler->getTxRxResult(dxl_comm_result);
    }
    else if (dxl_error != 0)
    {
      packetHandler->getRxPacketError(dxl_error);
    }
  


  

  // Close port
  Control_Task.setId(10);
  Print_Task.setId(20);
  Print_Priority.setHighPriorityScheduler(&Control_Priority);
  Print_Priority.enableAll(true);

}


void loop() {
  Print_Priority.execute();



    if(new_value_check){

  
      dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID, ADDR_PRO_GOAL_POSITION, target_position, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
    {
      packetHandler->getTxRxResult(dxl_comm_result);
    }
    else if (dxl_error != 0)
    {
      packetHandler->getRxPacketError(dxl_error);
    }
       do
    {
      // Read present position
      dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, DXL_ID, ADDR_PRO_PRESENT_POSITION, (uint16_t*)&dxl_present_position, &dxl_error);
      Serial.print(target_position);
      Serial.print(", present :  ");
      Serial.println(dxl_present_position);
      if (dxl_comm_result != COMM_SUCCESS)
      {
        packetHandler->getTxRxResult(dxl_comm_result);
      }
      else if (dxl_error != 0)
      {
        packetHandler->getRxPacketError(dxl_error);
      }

    }while((abs(target_position - dxl_present_position) > DXL_MOVING_STATUS_THRESHOLD));

  }
  new_value_check=false;
    

}
  
//  while(1)
//  {
//    Serial.print("Press any key to continue! (or press q to quit!)\n");
//
//
//    while(Serial.available()==0);
//
//    int ch;
//
//    ch = Serial.read();
//    if (ch == 'q')
//      break;

    // Write goal position
//    dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, DXL_ID, ADDR_PRO_GOAL_CURRENT, 1, &dxl_error);
//    if (dxl_comm_result != COMM_SUCCESS)
//    {
//      packetHandler->getTxRxResult(dxl_comm_result);
//    }
//    else if (dxl_error != 0)
//    {
//      packetHandler->getRxPacketError(dxl_error);
//    }
//    dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID, ADDR_PRO_GOAL_POSITION, dxl_goal_position[i], &dxl_error);
//    if (dxl_comm_result != COMM_SUCCESS)
//    {
//      packetHandler->getTxRxResult(dxl_comm_result);
//    }
//    else if (dxl_error != 0)
//    {
//      packetHandler->getRxPacketError(dxl_error);
//    }

//    do
//    {
//      // Read present position
//      dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, DXL_ID, ADDR_PRO_PRESENT_POSITION, (uint16_t*)&dxl_present_position, &dxl_error);
//      if (dxl_comm_result != COMM_SUCCESS)
//      {
//        packetHandler->getTxRxResult(dxl_comm_result);
//      }
//      else if (dxl_error != 0)
//      {
//        packetHandler->getRxPacketError(dxl_error);
//      }
//
//      Serial.print("[ID:");      Serial.print(DXL_ID);
//      Serial.print(" GoalPos:"); Serial.print(dxl_goal_position[i]);
//      Serial.print(" PresPos:");  Serial.print(dxl_present_position);
//      Serial.println(" ");
//
//
//    }while((abs(dxl_goal_position[i] - dxl_present_position) > DXL_MOVING_STATUS_THRESHOLD));

//    // Change goal position
//    if (i == 0)
//    {
//      i = 1;
//    }
//    else
//    {
//      i = 0;
//    }
//  }
//
//  // Disable Dynamixel Torque
//  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_ID, ADDR_PRO_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
//  if (dxl_comm_result != COMM_SUCCESS)
//  {
//    packetHandler->getTxRxResult(dxl_comm_result);
//  }
//  else if (dxl_error != 0)
//  {
//    packetHandler->getRxPacketError(dxl_error);
//  }
//
//  // Close port
//  portHandler->closePort();
