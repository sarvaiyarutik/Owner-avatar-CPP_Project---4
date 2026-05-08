#include <iostream>
#include <vector>
using namespace std;

class BankAccount
{
private:
    int AccountNumber;
    string AccountHolderName;
    double Balance;

public:
    BankAccount(int accNo, string name, double bal)
    {
        AccountNumber = accNo;
        AccountHolderName = name;
        Balance = bal;
    }

    void deposit(double amount)
    {
        Balance = Balance + amount;
        cout << "Deposit Successfully." << endl;
    }

    virtual void withdraw(double amount)
    {
        if (amount <= Balance)
        {
            Balance = Balance - amount;
            cout << "Withdraw Successfully." << endl;
        }
        else
        {
            cout << "Insufficient Balance" << endl;
        }
    }

    double getbalance()
    {
        return Balance;
    }

    virtual void calculateInterest()
    {
        cout << "Interest calculation in BankAccount." << endl;
    }

    virtual void displayAccountInfo()
    {
        cout << "\nAccount Number      : " << AccountNumber << endl;
        cout << "Account Holder Name : " << AccountHolderName << endl;
        cout << "Balance             : " << Balance << endl;
    }

    virtual ~BankAccount()
    {
    }
};

class SavingsAccount : public BankAccount
{
private:
    double interestRate;

public:
    SavingsAccount(int accNo, string name, double bal, double rate)
        : BankAccount(accNo, name, bal)
    {
        interestRate = rate;
    }

    void calculateInterest() override
    {
        double interest = getbalance() * interestRate / 100;
        cout << "Savings Account Interest : " << interest << endl;
    }
};

class CheckingAccount : public BankAccount
{
private:
    double overDraftLimit;

public:
    CheckingAccount(int accNo, string name, double bal, double limit)
        : BankAccount(accNo, name, bal)
    {
        overDraftLimit = limit;
    }

    void checkOverdraft(double amount)
    {
        if (amount > getbalance() + overDraftLimit)
        {
            cout << "Withdrawal exceeds overdraft limit" << endl;
        }
        else
        {
            cout << "Withdrawal is within overdraft limit" << endl;
        }
    }
};

class FixedDepositAccount : public BankAccount
{
private:
    int term;

public:
    FixedDepositAccount(int a, string n, double b, int t)
        : BankAccount(a, n, b)
    {
        term = t;
    }

    void calculateInterest() override
    {
        double interest = (getbalance() * 5 * term) / 100;
        cout << "FD Interest : " << interest << endl;
    }
};

int main()
{
    vector<BankAccount *> account;

    int choice;

    do
    {
        cout << "\n1. Savings Account" << endl;
        cout << "2. Checking Account" << endl;
        cout << "3. FD Account" << endl;
        cout << "4. Display All" << endl;
        cout << "5. Deposit" << endl;
        cout << "6. Withdraw" << endl;
        cout << "7. Calculate Interest" << endl;
        cout << "8. Exit" << endl;

        cout << "Enter your choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int accNo;
            string name;
            double bal, rate;

            cout << "Enter Account Number: ";
            cin >> accNo;

            cin.ignore();

            cout << "Enter Account Holder Name: ";
            getline(cin, name);

            cout << "Enter Balance: ";
            cin >> bal;

            cout << "Enter Interest Rate: ";
            cin >> rate;

            account.push_back(new SavingsAccount(accNo, name, bal, rate));

            cout << "Savings Account Created!" << endl;

            break;
        }

        case 2:
        {
            int accNo;
            string name;
            double bal, limit;

            cout << "Enter Account Number: ";
            cin >> accNo;

            cin.ignore();

            cout << "Enter Account Holder Name: ";
            getline(cin, name);

            cout << "Enter Balance: ";
            cin >> bal;

            cout << "Enter Overdraft Limit: ";
            cin >> limit;

            account.push_back(new CheckingAccount(accNo, name, bal, limit));

            cout << "Checking Account Created!" << endl;

            break;
        }

        case 3:
        {
            int accNo, term;
            string name;
            double bal;

            cout << "Enter Account Number: ";
            cin >> accNo;

            cin.ignore();

            cout << "Enter Account Holder Name: ";
            getline(cin, name);

            cout << "Enter Balance: ";
            cin >> bal;

            cout << "Enter Term (months): ";
            cin >> term;

            account.push_back(new FixedDepositAccount(accNo, name, bal, term));

            cout << "Fixed Deposit Account Created!" << endl;

            break;
        }

        case 4:
        {
            if (account.empty())
            {
                cout << "No Accounts Found!" << endl;
            }
            else
            {
                for (int i = 0; i < account.size(); i++)
                {
                    cout << "\n----- Account Index : " << i << " -----";
                    account[i]->displayAccountInfo();
                }
            }

            break;
        }

        case 5:
        {
            int A;
            double amount;

            cout << "Enter Account Index: ";
            cin >> A;

            cout << "Enter Deposit Amount: ";
            cin >> amount;

            if (A >= 0 && A < account.size())
            {
                account[A]->deposit(amount);
            }
            else
            {
                cout << "Invalid Account Index!" << endl;
            }

            break;
        }

        case 6:
        {
            int B;
            double amount;

            cout << "Enter Account Index: ";
            cin >> B;

            cout << "Enter Withdraw Amount: ";
            cin >> amount;

            if (B >= 0 && B < account.size())
            {
                account[B]->withdraw(amount);
            }
            else
            {
                cout << "Invalid Account Index!" << endl;
            }

            break;
        }

        case 7:
        {
            int index;

            cout << "Enter Account Index: ";
            cin >> index;

            if (index >= 0 && index < account.size())
            {
                account[index]->calculateInterest();
            }
            else
            {
                cout << "Invalid Account Index!" << endl;
            }

            break;
        }

        case 8:
        {
            cout << "Exit" << endl;
            break;
        }

        default:
        {
            cout << "Invalid Choice!" << endl;
            break;
        }
        }

    } while (choice != 8);

    for (int i = 0; i < account.size(); i++)
    {
        delete account[i];
    }

    return 0;
}