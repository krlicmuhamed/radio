#include <VirtualWire.h>
#include "common.cpp"

void setup()
{
  if(DEBUG_MODE){
    Serial.begin(9600);
    Serial.println("Receiver ready");
  }
  // Initialise the IO and ISR
  vw_setup(BIT_RATE);      // Bits per sec
  vw_set_rx_pin(RX_RADIO);
  vw_rx_start();       // Start the receiver PLL running
}
void loop()
{
  uint8_t message[VW_MAX_MESSAGE_LEN];
  uint8_t messageLength = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(message, &messageLength)) {
    Serial.print("Received: ");

    for (int i = 0; i < messageLength; i++) {
      Serial.write(message[i]);
    }

    Serial.println();
  }
}
