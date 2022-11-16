#include "checks.h"

bool check_email(string em) {

    regex filter("^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$");
    return regex_match(em , filter);

}
bool check_phone(string ph) {

    regex filter("(01([0-2]|5)[0-9]{8})");
    return regex_match(ph , filter);

}
bool check_name(string us) {

    regex filter("([A-z\\_]| )+");
    if (regex_match(us , filter))
        return true;
    return false;
}
bool check_gen(string g){

    regex filter("([F]|[M]){1}");
    return regex_match(g , filter);

}
bool check_address(string a){

    regex filter("([A-z]|[0-9]|-|_| )+");
    return regex_match(a , filter);

}
