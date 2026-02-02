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
#include <stdexcept>

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

// Attendance Tracker core operations
void createSheet(string name);
void getColumnInfo(int colIndex);
void insertRow();
void updateRow();
void deleteRow();
void showRowCount();
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
        
        // Validate user choice
        while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
        {
            cout << "Invalid input. Please enter Y or N: ";
            cin >> choice;
            cin.ignore();
        }

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

// Create a school term (database name) and return it
string createSchoolTerm()
{
    string termName;
    cout << "Enter term name: ";
    getline(cin, termName);
    
    // Validate non-empty term name
    if (termName.empty())
    {
        cout << "Warning: Empty term name. Using default name.\n";
        termName = "DefaultTerm";
    }
    
    cout << "Database \"" << termName << "\" created and loaded.\n\n";
    return termName;
}

// Check if a file exists in the filesystem
bool fileExists(const string& filename)
{
    ifstream file(filename);
    bool exists = file.good();
    file.close();
    return exists;
}

// Read an existing CSV database file and display it to the screen.
void readDatabase(const string& filename)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cout << "Error: Could not open database file \"" << filename << "\" for reading.\n\n";
        return;
    }

    string line;

    cout << "-------------------------------------------\n";
    cout << "Current Attendance Sheet\n";
    cout << "-------------------------------------------\n";

    while (getline(inFile, line))
        cout << line << endl;

    cout << endl;
    inFile.close();
}

// Main loop to define the sheet, insert rows, and allow updates/deletes
void runAttendanceTracker(const string& databaseFile)
{
    string input;
    int numCols;
    char continueInsert;

    cout << "Enter Attendance sheet name: ";
    getline(cin, input);
    
    // Validate non-empty sheet name
    if (input.empty())
    {
        cout << "Warning: Empty sheet name. Using default name.\n";
        input = "AttendanceSheet";
    }
    
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

    // Initial data entry loop
    continueInsert = 'y';
    while (continueInsert == 'y' || continueInsert == 'Y')
    {
        insertRow();
        cout << "Insert another row? (y/n): ";
        cin >> continueInsert;
        cin.ignore();
    }

    // Menu loop for viewing, updating, deleting, and saving
    bool done = false;
    while (!done)
    {
        int choice;
        cout << "\n======= Attendance Menu =======\n";
        cout << "1. View attendance sheet\n";
        cout << "2. Insert new row\n";
        cout << "3. Update existing row\n";
        cout << "4. Delete a row\n";
        cout << "5. Show number of rows\n";
        cout << "6. Save and exit\n";
        cout << "7. Exit without saving\n";
        cout << "Enter your choice (1-7): ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 7.\n";
            continue;
        }

        cin.ignore();

        switch (choice)
        {
        case 1:
            ViewCSV();
            break;
        case 2:
            insertRow();
            break;
        case 3:
            updateRow();
            break;
        case 4:
            deleteRow();
            break;
        case 5:
            showRowCount();
            break;
        case 6:
            ViewCSV();
            saveToCSV(databaseFile);
            done = true;
            break;
        case 7:
            cout << "Exiting without saving changes.\n";
            done = true;
            break;
        default:
            cout << "Invalid choice. Please choose a number between 1 and 7.\n";
            break;
        }
    }
}

// Create a new sheet (clears existing rows/columns)
void createSheet(string name)
{
    sheetName = name;
    numColumns = 0;
    numRows = 0;
}

// Insert a new row of data at the end of the sheet
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

// Update an existing row by index
void updateRow()
{
    if (numRows == 0)
    {
        cout << "No rows to update.\n";
        return;
    }

    int rowIndex;
    cout << "Enter the row number to update (1 to " << numRows << "): ";
    if (!(cin >> rowIndex))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Update cancelled.\n";
        return;
    }
    cin.ignore();

    if (rowIndex < 1 || rowIndex > numRows)
    {
        cout << "Row number out of range.\n";
        return;
    }

    rowIndex--; // convert to 0-based index

    string input;
    for (int i = 0; i < numColumns; i++)
    {
        cout << "Enter new value for " << columnNames[i] << ": ";
        getline(cin, input);

        if (columnTypes[i] == 0)
        {
            if (isNumber(input))
                intCells[rowIndex][i] = convertToInt(input);
            else
            {
                cout << "Invalid number. Keeping previous value for this column.\n";
            }
        }
        else
        {
            textCells[rowIndex][i] = input;
        }
    }

    cout << "Row updated successfully.\n";
}

// Delete a row by index and shift remaining rows up
void deleteRow()
{
    if (numRows == 0)
    {
        cout << "No rows to delete.\n";
        return;
    }

    int rowIndex;
    cout << "Enter the row number to delete (1 to " << numRows << "): ";
    if (!(cin >> rowIndex))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Delete cancelled.\n";
        return;
    }
    cin.ignore();

    if (rowIndex < 1 || rowIndex > numRows)
    {
        cout << "Row number out of range.\n";
        return;
    }

    rowIndex--; // convert to 0-based index

    for (int i = rowIndex; i < numRows - 1; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            intCells[i][j] = intCells[i + 1][j];
            textCells[i][j] = textCells[i + 1][j];
        }
    }

    numRows--;
    cout << "Row deleted successfully.\n";
}

// Show the current number of rows in the sheet
void showRowCount()
{
    cout << "Current number of rows in the attendance sheet: " << numRows << "\n";
}

// Display the current attendance sheet in CSV format to the screen
void ViewCSV()
{
    if (numColumns == 0)
    {
        cout << "No columns defined.\n";
        return;
    }

    // Print column headers
    for (int i = 0; i < numColumns; i++)
    {
        cout << columnNames[i];
        if (i < numColumns - 1) cout << ", ";
    }
    cout << endl;

    // Print all data rows
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

// Save the current attendance sheet to a CSV file
void saveToCSV(const string& filename)
{
    ofstream file(filename);

    if (!file)
    {
        cout << "Error: Could not open file \"" << filename << "\" for writing.\n";
        cout << "Data was not saved.\n";
        return;
    }

    // Write column headers
    for (int i = 0; i < numColumns; i++)
    {
        file << columnNames[i];
        if (i < numColumns - 1) file << ",";
    }
    file << "\n";

    // Write all data rows
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
    
    if (file.fail())
    {
        cout << "Error: Failed to write data to file.\n";
    }
    else
    {
        cout << "\nAttendance saved to database successfully.\n";
    }
}

// Validate if a string represents a valid integer number
bool isNumber(const string& str)
{
    if (str.empty()) return false;
    
    // Allow negative sign only at the start
    int start = 0;
    if (str[0] == '-')
    {
        if (str.length() == 1) return false; // Just a minus sign is invalid
        start = 1;
    }
    
    // Check all remaining characters are digits
    for (int i = start; i < str.length(); i++)
    {
        if (!isdigit(str[i])) return false;
    }
    
    return true;
}

// Convert string to integer with error handling
int convertToInt(const string& str)
{
    try
    {
        return stoi(str);
    }
    catch (const invalid_argument&)
    {
        cout << "Warning: Invalid number format. Using 0 as default.\n";
        return 0;
    }
    catch (const out_of_range&)
    {
        cout << "Warning: Number out of range. Using 0 as default.\n";
        return 0;
    }
}

// Get column name and determine its data type (INT or text)
void getColumnInfo(int colIndex)
{
    string input;
    cout << "Enter column " << colIndex + 1 << " name (add INT if needed): ";
    getline(cin, input);

    // Validate non-empty column name
    if (input.empty())
    {
        cout << "Warning: Empty column name. Using default name.\n";
        input = "Column" + to_string(colIndex + 1);
    }

    columnNames[colIndex] = input;
    // Determine type: 0 = integer, 1 = text
    columnTypes[colIndex] = (input.find("INT") != string::npos ||
                             input.find("int") != string::npos) ? 0 : 1;
}