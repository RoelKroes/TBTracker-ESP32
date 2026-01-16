//============================================================================
// Process a received LoRa packet. 
// This function will run if a packet has been received
// You should create your own actions here.
// Be sure to check if a correct packet was received!
//============================================================================
void ProcessRXPacket() {
  // Buffer to hold the received data from the radio
  byte buf[PACKETLEN];
  int16_t state;

  // EXAMPLE OF RX ACTION
  toSerialConsole("============================================\n");
  toSerialConsole("PACKET RECEIVED!\n");
  toSerialConsole("============================================\n");

  // Grab the data from the radio module
  switch (LORA_MODE) {
    case 1:  // Implicit header, so tell the radio how many bytes to read
      state = radio.readData(buf, LoRaSettings.implicitHeader);
      break;
    default:
      state = radio.readData(buf, 0);
      break;
  }

  // Packet was successfully received
  if (state == RADIOLIB_ERR_NONE) {
    toSerialConsole("Packet length: ");
    toSerialConsole(radio.getPacketLength());toSerialConsole("\n");
    toSerialConsole("          RSSI: ");
    toSerialConsole(radio.getRSSI());toSerialConsole("\n");
    toSerialConsole("           SNR: ");
    toSerialConsole(radio.getSNR());toSerialConsole("\n");
    toSerialConsole("First 10 chars: ");
    // Print the first 10 hex chars of the packet
    toSerialConsole("[RADIO] first 10 hex chars:\t");
    for (int i = 0; i < 10; i++) {
      toSerialConsole(buf[i], HEX);
      toSerialConsole(" ");
    }
    toSerialConsole("\n============================================\n");
  }

  // Reset the received flag
  receivedFlag = false;
}
