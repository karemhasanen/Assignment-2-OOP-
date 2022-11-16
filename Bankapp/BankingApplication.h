#ifndef BANKINGAPPLICATION_H ///
#define BANKINGAPPLICATION_H ///

#include <iostream> ///
using namespace std; ///

class BankingApplication {
protected:
    int choice;
public:
    BankingApplication();
    BankingApplication(int x);
    string KnowId(string);
    int display();
    void setChoice(int c);
    int getChoice();
};

#endif /// BANKINGAPPLICATION_H
