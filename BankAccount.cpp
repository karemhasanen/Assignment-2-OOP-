#include "BankAccount.h"
#include "BankingApplication.h"
#include "bits/stdc++.h"

BankAccount::BankAccount(){}

BankAccount::BankAccount(string n, string a, string m, int t, double b ,string j,string e,char g): Client(n,a,m,t,b,j,e,g){}

double BankAccount::withDraw(double b , string ID) {
    string temp4 = KnowId(ID);
    string tempW[10];
    stringstream ss;
    ss << temp4;
    for (int i = 0; i < 10; ++i) {
        getline(ss,tempW[i],',');
    }
    balance = stod(tempW[5]);

    if (b <= balance) {
        balance -= b;
        fstream file;
        file.open("data.txt",ios::in);
        fstream f2;
        f2.open("data2.txt",ios::out);
        string Temp = "" , temp;
        int line = 1;
        while (getline(file,temp)){
            if (line == stoi(tempW[9])){
                tempW[5] = to_string(balance);
                for (int i = 0; i < 9; ++i) {
                    if (i != 8){
                    f2 << tempW[i] << ',';
                    } else{
                        f2 << tempW[i];
                    }
                }
                f2 << endl;
            } else{
                f2 << temp << endl;
            }
            line++;
        }
        f2.close();
        file.close();
        remove("data.txt");
        rename("data2.txt","data.txt");

    }else{
        throw invalid_argument{"Sorry. This is more than what you can withdraw. "};
    }

}

double BankAccount::deposit(double b, string ID) {
    string temp4 = KnowId(ID);
    string tempW[10];
    stringstream ss;
    ss << temp4;
    for (int i = 0; i < 10; ++i) {
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
        if (line == stoi(tempW[9])) {
            tempW[5] = to_string(balance);
            for (int i = 0; i < 9; ++i) {
                if (i != 8) {
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
}
