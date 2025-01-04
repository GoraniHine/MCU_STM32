/*
 * ap.c
 *
 *  Created on: Dec 30, 2024
 *      Author: Minsig
 */


#include "ap.h"

void apInit(void)
{

}

void apMain(void)
{
  while(1)
  {
    ledToggle(_DEF_LED1);
    delay(500);
  }
}
