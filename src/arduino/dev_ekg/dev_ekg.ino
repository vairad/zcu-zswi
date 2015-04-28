/*
 *  EKG checker and sender
 *
 *  Version 0.1
 *  Author: Stepan Sevcik @ SEJDREm
 */

#include <PinChangeInt.h>
#include <eHealth.h>

#define LED 13
#define CYCLE_DELAY 25

int sec = 0;
int count = 0;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  float ekg = eHealth.getECG();
  
  Serial.print(sec); Serial.print(":"); Serial.print(count*CYCLE_DELAY);
  Serial.print("\t;"); Serial.println(ekg, 6);
  
  if(++count * CYCLE_DELAY >=1000){
    sec++;
    count = 0;
  }
  
  delay(CYCLE_DELAY);

}

void blik(int n, int t)
{
  while (n > 0)
  {
    digitalWrite(LED, HIGH);
    delay(t);
    digitalWrite(LED, LOW);
    delay(t);
    n--;
  }
}
