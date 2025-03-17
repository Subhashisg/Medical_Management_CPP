#include <sqlite3.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

void getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    cout << "Date: " << 1900 + ltm->tm_year << "-"
         << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
         << setw(2) << setfill('0') << ltm->tm_mday << endl;
}

void insertData(sqlite3* db) {
    string patientName, patientGender;
    int patientAge;
    cout << "\nEnter Patient Name: ";
    cin >> patientName;
    cout << "Enter Patient Age: ";
    cin >> patientAge;
    cout << "Enter Patient Gender: ";
    cin >> patientGender;

    const char* insertPatient = "INSERT INTO Patients (Name, Age, Gender) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, insertPatient, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, patientName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, patientAge);
    sqlite3_bind_text(stmt, 3, patientGender.c_str(), -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    string doctorName, doctorGender, doctorDepartment;
    int doctorAge, doctorSalary;
    cout << "\nEnter Doctor Name: ";
    cin >> doctorName;
    cout << "Enter Doctor Age: ";
    cin >> doctorAge;
    cout << "Enter Doctor Gender: ";
    cin >> doctorGender;
    cout << "Enter Doctor Department: ";
    cin >> doctorDepartment;
    cout << "Enter Doctor Salary: ";
    cin >> doctorSalary;

    const char* insertDoctor = "INSERT INTO Doctors (Name, Age, Gender, Department, Salary) VALUES (?, ?, ?, ?, ?);";
    sqlite3_prepare_v2(db, insertDoctor, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, doctorName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, doctorAge);
    sqlite3_bind_text(stmt, 3, doctorGender.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, doctorDepartment.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, doctorSalary);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    double charges;
    cout << "\nEnter basic service charges: ₹";
    cin >> charges;

    double gst = charges * 0.18;
    double total = charges + gst;

    cout << fixed << setprecision(2);
    cout << "GST (18%): ₹" << gst << endl;
    cout << "Total Amount (with GST): ₹" << total << endl;
}

void displayData(sqlite3* db) {
    sqlite3_stmt* stmt;
    cout << "\nPatients Table:\n";
    const char* selectPatients = "SELECT * FROM Patients;";
    if (sqlite3_prepare_v2(db, selectPatients, -1, &stmt, 0) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            cout << "ID: " << sqlite3_column_int(stmt, 0)
                 << ", Name: " << sqlite3_column_text(stmt, 1)
                 << ", Age: " << sqlite3_column_int(stmt, 2)
                 << ", Gender: " << sqlite3_column_text(stmt, 3) << endl;
        }
    }
    sqlite3_finalize(stmt);

    cout << "\nDoctors Table:\n";
    const char* selectDoctors = "SELECT * FROM Doctors;";
    if (sqlite3_prepare_v2(db, selectDoctors, -1, &stmt, 0) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            cout << "ID: " << sqlite3_column_int(stmt, 0)
                 << ", Name: " << sqlite3_column_text(stmt, 1)
                 << ", Age: " << sqlite3_column_int(stmt, 2)
                 << ", Gender: " << sqlite3_column_text(stmt, 3)
                 << ", Department: " << sqlite3_column_text(stmt, 4)
                 << ", Salary: ₹" << sqlite3_column_int(stmt, 5) << endl;
        }
    }
    sqlite3_finalize(stmt);
}

void updateData(sqlite3* db) {
    int id;
    cout << "\nUpdate Options:\n1. Patient\n2. Doctor\nSelect (1/2): ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        string newName;
        cout << "Enter Patient ID to update: ";
        cin >> id;
        cout << "Enter new name: ";
        cin >> newName;

        const char* updatePatient = "UPDATE Patients SET Name = ? WHERE ID = ?;";
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, updatePatient, -1, &stmt, 0);
        sqlite3_bind_text(stmt, 1, newName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, id);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        cout << "Patient updated successfully.\n";
    } else if (choice == 2) {
        int newSalary;
        cout << "Enter Doctor ID to update: ";
        cin >> id;
        cout << "Enter new salary: ";
        cin >> newSalary;

        const char* updateDoctor = "UPDATE Doctors SET Salary = ? WHERE ID = ?;";
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, updateDoctor, -1, &stmt, 0);
        sqlite3_bind_int(stmt, 1, newSalary);
        sqlite3_bind_int(stmt, 2, id);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        cout << "Doctor updated successfully.\n";
    }
}

void deleteData(sqlite3* db) {
    int id;
    cout << "\nDelete Options:\n1. Patient\n2. Doctor\nSelect (1/2): ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "Enter Patient ID to delete: ";
        cin >> id;
        const char* deletePatient = "DELETE FROM Patients WHERE ID = ?;";
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, deletePatient, -1, &stmt, 0);
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        cout << "Patient deleted.\n";
    } else if (choice == 2) {
        cout << "Enter Doctor ID to delete: ";
        cin >> id;
        const char* deleteDoctor = "DELETE FROM Doctors WHERE ID = ?;";
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, deleteDoctor, -1, &stmt, 0);
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        cout << "Doctor deleted.\n";
    }
}

int main() {
    const string ADMIN_PASSWORD = "1234";
    string enteredPassword;

    cout << "Enter Admin Password: ";
    cin >> enteredPassword;

    if (enteredPassword != ADMIN_PASSWORD) {
        cerr << "Access Denied. Incorrect password." << endl;
        return 1;
    }

    cout << "\nAccess Granted. Welcome to the Medical System Admin Panel.\n";
    getCurrentDate();

    sqlite3* db;
    int rc = sqlite3_open("medical_system.db", &db);
    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    }

    const char* createPatientsTable = "CREATE TABLE IF NOT EXISTS Patients ("
                                      "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                                      "Name TEXT NOT NULL,"
                                      "Age INT,"
                                      "Gender TEXT);";

    const char* createDoctorsTable = "CREATE TABLE IF NOT EXISTS Doctors ("
                                     "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                                     "Name TEXT NOT NULL,"
                                     "Age INT,"
                                     "Gender TEXT,"
                                     "Department TEXT,"
                                     "Salary INT);";

    char* errMsg = nullptr;
    sqlite3_exec(db, createPatientsTable, 0, 0, &errMsg);
    sqlite3_exec(db, createDoctorsTable, 0, 0, &errMsg);

    int option;
    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Insert Patient & Doctor\n";
        cout << "2. Update Record\n";
        cout << "3. Delete Record\n";
        cout << "4. Display Records\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> option;

        switch (option) {
            case 1:
                insertData(db);
                break;
            case 2:
                updateData(db);
                break;
            case 3:
                deleteData(db);
                break;
            case 4:
                displayData(db);
                break;
            case 5:
                cout << "Exiting Admin Panel.\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while (option != 5);

    sqlite3_close(db);
    return 0;
}
