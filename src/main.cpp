#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

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
    system("cls"); // to clear the screen before showing the clients list, it is windows specific, for linux use system("clear");
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
// Screen to show all clients
void ShowClientsScreen()
{
    vector<Client> clients = LoadClientsFromFile();
    PrintClients(clients);

    cout << "Press Enter to return to menu...";
    cin.ignore();
    cin.get();
}

// Save all clients to file (used after delete/update)
void SaveClientsToFile(const vector<Client>& clients)
{
    ofstream file(CLIENTS_FILE); // overwrite file

    if (file.is_open())
    {
        for (const Client& client : clients)
        {
            file << ConvertClientToLine(client) << endl;
        }

        file.close();
    }
}

// Converts a Client struct into a single line string for file storage
string ConvertClientToLine(const Client& client)
{
    return client.accountNumber + "#//#" +
        client.pinCode + "#//#" +
        client.name + "#//#" +
        client.phone + "#//#" +
        to_string(client.balance);
}

// Appends a new client to the clients file
void SaveClientToFile(const Client& client)
{
    ofstream file(CLIENTS_FILE, ios::app); // append mode

    if (file.is_open())
    {
        file << ConvertClientToLine(client) << endl;
        file.close();
    }
}

// Checks if an account number already exists in the clients list
bool AccountExists(const string& accountNumber, const vector<Client>& clients)
{
    for (const Client& client : clients)
    {
        if (client.accountNumber == accountNumber)
            return true;
    }
    return false;
}

// Find client by account number
bool FindClientByAccountNumber(const string& accountNumber, vector<Client>& clients, Client& client)
{
    for (Client& c : clients)
    {
        if (c.accountNumber == accountNumber)
        {
            client = c;
            return true;
        }
    }

    return false;
}

// Reads client details from user input and returns a Client struct
Client ReadNewClient()
{
    Client client;

    cout << "Enter Account Number: ";
    cin >> client.accountNumber;

    cout << "Enter PIN Code: ";
    cin >> client.pinCode;

    cin.ignore(); // clear buffer before getline

    cout << "Enter Full Name: ";
    getline(cin, client.name);

    cout << "Enter Phone: ";
    getline(cin, client.phone);

    cout << "Enter Initial Balance: ";
    cin >> client.balance;

    return client;
}

// Screen to add a new client
void AddClientScreen()
{
    vector<Client> clients = LoadClientsFromFile();

    cout << "\n=== Add New Client ===\n";

    Client newClient = ReadNewClient();

    if (AccountExists(newClient.accountNumber, clients))
    {
        cout << "Error: Account number already exists.\n";
        return;
    }

    SaveClientToFile(newClient);

    cout << "Client added successfully.\n";
    system("pause"); // Wait for user to press a key before returning to menu

}

// Print detailed client information
void PrintClientCard(const Client& client)
{
    cout << "\nClient Information\n";
    cout << "------------------------\n";
    cout << "Account Number : " << client.accountNumber << endl;
    cout << "PIN Code       : " << client.pinCode << endl;
    cout << "Name           : " << client.name << endl;
    cout << "Phone          : " << client.phone << endl;
    cout << "Balance        : " << client.balance << endl;
}

// Delete client from vector
bool DeleteClientByAccountNumber(const string& accountNumber, vector<Client>& clients)
{
    for (auto it = clients.begin(); it != clients.end(); ++it)
    {
        if (it->accountNumber == accountNumber)
        {
            clients.erase(it);
            return true;
        }
    }

    return false;
}

// Screen to delete client
void DeleteClientScreen()
{
    vector<Client> clients = LoadClientsFromFile();

    cout << "\n=== Delete Client ===\n";

    string accountNumber;
    cout << "Enter Account Number to delete: ";
    cin >> accountNumber;

    Client client;

    if (!FindClientByAccountNumber(accountNumber, clients, client))
    {
        cout << "Client not found.\n";
        system("pause");
        return;
    }

    PrintClientCard(client);

    char answer;
    cout << "\nAre you sure you want to delete this client? (y/n): ";
    cin >> answer;

    if (answer == 'y' || answer == 'Y')
    {
        DeleteClientByAccountNumber(accountNumber, clients);
        SaveClientsToFile(clients);

        cout << "\nClient deleted successfully.\n";
    }
    else
    {
        cout << "\nDelete cancelled.\n";
    }

    system("pause");
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

        case MainMenuOption::AddClient:
            AddClientScreen();
            break;
		
		case MainMenuOption::DeleteClient:
			DeleteClientScreen();
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