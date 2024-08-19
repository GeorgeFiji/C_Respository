#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <iomanip>
using namespace std;

class Person {
    // Class to represent a person in the simulation
public:
    int x;
    int y;
    bool infected;
    int infectedBy;
    int infectedDay;

    // Default constructor
    Person() {
        // Initialize default values for a person
        x = 0;
        y = 0;
        infected = false;
        infectedBy = -1;
        infectedDay = -1;
    }

    // Parameterized constructor
    Person(int xCoord, int yCoord) {
        // Initialize person with specified coordinates
        x = xCoord;
        y = yCoord;
        infected = false;
        infectedBy = -1;
        infectedDay = -1;
    }
};

class InfectionSimulator {
    // Class to manage the infection simulation
private:
    // Constants and arrays for simulation
    static const int MAX_PEOPLE = 100;
    static const int MAX_COORDINATE = 100;
    static const int MIN_COORDINATE = -100;
    const float MAX_DISTANCE = sqrt(2);
    static const int MOVEMENT_RANGE = 1;
    static const int INFECTION_CHANCE_PERCENT = 100 * 0.9;
    Person* people;
    int numPeople;
    int numInfectedDay1;
    int numDays;
    int* totalInfected;
    bool* infected;

public:
    // Constructor to set up the simulation
    InfectionSimulator(int peopleCount, int infectedDay1, int simulationDays) {
        // Initialize simulation parameters and allocate memory
        numPeople = peopleCount;
        numInfectedDay1 = infectedDay1;
        numDays = simulationDays;
        people = new Person[MAX_PEOPLE];
        totalInfected = new int[numDays + 1];
        infected = new bool[MAX_PEOPLE];
    }

    // Method to simulate random movement
    int randomMovement() {
        // Generate a random movement within a range
        return rand() % (2 * MOVEMENT_RANGE + 1) - MOVEMENT_RANGE;
    }

    // Method to calculate distance between two people
    double distance(const Person& p1, const Person& p2) {
        // Calculate Euclidean distance between two people
        int dx = p1.x - p2.x;
        int dy = p1.y - p2.y;
        return sqrt(dx * dx + dy * dy);
    }

    // Method to initialize people's initial positions
    void initializePeople() {
        // Set initial positions for people randomly
        for (int i = 0; i < numPeople; ++i) {
            int xCoord = rand() % (MAX_COORDINATE - MIN_COORDINATE + 1) + MIN_COORDINATE;
            int yCoord = rand() % (MAX_COORDINATE - MIN_COORDINATE + 1) + MIN_COORDINATE;
            this->people[i] = Person(xCoord, yCoord);
            this->infected[i] = false;
        }
    }

    // Method to infect initial people on Day 0
    void infectInitialPeople() {
        // Infect a specified number of people on Day 0
        for (int i = 0; i < numInfectedDay1; ++i) {
            int infectedIndex = rand() % numPeople;
            while (this->infected[infectedIndex]) {
                infectedIndex = rand() % numPeople;
            }
            // Mark person as infected and record details
            this->infected[infectedIndex] = true;
            this->people[infectedIndex].infected = true;
            this->people[infectedIndex].infectedBy = -1; // Infected on Day 0
            this->people[infectedIndex].infectedDay = 0;
            this->totalInfected[0]++;
        }
    }

    // Method to simulate infection spread for a day
    void simulateDay(int day) {
        // Simulate movement and infection spread for a day
        int newInfections = 0;
        const int PREV_DAY = 1;
        for (int i = 0; i < numPeople; ++i) {
            if (!this->infected[i]) {
                int dx = this->randomMovement();
                int dy = this->randomMovement();

                this->people[i].x += dx;
                this->people[i].y += dy;

                for (int j = 0; j < numPeople; ++j) {
                    if (this->infected[j] && this->distance(this->people[i], this->people[j]) <= this->MAX_DISTANCE) {
                        if (rand() % 100 < this->INFECTION_CHANCE_PERCENT) {
                            // Infect person if conditions are met
                            this->infected[i] = true;
                            this->people[i].infected = true;
                            this->people[i].infectedBy = j;
                            this->people[i].infectedDay = day;
                            newInfections++;
                            break;
                        }
                    }
                }
            }
        }

        this->totalInfected[day] = this->totalInfected[day - PREV_DAY] + newInfections;
    }

   
void printMovementsAndInfections(int day) {
    int totalInfected = 0;  // To keep track of the total infected points
    
    cout << "\nDay " << day << ":" << endl;
    cout << "------\n" << endl;
    cout << "ID:" << "\t\tPosition:" << "\t\tHealth Status:" << endl;

    for (int i = 0; i < numPeople; ++i) {
        int dx = randomMovement();
        int dy = randomMovement();

        people[i].x += dx;
        people[i].y += dy;

        cout << "S" << setfill('0') << setw(5) << i  << ":" << "\t\t(" << people[i].x << ", " << people[i].y << ")";
        if (people[i].infected) {
            cout << "\t\tInfected";
            totalInfected++;  // Increment the total infected count
        } else {
            cout << "\t\tHealthy";
        }
        cout << endl;
    }
    
    // Display the total number of infected points
    cout << "\nTotal Infected Points: " << totalInfected << endl;
}

   
void printInfectedSummary() {
    cout << "\nInfected People Summary:" << endl;
    cout << "------------------------\n" << endl;
    
    int totalInfections = 0;  // To keep track of the total number of infections
    
    for (int i = 0; i < numPeople; ++i) {
        if (people[i].infected) {
            if (people[i].infectedDay == 0) {
                cout << "S" << setfill('0') << setw(5) << i << " was already infected." << endl;
            } else {
                cout << "S" << setfill('0') << setw(5) << i  << " was infected by S" << setfill('0') << setw(5) << people[i].infectedBy
                    << " on Day " << people[i].infectedDay << "."<< endl;
            }
            
            totalInfections++;  // Increment the total infection count
        }
    }
    
    cout << "\nTotal Infections: " << totalInfections << endl;
}
int runSimulation() {
    srand((time(0)));

    initializePeople();
    infectInitialPeople();

    totalInfected[0] = numInfectedDay1;
    const int PREV_VALUE = 1;
    
    for (int day = 1; day <= numDays; ++day) {
        simulateDay(day);
    }
    
    // Calculate the total infections at the end of the simulation
    int totalInfections = 0;
    for (int i = 0; i <= numDays; ++i) {
        totalInfections += totalInfected[i];
    }
    
    return totalInfections;  // Return the total number of infections
}
 void runSimulationAndOutput(int numDays) {
        initializePeople();
        infectInitialPeople();
  		runSimulation();
        ofstream outputFile("Results/simulation_output.txt");
        streambuf* coutBuffer = cout.rdbuf();
        cout.rdbuf(outputFile.rdbuf());

        for (int day = 1; day <= numDays; ++day) {
           
            simulateDay(day);
            printMovementsAndInfections(day);
            cout << endl;
        }
	printInfectedSummary() ;
        cout.rdbuf(coutBuffer);
        outputFile.close();

    }
 
 
    void handleMenuOptions(InfectionSimulator &simulator, int numDays) {
    int choice;
    do {
        system("cls");  // Clear the screen before showing the loop iteration
        cout << "\nSelect an option:\n";
        cout << "1. Print infection summary with every day's result\n";
        cout << "2. Print summary only\n";
        cout << "3. Print result in console\n";
        cout << "4. Exit the program\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        	while(cin.fail() || choice < 0 || choice > 4){
		if(cin.fail()){
		cin.clear();
		char not_an_int;
		cin >> not_an_int;
		
	}
	cout << "Incorrect input, please try again (1 - 4): ";
	cin >> choice;
}

        switch (choice) {
            case 1: {
    

        cout << "\nSuccessful: Simulation results written to simulation_output.txt in the Results folder.\n" << endl;
      system("pause");
                break;
            }
          case 2: {
    ifstream summaryFile("Results/simulation_output.txt");
    ofstream resultFile("Results/infection_summary.txt");
    
    if (summaryFile.is_open() && resultFile.is_open()) {
        string line;
        bool display = false;

        resultFile << "\nInfected People Summary:" << endl;
    
        while (getline(summaryFile, line)) {
            if (display) {
                resultFile << line << endl;
            }
            if (line.find("Infected People Summary:") != string::npos) {
                display = true;
            }
        }

        summaryFile.close();
        resultFile.close();
        
        cout << "\nSuccessful: Infection summary written to infection_summary.txt in the Results folder\n" << endl;
        
    } else {
        cout << "\nUnable to open files.\n" << endl;

    }
  
  
     system("pause");
    break;
}
            case 3: {
                int specificDay;
                ifstream inputFile("Results/simulation_output.txt");
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            cout << line << endl;
        }
        inputFile.close();
    } else {
        cout << "Error: Unable to open the output file." << endl;
    }
                system("pause");
                break;
            }
            
            case 4: {
                cout << "\nExiting the program.\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please select a valid option (1-4).\n";
                system("pause");
                break;
            }
        }
    } while (choice != 4);
}

};


int getSimulationDays() {
    int numDays;
    cout << "DIGITAL FIJI - PANDEMIC OUTBREAK TRACING APP (POTA)"<< endl;
    cout << "---------------------------------------------------"<< endl;
    cout << "This is a pandemic outbreak tracing app.";
	cout << "\nA person with the symptoms of the disease should stay in confinement.";
	cout << "\nIf he/she moves around then there is a danger of passing the disease to others."<< endl;
    cout << "\nEnter the number of days for simulation: ";
    cin >> numDays;

	while(cin.fail() || numDays <= 0){
		if(cin.fail()){
		cin.clear();
		char not_an_int;
		cin >> not_an_int;
	}
	cout << "Incorect input, choose a value greater than 0: ";
	cin >> numDays;
}

    return numDays;
}


// Main function
int main() {
    const int numPeople = 100;
    const int numInfectedDay1 = numPeople * 0.1;
    int numDays = getSimulationDays();
  
    
    InfectionSimulator simulator(numPeople, numInfectedDay1, numDays);
    simulator.runSimulationAndOutput(numDays);
    simulator.handleMenuOptions(simulator, numDays);

    return 0;
}


