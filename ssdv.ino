//============================================================================
// All SSDV related procedures
//  
//============================================================================
#if defined(USE_SSDV)

#include "camera_pins.h"
#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32
#include "soc/soc.h"           // Brownout preventie
#include "soc/rtc_cntl_reg.h"
#include "ssdv.h"

#define IMG_BUFF_SIZE 128   // size of the buffer feeding SSDV process
#define LORA_BUFFER  255   // size of the lora packet buffer

//============================================================================
// Globals
//============================================================================
uint16_t ssdvPacketCount = 0;
ssdv_t ssdv;
uint16_t imageID = 0;
uint8_t imgBuff[IMG_BUFF_SIZE];
uint8_t loraBuff[LORA_BUFFER + 1];


//============================================================================
// Setup the camera and the SD card
//  
//============================================================================
void setupSSDV() {

  // Camera config
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.frame_size = FRAMESIZE_UXGA; // Resolutie: UXGA (1600x1200)
  config.pixel_format = PIXFORMAT_JPEG; 
  config.grab_mode = CAMERA_GRAB_LATEST;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 10;
  config.fb_count = 2;

  // Camera initialis
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) 
  {
    toSerialConsole("Could not initialized camera error code: 0x");
    toSerialConsole(err);
    toSerialConsole("\n");
    return;
  }
  else
  {
    toSerialConsole("Camera succesfully initialized.\n");
  }

  // SD-card initialise
  if(! SD_MMC.setPins(39, 38, 40))
  {
    toSerialConsole("Could not remap pins for SD-card\n");
    return;
  }


  if(!SD_MMC.begin("/sdcard",true)) 
  {
    toSerialConsole("Could not initialize SD-card\n");
    return;
  }
  else
  {
    toSerialConsole("SD-card succesfully initialized\n");
  }

  // Set all the auto functions for exposure, contrast and brightness, using the internal ISP of the camera
  sensor_t * s = esp_camera_sensor_get();
  s->set_whitebal(s, 1);       // 1 = enable Auto White Balance
  s->set_awb_gain(s, 1);       // 1 = enable AWB Gain
  s->set_wb_mode(s, 0);        // 0 = Auto modus (1=Sunny, 2=Cloudy, enz.)
  s->set_exposure_ctrl(s, 1);  // 1 = enable Auto Exposure Control
  s->set_aec2(s, 1);           // 1 = enable AEC sensor DSP
  s->set_ae_level(s, 0);       // exposure correction: -2 to 2 (0 is standard)
  s->set_gain_ctrl(s, 1);      // 1 = enable Auto Gain Control
  s->set_agc_gain(s, 0);       // 0 tot 30
  s->set_gainceiling(s, (gainceiling_t)0); // 0 = 2x gain, 6 = 128x gain
  // image improvement
  s->set_brightness(s, 0);     // -2 to 2
  s->set_contrast(s, 0);       // -2 to 2
  s->set_saturation(s, 0);     // -2 to 2
  s->set_bpc(s, 1);            // Black Pixel Cancellation
  s->set_wpc(s, 1);            // White Pixel Cancellation
  s->set_raw_gma(s, 1);        // Gamma correctie aan

  if (FLIP_HORIZONTAL)
  {
    s->set_hmirror(s, 1);     
  }
  else
  {
    s->set_hmirror(s, 0);
  }

  if (FLIP_VERTICAL)
  {
    s->set_vflip(s, 1);     
  }
  else
  {
    s->set_vflip(s, 0);
  }


  // CRUCIAL: Give the sensor time to adjust and measure
  delay(1500);
}

//============================================================================
// Take a high res picture and save it to SD
// File name is a combination of Date/Time/Location/Altitude
//============================================================================
void SaveHighResPhoto()
{
  // Get the latest GPS
  processGPSData();
  
  // Set the resolution of the sensor
  sensor_t * s = esp_camera_sensor_get();
  switch(HIGHRES_RESOLUTION)
  {
   case 1: {s->set_framesize(s,FRAMESIZE_UXGA);} break;
   case 2: {s->set_framesize(s,FRAMESIZE_FHD);} break;
   case 3: {s->set_framesize(s,FRAMESIZE_QXGA);} break;
   case 4: {s->set_framesize(s,FRAMESIZE_QHD);} break;
   case 5: {s->set_framesize(s,FRAMESIZE_5MP);} break;
   default: {s->set_framesize(s,FRAMESIZE_UXGA);} break; 
  }
  // Set the JPG quality
  int qual = HIGHRES_QUALITY;
  if ( (qual < 0) || (qual > 63)) {qual = 10;}
  s->set_quality(s,qual);
  
  // Let the sensor stabilize
  delay(1000);

  // Take the picture
  toSerialConsole("Taking High Res picture....");
  camera_fb_t * fb = esp_camera_fb_get();  
  if(!fb) 
  {
    toSerialConsole("Error taking picture\n");
    return;
  }
 
  // Create file name
  // Filename should be: YYDDMM-HHMMSS-longitude-latitude-altitude
  String picture_path = "/";
  picture_path += getTimeLocationString(); 
  picture_path += ".jpg"; 
  fs::FS &fs = SD_MMC;
  File file = fs.open(picture_path.c_str(), FILE_WRITE);  
  if(!file)
  {
    toSerialConsole("Could not open file for writing on SD card\n");
    return;
  }

  // Write the file 
  file.write(fb->buf, fb->len); 
  toSerialConsole("Photo saved: ");
  toSerialConsole(picture_path.c_str());
  toSerialConsole("\n");
  file.close();
  
  // Free the memory
  esp_camera_fb_return(fb);
}


//============================================================================
// Take a low res picture and send it over LoRa
//============================================================================
void TakeandSendLowResPhoto()
{
  // Set the resolution of the sensor 
  // according to what is in settings.h
  sensor_t * s = esp_camera_sensor_get();
  switch(LOWRES_RESOLUTION)
  {
    case 1: {s->set_framesize(s, FRAMESIZE_QVGA);} break;
    case 2: {s->set_framesize(s, FRAMESIZE_VGA);} break;
    case 3: {s->set_framesize(s, FRAMESIZE_SVGA);} break;
    case 4: {s->set_framesize(s, FRAMESIZE_XGA);} break;
    default: {s->set_framesize(s, FRAMESIZE_QVGA);} break;
  }
  // Set the quality always to 10
  s->set_quality(s,10);
  // Let the sensor stabilize
  delay(1000);

  // Take the picture
  toSerialConsole("Taking Low Res picture....");
  camera_fb_t * fb = esp_camera_fb_get();  
  if(!fb) 
  {
    toSerialConsole("Error taking picture\n");
    return;
  }
  toSerialConsole(imageID); toSerialConsole("\n");

  // Process the camera buffer
  process_ssdv(fb);

  // Free the memory
  esp_camera_fb_return(fb);
}

//============================================================================
// Read camera buffer
//============================================================================
int iread(uint8_t *buffer,int numBytes,camera_fb_t *fb, int fbIndex ){
  int bufSize = 0;
  // have we reached past end of imagebuffer
  if((fbIndex + numBytes ) < fb->len) {
    bufSize = numBytes;
  }  else  {
    bufSize = fb->len - fbIndex;
  }
  // clear the dest buffer
  memset(buffer,0,numBytes);
  memcpy(buffer,&fb->buf[fbIndex],bufSize);
  return bufSize;
}

//============================================================================
// Process the camera buffer
//============================================================================
void process_ssdv(camera_fb_t *fb)
{
  int index = 0, c = 0;
  ssdvPacketCount = 0;
  
  // initialise ssdv config structure
  ssdv_enc_init(&ssdv, SSDV_TYPE_NOFEC, CALLSIGN_SSDV, imageID++, LOWRES_QUALITY);
  // set the output lora packet buffer for ssdv where the final ssdv packet will end up
  ssdv_enc_set_buffer(&ssdv, loraBuff);

  while (1)   
  {
    toSerialConsole("Initialize SSDV\n");
    // set the output lora packet buffer for ssdv where the final ssdv packet will end up
    ssdv_enc_set_buffer(&ssdv, loraBuff);
    toSerialConsole("Feeding SSDV\n");
    // Feed the SSDV encoder the image.  Encoder saves it to loraBuff 
    while( (c = ssdv_enc_get_packet(&ssdv)) == SSDV_FEED_ME) 
    {
       // read packet worth of bytes from image buffer
       index += iread(imgBuff, IMG_BUFF_SIZE, fb, index);
       toSerialConsole("Feeding SSDV Encoder, index = ");toSerialConsole(index);toSerialConsole("\n");
       ssdv_enc_feed(&ssdv, imgBuff, IMG_BUFF_SIZE); 
    }

    if(c == SSDV_EOI) 
    {
      toSerialConsole("SSDV End of Image\n");
      break;  // break out of the while loop
    }
    else if(c != SSDV_OK)
    {
      toSerialConsole("ERROR: SSDV Error\n");
      break; // break out of the while loop 
    }

    // move lora data backwards 1 byte This seems needed for pits gateway to read it. (TT7)
    for(uint16_t i = 0; i < 256; i++) 
    {
      loraBuff[i] = loraBuff[i+1]; 
    }

    // Now send the packet over the radio
    toSerialConsole("Transmitting packet: ");
    toSerialConsole(ssdvPacketCount);
    toSerialConsole("\n");
    sendLoRaSSDV();
    // Up the packetcounter
    ssdvPacketCount++;

    // Send a telemetry packet every 25 packets to update location (which is about 1 minute)
    if (ssdvPacketCount % 25 == 0)
    {
      // Check the gps for updated location info
      smartDelay(1000);
      CheckGPS();
      // Print the sensor data
      printSensorData();
      CreateTXLine(LORA_PAYLOAD_ID, LoRaCounter++, LORA_PREFIX);
      sendLoRa(Sentence, LORA_MODE);
    }

    if (ssdvPacketCount > 300) 
    {
      toSerialConsole("ERROR: ssdvPacketCount > 300\n");
      break; // incase we get stuck in this loop, for example when the camera isn't on
    }
  } // while(true)
}

//============================================================================
// Send a LoRa SSDV packet
//============================================================================
void sendLoRaSSDV()
{
   char buf[PACKETLEN]; 
   int j;
   int i;

   // Setup the radio for LoRa mode 1
   SetupLoRa(LORA_MODE);
   // Set the transmit buffer to all zero's
   for (j = 0; j < PACKETLEN; j++) { buf[j] = '\0'; }
   // Fill the transmit buffer with SSDV data
   for (i = 0; i < LORA_BUFFER; i++) { buf[i] = loraBuff[i]; }
   Radiolib_assert(radio.transmit((uint8_t*)buf, PACKETLEN));
}

#endif