//============================================================================
// This file contains some general useful functions
//============================================================================


//============================================================================
// Sends output to the serial console with 1ms delay between characters
//============================================================================
template <typename T>
void toSerialConsole(T data) {  
#if defined(ALLOWDEBUG)	
  // this will work for int, float, double, char, etc.
  String Str = String(data);
  
  // Send the String one char at the time
  for (unsigned int i = 0; i < Str.length(); i++) {
    Serial.write(Str[i]);
    delay(1); // 1ms delay for esp32s2 and c3 mcu with native USB comms.
  }
	Serial.flush();
#endif	
}

// version for floats where you can specify the number of decimals
void toSerialConsole(double data, int decimals) {
#if defined(ALLOWDEBUG)	
  String Str = String(data, decimals);
  for (unsigned int i = 0; i < Str.length(); i++) {
    Serial.write(Str[i]);
    delay(1);
  }
	Serial.flush();
#endif	
}

//============================================================================
// Calculate CRC to be used in the TX line
//============================================================================
uint16_t _crc_xmodem_update(uint16_t crc, uint8_t data) {
	unsigned int i;

	crc = crc ^ ((uint16_t)data << 8);
	for (i = 0; i < 8; i++) {
		if (crc & 0x8000) {
			crc = (crc << 1) ^ 0x1021;
		} else {
			crc <<= 1;
		}
	}
	return crc;
}

//============================================================================
// Fast CRC16 code. Used in the Horus binary packets.
//============================================================================
unsigned int crc16(unsigned char *string, unsigned int len) {
	unsigned int i;
	unsigned int crc;
	crc = 0xFFFF;  // Standard CCITT seed for CRC16.
	// Calculate the sum, ignore $ sign's
	for (i = 0; i < len; i++) {
		crc = _crc_xmodem_update(crc, (uint8_t)string[i]);
	}
	return crc;
}

//============================================================================
// Print characters in Hex format
//============================================================================
void PrintHex(uint8_t *data, uint8_t length, char *tmp) {
	// Print char data as hex
	byte first;
	int j = 0;
	for (uint8_t i = 0; i < length; i++) {
		first = ((uint8_t)data[i] >> 4) | 48;
		if (first > 57) tmp[j] = first + (byte)39;
		else tmp[j] = first;
		j++;

		first = ((uint8_t)data[i] & 0x0F) | 48;
		if (first > 57) tmp[j] = first + (byte)39;
		else tmp[j] = first;
		j++;
	}
	tmp[length * 2] = 0;
}

//============================================================================
// Convert a float to a 8 bit two's complement number
// aNumber should be between -127 and 127
//============================================================================
int8_t Decto2compl(float aNumber) {
	// Get a rounded integer
	int8_t dec = round(aNumber);
	if (dec >= -128 && dec <= 127) {
		if (dec >= 0)  // for positive number twocomplement is the same
		{
			toSerialConsole("Temperatuur in 2-comp positief: ");
			toSerialConsole((int8_t)dec);toSerialConsole("\n");
			return dec;
		} else {
			// take abs value
			int8_t absvalue = -dec;
			// Invert the bits
			int8_t oneComplement = ~dec;
			// Add 1
			int8_t twoComplement = oneComplement + 1;
			// return the value
			toSerialConsole("Temperatuur in 2-comp negatief: ");
			toSerialConsole((int8_t)twoComplement);toSerialConsole("\n");
			return (int8_t)twoComplement;
		}
	} else {
		// error
		return 0;
	}
}

//============================================================================
// Evaluate the results of a call to the Radiolib library
// If the call does not succeed, wait 60 seconds, reset the esp32 and try again.
//============================================================================
void Radiolib_assert(int16_t lState) {
	if (lState >= RADIOLIB_ERR_NONE)  // Change this to (state == ERR_NONE) if you use an older radiolib library
	{
		toSerialConsole("done\n");
	} else 
	{
		toSerialConsole("failed, code ");
		toSerialConsole(lState); toSerialConsole("\n");
		delay(60000);
		ESP.restart();
	}
}
