// *********************************************************
// Program: Student Attendance Tracker - Milestone 2
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC5L
// Tutorial Class: TT15L
// Trimester: 2530
// Member_1: 252UC242D2 | ADAM SYAFIQ BIN SALLEHUDDIN | ADAM.SYAFIQ.SALLEHUDDIN1@STUDENT.MMU.EDU.MY | 012-361 3065
// Member_2: 252UC242QY | MUHAMMAD HAFIY AL-HAFIIZH BIN JOAHARI | MUHAMMAD.HAFIY.ALHAFIIZH1@STUDENT.MMU.EDU.MY | 016-212 3859
// Member_3: 252UC242NE | AIDAN KHALIQ BIN SHAHNAZARUDDIN | AIDAN.KHALIQ.SHAHNZARUDDI1@student.mmu.edu.my | 017-615 5250
// *********************************************************
// Task Distribution
// Member_1: Database handling [Reading, outputting and writing to a file]
// Member_2: 
// Member_3: 
// *********************************************************

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Creating a school term (Adam)
string createSchoolTerm()
{
    string termName;
    cout << "Enter term name: ";
    getline(cin, termName);

    cout << "Database \"" << termName << "\" created and loaded.\n\n";
    return termName;
}

// Check if a the file exists (Adam)
bool fileExists(const string& filename)
{
    ifstream file(filename);
    return file.good();
}

// If the file exists read the file (Adam)
void readDatabase(const string& filename)
{
    ifstream inFile(filename);
    string line;

    cout << "-------------------------------------------\n";
    cout << "Current Attendance Sheet\n";
    cout << "-------------------------------------------\n";

    while (getline(inFile, line))
    {
        cout << line << endl;
    }

    cout << endl;
    inFile.close();
}

// Main
int main()
{
    cout << "===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 2\n";
    cout << "   Update Attendance Check\n";
    cout << "===========================================\n\n";

    string termName = createSchoolTerm();
    string databaseFile = termName + "_Database.csv";

    // Check if database already exists (Adam)
    if (fileExists(databaseFile))
    {
        cout << "Existing database found.\n\n";
        readDatabase(databaseFile);

        char choice;
        cout << "Would you like to update the attendance rows? (Y/N): ";
        cin >> choice;

        if (choice == 'Y' || choice == 'y')
        {
            // -----------------Note to Aidan and Hafiy, updating, deleting etc starts here-------------------------------
            cout << "\n[NOTE] Update attendance logic will be implemented here later.\n";
            cout << "Program ended (update feature pending).\n";
        }
        else
        {
            cout << "\nNo changes made. Program ended.\n";
        }
    }
    else
    {
        cout << "No existing database found.\n";
        cout << "Program ended.\n";
    }

    return 0;
}
