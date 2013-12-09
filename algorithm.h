#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <string>

std::vector<int> backward_chaining(char, int);
bool tikslas_pasiekiamas();
void vykdyti_produkcija(int, bool& );
bool ar_tikslas_tarp_faktu(char);
void spausdinti_plana();
void spausdinti_busena();
void print_vector(std::vector <int> );
void print_vector(std::vector <char> );
bool salygos_patenkintos(int taisykle);
void salygos(std::string taisykle);
void print_answer(std::vector <int> vektorius);

extern std::vector<char> faktai;
extern std::string tikslas;
extern std::vector<std::string> taisykles;

#endif
