#include <stdio.h>
#include "vehicle.h"

void saveVehicles(const Vehicle vehicles[], int count) {
    FILE *fp = fopen("vehicles.dat", "wb");

    if (fp == NULL) {
        printf("Error: could not open vehicles.dat for writing.\n");
        return;
    }

    if (fwrite(vehicles, sizeof(Vehicle), (size_t)count, fp) != (size_t)count) {
        printf("Error: could not write all vehicle records.\n");
    } else {
        printf("Data saved successfully!\n");
    }

    fclose(fp);
}

void loadVehicles(Vehicle vehicles[], int *count) {
    FILE *fp = fopen("vehicles.dat", "rb");
    size_t recordsRead;

    *count = 0;

    if (fp == NULL) {
        /* File does not exist yet; start with an empty list. */
        return;
    }

    recordsRead = fread(vehicles, sizeof(Vehicle), MAX_VEHICLES, fp);
    *count = (int)recordsRead;

    if (!feof(fp)) {
        printf("Warning: vehicle file may contain more records than capacity.\n");
    }

    fclose(fp);
}
