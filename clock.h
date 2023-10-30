#ifndef CLOCK_H
#define CLOCK_H

#include "login.h"
#include "map.h"
#include "admin.h"
#include "booking.h"

int Hour = 8;  // Current hour (initialized to 8)
int Day = 0;  // Current day (initialized to 0)

void TimeManager() {
    if (Hour >= 24) {  // Check if hour exceeds 24
        Day += Hour / 24;  // Increment day by the number of days in excess of 24 hours
        Hour = Hour % 24;  // Reset hour to the remaining hours
    }
}

#endif
