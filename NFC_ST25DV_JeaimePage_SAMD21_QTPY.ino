/**
 ******************************************************************************
 * @file    NFC_ST25DV_JeaimePage_SAMD21_QTPY
 * @modified author  Je'aime Powell
 * @version V1.0.0
 * @date    27 February 2023
 * @brief   Arduino application for the Adafruit QT PY (SAMD21) and ST25DV NFC devices.
 *            Adds the jeaimehp.github.io url to the nfc device via I2C
 *          This application makes use of C++ classes obtained from the C
 *          components' drivers.
 ******************************************************************************
 * Referenced Source Code and Library app: https://github.com/stm32duino/ST25DV/examples 
 * Referenced Tutorial Video: https://www.youtube.com/watch?v=Jn-yGtRi_gs&t
 ******************************************************************************
 */
/**
******************************************************************************
* How to use this sketch
*
* This sketch uses the I2C interface to communicate with the NFC device.
* It writes an NFC tag type URI (Uniform Resource Identifier) and reads this same tag.
* Choose the uri by changing the content of uri_write.
*
* When the NFC module is started and ready, the message "Sytstem init done!" is
* displayed on the monitor window. Next, the tag is written, read and printed on
* the monitor window.
*
* You can also use your smartphone to read/write a tag.
* On Android, download a NFC Tools. Then start the app, check if NFC is activated
* on your smartphone. Put your smartphone near the tag, you can read it. You can
* write a tag with this app.
******************************************************************************
*/
 
#include "ST25DVSensor.h"

#define SerialPort      Serial

#define GPO_PIN 4 //QTPY GPIO 4 PA16 SDA
#define LPD_PIN 5 //QTPY GPIO 5 PA17 SCL



void setup() {
  const char uri_write_message[] = "jeaimehp.github.io/";       // Uri message to write in the tag
  const char uri_write_protocol[] = URI_ID_0x04_STRING; // Uri protocol to write in the tag https 04
  // ref: https://old.gototags.com/nfc/ndef/uri/ for the write protocols
  /**********************************
  URI PREFIX	BYTE VALUE
    none	0x00
    httpwww	0x01
    httpswww	0x02
    http	0x03
    https	0x04 <--
    tel	0x05
    mailto	0x06
    ftpanonymousanonymous	0x07
    ftp_ftp	0x08
    ftps	0x09
    sftp	0x0A
    smb	0x0B
    nfs	0x0C
    ftp	0x0D
    dav	0x0E
    news	0x0F
    telnet	0x10
    imap	0x11
    rtsp	0x12
    urn	0x13
    pop	0x14
    sip	0x15
    sips	0x16
    tftp	0x17
    btspp	0x18
    btl2cap	0x19
    btgoep	0x1A
    tcpobex	0x1B
    irdaobex	0x1C
    file	0x1D
    urnepcid	0x1E
    urnepctag	0x1F
    urnepcpat	0x20
    urnepcraw	0x21
    urnepc	0x22
    urnnfc	0x23
**************************************/

  String uri_write = String(uri_write_protocol) + String(uri_write_message);
  String uri_read;

  // Initialize serial for output.
  SerialPort.begin(115200);

  // The wire instance used can be omited in case you use default Wire instance
  if(st25dv.begin(GPO_PIN, LPD_PIN, &Wire) == 0) {
    SerialPort.println("System Init done!");
  } else {
    SerialPort.println("System Init failed!");
    while(1);
  }

  if(st25dv.writeURI(uri_write_protocol, uri_write_message, "")) {
    SerialPort.println("Write failed!");
    while(1);
  }

  delay(100);
  
  if(st25dv.readURI(&uri_read)) {
    SerialPort.println("Read failed!");
    while(1);
  }

  SerialPort.println(uri_read.c_str());

  if(strcmp(uri_read.c_str(), uri_write.c_str()) == 0) {
    SerialPort.println("Successfully written and read!");
  } else {
    SerialPort.println("Read bad string!");
  }
}

void loop() {  
  //empty loop
} 
