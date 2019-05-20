#include <iostream>
#include <chrono>
#include <iterator>
#include <algorithm>
#include "Vector.h"
#include "Studentas.h"

using std::cerr;
using namespace std::chrono;

int ivedimas(){
    int k = 0;
    cin >> k;
        if(cin.fail()){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cerr << "Klaida. Ivestas simbolis nera skaitmuo" << endl;
            return 0;
        }
    else return k;
}

void nuskaitymasFaile(int& sk, Vector<stud>& studentai){
    std::ifstream in("sugeneruota100000.txt");
    string eil;
    if(!in.good()){
        cerr << "Klaida. Toks failas neegzistuoja" << endl;
        exit(1);
    }
    int temp;
    sk = 0;
        while(in >> eil){
            stud studentas;
            studentas.setVardas(eil);
            in >> eil;
            studentas.setPavarde(eil);
            while(in.peek()!='\n' && in >> temp){
                if(in.fail() || temp <= 0) {
                    cerr << "Klaida. Patikrinkite faila" << endl;
                    exit(1);
                }
                studentas.pushNd(temp);
                studentas.addVidurkis(temp);
            }
            studentas.setEgzaminas();
            studentas.apskVidurki();
            studentai.push_back(studentas);
            sk++;
        }
        in.close();
}

bool maziau(const stud& esm) {
	return (esm.getVidurkis() < 5.0);
}



int main(){
    Vector<stud> studentai;
    int sk = -1;
    auto start = high_resolution_clock::now();

    nuskaitymasFaile(sk, studentai);

    Vector<stud> vargs;
    Vector<stud> kieti;


    for(int i = 0; i < studentai.size(); i++){
        if(studentai[i].getVidurkis() >= 5.0) kieti.push_back(studentai[i]);
        else vargs.push_back(studentai[i]);
    }


    auto it1 = studentai.begin();
    auto it2 = studentai.end();

    std::partition(it1, it2, maziau);

    studentai.erase(studentai.begin()+10, studentai.end());
    studentai.shrink_to_fit();

    auto ending = high_resolution_clock::now();

    duration<double> diff = ending-start;
    std::cout << sk << " studentu isskirstymas uztruko: " << diff.count() << "s" << endl;
}
