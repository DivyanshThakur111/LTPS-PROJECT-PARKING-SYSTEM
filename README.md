# LTPS-PROJECT-PARKING-SYSTEM
PARKING SYSTEM

# Parking Management System

**A Mini Project in C Programming**
---

## 1. Introduction

Managing a parking lot by hand is slow and error-prone. Attendants have to remember which
slots are free, note down entry times, and work out the charges by themselves. This project is
a console-based **Parking Management System** written in C that automates these tasks.

The program allocates a slot to every incoming vehicle, records its entry time, calculates the
parking fee when the vehicle leaves, and keeps a record of the total money collected. All data
is stored in a file, so nothing is lost when the program is closed.

## 2. Objectives

- To apply the core concepts of C programming in a practical, real-life application.
- To automate slot allocation, billing and record keeping for a small parking lot.
- To practise structures, arrays, functions, file handling and string handling.
- To write safe, readable and well-organised code.

## 3. Features

| No. | Feature | Description |
|---|---|---|
| 1 | Park a vehicle | Assigns the first free slot and records the vehicle number, type and entry time |
| 2 | Remove vehicle and bill | Calculates the fee, prints a bill, frees the slot and adds the amount to revenue |
| 3 | Show parking status | Displays all 10 slots as Free or Occupied |
| 4 | Search vehicle | Tells which slot a given vehicle number is parked in |
| 5 | Show total revenue | Displays the total amount collected so far |
| 6 | Persistent storage | Saves and reloads all data automatically from a file |

**Parking charges**

| Vehicle type | Rate |
|---|---|
| Car | Rs 20 per hour |
| Bike | Rs 10 per hour |

Parked time is rounded **up** to the next full hour, and the minimum charge is one hour.
For example, 1 hour 10 minutes is billed as 2 hours.

## 4. Concepts of C Used

| Concept | Where it is used |
|---|---|
| Structures (`struct`) | `Slot` and `ParkingLot` store the parking data |
| Enumeration (`enum`) | `VehicleType` (CAR, BIKE) gives readable names to vehicle types |
| Arrays | An array of 10 `Slot` records represents the parking lot |
| Functions | The program is divided into small functions, one for each task |
| Loops and `switch` | The menu runs in a `do...while` loop and `switch` selects the action |
| Strings | `strcmp`, `strncpy`, `toupper` are used for vehicle numbers |
| Pointers | Slots and the lot are passed to functions by address |
| File handling | `fopen`, `fwrite`, `fread`, `fclose` store data in a binary file |
| Time library | `time()`, `difftime()`, `ctime()`, `strftime()` handle entry and exit time |
| Preprocessor macros | `#define` sets slot count and rates, so they are easy to change |

## 5. Data Structures

```c
typedef struct {
    int         occupied;          // 0 = free, 1 = occupied
    char        plate[PLATE_LEN];  // vehicle number
    VehicleType type;              // CAR or BIKE
    time_t      entryTime;         // time of entry
} Slot;

typedef struct {
    Slot   slots[TOTAL_SLOTS];     // all parking slots
    double revenue;                // total money collected
} ParkingLot;
```

## 6. Function Description

| Function | Purpose |
|---|---|
| `readLine()` | Reads a line of text safely using `fgets()` |
| `readInt()` | Reads a number from the user using `readLine()` |
| `toUpperStr()` | Converts a vehicle number to capital letters so that "mh12ab1234" and "MH12AB1234" match |
| `saveData()` / `loadData()` | Write the parking data to a file and read it back |
| `findFreeSlot()` | Returns the first empty slot, or -1 if the lot is full |
| `findByPlate()` | Returns the slot holding a given vehicle, or -1 if not found |
| `calculateFee()` | Converts parked seconds to hours (rounded up) and multiplies by the rate |
| `parkVehicle()` | Handles vehicle entry |
| `removeVehicle()` | Handles vehicle exit and prints the bill |
| `displayStatus()` | Prints the status of every slot |
| `searchVehicle()` | Searches for a vehicle by number |
| `showRevenue()` | Prints the total revenue |
| `main()` | Loads data, shows the menu repeatedly and calls the chosen function |

## 7. Working of the Program

1. On start-up, `loadData()` reads `parking.dat`. If the file does not exist, the lot starts empty.
2. The menu is shown and the user enters a choice.
3. **Entry:** the program checks that a slot is free, that the vehicle is not already parked and
   that the type is valid. It then stores the details with the current time and saves the file.
4. **Exit:** the program finds the vehicle, finds the time spent with `difftime()`, calculates
   the fee, prints the bill, clears the slot, adds the fee to the revenue and saves the file.
5. The loop continues until the user chooses **Exit**, and the data is saved one last time.

## 8. Sample Output

**Parking status**

```
Slot   Status     Vehicle      Type   Since
---------------------------------------------------------
1      Free       -            -      -
2      Occupied   DL5SX99      Bike   03-11 09:16
3      Free       -            -      -
...
Occupied: 1   Free: 9   Total: 10
```

**Parking bill**

```
------ PARKING BILL ------
Vehicle : MH12AB1234 (Car)
Slot    : 1
Entry   : Tue Nov  3 09:16:43 2026
Exit    : Tue Nov  3 09:16:43 2026
Hours   : 1
Amount  : Rs 20.00
--------------------------
```

## 9. How to Compile and Run

**Using VS Code**

1. Install a C compiler (GCC) and the Microsoft **C/C++** extension.
2. Open the `parking-system` folder in VS Code (File > Open Folder).
3. Press `Ctrl+Shift+B` to build. Press `F5` to run with the debugger.

**Using the terminal**

```
gcc -Wall -Wextra -g main.c -o parking
./parking          (on Windows: parking.exe)
```

## 10. Project Files

| File | Description |
|---|---|
| `main.c` | Complete source code |
| `.vscode/tasks.json` | Build configuration for VS Code |
| `.vscode/launch.json` | Debug configuration for VS Code |
| `parking.dat` | Data file, created automatically when the program runs |
| `README.md` | This report |

## 11. Limitations

- The lot has a fixed number of slots (10), set at compile time.
- Only two vehicle types (car and bike) are supported.
- There is no login, so anyone who runs the program can use every option.
- Data is kept in a binary file that cannot be read in a text editor.

## 12. Future Scope

- Make the number of slots and rates configurable at run time.
- Add more vehicle types such as trucks and buses.
- Add an admin password and a printable billing history.
- Add slot reservation and monthly pass options.
- Build a graphical interface for easier use.

## 13. Conclusion

This project shows how the basic features of C, such as structures, arrays, functions, file
handling and the time library, can be combined to solve a real-world problem. The system
allocates slots, bills customers accurately and saves records between runs. Working on it gave
practical experience in program design, input validation and debugging, and it can be extended
with the features listed above.

