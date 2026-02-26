#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

/*
    Banking Console System
    Day 1: Base Architecture Setup

    Goal:
    - Define client data structure
    - Define main menu enum
    - Implement application loop
*/

const string CLIENTS_FILE = "../data/clients.txt";

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

// Splits a string by delimiter and returns vector of parts
vector<string> SplitString(const string& line, const string& delimiter)
{
    vector<string> parts;
    size_t start = 0;
    size_t end;

    while ((end = line.find(delimiter, start)) != string::npos)
    {
        parts.push_back(line.substr(start, end - start));
        start = end + delimiter.length();
    }

    parts.push_back(line.substr(start));
    return parts;
}

// Converts a single file line into a Client struct
Client ConvertLineToClient(const string& line)
{
    Client client;
    vector<string> data = SplitString(line, "#//#");

    if (data.size() == 5)
    {
        client.accountNumber = data[0];
        client.pinCode = data[1];
        client.name = data[2];
        client.phone = data[3];
        client.balance = stod(data[4]); // string → double
    }

    return client;
}

// Loads all clients from file into a vector
vector<Client> LoadClientsFromFile()
{
    vector<Client> clients;
    ifstream file(CLIENTS_FILE);

    if (!file.is_open())
    {
        cout << "Error: Could not open clients file.\n";
        return clients;
    }

    string line;

    while (getline(file, line))
    {
        if (!line.empty())
        {
            clients.push_back(ConvertLineToClient(line));
        }
    }

    file.close();
    return clients;
}


// Prints all clients in formatted table
void PrintClients(const vector<Client>& clients)
{
    cout << "\nTotal Clients: " << clients.size() << "\n\n";

    cout << left
         << setw(15) << "Account"
         << setw(10) << "PIN"
         << setw(25) << "Name"
         << setw(15) << "Phone"
         << setw(10) << "Balance"
         << "\n";

    cout << string(75, '-') << "\n";

    for (const Client& client : clients)
    {
        cout << left
             << setw(15) << client.accountNumber
             << setw(10) << client.pinCode
             << setw(25) << client.name
             << setw(15) << client.phone
             << setw(10) << client.balance
             << "\n";
    }

    cout << "\n";
}

void ShowClientsScreen()
{
    vector<Client> clients = LoadClientsFromFile();
    PrintClients(clients);

    cout << "Press Enter to return to menu...";
    cin.ignore();
    cin.get();
}






// Runs the main application 
void RunApplication()
{
    short userChoice = 0;

    do
    {
        PrintMainMenu();
        cout << "Choose an option (1-7): ";
        cin >> userChoice;

        switch (static_cast<MainMenuOption>(userChoice))
        {
            case MainMenuOption::ShowClients:
                ShowClientsScreen();
                break;

            case MainMenuOption::Exit:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Feature not implemented yet.\n";
        }

    } while (userChoice != static_cast<short>(MainMenuOption::Exit));
}

// Entry point of program
int main()
{
    RunApplication();
    return 0;
}