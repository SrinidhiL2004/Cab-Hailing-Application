#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#ifdef _WIN32
#include <windows.h> // For Windows API functions
#include <conio.h>   // For password input without echoing
#endif

#include "cancellation.h"
#include "booking.h"
#include "billing.h"
#include "advancedbooking.h"

// Define color constants
#define GREEN_TEXT 10
#define RED_TEXT 12
#define YELLOW_TEXT 14
#define WHITE_TEXT 15

#ifdef _WIN32
// Function to set console text color with border formatting for Windows
void setConsoleColor(int color, int border_color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
#else
// Function to set console text color with border formatting for non-Windows (placeholder function)
void setConsoleColor(int color, int border_color) {
    // Placeholder function for non-Windows platforms
    // You can define the appropriate color handling for non-Windows systems here
}
#endif

// Function to print a border with a given width
void printBorder(int width, char border_char) {
    for (int i = 0; i < width; i++) {
        printf("%c", border_char);
    }
}

// Function to read a password securely with masking
void readPassword(char* password, int max_length) {
#ifdef _WIN32
    int index = 0;
    char ch;
    while (1) {
        ch = _getch(); // Read a character without echoing it
        if (ch == 13) { // Check for Enter key
            break;
        } else if (ch == 8 && index > 0) { // Check for Backspace key
            printf("\b \b"); // Move the cursor back, print space to erase the character, move back again
            index--;
        } else if (ch >= 32 && ch <= 126 && index < max_length - 1) { // Check for printable ASCII characters
            password[index++] = ch;
            printf("*"); // Print '*' to mask the input
        }
    }
    password[index] = '\0'; // Null-terminate the password string
#else
    // Placeholder function for non-Windows platforms
    // You can define the appropriate password input handling for non-Windows systems here
    fgets(password, max_length, stdin);
    password[strcspn(password, "\n")] = 0; // Remove the newline character from the input
#endif
}

int main() {
    // Default admin user
    User admin;
    strcpy(admin.username, "Admin");
    strcpy(admin.password, "Sundaresh@143");
    users[userCount++] = admin;
     int flag=0; //flag variable to check if cab network is used or not
    int option;
    int admin_option;
    int user_option;
    int cancel_option;

    do {
        setConsoleColor(WHITE_TEXT, WHITE_TEXT);
        printBorder(40, '-');
        printf("\n");
        setConsoleColor(YELLOW_TEXT, WHITE_TEXT);
        printf("| 1. Signup                      |\n");
        printf("| 2. Login                       |\n");
        printf("| 3. Exit                        |\n");
        setConsoleColor(WHITE_TEXT, WHITE_TEXT);
        printBorder(40, '-');
        printf("\nEnter an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1: {
                signup();
                Hour += 1;
                TimeManager();
                break;
            }
            case 2: {
                if (Login()) {
                    setConsoleColor(GREEN_TEXT, WHITE_TEXT);
                    printBorder(35, '-');
                    printf("\n| Login successful!            |\n");
                    printBorder(35, '-');
                    printf("\n");
                    setConsoleColor(WHITE_TEXT, WHITE_TEXT);
                    if (strcmp("Admin", current_user) == 0) {
                        do {
                            printBorder(43, '-');
                            printf("\n");
                            printf("| Cab Hailing Application - Admin Portal |\n");
                            printf("|   1. Create Cab Network                |\n");
                            printf("|   2. Use Default Network               |\n");
                            printf("|   3. See All Bookings                  |\n");
                            printf("|   4. See All Advance Bookings          |\n");
                            printf("|   5. Log Out                           |\n");
                            printBorder(43, '-');
                            printf("\n");
                            printf("Enter an option: ");
                            scanf("%d", &admin_option);
                            switch (admin_option) {
                                case 1: {
                                    generateCabSystem();
                                    flag=1;
                                    storeCabInformationToFile();
                                    Hour += 2;
                                    TimeManager();
                                    break;
                                }
                                case 2: {
                                    readCabInformationFromFile(); flag=1;
                                    printf("Default Network Loaded Successfully\n");
                                    Hour += 2;
                                    TimeManager();
                                    break;
                                }
                                case 3: {
                                    printAllRides();
                                    Hour += 2;
                                    TimeManager();
                                    break;
                                }
                                case 4: {
                                    printAllAdvancedRides();
                                    Hour += 2;
                                    TimeManager();
                                    break;
                                }
                                case 5: {
                                    Day += 1;
                                    TimeManager();
                                    break;
                                }
                                default: {
                                    printf("Invalid option. Please try again.\n");
                                }
                            }
                        } while (admin_option != 5);
                    } else {
                        do { if(!flag)
                             {printf("No cab network is created\n");
                               break;
                              }
                            printBorder(43, '-');
                            printf("\n");
                            printf("| Cab Hailing Application - User Portal   |\n");
                            printf("|   1. Booking                            |\n");
                            printf("|   2. Advanced Booking                   |\n");
                            printf("|   3. Cancel a Ride                      |\n");
                            printf("|   4. Exit                               |\n");
                            printBorder(43, '-');
                            printf("\n");
                            printf("Enter an option: ");
                            scanf("%d", &user_option);
                            switch (user_option) {
                                case 1: {
                                    updateAvailability();
                                    Customer_Request Ride = getRideDetails();
                                    int customerLocation, cabType, dropLocation;
                                    customerLocation = Ride.customerLocation - 1;
                                    dropLocation = Ride.dropLocation - 1;
                                    cabType = Ride.cabType;
                                    printf("\n");
                                    displayRideDetails(Ride);
                                    printf("\n");

                                    int nearestCabIndex = getNearestCab(customerLocation, cabType);
                                    printCabDetails(nearestCabIndex, customerLocation);
                                    printf("\n");

                                    if (nearestCabIndex != -1) {
                                        Ride_Details allotment = updateRideDetails(Ride, nearestCabIndex);
                                        appendRide(allotment);
                                        int distance = CustomerToDrop(Map, customerLocation, dropLocation);
                                        printf("The Distance between the Customer Location and the Drop Location is %d\n", distance);
                                        printf("\n");
                                        printBookingBill(allotment, distance, current_user);
                                        printf("\n");
                                        float predefinedRating = 4.5;  // Predefined rating for the driver
                                        float userRating = rateDriver();  // User's rating

                                        // Update the driver's rating based on predefined and user ratings
                                        float updatedRating = (predefinedRating + userRating) / 2;
                                        allCabs[allotment.allottedCabIndex].rating = updatedRating;
                                    } else {
                                        printf("No available cabs found for the given cab type and customer location.\n");
                                    }
                                    
                                    Hour += 3;
                                    TimeManager();
                                    break;
                                }
                                case 2: {
                                    updateAvailability();
                                    Advanced_Customer_Request Ride = getAdvancedRideDetails();
                                    int customerLocation, cabType, dropLocation;
                                    customerLocation = Ride.customerLocation - 1;
                                    dropLocation = Ride.dropLocation - 1;
                                    cabType = Ride.cabType;
                                    printf("\n");
                                    displayAdvancedRideDetails(Ride);
                                    printf("\n");

                                    int nearestCabIndex = getNearestCab(customerLocation, cabType);
                                    printCabDetails(nearestCabIndex, customerLocation);
                                    printf("\n");

                                    if (nearestCabIndex != -1) {
                                        Advanced_Ride_Details allotment = updateAdvancedRideDetails(Ride, nearestCabIndex);
                                        appendAdvancedRide(allotment);
                                        int distance = CustomerToDrop(Map, customerLocation, dropLocation);
                                        printf("The Distance between the Customer Location and the Drop Location is %d\n", distance);
                                        printf("\n");
                                        printAdvancedBookingBill(allotment, distance, current_user);
                                        printf("\n");
                                        float predefinedRating = 4.5;  // Predefined rating for the driver
                                        float userRating = rateDriver();  // User's rating

                                        // Update the driver's rating based on predefined and user ratings
                                        float updatedRating = (predefinedRating + userRating) / 2;
                                        allCabs[allotment.allottedCabIndex].rating = updatedRating;
                                    } else {
                                        printf("No available cabs found for the given cab type and customer location.\n");
                                    }

                                    Hour += 3;
                                    TimeManager();
                                    break;
                                }
                                case 3: {
                                    do {
                                        printf("\n");
                                        printf("| Cab Hailing Application - User Cancellation Portal |\n");
                                        printf("|   1. Booking Cancellation                          |\n");
                                        printf("|   2. Advanced Booking Cancellation                 |\n");
                                        printf("|   3. Exit                                          |\n");
                                        printBorder(43, '-');
                                        printf("\n");
                                        printf("Enter an option: ");
                                        scanf("%d", &cancel_option);
                                        switch (cancel_option) {
                                            case 1: {
                                                printf("Enter the ID of the Ride you want to cancel: ");
                                                char rideID[9];
                                                scanf("%s", rideID);
                                                cancelRide(rideID);
                                                Hour += 4;
                                                TimeManager();
                                                break;
                                            }
                                            case 2: {
                                                printf("Enter the ID of the Ride you want to cancel: ");
                                                char rideID[9];
                                                scanf("%s", rideID);
                                                cancelAdvancedRide(rideID);
                                                Hour += 4;
                                                TimeManager();
                                                break;
                                            }
                                            case 3: {
                                                printf("Exiting...\n");
                                                Day += 1;
                                                TimeManager();
                                                break;
                                            }
                                            default: {
                                                printf("Invalid option. Please try again.\n");
                                            }
                                        }
                                    } while (cancel_option != 3);
                                    
                                    break;
                                }
                                case 4: {
                                    printf("Exiting...\n");
                                    Day += 1;
                                    TimeManager();
                                    break;
                                }
                                default: {
                                    printf("Invalid option. Please try again.\n");
                                }
                            }
                        } while (user_option != 4);
                    }
                } else {
                    setConsoleColor(RED_TEXT, WHITE_TEXT);
                    printBorder(46, '-');
                    printf("\n| Login failed. Invalid username or password. |\n");
                    printBorder(46, '-');
                    printf("\n");
                    setConsoleColor(WHITE_TEXT, WHITE_TEXT);
                }
                break;
            }
            case 3: {
                setConsoleColor(YELLOW_TEXT, WHITE_TEXT);
                printf("| Thank you for using our application!           |\n");
                printBorder(46, '-');
                printf("\n");
                setConsoleColor(WHITE_TEXT, WHITE_TEXT);
                break;
            }
            default: {
                setConsoleColor(RED_TEXT, WHITE_TEXT);
                printBorder(40, '-');
                printf("\n| Invalid option. Please try again.              |\n");
                printBorder(40, '-');
                printf("\n");
                setConsoleColor(WHITE_TEXT, WHITE_TEXT);
            }
        }
    } while (option != 3);

    return 0;
}
