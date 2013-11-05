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

int main( int argc, const char* argv[] )
{
	cout << "Programa pradeda darba\n\n";
	if ( ivesti() ){
		spausdinti();
		backward_chaining();
	}
		
	cout << "Programa baigia darba\n";
}

void remove_comment_and_spaces(string& line){
	
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

void remove_carriage_return(std::string& line)
{
    if (*line.rbegin() == '\r')
    {
        line.erase(line.length() - 1);
    }
}

void spausdinti(){
	cout << "1)Duomenys is failo:" << endl;
	int ilgis = 0;
	for (int i = 0; i < taisykles.size(); i++){
		//atskirti_taisykle(taisykles[i]);
	}
	for (int i = 0; i < taisykles.size(); i++){
		if ( ilgis < taisykles[i].length() )
			ilgis = taisykles[i].length();
	}
	cout << "\n  Taisykles \n";
	//cout << "max ilgis" << ilgis<< endl;
	for (int i = 0; i < taisykles.size(); i++){
		cout <<"    R"<<i+1<<": ";
		for (int j = 1; j < taisykles[i].length(); j++){
			//cout << "Jos ilgis " << taisykles[i].length() << endl;
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

bool ivesti(){
	string fileName;
	cout << "iveskite duomenu failo pavadinima: " << endl;//asks user to input filename
	cin >> fileName; //inputs user input into fileName
	ifstream duomenys (fileName.c_str());
	string line;
	if (duomenys.is_open())
  	{
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