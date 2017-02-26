#include <VirtualWire.h>

#define TX_RADIO 2
#define RX_RADIO 4

unsigned long previousMillis = 0;
byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message

void setup() {
  Serial.begin(9600);
  Serial.println("Device is ready");
  // Initialize the IO and ISR
  vw_setup(1000); // Bits per sec
  vw_set_tx_pin((uint8_t) TX_RADIO);
  vw_set_rx_pin((uint8_t) RX_RADIO);
  vw_rx_start(); // Start the receiver
}

// Non-blocking, ftw!
void loop() {
  unsigned long currentMillis = millis();
  if(vw_tx_active()){ // When transmitting see if we have a message
    Serial.print(vw_have_message()); // Prints out 0's for me
  }

  if (vw_have_message() && vw_get_message(message, &messageLength)) {
    Serial.print("Received: ");

    for (int i = 0; i < messageLength; i++) {
      Serial.write(message[i]);
    }

    Serial.println();
  }

  if(currentMillis - previousMillis > 1000) {
    previousMillis = currentMillis;
    send((char *)"Hello there");
  }
}

void send (char *message) {
  vw_send((uint8_t *)message, strlen(message));
  // vw_wait_tx(); // Wait until the whole message is gone
}
