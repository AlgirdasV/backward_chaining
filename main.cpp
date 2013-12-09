#include <iostream>
	using namespace std;
#include <vector>
	using namespace std;
#include <string>
	using namespace std;
#include <iomanip>
	using namespace std;
#include <fstream>
	using namespace std;
#include "algorithm.h" 

void spausdinti();
bool ivesti();
void remove_carriage_return(string&);
void remove_comment_and_spaces(string& line);

int main( int argc, const char* argv[] )	//pagrindine funkcija, 	
														//nuskaito ir atspausdina failo duomenis,														
{														//bei paleidzia tiesioginio isvedimo algoritma.
	cout << "\nPrograma pradeda darba\n\n";
	vector<string> atsakymas;
	if ( ivesti() ){
		spausdinti();
		atsakymas = backward_chaining(tikslas[0], 0);
	}
	print_answer(atsakymas);
	cout << "\nPrograma baigia darba\n";
}

void remove_comment_and_spaces(string& line){//funkcija, salinanti 
										 				//komentarus ir tarpus is eilutes
	string delimiters = " \t";
	size_t current;
	size_t next = -1;
	string new_line = "";
	
	do
	{
		current = next + 1;
		next = line.find_first_of( delimiters, current );
		new_line.append( line.substr( current, next - current ) );//<< endl;
	}
	while (next != string::npos);

	size_t pos = 0;
	if ( (pos = new_line.find_first_of("//") ) != string::npos){
		new_line = new_line.substr( 0, pos );
	}
	line = new_line;
}

void remove_carriage_return(std::string& line){//funkcija, salinanti "\r" simboli is eilutes
    if (*line.rbegin() == '\r')
    {
        line.erase(line.length() - 1);
    }
}

void spausdinti(){		//funkcija, spausdinanti duomenis, nuskaitytus is failo
	cout << "\n1)Duomenys is failo:" << endl;
	int ilgis = 0;

	for (int i = 0; i < taisykles.size(); i++){
		if ( ilgis < taisykles[i].length() )
			ilgis = taisykles[i].length();
	}
	cout << "\n  Taisykles \n";
	for (int i = 0; i < taisykles.size(); i++){
		cout <<"    R"<<i+1<<": ";
		for (int j = 1; j < taisykles[i].length(); j++){
			if ( (j==taisykles[i].length()-1) && (taisykles[i][j]!=' ') ){
				cout << taisykles[i][j] << " ";
				if ( ilgis !=taisykles[i].length() ){
					for (int k = 0; k < ilgis-taisykles[i].length(); k++) {
						cout << "   ";
					}
				}
			}
			else if(taisykles[i][j]!=' ') {
				cout <<taisykles[i][j];
				cout <<", ";
			}
		}
		cout << "-> " << taisykles[i][0];
		cout << endl;
	} 
	cout << "\n  Pradiniai faktai \n";
	cout << "    ";
	for (int i = 0; i < faktai.size(); i++){
		if (i==faktai.size()-1)
			cout << faktai[i];
		else 
			cout << faktai[i] << ", ";
	} 
	cout << "\n\n  Tikslas \n" << "    " << tikslas << "\n\n";
}

bool ivesti(){		//funkcija, kurios pagalba nuskaitomi duomenys is failo
	string fileName;
	cout << "iveskite duomenu failo pavadinima: " << endl;//asks user to input filename
	cin >> fileName; //inputs user input into fileName
	ifstream duomenys (fileName.c_str());
	string line;
	if (duomenys.is_open())
  	{
  		getline( duomenys, line );
  		remove_carriage_return(line);
  		remove_comment_and_spaces(line);
  		if (line.compare("1)Taisyklės") != 0){
  			cout << "Faile nerasta zymes 1) Taisyklės. ";
  			return false;
  		}
  		bool baigta = false;
		while ( !baigta ){
			getline( duomenys, line );
			remove_carriage_return(line);
			remove_comment_and_spaces(line);	
			if ( !line.empty() )
				taisykles.push_back(line);
			else
				baigta = true;
		}
		//cout << "Faktas \n";
		getline( duomenys, line );
  		remove_carriage_return(line);
  		remove_comment_and_spaces(line);
  		if (line.compare("2)Faktai") != 0){
  			cout << "Faile nerasta zymes 2) Faktai. ";
  			return false;
  		}
		baigta = false;
		while ( !baigta ){
			getline( duomenys, line );
			remove_carriage_return(line);
			remove_comment_and_spaces(line);
			if (!line.empty())
				for ( int i = 0; i < line.length(); i++) {
					faktai.push_back(line[i]);

				}
			else
				baigta = true;
		}
		//cout << "Tikslas \n";
		getline( duomenys, line );
  		remove_carriage_return(line);
  		remove_comment_and_spaces(line);
  		if (line.compare("3)Tikslas") != 0){
  			cout << "Faile nerasta zymes 3) Tikslas. ";
  			return false;
  		}
		getline( duomenys, tikslas);
		remove_carriage_return(tikslas);
		remove_comment_and_spaces(tikslas);
	    duomenys.close();
	    return true;
 	}
 	else {
 		cout << "Toks failas neegzistuoja. \n";
 		return false;
 	}
}
