#include <DueTimer.h>

volatile void myTimedPrint();
volatile void myTimedPulse();

//Global counter variable
volatile int printCounter;
volatile boolean l;

void setup() 
{
  Serial.begin(115200);
  pinMode(13,OUTPUT);
  printCounter = 0;
  
  //Choose from startTimer1 - 9
  startTimer1(2, myTimedPrint); // (Frequency, function)
  
  //Set pulse on a different timer
  startTimer2(5000, myTimedPulse);  // Pulse pin 13 at 5kHz
}

void loop() 
{
  //Disable print interrupt after 100 prints
  if(printCounter >= 100)
  {
    stopTimer1();
  }
}

volatile void myTimedPrint()
{
  Serial.print("Slow timer triggered ");
  Serial.print(printCounter);
  Serial.println(" times");
  printCounter++;
}

volatile void myTimedPulse()
{
  digitalWrite(13, l = !l);
}
