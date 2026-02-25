#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
    Banking Console System
    Day 1: Base Architecture Setup

    Goal:
    - Define client data structure
    - Define main menu enum
    - Implement application loop
*/

// Enum representing main menu options
// Using enum class prevents accidental implicit conversions
enum class MainMenuOption : short {
    ShowClients = 1,
    AddClient,
    DeleteClient,
    UpdateClient,
    FindClient,
    Transactions,
    Exit
};

// Structure representing a bank client
// This groups related data together
struct Client {
    string accountNumber;
    string pinCode;
    string name;
    string phone;
    double balance = 0.0;
};

// Prints the main menu
void PrintMainMenu()
{
    cout << "\n=====================================\n";
    cout << "        Banking System - Main Menu\n";
    cout << "=====================================\n";
    cout << "[1] Show Clients\n";
    cout << "[2] Add Client\n";
    cout << "[3] Delete Client\n";
    cout << "[4] Update Client\n";
    cout << "[5] Find Client\n";
    cout << "[6] Transactions\n";
    cout << "[7] Exit\n";
    cout << "=====================================\n";
}

// Runs the main application loop
void RunApplication()
{
    short userChoice = 0;

    do
    {
        PrintMainMenu();
        cout << "Choose an option (1-7): ";
        cin >> userChoice;

    } while (userChoice != static_cast<short>(MainMenuOption::Exit));

    cout << "Exiting program. Goodbye.\n";
}

// Entry point of program
int main()
{
    RunApplication();
    return 0;
}