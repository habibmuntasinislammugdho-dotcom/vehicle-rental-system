/* utils.h - input, validation, date and CSV helper functions (team file) */
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

/* Input */
void readLine(const char *prompt, char *out, int size);
void readText(const char *prompt, char *out, int size);   /* not empty, no comma */
int  readInt(const char *prompt, int min, int max);
double readMoney(const char *prompt);
int  readYesNo(const char *prompt);                       /* 1 = yes, 0 = no */
void readDate(const char *prompt, char *out);             /* YYYY-MM-DD */
void pauseScreen(void);

/* Date */
int  isValidDate(const char *date);
long dateToDays(const char *date);

/* String */
int  equalsIgnoreCase(const char *a, const char *b);
void copyText(char *dest, const char *src, int size);

/* CSV and memory */
void  dataPath(const char *fileName, char *out, int size);
int   splitCSV(char *line, char *fields[], int maxFields);
void *growArray(void *array, int count, int *capacity, size_t itemSize);
int   replaceFile(const char *tempPath, const char *realPath);

#endif
