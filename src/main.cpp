#ifndef ESPER_BUILD

#include <stdio.h>
#include <string.h>
//#include "common\WString.h"


void removeSpaces(char *str) {
  char *p1 = str, *p2 = str;
  do 
    while (*p2 == ' ')
      p2++;
  while (*p1++ = *p2++);
}

void esper_script(char* msg) {

  //validate msg
  if (msg == NULL) return;

  //sopy tring and remvoe spaces
  char *str = new char[strlen(msg)];
  strcpy(str, msg);
  removeSpaces(str);

  //split
  const char s[2] = ";";
  char* token;
  token = strtok(str, s);

  while( token != NULL ) {
     
    if (strncmp(token, "mode", 4)==0) {
      char* pin[4]; char* mode[3];
      if (2 == sscanf(token, "mode(%[^,],%[^)])", pin, mode)) {
        printf("%s => Pin: %s, Mode: %s\n", token, pin, mode);
      }
    } 

    else if (strncmp(token, "afreq", 5)==0) {
      int freq;
      if (1 == sscanf(token, "afreq(%d)", &freq)) {
        printf("%s => Freq: %i\n", token, freq);
      }
    }

    else if (strncmp(token, "arange", 6)==0) {
      int range;
      if (1 == sscanf(token, "arange(%d)", &range)) {
        printf("%s => Range: %i\n", token, range);
      }
    }

    else if (strncmp(token, "dread", 5)==0) {
      char pin[4];
      if (1 == sscanf(token, "dread(%[^)])", pin)) {
        printf("%s => Pin: %s\n", token, pin);
      }
    }

    else if (strncmp(token, "dwrite", 6)==0) {
      char pin[4]; int value;
      if (2 == sscanf(token, "dwrite(%[^,],%d)", pin, &value)) {
        printf("%s => Pin: %s, Value: %i\n", token, pin, value);
      }
    }

    else if (strncmp(token, "awrite", 6)==0) {
      char pin[4]; int value;
      if (2 == sscanf(token, "awrite(%[^,],%d)", pin, &value)) {
        printf("%s => Pin: %s, Value: %i\n", token, pin, value);
      }
    }

    if (strncmp(token, "attach", 6)==0) {
      char* pin[4]; char* topic[20];
      if (2 == sscanf(token, "attach(%[^,],'%[^')]')", pin, topic)) {
        printf("%s => Pin: %s, Topic: %s\n", token, pin, topic);
      }
    } 

    else if (strncmp(token, "detach", 6)==0) {
      char pin[2];
      if (1 == sscanf(token, "detach(%[^)])", pin)) {
        printf("%s => Pin: %s\n", token, pin);
      }
    }

    else if (strncmp(token, "dpulse", 6)==0) {
      int ms = 0; char pinout[4]; char pinin[4]; char topic[20];
      if (4 == sscanf(token, "dpulse(%d,%[^,],%[^,],'%[^']')", &ms, pinout, pinin, topic)) {
        printf("%s => Ms: %i, PinOut: %s, PinIn: %s, Topic: %s\n", token, ms, pinout, pinin, topic);
      }
    }
    
    else if (strncmp(token, "dtread", 6)==0) {
      int s = 0; char pin[4]; char topic[20];
      if (3 == sscanf(token, "dtread(%d,%[^,],%[^,],'%[^']')", &s, pin, topic)) {
        printf("%s => S: %i, Pin: %s, Topic: %s\n", token, s, pin, topic);
      }
    }

    else if (strncmp(token, "dttrig", 6)==0) {
      int s = 0; char cmpin[4]; char cmp[3]; int cmval = 0; 
      char trpin[4]; int tryes = 0; int trno = 0; char topic[20];
      //esper_script("dttrig(5,D1>233,D3,0,255,'/esper/dttrig5');");  //every 5 seconds check if D1 > D2 then digitalWrite to D3 0 else 255, send value to MQTT topic
      if (8 == sscanf(token, "dttrig(%d,%[^<>=]%[<>=]%d,%[^,],%d,%d,'%[^']')", 
                              &s, cmpin, cmp, &cmval, trpin, &tryes, &trno, topic)) {
        printf("%s => S: %i, CmPin: %s, Cmp: %s, CmVal:%i, TrPin:%s, TrY:%i, TrN:%i, Topic: %s\n", 
                token, s, cmpin, cmp, cmval, trpin, tryes, trno, topic);
      }
    }

    else if (strncmp(token, "dtpid", 5)==0) {
      int s = 0; char pinin[4]; char pinout[4]; float p = 0; float i = 0; float d=0; char topic[20];
      if (7 == sscanf(token, "dtpid(%d,%[^,],%[^,],%f,%f,%f,'%[^']')", 
                              &s, pinin, pinout, &p, &i, &d, topic)) {
        printf("%s => S: %i, PinIn: %s, PinOut: %s, P: %.2f, I: %.2f, D: %.2f, Topic: %s\n", 
                token, s, pinin, pinout, p, i, d, topic);
      }
    }

    token = strtok(NULL, s);
  }
}

int main()
{
  esper_script(""); 
  esper_script(NULL); 

  // Setup commands
  esper_script("mode(D1,I);mode( D2, I );mode( D3,O );mode(A1, O);"); //void pinMode(uint8_t pin, uint8_t mode);
  esper_script("afreq( 500);"); //void analogWriteFreq(uint32_t freq);
  esper_script("arange(128 );"); //void analogWriteRange(uint32_t range);

  // Basic commands
  esper_script("dread(D1);");  //int digitalRead(uint8_t pin);
  esper_script("dwrite(D2,255);"); //void digitalWrite(uint8_t pin, uint8_t val);
  esper_script("awrite(A1,223);");  //void analogWrite(uint8_t pin, int val);

  esper_script("attach(A3,'/esper/wow');");  // void attachInterrupt(uint8_t pin, void (*)(void), int mode);
  esper_script("detach(A3);");  // void detachInterrupt(uint8_t pin);

  //Pulse read
  esper_script("dpulse(10, D1,D2,'/esper/dpuls');");  //pulse 10ms on D1,  return pulseIn on D2

  // Timer process
  esper_script("dtread(5,D1,'/esper/dtread5');");  //return digitalRead result every 5 seconds

  //Digital comparator  process
  esper_script("dttrig(5, D1 <= 233, D3, 0, 255, '/esper/dttrig5');");  //every 5 seconds check if D1 > 233 then digitalWrite to D3 0 else 255, send value to MQTT topic

  // PID regulator process
  esper_script("dtpid(5, D1, D2, 1.1, 2.5, 0.2, '/esper/dtpid5');");  //every 5 seconds check if D1 > D2 then digitalWrite to D3 0 else 255

  return 0;
}





#endif
