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
// Member_1: Database handling [Reading, displaying and writing to a file]
// Member_2: 
// Member_3: 
// *********************************************************

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include <limits>

using namespace std;

// milestone 1 constants
const int MAX_COLUMNS = 10;
const int MAX_ROWS = 100;

// Combined variables
string sheetName;
string columnNames[MAX_COLUMNS];
string textCells[MAX_ROWS][MAX_COLUMNS];
int columnTypes[MAX_COLUMNS];
int intCells[MAX_ROWS][MAX_COLUMNS];
int numColumns = 0;
int numRows = 0;

// Combined functions
void createSheet(string name);
void getColumnInfo(int colIndex);
void insertRow();
void ViewCSV();
bool isNumber(const string& str);
int convertToInt(const string& str);

void runAttendanceTracker(const string& databaseFile);

// Database
string createSchoolTerm();
bool fileExists(const string& filename);
void readDatabase(const string& filename);
void saveToCSV(const string& filename);


//main
// Adam Syafiq
int main()
{
    cout << "===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 2\n";
    cout << "===========================================\n\n";

    string termName = createSchoolTerm();
    string databaseFile = termName + "_Database.csv";

    if (fileExists(databaseFile))
    {
        cout << "Existing database found.\n\n";
        readDatabase(databaseFile);

        char choice;
        cout << "Would you like to update the attendance rows? (Y/N): ";
        cin >> choice;
        cin.ignore();

        if (choice == 'Y' || choice == 'y')
            {
            // -----------------Note to Aidan and Hafiy, updating, deleting etc starts here---------------------------------------
            cout << "\n[NOTE] Update attendance logic will be implemented here later.\n";
            cout << "Program ended (update feature pending).\n";
            }
        else
            cout << "\nNo changes made. Program ended.\n";
    }
    else
    {
        cout << "No existing database found.\n";
        cout << "Creating new attendance database...\n\n";
        runAttendanceTracker(databaseFile);
    }

    return 0;
}

// functions
string createSchoolTerm()
{
    string termName;
    cout << "Enter term name: ";
    getline(cin, termName);
    // display
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
        cout << line << endl;

    cout << endl;
    inFile.close();
}

// void to run the original milestione1 file
void runAttendanceTracker(const string& databaseFile)
{
    //hafiy
    string input;
    int numCols;
    char continueInsert;

    cout << "Enter attendance sheet name: ";
    getline(cin, input);
    createSheet(input);

    cout << "Attendance sheet \"" << input << "\" created successfully.\n\n";

    cout << "Define number of columns (max 10): ";
    while (!(cin >> numCols) || numCols < 1 || numCols > MAX_COLUMNS)
    {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid number. Try again: ";
    }

    cin.ignore();
    numColumns = numCols;

    for (int i = 0; i < numCols; i++)
        getColumnInfo(i);

    cout << "\nSheet structure created successfully.\n\n";

    continueInsert = 'y';

    while (continueInsert == 'y' || continueInsert == 'Y')
    {
        cout << "-------------------------------------------\n";
        cout << "Insert New Attendance Row\n";
        cout << "-------------------------------------------\n";

        insertRow();

        cout << "\nInsert another row? (y/n): ";
        cin >> continueInsert;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
    }

    /* doesnt get called for M2 (milestone 2 btw)
    cout << "-------------------------------------------\n";
    cout << "View Attendance Sheet (CSV Mode)\n";
    cout << "-------------------------------------------\n";

    ViewCSV();
    */
    saveToCSV(databaseFile);
}

// attendance tracker copy paste
// hafiy
void insertRow()
{
    if (numRows >= MAX_ROWS)
    {
        cout << "Error: Maximum number of rows reached.\n";
        return;
    }

    string input;

    for (int i = 0; i < numColumns; i++)
    {
        bool isStatus =
            (columnNames[i] == "Status" || columnNames[i] == "status");

        if (isStatus)
            cout << "Enter " << columnNames[i]
                 << " (Present: 1, Absent: 0): ";
        else
            cout << "Enter " << columnNames[i] << ": ";

        getline(cin, input);

        if (columnTypes[i] == 0)
        {
            if (isNumber(input))
                intCells[numRows][i] = convertToInt(input);
            else
            {
                cout << "Invalid number. Try again.\n";
                i--;
                continue;
            }
        }
        else
        {
            textCells[numRows][i] = input;
        }
    }

    numRows++;
    cout << "Row inserted successfully.\n";
}

// Adam Syafiq [doesnt get called anymore for M2 (milestone 2 btw)]
/*
void ViewCSV()
{
    //For printing the column headers
    for (int i = 0; i < numColumns; i++)
    {
        cout << columnNames[i];
        if (i < numColumns - 1)
            cout << ", ";
    }
    cout << endl;

    //For printing rows
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            if (columnTypes[j] == 0)
                cout << intCells[i][j];
            else
                cout << textCells[i][j];

            if (j < numColumns - 1)
                cout << ", ";
        }
        cout << endl;
    }
}
*/
void createSheet(string name)
{
    sheetName = name;
    numColumns = 0;
    numRows = 0;
}

void saveToCSV(const string& filename)
{
    ofstream file(filename);

    for (int i = 0; i < numColumns; i++)
    {
        file << columnNames[i];
        if (i < numColumns - 1) file << ",";
    }
    file << "\n";

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            if (columnTypes[j] == 0)
                file << intCells[i][j];
            else
                file << textCells[i][j];

            if (j < numColumns - 1) file << ",";
        }
        file << "\n";
    }

    file.close();
    cout << "\nAttendance saved to database successfully.\n";
}

bool isNumber(const string& str)
{
    if (str.empty()) return false;
    for (char c : str)
        if (!isdigit(c) && c != '-') return false;
    return true;
}

int convertToInt(const string& str)
{
    return stoi(str);
}

void getColumnInfo(int colIndex)
{
    string input;
    cout << "Enter column " << colIndex + 1 << " name (add INT if needed): ";
    getline(cin, input);

    columnNames[colIndex] = input;
    columnTypes[colIndex] = (input.find("INT") != string::npos ||
                             input.find("int") != string::npos) ? 0 : 1;
}
