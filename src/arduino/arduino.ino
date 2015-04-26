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
 *  Version 0.6
 *  Author: Stepan Sevcik @ SEJDREm
 */
 
#include <PinChangeInt.h>
#include <eHealth.h>

//#define BT 

// sensor indexes
#define S_INVALID -1
#define S_EKG 0
#define S_TEMP 1
#define S_COND 2
#define S_RESI 3
#define S_BPM 4
#define S_SPO2 5
#define S_ACCE 6
#define S_AIRF 7
#define SENSOR_COUNT 8

// functional constants
#define LED 13

#define BAUD_RATE 115200
#define SETUP_WAIT 2000

// sensor organisation
//                                EKG  TEMP COND RESI BPM  SPO2 ACCE AIRF
char sensor_labels[]           = {'E', 'T', 'C', 'R', 'P', 'O', 'A', 'F'};
unsigned char dec_positions[]  = { 6 ,  0 ,  2 ,  2 ,  0 ,  0 ,  0 ,  0 };
// number of measures to be made per second / 1000 millis
int measure_gaps[]             = { 50,  1 ,  4 ,  4 ,  2 ,  2 ,  5 ,  25};
byte measure_delay[]           = { 0,   20,  50,  60,  30,  40,  70,  10};

unsigned short seconds_online = 0;
unsigned short millis_state = 0;
unsigned short last_check[SENSOR_COUNT];

uint8_t pulsCount = 0;
int cycle_delay;

/*  
 * #######################
 *     Main functions
 * #######################
 */

void setup() {
  Serial.begin(BAUD_RATE);
  delay(SETUP_WAIT);
  
  cycle_delay = calc_gaps();
  
  
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
  boolean indent = false;
  float vals[SENSOR_COUNT];
  
  int i;
  
  // printing timestamp
  Serial.print(seconds_online); Serial.print(':');
  Serial.print(millis_state);   Serial.print('\t');
  
  // reading values 
  for (i = 0; i < SENSOR_COUNT; i++) {
    if(millis_state - last_check[i] - measure_delay[i] > measure_gaps[i]) { continue; }
    
    vals[i] = get_sensor_value(i);
    last_check[i] = millis_state;
  }
  
  // printing values 
  Serial.print("[");
  for (int i = 0; i < SENSOR_COUNT; i++) {
    if(last_check[i] != millis_state) { continue; }
    
    if (indent) { Serial.print("\t"); }
    else { indent = true; }
    
    fprint_val( sensor_labels[i], vals[i], dec_positions[i]);
  }
  
  
  Serial.println("]");
  // Reduce this delay for more data rate
  delay(cycle_delay);
  
  millis_state += cycle_delay;
  if(millis_state >= 1000){
    second_done();
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

// taken from http://codereview.stackexchange.com/questions/37189/euclids-algorithm-greatest-common-divisor/37267#37267
// greatest common divisor
int gcd(unsigned int m, unsigned int n) {
    if(!m || !n)
        return(0);

    for (int r = m%n; r; m = n, n = r, r = m%n);

    return(n);
}

// calculates time gaps between measures for every sensor for given number of measures per 1000 millis
// returns cycle delay as greatest common divisor of all the calculated values
int calc_gaps() {
  for (int i = 0; i < SENSOR_COUNT; i++) {
    measure_gaps[i] = 1000 / measure_gaps[i];
  }
  int g_c_d = measure_gaps[0];
  for (int i = 1; i < SENSOR_COUNT; i++) {
    g_c_d = gcd(g_c_d, measure_gaps[i]);
  }
  return g_c_d;
}

/*  
 * #######################
 *       Loop related
 * #######################
 */

void second_done() {
  seconds_online++;
  millis_state -= 1000;
  for(int i = 0; i < SENSOR_COUNT; i++){
    last_check[i] -= 1000;
  }
}

float get_sensor_value(int S) {
  switch(S) {
    case S_AIRF: return eHealth.getAirFlow();
    case S_TEMP: return eHealth.getTemperature();
    case S_COND: return eHealth.getSkinConductance();
    case S_RESI: return eHealth.getSkinResistance();
    case S_EKG:  return eHealth.getECG();
    case S_BPM:  return eHealth.getBPM();
    case S_SPO2: return eHealth.getOxygenSaturation();
    case S_ACCE: return eHealth.getBodyPosition();
    default: return S_INVALID;
  }
}

void fprint_val (char stamp, float val, int format) {
  Serial.print(stamp); Serial.print('&'); Serial.print(val, format);
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
