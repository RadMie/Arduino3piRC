#include <OrangutanMotors.h>
#include <VirtualWire.h>
#include <avr/pgmspace.h>

void setup()
{
  vw_set_tx_pin(1);
  vw_set_rx_pin(0);
  vw_set_ptt_pin(10);
  vw_set_ptt_inverted(true);   // Required for DR3100
  vw_setup(2000);	       // Bits per sec
  
  vw_rx_start();
 
}

uint8_t buf[6];
uint8_t buflen = 6;
int motor = 0;

uint8_t right = 0;
uint8_t left = 0;
void loop()
{
  
  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    if(buf[1] > 127) {
      
      motor = map(buf[1],128,255,0,255);
      
      if(motor < 30) motor = 0;
      
      if(buf[2] > 127) {
        right = map(buf[2],128,255,0,motor/2);
        left = 0;
      } else {
        left = map(buf[2],127,0,0,motor/2);
        right = 0;
      }
      
      OrangutanMotors::setSpeeds(motor-left,motor-right);
      
    } else {
      
      motor = map(buf[1],127,0,0,-255);
      
      if(motor > -30) motor = 0;
      
      if(buf[2] > 127) {
        right = map(buf[2],128,255,0,(motor * -1)/2);
        left = 0;
      } else {
        left = map(buf[2],127,0,0,(motor * -1)/2);
        right = 0;
      }
      
      OrangutanMotors::setSpeeds(motor+left,motor+right);
      
    }
   
  }
  
}
