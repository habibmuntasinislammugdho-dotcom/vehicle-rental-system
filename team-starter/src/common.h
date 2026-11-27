/* common.h - structures and constants shared by all modules (team file) */
#ifndef COMMON_H
#define COMMON_H

#define ID_LEN      12
#define NAME_LEN    50
#define TYPE_LEN    20
#define PHONE_LEN   16
#define DATE_LEN    11      /* YYYY-MM-DD + '\0' */
#define STATUS_LEN  15
#define LINE_LEN    512

/* Vehicle status values */
#define V_AVAILABLE   "Available"
#define V_RENTED      "Rented"
#define V_MAINTENANCE "Maintenance"

/* Booking status values */
#define B_ACTIVE      "Active"
#define B_RETURNED    "Returned"
#define B_CANCELLED   "Cancelled"

typedef struct {
    int  id;
    char regNo[ID_LEN * 2];
    char model[NAME_LEN];
    char type[TYPE_LEN];
    char status[STATUS_LEN];
} Vehicle;

typedef struct {
    int  id;
    int  vehicleId;
    char customer[NAME_LEN];
    char phone[PHONE_LEN];
    char startDate[DATE_LEN];
    int  days;
    int  withDriver;        /* 1 = yes, 0 = no */
    int  withInsurance;     /* 1 = yes, 0 = no */
    char status[STATUS_LEN];
} Booking;

#endif
