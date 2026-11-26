#ifndef VEHICLE_H
#define VEHICLE_H

#define MAX_VEHICLES 100

enum VehicleStatus {
    AVAILABLE = 0,
    RENTED = 1
};

typedef struct Vehicle {
    int id;
    char name[50];
    char brand[30];
    char model[30];
    char registration[30];
    float rentPerDay;
    enum VehicleStatus status;
} Vehicle;

void addVehicle(Vehicle vehicles[], int *count);
void viewVehicles(const Vehicle vehicles[], int count);
void updateVehicle(Vehicle vehicles[], int count);
void removeVehicle(Vehicle vehicles[], int *count);

void loadVehicles(Vehicle vehicles[], int *count);
void saveVehicles(const Vehicle vehicles[], int count);

#endif
