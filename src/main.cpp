#ifndef ESPER_BUILD

#include <stdio.h>
#include <string.h>
//#include "common\WString.h"

void esper_script(char* msg) {

  const char s[2] = ";";
  char str[] = "mode(D1,I);mode(D2,I);mode(D3,O);mode(A1,O);";
  char* token;

  token = strtok(str, s);
  while( token != NULL ) {
     printf("Command: %s\n", token);
     
     //char* a; char* b; char* c;
     //sscanf(token, "%[^(]\t%[^,]\t%[^)]", &a, &b, &c);
     //printf(a); printf(b); printf(c);

     token = strtok(NULL, s);
  }
}

int main()
{
  printf("Hello\n");
  /*
  char str[] ="- This, a sample string.";
  char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str," ,.-");
  while (pch != NULL)
  {
    printf ("%s\n",pch);
    pch = strtok (NULL, " ,.-");
  }
  return 0;*/

  // Setup commands
  esper_script("mode(D1,I);mode(D2,I);mode(D3,O);mode(A1,O);"); //void pinMode(uint8_t pin, uint8_t mode);
  esper_script("afreq(500);"); //void analogWriteFreq(uint32_t freq);
  esper_script("arange(128);"); //void analogWriteRange(uint32_t range);

  // Basic commands
  esper_script("dread(D1);");  //int digitalRead(uint8_t pin);
  esper_script("dwrite(D2,255);"); //void digitalWrite(uint8_t pin, uint8_t val);
  esper_script("awrite(A1);");  //void analogWrite(uint8_t pin, int val);

  esper_script("attach(A3,'/esper/wow');");  // void attachInterrupt(uint8_t pin, void (*)(void), int mode);
  esper_script("detach(A3);");  // void detachInterrupt(uint8_t pin);

  //Pulse read
  esper_script("dpuls(10,D1,D2,'/esper/dpuls');");  //pulse 10ms on D1,  return pulseIn on D2

  // Timer process
  esper_script("dtread(5,D1,'/esper/dtread5');");  //return digitalRead result every 5 seconds

  //Digital comparator  process
  esper_script("dttrig(5,D1>D2,D3=0,D3=255,'/esper/dttrig5');");  //every 5 seconds check if D1 > D2 then digitalWrite to D3 0 else 255

  // PID regulator process
  esper_script("dtpid(5,D1,D2,'/esper/dtpid5');");  //every 5 seconds check if D1 > D2 then digitalWrite to D3 0 else 255

  return 0;
}





#endif
