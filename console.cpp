#include "Headers/console.h"
#include "Headers/Contract.h"
#include<iostream>
#include <string>

using std::cout;
using std::cin;


void ConsoleUI::print(const Vektor<contract> &contracts) {
    cout << "Contracte:Denumire || Ore || Tip || Profesor";
    //for (const auto &c: contracts)
    for (int i=0;i<contracts.size();i++){
        cout << "\n                " << contracts.get(i).get_denumire() << " || " << contracts.get(i).get_ore() << " || " << contracts.get(i).get_tip() << " || "
             << contracts.get(i).get_profesor();
    }
}

void ConsoleUI::delete_UI() {
    string denumire;
    cout << '\n' << "Introduceti denumire: ";
    cin >> denumire;
    ctr.delete_s(denumire);
    cout << "sters cu succes\n";
}

void ConsoleUI::addUI() {
    string denumire, tip, profesor;
    int ore;
    cout << '\n' << "Introduceti denumire: ";
    cin >> denumire;
    cout << "Introduceti numar de ore";
    cin >> ore;
    cout << "Introduceti tipul: ";
    cin >> tip;
    cout << "Introduceti Profesor:  ";
    cin >> profesor;
    ctr.addcontract(denumire, ore, tip, profesor);
    cout << "Adaugat cu succes";
}

void ConsoleUI::modify_UI() {
    string denumire, tip, profesor;
    int ore;
    cout << '\n' << "Introduceti denumire: ";
    cin >> denumire;
    cout << "Introduceti numar de ore";
    cin >> ore;
    cout << "Introduceti tipul: ";
    cin >> tip;
    cout << "Introduceti Profesor:  ";
    cin >> profesor;
    ctr.modify_s(denumire, ore, tip, profesor);
    cout << "Modificat cu  succes";
}

void ConsoleUI::search_UI() {
    string denumire;
    cout << '\n' << "Introduceti denumire: ";
    cin >> denumire;
    cout << "\n                " << ctr.search_s(denumire).get_denumire() << " || " << ctr.search_s(denumire).get_ore()
         << " || " << ctr.search_s(denumire).get_tip() << " || "
         << ctr.search_s(denumire).get_profesor();
}

void ConsoleUI::filter_h_UI() {
    int min_h;
    cout << "Introduceti numarul minim de ore: ";
    cin >> min_h;
    print(ctr.filter_greater(min_h));
}

void ConsoleUI::filter_t_UI() {
    string t;
    cout << "Introduceti Profesorul: ";
    cin >> t;
    print(ctr.filter_teacher(t));
}

void ConsoleUI::sort_d_UI(){
    print(ctr.sort_denumire());
}
void ConsoleUI::sort_o_UI(){
    print(ctr.sort_ore());
}
void ConsoleUI::sort_tp_UI(){
    print(ctr.sort_tip_prof());
}
void ConsoleUI::start() {
    while (true) {
        cout << "\nMeniu:\n";
        cout
                << "[0]Stop [1]Adauga [2]Tipareste [3]Sterge [4]Modificare [5]Cautare disciplina [6]Filtrare numar de ore\n[7]Filtrare dupa profesor: "
                   "[8]Sortare dupa denumire [9]Sortare dupa ora: [10]Sortare dupa tip si profesor ";
        int cmd;
        cin >> cmd;
        try {
            switch (cmd) {
                case 1:
                    addUI();
                    break;
                case 2:
                    print(ctr.getall());
                    break;
                case 3:
                    delete_UI();
                    break;
                case 4:
                    modify_UI();
                    break;
                case 5:
                    search_UI();
                    break;
                case 6:
                    filter_h_UI();
                    break;
                case 7:
                    filter_t_UI();
                    break;
                case 8:
                    sort_d_UI();
                    break;
                case 9:
                    sort_o_UI();
                    break;
                case 10:
                    sort_tp_UI();
                    break;
                case 0:
                    return;
                default:
                    cout << "comanda invalida\n";

            }
        }
        catch (const RepoException &ex) {
            cout << ex << '\n';
        }
        catch (const ValidateException &ex) {
            cout << ex << '\n';
        }
    }
}