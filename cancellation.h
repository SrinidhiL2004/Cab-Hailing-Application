#ifndef CANCELLATION_H
#define CANCELLATION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "booking.h"
#include "advancedbooking.h"
#include "cabfinder.h"

#define MAX_RIDES 100
#define CANCELLATION_FARE 10

Ride_Details allRides[MAX_RIDES];
int numRides = 0;

Advanced_Ride_Details allAdvancedRides[MAX_RIDES];
int numAdvancedRides = 0;

// Function to cancel a ride based on the ride ID
void cancelRide(char rideID[]) {
    int rideIndex = -1;
    
    // Find the index of the ride with the specified ride ID
    for (int i = 0; i < numRides; i++) {
        if (strcmp(allRides[i].rideID, rideID) == 0) {
            rideIndex = i;
            break;
        }
    }
    
    if (rideIndex != -1) {
        // Remove the ride from the allRides array
        for (int i = rideIndex; i < numRides - 1; i++) {
            allRides[i] = allRides[i + 1];
        }
        
        numRides -= 1;
        printf("Ride with ID %s cancelled.\n", rideID);
        float cancellation_fare = (CANCELLATION_FARE*(CustomerToDrop(Map, allRides[rideIndex].customerLocation - 1,allRides[rideIndex].dropLocation - 1)))/100;
        printf("The Cancellation Fares are %.2f\n",cancellation_fare);
        printf("\n");
    } else {
        printf("Ride with ID %s not found.\n", rideID);
    }
}

// Function to cancel an advanced ride based on the ride ID
void cancelAdvancedRide(char rideID[]) {
    int rideIndex = -1;
    
    // Find the index of the ride with the specified ride ID
    for (int i = 0; i < numAdvancedRides; i++) {
        if (strcmp(allAdvancedRides[i].rideID, rideID) == 0) {
            rideIndex = i;
            break;
        }
    }
    
    if (rideIndex != -1) {
        // Remove the ride from the allRides array
        for (int i = rideIndex; i < numAdvancedRides - 1; i++) {
            allAdvancedRides[i] = allAdvancedRides[i + 1];
        }
        
        numAdvancedRides -= 1;
        printf("Ride with ID %s cancelled.\n", rideID);
        float cancellation_fare = (CANCELLATION_FARE*(CustomerToDrop(Map, allAdvancedRides[rideIndex].customerLocation - 1,allAdvancedRides[rideIndex].dropLocation - 1)))/100;
        printf("The Cancellation Fares are %.2f\n",cancellation_fare);
        printf("\n");
    } else {
        printf("Ride with ID %s not found.\n", rideID);
    }
}

// Function to append a ride to the allRides array
void appendRide(Ride_Details ride) {
    if (numRides < MAX_RIDES) {
        allRides[numRides] = ride;
        numRides++;
        //printf("Ride appended to the array.\n");
    } else {
        printf("Maximum number of rides reached. Cannot append ride.\n");
    }
}

// Function to append an advanced ride to the allAdvancedRides array
void appendAdvancedRide(Advanced_Ride_Details ride) {
    if (numAdvancedRides < MAX_RIDES) {
        allAdvancedRides[numAdvancedRides] = ride;
        numAdvancedRides++;
       // printf("Ride appended to the array.\n");
    } else {
        printf("Maximum number of rides reached. Cannot append ride.\n");
    }
}

void printAllRides() {
    if (numRides == 0) {
        printf("No rides available.\n");
        return;
    }
    
    printf("All Regular Rides:\n\n");
    for (int i = 0; i < numRides; i++) {
        printf("Ride ID: %s\n", allRides[i].rideID);
        printf("Customer Location: %s\n", Locations[allRides[i].customerLocation - 1]);
        printf("Drop Location: %s\n", Locations[allRides[i].dropLocation - 1]);
        printf("Cab Type: %s\n", CabTypes[allRides[i].cabType - 1]);
        printf("Allotted Cab Index: %d\n", allRides[i].allottedCabIndex);
        printf("Rating: %.2f\n", allRides[i].rating);
        printf("Status: Completed\n");
        printf("\n");
    }
}

void printAllAdvancedRides() {
    if (numAdvancedRides == 0) {
        printf("No advanced rides available.\n");
        return;
    }
    
    printf("All Advanced Rides:\n");
    for (int i = 0; i < numAdvancedRides; i++) {
        printf("Ride ID: %s\n", allAdvancedRides[i].rideID);
        printf("Customer Location: %s\n", Locations[allAdvancedRides[i].customerLocation - 1]);
        printf("Drop Location: %s\n", Locations[allAdvancedRides[i].dropLocation - 1]);
        printf("Cab Type: %s\n", CabTypes[allAdvancedRides[i].cabType - 1]);
        printf("Allotted Cab Index: %d\n", allAdvancedRides[i].allottedCabIndex);
        printf("Rating: %.2f\n", allAdvancedRides[i].rating);
        printf("Requested Day: %d\n", allAdvancedRides[i].requested_day);
        printf("Requested Hour: %d\n", allAdvancedRides[i].requested_hour);
        printf("\n");
    }
}

#endif // CANCELLATION_H
