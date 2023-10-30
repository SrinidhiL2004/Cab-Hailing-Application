#ifndef CABFINDER_H
#define CABFINDER_H

extern int Login();

#include "map.h"
#include "admin.h"
#include "booking.h"
#include "clock.h"

// Function to perform Dijkstra's algorithm to calculate shortest distances
void dijkstra(int graph[MAX_LOCATIONS][MAX_LOCATIONS], int src, int dist[MAX_LOCATIONS]) {
    int visited[MAX_LOCATIONS] = {0};
    
    for (int i = 0; i < MAX_LOCATIONS; ++i) {
        dist[i] = INT_MAX;
    }
    
    dist[src] = 0;
    
    for (int count = 0; count < MAX_LOCATIONS - 1; ++count) {
        int u, min_dist = INT_MAX;
        
        for (int v = 0; v < MAX_LOCATIONS; ++v) {
            if (!visited[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                u = v;
            }
        }
        
        visited[u] = 1;
        
        for (int v = 0; v < MAX_LOCATIONS; ++v) {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

int ride_distance;

// Function to find the nearest available cab
int getNearestCab(int customerLocation, int cabType) {
    int dist[MAX_LOCATIONS];
    int minDist = INT_MAX;
    float maxRating = 0.0;
    int nearestCabIndex = -1;

    // Calculate shortest distances from the customer location
    dijkstra(Map, customerLocation, dist);

    for (int i = 0; i < MAX_LOCATIONS; ++i) {
        if (!allCabs[i].isAdvancedBooked){
            if (i != customerLocation && strcmp(allCabs[i].CabType, CabTypes[cabType - 1]) == 0) {
                int cabLocation = -1;
                for (int j = 0; j < MAX_LOCATIONS; ++j) {
                    if (strcmp(allCabs[i].Current_Location, Locations[j]) == 0) {
                        cabLocation = j;
                        break;
                    }
                }
                // Check if the cab is closer and has a higher rating
                if (cabLocation != -1 && dist[cabLocation] < minDist && allCabs[i].rating > maxRating) {
                    minDist = dist[cabLocation];
                    maxRating = allCabs[i].rating;
                    nearestCabIndex = i;
                }
            }
        }
    }
    ride_distance = minDist;
    return nearestCabIndex;
}

#endif // CABFINDER_H
