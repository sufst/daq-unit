# DAQ Unit


## Front Arduinos 
#### DAQ
    * Read damper pots, accelerometer, wheel speed sensor and ride height sensor
#### CAN Packet Structure:
    | Damper Pot[4] | AccelerometerX[4] | AccelerometerY[4] | AccelerometerZ[4] | Ride Height[4] | Wheel Speed[4] |
    
## Rear Arduino 
#### DAQ
    * Read fuel flow and ride height sensor
    * Left wheel
        * Read damper pots, wheel speed sensor and accelerometer
    * Right wheel
        * Read damper pots, wheel speed sensor and accelerometer 
#### CAN Packet Structure:
    | Damper Pot[4] | AccelerometerX_L[4] | AccelerometerY_L[4] | AccelerometerZ_L[4] | AccelerometerX_R[4] | AccelerometerY_R[4] | AccelerometerZ_R[4] | Ride Height[4] | Wheel Speed_L[4] | Wheel Speed_R[4] | Fuel Flow_R[4] |

## Arduino MCP2515 CAN Interface Library Installation 
    1. Download the ZIP file from https://github.com/autowp/arduino-mcp2515/archive/master.zip
    2. From the Arduino IDE: Sketch -> Include Library... -> Add .ZIP Library...