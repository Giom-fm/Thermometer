/**
 * @file Usart.cpp
 * @author Guillaume Fournier
 * @brief A Module used to print some Characters via Uart
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "Usart.hpp"

#include <avr/io.h>
#include <stdarg.h>
#include <stdio.h>
#include <util/setbaud.h>

/** The buffer size used for sending */
#define BUFFER_SIZE 50

/**
 * @brief Initialises the Uart interface as transmitter.
 * Data Framefort is set to 8 Bit data plus 1 Stopbit.
 * Sends an additional "new line".
 */
void Usart::init() {
  /** Enable UART Transmitter mode */
  UCSR0B |= (1 << TXEN0);
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
#if USE_2X
  UCSR0A |= (1 << U2X0);
#else
  UCSR0A &= ~(1 << U2X0);
#endif

  /** Set Frame format to 8 data with 1 stop bits */
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

  /** Sends a "new Line" */
  Usart::print_c('\r');
  Usart::print_c('\n');
}

void Usart::print_ln(const char *s, ...) {
  char buffer[BUFFER_SIZE];
  char *buffer_ptr = buffer;
  va_list args;
  va_start(args, s);
  vsprintf(buffer, s, args);
  va_end(args);

  while (*buffer_ptr) {
    Usart::print_c(*buffer_ptr);
    ++buffer_ptr;
  }

  /** Sends a "new Line" */
  Usart::print_c('\r');
  Usart::print_c('\n');
}

void Usart::print(const char *s, ...) {
  char buffer[BUFFER_SIZE];
  char *buffer_ptr = buffer;
  va_list args;
  va_start(args, s);
  vsprintf(buffer, s, args);
  va_end(args);

  while (*buffer_ptr) {
    Usart::print_c(*buffer_ptr);
    ++buffer_ptr;
  }
}

/**
 * @brief Blocks until buffer is empty and sends the passed character.
 */
void Usart::print_c(const char c) {
  // Wait until UART Data Register is empty
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  // Set Character into Data Register
  UDR0 = c;
}