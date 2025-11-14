#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "carpool.h"

void displaymenu() {
    printf("\n");
    printf("========================================\n");
    printf("     CARPOOL MANAGEMENT SYSTEM\n");
    printf("1. Register Driver\n");
    printf("2. Register Passenger\n");
    printf("3. Display All Routes\n");
    printf("4. Display All Landmarks\n");
    printf("5. Match Ride by Route\n");
    printf("6. Suggest Alternative Pickup Points\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    int id;
    char route[MAX_ROUTE_LEN];
    char landmark[MAX_LANDMARK_LEN];
    
    while (1) {
        displaymenu();
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1: {
                printf("\nEnter Driver ID: ");
                scanf("%d", &id);
                getchar();
                
                printf("Enter Route: ");
                fgets(route, MAX_ROUTE_LEN, stdin);
                route[strcspn(route, "\n")] = 0; 
                
                printf("Enter Landmark: ");
                fgets(landmark, MAX_LANDMARK_LEN, stdin);
                landmark[strcspn(landmark, "\n")] = 0; 
                
                registerDriver(id, route, landmark);
                break;
            }
            
            case 2: {
                printf("\nEnter Passenger ID: ");
                scanf("%d", &id);
                getchar();
                
                printf("Enter Route: ");
                fgets(route, MAX_ROUTE_LEN, stdin);
                route[strcspn(route, "\n")] = 0; 
                
                printf("Enter Landmark: ");
                fgets(landmark, MAX_LANDMARK_LEN, stdin);
                landmark[strcspn(landmark, "\n")] = 0;
                
                registerPassenger(id, route, landmark);
                break;
            }
            
            case 3: {
                if(routeroot==NULL){
                    printf("no routes registered yet");
                }
                displayRoutes(routeroot);
                break;
            }
            
            case 4: {
                displayLandmarks(landmarkroot);
                break;
            }
            
            case 5: {
                printf("\nEnter Passenger ID to match: ");
                scanf("%d", &id);
                getchar();
                
                matchRide(id);
                break;
            }
            
            case 6: {
                printf("\nEnter Passenger ID: ");
                scanf("%d", &id);
                getchar();
                
                suggestAlternativePickup(id);
                break;
            }
            
            case 7: {
                printf("\nThank you for using Carpool Management System!\n");
                printf("Exiting\n\n");
                exit(0);
            }
            
            default: {
                printf("\n*** Invalid choice! Please enter a number between 1-7 ***\n");
                break;
            }
        }
        
    
    }
    
    return 0;

}
