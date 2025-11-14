#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carpool.h"

int main() {
    int choice;
    while (1) {
        printf("\n\n====== CARPOOL MATCHING SYSTEM ======");
        printf("\n1. Register Driver");
        printf("\n2. Register Passenger");
        printf("\n3. Display All Routes");
        printf("\n4. Match Ride");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input.\n");
            break;
        }

        getchar();

        if (choice == 1) {
            int id;
            char route[500];
            printf("Enter Driver ID: ");
            scanf("%d", &id);
            getchar();
            printf("Enter Route: ");
            fgets(route, sizeof(route), stdin);
            route[strcspn(route, "\n")] = 0;
            registerDriver(id, route);
        } 
        else if (choice == 2) {
            int id;
            char route[500];
            printf("Enter Passenger ID: ");
            scanf("%d", &id);
            getchar();
            printf("Enter Route: ");
            fgets(route, sizeof(route), stdin);
            route[strcspn(route, "\n")] = 0;
            registerPassenger(id, route);
        } 
        else if (choice == 3) {
            if (routeroot == NULL)
                printf("\nNo routes registered yet.");
            else
                displayRoutes(routeroot);
        } 
        else if (choice == 4) {
            int uid;
            printf("Enter Passenger ID to match: ");
            scanf("%d", &uid);
            matchRide(uid);
        } 
        else if (choice == 5) {
            printf("\nExiting...\n");
            break;
        } 
        else {
            printf("\nInvalid choice.");
        }
    }
    return 0;
}
