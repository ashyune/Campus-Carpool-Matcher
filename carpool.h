#ifndef CARPOOL_H
#define CARPOOL_H

typedef struct driver {
    int driverid;
    char route[500];
    struct driver *next;
} driver;

typedef struct passenger {
    int userid;
    char route[500];
    struct passenger *next;
} passenger;

typedef struct RouteNode {
    char route[500];
    driver* drivers;
    passenger* passengers;
    struct RouteNode* left;
    struct RouteNode* right;
} RouteNode;

extern RouteNode* routeroot;

RouteNode* insertRoute(RouteNode** root, char* route);
RouteNode* findRoute(RouteNode* root, char* route);
void registerDriver(int driverID, char *r);
void registerPassenger(int psngrid, char *r);
void displayDrivers(driver *head);
void displayPassengers(passenger *head);
void displayRoutes(RouteNode* root);
void matchRide(int userID);

#endif
