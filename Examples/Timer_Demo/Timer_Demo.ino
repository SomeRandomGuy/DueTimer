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
 
  // Start timer. Parameters are:

  // TC1 : timer counter. Can be TC0, TC1 or TC2
  // 0   : channel. Can be 0, 1 or 2
  // TC3_IRQn: irq number. See table.
  // 2  : frequency (in Hz)
  // myTimedPrint : function pointer to the function you want executed

  startTimer(TC1, 0, TC3_IRQn, 2, myTimedPrint);

  // Paramters table:
  // TC0, 0, TC0_IRQn
  // TC0, 1, TC1_IRQn
  // TC0, 2, TC2_IRQn
  // TC1, 0, TC3_IRQn
  // TC1, 1, TC4_IRQn
  // TC1, 2, TC5_IRQn
  // TC2, 0, TC6_IRQn
  // TC2, 1, TC7_IRQn
  // TC2, 2, TC8_IRQn
  
  //Set pulse on a different timer
  startTimer(TC2, 0, TC6_IRQn, 5000, myTimedPulse);
}

void loop() 
{
  //Disable print interrupt after 100 prints
  if(printCounter >= 100)
  {
    stopTimer(TC3_IRQn);
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
