/*
 *  Original example code which this code is based on can be found at: 
 *  http://www.cooking-hacks.com/documentation/tutorials/ehealth-biometric-sensor-platform-arduino-raspberry-pi-medical
 * 
 *  Jauvajs Ino
 *  Bluetooth relayed loop designed for collecting and sending values from sensors.
 *
 *  Version 1.0
 *  Author: Stepan Sevcik, Radek Vais, David Jaros, Denisa Tarantikova, Jakub Zaruba
 */
 
#include <PinChangeInt.h>
#include <eHealth.h>

//#define BT
//#define PRINT_TIMESTAMPS

// sensor indexes
#define S_INVALID -1
#define S_EKG 0
#define S_AIRF 1
// less often required sensors
#define SENSOR_LESSER_FIRST 2
#define S_COND 2
#define S_RESI 3
#define S_BPM 4
#define S_SPO2 5
#define S_TEMP 6
#define S_ACCE 7
#define SENSOR_COUNT 7

// functional constants
#define LED 13

#define BAUD_RATE 115200
#define SETUP_WAIT 2000
#define CYCLE_DELAY 20

// sensor organisation
//                                EKG  AIRF COND RESI BPM  SPO2 TEMP ACCE
char sensor_labels[]           = {'E', 'F', 'C', 'R', 'P', 'O', 'T', 'A'};
unsigned char dec_positions[]  = { 6 ,  0 ,  2 ,  2 ,  0 ,  0 ,  2 ,  0 };
// number of measures to be made per second / 1000 millis    later to be used
// as number of millis to be waited between measures

unsigned short seconds_online = 0;
unsigned short millis_state = 0;

uint8_t pulsCount = 0;
int cycle_state = 0, max_state = 50, scanned_sensor = 2;



/*  
 * #######################
 *     Main functions
 * #######################
 */

void setup() {
  Serial.begin(BAUD_RATE);
  delay(SETUP_WAIT);
  
  
#ifdef BT
  bt_setup();
#endif

  
  eHealth.initPulsioximeter();
  eHealth.initPositionSensor();

  //Attach the inttruptions for using the pulsioximeter.
  PCintPort::attachInterrupt(6, readPulsioximeter, RISING);
  
  delay(1000);
}

void loop() {
  float ekg;
  int other_sensor;
  
  // printing timestamp
  #ifdef PRINT_TIMESTAMP
  Serial.print(seconds_online); Serial.print(':');
  Serial.print(millis_state);   Serial.print('\t');
  #endif
  
  other_sensor = (cycle_state % 2 == 1) ? S_AIRF : get_other_sensor();
  if (++cycle_state >= max_state) { cycle_state = 0; }
  // reading values
  ekg = get_sensor_value(S_EKG);
  
  
  // printing values 
  Serial.print("[");
  
  Serial.print(ekg, dec_positions[S_EKG]);
  if(other_sensor != S_INVALID) {
    Serial.print('\t');
    fprint_val( sensor_labels[other_sensor], get_sensor_value(other_sensor), dec_positions[other_sensor]);
  }
  
  Serial.println("]");
  Serial.flush();
  
  // Reduce this delay for more data rate
  delay(CYCLE_DELAY);
  
  millis_state += CYCLE_DELAY;
  if(millis_state >= 1000){
    seconds_online++;
    millis_state -= 1000;
  }
}

/*  
 * #######################
 *      Setup-related
 * #######################
 */

void bt_setup() {
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
}

/*  
 * #######################
 *       Loop related
 * #######################
 */



float get_other_sensor() {
  
  int tmp = S_INVALID;
  
  if (cycle_state == 0) {
    tmp = scanned_sensor;
    if (++scanned_sensor >= SENSOR_COUNT) {
      scanned_sensor = SENSOR_LESSER_FIRST;
    }
  }
  return tmp;
}

float get_sensor_value(int S) {
  switch(S) {
    case S_EKG:  return eHealth.getECG();
    case S_AIRF: return eHealth.getAirFlow();
    case S_TEMP: return eHealth.getTemperature();
    case S_COND: return eHealth.getSkinConductance();
    case S_RESI: return eHealth.getSkinResistance();
    case S_BPM:  return eHealth.getBPM();
    case S_SPO2: return eHealth.getOxygenSaturation();
    case S_ACCE: return eHealth.getBodyPosition();
    default: return S_INVALID;
  }
}

void fprint_val (char stamp, float val, int format) {
  Serial.print(stamp); Serial.print(val, format);
}


//Include always this code when using the pulsioximeter sensor
//=========================================================================
void readPulsioximeter() { 

  pulsCount ++;

  if (pulsCount >= 50) { //Get only one of 50 measures to reduce the latency
    eHealth.readPulsioximeter();
    pulsCount = 0;
  }
}
