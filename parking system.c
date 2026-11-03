
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define SLOTS 10
#define FILE_NAME "parking.dat"

const char *TYPE[]   = {"", "Car", "Bike"};   /* index = vehicle type  */
const double RATE[]  = {0, 20.0, 10.0};      /* Rs per hour           */

typedef struct {
    int    type;          /* 0 = free slot, 1 = Car, 2 = Bike */
    char   plate[20];
    time_t entry;
} Slot;

Slot   lot[SLOTS];
double revenue = 0;

/* read a line from the keyboard (safe replacement for scanf) */
void input(const char *msg, char *buf, int size) {
    printf("%s", msg);
    if (!fgets(buf, size, stdin)) buf[0] = '\0';
    buf[strcspn(buf, "\n")] = '\0';
}

/* ask for a vehicle number and make it uppercase */
void getPlate(char *p) {
    input("Enter vehicle number: ", p, 20);
    for (int i = 0; p[i]; i++) p[i] = toupper((unsigned char)p[i]);
}

/* return slot index of a plate, or of the first free slot if plate is NULL; -1 if none */
int find(const char *plate) {
    for (int i = 0; i < SLOTS; i++)
        if (plate ? (lot[i].type && !strcmp(lot[i].plate, plate)) : !lot[i].type)
            return i;
    return -1;
}

void save(void) {
    FILE *f = fopen(FILE_NAME, "wb");
    if (!f) return;
    fwrite(lot, sizeof lot, 1, f);
    fwrite(&revenue, sizeof revenue, 1, f);
    fclose(f);
}

void load(void) {
    FILE *f = fopen(FILE_NAME, "rb");
    if (!f) return;
    if (fread(lot, sizeof lot, 1, f) != 1 || fread(&revenue, sizeof revenue, 1, f) != 1) {
        memset(lot, 0, sizeof lot);
        revenue = 0;
    }
    fclose(f);
}

void parkVehicle(void) {
    int i = find(NULL);
    if (i < 0) { printf("Parking is FULL!\n"); return; }

    char plate[20], t[8];
    getPlate(plate);
    if (!plate[0] || find(plate) >= 0) { printf("Invalid or already parked.\n"); return; }

    input("Type (1 = Car, 2 = Bike): ", t, sizeof t);
    if (atoi(t) != 1 && atoi(t) != 2) { printf("Invalid type.\n"); return; }

    lot[i].type = atoi(t);
    lot[i].entry = time(NULL);
    strcpy(lot[i].plate, plate);
    save();
    printf("%s %s parked at slot %d.\n", TYPE[lot[i].type], plate, i + 1);
}

void removeVehicle(void) {
    char plate[20];
    getPlate(plate);
    int i = find(plate);
    if (i < 0) { printf("Vehicle not found.\n"); return; }

    time_t now = time(NULL);
    int hours = (int)((difftime(now, lot[i].entry) + 3599) / 3600);   /* round up */
    if (hours < 1) hours = 1;
    double fee = hours * RATE[lot[i].type];

    printf("\n--- BILL ---\nVehicle: %s (%s)\nSlot: %d\nHours: %d\nAmount: Rs %.2f\n------------\n",
           plate, TYPE[lot[i].type], i + 1, hours, fee);
    revenue += fee;
    memset(&lot[i], 0, sizeof(Slot));
    save();
}

void showStatus(void) {
    printf("\nSlot  Status    Vehicle     Type\n");
    for (int i = 0; i < SLOTS; i++)
        if (lot[i].type) printf("%-5d Occupied  %-11s %s\n", i + 1, lot[i].plate, TYPE[lot[i].type]);
        else             printf("%-5d Free\n", i + 1);
}

int main(void) {
    char c[8], plate[20];
    int i;
    load();
    do {
        printf("\n1.Park  2.Remove & Bill  3.Status  4.Search  5.Revenue  6.Exit\n");
        input("Choice: ", c, sizeof c);
        switch (atoi(c)) {
            case 1: parkVehicle(); break;
            case 2: removeVehicle(); break;
            case 3: showStatus(); break;
            case 4: getPlate(plate); i = find(plate);
                    if (i < 0) printf("Not found.\n");
                    else printf("Parked at slot %d.\n", i + 1);
                    break;
            case 5: printf("Total revenue: Rs %.2f\n", revenue); break;
            case 6: save(); printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (atoi(c) != 6);
    return 0;
}
