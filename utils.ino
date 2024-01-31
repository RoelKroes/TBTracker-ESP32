uint16_t _crc_xmodem_update(uint16_t crc, uint8_t data)
{
	unsigned int i;

	crc = crc ^ ((uint16_t)data << 8);
	for (i=0; i<8; i++) {
		if (crc & 0x8000) {
			crc = (crc << 1) ^ 0x1021;
		} else {
			crc <<= 1;
		}
	}
	return crc;
}

// Fast CRC16 code
unsigned int crc16(unsigned char *string, unsigned int len) {
	unsigned int i;
	unsigned int crc;
	crc = 0xFFFF; // Standard CCITT seed for CRC16.
	// Calculate the sum, ignore $ sign's
	for (i = 0; i < len; i++) {
		crc = _crc_xmodem_update(crc,(uint8_t)string[i]);
	}
	return crc;
}


void PrintHex(uint8_t* data, uint8_t length, char *tmp){
 // Print char data as hex
 byte first ;
 int j=0;
 for (uint8_t i=0; i<length; i++) 
 {
   first = ((uint8_t)data[i] >> 4) | 48;
   if (first > 57) tmp[j] = first + (byte)39;
   else tmp[j] = first ;
   j++;

   first = ((uint8_t)data[i] & 0x0F) | 48;
   if (first > 57) tmp[j] = first + (byte)39; 
   else tmp[j] = first;
   j++;
 }
 tmp[length*2] = 0;
}

