#include "BankAccount.h"
#include "bits/stdc++.h"

class SavingBankAccount : public Client{
private:
    double minimumBalance = 1000;
public:
    SavingBankAccount();
    SavingBankAccount(string n, string a, string m, int t, double b , string j, string e, char g , double min);
    double deposit(double ,string );
    double withDraw(double , string );
};
