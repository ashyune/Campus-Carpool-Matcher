#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carpool.h"

RouteNode* routeroot = NULL;
LandmarkNode* landmarkroot = NULL;

RouteNode* insertRoute(RouteNode** root, char* route) {
    if (*root == NULL) {
        RouteNode* newNode = (RouteNode*)malloc(sizeof(RouteNode));
        strcpy(newNode->route, route);
        newNode->drivers = NULL;
        newNode->passengers = NULL;
        newNode->left = newNode->right = NULL;
        *root = newNode;
        return newNode;
    }
    int cmp = strcmp(route, (*root)->route);
    if (cmp == 0)
        return *root;
    else if (cmp < 0)
        return insertRoute(&((*root)->left), route);
    else
        return insertRoute(&((*root)->right), route);
}

RouteNode* findRoute(RouteNode* root, char* route) {
    if (!root) return NULL;
    int cmp = strcmp(route, root->route);
    if (cmp == 0) return root;
    return cmp < 0 ? findRoute(root->left, route) : findRoute(root->right, route);
}


LandmarkNode* insertLandmark(LandmarkNode** root, char* landmark) {
    if (*root == NULL) {
        LandmarkNode* newNode = (LandmarkNode*)malloc(sizeof(LandmarkNode));
        strcpy(newNode->landmark, landmark);
        newNode->drivers = NULL;
        newNode->passengers = NULL;
        newNode->left = newNode->right = NULL;
        *root = newNode;
        return newNode;
    }
    int cmp = strcmp(landmark, (*root)->landmark);
    if (cmp == 0)
        return *root;
    else if (cmp < 0)
        return insertLandmark(&((*root)->left), landmark);
    else
        return insertLandmark(&((*root)->right), landmark);
}

LandmarkNode* findLandmark(LandmarkNode* root, char* landmark) {
    if (!root) return NULL;
    int cmp = strcmp(landmark, root->landmark);
    if (cmp == 0) return root;
    return cmp < 0 ? findLandmark(root->left, landmark) : findLandmark(root->right, landmark);
}

void registerDriver(int driverID, char *r, char *landmark) {
    RouteNode* routeNode = insertRoute(&routeroot, r);
    driver *newdriver = (driver *)malloc(sizeof(driver));
    newdriver->driverid = driverID;
    strcpy(newdriver->route, r);
    newdriver->next = routeNode->drivers;
    routeNode->drivers = newdriver;
    
    LandmarkNode* landmarkNode = insertLandmark(&landmarkroot, landmark);
    driver *newdriverLandmark = (driver *)malloc(sizeof(driver));
    newdriverLandmark->driverid = driverID;
    strcpy(newdriverLandmark->route, r);
    newdriverLandmark->next = landmarkNode->drivers;
    landmarkNode->drivers = newdriverLandmark;
    
    printf("Driver %d registered for route %s at landmark %s\n", driverID, r, landmark);
}

void registerPassenger(int psngrid, char *r, char *landmark) {
    RouteNode* routeNode = insertRoute(&routeroot, r);
    passenger *newpassenger = (passenger *)malloc(sizeof(passenger));
    newpassenger->userid = psngrid;
    strcpy(newpassenger->route, r);
    newpassenger->next = routeNode->passengers;
    routeNode->passengers = newpassenger;
    
    LandmarkNode* landmarkNode = insertLandmark(&landmarkroot, landmark);
    passenger *newpassengerLandmark = (passenger *)malloc(sizeof(passenger));
    newpassengerLandmark->userid = psngrid;
    strcpy(newpassengerLandmark->route, r);
    newpassengerLandmark->next = landmarkNode->passengers;
    landmarkNode->passengers = newpassengerLandmark;
    
    printf("Passenger %d registered for route %s at landmark %s\n", psngrid, r, landmark);
}

void displayDrivers(driver *head) {
    if (!head) {
        printf("\n  (No drivers)");
        return;
    }
    while (head) {
        printf("\n  Driver ID: %d", head->driverid);
        head = head->next;
    }
}

void displayPassengers(passenger *head) {
    if (!head) {
        printf("\n  (No passengers)");
        return;
    }
    while (head) {
        printf("\n  Passenger ID: %d", head->userid);
        head = head->next;
    }
}

void displayRoutes(RouteNode* root) {
    if (!root) return;
    displayRoutes(root->left);
    printf("\n\n  Route: %s", root->route);
    printf("\n  Drivers:");
    displayDrivers(root->drivers);
    printf("\n  Passengers:");
    displayPassengers(root->passengers);
    displayRoutes(root->right);
}

void displayLandmarks(LandmarkNode* root) {
    if (!root) return;
    displayLandmarks(root->left);
    printf("\n\n  Landmark: %s", root->landmark);
    printf("\n  Drivers:");
    displayDrivers(root->drivers);
    printf("\n  Passengers:");
    displayPassengers(root->passengers);
    displayLandmarks(root->right);
}


void matchRideHelper(RouteNode* root, int userID, int *found) {
    if (!root) return;
    matchRideHelper(root->left, userID, found);
    passenger* p = root->passengers;
    while (p) {
        if (p->userid == userID) {
            *found = 1;
            if (root->drivers)
                printf("\n  Matched Passenger %d with Driver %d on route %s\n",
                       userID, root->drivers->driverid, root->route);
            else
                printf("\n  No available drivers for route %s\n", root->route);
            return;
        }
        p = p->next;
    }
    matchRideHelper(root->right, userID, found);
}

void matchRide(int userID) {
    int found = 0;
    matchRideHelper(routeroot, userID, &found);
    if (!found)
        printf("\nPassenger %d not found.\n", userID);
}


void suggestAlternativePickupHelper(LandmarkNode* root, int passengerID, int *found) {
    if (!root) return;
    
    suggestAlternativePickupHelper(root->left, passengerID, found);
    
    passenger* p = root->passengers;
    while (p) {
        if (p->userid == passengerID) {
            *found = 1;
            printf("\n  Passenger %d found at landmark: %s\n", passengerID, root->landmark);
            
            if (root->drivers) {
                printf("Available drivers at this landmark:\n");
                driver* d = root->drivers;
                while (d) {
                    printf(" - Driver %d (route: %s)\n", d->driverid, d->route);
                    d = d->next;
                }
            } else {
                printf("No available drivers at landmark %s\n", root->landmark);
            }
            return;
        }
        p = p->next;
    }
    
    suggestAlternativePickupHelper(root->right, passengerID, found);
}

void suggestAlternativePickup(int passengerID) {
    printf("\n Suggesting Alternative Pickup Points for Passenger %d \n", passengerID);
    int found = 0;
    suggestAlternativePickupHelper(landmarkroot, passengerID, &found);
    
    if (!found) {
        printf("\nPassenger %d not registered at any landmark.\n", passengerID);
    }

}
