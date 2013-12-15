#include "algorithm.h" 
#include <iostream>
	using namespace std;
#include <vector>
	using namespace std;
#include <string>
	using namespace std;
#include <algorithm>

vector<char> faktai;
string tikslas;
vector<string> taisykles;
vector<int> panaudotos_taisykles;
vector<char> ieskoti_tikslai;
char tmp = ' ';
vector<int> kelias;
bool need_to_print = true;
int zingsniu_skaicius = 0;
int zingsnis_kartojas = 0;
char buves_tikslas;

vector<int> backward_chaining(char goal, int lygis){
	bool rasta_produkcija = false;
	bool aklaviete = false;
	bool ciklas = false;
	vector<int> reikalingos_taisykles;

	zingsniu_skaicius++;
	print_zingsniai(zingsniu_skaicius, lygis);
	cout << "Tikslas "<< goal <<". ";
// 1: Tikriname ar tisklas nėra tarp duotųjų faktų
	if (ar_tikslas_tarp_faktu(goal) ){
// 2: Jei yra, tuomet išeiti
		exit(0);
	}
	need_to_print = false;
// 3: Jei tikslas nėra jau ieškotas
	if(std::find(ieskoti_tikslai.begin(), ieskoti_tikslai.end(),
								 goal) == ieskoti_tikslai.end()){
			rasta_produkcija = false;
// 4: Einame per visas taisykles:
			for (int i = 0; i < taisykles.size() ; i++ ) {
// 5: Jei taisyklė yra nepanaudota:
				if ( std::find(panaudotos_taisykles.begin(),	// ar produkcija yra tarp panaudotu produkciju:
							panaudotos_taisykles.end(), i)==panaudotos_taisykles.end() ){
// 6: Jei taisyklė veda į tikslą
					if (taisykles[i][0] == goal)
// 7: Tuomet pradėti
					{
// 8: Pasižymime ją kaip reikalingą:
						reikalingos_taisykles.push_back(i);
// 9: Pasižymime, kad radome į tikslą vedančią taisyklę
						rasta_produkcija = true;
// 10: Baigti
					}
				}
// 11: Baigiame eiti per taisykles
			}
// 12: Jei nė viena taisyklė nerasta,
			if (!rasta_produkcija) {
// 13: Vadinasi pasiekėme aklavietę:
				cout << "Aklavietė (nėra taisyklių).\n";
				tmp = goal;
			}
	}
// 14: Jei tikslas jau buvo ieškotas, vadinasi priėjome ciklą:
	else {
		cout << "Ciklas.\n";
		tmp = goal;
	}
// 15: Einame per tikslui pasiekti reikalingas taisykles
	for (int rule = 0; rule < reikalingos_taisykles.size(); ++rule) {
		int taisykle = reikalingos_taisykles[rule];
		ieskoti_tikslai.push_back(taisykles[taisykle][0]); // pazymime, kad taisykles isvados jau ieskojome
		panaudotos_taisykles.push_back(taisykle); // prie kelio pridedame sia taisykle
		vector <int> rastu_taisykliu_list;
		bool patenkintos_salygos = true;
		if (need_to_print){
			zingsniu_skaicius++;
			print_zingsniai(zingsniu_skaicius, lygis);
			cout << "Tikslas "<< goal <<". ";
		}

		cout << "Randame R" << taisykle+1 << print_taisykle(taisykle) << ". ";
		cout << "Nauji tikslai: ";
		salygos(taisykles[taisykle]);
		cout << ".\n";
		kelias.push_back(taisykle);
		bool ivykdoma = true;
// 16: Einame per taisyklės salygas:
		for (int i = 1; i < taisykles[taisykle].size() && ivykdoma; ++i) {
			char salyga = taisykles[taisykle].at(i);
// 17: Jei taisyklės sąlygos nėra tarp faktų:
			if (std::find(faktai.begin(), faktai.end(),
								 salyga)==faktai.end()) {
				vector <int> kelias_temp;
				patenkintos_salygos = false;
// 18: Tuomet tą salygą pridedame kaip tarpinį tikslą:
				kelias_temp = backward_chaining(salyga, lygis+1);
				if (kelias_temp.size() == 0)
					ivykdoma = false;
				for (int j = 0; j < kelias_temp.size(); ++j) {
					rastu_taisykliu_list.push_back(kelias_temp[j]);
				}
			}
			if (tmp == ' '){
				zingsniu_skaicius++;
				tmp = salyga;
				print_zingsniai(zingsniu_skaicius, lygis+1);
				cout << "Tikslas "<< salyga;
						cout << ". Duotas faktas.\n";
			}
			else {
				if(tmp != salyga){
					tmp = salyga;
					zingsniu_skaicius++;
					print_zingsniai(zingsniu_skaicius, lygis+1);
					cout << "Tikslas "<< salyga;
							cout <<". Duotas faktas.\n";
				}
				else {
					tmp = ' ';
				}
			}
// 19: Baigiame eiti per taisykles
		}
// 20: Jei taisyklės visos sąlygos yra patenkintos:
		if (salygos_patenkintos(taisykle)) {
			char isvada = taisykles[taisykle][0];
			faktai.push_back(isvada);
			rastu_taisykliu_list.push_back(taisykle);
			zingsniu_skaicius++;
			print_zingsniai(zingsniu_skaicius, lygis);
			cout << "Tikslas "<< taisykles[taisykle][0];
			cout << ". Naujai gautas faktas. \n";
			tmp = taisykles[taisykle][0];
// 21: Tuomet grąžiname rastų taisyklių sąrašą (vektorių):
			return rastu_taisykliu_list;
		}
		else {
			if (zingsnis_kartojas == zingsniu_skaicius){
				zingsniu_skaicius++;
				print_zingsniai(zingsniu_skaicius, lygis);
				cout << "Tikslas "<< buves_tikslas;
				cout << ". Išvesti neįmanoma.\n";
				zingsnis_kartojas = 0;
			}
			else {
				zingsnis_kartojas = zingsniu_skaicius;
				buves_tikslas = goal;
			}
			need_to_print = true;
			tmp = taisykles[taisykle][0];
		}
		// taisyklė pašalinama iš panaudotų produkcijų sąrašo:
		vector<int>::iterator position = std::find(panaudotos_taisykles.begin(), panaudotos_taisykles.end(), taisykle);
		if (position != panaudotos_taisykles.end())
			panaudotos_taisykles.erase(position);
		// taisyklės išvada pašalinama iš	ieškotų tikslų sąrašo:
		vector<char>::iterator position2 = std::find(ieskoti_tikslai.begin(), ieskoti_tikslai.end(), taisykles[taisykle][0]);
				if (position2 != ieskoti_tikslai.end())
					ieskoti_tikslai.erase(position2);
// 22: Baigiame eiti per reikalingas taisykles
	}
	if (need_to_print){
		zingsniu_skaicius++;
		print_zingsniai(zingsniu_skaicius, lygis);
		cout << "Tikslas "<< goal <<". ";
		cout << "Išvesti neįmanoma.\n";
	}
	vector <int> empty;
// 23: Gražiname tuščią vektorių:
	return empty;
}

string print_taisykle(int taisykle){
	string pilna_taisykle;
	pilna_taisykle+=": ";
	for (int i = 1; i < taisykles[taisykle].size(); ++i) {
		pilna_taisykle+=taisykles[taisykle][i];
		if (i != taisykles[taisykle].size()-1)
			pilna_taisykle+=", ";
	}
	pilna_taisykle+=" -> ";
	pilna_taisykle+=taisykles[taisykle][0];
	return pilna_taisykle;
}
void print_vector(vector <int> vektorius){
	for (int el = 0; el < vektorius.size(); ++el) {
		cout << vektorius[el] << " ";
	}
	cout << endl;
}
void print_answer(vector <int> vektorius, bool pasiekiamas){
	cout << "\n3) Rezultatas:\n";
	if (pasiekiamas){
		cout << "\n  Tikslas " << tikslas << " pasiekiamas. ";
		cout << "Planas: {";
		int dydis = vektorius.size();
		for (int el = 0; el < dydis; ++el) {
			if (el == dydis-1)
				cout <<"R"<<  vektorius[el]+1;
			else
				cout <<"R"<<  vektorius[el]+1 << ", ";
		}
		cout << "}\n";
		if (vektorius.size() == 0)
			cout << "\nPrograma baigia darbą\n";
	}
	else
		cout << "\n  Tikslas nepasiekiamas. \n";
}
void print_zingsniai(int zingsniai, int lygis){
	cout <<"  " << zingsniai;
	for (int i = 0; i < lygis+1; ++i) {
		cout << "  ";
	}
}
void salygos(string taisykle){
	for (int simb = 1; simb < taisykle.length(); ++simb) {
		if (simb == taisykle.length()-1)
			cout << taisykle[simb];
		else
			cout << taisykle[simb] << ", ";
	}
}
bool salygos_patenkintos(int taisykle){
	for (int salyga = 1; salyga < taisykles[taisykle].size(); ++salyga) {
		if (std::find(faktai.begin(), faktai.end(),
								 taisykles[taisykle][salyga])==faktai.end()){
			return false;
		}
	}
	return true;
}
void print_vector(vector <char> vektorius){
	for (int el = 0; el < vektorius.size(); ++el) {
		cout << vektorius[el] << " ";
	}
	cout << endl;
}

bool ar_tikslas_tarp_faktu(char tikslas_new){//dar nepradejus algoritmo vykdymo tikrina
							//ar tikslas jau egzistuoja tarp faktu
	bool tarp_duotu = false;
	for (int i = 0; i < faktai.size(); i++) {
		if ( faktai[i] == tikslas_new)
			tarp_duotu = true;
	}
	if (tarp_duotu){
		cout << "Duotas faktas.\n";
		vector<int> empty;
		print_answer(empty, true);
	}

	return (tarp_duotu );
}
