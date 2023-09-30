# Introduction 
Arduino Project to read and display Temperature data while parallelly generating 1sec clock without any delay.
You can take this as a great example to generate 1sec clock without use of delay function. This can be use full in many application where you want something to look parallell.

Dividing this project in 3 part
1. Display digits on 7-segment display using 74LS247N ic
2. Get Temperature reading from analog temprature sensor
3. Generate precise 1 sec clock

# 1. Display 3 digit of temperature on 7-segment
## To save pins on Arduino Uno I have use bellow method.
1. Take 3 "74LS247N ic"
2. Short each A, B, C, and D pins of all 3 ICs respectively.
3. In this example I have connect pins to arduino as define Ai = 8, Bi = 9, Ci = 10 and Di = 11. As we shorted each A, B, C, and D pings of all IC so we will need only 4 pins to represent all 3 ics.
4. I have taken common anode 7-segment display. Here, I have take VCC pins of each display as Digit1, Digit2 and Digit3 and connected it to arduino at ping 2, 3, and 4 accordingly. It's connected this way to switch display on and off on certain time interval.

# 2. Connect temperature Sensor

- Here temperature sensor is connected on A5 pine
- TemperaturePreset is a just a deferencial value to adjust temperature slightly

# 3. Generate 2 sec clock without delay

- You will get half sec trigger behavior on ping 12 and 13 of ardino.
- Here each 500miliseconds pin 12 and 13 will generate oposite behavior.
- This is precide despite having above all code as I have not use any delay in the code.