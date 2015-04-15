  /*
*  Sending data using Bluetooth module from Libelium for Arduino
*  Connect without security
*
*  Copyright (C) 2009 Libelium Comunicaciones Distribuidas S.L.
*  http://www.libelium.com
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*  Version 0.1
*  Author: Marcos Yarza
*/


int led = 13;
int val = -1;
int n = 0;

void setup(){
  Serial.begin(115200);
  
  delay(2000);
  Serial.print("AT+JSEC=1,1,2,04,0000\r\n"); // Enable security command
  delay(2000);
  Serial.print("AT+JSLN=10,JauvajsIno\r\n"); // Setup name of device
  delay(2000);  
  Serial.print("AT+JDIS=3\r\n"); // Discoverable command
  delay(2000);
  Serial.print("AT+JRLS=1101,11,Serial Port,01,000000\r\n"); // Register local sevice command
  delay(2000);
  Serial.print("AT+JAAC=1\r\n");// Auto accept connection requests command
  delay(2000);
  pinMode(led,  OUTPUT);
  digitalWrite(led, LOW);
  Serial.flush();

  //wait until BT module will be configured
  int val = -1;
  val = Serial.read();
  while (val != 'R'){
    val = Serial.read();
  }
    Serial.print("AT+JSCR\r\n"); // Stream Connection Request command
}

void loop(){
  
  Serial.print(++n); Serial.println("\tHola caracola...");
  delay(20);
}
