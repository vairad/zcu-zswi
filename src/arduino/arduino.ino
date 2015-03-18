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

unsigned short sensor_usage = 127;
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
  print_sensor_usage();

}

void loop()
{
      float temperature, conductance, resistance, EKG;
      int BPM, SPO2;
      uint8_t pos;
      boolean first_sent = false;
      
      input_check();
      if(sensor_usage > 0){
        Serial.print("Check cycle: "); Serial.print(check_delayer); Serial.print("\t\t");
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
        //Serial.print(int(airFlow));     Serial.print("#");
      
        Serial.print("[");
        if((unsigned short)(sensor_usage & S_TEMP) > 0){
          first_sent = print_if_not_first("T&", temperature, first_sent);    // teplota
        }
        if((unsigned short)(sensor_usage & S_BPM) > 0){
          first_sent = print_if_not_first("P&", int(BPM), first_sent);       // puls
        }
        if((unsigned short)(sensor_usage & S_SPO2) > 0){
          first_sent = print_if_not_first("O&", int(SPO2), first_sent);      // okysliceni
        }
        if((unsigned short)(sensor_usage & S_COND) > 0){
          first_sent = print_if_not_first("V&", conductance, first_sent);    // GSR - napětí
        }
        if((unsigned short)(sensor_usage & S_RESI) > 0){
          first_sent = print_if_not_first("R&", int(resistance), first_sent);// GSR - odpor
        }
        if((unsigned short)(sensor_usage & S_EKG) > 0){
          first_sent = print_if_not_first("H&", EKG, first_sent);            // EKG
        }
        if((unsigned short)(sensor_usage & S_ACCE) > 0){
          first_sent = print_if_not_first("A&", int(pos), first_sent);      // akcelerometr
        }
        Serial.print("]\n");
        // Reduce this delay for more data rate
        delay(250);
      } else {
        Serial.print("Sleep cycle: "); Serial.print(check_delayer); Serial.print("\n");
        delay(500);
      }
      
}

boolean print_if_not_first(char* stamp, int val, boolean first_sent){
  if(first_sent){
    Serial.print("\t");
  }
  Serial.print(stamp); Serial.print(val);
  return true;
}

void input_check(){
  char *temp, *command, *argument;
  
  if(++check_delayer >= CHECK_DELAY){
    check_delayer = 0;
    check();
    if(cont != 0){
      command = strtok_r(recv, " ", &temp);
      argument= strtok_r(NULL, " ", &temp);
      if(command != NULL && argument != NULL){
        process_command(command, argument);
      } else {
        Serial.print("Neplatny prikaz-argument!\n");
      }
    }
  }
}

void process_command(char *command, char *argument){
  unsigned short differ;
  if(strcmp(command, "SET") == 0){
    if(strlen(argument) != 7){
      Serial.print("Can't set "); Serial.print(argument); Serial.print(" size not 7, was ");
      Serial.print(strlen(argument)); Serial.print("\n");
      return;
    }
    Serial.print("SETTING "); Serial.print(argument); Serial.print("\n");
    return;
  }
  switch(argument[0]){
    case 'T': differ = S_TEMP; break;
    case 'V': differ = S_COND; break;
    case 'R': differ = S_RESI; break;
    case 'H': differ = S_EKG;  break;
    case 'P': differ = S_BPM;  break;
    case 'O': differ = S_SPO2; break;
    case 'A': differ = S_ACCE; break;
    default:
      Serial.print("Invalid argument: "); Serial.print(argument); Serial.print(" value not in [A H O P R T V]!\n");
      return;
  }
  switch(command[0]){
    case 'E':
      print_sensor_usage();
      Serial.print("Enabling "); Serial.print(differ); Serial.print("\n");
      sensor_usage = sensor_usage | differ;
      print_sensor_usage();
      break;
    case 'D':
      print_sensor_usage();
      Serial.print("Disabling "); Serial.print(differ); Serial.print("\n");
      differ = ~differ;
      Serial.print("Disabler: "); Serial.print(differ); Serial.print("\n");
      sensor_usage = sensor_usage & differ;
      print_sensor_usage();
      break;
    }
}

void print_sensor_usage(){
  Serial.print("Sensor usage: "); Serial.print(sensor_usage); Serial.print("\n");
}

void check(){
  cont=0; delay(500);
  while (Serial.available()>0)
  {
     recv[cont]=toupper(Serial.read()); delay(10);
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
