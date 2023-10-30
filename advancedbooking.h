#ifndef ADVANCEDBOOKING_H
#define ADVANCEDBOOKING_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "login.h"
#include "map.h"
#include "admin.h"
#include "clock.h"
#include "cabfinder.h"
#include "billing.h"

typedef struct {
    int customerLocation;
    int dropLocation;
    int cabType;
    int requested_day;
    int requested_hour;
} Advanced_Customer_Request;

typedef struct {
    int customerLocation;
    int dropLocation;
    int cabType;
    int allottedCabIndex;
    float rating;
    int requested_day;
    int requested_hour;
    char rideID[LICENSE_ID_LENGTH];
} Advanced_Ride_Details;

// Function to display available locations
void displayAdvancedLocations() {
    printf("Locations:\n");
    for (int i = 0; i < MAX_LOCATIONS; i++) {
        printf("%d. %s\n", i + 1, Locations[i]);
    }
}

// Function to display available cab types
void displayAdvancedCabTypes() {
    printf("Cab Types:\n");
    for (int i = 0; i < numCabTypes; i++) {
        printf("%d. %s\n", i + 1, CabTypes[i]);
    }
}

// Function to display advanced ride details
void displayAdvancedRideDetails(Advanced_Customer_Request ride) {
    printf("Ride Details:\n");
    printf("Customer Location: %s\n", Locations[ride.customerLocation - 1]);
    printf("Drop Location: %s\n", Locations[ride.dropLocation - 1]);
    printf("Preferred Cab Type: %s\n", CabTypes[ride.cabType - 1]);
    printf("Requested day: %d\n", ride.requested_day);
    printf("Requested hour: %d\n", ride.requested_hour);
}

// Function to print cab details for advanced booking
void printAdvancedCabDetails(int cabIndex, int customerLocation) {
    if (cabIndex != -1) {
        printf("Cab Type: %s\n", allCabs[cabIndex].CabType);
        printf("License ID: %s\n", allCabs[cabIndex].LicenseId);
        printf("Current Location: %s\n", allCabs[cabIndex].Current_Location);
        int cabLocationIndex;
        for (int a = 0; a < MAX_LOCATIONS; a++) {
            if (strcmp(allCabs[cabIndex].Current_Location, Locations[a]) == 0) {
                cabLocationIndex = a;
            }
        }
        //printf("Distance from Customer: %d\n", Map[customerLocation][cabLocationIndex]); // Updated line
        printf("Distance from Customer: %d\n", ride_distance); // Updated line
    } else {
        printf("No available cabs found for the given cab type and customer location.\n");
    }
}

// Function to print advanced booking bill
void printAdvancedBookingBill(Advanced_Ride_Details allotment, int distance, char user[MAX_USERNAME_LENGTH]) {
    printf("Customer location: %s\n", Locations[allotment.customerLocation - 1]);
    printf("Drop location: %s\n", Locations[allotment.dropLocation - 1]);
    printf("Driver Rating: %.2f\n", allotment.rating);
    printf("Ride ID: %s\n", allotment.rideID);
    printf("Distance: %d KM\n", distance);
    printf("Booking Day: %d\n", allotment.requested_day);
    printf("Booking Hour: %d\n", allotment.requested_hour);
    printf("Fare: Rs. %.2f\n", calculateFare(distance));
    float price = calculateFare(distance);
    int surge_hour = Surge[allotment.customerLocation][allotment.dropLocation];
    float surge_price;
    if (surge_hour == allotment.requested_hour) {
        surge_price = (price * SURGE_PRICE_PERCENTAGE) / 100;
    } else {
        surge_price = 0;
    }
    printf("Surge Fare: Rs. %.2f\n", surge_price);
    printf("Total Fare: Rs. %.2f\n", price + surge_price);
    printf("Thank you for booking a ride with us, %s!\n", user);
}

// Function to get advanced ride details from the user
Advanced_Customer_Request getAdvancedRideDetails() {
    Advanced_Customer_Request ride;
    do {
        do {
        displayAdvancedLocations();
        printf("Enter Customer Location: ");
        scanf("%d", &ride.customerLocation);
        if (ride.customerLocation >22 || ride.customerLocation<1){
            printf("Please Enter a Valid Location\n");
            printf("\n");
        }
        } while (ride.customerLocation >22 || ride.customerLocation<1);

        do {
        displayAdvancedLocations();
        printf("Enter Drop Location: ");
        scanf("%d", &ride.dropLocation);
        if (ride.dropLocation >22 || ride.dropLocation<1){
            printf("Please Enter a Valid Location\n");
            printf("\n");
        }
        } while (ride.dropLocation >22 || ride.dropLocation<1);
        if (ride.customerLocation == ride.dropLocation){
            printf("The Pickup Location and the Drop Location are the same\n");
            printf("\n");
        }
    } while (ride.customerLocation == ride.dropLocation);

    do {
    displayAdvancedCabTypes();
    printf("Enter Preferred Cab Type: ");
    scanf("%d", &ride.cabType);
    if (ride.cabType > numCabTypes||ride.cabType<1){
        printf("Please Enter a Valid Cab Type\n");
    }
    } while (ride.cabType > numCabTypes||ride.cabType<1);

    printf("Current Time: Day = %d and Hour = %d\n", Day, Hour);
    do {
        printf("Enter the Day: ");
        scanf("%d", &ride.requested_day);
        if (ride.requested_day < Day) {
            printf("Enter a valid input.\n");
        }
    } while (ride.requested_day < Day);

    if (ride.requested_day == Day) {
        do {
            printf("Enter the Hour: ");
            scanf("%d", &ride.requested_hour);
            if (ride.requested_hour < Hour) {
                printf("Enter a valid input.\n");
            }
        } while (ride.requested_hour < Hour);
    } else {
        printf("Enter the Hour: ");
        scanf("%d", &ride.requested_hour);
    }

    return ride;
}

// Function to find shortest path from source to destination
int AdvancedCustomerToDrop(int graph[MAX_LOCATIONS][MAX_LOCATIONS], int src, int dest) {
    int dist[MAX_LOCATIONS];
    int visited[MAX_LOCATIONS] = {0};

    for (int i = 0; i < MAX_LOCATIONS; ++i) {
        dist[i] = INT_MAX;
    }

    dist[src] = 0;

    for (int count = 0; count < MAX_LOCATIONS - 1; ++count) {
        int u, minDist = INT_MAX;

        for (int v = 0; v < MAX_LOCATIONS; ++v) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                u = v;
            }
        }

        visited[u] = 1;

        if (u == dest) {
            return dist[u]; // Found the shortest distance to the destination
        }

        for (int v = 0; v < MAX_LOCATIONS; ++v) {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    return -1; // No path found
}

// Function to update advanced ride details after allotment
Advanced_Ride_Details updateAdvancedRideDetails(Advanced_Customer_Request ride, int cabIndex) {
    Advanced_Ride_Details allotted_ride;
    allotted_ride.customerLocation = ride.customerLocation;
    allotted_ride.dropLocation = ride.dropLocation;
    allotted_ride.cabType = ride.cabType;
    allotted_ride.allottedCabIndex = cabIndex;
    allotted_ride.rating = allCabs[cabIndex].rating;
    strcpy(allCabs[cabIndex].Current_Location, Locations[ride.dropLocation - 1]);
    allotted_ride.requested_day = ride.requested_day;
    allotted_ride.requested_hour = ride.requested_hour;
    generateRideID(allotted_ride.rideID);
    allCabs[cabIndex].isAdvancedBooked = true;
    allCabs[cabIndex].Requested_Day = ride.requested_day;
    AdvancedBookedCabIndices[numAdvancedBookedCab] = cabIndex;
    numAdvancedBookedCab += 1;
    return allotted_ride;
}

// Function to update cab availability based on current day
void updateAvailability() {
    for (int s = 0; s < numAdvancedBookedCab; s++) {
        if (allCabs[AdvancedBookedCabIndices[s]].Requested_Day > Day) {
            allCabs[AdvancedBookedCabIndices[s]].Requested_Day = -1;
            allCabs[AdvancedBookedCabIndices[s]].isAdvancedBooked = false;
            for (int i = s; i < numAdvancedBookedCab - 1; i++) {
                AdvancedBookedCabIndices[i] = AdvancedBookedCabIndices[i + 1];
            }
            numAdvancedBookedCab -= 1;
        } else {
            continue;
        }
    }
}

#endif // ADVANCEDBOOKING_H
