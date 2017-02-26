#include <VirtualWire.h>
#include "common.cpp"

unsigned long previousMillis = 0;

void send (char *message) {
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
}

void setup() {
  if(DEBUG_MODE){
    Serial.begin(9600);
    Serial.println("Transmitter ready");
  }
  // Initialize the IO and ISR
  vw_setup(BIT_RATE); // Bits per sec
  vw_set_tx_pin(TX_RADIO);
  vw_set_rx_pin(RX_RADIO);
  vw_rx_start(); // Start the receiver
}

// Non-blocking, ftw!
void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > SEND_EVERY) {
   previousMillis = currentMillis;
    send((char *)"testing");
  }
}
