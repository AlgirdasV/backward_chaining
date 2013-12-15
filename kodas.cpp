001 vector<char> faktai; // visų faktų vektorius
002 string tikslas; // pradinis tikslas
003 vector<string> taisykles; // visų taisyklių vektorius
004 vector<int> panaudotos_taisykles; // panaudotų taisyklių vektorius
005 vector<char> ieskoti_tikslai; // ieškotų tikslų vektorius
006 char tmp = ' '; // laikinas kintamasis saugoti tikslui tarp rekursijos lygių
007 vector<int> kelias; // vektorius, kuriame kaupiamas atsakymas
008 bool need_to_print = true; // flag'as, kuris žymi ar reikią spausdintį tikslą
009 int zingsniu_skaicius = 0; // žingsnių skaitliukas
010 int zingsnis_kartojas = 0; // flag'as, kuris žymi ar paskutinis spausdintas žingsnis kartojas
011 char buves_tikslas; // laikinas kintamasis, saugoti buvusiam tikslui
012 
013 // Pagrindinė rekursyvi algoritmo funkcija
014 vector<int> backward_chaining(char goal, int lygis){
015 	bool rasta_produkcija = false; // flag'as, žymi ar rasta bent 1  tinkama produkcija
016 	vector<int> reikalingos_taisykles; // vektorius, kuriame bus saugomos tikslui
017 																		 // pasiekti reikalingos taisyklės
018 
019 	zingsniu_skaicius++;
020 	print_zingsniai(zingsniu_skaicius, lygis);
021 	cout << "Tikslas "<< goal <<". ";
022 // 1: Tikriname ar tisklas nėra tarp duotųjų faktų
023 	if (ar_tikslas_tarp_faktu(goal) ){
024 // 2: Jei yra, tuomet išeiti
025 		exit(0);
026 	}
027 	need_to_print = false;
028 // 3: Jei tikslas nėra jau ieškotas
029 	if(std::find(ieskoti_tikslai.begin(), ieskoti_tikslai.end(),
030 								 goal) == ieskoti_tikslai.end()){
031 			rasta_produkcija = false;
032 // 4: Einame per visas taisykles:
033 			for (int i = 0; i < taisykles.size() ; i++ ) {
034 // 5: Jei taisyklė yra nepanaudota:
035 				if ( std::find(panaudotos_taisykles.begin(),	// ar produkcija yra tarp panaudotu produkciju:
036 							panaudotos_taisykles.end(), i)==panaudotos_taisykles.end() ){
037 // 6: Jei taisyklė veda į tikslą
038 					if (taisykles[i][0] == goal)
039 // 7: Tuomet pradėti
040 					{
041 // 8: Pasižymime ją kaip reikalingą:
042 						reikalingos_taisykles.push_back(i);
043 // 9: Pasižymime, kad radome į tikslą vedančią taisyklę
044 						rasta_produkcija = true;
045 // 10: Baigti
046 					}
047 				}
048 // 11: Baigiame eiti per taisykles
049 			}
050 // 12: Jei nė viena taisyklė nerasta,
051 			if (!rasta_produkcija) {
052 // 13: Vadinasi pasiekėme aklavietę:
053 				cout << "Aklavietė (nėra taisyklių).\n";
054 				tmp = goal;
055 			}
056 	}
057 // 14: Jei tikslas jau buvo ieškotas, vadinasi priėjome ciklą:
058 	else {
059 		cout << "Ciklas.\n";
060 		tmp = goal;
061 	}
062 // 15: Einame per tikslui pasiekti reikalingas taisykles
063 	for (int rule = 0; rule < reikalingos_taisykles.size(); ++rule) {
064 		int taisykle = reikalingos_taisykles[rule];
065 		// Pazymime, kad taisykles isvados jau ieskojome
066 		ieskoti_tikslai.push_back(taisykles[taisykle][0]); 
067 		// Prie kelio pridedame sia taisykle
068 		panaudotos_taisykles.push_back(taisykle); 
069 		vector <int> rastu_taisykliu_list;
070 		bool patenkintos_salygos = true;
071 		if (need_to_print){
072 			zingsniu_skaicius++;
073 			print_zingsniai(zingsniu_skaicius, lygis);
074 			cout << "Tikslas "<< goal <<". ";
075 		}
076 		cout << "Randame R" << taisykle+1 << print_taisykle(taisykle) << ". ";
077 		cout << "Nauji tikslai: ";
078 		salygos(taisykles[taisykle]);
079 		cout << ".\n";
080 		kelias.push_back(taisykle);
081 		bool ivykdoma = true;
082 // 16: Einame per taisyklės salygas:
083 		for (int i = 1; i < taisykles[taisykle].size() && ivykdoma; ++i) {
084 			char salyga = taisykles[taisykle].at(i);
085 // 17: Jei taisyklės sąlygos nėra tarp faktų:
086 			if (std::find(faktai.begin(), faktai.end(),
087 								 salyga)==faktai.end()) {
088 				vector <int> kelias_temp;
089 				patenkintos_salygos = false;
090 // 18: Tuomet tą salygą pridedame kaip tarpinį tikslą:
091 				kelias_temp = backward_chaining(salyga, lygis+1);
092 				if (kelias_temp.size() == 0)
093 					ivykdoma = false;
094 				for (int j = 0; j < kelias_temp.size(); ++j) {
095 					rastu_taisykliu_list.push_back(kelias_temp[j]);
096 				}
097 			}
098 			if (tmp == ' '){
099 				zingsniu_skaicius++;
100 				tmp = salyga;
101 				print_zingsniai(zingsniu_skaicius, lygis+1);
102 				cout << "Tikslas "<< salyga;
103 						cout << ". Duotas faktas.\n";
104 			}
105 			else {
106 				if(tmp != salyga){
107 					tmp = salyga;
108 					zingsniu_skaicius++;
109 					print_zingsniai(zingsniu_skaicius, lygis+1);
110 					cout << "Tikslas "<< salyga;
111 							cout <<". Duotas faktas.\n";
112 				}
113 				else {
114 					tmp = ' ';
115 				}
116 			}
117 // 19: Baigiame eiti per taisykles
118 		}
119 // 20: Jei taisyklės visos sąlygos yra patenkintos:
120 		if (salygos_patenkintos(taisykle)) {
121 			char isvada = taisykles[taisykle][0];
122 			faktai.push_back(isvada);
123 			rastu_taisykliu_list.push_back(taisykle);
124 			zingsniu_skaicius++;
125 			print_zingsniai(zingsniu_skaicius, lygis);
126 			cout << "Tikslas "<< taisykles[taisykle][0];
127 			cout << ". Naujai gautas faktas. \n";
128 			tmp = taisykles[taisykle][0];
129 // 21: Tuomet grąžiname rastų taisyklių sąrašą (vektorių):
130 			return rastu_taisykliu_list;
131 		}
132 		else {
133 			if (zingsnis_kartojas == zingsniu_skaicius){
134 				zingsniu_skaicius++;
135 				print_zingsniai(zingsniu_skaicius, lygis);
136 				cout << "Tikslas "<< buves_tikslas;
137 				cout << ". Išvesti neįmanoma.\n";
138 				zingsnis_kartojas = 0;
139 			}
140 			else {
141 				zingsnis_kartojas = zingsniu_skaicius;
142 				buves_tikslas = goal;
143 			}
144 			need_to_print = true;
145 			tmp = taisykles[taisykle][0];
146 		}
147 		// Taisyklė pašalinama iš panaudotų produkcijų sąrašo:
148 		vector<int>::iterator position = std::find(panaudotos_taisykles.begin(), panaudotos_taisykles.end(), taisykle);
149 		if (position != panaudotos_taisykles.end())
150 			panaudotos_taisykles.erase(position);
151 		// Taisyklės išvada pašalinama iš	ieškotų tikslų sąrašo:
152 		vector<char>::iterator position2 = std::find(ieskoti_tikslai.begin(), ieskoti_tikslai.end(), taisykles[taisykle][0]);
153 				if (position2 != ieskoti_tikslai.end())
154 					ieskoti_tikslai.erase(position2);
155 // 22: Baigiame eiti per reikalingas taisykles
156 	}
157 	if (need_to_print){
158 		zingsniu_skaicius++;
159 		print_zingsniai(zingsniu_skaicius, lygis);
160 		cout << "Tikslas "<< goal <<". ";
161 		cout << "Išvesti neįmanoma.\n";
162 	}
163 	vector <int> empty;
164 // 23: Gražiname tuščią vektorių:
165 	return empty;
166 }