#include <avr/io.h>
#include <util/delay.h>

#include "DHT22.hpp"
#include "Usart.hpp"
#include "Util.hpp"

#define DEBUG 1

uint32_t get_pulse_length(level_t level) {
  uint32_t cycles = 0;

  uint8_t before = IS_BIT_SET(PIND, PD2);
  while ((IS_BIT_SET(PIND, PD2) == level) && cycles < 160000000L) {
    ++cycles;
  }
  // print_ln_debug("E: %u\tLB: %u\tLA: %u\t%u", level, before,
  //  IS_BIT_SET(PIND, PD2), cycles);
  return cycles;
}

int main() {
  Usart::init();
  DHT22 dht22(PD2);
  float temperature, humidity;
  print_ln_debug("Start");
  _delay_ms(2000);

  while (1) {
    dht22_error error = dht22.read(&temperature, &humidity);
    if (error) {
      print_ln_debug("DHT22 Error 0x%X", error);
    } else {
      print_ln_debug("Temperature: %.1f°C\nHumidity: %.1f%%", temperature, humidity);
    }
    _delay_ms(2500);
  }
}
