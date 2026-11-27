/* booking.h - Module 2: Customer Booking */
#ifndef BOOKING_H
#define BOOKING_H

#include "common.h"

/* Returns number of records. *list is allocated with malloc/realloc: free() it. */
int  loadBookings(Booking **list);
int  saveBookings(const Booking *list, int count);
int  findBooking(const Booking *list, int count, int id);   /* index or -1 */
void customerMenu(void);

#endif
