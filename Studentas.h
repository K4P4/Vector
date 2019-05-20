#ifndef STUDENTAS_H_INCLUDED
#define STUDENTAS_H_INCLUDED

#include "Zmogus.h"

#include <fstream>

using std::endl;
using std::cout;
using std::cin;

class stud: public zmogus{
protected:
    int egz;
    Vector<int> nd;
    double vidurkis;
public:
    stud() : vidurkis(0){}
    stud(std::istream& is);
    double getVidurkis() const { return vidurkis;}
	void pushNd(int pazymys) { nd.push_back(pazymys);}
	void setEgzaminas();
	void apskVidurki();
	void addVidurkis(int pazymys);
    friend bool operator == (const stud &st1, const stud& st2) { return st1.vidurkis == st2.vidurkis;}
    friend bool operator != (const stud &st1, const stud& st2) { return st1.vidurkis != st2.vidurkis;}
    friend std::istream & operator >> (std::istream & in, stud & st);
    friend std::ostream & operator << (std::ostream & out, const stud &st);
    stud (const stud& a);
    stud& operator=(const stud& st);
    stud(stud&& st) : zmogus{st.vardas,st.pavarde}, egz{st.egz}, vidurkis{st.vidurkis},nd{std::move(st.nd)} {};
    friend bool operator < (const stud &st1, const stud &st2) { return st1.vidurkis < st2.vidurkis;}
    friend bool operator > (const stud &st1, const stud &st2) { return st1.vidurkis > st2.vidurkis;}
};


std::istream& operator >> (std::istream & in, stud & st){
        cout << "Pasibaigus namu darbu eilutei iveskite neigiama skaiciu (pvz. -1)" << endl;
        cout << "Iveskite studento varda: ";
        cin >> st.vardas;
        cout << "Pavarde: ";
        cin >> st.pavarde;
        cout << "Namu darbu rezultatus:" << endl;
        st.vidurkis = 0;
        int k=1;
            while(k >= 0){
                cin >> k;
                if(k > 0){
                    st.nd.push_back(k);
                    st.vidurkis += k;
                }
            }
        cout << "Egzamino ivertinima: ";
        st.egz = 0;
        while(st.egz <= 0) cin >> st.egz;
        return in;
}

std::ostream & operator << (std::ostream & out, const stud &st){
        out << "Vardas: " << st.vardas << endl;
        out << "Pavarde: " << st.pavarde << endl;
        out << "Vidurkis: " << st.vidurkis << endl;
        return out;
}

stud& stud::operator=(const stud& st){
	if (&st == this) return *this;
	vardas = st.vardas;
	pavarde = st.pavarde;
	egz = st.egz;
    nd = st.nd;
	vidurkis = st.vidurkis;
	return *this;
}

stud::stud(const stud& st){
	vardas = st.vardas;
	pavarde = st.pavarde;
	egz = st.egz;
    nd = st.nd;
	vidurkis = st.vidurkis;
}

void stud::setEgzaminas(){
    egz = nd[nd.size()-1];
    nd.pop_back();
}

void stud::apskVidurki(){
    vidurkis = vidurkis/nd.size()*0.4 + egz*0.6;
}

void stud::addVidurkis(int pazymys){
    vidurkis += pazymys;
}


#endif // STUDENTAS_H_INCLUDED
