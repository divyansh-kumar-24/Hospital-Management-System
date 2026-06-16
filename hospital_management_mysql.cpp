
// hospital_management_mysql.cpp
// Extension of the original Hospital Management System.
// All OOP demonstrations are preserved. MySQL is added only as a
// persistence layer (DAO classes + database connection).

#include <iostream>
#include <cstring>
#include <string>
#include <mysql/mysql.h>

using namespace std;

/* ---------------- DATABASE LAYER ---------------- */

class Database
{
    MYSQL *conn;

public:
    Database()
    {
        conn = mysql_init(NULL);

        conn = mysql_real_connect(
            conn,
            "localhost",
            "root",
            "password",     // CHANGE THIS
            "hospital_db",
            3306,
            NULL,
            0);

        if (conn)
            cout << "Database Connected\n";
        else
            cout << "Database Connection Failed\n";
    }

    MYSQL *getConn()
    {
        return conn;
    }

    ~Database()
    {
        if (conn)
            mysql_close(conn);
    }
};

/* ---------------- ORIGINAL OOP CLASSES ---------------- */

class hospital
{
public:
    static int capacity;
};

int hospital::capacity = 500;

class info : public hospital
{
protected:
    char name[50];
    int age;

public:
    info()
    {
        strcpy(name, "N/A");
        age = 0;
    }

    void get()
    {
        cout << "Enter Name: ";
        cin >> name;

        cout << "Enter Age: ";
        cin >> age;
    }

    void show()
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }

    char *getName() { return name; }
    int getAge() { return age; }
};

class patient : public info
{
    int id;

public:
    patient()
    {
        id = 0;
    }

    void get()
    {
        cout << "\nPatient Details\n";
        info::get();

        cout << "Enter Patient ID: ";
        cin >> id;

        cout << "Remaining Capacity: "
             << --capacity << endl;
    }

    void show()
    {
        cout << "\nPatient Details\n";
        info::show();
        cout << "Patient ID: " << id << endl;
    }

    int getId() { return id; }
};

class employee : public info
{
    int id;
    int type;
    float sal;

public:
    employee()
    {
        id = 0;
        type = 0;
        sal = 0;
    }

    void get()
    {
        cout << "\nEmployee Details\n";

        info::get();

        cout << "Employee ID: ";
        cin >> id;

        cout << "[1] Doctor\n";
        cout << "[2] Admin\n";
        cout << "[3] Housekeeping\n";
        cout << "[4] Maintenance\n";

        cout << "Type: ";
        cin >> type;
    }

    void show()
    {
        cout << "\nEmployee Details\n";
        info::show();

        cout << "Employee ID: " << id << endl;
        cout << "Type: " << type << endl;
        cout << "Salary: " << sal << endl;
    }

    int getId() { return id; }
    int getType() { return type; }
    float getSalary() { return sal; }

    friend void calcsal(employee &);
};

void calcsal(employee &e)
{
    int hours;

    cout << "Enter Hours Clocked: ";
    cin >> hours;

    switch (e.type)
    {
    case 1:
        e.sal = 5000 * hours;
        break;

    case 2:
        e.sal = 2000 * hours;
        break;

    case 3:
        e.sal = 1000 * hours;
        break;

    case 4:
        e.sal = 500 * hours;
        break;
    }
}

/* Function overloading demonstration */

void add(int a, int b)
{
    cout << "Tablet Total: " << a + b << endl;
}

void add(float a, float b)
{
    cout << "Vial Total: " << a + b << endl;
}

/* Operator overloading demonstration */

class bill
{
    int fixed;
    int variable;

public:
    bill()
    {
        fixed = variable = 0;
    }

    void set(int f, int v)
    {
        fixed = f;
        variable = v;
    }

    bill operator+(bill b) const
    {
        bill temp;
        temp.fixed = fixed + b.fixed;
        temp.variable = variable + b.variable;
        return temp;
    }

    int getFixed() { return fixed; }
    int getVariable() { return variable; }
};

/* Virtual function demonstration */

class typesalthree
{
public:
    virtual void display()
    {
        cout << "Type 3 Salary: Rs.1000/hr\n";
    }
};

class typesalfour : public typesalthree
{
public:
    void display()
    {
        cout << "Type 4 Salary: Rs.500/hr\n";
    }
};

/* Multiple inheritance demonstration */

class scan
{
public:
    void display()
    {
        cout << "Scans Available\n";
    }
};

class ptime
{
public:
    void display()
    {
        cout << "Time Information\n";
    }
};

class scantime : public scan, public ptime
{
};

/* ---------------- DAO CLASSES ---------------- */

class PatientDAO
{
    Database &db;

public:
    PatientDAO(Database &database)
        : db(database)
    {
    }

    void addPatient(patient &p)
    {
        MYSQL *conn = db.getConn();

        string query =
            "INSERT INTO Patient VALUES(" +
            to_string(p.getId()) +
            ",'" +
            string(p.getName()) +
            "'," +
            to_string(p.getAge()) +
            ")";

        mysql_query(conn, query.c_str());
    }

    void searchPatient(int id)
    {
        MYSQL *conn = db.getConn();

        string query =
            "SELECT * FROM Patient WHERE patient_id=" +
            to_string(id);

        mysql_query(conn, query.c_str());

        MYSQL_RES *res = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(res);

        if (row)
        {
            cout << "\nPatient Found\n";
            cout << "ID   : " << row[0] << endl;
            cout << "Name : " << row[1] << endl;
            cout << "Age  : " << row[2] << endl;
        }
        else
        {
            cout << "Patient Not Found\n";
        }

        mysql_free_result(res);
    }
};

class EmployeeDAO
{
    Database &db;

public:
    EmployeeDAO(Database &database)
        : db(database)
    {
    }

    void addEmployee(employee &e)
    {
        MYSQL *conn = db.getConn();

        string query =
            "INSERT INTO Employee VALUES(" +
            to_string(e.getId()) +
            ",'" +
            string(e.getName()) +
            "'," +
            to_string(e.getAge()) +
            "," +
            to_string(e.getType()) +
            "," +
            to_string(e.getSalary()) +
            ")";

        mysql_query(conn, query.c_str());
    }
};

class BillDAO
{
    Database &db;

public:
    BillDAO(Database &database)
        : db(database)
    {
    }

    void saveBill(int patientId, bill &b)
    {
        MYSQL *conn = db.getConn();

        string query =
            "INSERT INTO Bill(patient_id,fixed_charge,"
            "variable_charge,total) VALUES(" +
            to_string(patientId) +
            "," +
            to_string(b.getFixed()) +
            "," +
            to_string(b.getVariable()) +
            "," +
            to_string(b.getFixed() +
                      b.getVariable()) +
            ")";

        mysql_query(conn, query.c_str());
    }
};

/* ---------------- MAIN ---------------- */

int main()
{
    Database db;

    PatientDAO patientDAO(db);
    EmployeeDAO employeeDAO(db);
    BillDAO billDAO(db);

    patient p;
    p.get();
    patientDAO.addPatient(p);

    employee e;
    e.get();
    calcsal(e);
    employeeDAO.addEmployee(e);

    bill b1, b2, b3;

    b1.set(5000, 2000);
    b2.set(3000, 1000);

    b3 = b1 + b2;
    billDAO.saveBill(p.getId(), b3);

    typesalthree *ptr;
    typesalfour t4;

    ptr = &t4;
    ptr->display();

    scantime s;
    s.scan::display();
    s.ptime::display();

    add(100, 200);
    add(100.5f, 200.5f);

    return 0;
}
