#include <application.h>

uint32_t lastReset = 0; // last known reset time
bool s = true;

void setup()
{
/*
  // Watchdog setup in case you want to override 
  // the system configuration
  //--------------------------------------------
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  // check that we flag reset before writing Prescaler
  while (IWDG_GetFlagStatus(IWDG_FLAG_PVU) == SET) {
    // Wait until hardware is ready 
  }
  
  //IWDG_SetPrescaler(IWDG_Prescaler_64);
  IWDG_SetPrescaler(IWDG_Prescaler_256);
  
  // check that we flag reset before writing Reload value
  while (IWDG_GetFlagStatus(IWDG_FLAG_RVU) == SET) {
    // Wait until hardware is ready 
  }
  
  //IWDG_SetReload(0x0FFF); // 0x0FFF = 6.55 seconds (prescaler of 64)
  IWDG_SetReload(0x0FFF); // 0x0FFF = 26.2 seconds (prescaler of 256)

  IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable); // block lockdown
  IWDG_ReloadCounter(); // kick the dog for the first time
  IWDG_Enable(); // should probably not be needed since we are setting the flags above and then disabling the write access but it doesnt hurt...   
*/
  pinMode(D7, OUTPUT);
  lastReset = millis(); // We just powered up 
}

void loop() {
  // Wait 5 seconds before running our code, this demonstrates that the RGB
  // is breathing RED to indicate IWDG reset occurred.
  if( (millis()-lastReset) > (5*1000) ) {
    // After 5 seconds...

    // This is how we can detect we are running from a IWDG (Independent Watchdog) reset
    if(IWDG_SYSTEM_RESET == 1) {
      // This is how we switch breathing RED back to CYAN
      LED_SetRGBColor(RGB_COLOR_CYAN);
      IWDG_SYSTEM_RESET = 0; // reset IWDG flag for good measure
      
      // Optionally, we can log that 
      //a watchdog timeout occurred.
    }

    // This hard loop will force the IWDG to occur after 26.208 seconds
    while(true) {
      digitalWrite(D7,s);
      s = !s; // toggle the state
      delay(30); // makes it blink faster!!! 
    }
  }
  
  // Blink the LED so know the code is running...
  digitalWrite(D7,s);
  s = !s; // toggle the state
  delay(100); // makes it blinky
}