#include "Headers/validator.h"
#include <assert.h>
#include <sstream>

void Validator::validate(const contract &c) {
    vector<string> msgs;
    if (c.get_ore() < 0) msgs.emplace_back("numarul de ore trebuie sa fie un numar pozitiv");
    if (c.get_tip().empty()) msgs.emplace_back("tip vid!");
    if (c.get_profesor().empty())msgs.emplace_back("profesor vid");
    if (c.get_denumire().empty()) msgs.emplace_back("denumire vida!");
    if (!msgs.empty()) {
        throw ValidateException(msgs);
    }
}

ostream &operator<<(ostream &out, const ValidateException &ex) {
    for (const auto& msg : ex.msgs) {
        out << msg << " ";
    }
    return out;
}

void test_validator() {
    Validator v;
    contract c{"", -1, "", ""};
    try {
        v.validate(c);
    }
    catch (const ValidateException &ex) {
        std::stringstream sout;
        sout << ex;
        auto mesaj = sout.str();
        assert(mesaj.find("negativ") >= 0);
        assert(mesaj.find("vid") >= 0);
    }

}