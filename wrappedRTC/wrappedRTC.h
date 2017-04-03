/*
 * wrappedRTC.h
 *
 *  Created on: Aug 1, 2015
 *      Author: Dinh
 */

/*
 * This makes use of the hibernation module RTC
 * because it is easier to set up.
 */
#ifndef COINHUTAODACHET_WRAPPEDRTC_WRAPPEDRTC_H_
#define COINHUTAODACHET_WRAPPEDRTC_WRAPPEDRTC_H_

#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include "driverlib/sysctl.h"
#include "driverlib/hibernate.h"

void setUpRTC();

#endif /* COINHUTAODACHET_WRAPPEDRTC_WRAPPEDRTC_H_ */
