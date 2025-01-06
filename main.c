/*
 * main.c
 *
 *  Created on: Dec 30, 2024
 *      Author: Minsig
 */


#include "main.h"

int main(void)
{
  hwInit();
  apInit();

  apMain();

  return 0;
}
