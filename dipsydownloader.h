#ifndef DIPSYDUINO_H
#define DIPSYDUINO_H

#include <SPI.h>

namespace dipsy
{
struct ArrayConfig
{
  ArrayConfig(const size_t size, const uint8_t* data) : size_(size), pData_(data)
  {
    reset();
  }
  void reset()
  {
    i_ = 0;
  }
  bool get(uint8_t* dest)
  {
    if(i_ < size_)
    {
      *dest = pData_[i_];
      i_++;
      return true;
    }
    else
    {
      return false;
    }
  }
  size_t size_;
  const uint8_t* const pData_;
  size_t i_;
};
template <typename spi_type, typename config_type>
bool configure(int creset_pin, int cdone_pin, int ss_pin, spi_type& spi, config_type& configObject)
{
  pinMode(creset_pin, OUTPUT);
  pinMode(cdone_pin, INPUT_PULLUP);
  pinMode(ss_pin, OUTPUT);

  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE3));

  digitalWriteFast(creset_pin, 0);
  digitalWriteFast(ss_pin, 0);
  delay(2);
  digitalWriteFast(creset_pin, 1);
  delay(2);

  uint8_t data;
  configObject.reset();
  while(configObject.get(&data))
  {
    SPI.transfer(data);
  }
  bool done = digitalReadFast(cdone_pin);
  for(uint8_t i = 0; i < (49/8 + 1); i++)
  {
    SPI.transfer(0x00);
  }
  digitalWriteFast(ss_pin, 1);

  // pinMode(creset_pin, INPUT); removed: issue #1
  pinMode(cdone_pin, INPUT);
  pinMode(ss_pin, INPUT);

  SPI.endTransaction();

  return done;
}
}

#endif // DIPSYDUINO_H

