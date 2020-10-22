#include "DHT22.hpp"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "Usart.hpp"
#include "Util.hpp"

#define DEBUG 1

DHT22::DHT22(uint8_t data_pin) : data_pin(data_pin) {
  DDRD |= (1 << this->data_pin);
  PORTD |= (1 << this->data_pin);

  for (uint8_t i = 0; i < STREAM_LENGTH; ++i) {
    this->low_cycles[i] = 0;
    this->high_cycles[i] = 0;
  }
}

dht22_error DHT22::start() {
  // Pull low for 1100us
  DDRD |= (1 << this->data_pin);
  PORTD &= ~(1 << this->data_pin);
  _delay_us(START_LOW_DELAY);
  // Pull up for 40us
  PORTD |= (1 << this->data_pin);
  _delay_us(START_HIGH_DELAY);

  // Check Acknowledge
  DDRD &= ~(1 << this->data_pin);
  PORTD &= ~(1 << this->data_pin);

  dht22_error error = DHT22Error::OK;

  if (this->get_pulse_length(Level::LOW) >= TIMEOUT_CYCLES) {
    print_ln_debug("Timeout waiting for Lowpulse");
    error = DHT22Error::START_FAILED;
  }

  if (this->get_pulse_length(Level::HIGH) >= TIMEOUT_CYCLES) {
    print_ln_debug("Timeout waiting for Highpulse");
    error = DHT22Error::START_FAILED;
  }

  return error;
}

uint16_t DHT22::get_pulse_length(level_t level) {
  uint16_t cycles = 0;

  while ((IS_BIT_SET(PIND, this->data_pin) == level) &&
         cycles < TIMEOUT_CYCLES) {
    ++cycles;
  }

  return cycles;
}

uint8_t DHT22::get_value(const uint8_t from) {
  uint8_t value = 0;
  const uint8_t to = from + WORD_LENGTH;
  for (uint8_t i = from; i < to; ++i) {
    value <<= 1;
    if (this->low_cycles[i] < this->high_cycles[i]) {
      value |= 1;
    }
  }
  return value;
}

// TODO check 1 Bit of Temp for negativ temperature
dht22_error DHT22::get_values(float* temperature, float* humidity) {
  uint8_t temperature_lsb, temperature_msb, humidity_lsb, humidity_msb,
      checksum, compare_sum;

  humidity_msb = this->get_value(HUMIDITY_MSB_START);
  humidity_lsb = this->get_value(HUMIDITY_LSB_START);
  temperature_msb = this->get_value(TEMPERATURE_MSB_START);
  temperature_lsb = this->get_value(TEMPERATURE_LSB_START);
  checksum = this->get_value(CHECKSUM_START);
  compare_sum = humidity_lsb + humidity_msb + temperature_lsb + temperature_msb;

  if (checksum != compare_sum) return DHT22Error::CHECKSUM_MISSMATCH;

  *temperature = (((uint16_t)temperature_msb << 8) | temperature_lsb) / FACTOR;
  *humidity = (((uint16_t)humidity_msb << 8) | humidity_lsb) / FACTOR;

  return DHT22Error::OK;
}

dht22_error DHT22::read(float* temperature, float* humidity) {
  cli();
  dht22_error error = DHT22Error::OK;
  error = this->start();

  if (!error) {
    uint8_t i = 0;

    // FIXME change to while
    do {
      this->low_cycles[i] = this->get_pulse_length(LOW);
      this->high_cycles[i] = this->get_pulse_length(HIGH);
      ++i;
    } while (i < STREAM_LENGTH && this->low_cycles[i - 1] < TIMEOUT_CYCLES &&
             this->high_cycles[i - 1] < TIMEOUT_CYCLES);

    if (i < STREAM_LENGTH) {
      error = DHT22Error::TIMEOUT;
    } else {
      this->get_values(temperature, humidity);
    }
  }
  sei();
  return error;
}