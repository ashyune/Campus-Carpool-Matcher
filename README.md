# Campus-Carpool-Matcher
A simple C-based console application that matches passengers with available drivers using routes and landmarks, stored in linked lists and binary search trees (BSTs).

## Features
- Register Driver (with route)
- Register Passenger (with route)
- Display All Routes (Route BST)
- Match Ride (matches passenger and driver on the same route)
- Suggest Alternate Pickup Points
  - Enter Passenger ID
  - System finds their registered landmark
  - Shows drivers available at that landmark (Landmark BST)
- Memory cleanup on exit

## Files included
- `main.c` — Menu + user interaction
- `carpool.c` — Logic, BSTs, linked lists
- `carpool.h` — Structs + function declarations

## Compile and Run
```gcc main.c carpool.c -o carpool```<br>
```./carpool```


## Working
- Drivers and passengers are stored using linked lists  
- Routes and landmarks are stored in BSTs  
- Matching is done first by route, and if not found, by landmark  
- Passengers provide their User ID for alternate pickup suggestions  
