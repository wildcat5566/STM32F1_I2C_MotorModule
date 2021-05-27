# STM32F1_I2C_MotorModule

Please refer to this repository for implementation details.
https://github.com/wildcat5566/Quadrature_Encoder_STM32F0

STM32F103C8T6 as slave transmitter, Arduino Due as master receiver.

## Project objective
Objective is to read from a quadrature encoder with an STM32F103 and to pass reading value to an Arduino Due via I2C. <br />
For quadrature encoder reading and logic please see this repo for details:<br /> 
https://github.com/wildcat5566/Quadrature_Encoder_STM32F0 <br />
The STM32F103(s) as slave transmitter(s) and the Arduino Due as the master receiver. <br />
<br />
![alt text](./src/abstract.jpg)

Since data is transmitted in 8-bit hexadecimal form, we follow the flow described in the diagram below.<br />
On slave side we convert decimals reading into hexadecimal, transmit it via I2C, and do the reversed conversion on master side.<br />
<br />
![alt text](./src/flow.jpg)

## Hardware setup
The master and slaves are connected on the I2C bus as shown in diagram below.<br />
As for the "external reset line", it's intended to reset all slaves every time we reset the master. <br />
This is implemented on master side, by pulling the voltage low on this external reset line and then releasing it.<br />
<br />
> void setup(){ <br />
> ...... <br />
> digitalWrite(22, LOW); <br />
> delay(10); <br />
> digitalWrite(22, HIGH); <br />
> } <br />
<br />

![alt text](./src/diagram.jpg)

## I2C Signals
Here are some oscilloscope screenshots and explanations of I2C signals during data transmission:
![alt text](./src/address.jpg)
![alt text](./src/data0.jpg)
![alt text](./src/data1.jpg)
![alt text](./src/data2.jpg)
