#include "BankingApplication.h"
#include "BankAccount.h" ///
#include "SavingBankAccount.h" ///
#include "Client.h"
#include "regex"
#include "sstream"
#include "checks.h"

BankingApplication::BankingApplication(){}
BankingApplication::BankingApplication(int x){
    choice = x;
    if (choice==1){
        string n,a,m_b,j,em,gen;
        double bal;
        int ban_type;
        cout<<"please enter your name =========>";
        cin.ignore();
        getline(cin,n);
        if (!check_name(n)){
            throw invalid_argument{"The name is invalid"};
        }
        cout<<"please enter your address =========>";
        getline(cin,a);
        if (!check_address(a)){
            throw invalid_argument{"The address is invalid"};
        }
        cout<<"please enter your mobile number =========>";
        cin>>m_b;
        if (!check_phone(m_b)){
            throw invalid_argument{"The mobile number is invalid"};
        }
        cout<<"please enter your job =========>";
        cin.ignore();
        getline(cin,j);
        if (!check_name(j)){
            throw invalid_argument{"The job is invalid"};
        }
        cout<<"please enter your email =========>";
        cin>>em;
        if (!check_email(em)){
            em = "";
            throw invalid_argument{"The email is invalid"};
        }
        cout<<"please enter your gender(M)for male,(F) for female =========>";
        cin>>gen;
        if (!check_gen(gen)){
            throw invalid_argument{"The gender is invalid"};
        }
        cout<<"what Type of Account Do You Like? (1) Basic (2) Saving – Type 1 or 2 =======>";
        cin>>ban_type;
        cout<<"please enter your starting balance =========>";
        cin>>bal;
        if (ban_type == 1) {
            char g = gen[0];
            BankAccount b(n, a, m_b, ban_type, bal, j, em, g);
            cout<<"Account has been created"<<endl;
            cout << "Your ID is ====> " << b.getID() << endl;
        }else{
            double minBal;
            cout << "enter your minimum balance ====> ";
            cin >> minBal;
            char g = gen[0];
            SavingBankAccount s(n, a, m_b, ban_type, bal, j, em, g , minBal);
            cout<<"Account has been created"<<endl;
            cout << "Your ID is ====> " << s.getID() << endl;
        }
    }
    else if (choice == 2){
        ifstream file;
        file.open("data.txt");
        string temp , temparr[10];
        int clientNum = 0;
        while (getline(file,temp)){
            clientNum++;
            cout << endl << "\nClient number " << clientNum << endl <<  endl;
            stringstream ss;
            ss << temp;
            for (int i = 0; i < 10; ++i) {
                getline(ss,temparr[i],',');
            }
            cout << "Name ====> " << temparr[1] <<  endl;
            cout << "Address ====> " << temparr[2]<<  endl;
            cout << "Phone ====> " << temparr[3]<<  endl;
            cout << "Account ID ====> " << temparr[0]<<  endl;
            if (temparr[4] == "1"){
                cout << "Account type ====> Basic"<<  endl;
                cout << "Balance ====> " << temparr[5]<<  endl;
            } else{
                cout << "Account type ====> Saving"<<  endl;
                cout << "Balance ====> " << temparr[5]<<  endl;
                cout << "Minimum Balance ====> " << temparr[9]<<  endl;
            }

        }
    }
    else if (choice == 3){
        string ID , line , banktype = "", balance = "" , minBalance = "";
        int amount , count = 0;
        cout << "Please Enter Account ID (e.g., FCAI-015) =========> ";
        cin >> ID;
        cout << "Account ID : " << ID << endl;
        line = KnowId(ID);

        for (int i = 0; i < line.size(); ++i) {
            if (line[i] == ','){
                count++;
            }else if (count == 4){
                banktype += line[i];
            } else if (count == 5){
                balance += line[i];
            }else if (count == 9){
                minBalance += line[i];
            }
        }
        cout << "Balance: " << balance << endl;
        if (banktype == "1") {
            cout << "Account Type: Basic\n";
            cout << "Please Enter The Amount to Withdraw =========> ";
            cin >> amount;
            BankAccount B1;
            B1.withDraw(amount,ID);
        }else {
            cout << "Account Type: Saving\n";
            cout << "your minimum balance is ====> " << minBalance << endl;
            cout << "Please Enter The Amount to Withdraw =========> ";
            cin >> amount;
            SavingBankAccount S1;
            S1.withDraw(amount,ID);
        }

        cout << "Thank you!\n";
        cout << "Account ID ====> " << ID << endl;
        cout << "New Balance ====> " << stod(balance) - amount<< endl;
    }
    else if (choice == 4){

        string ID , line , banktype = "", balance = "" , minBalance = "";
        int amount , count = 0;
        cout << "Please Enter Account ID (e.g., FCAI-015) =========> ";
        cin >> ID;
        cout << "Account ID : " << ID << endl;
        line = KnowId(ID);
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] == ','){
                count++;
            }else if (count == 4){
                banktype += line[i];
            } else if (count == 5){
                balance += line[i];
            } else if (count == 9){
                minBalance += line[i];
            }
        }
        cout << "Balance: " << balance << endl;
        if (banktype == "1") {
            cout << "Account Type: Basic\n";
            cout << "Please Enter The Amount to deposit =========> ";
            cin >> amount;
            BankAccount B1;
            B1.deposit(amount,ID);
        }else {
            cout << "Account Type: Saving\n";
            cout << "your minimum balance is ====> " << minBalance << endl;
            cout << "Please Enter The Amount to deposit =========> ";
            cin >> amount;
            SavingBankAccount S1;
            S1.deposit(amount,ID);
        }

        cout << "Thank you!\n";
        cout << "Account ID: " << ID << endl;
        cout << "New Balance: " << stod(balance) + amount<< endl;
    }
    else{
        throw invalid_argument{"Please enter valid choice!"};

    }
}
string BankingApplication:: KnowId(string id){
    string temp2;
    ifstream f;
    f.open("data.txt");
    int lineNum = 1;
    while (getline(f,temp2)){
        string temp10 = "";
        for (int i = 0; i < temp2.size(); ++i) {
            if (temp2[i] == ','){
                if (id == temp10) {
                    temp2 += ',' + to_string(lineNum);
                    f.close();
                    return temp2;
                }
            }
            temp10 += temp2[i];
        }

        lineNum++;
    }
    throw invalid_argument{"The ID not found"};

}
int BankingApplication::display(){
    int choice;
    cout << "Welcome to FCAI Banking Application \n"
            "1. Create a New Account \n"
            "2. List Clients and Accounts \n"
            "3. Withdraw Money \n"
            "4. Deposit Money \n"
            "Please Enter Choice =========> ";
    cin >> choice;
    return choice;
}
