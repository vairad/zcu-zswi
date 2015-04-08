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

#define S_INVALID -1
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
#define CYCLE_DELAY 100
#define LED 13

#define SETUP_WAIT 4000

#define RECV_SIZE 32

char sensor_labels[]           = {'T', 'C', 'R', 'H', 'P', 'O', 'A', 'F'};
unsigned short dec_positions[] = { 0 ,  2 ,  2 ,  6 ,  0 ,  0 ,  0 ,  0 }; 
boolean sensor_usage[SENSOR_COUNT];

char recv[RECV_SIZE];
uint8_t cont = 0;
uint8_t pulsCount = 0;


char verification_key = 0;
short check_delayer = 0;

//  Note :  The Xbee modules must be configured previously.
//  See the next link http://www.cooking-hacks.com/index.php/documentation/tutorials/arduino-xbee-shield

void bt_setup(){
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

  char val = 0;
  while (val != 'R'){
    val = Serial.read();
    Serial.flush();
  }
  
  Serial.print("AT+JSCR\r\n"); // Stream Connection Request command
}

void sync(){
  char val = Serial.read();
  while (val != 'P')
  {
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
  sync();  
#endif
  
  for(short i = 0; i < SENSOR_COUNT; i++)
  {
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
  boolean tab = false;
  
  input_check();
  
  Serial.print("Check "); Serial.print(check_delayer); Serial.print(":\t");
  int i;
  float vals[SENSOR_COUNT];
  
  for(i = 0; i < SENSOR_COUNT; i++){
    vals[i] = get_sensor_value(i);
  }

  Serial.print("[");
  for(int i = 0; i < SENSOR_COUNT; i++){
    if(!is_enabled(i)) { continue; }
    tab = fprint_val(tab, sensor_labels[i], vals[i], dec_positions[i]);
  }
  
  Serial.print("]\n");
  // Reduce this delay for more data rate
  delay(CYCLE_DELAY);

}

float get_sensor_value(int S){
  if(!is_enabled(S)){
    return 0;
  }
  switch(S){
    case S_AIRF: return eHealth.getAirFlow();
    case S_TEMP: return eHealth.getTemperature();
    case S_COND: return eHealth.getSkinConductance();
    case S_RESI: return eHealth.getSkinResistance();
    case S_EKG: return eHealth.getECG();
    case S_BPM: return eHealth.getBPM();
    case S_SPO2: return eHealth.getOxygenSaturation();
    case S_ACCE: return eHealth.getBodyPosition();
    default: return S_INVALID;
  }
}

boolean is_enabled(int sensor_number){
  if(sensor_number < 0 || sensor_number > SENSOR_COUNT)
  {
    Serial.print("Bad sensor number: "); Serial.println(sensor_number);
    return false;
  }
  return sensor_usage[sensor_number];
}

boolean fprint_val(boolean first_sent, char stamp, float val, int format){
  if(first_sent)
  {
    Serial.print("\t");
  }
  Serial.print(stamp); Serial.print(val, format);
  
  return true;
}

void set_enabled(boolean value, short sensor){
  if(sensor < 0 || sensor >= SENSOR_COUNT)
  {
    Serial.print("Invalid bit index: "); Serial.println(sensor);
  }
  sensor_usage[sensor] = value;
}

int process_command(char *command, char *argument){

  if(strcmp(command, "SET") == 0)
  {
    return set_usage_bits(argument);
  }
  
  if(strcmp(command, "REVERIFY") == 0){
    return print_enabled_sensors();
  }
  
  
  unsigned short differ = char_to_sensor_number(argument[0]);
  
  if(differ == S_INVALID){
    Serial.print("Invalid argument: "); Serial.print(argument); Serial.println(" value not in [A F H O P R T V]!");
      return 2;
  }
  
  switch(command[0])
  {
    case 'E':
      Serial.print("Enabling "); Serial.println(differ);
      set_enabled(true, differ);
      print_enabled_sensors();
      break;
    case 'D':
      Serial.print("Disabling "); Serial.println(differ);
      set_enabled(false, differ);
      print_enabled_sensors();
      break;
    default: 
      return 3;
  }
    return 0;
}

unsigned short char_to_sensor_number(char c){
  switch(c){
    case 'T': return S_TEMP;
    case 'V': return S_COND;
    case 'R': return S_RESI;
    case 'H': return S_EKG;
    case 'P': return S_BPM;
    case 'O': return S_SPO2;
    case 'A': return S_ACCE;
    case 'F': return S_AIRF;
    default : return S_INVALID;
      
  }
}

int set_usage_bits(char *argument){
  int len = strlen(argument);
  if(len != SENSOR_COUNT)
  {
    Serial.print("Can't set "); Serial.print(argument); Serial.print(" size not ");
    Serial.print(SENSOR_COUNT); Serial.print(" was "); Serial.println(len);
    return 1;
  }
  short i;
  for(i = 0; i < SENSOR_COUNT; i++)
  {
    set_enabled((argument[i] == '1'), i);
  }
  Serial.print("Setting "); Serial.println(argument); 
  print_enabled_sensors();
  return 0;
}

int print_enabled_sensors(){
  verification_key++;
  boolean first_comma = false;
  
  Serial.print(verification_key);
  Serial.print("[");  
  
  for(int i = 0; i < SENSOR_COUNT; i++)
  {
    if(is_enabled(i))
    {
      if(first_comma)
      {
        Serial.print(", ");
      }
      Serial.print(sensor_labels[i]);
      first_comma = true;
    }
  }
  Serial.print("]");
  
  
  return 0;
}

void input_check(){
  char *temp, *command, *argument;
  
  if(++check_delayer >= CHECK_DELAY)
  {
    check_delayer = 0;
    check();
    if(cont != 0)
    {
      Serial.print("Received cmd: "); Serial.println(recv);
      command = strtok_r(recv, " ", &temp);
      argument= strtok_r(NULL, " ", &temp);
      if(command != NULL)
      {
        switch(process_command(command, argument))
        {
          default: case 0:
            break;
          case 1: case 2: case 3:
            blik(3, 150);
        }
      } else {
        Serial.print("Neplatny prikaz!\n");
      }
    }
  }
}

void check(){
  cont=0; delay(350);
  int drop = 0;
  while (Serial.available()>0)
  {
    if(cont < RECV_SIZE -1){
      recv[cont]=toupper(Serial.read()); delay(10);
      cont++;
    } else {
      drop++;
    }
  }
  recv[cont]='\0';
  if(drop)
  {
    Serial.print("Incomming command was "); Serial.print(drop); Serial.print(" characters longer than max of ");
    Serial.println(RECV_SIZE-1);
  }
  Serial.flush(); delay(100);
}

void blik(int n, int t){
  while(n > 0)
  {
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

  pulsCount ++;

  if (pulsCount >= 50) { //Get only one of 50 measures to reduce the latency
    eHealth.readPulsioximeter();
    pulsCount = 0;
  }
}
