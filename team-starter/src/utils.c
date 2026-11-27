/* utils.c - input, validation, date and CSV helper functions (team file) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "utils.h"

/* Reads one full line from keyboard. Exits safely if input is closed. */
void readLine(const char *prompt, char *out, int size)
{
    char buffer[LINE_LEN];
    size_t len;

    printf("%s", prompt);
    fflush(stdout);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("\nInput closed. Exiting.\n");
        exit(0);
    }
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] != '\n') {   /* line too long: discard rest */
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
    buffer[strcspn(buffer, "\r\n")] = '\0';
    copyText(out, buffer, size);
}

/* A comma would break the CSV file, so it is not allowed. */
void readText(const char *prompt, char *out, int size)
{
    char buffer[LINE_LEN];

    while (1) {
        readLine(prompt, buffer, sizeof(buffer));
        if (strlen(buffer) == 0)
            printf("  This field cannot be empty.\n");
        else if (strchr(buffer, ',') != NULL || strchr(buffer, '"') != NULL)
            printf("  Comma and quote are not allowed.\n");
        else if ((int)strlen(buffer) >= size)
            printf("  Too long. Maximum %d characters.\n", size - 1);
        else
            break;
    }
    copyText(out, buffer, size);
}

int readInt(const char *prompt, int min, int max)
{
    char buffer[64];
    char extra;
    int value;

    while (1) {
        readLine(prompt, buffer, sizeof(buffer));
        if (sscanf(buffer, "%d %c", &value, &extra) == 1 && value >= min && value <= max)
            return value;
        printf("  Invalid input. Enter a number from %d to %d.\n", min, max);
    }
}

double readMoney(const char *prompt)
{
    char buffer[64];
    char extra;
    double value;

    while (1) {
        readLine(prompt, buffer, sizeof(buffer));
        if (sscanf(buffer, "%lf %c", &value, &extra) == 1 && value >= 0 && value <= 1000000)
            return value;
        printf("  Invalid amount. Enter 0 to 1000000.\n");
    }
}

int readYesNo(const char *prompt)
{
    char buffer[16];

    while (1) {
        readLine(prompt, buffer, sizeof(buffer));
        if (equalsIgnoreCase(buffer, "y"))
            return 1;
        if (equalsIgnoreCase(buffer, "n"))
            return 0;
        printf("  Please type y or n.\n");
    }
}

void readDate(const char *prompt, char *out)
{
    char buffer[64];

    while (1) {
        readLine(prompt, buffer, sizeof(buffer));
        if (isValidDate(buffer))
            break;
        printf("  Invalid date. Use YYYY-MM-DD (example: 2026-12-05).\n");
    }
    copyText(out, buffer, DATE_LEN);
}

void pauseScreen(void)
{
    char buffer[8];
    readLine("\nPress Enter to continue...", buffer, sizeof(buffer));
}

static int isLeapYear(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

static int daysInMonth(int y, int m)
{
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && isLeapYear(y))
        return 29;
    return days[m - 1];
}

int isValidDate(const char *date)
{
    int i, y, m, d;

    if (strlen(date) != 10)
        return 0;
    for (i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            if (date[i] != '-')
                return 0;
        } else if (!isdigit((unsigned char)date[i])) {
            return 0;
        }
    }
    sscanf(date, "%d-%d-%d", &y, &m, &d);
    if (y < 2000 || y > 2100 || m < 1 || m > 12)
        return 0;
    return d >= 1 && d <= daysInMonth(y, m);
}

/* Converts a valid date to a day number, so two dates can be subtracted. */
long dateToDays(const char *date)
{
    int y = 0, m = 0, d = 0, i;
    long total = 0;

    sscanf(date, "%d-%d-%d", &y, &m, &d);
    for (i = 2000; i < y; i++)
        total += isLeapYear(i) ? 366 : 365;
    for (i = 1; i < m; i++)
        total += daysInMonth(y, i);
    return total + d;
}

int equalsIgnoreCase(const char *a, const char *b)
{
    while (*a != '\0' && *b != '\0') {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b))
            return 0;
        a++;
        b++;
    }
    return *a == *b;
}

void copyText(char *dest, const char *src, int size)
{
    strncpy(dest, src, size - 1);
    dest[size - 1] = '\0';
}

/* Finds the data folder even if the program is started from another folder. */
void dataPath(const char *fileName, char *out, int size)
{
    const char *folders[] = {"data", "../data"};
    char test[200];
    int i;

    for (i = 0; i < 2; i++) {
        FILE *fp;
        snprintf(test, sizeof(test), "%s/vehicles.csv", folders[i]);
        fp = fopen(test, "r");
        if (fp != NULL) {
            fclose(fp);
            snprintf(out, size, "%s/%s", folders[i], fileName);
            return;
        }
    }
    snprintf(out, size, "data/%s", fileName);
}

/* Splits one CSV line at commas. fields[] stores pointers into the line. */
int splitCSV(char *line, char *fields[], int maxFields)
{
    int count = 0;
    char *token;

    line[strcspn(line, "\r\n")] = '\0';
    token = strtok(line, ",");
    while (token != NULL && count < maxFields) {
        fields[count++] = token;
        token = strtok(NULL, ",");
    }
    return count;
}

/* Makes a dynamic array bigger when it is full (uses realloc). */
void *growArray(void *array, int count, int *capacity, size_t itemSize)
{
    void *bigger;
    int newCapacity;

    if (count < *capacity)
        return array;
    newCapacity = (*capacity == 0) ? 10 : *capacity * 2;
    bigger = realloc(array, newCapacity * itemSize);
    if (bigger == NULL) {
        printf("Memory allocation failed.\n");
        free(array);
        exit(1);
    }
    *capacity = newCapacity;
    return bigger;
}

/* Replaces the old CSV file with the newly written temporary file. */
int replaceFile(const char *tempPath, const char *realPath)
{
    remove(realPath);
    if (rename(tempPath, realPath) != 0) {
        printf("Error: could not save %s (close it if it is open in Excel).\n", realPath);
        return 0;
    }
    return 1;
}
