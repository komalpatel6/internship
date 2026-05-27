#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Student
{
private:
    int rollNo;
    char name[50];
    float marks;

public:
    void addStudent()
    {
        cout << "\nEnter Roll Number: ";
        cin >> rollNo;

        cin.ignore();

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Marks: ";
        cin >> marks;
    }

    void displayStudent()
    {
        cout << left << setw(10) << rollNo
             << setw(25) << name
             << setw(10) << marks << endl;
    }

    int getRollNo()
    {
        return rollNo;
    }
};

// Function to add student
void addRecord()
{
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    s.addStudent();

    file.write((char *)&s, sizeof(s));

    file.close();

    cout << "\nStudent record added successfully!\n";
}

// Function to display all students
void displayRecords()
{
    Student s;
    ifstream file("students.dat", ios::binary);

    cout << "\n-------------------------------------------\n";
    cout << left << setw(10) << "Roll No"
         << setw(25) << "Name"
         << setw(10) << "Marks" << endl;
    cout << "-------------------------------------------\n";

    while (file.read((char *)&s, sizeof(s)))
    {
        s.displayStudent();
    }

    file.close();
}

// Function to search student
void searchRecord()
{
    Student s;
    int roll;
    bool found = false;

    ifstream file("students.dat", ios::binary);

    cout << "\nEnter Roll Number to Search: ";
    cin >> roll;

    while (file.read((char *)&s, sizeof(s)))
    {
        if (s.getRollNo() == roll)
        {
            cout << "\nStudent Found:\n";
            s.displayStudent();
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nRecord not found!\n";
    }

    file.close();
}

// Function to delete record
void deleteRecord()
{
    Student s;
    int roll;
    bool found = false;

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    while (file.read((char *)&s, sizeof(s)))
    {
        if (s.getRollNo() == roll)
        {
            found = true;
        }
        else
        {
            temp.write((char *)&s, sizeof(s));
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "\nRecord deleted successfully!\n";
    else
        cout << "\nRecord not found!\n";
}

// Main Function
int main()
{
    int choice;

    do
    {
        cout << "\n========== Student Management System ==========\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addRecord();
            break;

        case 2:
            displayRecords();
            break;

        case 3:
            searchRecord();
            break;

        case 4:
            deleteRecord();
            break;

        case 5:
            cout << "\nExiting Program...\n";
            break;

        default:
            cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 5);

    return 0;
}