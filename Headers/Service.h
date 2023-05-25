//
// Created by ultra on 07.04.2023.
//

#ifndef LAB6_7_SERVICE_H
#define LAB6_7_SERVICE_H

#include "Contract.h"
#include "Repo.h"
#include <string>
#include "VektorTemplate.h"
#include <functional>
#include "validator.h"

using std::function;

class service {
    repo &rep;
    Validator &val;

    /*
     * General funtion to filter the list
     * fct it's the funtion used to filter
     * return a list of contracts
     */
    Vektor<contract> filter(const function<bool(const contract &)>& fct);

    /*
     * General funtion to sort the list of contracts
     * lesser funtion that compare  2 contracts ,verify the relation between them
     * it can be any funtion that respect the structure (return bool and have 2 contract parameters
     * retunr a list of contracts by the given criteria
     */
    Vektor<contract> generalSort(bool (*lesser)(const contract &, const contract &));

public:
    service(repo &rep, Validator &val) : rep{rep}, val{val} {}

    service(const service &ot) = delete;

    /*
     * return all contracts
     */
    const Vektor<contract> &getall() noexcept {
        return rep.getall();
    }

    /*
     * return all contracts that have more hours that a given number
     */
    Vektor<contract> filter_greater(int min_ore);

    /*
     * return all contracts that have save teacher as the given one
     */
    Vektor<contract> filter_teacher(const string& teacher);

    /*
     * sort the list by "denumire"
     */
    Vektor<contract> sort_denumire();
    /*
     * sort the list by "ore"
     */
    Vektor<contract> sort_tip_prof();
    /*
     * sort the list by "tip" and "profesor"
     */
    Vektor<contract> sort_ore();
    /*
     * add new contract
     * throw exception if arleady exist
     */
    void addcontract(const string &denumire, int ore, const string &tip, const string &profesor);

    /*
     * delete a contract from the list
     * throw exception if doesn't exist
     */
    void delete_s(const string &denumire);

    /*
     * modify a contract from  the list
     * throw exception if doesn't exist
     */
    void modify_s(const string &denumire, int ore, const string &tip, const string &profesor);

    /*
     * search an contract by it's disciplina
     * throw exception if the contract doesn't exist
     */
    const contract &search_s(const string &denumire);

};

void test_service();

#endif //LAB6_7_SERVICE_H
