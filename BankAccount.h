#ifndef BANKACCOUNT_H ///
#define BANKACCOUNT_H ///



#include "Client.h" ///
#include<iostream> ///
using namespace std; ///

class BankAccount : public Client{
public:
    BankAccount();
    BankAccount(string n, string a, string m, int t, double b ,string j,string e,char g);
    virtual double withDraw(double,string);
    virtual double deposit(double,string);
};


#endif /// BANKACCOUNT_H
