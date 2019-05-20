#ifndef ZMOGUS_H_INCLUDED
#define ZMOGUS_H_INCLUDED

#include <string>
using std::string;

class zmogus{
protected:
    string vardas;
    string pavarde;
public:
    zmogus(string defv = "", string defp = ""): vardas{defv}, pavarde{defp}{}
    virtual void setEgzaminas() = 0;
    void setVardas(string vard) { vardas = vard;}
	void setPavarde(string pav) { pavarde = pav;}
    inline string getVardas() const { return vardas;}
    inline string getPavarde() const { return pavarde;}
};

#endif // ZMOGUS_H_INCLUDED
