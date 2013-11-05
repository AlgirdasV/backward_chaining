#include "algorithm.h" 
#include <iostream>
	using namespace std;
#include <vector>
	using namespace std;
#include <string>
	using namespace std;
#include <algorithm>

vector<char> faktai;
vector<char> objektai;
string tikslas;
vector<string> taisykles;
vector <int> panaudotos_produkcijos;

void backward_chaining(){
	
}

void spausdinti_busena(){
	cout << "Busena: {";
	for (int i = 0; i < objektai.size(); i++) {
		if (i == objektai.size()-1)
			cout << objektai[i];
		else
			cout << objektai[i] << ", ";
	}
	cout << "}\n";
}
void spausdinti_plana(){
	cout << "Planas: {";
	for (int j = 0;  j < panaudotos_produkcijos.size() ; j++ ) {
		if (j == panaudotos_produkcijos.size()-1)
			cout << "R" << panaudotos_produkcijos[j]+1;
		else
			cout << "R" << panaudotos_produkcijos[j]+1 << ", ";
	}
	cout << "}\n";
}
void vykdyti_produkcija(int nr, bool& ivykdyta){
	cout << "      Produkcija R"<< nr+1<<" vykdoma; ";
	objektai.push_back(taisykles[nr][0]);
	ivykdyta = true;
	panaudotos_produkcijos.push_back(nr);
}
bool ar_tikslas_pasiektas(){
	bool pasiektas = false;
	for (int i = 0; i < faktai.size(); i++) {
		if ( faktai[i] == tikslas[0])
			pasiektas = true;
	}
	return pasiektas;
}
bool tikslas_pasiekiamas(){
	bool imanoma = false;
	for (int i = 0; i < taisykles.size(); i++) {
		for (int j = 0; j < taisykles[i].size(); j++) {
			if (tikslas[0] == taisykles[i][j])
				imanoma = true;
		}
	}
	for (int i = 0; i < faktai.size(); i++) {
		if (tikslas[0] == faktai[i])
				imanoma = true;
	}
	if (!imanoma) {
		cout << "\n3)Rezultatas\n";
		cout << "      Tikslo "<< tikslas[0]<<" pasiekti neimanoma\n";
		return false;
	}
	else
		return true;
}