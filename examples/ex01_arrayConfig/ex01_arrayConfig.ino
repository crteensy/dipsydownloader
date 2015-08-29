#include <SPI.h>
#include <dipsydownloader.h>

void setup() {
  // open serial monitor, type anything and press return to start config
  while(!Serial.available());
  while(Serial.available()) Serial.read();

  static const uint8_t DIPSY_CRESETB = 0;
  static const uint8_t DIPSY_CDONE = 1;
  static const uint8_t DIPSY_SS = 2;

  SPI.begin();

  extern const uint8_t top_bitmap_bin[];
  extern const uint16_t top_bitmap_bin_len;
  dipsy::ArrayConfig config(top_bitmap_bin_len, top_bitmap_bin);
  if (dipsy::configure(DIPSY_CRESETB, DIPSY_CDONE, DIPSY_SS, SPI, config))
  {
    Serial.print("config done");
  }
  else
  {
    Serial.print("config error");
  }

  SPI.end();

}

void loop() {
}

