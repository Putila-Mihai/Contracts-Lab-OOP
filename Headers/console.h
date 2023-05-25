
#ifndef LAB6_7_CONSOLE_H
#define LAB6_7_CONSOLE_H

#include "Service.h"
#include "Contract.h"

class ConsoleUI {
    service &ctr;

    /*
    Read a contract from input and addd it to the list
    */
    void addUI();

    /*
    Print the list of contracts
    */
    static void print(const Vektor<contract> &contracts);

    /*
     * delete a contract
     * throw exception if the contract doesn't exist
     */
    void delete_UI();

    /*
     * modify a contract
     * throw exception if the contract doesn't exist
     */
    void modify_UI();

    /*
     * search an contract by it's disciplina
     * throw exception if the contract doesn't exist
     */
    void search_UI();

    /*
     * filter all contract by their number of hours
     */
    void filter_h_UI();

    /*
     * filter all contract by their teacher
     */
    void filter_t_UI();
    /*
     * sort the list of contract by "denumire"
     */
    void sort_d_UI();
    /*
     * sort the list of contracts by "ore"
     */
    void sort_o_UI();
    /*
     * sort the list of contracts by "tip" and "profesor"
     */
    void sort_tp_UI();
public:
    ConsoleUI(service &ctr) : ctr{ctr} {
    }

    ConsoleUI(const ConsoleUI &ot) = delete;

    /*
     * start the app
     */
    void start();
};

#endif //LAB6_7_CONSOLE_H
