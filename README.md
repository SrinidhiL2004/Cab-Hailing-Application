# Cab-Hailing Application

This project implements a basic cab-hailing system using Dijkstra's Algorithm to allocate cabs to customers. Built in C, this project was developed as an early exercise to gain proficiency in C programming and basic algorithms.

## Overview

The application includes several modules and features:

### Fixed Cab Database

- **Drivers:** Information about cab drivers.
- **Vehicles:** Details on different vehicles.
- **Default Location:** Standard starting points for cabs.
- **Ratings:** Driver ratings and reviews.

### Fixed Map Database

- **Locations:** Various locations on the map.
- **Distances:** Distances between locations.
- **Surge Times:** Surge pricing information for different routes.

### User Input Interface

Provides options to switch between services:
- **Advanced Booking:** Reserve cabs for future dates.
- **Cancellation:** Cancel trips using the trip ID.
- **Normal Booking:** Book cabs based on current availability.

### Booking Module

Books cabs for users based on the availability of drivers as determined by the Cab Finder Module.

### Advanced Booking

Reserves cabs for users based on their requested time periods and driver availability.

### Cancellation Module

Handles the cancellation of trips with reference to the trip ID.

### Dynamic Location Tracker

Monitors and updates the current location of drivers and their availability status.

### Advanced Availability Checker

Calculates driver availability based on ongoing trips and future requests.

### Trips Manager

Maintains information about ongoing trips in the system.

### Availability Updater

Updates the database with the availability status of cabs after a booking or cancellation.

### Cab Finder Wizard

Filters and identifies the best available cab options according to user preferences.

### Bill Generator

Generates and provides a bill for the user based on booked or canceled trips.


