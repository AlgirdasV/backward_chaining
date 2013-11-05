#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <string>

void backward_chaining();
bool tikslas_pasiekiamas();
void vykdyti_produkcija(int, bool& );
bool ar_tikslas_pasiektas();
void spausdinti_plana();
void spausdinti_busena();

extern std::vector<char> faktai;
extern std::string tikslas;
extern std::vector<std::string> taisykles;

#endif
