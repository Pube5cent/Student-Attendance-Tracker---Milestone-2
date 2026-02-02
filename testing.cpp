#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

// globals
const int MAX_COLUMNS = 10;
const int MAX_ROWS = 100;

string sheetName;
string columnNames[MAX_COLUMNS];
string textCells[MAX_ROWS][MAX_COLUMNS];
int columnTypes[MAX_COLUMNS];
int intCells[MAX_ROWS][MAX_COLUMNS];
int numColumns = 0;
int numRows = 0;

// Attendance Tracker
void createSheet(string name);
void getColumnInfo(int colIndex);
void insertRow();
void ViewCSV();
bool isNumber(const string& str);
int convertToInt(const string& str);

void runAttendanceTracker(const string& databaseFile);

// TC5L database
string createSchoolTerm();
bool fileExists(const string& filename);
void readDatabase(const string& filename);
void saveToCSV(const string& filename);

// main
int main()
{
    cout << "===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - COMBINED\n";
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
            runAttendanceTracker(databaseFile);
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
    cout << "Database \"" << termName << "\" created and loaded.\n\n";
    return termName;
}

bool fileExists(const string& filename)
{
    ifstream file(filename);
    return file.good();
}

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

// void to run the original file
void runAttendanceTracker(const string& databaseFile)
{
    string input;
    int numCols;
    char continueInsert;

    cout << "Enter Attendance sheet name: ";
    getline(cin, input);
    createSheet(input);

    cout << "Enter number of columns (max 10): ";
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

    continueInsert = 'y';
    while (continueInsert == 'y' || continueInsert == 'Y')
    {
        insertRow();
        cout << "Insert another row? (y/n): ";
        cin >> continueInsert;
        cin.ignore();
    }

    ViewCSV();
    saveToCSV(databaseFile);
}

// attendance tracker copy paste
void createSheet(string name)
{
    sheetName = name;
    numColumns = 0;
    numRows = 0;
}

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

void ViewCSV()
{
    for (int i = 0; i < numColumns; i++)
    {
        cout << columnNames[i];
        if (i < numColumns - 1) cout << ", ";
    }
    cout << endl;

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            if (columnTypes[j] == 0)
                cout << intCells[i][j];
            else
                cout << textCells[i][j];

            if (j < numColumns - 1) cout << ", ";
        }
        cout << endl;
    }
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
