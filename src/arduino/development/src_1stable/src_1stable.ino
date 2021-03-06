/*
 *  Original example code which this code is based on can be found at: 
 *  http://www.cooking-hacks.com/documentation/tutorials/ehealth-biometric-sensor-platform-arduino-raspberry-pi-medical
 * 
 *  Jauvajs Ino
 *  Bluetooth relayed loop designed for collecting and sending values from sensors.
 *  
 *  Allows selection of individual sensors to scan and send via commands scanned on
 *  serial port.
 *
 *  Version 0.5
 *  Author: Stepan Sevcik @ SEJDREm
 */
 
#include <PinChangeInt.h>
#include <eHealth.h>

#define BT
//#define SYNC

#define S_TEMP 0
#define S_COND 1
#define S_RESI 2
#define S_EKG 3
#define S_BPM 4
#define S_SPO2 5
#define S_ACCE 6
#define S_AIRF 7
#define SENSOR_COUNT 8

#define CHECK_DELAY 4
#define CYCLE_DELAY 20
#define LED 13

char recv[128];
uint8_t cont = 0;


boolean sensor_usage[SENSOR_COUNT];
short check_delayer = 0;

//  Note :  The Xbee modules must be configured previously.
//  See the next link http://www.cooking-hacks.com/index.php/documentation/tutorials/arduino-xbee-shield

void bt_setup(){
  delay(4000);
  Serial.print("AT+JSEC=1,1,2,04,0000\r\n"); // Enable security command
  delay(4000);
  Serial.print("AT+JSLN=10,JauvajsIno\r\n"); // Setup name of device
  delay(4000);  
  Serial.print("AT+JDIS=3\r\n"); // Discoverable command
  delay(4000);
  Serial.print("AT+JRLS=1101,11,Serial Port,01,000000\r\n"); // Register local sevice command
  delay(4000);
  Serial.print("AT+JAAC=1\r\n");// Auto accept connection requests command
  delay(4000);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.flush();

  //wait until BT module will be configured
  int val = -1;
  val = Serial.read();
  while (val != 'R'){
    val = Serial.read();
  }
  
}

void sync(){
  char val = Serial.read();
  while (val != 'P'){
    Serial.print("Ja jsem Jauvajs Ino.\n Potrebuji >P< abych mohlo zacit pracovat.");
    delay(333);
    val = Serial.read();
  }
}

void setup()
{
  Serial.begin(115200);
  delay(2000);

#ifdef BT
  bt_setup();
#endif

#ifdef SYNC
  sync();
#endif 

  delay(1000);
  Serial.print("AT+JSCR\r\n"); // Stream Connection Request command
  
  for(short i = 0; i < SENSOR_COUNT; i++){
    sensor_usage[i] = true;
  }
  eHealth.initPulsioximeter();
  eHealth.initPositionSensor();

  //Attach the inttruptions for using the pulsioximeter.
  PCintPort::attachInterrupt(6, readPulsioximeter, RISING);
  delay(1000);

}

void loop()
{
  float SPO2, BPM, temperature, conductance, resistance, EKG;
  int   airflow;
  uint8_t pos;
  boolean first_sent = false;
  
  //input_check();
  if(sensor_usage > 0){
    
    Serial.print(millis());Serial.print("\tCheck: "); Serial.print(check_delayer); Serial.print("\t-\t");
    
    if(is_enabled(S_AIRF)){
      airflow = eHealth.getAirFlow();
    }
    if(is_enabled(S_TEMP)){
      temperature = eHealth.getTemperature();
    }
    if(is_enabled(S_COND)){
      conductance = eHealth.getSkinConductance();
    }
    if(is_enabled(S_RESI)){
      resistance = eHealth.getSkinResistance();
    }
    if(is_enabled(S_EKG)){
      EKG = eHealth.getECG();
    }
    if(is_enabled(S_BPM)){
      BPM = eHealth.getBPM();
    }
    if(is_enabled(S_SPO2)){
      SPO2 = eHealth.getOxygenSaturation();
    }
    if(is_enabled(S_ACCE)){
      pos = eHealth.getBodyPosition();
    }
  
    Serial.print("[");
    if(is_enabled(S_AIRF)){
      first_sent = fprint_int   (first_sent, "F&", airflow, 0);
    }
    if(is_enabled(S_TEMP)){
      first_sent = fprint_float (first_sent, "T&", temperature, 2);    // teplota
    }
    if(is_enabled(S_BPM)){
      first_sent = fprint_int   (first_sent, "P&", int(BPM), 2);       // puls
    }
    if(is_enabled(S_SPO2)){
      first_sent = fprint_int   (first_sent, "O&", SPO2, 0);           // okysliceni
    }
    if(is_enabled(S_COND)){
      first_sent = fprint_float (first_sent, "V&", conductance, 2);    // GSR - napětí
    }
    if(is_enabled(S_RESI)){
      first_sent = fprint_int   (first_sent, "R&", int(resistance), 0);// GSR - odpor
    }
    if(is_enabled(S_EKG)){
      first_sent = fprint_float (first_sent, "H&", EKG, 6);            // EKG
    }
    if(is_enabled(S_ACCE)){
      first_sent = fprint_int   (first_sent, "A&", int(pos), 0);      // akcelerometr
    }
    Serial.print("]\n");
    // Reduce this delay for more data rate
    delay(CYCLE_DELAY);
  } else {
    Serial.print("Sleep cycle: "); Serial.print(check_delayer); Serial.print("\n");
    delay(CYCLE_DELAY * 4 / 3);
  }

}

boolean is_enabled(int sensor_number){
  if(sensor_number < 0 || sensor_number > SENSOR_COUNT){
    Serial.print("Bad sensor number: "); Serial.print(sensor_number);
    return false;
  }
  return sensor_usage[sensor_number];
}

boolean fprint_int(boolean first_sent, char* stamp, int val, int format){
  if(first_sent){
    Serial.print("\t");
  }
  
  Serial.print(stamp);
  
  if(format > 1){ Serial.print(val, format);
  } else {
    Serial.print(val);
  }
  
  return true;
}

boolean fprint_float(boolean first_sent, char* stamp, float val, int format){
  if(first_sent){
    Serial.print("\t");
  }
  Serial.print(stamp); Serial.print(val, format);
  
  return true;
}

void set_enabled(boolean value, short sensor){
  if(sensor < 0 || sensor >= SENSOR_COUNT){
    Serial.print("Invalid bit index: "); Serial.print(sensor);
  }
  sensor_usage[sensor] = value;
}

int process_command(char *command, char *argument){
  unsigned short differ;
  if(strcmp(command, "SET") == 0){
    return set_usage_bits(argument);
  }
  switch(argument[0]){
    case 'T': differ = S_TEMP; break;
    case 'V': differ = S_COND; break;
    case 'R': differ = S_RESI; break;
    case 'H': differ = S_EKG;  break;
    case 'P': differ = S_BPM;  break;
    case 'O': differ = S_SPO2; break;
    case 'A': differ = S_ACCE; break;
    case 'F': differ = S_AIRF; break;
    default:
      Serial.print("Invalid argument: "); Serial.print(argument); Serial.print(" value not in [A F H O P R T V]!\n");
      return 2;
  }
  switch(command[0]){
    case 'E':
      Serial.print("Enabling "); Serial.print(differ); Serial.print("\n");
      set_enabled(true, differ);
      break;
    case 'D':
      Serial.print("Disabling "); Serial.print(differ); Serial.print("\n");
      set_enabled(false, differ);
      break;
    default: 
      return 3;
  }
    return 0;
}

int set_usage_bits(char *argument){
  int len = strlen(argument);
  if(len != SENSOR_COUNT){
    Serial.print("Can't set "); Serial.print(argument); Serial.print(" size not SENSOR_COUNT was ");
    Serial.print(len); Serial.print("\n");
    return 1;
  }
  short i;
  for(i = 0; i < SENSOR_COUNT; i++){
    set_enabled((argument[i] == '1'), i);
  }
  Serial.print("Setting "); Serial.print(argument); 
  return 0;
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
        switch(process_command(command, argument)){
          default: case 0:
            break;
          case 1: case 2: case 3:
            blik(3, 150);
        }
      } else {
        Serial.print("Neplatny prikaz-argument!\n");
      }
    }
  }
}

void check(){
  cont=0; delay(350);
  while (Serial.available()>0)
  {
     recv[cont]=toupper(Serial.read()); delay(10);
     cont++;
  }
  recv[cont]='\0';
  Serial.println(recv);
  Serial.flush(); delay(100);
}

void blik(int n, int t){
  while(n > 0){
    digitalWrite(LED, HIGH);
    delay(t);
    digitalWrite(LED, LOW);
    delay(t);
    n--;
  }
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
