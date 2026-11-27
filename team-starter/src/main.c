/* main.c - Vehicle Rental System: main menu and admin login (team file) */
#include <stdio.h>
#include <string.h>
#include "vehicle.h"
#include "booking.h"
#include "rental.h"
#include "billing.h"
#include "utils.h"

#define ADMIN_USER "admin"
#define ADMIN_PASS "1234"

static int adminLogin(void)
{
    char user[30], pass[30];
    int attempt;

    for (attempt = 1; attempt <= 3; attempt++) {
        readLine("Username: ", user, sizeof(user));
        readLine("Password: ", pass, sizeof(pass));
        if (strcmp(user, ADMIN_USER) == 0 && strcmp(pass, ADMIN_PASS) == 0)
            return 1;
        printf("Wrong username or password (%d/3).\n", attempt);
    }
    return 0;
}

static void adminMenu(void)
{
    int choice;
    do {
        printf("\n===== ADMIN PANEL =====\n");
        printf("1. Vehicle management\n2. Rentals and returns\n3. Billing\n0. Logout\n");
        choice = readInt("Choice: ", 0, 3);
        switch (choice) {
            case 1: vehicleAdminMenu(); break;
            case 2: rentalAdminMenu(); break;
            case 3: billingAdminMenu(); break;
            default: break;
        }
    } while (choice != 0);
}

int main(void)
{
    int choice;
    do {
        printf("\n=================================\n");
        printf("      VEHICLE RENTAL SYSTEM\n");
        printf("=================================\n");
        printf("1. Admin login\n2. Customer menu\n0. Exit\n");
        choice = readInt("Choice: ", 0, 2);
        switch (choice) {
            case 1:
                if (adminLogin())
                    adminMenu();
                break;
            case 2:
                customerMenu();
                break;
            default:
                printf("Thank you!\n");
                break;
        }
    } while (choice != 0);
    return 0;
}
