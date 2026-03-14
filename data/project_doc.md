# **Circuit Documentation**

## **Summary of the Circuit**

This circuit is built around a XIAO ESP32C3 microcontroller and includes various components such as resistors, capacitors, LEDs, a servo motor, a pushbutton, and a power module. The circuit is designed to control a servo motor and LEDs based on input from a pushbutton, with power supplied by an HLK-5M05 module. The microcontroller interfaces with the components to perform the desired operations.

## **Component List**

1. **XIAO ESP32C3**  
   * **Description**: A compact microcontroller with Wi-Fi and Bluetooth capabilities.  
   * **Pins**: GPIO2/A0/D0, GPIO3/A1/D1, GPIO4/A2/D2, GPIO5/A3/D3, GPIO6/SDA/D4, GPIO7/SCL/D5, GPIO21/Tx/D6, 5V, GND, 3V3, GPIO10/MOSI/D10, GPIO9/MISO/D9, GPIO8/SCK/D8, GPIO20/Rx/D7  
2. **Electrolytic Capacitor**  
   * **Description**: A capacitor used for smoothing voltage.  
   * **Capacitance**: 0.001 Farads  
   * **Pins**: \-, \+  
3. **Ceramic Capacitor**  
   * **Description**: A capacitor used for filtering high-frequency noise.  
   * **Capacitance**: 0.0000001 Farads  
   * **Pins**: pin0, pin1  
4. **Resistor (100 Ohms)**  
   * **Description**: A resistor used to limit current.  
   * **Resistance**: 100 Ohms  
   * **Pins**: pin1, pin2  
5. **Resistor (1000 Ohms)**  
   * **Description**: A resistor used to limit current.  
   * **Resistance**: 1000 Ohms  
   * **Pins**: pin1, pin2  
6. **SG90 Servo Motor**  
   * **Description**: A small servo motor for precise control of angular position.  
   * **Pins**: PWM, \+5V, GND  
7. **Pushbutton**  
   * **Description**: A button used to provide user input.  
   * **Pins**: Pin 3 (out), Pin 4 (out), Pin 1 (in), Pin 2 (in)  
8. **Red LED**  
   * **Description**: A light-emitting diode that emits red light.  
   * **Pins**: \+, \-  
9. **Green LED**  
   * **Description**: A light-emitting diode that emits green light.  
   * **Pins**: \+, \-  
10. **HLK-5M05**  
    * **Description**: A power module that provides a stable 5V output.  
    * **Pins**: pin 1, pin 2, \-Vo, \+Vo

## **Wiring Details**

### **XIAO ESP32C3**

* **GND** is connected to:  
  * Red LED (-)  
  * Green LED (-)  
  * Ceramic Capacitor (pin0)  
  * Electrolytic Capacitor (-)  
  * Pushbutton (Pin 4 (out))  
  * SG90 Servo Motor (GND)  
  * HLK-5M05 (-Vo)  
* **5V** is connected to:  
  * Ceramic Capacitor (pin1)  
  * Electrolytic Capacitor (+)  
  * SG90 Servo Motor (+5V)  
  * HLK-5M05 (+Vo)  
* **GPIO4/A2/D2** is connected to Resistor (100 Ohms) (pin2)  
* **GPIO3/A1/D1** is connected to Pushbutton (Pin 2 (in))  
* **GPIO5/A3/D3** is connected to Resistor (1000 Ohms) (pin2)  
* **GPIO6/SDA/D4** is connected to Resistor (1000 Ohms) (pin2)

### **Electrolytic Capacitor**

* **\-** is connected to GND  
* **\+** is connected to 5V

### **Ceramic Capacitor**

* **pin0** is connected to GND  
* **pin1** is connected to 5V

### **Resistor (100 Ohms)**

* **pin1** is connected to SG90 Servo Motor (PWM)  
* **pin2** is connected to XIAO ESP32C3 (GPIO4/A2/D2)

### **Resistor (1000 Ohms)**

* **pin1** is connected to Red LED (+)  
* **pin2** is connected to XIAO ESP32C3 (GPIO6/SDA/D4)

### **SG90 Servo Motor**

* **PWM** is connected to Resistor (100 Ohms) (pin1)  
* **\+5V** is connected to 5V  
* **GND** is connected to GND

### **Pushbutton**

* **Pin 2 (in)** is connected to XIAO ESP32C3 (GPIO3/A1/D1)  
* **Pin 4 (out)** is connected to GND

### **Red LED**

* **\+** is connected to Resistor (1000 Ohms) (pin1)  
* **\-** is connected to GND

### **Green LED**

* **\+** is connected to Resistor (1000 Ohms) (pin1)  
* **\-** is connected to GND

### **HLK-5M05**

* **\-Vo** is connected to GND  
* **\+Vo** is connected to 5V

## **Documented Code**

There is no code provided for this circuit. If code is developed for the microcontroller, it should be documented here with explanations of its functionality and how it interacts with the hardware components.