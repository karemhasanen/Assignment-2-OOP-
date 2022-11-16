#include "BigReal.h"
#include "regex"
#include "string"

bool BigReal::checkValidInput(string input){
    regex validInput("[-+]?[0-9]+.[0-9]+");
    return regex_match(input, validInput);
}
BigReal::BigReal() {
    Int.setNumber("0");
    fraction.setNumber("0");
    dot = '.';
}
BigReal::BigReal(BigDecimalInt bigInteger) {
    Int = bigInteger;
    dot = '.';
    fraction.setNumber("0");
}
BigReal::BigReal(string num){
    if (!checkValidInput(num)){
        throw invalid_argument{"please enter valid number!"};
    }
    string temp = "" , temp2 = "";
    int i = 0;
    while (num[i] != '.'){
        temp+= num[i];
        i++;
    }
    i++;
    while (i < num.size()){
        temp2+= num[i];
        i++;
    }
    Int.setNumber(temp);
    dot = '.';
    fraction.setNumber(temp2);
}
BigReal::BigReal (const BigReal& anotherBigReal){
    Int = anotherBigReal.Int;
    fraction = anotherBigReal.fraction;
    dot = '.';
}
BigReal::BigReal (BigReal&& anotherBigReal){
    Int = anotherBigReal.Int;
    fraction = anotherBigReal.fraction;
    dot = '.';
}
bool BigReal::operator < (const BigReal& anotherBigReal){
    BigDecimalInt i = anotherBigReal.Int;
    if (Int < anotherBigReal.Int){
        return true;
    } else if (Int == anotherBigReal.Int && fraction < anotherBigReal.fraction && Int.getSign() == '+' && i.getSign() == '+'){
        return true;
    } else if (Int == anotherBigReal.Int && fraction > anotherBigReal.fraction && Int.getSign() == '-' && i.getSign() == '-') {
        return true;
    }
    else{
        return false;
    }
}
bool BigReal::operator > (const BigReal& anotherBigReal){
    BigDecimalInt i = anotherBigReal.Int;
    if (Int > anotherBigReal.Int){
        return true;
    } else if (Int == anotherBigReal.Int && fraction > anotherBigReal.fraction && Int.getSign() == '+' && i.getSign() == '+'){
        return true;
    } else if (Int == anotherBigReal.Int && fraction < anotherBigReal.fraction && Int.getSign() == '-' && i.getSign() == '-') {
        return true;
    }
    else{
        return false;
    }
}
bool BigReal::operator == (BigReal anotherBigReal){
    if (Int == anotherBigReal.Int && fraction == anotherBigReal.fraction){
        return true;
    }else{
        return false;
    }
}
BigReal& BigReal::operator = (BigReal& anotherBigReal){
    Int = anotherBigReal.Int;
    fraction = anotherBigReal.fraction;
    dot = '.';
    return *this;
}
BigReal& BigReal::operator = (BigReal&& anotherBigReal){
    Int = anotherBigReal.Int;
    fraction = anotherBigReal.fraction;
    dot = '.';
    return *this;
}
BigReal BigReal::operator + (BigReal anotherBigReal){
    BigReal temp ;
    int counter = min(fraction.size() , anotherBigReal.fraction.size());
    int numDigits = max(fraction.size() , anotherBigReal.fraction.size());
    temp.Int = Int + anotherBigReal.Int;
    BigDecimalInt temp2 , one("1");
    string s1 = fraction.getNumber() , s2 = "" , s3 = anotherBigReal.fraction.getNumber();
    if (Int.getSign() == '+' && anotherBigReal.Int.getSign() == '+') {
        if (fraction.size() > anotherBigReal.fraction.size()) {
            while (counter < fraction.size()) {
                s2 = s2 + s1[counter];
                counter++;
            }
            int x = s1.find(s2);
            s1.replace(x, s2.size(), "");
            fraction.setNumber(s1);
            temp.fraction = fraction + anotherBigReal.fraction;
            s1 = temp.fraction.getNumber();
            s1 += s2;
            if (s1.size() > numDigits) {
                s1.erase(s1.begin());
                temp.fraction.setNumber(s1);
                temp.Int = temp.Int + one;
            } else {
                temp.fraction.setNumber(s1);
            }
        } else if (anotherBigReal.fraction.size() > fraction.size()) {
            while (counter < anotherBigReal.fraction.size()) {
                s2 = s2 + s3[counter];
                counter++;
            }
            int x = s3.find(s2);
            s3.replace(x, s2.size(), "");
            anotherBigReal.fraction.setNumber(s3);
            temp.fraction = fraction + anotherBigReal.fraction;
            s3 = temp.fraction.getNumber();
            s3 += s2;
            if (s3.size() > numDigits) {
                s3.erase(s3.begin());
                temp.fraction.setNumber(s3);
                temp.Int = temp.Int + one;
            } else {
                temp.fraction.setNumber(s3);
            }

        } else {
            temp.fraction = fraction + anotherBigReal.fraction;
            s3 = temp.fraction.getNumber();
            if (s3.size() > numDigits) {
                s3.erase(s3.begin());
                temp.fraction.setNumber(s3);
                temp.Int = temp.Int + one;
            } else {
                temp.fraction.setNumber(s3);
            }
        }
        return temp;
    }
    else if (Int.getSign() == '-' && anotherBigReal.Int.getSign() == '+'){
        Int.setSign('+');
        temp = anotherBigReal - *this;
    }
    else if (Int.getSign() == '+' && anotherBigReal.Int.getSign() == '-'){
        anotherBigReal.Int.setSign('+');
        temp = *this - anotherBigReal;
    }
    else if (Int.getSign() == '-' && anotherBigReal.Int.getSign() == '-'){
        Int.setSign('+');
        anotherBigReal.Int.setSign('+');
        temp = *this + anotherBigReal;
        temp.Int.setSign('-');
    }
}
BigReal BigReal::operator - (BigReal anotherBigReal) {
    BigReal temp;
    int counter = min(fraction.size(), anotherBigReal.fraction.size());
    int numDigits = max(fraction.size(), anotherBigReal.fraction.size());
    temp.Int = Int + anotherBigReal.Int;
    BigDecimalInt temp2, one("1"), zero("0"), ten("10");
    string s1 = fraction.getNumber(), s2 = "", s3 = anotherBigReal.fraction.getNumber();
    if (Int.getSign() == '+' && anotherBigReal.Int.getSign() == '+') {
        if (fraction.size() > anotherBigReal.fraction.size()) {
            while (counter < fraction.size()) {
                s3 += '0';
                counter++;
            }
            anotherBigReal.fraction.setNumber(s3);
            if (fraction > anotherBigReal.fraction) {
//            BigReal r1("8.385");
//            BigReal r2("9.2");
                if (Int < anotherBigReal.Int) {
                    string s4 = anotherBigReal.fraction.getNumber();
                    s4.insert(0, "1");
                    anotherBigReal.fraction.setNumber(s4);
                    anotherBigReal.Int = anotherBigReal.Int - one;
                    temp.fraction = anotherBigReal.fraction - fraction;
                    temp.Int = anotherBigReal.Int - Int;
                    temp.Int.setSign('-');
                    cout << temp.Int.getSign();
                }
                    //            BigReal r1("9.385");
//            BigReal r2("9.2");
                else if (Int == anotherBigReal.Int) {
                    temp.Int.setNumber("0");
                    temp.fraction = fraction - anotherBigReal.fraction;
                } //            BigReal r1("12.385");
//            BigReal r2("9.2");
                else {
                    temp.fraction = fraction - anotherBigReal.fraction;
                    temp.Int = Int - anotherBigReal.Int;
                }
            } else {
                //            BigReal r1("0.385");
//            BigReal r2("0.6");
                if (Int == zero && anotherBigReal.Int == zero) {
                    temp.fraction = anotherBigReal.fraction - fraction;
                    temp.Int.setNumber("-0");
                    cout << temp.Int.getSign();
                }//            BigReal r1("12.185");
//            BigReal r2("9.2");
                else if (Int > anotherBigReal.Int) {
                    string s4 = fraction.getNumber();
                    s4.insert(0, "1");
                    fraction.setNumber(s4);
                    Int = Int - one;
                    temp.fraction = fraction - anotherBigReal.fraction;
                    temp.Int = Int - anotherBigReal.Int;
                }//            BigReal r1("8.185");
//            BigReal r2("9.2");
                else if (Int < anotherBigReal.Int) {
                    temp.Int = anotherBigReal.Int - Int;
                    temp.fraction = anotherBigReal.fraction - fraction;
                    temp.Int.setSign('-');
                }
                    //            BigReal r1("9.185");
//            BigReal r2("9.2");
                else {
                    temp.fraction = fraction - anotherBigReal.fraction;
                    temp.fraction.setSign('+');
                    temp.Int.setNumber("-0");
                    cout << temp.Int.getSign();
                }
            }
        }
        else if (anotherBigReal.fraction.size() > fraction.size()) {
            while (counter < anotherBigReal.fraction.size()) {
                s1 += '0';
                counter++;
            }
            fraction.setNumber(s1);
            if (anotherBigReal.fraction > fraction) {
//            BigReal r1("8.385");
//            BigReal r2("9.2");
                if (anotherBigReal.Int < Int) {
                    string s4 = fraction.getNumber();
                    s4.insert(0, "1");
                    fraction.setNumber(s4);
                    Int = Int - one;
                    temp.fraction = fraction - anotherBigReal.fraction;
                    temp.Int = Int - anotherBigReal.Int;
                }
                    //            BigReal r1("9.385");
//            BigReal r2("9.2");
                else if (anotherBigReal.Int == Int) {
                    temp.fraction = fraction - anotherBigReal.fraction;

                    char x = temp.fraction.getSign();
                    if (temp.fraction.getSign() == '-') {
                        cout << x;
                        temp.fraction.setSign('+');
                    }

                    temp.Int.setNumber("0");
                }//            BigReal r1("12.385");
//            BigReal r2("9.2");
                else {
                    temp.fraction = fraction - anotherBigReal.fraction;
                    temp.Int = Int - anotherBigReal.Int;
                }
            } else {
                //            BigReal r1("0.385");
//            BigReal r2("0.6");
                if (anotherBigReal.Int == zero && Int == zero) {
                    temp.fraction = fraction - anotherBigReal.fraction;
                    temp.Int.setNumber("-0");
                    cout << temp.Int.getSign();
                }//            BigReal r1("12.185");
//            BigReal r2("9.2");

                else if (anotherBigReal.Int > Int) {
                    string s4 = anotherBigReal.fraction.getNumber();
                    s4.insert(0, "1");
                    anotherBigReal.fraction.setNumber(s4);
                    anotherBigReal.Int = anotherBigReal.Int - one;
                    temp.fraction = anotherBigReal.fraction - fraction;
                    temp.Int = anotherBigReal.Int - Int;
                    temp.Int.setSign('-');
                }//            BigReal r1("8.185");
//            BigReal r2("9.2");
                else if (anotherBigReal.Int < Int) {
                    temp.Int = Int - anotherBigReal.Int;
                    temp.fraction = fraction - anotherBigReal.fraction;
                }
                    //            BigReal r1("9.185");
//            BigReal r2("9.2");
                else {
                    temp.fraction = anotherBigReal.fraction - fraction;
                    temp.fraction.setSign('+');
                    temp.Int.setNumber("-0");
                }
            }
        }
        else if (fraction.size() == anotherBigReal.fraction.size()) {
            if (fraction > anotherBigReal.fraction) {
                temp.Int = Int - anotherBigReal.Int;
                temp.fraction = fraction - anotherBigReal.fraction;
            } else if (fraction < anotherBigReal.fraction) {
                if (Int > anotherBigReal.Int) {
                    string s4 = fraction.getNumber();
                    s4.insert(0, "1");
                    fraction.setNumber(s4);
                    Int = Int - one;
                    temp.fraction = fraction - anotherBigReal.fraction;
                    temp.Int = Int - anotherBigReal.Int;
                } else if (anotherBigReal.Int > Int) {
                    temp.Int = Int - anotherBigReal.Int;
                    temp.fraction = anotherBigReal.fraction - fraction;
                }
            } else {
                temp.fraction.setNumber("0");
                temp.Int = Int - anotherBigReal.Int;
            }
        }
    }
    else if (Int.getSign() == '-' && anotherBigReal.Int.getSign() == '+'){
        Int.setSign('+');
        temp = *this + anotherBigReal;
        temp.Int.setSign('-');
    }
    else if (Int.getSign() == '+' && anotherBigReal.Int.getSign() == '-'){
        anotherBigReal.Int.setSign('+');
        temp = *this + anotherBigReal;
    }
    else if (Int.getSign() == '-' && anotherBigReal.Int.getSign() == '-'){
        anotherBigReal.Int.setSign('+');
        Int.setSign('+');
        temp = anotherBigReal - *this;
    }
    string s6 = temp.fraction.getNumber();
    while (s6.size() < numDigits) {
        s6.insert(0, "0");
    }
    while (s6[s6.size()-1] == '0' && s6.size() != 1){
        s6.erase(s6.end()-1);
    }
    temp.fraction.setNumber(s6);
    return temp;
}
int BigReal::size() {
    return Int.size() + fraction.size() + 1;
}
int BigReal::sign() {
    return Int.sign();
}
istream &operator >> (istream &in, BigReal &num){
    string tempB;
    in >> tempB;
    if (!num.checkValidInput(tempB)){
        throw invalid_argument{"please enter valid number!"};
    }
    string temp = "" , temp2 = "";
    int i = 0;

    while (tempB[i] != '.'){
        temp+= tempB[i];
        i++;
    }
    i++;
    while (i < tempB.size()){
        temp2+= tempB[i];
        i++;
    }
    num.Int.setNumber(temp);
    num.dot = '.';
    num.fraction.setNumber(temp2);
    return in;
}
ostream &operator << (ostream &out, BigReal num){
    out << num.Int << num.dot << num.fraction << endl;
    return out;
}