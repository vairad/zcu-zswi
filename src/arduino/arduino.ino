/*
 *  eHealth sensor platform for Arduino and Raspberry from Cooking-hacks.
 *
 *  Description: "The e-Health Sensor Shield allows Arduino and Raspberry Pi
 *  users to perform biometric and medical applications by using 9 different
 *  sensors: Pulse and Oxygen in Blood Sensor (SPO2), Airflow Sensor (Breathing),
 *  Body Temperature, Electrocardiogram Sensor (ECG), Glucometer, Galvanic Skin
 *  Response Sensor (GSR - Sweating), Blood Pressure (Sphygmomanometer) and
 *  Patient Position (Accelerometer)."
 *
 *  Explanation: This example shows the way to communicate with
 *  the Arduino using ZigBee protocol.
 *
 *  Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version 2.0
 *  Author: Luis Martin & Ahmad Saad
 */
 
#include <PinChangeInt.h>
#include <eHealth.h>

#define S_TEMP 1
#define S_COND 2
#define S_RESI 4
#define S_EKG 8
#define S_BPM 16
#define S_SPO2 32
#define S_ACCE 64

#define CHECK_DELAY 4

char recv[128];
uint8_t cont = 0;

char sensor_usage = 0xFF;
short check_delayer = 0;

//  Note :  The Xbee modules must be configured previously.
//  See the next link http://www.cooking-hacks.com/index.php/documentation/tutorials/arduino-xbee-shield

void setup()
{
  Serial.begin(9600);

  eHealth.initPulsioximeter();
  eHealth.initPositionSensor();

  //Attach the inttruptions for using the pulsioximeter.
  PCintPort::attachInterrupt(6, readPulsioximeter, RISING);
  delay(1000);

}

void loop()
{
      float temperature, conductance, resistance, EKG;
      int BPM, SPO2;
      uint8_t pos;
      
      input_check();
      
      //1. Read from eHealth.
       //int airFlow = eHealth.getAirFlow();
       if(sensor_usage & S_TEMP > 0){
         temperature = eHealth.getTemperature();
       }
       if(sensor_usage & S_COND > 0){
         conductance = eHealth.getSkinConductance();
       }
       if(sensor_usage & S_RESI > 0){
         resistance = eHealth.getSkinResistance();
       }
       if(sensor_usage & S_EKG > 0){
         EKG = eHealth.getECG();
       }
       if(sensor_usage & S_BPM > 0){
         BPM = eHealth.getBPM();
       }
       if(sensor_usage & S_SPO2 > 0){
         SPO2 = eHealth.getOxygenSaturation();
       }
       if(sensor_usage & S_ACCE> 0){
         pos = eHealth.getBodyPosition();
       }

      Serial.print("Check cycle: "); Serial.print(check_delayer); Serial.print("\t");
      
      //Serial.print(int(airFlow));     Serial.print("#");
      if(sensor_usage & S_TEMP > 0){
        Serial.print("T&");  Serial.print(temperature);      Serial.print("#"); // teplota
      }
      if(sensor_usage & S_BPM > 0){
        Serial.print("P&");  Serial.print(int(BPM));         Serial.print("#"); // puls
      }
      if(sensor_usage & S_SPO2 > 0){
        Serial.print("O&");  Serial.print(int(SPO2));        Serial.print("#"); // okysliceni
      }
      if(sensor_usage & S_COND > 0){
        Serial.print("V&");  Serial.print(conductance);      Serial.print("#"); // GSR
      }
      if(sensor_usage & S_RESI > 0){
        Serial.print("R&");  Serial.print(int(resistance));  Serial.print("#"); // GSR
      }
      if(sensor_usage & S_EKG > 0){
        Serial.print("H&");  Serial.print(EKG);              Serial.print("#"); // EKG
      }
      if(sensor_usage & S_ACCE > 0){
        Serial.print("A&");  Serial.print(int(pos));         Serial.print("#"); // akcelerometr
      }
      Serial.print("\n");

      // Reduce this delay for more data rate
      delay(250);
}

void input_check(){
  if(++check_delayer >= CHECK_DELAY){
        check_delayer = 0;
        check();
        Serial.print("Got: "); Serial.print(recv); Serial.print("\n");
   }
}

void check(){
  cont=0; delay(500);
  while (Serial.available()>0)
  {
     recv[cont]=Serial.read(); delay(10);
     cont++;
  }
  recv[cont]='\0';
  Serial.println(recv);
  Serial.flush(); delay(100);
}



//Include always this code when using the pulsioximeter sensor
//=========================================================================
void readPulsioximeter(){

  cont ++;

  if (cont == 50) { //Get only one of 50 measures to reduce the latency
    eHealth.readPulsioximeter();
    cont = 0;
  }
}
