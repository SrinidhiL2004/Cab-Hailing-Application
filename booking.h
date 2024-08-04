#ifndef BOOKING_H
#define BOOKING_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "login.h"
#include "map.h"
#include "admin.h"
#include "clock.h"
#include "cabfinder.h"
#include "billing.h"

#define SURGE_PRICE_PERCENTAGE 10

typedef struct {
    int customerLocation;
    int dropLocation;
    int cabType;
} Customer_Request;

typedef struct {
    int customerLocation;
    int dropLocation;
    int cabType;
    int allottedCabIndex;
    float rating;
    char rideID[LICENSE_ID_LENGTH];
} Ride_Details;

// Function to display available locations
void displayLocations() {
    printf("Locations:\n");
    for (int i = 0; i < MAX_LOCATIONS; i++) {
        printf("%d. %s\n", i + 1, Locations[i]);
    }
}

// Function to display available cab types
void displayCabTypes() {
    printf("Cab Types:\n");
    for (int i = 0; i < numCabTypes; i++) {
        printf("%d. %s\n", i + 1, CabTypes[i]);
    }
}

// Function to display ride details
void displayRideDetails(Customer_Request ride) {
    printf("Ride Details:\n");
    printf("Customer Location: %s\n", Locations[ride.customerLocation - 1]);
    printf("Drop Location: %s\n", Locations[ride.dropLocation - 1]);
    printf("Preferred Cab Type: %s\n", CabTypes[ride.cabType - 1]);
}

// Function to print cab details
void printCabDetails(int cabIndex, int customerLocation) {
    if (cabIndex != -1) {
        printf("Cab Type: %s\n", allCabs[cabIndex].CabType);
        printf("License ID: %s\n", allCabs[cabIndex].LicenseId);
        printf("Current Location: %s\n", allCabs[cabIndex].Current_Location);
        int cabLocationIndex;
        for (int a = 0; a < MAX_LOCATIONS; a++){
            if (strcmp(allCabs[cabIndex].Current_Location, Locations[a])==0){
                cabLocationIndex = a;
            }
        }
        printf("Distance from Customer: %d\n", ride_distance);
    } else {
        printf("No available cabs found for the given cab type and customer location.\n");
    }
}

// Function to print booking bill
void printBookingBill (Ride_Details allotment, int distance, char user[MAX_USERNAME_LENGTH]){
  printf("Customer location: %s\n", Locations[allotment.customerLocation - 1]);
  printf("Drop location: %s\n",Locations[allotment.dropLocation - 1]);
  printf("Driver Rating: %.2f\n", allotment.rating);
  printf("Ride ID: %s\n",allotment.rideID);
  printf("Distance: %d KM\n",distance);
  printf("Fare: Rs. %.2f\n",calculateFare(distance));
  float price = calculateFare(distance);
  int surge_hour = Surge[allotment.customerLocation][allotment.dropLocation];
  float surge_price;
  if (surge_hour == Hour) {
    surge_price = (price*SURGE_PRICE_PERCENTAGE)/100;
  } else {
    surge_price = 0;
  }
  printf("Surge Fare: Rs. %.2f\n",surge_price);
  printf("Total Fare: Rs. %.2f\n",price+surge_price);
  printf("Thank you for booking a ride with us!! %s\n",user);
}

// Function to get ride details from the user
Customer_Request getRideDetails() {
    Customer_Request ride;
    do {
        do {
        displayLocations();
        printf("Enter Customer Location: ");
        scanf("%d", &ride.customerLocation);
        if (ride.customerLocation >22 || ride.customerLocation<1){
            printf("Please Enter a Valid Location\n");
            printf("\n");
        }
        } while (ride.customerLocation >22 || ride.customerLocation<1);

        do {
        displayLocations();
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
    }while (ride.customerLocation == ride.dropLocation);

    do {
    displayCabTypes();
    printf("Enter Preferred Cab Type: ");
    scanf("%d", &ride.cabType);
    if (ride.cabType > numCabTypes||ride.cabType<1){
        printf("Please Enter a Valid Cab Type\n");
    }
    } while (ride.cabType > numCabTypes||ride.cabType<1);

    return ride;
}

// Function to calculate shortest distance from source to destination
int CustomerToDrop(int graph[MAX_LOCATIONS][MAX_LOCATIONS], int src, int dest) {
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

// Function to generate a random ride ID
void generateRideID(char *rideID) {
    const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;
    for (i = 0; i < LICENSE_ID_LENGTH - 1; i++) {
        rideID[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    rideID[i] = '\0';
} 

// Function to update ride details after cab allocation
Ride_Details updateRideDetails (Customer_Request ride, int cabIndex) {
    Ride_Details allotted_ride;
    allotted_ride.customerLocation = ride.customerLocation;
    allotted_ride.dropLocation = ride.dropLocation;
    allotted_ride.cabType = ride.cabType;
    allotted_ride.allottedCabIndex = cabIndex;
    allotted_ride.rating = allCabs[cabIndex].rating;
    strcpy(allCabs[cabIndex].Current_Location, Locations[ride.dropLocation - 1]);
    generateRideID(allotted_ride.rideID);
    return allotted_ride;
}

// Function to rate the driver
float rateDriver() {
    float rating;
    printf("Please rate your driver (from 1 to 5): ");
    scanf("%f", &rating);

    if (rating < 1 || rating > 5) {
        printf("Invalid rating. Please rate between 1 and 5.\n");
        rating = rateDriver();
    }

    return rating;
}

#endif // BOOKING_H
