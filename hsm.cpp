#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct User
{
    string username;
    string password;
};

vector<User> readUserCredentials(const string& filename)
{
    vector<User> users;
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return vector<User>();
    }
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string username, password;
        if (getline(iss, username, ',') && getline(iss, password, ','))
        {
            users.push_back({ username, password });
        }
    }
    file.close();
    return users;
}

struct Patient
{
    string email;
    string password;
    string firstname;
    string lastname;
    int age;
    char gender;
    string message;
    vector<string> medicalHistory;
    vector<string> testResults;
};

struct Doctor
{
    string email;
    string firstname;
    string password;
    string lastname;
    int age;
    char gender;
    vector<string> availability;
    vector<string> appointments;
    vector<string> messages;
};

vector<Patient> patients;
vector<Doctor> doctors;

void readPatients(const string& filename)
{
    patients.clear();
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string email, firstname, lastname;
        int age;
        char gender;
        if (getline(iss, email, ',') && getline(iss, firstname, ',') && getline(iss, lastname, ','))
        {
            iss >> age;
            iss.ignore(); // Ignore the comma after age
            iss >> gender;
            patients.push_back({ email, "", firstname, lastname, age, gender });
        }
    }
    file.close();
}

void readDoctors(const string& filename)
{
    doctors.clear();
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string email, firstname, lastname;
        int age;
        char gender;
        if (getline(iss, email, ',') && getline(iss, firstname, ',') && getline(iss, lastname, ','))
        {
            iss >> age;
            iss.ignore(); // Ignore the comma after age
            iss >> gender;
            doctors.push_back({ email, firstname, "", lastname, age, gender });
        }
    }
    file.close();
}

void updatePatientData(const string& filename, const string& userEmail)
{
    auto it = find_if(patients.begin(), patients.end(), [&](const Patient& p)
        { return p.email == userEmail; });
    if (it != patients.end())
    {
        cout << "Update your information:" << endl;
        cout << "Enter your first name: ";
        cin >> it->firstname;
        cout << "Enter your last name: ";
        cin >> it->lastname;
        cout << "Enter your age: ";
        cin >> it->age;
        cout << "Enter your gender (M/F): ";
        cin >> it->gender;
        ofstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        for (const Patient& patient : patients)
        {
            file << patient.email << "," << patient.firstname << "," << patient.lastname << "," << patient.age << "," << patient.gender << endl;
        }
        file.close();
        cout << "User information updated successfully." << endl;
    }
    else
    {
        cout << "Error: User with email " << userEmail << " not found." << endl;
    }
}

void updateDoctorData(const string& filename, const string& doctorEmail)
{
    auto it = find_if(doctors.begin(), doctors.end(), [&](const Doctor& d)
        { return d.email == doctorEmail; });
    if (it != doctors.end())
    {
        cout << "Update your information:" << endl;
        cout << "Enter your first name: ";
        cin >> it->firstname;
        cout << "Enter your last name: ";
        cin >> it->lastname;
        cout << "Enter your age: ";
        cin >> it->age;
        cout << "Enter your gender (M/F): ";
        cin >> it->gender;
        ofstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        for (const Doctor& doctor : doctors)
        {
            file << doctor.email << "," << doctor.firstname << "," << doctor.lastname << "," << doctor.age << "," << doctor.gender << endl;
        }
        file.close();
        cout << "User information updated successfully." << endl;
    }
    else
    {
        cout << "Error: Doctor with email " << doctorEmail << " not found." << endl;
    }
}

void handle(const string& filename, const string& userType)
{
    vector<User> users = readUserCredentials(filename);
    if (users.empty())
    {
        cerr << "Error: No users found in file." << endl;
        return;
    }
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    bool loginSuccess = false;
    for (const User& user : users)
    { // here
        if (user.username == username && user.password == password)
        { // here
            loginSuccess = true;
            break;
        }
    }
    if (loginSuccess)
    {
        cout << "Login successful!" << endl;
    }
    else
    {
        cout << "Invalid username or password. Login failed." << endl;
    }
}

void signupPatient()
{
    Patient newPatient;
    cout << "Enter your E-mail:" << endl;
    cin >> newPatient.email;
    if (find_if(patients.begin(), patients.end(), [&](const Patient& p)
        { return p.email == newPatient.email; }) != patients.end())
    {
        cout << "Error: Email already exists." << endl;
        return;
    }
    string password;
    cout << "Enter your password:" << endl;
    cin >> password;
    newPatient.password = password;
    cout << "Enter your first name:" << endl;
    cin >> newPatient.firstname;
    cout << "Enter your last name:" << endl;
    cin >> newPatient.lastname;
    cout << "Enter your age:" << endl;
    cin >> newPatient.age;
    while (newPatient.age <= 0)
    {
        cout << "Invalid age. Please enter a positive integer:" << endl;
        cin >> newPatient.age;
    }
    cout << "Enter your gender (M/F):" << endl;
    cin >> newPatient.gender;
    while (newPatient.gender != 'M' && newPatient.gender != 'F')
    {
        cout << "Invalid gender. Please enter 'M' or 'F':" << endl;
        cin >> newPatient.gender;
    }
    cout << "Signup Successful!" << endl;
    patients.push_back(newPatient);
    ofstream my_file("patient.csv", ios::app);
    if (!my_file)
    {
        cout << "Error occurred while opening the file 'patient.csv'" << endl;
        return;
    }
    my_file << newPatient.email << "," << newPatient.password << "," << newPatient.firstname << "," << newPatient.lastname << "," << newPatient.age << "," << newPatient.gender << endl;
    my_file.close();
}

void signupDoctor()
{
    Doctor newDoctor;
    cout << "Enter your E-mail:" << endl;
    cin >> newDoctor.email;
    if (find_if(doctors.begin(), doctors.end(), [&](const Doctor& d)
        { return d.email == newDoctor.email; }) != doctors.end())
    {
        cout << "Error: Email already exists." << endl;
        return;
    }
    string password;
    cout << "Enter your password:" << endl;
    cin >> newDoctor.password;
    cout << "Enter your first name:" << endl;
    cin >> newDoctor.firstname;
    cout << "Enter your last name:" << endl;
    cin >> newDoctor.lastname;
    cout << "Enter your age:" << endl;
    cin >> newDoctor.age;
    while (newDoctor.age <= 0)
    {
        cout << "Invalid age. Please enter a positive integer:" << endl;
        cin >> newDoctor.age;
    }
    cout << "Enter your gender (M/F):" << endl;
    cin >> newDoctor.gender;
    while (newDoctor.gender != 'M' && newDoctor.gender != 'F')
    {
        cout << "Invalid gender. Please enter 'M' or 'F':" << endl;
        cin >> newDoctor.gender;
    }
    cout << "Signup Successful!" << endl;
    ofstream my_file("doctor.csv", ios::app);
    if (!my_file)
    {
        cout << "Error occurred while opening the file 'doctor.csv'" << endl;
        return;
    }
    my_file << newDoctor.email << "," << newDoctor.password << "," << newDoctor.firstname << "," << newDoctor.lastname << "," << newDoctor.age << "," << newDoctor.gender << endl;
    my_file.close();
    doctors.push_back(newDoctor);
}

void setDoctorAvailability(vector<Doctor>& doctors)
{
    string email;
    cout << "Enter your email to set availability: ";
    cin >> email;
    for (Doctor& doc : doctors)
    {
        if (doc.email == email)
        {
            cout << "Enter your availability slots (e.g., Monday 9-12, Tuesday 14-17):" << endl;
            string availabilityInput;
            cin.ignore();
            getline(cin, availabilityInput);
            doc.availability.push_back(availabilityInput);
            cout << "Availability set successfully." << endl;
            return;
        }
    }
    cout << "Doctor with email " << email << " not found." << endl;
}

bool isDoctorAvailable(const Doctor& doc, const string& timeSlot)
{
    for (const string& slot : doc.availability)
    {
        if (slot == timeSlot)
        {
            return true;
        }
    }
    return false;
}

void bookAppointment(vector<Doctor>& doctors)
{
    string patientEmail, doctorEmail, timeSlot;
    cout << "Enter patient's email: ";
    cin >> patientEmail;
    cout << "Enter doctor's email: ";
    cin >> doctorEmail;
    cout << "Enter desired appointment time slot: ";
    cin >> timeSlot;
    auto it = find_if(doctors.begin(), doctors.end(), [&](const Doctor& d)
        { return d.email == doctorEmail; });
    if (it != doctors.end())
    {
        cout << "Booking appointment for " << patientEmail << " with " << doctorEmail << " at " << timeSlot << endl;
        it->appointments.push_back(timeSlot); // Add appointment to doctor's list
        cout << "Appointment booked successfully!" << endl;
    }
    else
    {
        cout << "Error: Doctor with email " << doctorEmail << " not found." << endl;
    }
}

void updateAppointment(vector<Doctor>& doctors, const string& patientEmail)
{
    string newDoctorEmail, newTimeSlot;
    cout << "Enter new doctor's email: ";
    cin >> newDoctorEmail;
    cout << "Enter new appointment time slot: ";
    cin >> newTimeSlot;
    for (Doctor& doc : doctors)
    {
        if (doc.email == newDoctorEmail)
        {
            if (isDoctorAvailable(doc, newTimeSlot))
            {
                cout << "Appointment updated successfully." << endl;
                return;
            }
            else
            {
                cout << "Doctor is not available at the specified time slot." << endl;
                return;
            }
        }
    }
    cout << "Doctor with email " << newDoctorEmail << " not found." << endl;
}

void viewAppointments(const vector<Doctor>& doctors)
{
    for (const Doctor& doctor : doctors)
    {
        cout << "Appointments for Dr. " << doctor.firstname << " " << doctor.lastname << ":" << endl;
        for (const string& appointment : doctor.appointments)
        {
            cout << appointment << endl;
        }
    }
}

void cancelAppointment(vector<Doctor>& doctors)
{
    string doctorEmail, timeSlot;
    cout << "Enter doctor's email: ";
    cin >> doctorEmail;
    cout << "Enter appointment time slot: ";
    cin >> timeSlot;
    for (Doctor& doctor : doctors)
    {
        if (doctor.email == doctorEmail)
        {
            auto it = find(doctor.appointments.begin(), doctor.appointments.end(), timeSlot);
            if (it != doctor.appointments.end())
            {
                doctor.appointments.erase(it);
                cout << "Appointment canceled successfully." << endl;
                return;
            }
            else
            {
                cout << "Appointment not found for the specified time slot." << endl;
                return;
            }
        }
    }
    cout << "Doctor with email " << doctorEmail << " not found." << endl;
}

// Function to delete user data
void deleteUser(const string& filename, const string& userEmail)
{
    ifstream InputFile(filename);
    // string userEmail;

    // Create a temporary file
    ofstream tempFile("temp.csv");
    if (!tempFile)
    {
        cerr << "Error creating temporary file." << endl;
        //  filename.close();
        return;
    }

    // Variables to track if user found
    bool found = false;

    // Read and process each line from the input file
    string line;
    while (getline(InputFile, line))
    {
        // Extract email from the line
        string email = line.substr(0, line.find(','));

        // If the email matches, skip writing to temporary file
        // This effectively deletes the user from the new file
        if (email == userEmail)
        {
            found = true;
            continue;
        }

        // Write the line to the temporary file
        tempFile << line << endl;
    }

    // Close both files
    InputFile.close();
    tempFile.close();

    // Check if user was found
    if (!found)
    {
        cerr << "User not found." << endl;
        // Remove the temporary file
        remove("temp.csv");
        return;
    }

    // Replace the original file with the temporary file
    remove(filename.c_str());
    rename("temp.csv", filename.c_str());

    cout << "User data deleted successfully." << endl;
}

void showMenu()
{
    cout << "Welcome to the HSM hospital system" << endl;
    cout << "1: Login" << endl;
    cout << "2: Sign up" << endl;
    cout << "3: Book an Appointment" << endl;
    cout << "4: Update Personal Information" << endl;
    cout << "5: Set Doctor Availability" << endl;
    cout << "6: delete data" << endl;
    cout << "7: Exit" << endl;
    cout << "Enter your choice: ";
}

int main()
{
    int choice;
    string fileName;
    string email2;
    // declaration for delete data
    string UserEmail;
    string Filename;
    readPatients("patient.csv");
    readDoctors("doctor.csv");
    do
    {
        showMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "1: As a patient" << endl;
            cout << "2: As a doctor" << endl;
            int userType;
            cin >> userType;
            if (userType == 1)
            {
                fileName = "patient.csv";
                handle(fileName, "patient");
            }
            else if (userType == 2)
            {
                fileName = "doctor.csv";
                handle(fileName, "doctor");
            }
            else
            {
                cout << "Invalid choice. Please enter 1 or 2." << endl;
            }
            break;
        case 2:
            cout << "Signup as a patient or doctor?" << endl;
            cout << "1: Patient" << endl;
            cout << "2: Doctor" << endl;
            int signupType;
            cin >> signupType;
            if (signupType == 1)
            {
                signupPatient();
            }
            else if (signupType == 2)
            {
                signupDoctor();
            }
            else
            {
                cout << "Invalid choice. Please enter 1 or 2." << endl;
            }
            break;
        case 3:
            bookAppointment(doctors);
            break;
        case 4:
            cout << "Update personal information as a patient or doctor?" << endl;
            cout << "1: Patient" << endl;
            cout << "2: Doctor" << endl;

            int updateType;
            cin >> updateType;
            if (updateType == 1)
            {
                cout << "Enter your email" << endl;
                cin >> email2;
                updatePatientData("patient.csv", email2);
            }
            else if (updateType == 2)
            {
                cout << "Enter your email" << endl;
                cin >> email2;
                updateDoctorData("doctor.csv", email2);
            }
            else
            {
                cout << "Invalid choice. Please enter 1 or 2." << endl;
            }
            break;
        case 5:
            setDoctorAvailability(doctors);
            break;
        case 6:

            // Ask the user for filename
            cout << "Enter the filename (patient.csv or doctor.csv): ";
            cin >> Filename;

            // Ask the user for the email to delete
            cout << "Enter the email of the user to delete: ";
            cin >> UserEmail;

            deleteUser(Filename, UserEmail);
            break;
        case 7:
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != 6);
    return 0;
}