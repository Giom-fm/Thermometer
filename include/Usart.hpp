#pragma once
#define BAUD 9600

#include <stdio.h>

/**
 * Debug makro that is used to send some data over the USART interface.
 * If DEBUG is false, the code should be optimized by the compiler.
 */
#define print_ln_debug(...) \
  if (DEBUG) Usart::print_ln(__VA_ARGS__)

#define print_debug(...) \
  if (DEBUG) Usart::print(__VA_ARGS__)

class Usart {
 public:
  static void init();
  static void print_ln(const char *s, ...);
  static void print(const char *s, ...);

 private:
  static void print_c(const char c);
};
