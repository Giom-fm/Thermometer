#include <avr/io.h>
#include <util/delay.h>

#include "DHT22.hpp"
#include "Usart.hpp"
#include "Util.hpp"

#define DEBUG 1

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
