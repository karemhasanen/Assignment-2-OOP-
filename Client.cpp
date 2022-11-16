#include "Client.h"
#include <fstream> ///
void Client::numLines(){
    int numlines = 0;
    string line;
    fstream f;
    f.open("data.txt",ios::in);
    while(getline(f,line)){
        numlines++;
    }
    id = numlines + 1;
}

Client::Client() {}

Client::Client(string n, string a, string m, int t, double b ,string j,string e,char g) {
    name = n;
    address = a;
    mobileNumber = m;
    BankAccType = t;
    balance = b;
    numLines();
    ID += to_string(id);
    job = j;
    email = e;
    gender = g;
    fstream data;
    data.open("data.txt", ios::app);
    if (BankAccType == 1) {
        data << ID << "," << name << "," << address << "," << mobileNumber << "," << BankAccType << "," << balance
             << "," << job << "," << email << "," << gender << endl;
    }
    data.close();
}
string Client::getID(){
    return ID;
}
void Client::SetBalance(double b){
    balance = b;
}
double Client::GetBalance() {
    return balance;
}
