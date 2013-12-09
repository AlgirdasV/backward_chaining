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
vector<int> panaudotos_produkcijos;
vector<char> ieskoti_tikslai;
string tmp = "";
vector<int> kelias;



vector<int> backward_chaining(char tikslas_new, int lygis){
	bool rasta_produkcija = false;
	bool aklaviete = false;
	bool ciklas = false;
	vector<int> reikalingos_taisykles;
	for (int i = 0; i < lygis; ++i) {
		cout << "  ";
	}
	cout << "Tikslas "<< tikslas_new <<"; ";
	if (ar_tikslas_tarp_faktu(tikslas_new)){	//galbut tikslas jau egzistuoja tarp faktu
		vector<string> empty;
		exit(0);
	}
	//Ieskome taisykliu, reikalingu tikslui pasiekti:
	if(std::find(ieskoti_tikslai.begin(), ieskoti_tikslai.end(),
								 tikslas_new) == ieskoti_tikslai.end()){ // tikslo nera tarp panaudotu tikslu
			cout <<  "tikslo " <<tikslas_new<< "nera tarp panaudotu isvadu\n";
			rasta_produkcija = false;
			//Einame per visas taisykles
			for (int i = 0; i < taisykles.size() ; i++ ) {
//				cout << "einame per taisykle " << i+1 << "\n";
				if ( std::find(panaudotos_produkcijos.begin(),	//ar produkcija yra tarp panaudotu produkciju
							panaudotos_produkcijos.end(), i)!=panaudotos_produkcijos.end() ){

					cout << "Taisykle R"<< i+1<<" jau panaudota\n";
				}
				else { // Jei taisykle nepanaudota
					//jei taisykles gaminamas faktas yra musu potikslis
					if (taisykles[i][0] == tikslas_new){
//						cout << "Taisykle R"<< i+1<<" nepanaudota\n";
//						cout <<"Randame R"
//							<< i+1 << " produkcijoje\n";
						reikalingos_taisykles.push_back(i);
//						cout <<" reikalingos taisykles vektorius: " ;
//						print_vector(reikalingos_taisykles);
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
		int taisykle = reikalingos_taisykles[rule];
//		cout <<" reikalingos taisykles vektorius veliau cikle: " ;
								//print_vector(reikalingos_taisykles);
//		cout << "einame per reikalinga taisykle "<< taisykle+1 << "\n";
		ieskoti_tikslai.push_back(taisykles[rule][0]); // pazymime, kad taisykles isvados jau ieskojome
		panaudotos_produkcijos.push_back(taisykle); //prie kelio pridedame sia taisykle
		vector <int> rastu_taisykliu_list;
		bool patenkintos_salygos = true;
		cout << "Randame R" << taisykle+1 << "\n";
		cout << "Nauji tikslai: ";
		salygos(taisykles[taisykle]);
		kelias.push_back(taisykle);
//		for (int spaces = 0; spaces < lygis; ++spaces) {
//									cout << "  ";
//								}
		//cout << "tiksle "<< tikslas_new <<" einama per taisykles " << taisykle+1 << " sakygas, taisyke vektoriuje "<<rule <<" \n";
		for (int i = 1; i < taisykles[taisykle].size(); ++i) {
			char salyga = taisykles[taisykle][i];
//			cout <<" tikrinam salyga " << taisykles[taisykle][i] << "\n";
			if (std::find(faktai.begin(), faktai.end(),
								 salyga)==faktai.end()) { // jei taisykles salyga nerasta tarp faktu
//				cout << "salyga "<< salyga<<" nerasta tarp faktu\n";
				vector <int> kelias_temp;
				patenkintos_salygos = false;
//				cout << "bus kvieciamas bc salygai "<<salyga<< "\n";
				kelias_temp = backward_chaining(salyga, lygis+1);
				for (int j = 0; j < kelias_temp.size(); ++j) {
					rastu_taisykliu_list.push_back(kelias_temp[j]);
				}
			}
			if (tmp == ""){
				tmp = salyga;
				cout << "tikslas "<< tikslas_new<<" faktas(duota)\n";
			}
			else {
				if(tmp[0] != salyga){
					tmp = salyga;
					cout << "tikslas "<< tikslas_new<<" faktas(duota)\n";
				}
				else {
					tmp = "";
				}
			}
		}

		if (salygos_patenkintos(taisykle)) {
			char isvada = taisykles[taisykle][0];
			faktai.push_back(isvada);
//			backward_chaining(isvada, lygis);
			rastu_taisykliu_list.push_back(taisykle);
			cout << "Yra naujai gautas faktas. \n";
			tmp = taisykles[taisykle][0];
			return rastu_taisykliu_list;
		}
		else {
			cout << "fakto isvesti neimanoma\n";\
			tmp = taisykles[taisykle][0];
		}
		vector<int>::iterator position = std::find(panaudotos_produkcijos.begin(), panaudotos_produkcijos.end(), taisykle);
		if (position != panaudotos_produkcijos.end()) // == vector.end() means the element was not found
			panaudotos_produkcijos.erase(position);
//		panaudotos_produkcijos;//pasalinti taisykle
		vector<char>::iterator position2 = std::find(ieskoti_tikslai.begin(), ieskoti_tikslai.end(), taisykle);
				if (position2 != ieskoti_tikslai.end()) // == vector.end() means the element was not found
					ieskoti_tikslai.erase(position2);
//		ieskoti_tikslai//pasalinti taisykles isvada;

	}

}

void print_vector(vector <int> vektorius){
	for (int el = 0; el < vektorius.size(); ++el) {
		cout << vektorius[el] << " ";
	}
	cout << endl;
}
void print_answer(vector <string> vektorius){
	for (int el = 0; el < vektorius.size(); ++el) {
		cout <<"R"<<  vektorius[el] << " ";
	}
	cout << endl;
}
void salygos(string taisykle){
	for (int simb = 1; simb < taisykle.length(); ++simb) {
		cout << taisykle[simb] << " ";
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
bool ar_tikslas_tarp_faktu(char tikslas_new){//dar nepradejus algoritmo vykdymo tikrina
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
