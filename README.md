
# Medical System Admin Panel

A command-line application built with C++ and SQLite for managing patient and doctor records in a medical system. This project provides basic CRUD (Create, Read, Update, Delete) operations for patient and doctor data, along with a simple billing feature that calculates charges with GST.

## Features

- **Database Management**: Uses SQLite to store and manage patient and doctor records.
- **Patient Records**: Add, update, delete, and display patient information (name, age, gender).
- **Doctor Records**: Add, update, delete, and display doctor information (name, age, gender, department, salary).
- **Billing**: Calculate basic service charges with an 18% GST.
- **Admin Access**: Password-protected admin panel (default password: `1234`).
- **Current Date Display**: Shows the current date upon login.
- **Interactive Menu**: Simple command-line interface for admin operations.

## Prerequisites

- **C++ Compiler**: A C++11 or later compatible compiler (e.g., `g++`).
- **SQLite3**: SQLite library installed on your system.
  - On Ubuntu: `sudo apt-get install libsqlite3-dev`
  - On macOS: `brew install sqlite`
  - On Windows: Download SQLite DLL and headers from [sqlite.org](https://www.sqlite.org/download.html) and link them during compilation.

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/medical-system-admin.git
   cd medical-system-admin
   ```

2. **Compile the Code**:
   Use the following command to compile the application with `g++`:
   ```bash
   g++ -o medical_system main.cpp -lsqlite3
   ```
   - Replace `main.cpp` with the actual filename if different.
   - On Windows, you may need to specify the SQLite library path (e.g., `-L"path\to\sqlite" -lsqlite3`).

3. **Run the Application**:
   ```bash
   ./medical_system
   ```

## Usage

1. **Login**:
   - Launch the application and enter the admin password (`1234` by default).
   - Upon successful login, the current date is displayed, and the admin menu appears.

2. **Admin Menu Options**:
   - **1. Insert Patient & Doctor**: Add a new patient and doctor record, followed by entering service charges to calculate total with GST.
   - **2. Update Record**: Update a patient’s name or a doctor’s salary by ID.
   - **3. Delete Record**: Delete a patient or doctor record by ID.
   - **4. Display Records**: View all patient and doctor records.
   - **5. Exit**: Close the application.

3. **Sample Interaction**:
   ```
   Enter Admin Password: 1234
   Access Granted. Welcome to the Medical System Admin Panel.
   Date: 2025-03-17

   --- Admin Menu ---
   1. Insert Patient & Doctor
   2. Update Record
   3. Delete Record
   4. Display Records
   5. Exit
   Choose an option: 1

   Enter Patient Name: John
   Enter Patient Age: 30
   Enter Patient Gender: Male
   ```

4. **Database**:
   - The application creates a file named `medical_system.db` in the working directory to store data persistently.

## Project Structure

- `main.cpp`: The main source file containing the application logic.
- `medical_system.db`: SQLite database file (created automatically on first run).

## Dependencies

- **SQLite3**: Embedded database library for data storage.
- **Standard C++ Libraries**: `<iostream>`, `<string>`, `<iomanip>`, `<ctime>`.

## Notes

- The SQLite shell code (`shell.c`) included in the submission is part of the SQLite library and not directly used in this application. It is likely included for reference or potential future integration.
- Error handling is minimal; ensure valid inputs to avoid crashes.
- The admin password is hardcoded (`1234`) and should be modified for security in a production environment.

## Contributing

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/your-feature`).
3. Make your changes and commit (`git commit -m "Add your message"`).
4. Push to your branch (`git push origin feature/your-feature`).
5. Open a pull request.

## License

This project is open-source and available under the [MIT License](LICENSE). See the `LICENSE` file for details.

## Acknowledgments

- Built with [SQLite](https://www.sqlite.org/) for lightweight database management.
- Inspired by simple command-line database applications.

---

### Notes for Customization
- Replace `yourusername/medical-system-admin` with your actual GitHub username and repository name.
- If you plan to include additional features (e.g., integrating the SQLite shell), update the README accordingly.
- Add a `LICENSE` file to your repository if you choose the MIT License or another license.

Let me know if you’d like to refine this further!
