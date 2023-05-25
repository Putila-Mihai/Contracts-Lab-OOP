
#ifndef LAB6_7_VALIDATOR_H
#define LAB6_7_VALIDATOR_H

#include "Contract.h"
#include <string>
#include <vector>
using std::string;
using std::ostream;
using std::vector;


class ValidateException {
    vector<string> msgs;
public:
    explicit ValidateException(const vector<string>& errors) : msgs{errors} {}

    friend ostream &operator<<(ostream &out, const ValidateException &ex);
};

ostream &operator<<(ostream &out, const ValidateException &ex);

class Validator {
public:
    static void validate(const contract &c);

};

void test_validator();

#endif