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

void setup(){
	delay(2000);
	Serial.begin(115200);
	delay(2000);
	Serial.print("AT+JSEC=1,1,1,04,1111\r\n"); // Enable security command
	delay(2000);
	Serial.print("AT+JDIS=3\r\n"); // Discorable command
	delay(2000);
	Serial.print("AT+JRLS=1101,11,Serial Port,01,000000\r\n"); // Register local sevice command
	delay(2000);
	Serial.print("AT+JAAC=1\r\n");// Auto accept connection requests command
	delay(2000);
	pinMode(led, OUTPUT);
	digitalWrite(led,HIGH);
	Serial.flush();
	val = Serial.read();
	while (val != 'R'){
	  val = Serial.read();
	}
	delay(1000);
	Serial.print("AT+JSCR\r\n"); // Stream Connection Request command
}

void loop(){
	Serial.println("Hola caracola...");
	delay(2000);
}
