/************************************************************************************
* Process a received LoRa packet. 
* This function will run if a packect has been received
* You should create your own actions here.
* Be sure to check if a correct packet was received!
************************************************************************************/
void ProcessRXPacket()
{
  // Buffer to hold the received data from the radio
  byte buf[PACKETLEN];
  int16_t state;

  // EXAMPLE OF RX ACTION 

  // reset the data received flag
  Serial.println("============================================");
  Serial.println("PACKET RECEIVED!");
  Serial.println("============================================");
  
  // Grab the data from the radio module
  switch(LORA_MODE)
  {
     case 1:  // Implicit header, so tell the radio how many bytes to read
        state = radio.readData(buf,LoRaSettings.implicitHeader);
     break;
     default: 
        state = radio.readData(buf,0);
    break;
  }

  // Packet was successfully received
  if (state == RADIOLIB_ERR_NONE) 
  {
      Serial.print( "Packet length: "); Serial.println(radio.getPacketLength());
      Serial.print("          RSSI: "); Serial.println(radio.getRSSI());
      Serial.print("           SNR: "); Serial.println(radio.getSNR());
      Serial.print("First 10 chars: ");
      // Print the first 10 hex chars of the packet
      Serial.print("[RADIO] first 10 hex chars:\t");
      for (int i = 0; i < 10; i++)
      {
        Serial.print(buf[i],HEX);
        Serial.print(" ");
      }
      Serial.println();
      Serial.println("============================================");
  }

  // Reset the received flag  
  receivedFlag = false;
}
