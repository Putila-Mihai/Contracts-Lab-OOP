#include "Headers/Service.h"
#include <assert.h>

void service::addcontract(const std::string &denumire, int ore, const std::string &tip, const std::string &profesor) {
    contract c{denumire, ore, tip, profesor};
    Validator::validate(c);
    rep.store(c);
}

void service::delete_s(const string &denumire) {
    rep.delete_contract(denumire);
}

void service::modify_s(const std::string &denumire, int ore, const std::string &tip, const std::string &profesor) {
    rep.modify_contract(denumire, ore, tip, profesor);
}

const contract &service::search_s(const string &denumire) {
    return rep.find_by_d(denumire);
}

Vektor<contract> service::filter(const function<bool(const contract &)>& fct) {
    Vektor<contract>rez;
    for (int i=0;i<=rep.getall().size();i++) {
        if (fct(rep.getall().get(i))) {
            rez.add(rep.getall().get(i));
        }
    }
    return rez;
}

Vektor<contract> service::filter_greater(int min_ore) {
    return filter([min_ore](const contract &c) {
        return c.get_ore() > min_ore;
    });
}

Vektor<contract> service::filter_teacher(const string& teacher) {
    return filter([teacher](const contract &c) {
        return c.get_profesor() == teacher;
    });
}

Vektor<contract> service::generalSort(bool (*lesser)(const contract &, const contract &)) {
    Vektor<contract> rez{rep.getall()};
    for (size_t i = 0; i < rez.size(); i++) {
        for (size_t j = i + 1; j < rez.size(); j++) {
            if (!lesser(rez.get(i), rez.get(j))) {
                contract aux = rez.get(i);
                rez.get(i) = rez.get(j);
                rez.get(j) = aux;
            }
        }
    }
    return rez;
}

Vektor<contract> service::sort_denumire() {
    return generalSort(cmpDenumire);
}

Vektor<contract> service::sort_ore() {
    return generalSort(cmpore);
}

Vektor<contract> service::sort_tip_prof() {
    return generalSort([](const contract &c1, const contract &c2) {
        if (c1.get_tip() == c2.get_tip()) {
            return c1.get_profesor() < c2.get_profesor();
        }
        return c1.get_tip() < c2.get_tip();
    });
}

/////////////////////////////////////////TEST////////////////////////////////////
void test_add_service() {
    repo rep;
    Validator val;
    service ctr{rep, val};
    ctr.addcontract("a", 2, "a", "c");
    assert(ctr.getall().size() == 1);
    try {
        ctr.addcontract("", -1, "", "");
        assert(false);
    }
    catch (ValidateException &) {
        assert(true);
    }
    assert(ctr.search_s("a").get_ore() == 2);
    //incerc sa adaug ceva ce existadeja
}

void test_deletes() {
    repo rep;
    Validator val;
    service ctr{rep, val};
    ctr.addcontract("a", 2, "a", "c");
    ctr.addcontract("b", 2, "5", "c");
    ctr.delete_s("a");
    assert(ctr.getall().size() == 1);

}

void test_modifys() {
    repo rep;
    Validator val;
    service ctr{rep, val};
    ctr.addcontract("a", 2, "a", "c");
    ctr.modify_s("a", 23, "sd", "asdfa");
    assert(ctr.getall().get(0).get_ore() == 23);

}

void test_filter() {
    repo rep;
    Validator val;
    service ctr{rep, val};
    ctr.addcontract("a", 2, "a", "c");
    ctr.addcontract("b", 26, "sd", "d");
    ctr.addcontract("c", 222, "a", "c");
    assert(ctr.filter_greater(25).size() == 2);
    assert(ctr.filter_teacher("d").size() == 1);
}

void testSort() {
    repo rep;
    Validator val;
    service ctr{rep, val};
    ctr.addcontract("asdasd", 323, "a", "d");
    ctr.addcontract("b", 22, "sd", "d");
    ctr.addcontract("c", 222, "a", "c");

    auto firstC = ctr.sort_denumire().get(0);
    assert(firstC.get_denumire() == "asdasd");

    firstC = ctr.sort_ore().get(0);
    assert(firstC.get_tip() == "sd");

    firstC = ctr.sort_tip_prof().get(0);
    assert(firstC.get_ore() == 222);
}

void test_service() {
    test_add_service();
    test_deletes();
    test_modifys();
    test_filter();
    testSort();
}