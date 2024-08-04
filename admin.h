#ifndef ADMIN_H
#define ADMIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "map.h"

#define MAX_CAB_TYPES 10
#define LICENSE_ID_LENGTH 9

typedef struct {
    char CabType[20];
    char LicenseId[LICENSE_ID_LENGTH];
    char Default_Location[20];
    char Current_Location[20];
    float rating;
    bool isAdvancedBooked;
    int Requested_Day;
} Cab;

int AdvancedBookedCabIndices[100];
int numAdvancedBookedCab = 0;

// Function to generate a random license ID
void generateLicenseId(char *licenseId) {
    const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;
    for (i = 0; i < LICENSE_ID_LENGTH - 1; i++) {
        licenseId[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    licenseId[i] = '\0';
}

char CabTypes[MAX_CAB_TYPES][10];
int numCabs[MAX_CAB_TYPES];
Cab allCabs[MAX_CAB_TYPES * 100];  // Assuming max 100 cabs per cab type
int numCabTypes;

// Function to generate the cab system
int generateCabSystem() {
    // Get the number of cab types
    printf("Enter the number of cab types: ");
    scanf("%d", &numCabTypes);

    if (numCabTypes > MAX_CAB_TYPES) {
        printf("Maximum number of cab types exceeded.\n");
        return 1;
    }

    // Get cab type details
    printf("Enter cab details:\n");
    for (int i = 0; i < numCabTypes; i++) {
        printf("Cab Type %d:\n", i + 1);

        // Get cab type name
        printf("Enter cab type name: ");
        scanf("%s", CabTypes[i]);

        printf("\n");
    }

    // Get the number of each cab type
    for (int i = 0; i < numCabTypes; i++) {
        printf("Enter the number of %s cabs: ", CabTypes[i]);
        scanf("%d", &numCabs[i]);
    }

    // Generate cab details for each cab
    srand(time(0));
    int cabIndex = 0;
    for (int i = 0; i < numCabTypes; i++) {
        for (int j = 0; j < numCabs[i]; j++) {
            // Generate license ID
            generateLicenseId(allCabs[cabIndex].LicenseId);

            // Assign a random location
            int randomIndex = rand() % (sizeof(Locations) / sizeof(Locations[0]));
            strcpy(allCabs[cabIndex].Default_Location, Locations[randomIndex]);
            strcpy(allCabs[cabIndex].Current_Location, Locations[randomIndex]);

            // Assign cab type
            strcpy(allCabs[cabIndex].CabType, CabTypes[i]);
            allCabs[cabIndex].rating = 4.5;
            allCabs[cabIndex].isAdvancedBooked = false;
            allCabs[cabIndex].Requested_Day = -1;
            cabIndex++;
        }
    }

    // Print cab details
    printf("\nCab details:\n");
    for (int i = 0; i < cabIndex; i++) {
        printf("Cab %d:\n", i + 1);
        printf("Cab Type: %s\n", allCabs[i].CabType);
        printf("License ID: %s\n", allCabs[i].LicenseId);
        printf("Default Location: %s\n", allCabs[i].Default_Location);
        printf("Current Location: %s\n", allCabs[i].Current_Location);
        printf("\n");
    }

    // Set initial rating for all cabs
    for (int i = 0; i < numCabTypes; i++) {
        for (int j = 0; j < numCabs[i]; j++) {
            allCabs[cabIndex].rating = 0.0;
            cabIndex++;
        }
    }
    
    return 0;
}

void storeCabInformationToFile() {
    FILE *file = fopen("cab_info.txt", "w");  // Open the file in write mode

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Write the values of CabTypes, numCabs, allCabs, and numCabTypes to the file
    fprintf(file, "%d\n", numCabTypes);

    for (int i = 0; i < numCabTypes; i++) {
        fprintf(file, "%s\n", CabTypes[i]);
        fprintf(file, "%d\n", numCabs[i]);
    }

    for (int i = 0; i < numCabTypes * 100; i++) {
        fprintf(file, "%s\n", allCabs[i].CabType);
        fprintf(file, "%s\n", allCabs[i].LicenseId);
        fprintf(file, "%s\n", allCabs[i].Default_Location);
        fprintf(file, "%s\n", allCabs[i].Current_Location);
        fprintf(file, "%f\n", allCabs[i].rating);
        fprintf(file, "%d\n", allCabs[i].isAdvancedBooked);
        fprintf(file, "%d\n", allCabs[i].Requested_Day);
    }

    fclose(file);  // Close the file
}

void readCabInformationFromFile() {
    FILE *file = fopen("cab_info.txt", "r");  // Open the file in read mode

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Read the values from the file into the variables
    fscanf(file, "%d\n", &numCabTypes);

    for (int i = 0; i < numCabTypes; i++) {
        fscanf(file, "%s\n", CabTypes[i]);
        fscanf(file, "%d\n", &numCabs[i]);
    }

    for (int i = 0; i < numCabTypes * 100; i++) {
        fscanf(file, "%s\n", allCabs[i].CabType);
        fscanf(file, "%s\n", allCabs[i].LicenseId);
        fscanf(file, "%s\n", allCabs[i].Default_Location);
        fscanf(file, "%s\n", allCabs[i].Current_Location);
        fscanf(file, "%f\n", &allCabs[i].rating);
        fscanf(file, "%d\n", &allCabs[i].isAdvancedBooked);
        fscanf(file, "%d\n", &allCabs[i].Requested_Day);
    }

    fclose(file);  // Close the file
}

#endif // ADMIN_H
