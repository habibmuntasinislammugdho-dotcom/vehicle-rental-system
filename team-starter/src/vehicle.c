/* vehicle.c - Module 1 (stub: replaced by the module owner) */
#include <stdio.h>
#include "vehicle.h"

int loadVehicles(Vehicle **list) { *list = NULL; return 0; }
int saveVehicles(const Vehicle *list, int count) { (void)list; (void)count; return 0; }
int findVehicle(const Vehicle *list, int count, int id) { (void)list; (void)count; (void)id; return -1; }
int setVehicleStatus(int vehicleId, const char *status) { (void)vehicleId; (void)status; return 0; }
void showVehicles(int onlyAvailable) { (void)onlyAvailable; printf("Vehicle module is not added yet.\n"); }
void vehicleAdminMenu(void) { printf("Vehicle module is not added yet.\n"); }
