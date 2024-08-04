#ifndef BILLING_H
#define BILLING_H

#define BASE_FARE 100
#define PER_KM_FARE 13.50

// Function to calculate the fare based on the distance
float calculateFare(int distance){
  float price = 0.0;
  price += BASE_FARE;
  float distance_fare = distance * PER_KM_FARE;
  price += distance_fare;
  return price;
}

#endif // BILLING_H
