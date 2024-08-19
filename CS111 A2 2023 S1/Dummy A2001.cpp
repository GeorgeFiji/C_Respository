#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

void print_data(int size, string last_name[], string f_name_initial[], int employees_id[],
                int year_of_birth[], double gpa_[]) {
    for (int i = 0; i < size; i++) {
        cout << "\t" << last_name[i] << " " << f_name_initial[i] << " \t"
             << employees_id[i] << "   \t" << year_of_birth[i] << "   \t" << gpa_[i] << endl;
    }
}

int main() {
    const int MAX_ARRSIZE_STUDENTS = 300;

    cout << "\t\t\t\t Student details" << endl;

    string last_name[MAX_ARRSIZE_STUDENTS];
    string f_name_initial[MAX_ARRSIZE_STUDENTS];
    int employees_id[MAX_ARRSIZE_STUDENTS];
    int year_of_birth[MAX_ARRSIZE_STUDENTS];
    double gpa_[MAX_ARRSIZE_STUDENTS];
    char enteredValue;

    ifstream infile;
    infile.open("StudentRec.txt");
    if (!infile) {
        cout << "\n\tfile not found";
        return 1;
    }

    string line;
    int size = 0;
    while (getline(infile, line) && size < MAX_ARRSIZE_STUDENTS) {
        istringstream iss(line);
        if (iss >> last_name[size] >> f_name_initial[size] >> employees_id[size] >> year_of_birth[size] >> gpa_[size]) {
            size++;
        }
    }

    infile.close();

    do {
        cout << "\n\t                          \n";
        cout << "\tPayroll Generator Application\n";
        cout << "\t \n";
        cout << "\t1. Display All Employee Data\n";
        cout << "\t2. Print Data with Employee last name\n";
        cout << "\t3. Calculate wages\n";
        cout << "\t4. Display payroll results\n";
        cout << "\t5. Write results to file\n";
        cout << "\t6. Exit program or Q to Exit\n";

        bool input = false;
        do {
            cout << "\n\tYour Option: ";
            cin >> enteredValue;

            enteredValue = toupper(enteredValue);

            if (enteredValue == '1' || enteredValue == '2' || enteredValue == '3' || enteredValue == '4' ||
                enteredValue == '5' || enteredValue == '6' || enteredValue == 'Q') {
                input = true;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cout << "\n\t                               \n";
                cout << "\tIncorrect option has been chosen\n";
                cout << "\t                                \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (!input);

        if (enteredValue == '1') {
            print_data(size, last_name, f_name_initial, employees_id, year_of_birth, gpa_);
        } else if (enteredValue == 'Q') {
            break;
        }
        // Add code for other menu options (2-6) here

    } while (true);

    return 0;
}

