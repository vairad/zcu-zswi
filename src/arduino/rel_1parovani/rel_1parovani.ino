/*
 *  Original example code which this code is based on can be found at: 
 *  http://www.cooking-hacks.com/documentation/tutorials/ehealth-biometric-sensor-platform-arduino-raspberry-pi-medical
 * 
 *  Jauvajs Ino Device Pairing
 *  Bluetooth pairing setup enabling pair-up with desktop device
 *  
 *  Version 1.0
 *  Author: Stepan Sevcik, Radek Vais, David Jaros, Denisa Tarantikova, Jakub Zaruba
 */

#define BAUD_RATE 115200
#define SETUP_WAIT 2000


/*  
 * #######################
 *     Main functions
 * #######################
 */

void setup() {
  Serial.begin(BAUD_RATE);
  delay(SETUP_WAIT);
  delay(SETUP_WAIT);
  Serial.print("AT+JSEC=1,1,2,04,0000\r\n"); // Enable security command
  
  delay(SETUP_WAIT);
  Serial.print("AT+JSLN=10,JauvajsIno\r\n"); // Setup name of device
  
  delay(SETUP_WAIT);  
  Serial.print("AT+JDIS=3\r\n"); // Discoverable command
  
  delay(SETUP_WAIT);
  Serial.print("AT+JRLS=1101,11,Serial Port,01,000000\r\n"); // Register local sevice command
  
  delay(SETUP_WAIT);
  Serial.print("AT+JAAC=1\r\n");// Auto accept connection requests command
  
  delay(SETUP_WAIT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  
  Serial.flush();

  //wait until BT module will be configured
  int val = Serial.read();
  while (val != 'R') {
    val = Serial.read();
  }
  
  Serial.print("AT+JSCR\r\n"); // Stream Connection Request command
  
  delay(1000);
}

void loop() {}
