#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carpool.h"

RouteNode* routeroot = NULL;

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

void registerDriver(int driverID, char *r) {
    RouteNode* routeNode = insertRoute(&routeroot, r);
    driver *newdriver = (driver *)malloc(sizeof(driver));
    newdriver->driverid = driverID;
    strcpy(newdriver->route, r);
    newdriver->next = routeNode->drivers;
    routeNode->drivers = newdriver;
    printf("Driver %d registered for route %s\n", driverID, r);
}

void registerPassenger(int psngrid, char *r) {
    RouteNode* routeNode = insertRoute(&routeroot, r);
    passenger *newpassenger = (passenger *)malloc(sizeof(passenger));
    newpassenger->userid = psngrid;
    strcpy(newpassenger->route, r);
    newpassenger->next = routeNode->passengers;
    routeNode->passengers = newpassenger;
    printf("  Passenger %d registered for route %s\n", psngrid, r);
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
