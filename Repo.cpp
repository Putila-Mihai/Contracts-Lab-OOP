#include "Headers/Repo.h"
#include <assert.h>
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

void repo::store(const contract &c) {
    if (exist(c)) {
        throw RepoException("Exista deja acest contract:" + c.get_denumire());
    }
    all.add(c);
}

void repo::delete_contract(const std::string &denumire) {
    int ok = 0;
    for (int i = 0; i < all.size(); i++) {
        if (all.get(i).get_denumire() == denumire) {
            ok = 1;
            all.erase(i);
            break;
        }
    }
    if (ok == 0) {
        throw RepoException("Acest contract nu exista");
    }
}

void repo::modify_contract(const string &denumire, const int &ore, const string &tip, const string &profesor) {
    int ok = 0;
    for (int i = 0; i < all.size(); i++) {
        if (all.get(i).get_denumire() == denumire) {
            ok = 1;
            all.get(i).set_profesor(profesor);
            all.get(i).set_ore(ore);
            all.get(i).set_tip(tip);
            break;
        }
    }
    if (ok == 0) {
        throw RepoException("Acest contract nu exista");
    }

}

bool repo::exist(const contract &c) const {
    try {
        find(c.get_denumire(), c.get_tip(), c.get_profesor());
        return true;
    }
    catch (RepoException &) {
        return false;
    }
}

const contract &repo::find(const string &denumire, const string &tip, const string &profesor) const {
    for (int i=0;i<all.size();i++) {
        if (all.get(i).get_denumire() == denumire && all.get(i).get_profesor() == profesor && all.get(i).get_tip() == tip) {
            return all.get(i);
        }
    }
    throw RepoException("Nu exista acest contract");
}

const Vektor<contract> &repo::getall() const noexcept {
    return all;
}

ostream &operator<<(ostream &out, const RepoException &ex) {
    out << ex.msg;
    return out;
}

const contract &repo::find_by_d(const string &denumire) const {
    for (int i=0;i<all.size();i++) {
        if (all.get(i).get_denumire() == denumire) {
            return all.get(i);
        }
    }
    throw RepoException("Nu exista acest contract");
}


//!!!!!!!!!!!!!!!!!!!!!!TEST!!!!!!!!!!!!!!!!!!!!!!!!



void test_adauga() {
    repo rep;
    rep.store(contract{"OOP", 20, "Info", "mihai"});
    assert(rep.getall().size() == 1);
    assert(rep.find("OOP", "Info", "mihai").get_denumire() == "OOP");
    assert(rep.find_by_d("OOP").get_tip() == "Info");
    try {
        rep.store(contract{"OOP", 20, "Info", "mihai"});
        assert(false);
    }
    catch (const RepoException &) {
        assert(true);
    }
    try {
        rep.find("c", "c", "c");
        assert(false);
    }
    catch (const RepoException &e) {
        stringstream os;
        os << e;
        assert(os.str().find("exista") >= 0);
    }
    try {
        rep.find_by_d("c");
        assert(false);
    }
    catch (const RepoException &e) {
        stringstream os;
        os << e;
        assert(os.str().find("exista") >= 0);
    }
}

void test_cauta() {
    repo rep;
    rep.store(contract{"a", 20, "a", "a"});
    rep.store(contract{"b", 20, "b", "b"});

    auto c = rep.find("a", "a", "a");
    assert(c.get_denumire() == "a");
    assert(c.get_profesor() == "a");
    assert(c.get_tip() == "a");
    assert(c.get_ore() == 20);

    //throw exception
    try {
        rep.find("a", "b", "c");
        assert(false);
    }
    catch (RepoException &) {
        assert(true);
    }
}

void test_delete() {
    repo rep;
    rep.store(contract{"a", 20, "a", "a"});
    rep.store(contract{"b", 20, "b", "b"});
    rep.delete_contract("a");
    assert(rep.getall().size() == 1);
    try {
        rep.delete_contract("sad");
        assert(false);
    }
    catch (const RepoException &) {
        assert(true);
    }
}

void test_modify() {
    repo rep;
    rep.store(contract{"a", 20, "a", "a"});
    rep.modify_contract("a", 40, "b", "s");
    try {
        rep.modify_contract("assag", 40, "b", "s");
        assert(false);
    }
    catch (const RepoException &) {
        assert(true);
    }
}

void testeRepo() {
    test_adauga();
    test_cauta();
    test_delete();
    test_modify();
}
