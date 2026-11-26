#include <stdio.h>
#include "vehicle.h"

int main(void) {
    Vehicle vehicles[MAX_VEHICLES];
    int count = 0;
    int choice;

    loadVehicles(vehicles, &count);

    printf("\n================================\n");
    printf("     VEHICLE MANAGEMENT SYSTEM\n");
    printf("================================\n");

    do {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Add New Vehicle\n");
        printf("2. View All Vehicles\n");
        printf("3. Update Vehicle\n");
        printf("4. Remove Vehicle\n");
        printf("5. Exit\n");
        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                addVehicle(vehicles, &count);
                saveVehicles(vehicles, count);
                break;

            case 2:
                viewVehicles(vehicles, count);
                break;

            case 3:
                updateVehicle(vehicles, count);
                saveVehicles(vehicles, count);
                break;

            case 4:
                removeVehicle(vehicles, &count);
                saveVehicles(vehicles, count);
                break;

            case 5:
                saveVehicles(vehicles, count);
                printf("\nThank you for using the system!\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
