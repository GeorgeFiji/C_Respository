#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;


// Function for the class list
void print_data(int size, string last_name[], string f_name_initial[], int employees_id[], int year_of_birth[], double gpa_[]) {
    for (int i = 0; i < size; i++) 
	{
      cout << "\n\t" << last_name[i] << " \t" << f_name_initial[i] << " \t"
    	<< employees_id[i] << "   \t" << year_of_birth[i] << "   \t" << gpa_[i] << endl;
    }
}

// Function to print the list including the last name and age
void print_class_list(const string last_name[], const string f_name_initial[], const int employees_id[],
const int year_of_birth[], const double gpa[], int size) {
    cout << "\n";
    cout << "Class List with Last Name Initial and Age:\n\n ";
    cout << "--------------------------------------------------------------------------------------------------" << endl;
    cout << "Last Name\tLast Name Initial\tFirst Name Initial\tID#\t\tAge\tGPA" << endl;
    cout << "--------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < size; i++) {
        char last_name_initial = last_name[i][0];  // First character of the last name
        int age = 2023 - year_of_birth[i];  // Calculates age based on the current year

        cout << last_name[i] << "\t\t" << last_name_initial << "\t\t\t\t" << f_name_initial[i] << "\t\t"
             << employees_id[i] << "\t" << age << "\t" << gpa[i] << endl;
    }
}
void Swap(int index, int minIndex, string initial[], int id[], int birth_year[], double gpa[], int age[],
          string lastname[], string degree[], string firstname[]) {
    string tempstr;
    double temp;

    // Swap initial array elements
    tempstr = initial[index];
    initial[index] = initial[minIndex];
    initial[minIndex] = tempstr;

    // Swap lastname array elements
    tempstr = lastname[index];
    lastname[index] = lastname[minIndex];
    lastname[minIndex] = tempstr;

    // Swap id array elements
    temp = id[index];
    id[index] = id[minIndex];
    id[minIndex] = temp;

    // Swap age array elements
    temp = age[index];
    age[index] = age[minIndex];
    age[minIndex] = temp;

    // Swap gpa array elements
    temp = gpa[index];
    gpa[index] = gpa[minIndex];
    gpa[minIndex] = temp;

    // Swap degree array elements
    tempstr = degree[index];
    degree[index] = degree[minIndex];
    degree[minIndex] = tempstr;

    // Swap firstname array elements
    tempstr = firstname[index];
    firstname[index] = firstname[minIndex];
    firstname[minIndex] = tempstr;
}


void SortAscending(int nElements, string initial[], int id[], int birth_year[], double gpa[], int age[],
                   string lastname[], string degree[], string firstname[]) {
    double min;
    int minPos;
    for (int i = 0; i < nElements - 1; i++) {
        min = gpa[i];
        minPos = i;
        for (int j = i + 1; j < nElements; j++)
            if (gpa[j] < min) {
                min = gpa[j];
                minPos = j;
            }
        Swap(i, minPos, initial, id, birth_year, gpa, age, lastname, degree, firstname);
    }
}
string calculateDegreeClassification(double gpa) {
    if (gpa >= 4) {
        return "First Class Honours";
    } else if (gpa >= 3.3) {
        return "Upper Second Class Honours";
    } else if (gpa >= 2.7) {
        return "Lower Second Class Honours";
    } else if (gpa >= 2.0) {
        return "Third Class Honours";
    } else {
        return "0rdinary degree (no honours)";
    }
}

// Function that asks the user to search
void print_students_by_last_name_initial(int size, const string last_name[], const string f_name_initial[], const int employees_id[],
 const int year_of_birth[], const double gpa_[]) {
    char s_initial;
    cout << "\nEnter the last name initial to search for: ";
    cin >> s_initial;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    bool found = false;

    for (int i = 0; i < size; i++) {
        if (last_name[i][0] == s_initial) {
            found = true;
            cout << "\nStudent Found:" << endl;
            cout << "Last Name: " << last_name[i] << endl;
            cout << "First Name Initial: " << f_name_initial[i] << endl;
            cout << "ID#: " << employees_id[i] << endl;
            cout << "Year of Birth: " << year_of_birth[i] << endl;
            cout << "GPA: " << gpa_[i] << endl;
        }
    }

    if (!found) {
        cout << "\n\tName does not exist in the records.\n" << endl;
    }
}

// Function to calculate and display the GPA degree classifications
void calculate_and_display_degree_classification(const string last_name[], const string f_name_initial[], const int employees_id[], const double gpa_[], int size) {
    cout << "\n";
    cout << "Degree Classification based on GPA:\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n" << endl;
    cout << "Last Name\tLast Name Initial\tFirst Name Initial\tID#\t\tGPA\t\tDegree Classification" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------\n" << endl;

    for (int i = 0; i < size; i++) {
        char last_name_initial = last_name[i][0];  // First character of the last name
        string degree_classification = calculateDegreeClassification(gpa_[i]);

        cout << last_name[i] << "\t\t\t" << last_name_initial << "\t\t\t" << f_name_initial[i] << "\t\t"
        << employees_id[i] << "\t" << gpa_[i] << "\t\t" << degree_classification << endl;
    }
}

int main() {
    const int MAX_ARRSIZE_STUDENTS = 300;

    string last_name[MAX_ARRSIZE_STUDENTS];
    string f_name_initial[MAX_ARRSIZE_STUDENTS];
    int employees_id[MAX_ARRSIZE_STUDENTS];
    int year_of_birth[MAX_ARRSIZE_STUDENTS];
    int age[MAX_ARRSIZE_STUDENTS];
    double gpa_[MAX_ARRSIZE_STUDENTS];
    string degree_classification [MAX_ARRSIZE_STUDENTS];
    char enteredValue;

    ifstream infile;
    infile.open("StudentRec.txt");
    if (!infile) {
        cout << "\n\tFile not found";
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
        cout << "========================================================================================================================\n" << endl;
        cout << "\tStudent Details\n";
        cout << "========================================================================================================================\n\t" << endl;
        cout << "\t1. Display Class List\n";
        cout << "\t2. Display Class List with Students last name initial and age\n";
        cout << "\t3. Display Class List Sorted by GPA \n";
        cout << "\t4. Display Class List Which Matches a given last name initial\n";
        cout << "\t5. Calculate and Display the Current GPA Degree Classifications\n";
        cout << "\t6. Produce Enrollment File \n";
        cout << "\t7. Exit program or Q to Exit\n";
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        bool input = false;
        do {
            cout << "\n\tYour Option: ";
            cin >> enteredValue;
            cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
            enteredValue = toupper(enteredValue);

            // Validating the input where the options to execute the menu accept numbers one to seven and Q to exit the program
            if (enteredValue == '1' || enteredValue == '2' || enteredValue == '3' || enteredValue == '4' || enteredValue == '5' ||
                enteredValue == '6' || enteredValue == '7' || enteredValue == 'Q') {
                input = true;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cout << "\n\tInvalid input\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (!input);

        // The following are codes that will display the menus once the numbers from one to seven or letter Q are inputted
        if (enteredValue == '1') 
		{
            // Calling the function for the class list
            print_data(size, last_name, f_name_initial, employees_id, year_of_birth, gpa_);
        } 
		else if (enteredValue == '2') 
		{
            // Calling function to print the list including the last name and age
            print_class_list(last_name, f_name_initial, employees_id, year_of_birth, gpa_, size);
        } 
        else if (enteredValue == '3')
		 {
	    // Calling the function to sort the class list by GPA in ascending order
	    SortAscending(size, f_name_initial, employees_id, year_of_birth, gpa_, age, last_name, degree_classification, f_name_initial);
	
	    // Printing the sorted class list
	    print_data(size, last_name, f_name_initial, employees_id, year_of_birth, gpa_);
		}
		else if (enteredValue == '4')
		{
            print_students_by_last_name_initial(size, last_name, f_name_initial, employees_id, year_of_birth, gpa_);
        } 
		else if (enteredValue == '5') 
		{
        calculate_and_display_degree_classification(last_name, f_name_initial, employees_id, gpa_, size);

        } 
       else if (enteredValue == '6') {
    ofstream outfile("Enrollments.txt");
    if (!outfile) {
        cout << "\n\tError creating the file.\n";
        return 1;
    }
    

    outfile << "------------------------------------------------------------------------------------------------------------\nLast Name\tLast Name Initial\tFirst Name Initial\tID#\t\tAge\tGPA\t\tDegree Classification\n------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < size; i++) {
        char last_name_initial = last_name[i][0]; // Get the first character of the last name
        string degree_classification = calculateDegreeClassification(gpa_[i]);
        int age = 2023 - year_of_birth[i]; // Calculate age based on the current year

        outfile << last_name[i] << "\t\t\t" << last_name_initial << "\t\t\t" << f_name_initial[i] << "\t\t\t"
                << employees_id[i] << "\t" << age << "\t" << gpa_[i] << "\t\t" << degree_classification << endl;
    }

    outfile.close();
    cout << "\n\tEnrollments file  created successfully.\n";
	}


	else if (enteredValue == '7'||'Q') {
	    cout << "========================================================================================================================" << endl;
	    cout << "\nThank you for using this program" << endl;
	    cout << "========================================================================================================================" << endl;
	    return 0;
	}

    } while (true);

    cout << "========================================================================================================================\n" << endl;
    cout << "\nThank you for using this program" << endl;
    cout << "========================================================================================================================\n" << endl;
    return 0;
}

