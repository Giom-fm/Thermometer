#pragma once

#include <stdint.h>


#define HUMIDITY_MSB_START 0
#define HUMIDITY_LSB_START 8

#define TEMPERATURE_MSB_START 16
#define TEMPERATURE_LSB_START 24

#define CHECKSUM_START 32
#define WORD_LENGTH 8
#define FACTOR 10.0f
#define NEGATIV_BIT 7

#define STREAM_LENGTH 40

#define START_LOW_DELAY 1100
#define START_HIGH_DELAY 40


// 1ms/(1/F_CPU) = Clock cycles in 1 Ms
#define TIMEOUT_CYCLES 16000

typedef enum DHT22Error {
  OK = 0,
  START_FAILED,
  TIMEOUT,
  CHECKSUM_MISSMATCH

} dht22_error;

typedef enum Level { LOW = 0, HIGH = 1 } level_t;

class DHT22 {
 private:
  uint16_t low_cycles[STREAM_LENGTH];
  uint16_t high_cycles[STREAM_LENGTH];

  const uint8_t data_pin;
  dht22_error start();
  uint16_t get_pulse_length(level_t level);

  uint8_t get_value(const uint8_t from);
  dht22_error get_values(float* temperature, float* humidity);

 public:
  DHT22(uint8_t data_pin);
  dht22_error read(float* temperature, float* humidity);
};