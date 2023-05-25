#ifndef LAB6_7_REPO_H
#define LAB6_7_REPO_H

#include "Contract.h"
#include <utility>
#include "VektorTemplate.h"
#include <string>
#include <ostream>

using std::string;
using std::ostream;

class repo {
    Vektor<contract> all;

    /*
     * Funtion verify if the contract arleady exist in the list
     * return ture if exist and false either
     */
    [[nodiscard]] bool exist(const contract &c) const;

public:
    repo() = default;

    /*
     * save contract to list
     * throw exception if arleady exist
     */
    void store(const contract &c);

    /*
     * search for a contract in list
     * throw expection if doesn't exist
     */
    [[nodiscard]] const contract &find(const string &denumire, const string &tip, const string &profesor) const;

    /*
     * search for a contract in list
     * throw expection if doesn't exist
     */
    [[nodiscard]] const contract &find_by_d(const string &denumire) const;

    /*
     * return all contracts from the list
     */
    [[nodiscard]] const Vektor<contract> &getall() const noexcept;

    /*
     * delete a contract from the list
     * throw exception if the contract doesn't exist
     */
    void delete_contract(const string &denumire);

    /*
     * modify the contract from the list
     * throw exception if the contract doesn't exist
     */
    void modify_contract(const string &denumire, const int &ore, const string &tip, const string &profesor);
};

class RepoException {
    string msg;
public:
    explicit RepoException(string exc) : msg{std::move(exc)} {}

    friend ostream &operator<<(ostream &out, const RepoException &ex);
};

ostream &operator<<(ostream &out, const RepoException &ex);

void testeRepo();

#endif //LAB6_7_REPO_H
