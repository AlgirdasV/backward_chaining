#include "algorithm.h" 
#include <iostream>
	using namespace std;
#include <vector>
	using namespace std;
#include <string>
	using namespace std;
#include <algorithm>

vector<char> faktai;
vector<char> nauji_faktai;
vector<char> objektai;
string tikslas;
vector<string> taisykles;
vector<int> panaudotos_produkcijos;
vector<char> ieskoti_tikslai;
string tmp = "";
vector<int> kelias;



vector<string> backward_chaining(char tikslas_new, int lygis){
	bool rasta_produkcija = false;
	bool aklaviete = false;
	bool ciklas = false;
	vector<int> reikalingos_taisykles;
	for (int i = 0; i < lygis; ++i) {
		cout << "  ";
	}
	cout << "Tikslas "<< tikslas_new <<"; ";
	if (ar_tikslas_pasiektas(tikslas_new)){	//galbut tikslas jau egzistuoja tarp faktu
		vector<string> empty;
		return empty;
	}
	if(std::find(ieskoti_tikslai.begin(), ieskoti_tikslai.end(),
								 tikslas_new) == ieskoti_tikslai.end()){ // tikslo nera tarp panaudotu tikslu
			cout <<  "tikslo " <<tikslas_new<< "nera tarp panaudotu isvadu\n";
			rasta_produkcija = false;
			for (int i = 0; i < taisykles.size() && !rasta_produkcija; i++ ) {
				cout << "einame per taisykle " << i+1 << "\n";
				if ( std::find(panaudotos_produkcijos.begin(),	//ar produkcija yra tarp panaudotu produkciju
							panaudotos_produkcijos.end(), i)!=panaudotos_produkcijos.end() ){

					cout << "Taisykle R"<< i+1<<" jau panaudota\n";
				}
				else { // jei produkcija nepanaudota
					if (taisykles[i][0] == tikslas_new){//jei produkcijos gaminamas faktas yra musu potikslis
						cout << "Taisykle R"<< i+1<<" nepanaudota\n";
						cout <<"Randame R"
							<< i+1 << " produkcijoje\n";
						reikalingos_taisykles.push_back(i);
						cout <<" reikalingos taisykles vektorius: " ;
						print_vector(reikalingos_taisykles);
						rasta_produkcija = true;
					}
				}

			}
			if (!rasta_produkcija) {
				cout << "Aklaviete. Tikslo isvesti negalima\n";
				aklaviete = true;
				tmp = tikslas_new;
				//return;
			}
	} else {
		cout << "Ciklas\n";
		tmp = tikslas_new;
		//return;

	}
	for (int rule = reikalingos_taisykles.size()-1; rule >= 0; --rule) {
//		cout <<" reikalingos taisykles vektorius veliau cikle: " ;
								//print_vector(reikalingos_taisykles);
		cout << "einame per reikalinga taisykle "<< reikalingos_taisykles[rule]+1 << "\n";
		ieskoti_tikslai.push_back(taisykles[rule][0]); // pazymime, kad taisykles isvados jau ieskojome
		panaudotos_produkcijos.push_back(reikalingos_taisykles[rule]); //prie kelio pridedame sia taisykle
		vector <string> rastu_taisykliu_list;
		bool patenkintos_salygos = true;
		kelias.push_back(reikalingos_taisykles[rule]);
//		for (int spaces = 0; spaces < lygis; ++spaces) {
//									cout << "  ";
//								}
		//cout << "tiksle "<< tikslas_new <<" einama per taisykles " << reikalingos_taisykles[rule]+1 << " sakygas, taisyke vektoriuje "<<rule <<" \n";
		int rule_index = reikalingos_taisykles[rule];
		for (int salyg = 1; salyg < taisykles[rule_index].size(); ++salyg) {
			cout <<" tikrinam salyga " << taisykles[rule_index][salyg] << "\n";
			if (std::find(faktai.begin(), faktai.end(),
								 taisykles[rule_index][salyg])==faktai.end()) { // jei taisykles salyga nerasta tarp faktu
				cout << "salyga "<< taisykles[rule_index][salyg]<<" nerasta tarp faktu\n";
				vector <string> kelias_temp;
				patenkintos_salygos = false;
				cout << "bus kvieciamas bc salygai "<<taisykles[rule_index][salyg]<< "\n";
				kelias_temp = backward_chaining(taisykles[rule_index][salyg], lygis+1);
				for (int kelio_el = 0; kelio_el < kelias.size(); ++kelio_el) {
					rastu_taisykliu_list.push_back(kelias_temp[kelio_el]);
				}
			}
				if (tmp == ""){
					tmp = taisykles[rule_index][salyg];
					cout << "tikslas "<< tikslas_new<<" faktas(duota)\n";
				}
				else if(tmp[0] != taisykles[rule_index][salyg]){
					tmp = taisykles[rule_index][salyg];
					cout << "tikslas "<< tikslas_new<<" faktas(duota)\n";
				}
				else {
					tmp = "";
				}

			}
		}

		if (salygos_patenkintos(rule_index)) {
			faktai.push_back(taisykles[rule_index][0]);
			backward_chaining(taisykles[rule_index][0], lygis);
			rastu_taisykliu_list.push_back(taisykles[rule_index]);
			cout << "Yra naujai gautas faktas. \n";
			tmp = taisykles[rule_index][0];
			return rastu_taisykliu_list;
		}
		else {
			cout << "fakto isvesti neimanoma\n";\
			tmp = taisykles[rule_index][0];
		}
		vector<int>::iterator position = std::find(panaudotos_produkcijos.begin(), panaudotos_produkcijos.end(), rule_index);
		if (position != panaudotos_produkcijos.end()) // == vector.end() means the element was not found
			panaudotos_produkcijos.erase(position);
//		panaudotos_produkcijos;//pasalinti taisykle
		vector<char>::iterator position2 = std::find(ieskoti_tikslai.begin(), ieskoti_tikslai.end(), rule_index);
				if (position2 != ieskoti_tikslai.end()) // == vector.end() means the element was not found
					ieskoti_tikslai.erase(position2);
//		ieskoti_tikslai//pasalinti taisykles isvada;

	}

	cout << "tikslo isvesti neimanoma\n";
	vector<string> empty;
			return empty;
}

void print_vector(vector <int> vektorius){
	for (int el = 0; el < vektorius.size(); ++el) {
		cout << vektorius[el] << " ";
	}
	cout << endl;
}
bool salygos_patenkintos(int taisykle){
	for (int salyga = 0; salyga < taisykles[taisykle].size(); ++salyga) {
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
void spausdinti_busena(){//spausdina tam tikro zingsnio busena
												 			//t.y. turimus objektus
	cout << "Busena: {";
	for (int i = 0; i < objektai.size(); i++) {
		if (i == objektai.size()-1)
			cout << objektai[i];
		else
			cout << objektai[i] << ", ";
	}
	cout << "}\n";
}
void spausdinti_plana(){//funkcija spausdina rasta plana
	cout << "Planas: {";
	for (int j = panaudotos_produkcijos.size()-1;  j >=0 ; j-- ) {
		if (j == 0)
			cout << "R" << panaudotos_produkcijos[j]+1;
		else
			cout << "R" << panaudotos_produkcijos[j]+1 << ", ";
	}
	cout << "}\n";
}
void vykdyti_produkcija(int nr, bool& ivykdyta){
												//funkcija, kuri ivykdo produkcija, pazymeta
												//numeriu 'nr' ir pazymi ar produkcija buvo ivykdyta
												//veliavoje 'ivykdyta'
	cout << "      Produkcija R"<< nr+1<<" vykdoma; ";
	objektai.push_back(taisykles[nr][0]);
	ivykdyta = true;
	panaudotos_produkcijos.push_back(nr);
}
bool ar_tikslas_pasiektas(char tikslas_new){//dar nepradejus algoritmo vykdymo tikrina
							//ar tikslas jau egzistuoja tarp faktu
	bool tarp_duotu = false;
	bool tarp_nauju = false;
	for (int i = 0; i < faktai.size(); i++) {
		if ( faktai[i] == tikslas_new)
			tarp_duotu = true;
	}
	if (tarp_duotu)
		cout << "Tikslas yra tarp faktu. \n";

	return (tarp_duotu );
}
bool tikslas_pasiekiamas(){//tikrina ar tikslas pasiekiamas
													 	//t.y. ar jis egzistuoja tarp produkciju desiniu pusiu
	bool imanoma = false;
	for (int i = 0; i < taisykles.size(); i++) {
		for (int j = 0; j < taisykles[i].size(); j++) {
			if (tikslas[0] == taisykles[i][0])
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
