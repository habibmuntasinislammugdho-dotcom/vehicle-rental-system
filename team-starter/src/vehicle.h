/* vehicle.h - Module 1: Vehicle Management */
#ifndef VEHICLE_H
#define VEHICLE_H

#include "common.h"

/* Returns number of records. *list is allocated with malloc/realloc: free() it. */
int  loadVehicles(Vehicle **list);
int  saveVehicles(const Vehicle *list, int count);
int  findVehicle(const Vehicle *list, int count, int id);   /* index or -1 */
int  setVehicleStatus(int vehicleId, const char *status);   /* 1 = success */
void showVehicles(int onlyAvailable);
void vehicleAdminMenu(void);

#endif
