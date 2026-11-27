/* billing.h - Module 4: Billing and Cost Calculation */
#ifndef BILLING_H
#define BILLING_H

#include "common.h"

typedef struct {
    int    billId;
    int    bookingId;
    char   customer[NAME_LEN];
    char   regNo[ID_LEN * 2];
    char   type[TYPE_LEN];
    char   returnDate[DATE_LEN];
    int    days;
    int    lateDays;
    double baseCost;
    double driverFee;
    double insuranceFee;
    double discount;
    double lateFee;
    double damageFee;
    double vat;
    double total;
} Bill;

double getDailyRate(const char *type);
void   calculateBill(Bill *bill, int withDriver, int withInsurance);
void   showEstimate(const char *type, int days, int withDriver, int withInsurance);
int    generateBill(const Booking *booking, const Vehicle *vehicle,
                    const char *returnDate, int lateDays, double damageFee);
void   billingAdminMenu(void);

#endif
