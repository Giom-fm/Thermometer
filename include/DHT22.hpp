/**
 * @file DHT22.hpp
 * @author Guillaume Fournier
 * @brief A module to read out a DHT22 sensor via a One-Wire bus.
 * @date 2020-10-24
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include <stdint.h>

/** The length of the data stream in bits sent by the DHT22. */
#define STREAM_LENGTH 40

/** The start bit of the MSB humidity byte. */
#define HUMIDITY_MSB_START 0
/** The start bit of the LSB humidity byte. */
#define HUMIDITY_LSB_START 8

/** The start bit of the MSB temperature byte. */
#define TEMPERATURE_MSB_START 16
/** The start bit of the LSB temperature byte. */
#define TEMPERATURE_LSB_START 24

/** The start bit of the checksum byte. */
#define CHECKSUM_START 32

/** The length of one byte in bits sent by the DHT22. */
#define WORD_LENGTH 8

/** The factor to divide by to get the right result. */
#define FACTOR 10.0f

/** The bit which indicates if the temperature is negative. */
#define NEGATIV_BIT 7

/** The delay for pulling down the start signal in miliseconds. */
#define START_LOW_DELAY 1100
/** The delay for pulling up the start signal in miliseconds. */
#define START_HIGH_DELAY 40

/** The maximum cycles until a timeout error is reached.
 * 1ms/(1/F_CPU) = Clock cycles in 1 Ms
 */
#define TIMEOUT_CYCLES 16000

/**
 * @brief An enum which signals DHT22 errors.
 */
typedef enum DHT22Error {
  OK = 0,
  START_FAILED,
  TIMEOUT,
  CHECKSUM_MISSMATCH
} dht22_error;

/**
 * @brief An enum which represents a pin state
 */
typedef enum Level { LOW = 0, HIGH = 1 } level_t;

/**
 * @brief A class representing a DHT22 sensor.
 * At each read the CPU blocks.
 */
class DHT22 {
 private:  // ##################################################################
  const uint8_t data_pin;
  uint16_t low_cycles[STREAM_LENGTH];
  uint16_t high_cycles[STREAM_LENGTH];

  /**
   * @brief Sends the start signal to the DHT22 and evaluates its response.
   *
   * @return dht22_error The possible error
   */
  dht22_error start();

  /**
   * @brief indicates the number of cpucycles that the data pin is in a certain
   * state.
   *
   * @param level The logic level the pin has.
   * @return uint16_t The number of cpucycles.
   */
  uint16_t get_pulse_length(level_t level);

  /**
   * @brief Encodes the data stream and reads out the temperature and relative
   * humidity.
   *
   * @param temperature The temperature
   * @param humidity The humidity
   * @return dht22_error The possible error
   */
  dht22_error get_values(float* temperature, float* humidity);

  /**
   * @brief Returns one byte of the data stream.
   * Helper of @see get_values.
   *
   * @param from The first bit from wich to start.
   * @return uint8_t The byte from the data stream.
   */
  uint8_t DHT22::get_value(const uint8_t from);

 public:  // ###################################################################
  /**
   * @brief Construct a new DHT22 object.
   *
   * @param data_pin The pin used to communicate with the DHT22.
   */
  DHT22(uint8_t data_pin);

  /**
   * @brief Reads the temperature and relative humidity from the DHT22.
   *
   * @param temperature The temperature
   * @param humidity The humidity
   * @return dht22_error The possible error
   */
  dht22_error read(float* temperature, float* humidity);
};