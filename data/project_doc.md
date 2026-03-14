# **Circuit Documentation**

## **Summary**

This circuit is a mixed-signal design incorporating both analog and digital components. It includes a microcontroller (Seeed Studio XIAO ESP32C3) for processing and control, a servo motor for mechanical movement, LEDs for visual indication, capacitors for filtering, resistors for current limiting, a pushbutton for user input, and a power module for voltage regulation. The circuit is designed to perform basic input/output operations, control a servo motor, and provide visual feedback through LEDs.

## **Component List**

1. **Electrolytic Capacitor**  
   * **Description**: A polarized capacitor used for filtering and energy storage.  
   * **Capacitance**: 0.001 Farads  
2. **Ceramic Capacitor**  
   * **Description**: A non-polarized capacitor used for high-frequency filtering.  
   * **Capacitance**: 0.0000001 Farads  
3. **Resistors**  
   * **Description**: Passive components used to limit current and divide voltages.  
   * **Values**:  
     * 100 Ohms  
     * 1000 Ohms (two instances)  
4. **SG90 Servo Motor**  
   * **Description**: A small servo motor used for precise control of angular position.  
5. **Pushbutton**  
   * **Description**: A momentary switch used for user input.  
6. **Red LED**  
   * **Description**: A light-emitting diode used for visual indication.  
7. **Green LED**  
   * **Description**: A light-emitting diode used for visual indication.  
8. **HLK-5M05 Power Module**  
   * **Description**: A power module used to convert AC to DC voltage.  
9. **Seeed Studio XIAO ESP32C3**  
   * **Description**: A microcontroller with WiFi and Bluetooth capabilities for processing and control.

## **Wiring Details**

### **Electrolytic Capacitor**

* **Positive (+) Pin**: Connected to the \+5V net, shared with the Ceramic Capacitor, Seeed Studio XIAO ESP32C3, SG90 Servo Motor, and HLK-5M05.  
* **Negative (-) Pin**: Connected to the GND net, shared with multiple components including the Red and Green LEDs, Ceramic Capacitor, Seeed Studio XIAO ESP32C3, Pushbutton, SG90 Servo Motor, and HLK-5M05.

### ---

**Ceramic Capacitor**

* **Pin 0**: Connected to the GND net.  
* **Pin 1**: Connected to the \+5V net.

### ---

**Resistor (100 Ohms)**

* **Pin 1**: Connected to the PWM pin of the SG90 Servo Motor.  
* **Pin 2**: Connected to GPIO4-A2-D2 of the Seeed Studio XIAO ESP32C3.

### ---

**Resistor (1000 Ohms)**

* **Instance 1**:  
  * **Pin 1**: Connected to the positive pin of the Green LED.  
  * **Pin 2**: Connected to GPIO5-A3-D3 of the Seeed Studio XIAO ESP32C3.  
* **Instance 2**:  
  * **Pin 1**: Connected to the positive pin of the Red LED.  
  * **Pin 2**: Connected to GPIO6-SDA-D4 of the Seeed Studio XIAO ESP32C3.

### ---

**SG90 Servo Motor**

* **PWM Pin**: Connected to the 100 Ohm resistor.  
* **\+5V Pin**: Connected to the \+5V net.  
* **GND Pin**: Connected to the GND net.

### ---

**Pushbutton**

* **Pin 1 (in)**: Not connected in the provided net list.  
* **Pin 2 (in)**: Connected to GPIO3-A1-D1 of the Seeed Studio XIAO ESP32C3.  
* **Pin 3 (out)**: Not connected in the provided net list.  
* **Pin 4 (out)**: Connected to the GND net.

### ---

**Red LED**

* **Positive (+) Pin**: Connected to the 1000 Ohm resistor (Instance 2).  
* **Negative (-) Pin**: Connected to the GND net.

### ---

**Green LED**

* **Positive (+) Pin**: Connected to the 1000 Ohm resistor (Instance 1).  
* **Negative (-) Pin**: Connected to the GND net.

### ---

**HLK-5M05 Power Module**

* **\+Vo Pin**: Connected to the \+5V net.  
* **\-Vo Pin**: Connected to the GND net.

### ---

**Seeed Studio XIAO ESP32C3**

* **\+5V Pin**: Connected to the \+5V net.  
* **GND Pin**: Connected to the GND net.  
* **GPIO2-A0-D0 to GPIO20-RX-D7**: Various connections to resistors and pushbutton as detailed above.

## **Code Documentation**

No code was provided for this circuit. If code is added, it should be documented here with explanations of its functionality and how it interacts with the hardware components.