# Vehicle Rental System
[Mugdho](https://github.com/habibmuntasinislammugdho-dotcom)
## About the Project
The **Vehicle Rental System** is a student capstone project developed using the C programming language and file handling. It is designed to demonstrate how a simple vehicle rental process can be managed through a menu-driven program.

The system focuses on keeping vehicle records, checking availability, managing rental bookings, and calculating rental costs.

## Project Objectives
- Manage vehicle information and rental bookings.
- Allow administrative staff to add, remove, and update vehicle records.
- Show customers which vehicles are available for rent.
- Record rental periods and monitor ongoing rentals.
- Process vehicle returns and update vehicle availability.
- Estimate and calculate rental charges based on rental duration, vehicle type, and additional fees.
- Store and retrieve records using file handling so that data can be retained between program runs.

## Planned Features
### 1. Vehicle Management
- Add a new vehicle.
- View the list of registered vehicles.
- Update vehicle details.
- Remove a vehicle record.
- Track whether a vehicle is available or rented.

### 2. Rental Booking
- Browse available vehicles.
- Select a vehicle and enter the rental period.
- Create and view rental bookings.
- Track ongoing rentals.

### 3. Return Processing
- Record a vehicle return.
- Update the vehicle's status to available.
- Calculate the final rental charge when appropriate.

### 4. Billing
- Estimate the rental cost before booking.
- Calculate the total charge using the rental duration and vehicle's rate.
- Include any additional fees configured by the program.

### 5. File Handling
- Save vehicle and booking records to files.
- Load saved records when the program starts.
- Update files when records change.

> **Note:** These are the project's planned features. The final implementation may vary depending on the team's requirements and progress.

## Technologies
- **Programming language:** C
- **Data storage:** Files using C file-handling functions
- **Development approach:** Menu-driven console application

## Getting Started
### Prerequisites
- A C compiler, such as GCC, or an IDE that supports C.
- A terminal or command prompt to run the program.

### Compile
After the team creates the source file (for example, `main.c`), compile it with GCC:

```bash
gcc main.c -o vehicle_rental
```

### Run
On Linux or macOS:

```bash
./vehicle_rental
```

On Windows:

```bash
vehicle_rental.exe
```

The compile and run commands may need to be adjusted if the project uses multiple `.c` files.

## Example Workflow
1. Start the program.
2. Choose an option from the main menu.
3. Add or browse vehicle records.
4. Create a rental booking and enter the rental duration.
5. View the estimated or final rental cost.
6. Process the return and update the vehicle's availability.
7. Exit the program; saved records can be loaded the next time it runs.

## Project Structure
The structure below is a suggested starting point. Adjust it to match the files actually created by the team.

```text
vehicle-rental-system/
├── main.c
├── vehicles.txt       # Example data file; created/used by the program
├── bookings.txt       # Example data file; created/used by the program
└── README.md
```

## Team Members
Add your team members' names and student IDs here:

- Member 1: Mugdho — Student Id : 253-35-090
- Member 2: Shuchi — Student ID : 253-35-159
- Member 3: Saif   — Student ID : 253-35-277
- Member 4: Makama — Student ID : 253-35-050
- Member 5: Mutasim— Student ID : 253-35-639

## Current Status
**Project stage:** Capstone Project  — Student development project.

Update this section as the team implements and tests each feature.

## Future Improvements
- Add customer details and booking history.
- Validate input and handle file errors more robustly.
- Prevent bookings when a vehicle is already rented.
- Improve billing rules and display a clear cost breakdown.
- Add search and sorting options for vehicles.
- Expand testing for invalid input and edge cases.

## Learning Outcomes
Through this project, the team aims to practise:
- C structures, functions, loops, and conditional statements.
- File input and output.
- Basic record management.
- Applying problem-solving and software design skills to a practical scenario.
- Testing and documenting a small software project.

## Academic Disclaimer
This is an educational project created for learning and demonstration purposes. It is not intended to be used as a production vehicle-rental service.

---
**Capstone Project  — Vehicle Rental System**

