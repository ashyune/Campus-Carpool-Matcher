#ifndef CARPOOL_H
#define CARPOOL_H

#define MAX_ROUTE_LEN 100
#define MAX_LANDMARK_LEN 100

// Driver structure
typedef struct driver {
    int driverid;
    char route[MAX_ROUTE_LEN];
    struct driver *next;
} driver;

// Passenger structure
typedef struct passenger {
    int userid;
    char route[MAX_ROUTE_LEN];
    struct passenger *next;
} passenger;

// Route BST Node
typedef struct RouteNode {
    char route[MAX_ROUTE_LEN];
    driver *drivers;
    passenger *passengers;
    struct RouteNode *left;
    struct RouteNode *right;
} RouteNode;

// Landmark BST Node
typedef struct LandmarkNode {
    char landmark[MAX_LANDMARK_LEN];
    driver *drivers;
    passenger *passengers;
    struct LandmarkNode *left;
    struct LandmarkNode *right;
} LandmarkNode;

// Global roots
extern RouteNode* routeroot;
extern LandmarkNode* landmarkroot;

// Route and registration functions
RouteNode* insertRoute(RouteNode** root, char* route);
RouteNode* findRoute(RouteNode* root, char* route);
void registerDriver(int driverID, char *r, char *landmark);
void registerPassenger(int psngrid, char *r, char *landmark);
void displayDrivers(driver *head);
void displayPassengers(passenger *head);
void displayRoutes(RouteNode* root);
void matchRide(int userID);

// Landmark functions
LandmarkNode* insertLandmark(LandmarkNode** root, char* landmark);
LandmarkNode* findLandmark(LandmarkNode* root, char* landmark);
void displayLandmarks(LandmarkNode* root);
void suggestAlternativePickup(int passengerID);

#endif