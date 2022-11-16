#include "SavingBankAccount.h"
#include "fstream"

SavingBankAccount::SavingBankAccount(){}

SavingBankAccount::SavingBankAccount(string n, string a, string m, int t, double b, string j, string e, char g , double min) : Client(n, a, m, t, b, j, e, g){
    minimumBalance = min;
    fstream data;
    data.open("data.txt", ios::app);
    data << ID << "," << name << "," << address << "," << mobileNumber << "," << BankAccType << "," << balance
         << "," << job << "," << email << "," << gender << "," << minimumBalance << endl;

}

double  SavingBankAccount::deposit(double b , string ID) {
    if (b >= 100){
        string temp4 = KnowId(ID);
        string tempW[11];
        stringstream ss;
        ss << temp4;
        for (int i = 0; i < 11; ++i) {
            getline(ss, tempW[i], ',');
        }
        balance = stod(tempW[5]);

        balance += b;
        fstream file;
        file.open("data.txt", ios::in);
        fstream f2;
        f2.open("data2.txt", ios::out);
        string  temp;
        int line = 1;
        while (getline(file, temp)) {
            if (line == stoi(tempW[10])) {
                tempW[5] = to_string(balance);
                for (int i = 0; i < 10; ++i) {
                    if (i != 9) {
                        f2 << tempW[i] << ',';
                    } else {
                        f2 << tempW[i];
                    }
                }
                f2 << endl;
            } else {
                f2 << temp << endl;
            }
            line++;
        }
        f2.close();
        file.close();
        remove("data.txt");
        rename("data2.txt", "data.txt");
    }else{
        throw invalid_argument{"Minimum balance to deposit is 100 L.E."};
    }
}
double SavingBankAccount::withDraw(double b , string ID) {

        string temp4 = KnowId(ID);
        string tempW[11];
        stringstream ss;
        ss << temp4;
        for (int i = 0; i < 11; ++i) {
            getline(ss, tempW[i], ',');
        }
        balance = stod(tempW[5]);
        minimumBalance = stod(tempW[9]);

    if (balance - b >= minimumBalance) {

        balance -= b;
        fstream file;
        file.open("data.txt", ios::in);
        fstream f2;
        f2.open("data2.txt", ios::out);
        string temp;
        int line = 1;
        while (getline(file, temp)) {
            if (line == stoi(tempW[10])) {
                tempW[5] = to_string(balance);
                for (int i = 0; i < 10; ++i) {
                    if (i != 9) {
                        f2 << tempW[i] << ',';
                    } else {
                        f2 << tempW[i];
                    }
                }
                f2 << endl;
            } else {
                f2 << temp << endl;
            }
            line++;
        }
        f2.close();
        file.close();
        remove("data.txt");
        rename("data2.txt", "data.txt");
    }else{
        throw invalid_argument{"The new balance is less than minimum balance"};
    }
}
