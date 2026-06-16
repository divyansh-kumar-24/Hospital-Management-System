
CREATE DATABASE IF NOT EXISTS hospital_db;
USE hospital_db;

CREATE TABLE IF NOT EXISTS Patient(
    patient_id INT PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    age INT NOT NULL
);

CREATE TABLE IF NOT EXISTS Employee(
    employee_id INT PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    age INT,
    type INT,
    salary FLOAT
);

CREATE TABLE IF NOT EXISTS Bill(
    bill_id INT AUTO_INCREMENT PRIMARY KEY,
    patient_id INT,
    fixed_charge FLOAT,
    variable_charge FLOAT,
    total FLOAT,
    FOREIGN KEY (patient_id)
        REFERENCES Patient(patient_id)
        ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS ScanBooking(
    scan_id INT AUTO_INCREMENT PRIMARY KEY,
    patient_id INT,
    scan_type VARCHAR(50),
    booking_time DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (patient_id)
        REFERENCES Patient(patient_id)
        ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS CafeOrder(
    order_id INT AUTO_INCREMENT PRIMARY KEY,
    patient_id INT,
    amount FLOAT,
    order_time DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (patient_id)
        REFERENCES Patient(patient_id)
        ON DELETE CASCADE
);
