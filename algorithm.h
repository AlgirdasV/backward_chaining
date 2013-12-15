#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <string>

std::vector<int> backward_chaining(char, int);
bool ar_tikslas_tarp_faktu(char);
void print_vector(std::vector <int> );
void print_vector(std::vector <char> );
void print_zingsniai(int, int );
bool salygos_patenkintos(int taisykle);
void salygos(std::string taisykle);
void print_answer(std::vector <int> vektorius, bool);
std::string print_taisykle(int);

extern std::vector<char> faktai;
extern std::string tikslas;
extern std::vector<std::string> taisykles;

#endif
