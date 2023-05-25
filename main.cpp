#include "Headers/validator.h"
#include "Headers/Repo.h"
#include "Headers/Service.h"
#include "Headers/console.h"
#include "Headers/Contract.h"

template <typename MyVector>
MyVector testCopyIterate(MyVector v) {
    int totalPrice = 0;
    for (auto el : v) {
        totalPrice += el.get_ore();
    }
    contract p{ "total",totalPrice,"tt","asdas" };
    v.add(p);
    return v;
}

template <typename MyVector>
void addPets(MyVector& v, int cate) {
    for (int i = 0; i<cate; i++) {
        contract p{ std::to_string(i) + "_type",i,"c","a" };
        v.add(p);
    }
}

template <typename MyVector>
void testCreateCopyAssign() {
    MyVector v;//default constructor
    addPets(v, 100);
    assert(v.size() == 100);
    assert(v.get(50).get_denumire() == "50_type");

    MyVector v2{ v };//constructor de copiere
    assert(v2.size() == 100);
    assert(v2.get(50).get_denumire() == "50_type");

    MyVector v3;//default constructor
    v3 = v;//operator=   assignment
    assert(v3.size() == 100);
    assert(v3.get(50).get_denumire() == "50_type");

    auto v4 = testCopyIterate(v3);
    assert(v4.size() == 101);
    assert(v4.get(50).get_denumire() == "50_type");
}

/*
  Test pentru move constructor si move assgnment
*/
template <typename MyVector>
void testMoveConstrAssgnment() {
    std::vector<MyVector> v;
    //adaugam un vector care este o variabila temporara
    //se v-a apela move constructor
    v.push_back(MyVector{});

    //inseram, la fel se apeleaza move costructor de la vectorul nostru
    v.insert(v.begin(),MyVector{});

    assert(v.size() == 2);

    MyVector v2;
    addPets(v2, 50);

    v2 = MyVector{};//move assignment

    assert(v2.size() == 0);

}
template <typename MyVector>
void testAll() {
    //testCreateCopyAssign<MyVector>();
    testMoveConstrAssgnment<MyVector>();
}


void test_all() {
    testeRepo();
    test_validator();
    test_service();
    test_contract();
    test_all();
}

void add5(service &ctr) {
    ctr.addcontract("OOP", 25, "Info", "Mihai");
    ctr.addcontract("SD", 20, "Math", "Ion");
    ctr.addcontract("SDA", 22, "Info", "Ionel");
    ctr.addcontract("OS", 23, "Info", "Ionut");
    ctr.addcontract("Geo", 19, "Math", "Ionica");
}

int main() {
   // test_all();
    repo rep;
    Validator val;
    service ctr{rep, val};
    add5(ctr);
    ConsoleUI ui{ctr};
    ui.start();
    return 0;
}
