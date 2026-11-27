/* vehicle.c - Module 1: Vehicle Management (add, view, update, remove) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vehicle.h"
#include "booking.h"
#include "billing.h"
#include "utils.h"

#define VEHICLE_HEADER "id,regNo,model,type,status"

int loadVehicles(Vehicle **list)
{
    char path[200], line[LINE_LEN];
    char *f[5];
    int count = 0, capacity = 0;
    FILE *fp;

    *list = NULL;
    dataPath("vehicles.csv", path, sizeof(path));
    fp = fopen(path, "r");
    if (fp == NULL)
        return 0;
    if (fgets(line, sizeof(line), fp) == NULL) {    /* skip header row */
        fclose(fp);
        return 0;
    }
    while (fgets(line, sizeof(line), fp) != NULL) {
        Vehicle *v;
        if (splitCSV(line, f, 5) != 5)
            continue;
        *list = growArray(*list, count, &capacity, sizeof(Vehicle));
        v = &(*list)[count++];
        v->id = atoi(f[0]);
        copyText(v->regNo, f[1], sizeof(v->regNo));
        copyText(v->model, f[2], sizeof(v->model));
        copyText(v->type, f[3], sizeof(v->type));
        copyText(v->status, f[4], sizeof(v->status));
    }
    fclose(fp);
    return count;
}

int saveVehicles(const Vehicle *list, int count)
{
    char path[200], temp[220];
    FILE *fp;
    int i;

    dataPath("vehicles.csv", path, sizeof(path));
    snprintf(temp, sizeof(temp), "%s.tmp", path);
    fp = fopen(temp, "w");
    if (fp == NULL) {
        printf("Error: cannot write vehicle file.\n");
        return 0;
    }
    fprintf(fp, "%s\n", VEHICLE_HEADER);
    for (i = 0; i < count; i++)
        fprintf(fp, "%d,%s,%s,%s,%s\n", list[i].id, list[i].regNo,
                list[i].model, list[i].type, list[i].status);
    fclose(fp);
    return replaceFile(temp, path);
}

int findVehicle(const Vehicle *list, int count, int id)
{
    int i;
    for (i = 0; i < count; i++)
        if (list[i].id == id)
            return i;
    return -1;
}

int setVehicleStatus(int vehicleId, const char *status)
{
    Vehicle *list;
    int count = loadVehicles(&list);
    int index = findVehicle(list, count, vehicleId);
    int ok = 0;

    if (index >= 0) {
        copyText(list[index].status, status, STATUS_LEN);
        ok = saveVehicles(list, count);
    }
    free(list);
    return ok;
}

void showVehicles(int onlyAvailable)
{
    Vehicle *list;
    int count = loadVehicles(&list);
    int i, shown = 0;

    printf("\n%-4s %-14s %-22s %-10s %-12s %s\n",
           "ID", "Reg No", "Model", "Type", "Status", "Rate/Day");
    printf("-------------------------------------------------------------------------\n");
    for (i = 0; i < count; i++) {
        if (onlyAvailable && strcmp(list[i].status, V_AVAILABLE) != 0)
            continue;
        printf("%-4d %-14s %-22s %-10s %-12s %.2f\n", list[i].id, list[i].regNo,
               list[i].model, list[i].type, list[i].status, getDailyRate(list[i].type));
        shown++;
    }
    if (shown == 0)
        printf("No vehicle found.\n");
    free(list);
}

static void chooseType(char *type)
{
    printf("Type: 1. Car  2. SUV  3. Microbus  4. Bike\n");
    switch (readInt("Choose type: ", 1, 4)) {
        case 1: copyText(type, "Car", TYPE_LEN); break;
        case 2: copyText(type, "SUV", TYPE_LEN); break;
        case 3: copyText(type, "Microbus", TYPE_LEN); break;
        default: copyText(type, "Bike", TYPE_LEN); break;
    }
}

static int regNoExists(const Vehicle *list, int count, const char *regNo)
{
    int i;
    for (i = 0; i < count; i++)
        if (equalsIgnoreCase(list[i].regNo, regNo))
            return 1;
    return 0;
}

static void addVehicle(void)
{
    Vehicle *list, v;
    Booking *bookings;
    int count, bookingCount, capacity, i, maxId = 0;

    count = loadVehicles(&list);
    readText("Registration No: ", v.regNo, sizeof(v.regNo));
    if (regNoExists(list, count, v.regNo)) {
        printf("This registration number already exists.\n");
        free(list);
        return;
    }
    readText("Model name: ", v.model, sizeof(v.model));
    chooseType(v.type);
    copyText(v.status, V_AVAILABLE, STATUS_LEN);

    /* An old ID is never reused if it is present in booking history. */
    for (i = 0; i < count; i++)
        if (list[i].id > maxId)
            maxId = list[i].id;
    bookingCount = loadBookings(&bookings);
    for (i = 0; i < bookingCount; i++)
        if (bookings[i].vehicleId > maxId)
            maxId = bookings[i].vehicleId;
    free(bookings);
    v.id = maxId + 1;

    capacity = count;
    list = growArray(list, count, &capacity, sizeof(Vehicle));
    list[count++] = v;
    if (saveVehicles(list, count))
        printf("Vehicle added. ID = %d\n", v.id);
    free(list);
}

static void updateVehicle(void)
{
    Vehicle *list;
    int count, index;

    showVehicles(0);
    count = loadVehicles(&list);
    index = findVehicle(list, count, readInt("\nVehicle ID to update (0 = back): ", 0, 100000));
    if (index < 0) {
        printf("No vehicle updated.\n");
        free(list);
        return;
    }
    printf("1. Model  2. Type  3. Status\n");
    switch (readInt("What to update: ", 1, 3)) {
        case 1:
            readText("New model: ", list[index].model, NAME_LEN);
            break;
        case 2:
            if (strcmp(list[index].status, V_RENTED) == 0) {
                printf("Type of a rented vehicle cannot be changed.\n");
                free(list);
                return;
            }
            chooseType(list[index].type);
            break;
        default:
            if (strcmp(list[index].status, V_RENTED) == 0) {
                printf("Vehicle is rented. Process the return first.\n");
                free(list);
                return;
            }
            printf("1. Available  2. Maintenance\n");
            if (readInt("New status: ", 1, 2) == 1)
                copyText(list[index].status, V_AVAILABLE, STATUS_LEN);
            else
                copyText(list[index].status, V_MAINTENANCE, STATUS_LEN);
            break;
    }
    if (saveVehicles(list, count))
        printf("Vehicle updated.\n");
    free(list);
}

static void removeVehicle(void)
{
    Vehicle *list;
    int count, index, i;

    showVehicles(0);
    count = loadVehicles(&list);
    index = findVehicle(list, count, readInt("\nVehicle ID to remove (0 = back): ", 0, 100000));
    if (index < 0) {
        printf("No vehicle removed.\n");
    } else if (strcmp(list[index].status, V_RENTED) == 0) {
        printf("A rented vehicle cannot be removed.\n");
    } else if (readYesNo("Are you sure? (y/n): ")) {
        for (i = index; i < count - 1; i++)
            list[i] = list[i + 1];
        if (saveVehicles(list, count - 1))
            printf("Vehicle removed.\n");
    }
    free(list);
}

void vehicleAdminMenu(void)
{
    int choice;
    do {
        printf("\n--- Vehicle Management ---\n");
        printf("1. View all vehicles\n2. Add vehicle\n3. Update vehicle\n4. Remove vehicle\n0. Back\n");
        choice = readInt("Choice: ", 0, 4);
        switch (choice) {
            case 1: showVehicles(0); pauseScreen(); break;
            case 2: addVehicle(); break;
            case 3: updateVehicle(); break;
            case 4: removeVehicle(); break;
            default: break;
        }
    } while (choice != 0);
}
