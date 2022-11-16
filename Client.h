#ifndef CLIENT_H ///
#define CLIENT_H ///


#include<iostream> ///
#include "BankingApplication.h" ///
using namespace std; ///

class Client : public BankingApplication {
protected:
    string name , address , mobileNumber , ID = "FCAI-00",job,email;
    char gender;
    int BankAccType ;
    int id;
    double balance;
public:
    void SetBalance(double);
    double GetBalance();
    Client();
    Client(string , string , string , int , double , string,string ,char);
    void numLines();
    string getID();
};

#endif /// CLIENT_H
