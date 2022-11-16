#include "BigDecimalIntClass.h"
#ifndef UNTITLED16_BIGREAL_H
#define UNTITLED16_BIGREAL_H

class BigReal {
private:
    char dot;
    BigDecimalInt Int , fraction;
public:
    BigReal();
    BigReal(string);
    BigReal (BigDecimalInt );
    BigReal (const BigReal&);
    BigReal (BigReal&& );
    bool checkValidInput(string input);
    void setInt(BigDecimalInt i){
        Int = i;
    }
    void setFraction(BigDecimalInt f){
        fraction = f;
    }
    bool operator < (const BigReal& );
    bool operator > (const BigReal& );
    bool operator == (BigReal );
    BigReal& operator = (BigReal& );
    BigReal& operator= (BigReal&& other);
    BigReal operator + (BigReal);
    BigReal operator - (BigReal);
    int size();
    int sign();
    friend ostream &operator << (ostream &out, BigReal num);
    friend istream &operator >> (istream &in, BigReal &num);
};
ostream &operator << (ostream &out, BigReal num);
istream &operator >> (istream &in, BigReal &num);
#endif //UNTITLED16_BIGREAL_H
