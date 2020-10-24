/**
 * @file Usart.hpp
 * @author Guillaume Fournier
 * @brief A Module used to print some Characters via Uart
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

/** Set BAUD raute to 9600 */
#define BAUD 9600

#include <stdio.h>

/**
 * @brief Debug makro that is used to send some data over the USART interface.
 * An addition "New Line" is added at the end of the string
 * If DEBUG is false, the code should be optimized by the compiler.
 */
#define print_ln_debug(...) \
  if (DEBUG) Usart::print_ln(__VA_ARGS__)

/**
 * @brief Debug makro that is used to send some data over the USART interface.
 * If DEBUG is false, the code should be optimized by the compiler.
 */
#define print_debug(...) \
  if (DEBUG) Usart::print(__VA_ARGS__)

/**
 * @brief The static class to print some characters to Uart.
 * This class works in a blocking way
 */
class Usart {
 public:
  /**
   * @brief Initialises the Uart interface as transmitter
   */
  static void init();

  /**
   * @brief Sends a character string via the UART interface.
   * Sends an additional "\n\r".
   *
   * @param s The string to be sent
   * @param ... The values to be included in the string
   */
  static void print_ln(const char *s, ...);

   /**
   * @brief Sends a character string via the UART interface.
   *
   * @param s The string to be sent
   * @param ... The values to be included in the string
   */
  static void print(const char *s, ...);

 private:

 /**
  * @brief Sends a single character via the Uart interface
  * 
  * @param c The character to be sent
  */
  static void print_c(const char c);
};
