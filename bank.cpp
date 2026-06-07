#include <iostream>
#include <fstream>
using namespace std;

class Account {
private:
    int accNo;
    char name[50];
    float balance;

public:
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void showAccount() const {
        cout << "\nAccount Number: " << accNo;
        cout << "\nName: " << name;
        cout << "\nBalance: " << balance << endl;
    }

    void deposit(float amt) {
        balance += amt;
    }

    void withdraw(float amt) {
        if (amt <= balance)
            balance -= amt;
        else
            cout << "Insufficient Balance!\n";
    }

    int getAccNo() const {
        return accNo;
    }

    float getBalance() const {
        return balance;
    }
};

void writeAccount() {
    Account acc;
    ofstream outFile("bank.dat", ios::binary | ios::app);

    acc.createAccount();
    outFile.write(reinterpret_cast<char*>(&acc), sizeof(acc));
    outFile.close();

    cout << "Account Created Successfully!\n";
}

void displayAccount(int accNo) {
    Account acc;
    ifstream inFile("bank.dat", ios::binary);

    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(acc))) {
        if (acc.getAccNo() == accNo) {
            acc.showAccount();
            return;
        }
    }
    cout << "Account not found!\n";
}

void modifyAccount(int accNo, int option) {
    Account acc;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    while (file.read(reinterpret_cast<char*>(&acc), sizeof(acc))) {
        if (acc.getAccNo() == accNo) {

            float amt;
            cout << "Enter amount: ";
            cin >> amt;

            if (option == 1)
                acc.deposit(amt);
            else if (option == 2)
                acc.withdraw(amt);

            int pos = (-1) * static_cast<int>(sizeof(acc));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&acc), sizeof(acc));

            cout << "Transaction Successful!\n";
            return;
        }
    }

    cout << "Account not found!\n";
}

int main() {
    int choice, accNo;

    do {
        cout << "\n===== BANK MENU =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Balance Inquiry\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            writeAccount();
            break;

        case 2:
            cout << "Enter Account Number: ";
            cin >> accNo;
            modifyAccount(accNo, 1);
            break;

        case 3:
            cout << "Enter Account Number: ";
            cin >> accNo;
            modifyAccount(accNo, 2);
            break;

        case 4:
            cout << "Enter Account Number: ";
            cin >> accNo;
            displayAccount(accNo);
            break;

        case 5:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}