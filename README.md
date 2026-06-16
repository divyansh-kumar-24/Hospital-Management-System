
# Hospital Management System (C++ & MySQL)

## Overview

This project is a console-based Hospital Management System developed in C++ with MySQL integration. The application simulates various hospital operations such as patient admission, employee salary management, pharmacy calculations, billing, scan selection, and cafeteria services.

The primary objective of the project is to demonstrate Object-Oriented Programming (OOP) concepts in C++ while introducing persistent data storage using MySQL. The project models real-world hospital workflows and follows a layered architecture by separating business logic from database operations.

---

## Features

### 1. Patient Admission Management

- Admit new patients.
- Store patient details including:
  - Name
  - Age
  - Patient ID
- View patient information using Patient ID.
- Track available hospital capacity.
- Persist patient records in MySQL.

### 2. Employee Management

- Register employee details.
- Support multiple employee categories:
  - Doctor
  - Admin
  - Housekeeping
  - Maintenance
- Calculate monthly salary based on employee type and hours worked.
- Persist employee information and salary records in MySQL.

### 3. Pharmacy Module

- Calculate total supplier cost of tablets.
- Calculate total supplier cost of vials.
- Demonstrates function overloading.

### 4. Billing Module

- Calculate charges for:
  - General Ward stay
  - ICU stay
- Generate combined patient bill.
- Demonstrates operator overloading.
- Persist billing information in MySQL.

### 5. Scan Department

- Display available imaging services:
  - X-Ray
  - MRI
  - CT Scan
- Display estimated scan duration.
- Allow scan selection.
- Store scan booking information in MySQL.

### 6. Cafeteria Module

- Order food and beverages.
- Supported items:
  - Tea
  - Coffee
  - Sandwich
  - Cookie
- Calculate final cafeteria bill.
- Store cafeteria orders in MySQL.

---

## Project Architecture

```text
Presentation Layer (Console Menus)
                |
                v
Business Logic Layer
(Patient, Employee, Bill, Scan, Cafe Classes)
                |
                v
Persistence Layer
(Database, PatientDAO, EmployeeDAO, BillDAO, etc.)
                |
                v
MySQL Database
```

The separation of concerns makes the application easier to maintain, extend, and scale.

---

## Project Flow

```text
Start
  |
  v
Initialize Database Connection
  |
  v
Patient Admission System
  |
  +--> Add Patient
  |         |
  |         +--> INSERT INTO Patient
  |
  +--> View Patient Details
            |
            +--> SELECT FROM Patient
  |
  v
Employee Management
  |
  +--> Enter Employee Details
  +--> Calculate Salary
  +--> INSERT INTO Employee
  |
  v
Pharmacy Module
  |
  +--> Tablet Cost Calculation
  +--> Vial Cost Calculation
  |
  v
Billing Department
  |
  +--> General Ward Charges
  +--> ICU Charges
  +--> Total Bill Generation
  +--> INSERT INTO Bill
  |
  v
Scan Department
  |
  +--> View Scan Types
  +--> Select Scan
  +--> INSERT INTO ScanBooking
  |
  v
Cafeteria
  |
  +--> Order Food Items
  +--> Generate Food Bill
  +--> INSERT INTO CafeOrder
  |
  v
End
```

---

## Class Structure

```text
hospital
   |
   v
info
   |
   +------> patient
   |
   +------> employee

scan
   |
ptime
   |
   v
scantime


Database
   |
   +------> PatientDAO
   |
   +------> EmployeeDAO
   |
   +------> BillDAO
   |
   +------> ScanDAO
   |
   +------> CafeDAO
```

---

## Database Schema

### Patient Table

```sql
Patient(
    patient_id,
    name,
    age
)
```

### Employee Table

```sql
Employee(
    employee_id,
    name,
    age,
    type,
    salary
)
```

### Bill Table

```sql
Bill(
    bill_id,
    patient_id,
    fixed_charge,
    variable_charge,
    total
)
```

### ScanBooking Table

```sql
ScanBooking(
    scan_id,
    patient_id,
    scan_type,
    booking_time
)
```

### CafeOrder Table

```sql
CafeOrder(
    order_id,
    patient_id,
    amount,
    order_time
)
```

---

## OOP Concepts Demonstrated

| Concept | Implementation |
|---------|----------------|
| Classes and Objects | hospital, patient, employee, bill, cafe |
| Inheritance | patient → info → hospital |
| Multiple Inheritance | scantime inherits scan and ptime |
| Constructors | All major classes |
| Function Overloading | add(int,int), add(float,float) |
| Function Overriding | display() methods |
| Static Members | hospital capacity |
| Friend Function | calcsal(employee&) |
| Virtual Functions | display() in typesalthree |
| Runtime Polymorphism | Base pointer referencing derived object |
| Operator Overloading | bill + bill |
| Dynamic Memory Allocation | new cafe, delete cafe |
| Inline Functions | Welcome message functions |
| this Pointer | Parameterized bill constructor |
| Abstraction | Database and DAO classes hide SQL implementation details |
| Encapsulation | Private data members with controlled access through member functions |
| Separation of Concerns | Business logic separated from persistence layer |

---

## Technologies Used

- C++
- Object-Oriented Programming (OOP)
- Standard Template Library (STL)
- MySQL
- MySQL Connector/C API
- SQL (DDL and CRUD Operations)

---

## Learning Outcomes

This project helped in understanding:

- Real-world modelling using classes and objects
- Implementation of the pillars of OOP
- Function and operator overloading
- Runtime polymorphism and multiple inheritance
- Layered software architecture
- Database design and normalization
- CRUD operations using SQL
- Integration of C++ applications with MySQL
- Separation of business logic and persistence logic using DAO classes
- Designing scalable and maintainable software systems
