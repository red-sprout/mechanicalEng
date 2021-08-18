/*
  Motor : XL320

  DEVICENAME "1" -> Serial1
  DEVICENAME "2" -> Serial2
  DEVICENAME "3" -> Serial3
*/

#include <DynamixelSDK.h>


#define BOARD_BUTTON_PIN                16


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
#define DXL_MAXIMUM_CURRENT_VALUE       1
#define DXL_MOVING_STATUS_THRESHOLD     20                  // Dynamixel moving status threshold

#define ESC_ASCII_VALUE                 0x1b

void setup() {
  int DXL_ID;
  int BAUD[4] = {9600,115200,1000000,2000000};
  int BAUDRATE;

  pinMode(BOARD_BUTTON_PIN, INPUT_PULLDOWN);

  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);


  Serial.println("Start..");


  // Initialize PortHandler instance
  // Set the port path
  // Get methods and members of PortHandlerLinux or PortHandlerWindows
  dynamixel::PortHandler *portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);

  // Initialize PacketHandler instance
  // Set the protocol version
  // Get methods and members of Protocol1PacketHandler or Protocol2PacketHandler
  dynamixel::PacketHandler *packetHandler1 = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
  
  int index = 0;
  int dxl_comm_result1 = COMM_TX_FAIL;             // Communication result
  int dxl_comm_result2 = COMM_TX_FAIL;             // Communication result
  int dxl_goal_position[2] = {DXL_MINIMUM_POSITION_VALUE, DXL_MAXIMUM_POSITION_VALUE};         // Goal position
  int dxl_goal_current = DXL_MAXIMUM_CURRENT_VALUE;

  uint8_t dxl_error = 0;                          // Dynamixel error
  int16_t dxl_present_position = 0;               // Present position

  // Open port
  if (portHandler->openPort())
  {
    Serial.print("Succeeded to open the port!\n");
  }
  else
  {
    Serial.print("Failed to open the port!\n");
    Serial.print("Press any key to terminate...\n");
    return;
  }

  // Set port baudrate
//  if (portHandler->setBaudRate(BAUDRATE))
//  {
//    Serial.print("Succeeded to change the baudrate!\n");
//  }
//  else
//  {
//    Serial.print("Failed to change the baudrate!\n");
//    Serial.print("Press any key to terminate...\n");
//    return;
//  }

  // find ID, Baudrate
  BAUDRATE = BAUD[3];
  if (portHandler->setBaudRate(BAUDRATE))
  {
    Serial.print("Succeeded to change the baudrate!\n");
  }
  else
  {
    Serial.print("Failed to change the baudrate!\n");
    Serial.print("Press any key to terminate...\n");
  }

  for(int id = 0;id<255;id++){
    dxl_comm_result1 = packetHandler1->write1ByteTxRx(portHandler, id, ADDR_PRO_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
    if (dxl_comm_result1 != COMM_SUCCESS){
      Serial.print("Error Id is");
      Serial.println(id);
      
    }else{
      DXL_ID = id;
      break;
      
      }
  }

// Enable Dynamixel Torque
  dxl_comm_result1 = packetHandler1->write1ByteTxRx(portHandler, DXL_ID, ADDR_PRO_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
  if (dxl_comm_result1 != COMM_SUCCESS)
  {
    packetHandler1->getTxRxResult(dxl_comm_result1);
  }
  else if (dxl_error != 0)
  {
    packetHandler1->getRxPacketError(dxl_error);
  }
  else
  {
    Serial.print("Dynamixel has been successfully connected \n");
  }
 
  Serial.print("DXL_ID is ");
  Serial.println(DXL_ID);
  
  Serial.print("BAUDRATE is ");
  Serial.println(BAUDRATE);
 

// Change mode
  dxl_comm_result1 = packetHandler1->write1ByteTxRx(portHandler, DXL_ID, 11, 5, &dxl_error);
  if (dxl_comm_result1 != COMM_SUCCESS)
  {
    packetHandler1->getTxRxResult(dxl_comm_result1);
  }
  else if (dxl_error != 0)
  {
    packetHandler1->getRxPacketError(dxl_error);
  }
  else
  {
    Serial.print("Change Modde \n");
  }

 // Change Position P gain
  dxl_comm_result1 = packetHandler1->write2ByteTxRx(portHandler, DXL_ID, 84, 8000, &dxl_error);
  if (dxl_comm_result1 != COMM_SUCCESS)
  {
    packetHandler1->getTxRxResult(dxl_comm_result1);
  }
  else if (dxl_error != 0)
  {
    packetHandler1->getRxPacketError(dxl_error);
  }
  else
  {
    Serial.print("Change P gain \n");
  }
  
  // Change Goal Current
  dxl_comm_result1 = packetHandler1->write2ByteTxRx(portHandler, DXL_ID, ADDR_PRO_GOAL_CURRENT, DXL_MAXIMUM_CURRENT_VALUE, &dxl_error);
  if (dxl_comm_result1 != COMM_SUCCESS)
  {
    packetHandler1->getTxRxResult(dxl_comm_result1);
  }
  else if (dxl_error != 0)
  {
    packetHandler1->getRxPacketError(dxl_error);
  }
  else
  {
    Serial.print("Change Goal Current \n");
  }
  
  while(1)
  {
    Serial.print("Press any key to continue! (or press q to quit!)\n");


    while(Serial.available()==0);

    int ch;

    ch = Serial.read();
    if (ch == 'q')
      break;

    // Write goal position
//    dxl_comm_result1 = packetHandler1->write2ByteTxRx(portHandler, DXL_ID, ADDR_PRO_GOAL_CURRENT, 1, &dxl_error);
//    if (dxl_comm_result1 != COMM_SUCCESS)
//    {
//      packetHandler1->getTxRxResult(dxl_comm_result1);
//    }
//    else if (dxl_error != 0)
//    {
//      packetHandler1->getRxPacketError(dxl_error);
//    }
//    dxl_comm_result1 = packetHandler1->write4ByteTxRx(portHandler, DXL_ID, ADDR_PRO_GOAL_POSITION, dxl_goal_position[index], &dxl_error);
//    if (dxl_comm_result1 != COMM_SUCCESS)
//    {
//      packetHandler1->getTxRxResult(dxl_comm_result1);
//    }
//    else if (dxl_error != 0)
//    {
//      packetHandler1->getRxPacketError(dxl_error);
//    }

//    do
//    {
//      // Read present position
//      dxl_comm_result1 = packetHandler1->read2ByteTxRx(portHandler, DXL_ID, ADDR_PRO_PRESENT_POSITION, (uint16_t*)&dxl_present_position, &dxl_error);
//      if (dxl_comm_result1 != COMM_SUCCESS)
//      {
//        packetHandler1->getTxRxResult(dxl_comm_result1);
//      }
//      else if (dxl_error != 0)
//      {
//        packetHandler1->getRxPacketError(dxl_error);
//      }
//
//      Serial.print("[ID:");      Serial.print(DXL_ID);
//      Serial.print(" GoalPos:"); Serial.print(dxl_goal_position[index]);
//      Serial.print(" PresPos:");  Serial.print(dxl_present_position);
//      Serial.println(" ");
//
//
//    }while((abs(dxl_goal_position[index] - dxl_present_position) > DXL_MOVING_STATUS_THRESHOLD));

    // Change goal position
    if (index == 0)
    {
      index = 1;
    }
    else
    {
      index = 0;
    }
  }

  // Disable Dynamixel Torque
  dxl_comm_result1 = packetHandler1->write1ByteTxRx(portHandler, DXL_ID, ADDR_PRO_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
  if (dxl_comm_result1 != COMM_SUCCESS)
  {
    packetHandler1->getTxRxResult(dxl_comm_result1);
  }
  else if (dxl_error != 0)
  {
    packetHandler1->getRxPacketError(dxl_error);
  }

  // Close port
  portHandler->closePort();
}


void loop() {
  // put your main code here, to run repeatedly:

}
