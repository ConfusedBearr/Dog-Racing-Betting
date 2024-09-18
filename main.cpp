//Coded by Rodrigo Peixoto
//Coded on 03/27/2023
// Purpose: Showing my ability to use structs, create and use menus, create and use array of structs, and generate
// and use random numbers
// Also this program is a gambling simulator on dog race betting
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Struct for dog information
struct Dog{
    string name;
    double payout;
    int odds;
};

// This is the array wil all the dogs their payouts and odds of winning
Dog dogs[9] = {
        {"Bela", 2, 40},
        {"Max", 5, 10},
        {"Luna", 10, 8},
        {"Charlie", 15, 6},
        {"Lucy", 50, 1},
        {"Cooper", 20, 4},
        {"Elvis", 10, 8},
        {"Cash", 5, 10},
        {"Vanilla", 3, 13},
};

// Prints out the current balance of the user
void printBalance(double balance){
    cout << "Your current balance is: $" << balance << endl;
}
//This will ask the user to enter a bet that is between their minvalue which is 1 and maxValue which is their balance
double getInput(string message, double minValue, double maxValue){
    double input;
    do {
        cout << message;
        cin >> input;
        if(cin.fail() || input < minValue || input > maxValue){
            cout << "Invalid Input. Please enter an number between " << minValue << " and " << maxValue << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            break;
        }
    } while (true);
    return input;
}

int main() {
    //Setting a random number generator
    srand(time(nullptr));

    //Setting initial balance
    double balance = 100;

    // Keeping the track race results
    int raceResults[9]= {0};

    // Loop for the menu
    while (true){
        cout << "\nWelcome to the Dog Racing Track!" << endl;
        cout << "[G]amble" << endl;
        cout << "[B]anking" << endl;
        cout << "[R]esults of previous races" << endl;
        cout << "[L]eave the dog track" << endl;
        cout << "Please choose one of the options above: ";

        char choice;
        cin >> choice;

        switch (choice) {
            case 'G':
            case 'g': {
                double wager = getInput("Enter wager amount: $", 1, balance);

                cout << "\nDogs available to bet on:" << endl;
                for (int i = 0; i < 9; i++) {
                    cout << i + 1 << ". " << dogs[i].name << " (" << dogs[i].payout << " to 1, " << dogs[i].odds
                         << "% chance of winning)" << endl;
                }
                int dogNumber = getInput("Choose a dog (1-9): ", 1, 9);

                int winningDog = -1;
                int randomNumber = rand() % 100 + 1;
                int totalOdds = 0;
                for (int i = 0; i < 9; i++) {
                    totalOdds += dogs[i].odds;
                    if (randomNumber <= totalOdds) {
                        winningDog = i;
                        break;
                    }
                }
                cout << "The winning dog is " << dogs[winningDog].name << endl;
                cout << "You bet on " << dogs[dogNumber - 1].name << endl;

                if (dogNumber - 1 == winningDog) {
                    double payout = wager * dogs[dogNumber - 1].payout;
                    cout << "Congratulations! You won $" << payout << "!" << endl;
                    balance += payout;
                } else {
                    cout << "Sorry, you lost your wager." << endl;
                    balance -= wager;
                }
                // Added the winning dog to the race results array
                raceResults[winningDog]++;
                //Prints the current balance after the wager
                printBalance(balance);
                break;
            }
            case 'B':
            case 'b': {
                cout << "Do you want to [D]eposit or [W]ithdraw funds?" << endl;
                char depOrWith;
                cin >> depOrWith;

                switch (depOrWith) {
                    case 'D':
                    case 'd': {
                        double deposit = getInput("Enter deposit amount: $", 1, 10000);
                        balance += deposit;
                        cout << "Deposit was successful\n";
                        printBalance(balance);
                        cout << endl;
                        break;
                    }
                    case 'W':
                    case 'w': {
                        double withdrawal = getInput("Enter withdrawal amount: $", 1, balance);
                        balance -= withdrawal;
                        cout << "Withdrawal successful";
                        printBalance(balance);
                        cout << endl;
                        break;
                    }
                    default:
                        cout << "Invalid choice." << endl;
                        break;
                }
            }
                break;

            case 'R':
            case 'r':{
                // Shows the result of previous races
                cout << "Results of previous races:" << endl;
                for (int i = 0; i < 9; i++){
                    cout << dogs[i].name << ": " << raceResults[i] << " wins" << endl;
                }
                // show the current balance
                printBalance(balance);

                break;
            }
            case 'L':
            case 'l':{
                //Ends the program
                cout << "Thank you for visiting the Dog Racing Track!" << endl;
                return 0;
            }
            default: {
            cout << "Invalid choice." << endl;
            break;
            }
        }
    }
}