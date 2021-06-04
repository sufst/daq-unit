# DAQ Unit


## Rear Arduino 
Performs DAQ for rear of the car, reads ECU and front MKR data over CAN and transmits the data over Zigbee
#### DAQ
    * 2 damper pots, accelerometer, 2 wheel speeds, fuel flow and ride height
#### XBEE Packet Byte Structure:
    * Core: | Start[1] | Command[1] | Bitfield[2] | RPM[2] | Water Temp[2] | TPS[2] | Battery[2] | External5V[2] | Fuel Flow[4] | lambda[2] | Speed[2] |
    * Power: | Start[1] | Command[1] | Bitfield[2] | Injection Time[2] | Lambda PID Adjustment[2] | Lambda PID[2] | Advance[2] |
    * Suspension: | Start[1] | Command[1] | Bitfield[2] | Ride Height Front[4] | Ride Height Rear[4] |
    * Misc: | Start[1] | Command[1] | Bitfield[2] | Accel X Front[4] | Accel Y Front[4] | Accel Z Front[4] | Accel X Rear[4] | Accel Y Rear[4] | Accel Z Rear[4] | Damper Left Front[4] | Damper Right Front[4] | Damper Left Rear[4] | Damper Right Rear[4] | Wheel Speed Left Front[4] | Wheel Speed Right Front[4] | Wheel Speed Left Rear[4] | Wheel Speed Right Rear[4] |
    
## Front Arduino 
Performs DAQ for front of the car and transmits MKR data over CAN
#### DAQ
    * 2 damper pots, accelerometer and 2 wheel speeds 
#### CAN Packet Structure:
    || Accel X | Accel Y || Accel Z || Damper Pot Left[4] | Damper Pot Right[4] || Wheel Speed Left[4] | Wheel Speed Right[4] || Ride Height[4] |

## Arduino MCP2515 CAN Interface Library Installation 
    1. Download the ZIP file from https://github.com/coryjfowler/MCP_CAN_lib
    2. From the Arduino IDE: Sketch -> Include Library... -> Add .ZIP Library...
    
## TODO
   * Configure SD Card
   * XBEE: Aero and Diagnositic Packets 
