#include <stdio.h>
#include "vehicle.h"

static int findVehicleById(const Vehicle vehicles[], int count, int id) {
    int i;

    for (i = 0; i < count; i++) {
        if (vehicles[i].id == id) {
            return i;
        }
    }

    return -1;
}

void addVehicle(Vehicle vehicles[], int *count) {
    int id;
    Vehicle newVehicle;

    if (*count >= MAX_VEHICLES) {
        printf("\nVehicle storage is full!\n");
        return;
    }

    printf("\nEnter Vehicle ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID input.\n");
        return;
    }

    if (findVehicleById(vehicles, *count, id) != -1) {
        printf("Vehicle ID already exists!\n");
        return;
    }

    newVehicle.id = id;

    printf("Enter Vehicle Name: ");
    scanf(" %49[^\n]", newVehicle.name);

    printf("Enter Brand: ");
    scanf(" %29[^\n]", newVehicle.brand);

    printf("Enter Model: ");
    scanf(" %29[^\n]", newVehicle.model);

    printf("Enter Registration Number: ");
    scanf(" %29[^\n]", newVehicle.registration);

    printf("Enter Rent Per Day: ");
    if (scanf("%f", &newVehicle.rentPerDay) != 1 ||
        newVehicle.rentPerDay < 0) {
        printf("Invalid rent amount.\n");
        return;
    }

    newVehicle.status = AVAILABLE;
    vehicles[*count] = newVehicle;
    (*count)++;

    printf("\nVehicle added successfully!\n");
}

void viewVehicles(const Vehicle vehicles[], int count) {
    int i;

    if (count == 0) {
        printf("\nNo vehicles registered yet!\n");
        return;
    }

    printf("\n========== VEHICLE LIST ==========\n");

    for (i = 0; i < count; i++) {
        printf("\nVehicle ID: %d\n", vehicles[i].id);
        printf("Name: %s\n", vehicles[i].name);
        printf("Brand: %s\n", vehicles[i].brand);
        printf("Model: %s\n", vehicles[i].model);
        printf("Registration: %s\n", vehicles[i].registration);
        printf("Rent Per Day: %.2f\n", vehicles[i].rentPerDay);
        printf("Status: %s\n",
               vehicles[i].status == AVAILABLE ? "Available" : "Rented");
        printf("----------------------------------\n");
    }
}

void updateVehicle(Vehicle vehicles[], int count) {
    int id, index, choice, status;

    printf("\nEnter Vehicle ID to update: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID input.\n");
        return;
    }

    index = findVehicleById(vehicles, count, id);

    if (index == -1) {
        printf("\nVehicle not found!\n");
        return;
    }

    printf("\n1. Update Name\n");
    printf("2. Update Brand\n");
    printf("3. Update Model\n");
    printf("4. Update Registration\n");
    printf("5. Update Rent\n");
    printf("6. Update Status\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid choice input.\n");
        return;
    }

    switch (choice) {
        case 1:
            printf("Enter new name: ");
            scanf(" %49[^\n]", vehicles[index].name);
            break;

        case 2:
            printf("Enter new brand: ");
            scanf(" %29[^\n]", vehicles[index].brand);
            break;

        case 3:
            printf("Enter new model: ");
            scanf(" %29[^\n]", vehicles[index].model);
            break;

        case 4:
            printf("Enter new registration: ");
            scanf(" %29[^\n]", vehicles[index].registration);
            break;

        case 5:
            printf("Enter new rent: ");
            if (scanf("%f", &vehicles[index].rentPerDay) != 1 ||
                vehicles[index].rentPerDay < 0) {
                printf("Invalid rent amount.\n");
                return;
            }
            break;

        case 6:
            printf("0. Available\n1. Rented\nEnter new status: ");
            if (scanf("%d", &status) != 1 || (status != 0 && status != 1)) {
                printf("Invalid status!\n");
                return;
            }
            vehicles[index].status = (enum VehicleStatus)status;
            break;

        default:
            printf("Invalid choice!\n");
            return;
    }

    printf("\nVehicle updated successfully!\n");
}

void removeVehicle(Vehicle vehicles[], int *count) {
    int id, index, i;

    printf("\nEnter Vehicle ID to remove: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID input.\n");
        return;
    }

    index = findVehicleById(vehicles, *count, id);

    if (index == -1) {
        printf("\nVehicle not found!\n");
        return;
    }

    for (i = index; i < *count - 1; i++) {
        vehicles[i] = vehicles[i + 1];
    }

    (*count)--;
    printf("\nVehicle removed successfully!\n");
}
