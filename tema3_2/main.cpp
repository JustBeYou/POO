#include <memory>
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using namespace std;

class Animal;
class FabricaDeAnimale {
    public:
    static Animal* creeaza(const string& nume);
};

/**
 * Clasa abstracta de baza, implementeaza doar afisarea si citirea generica
 */
class Animal {
    public:
    Animal(const bool areColoanaVertebrala):
        areColoanaVertebrala(areColoanaVertebrala) {}
    virtual string mananca() const = 0;
    virtual pair<string, Animal*> inmultire(bool doarAfiseaza = false) const = 0;
    virtual string miscare() const = 0;
    virtual string comunicare() const = 0; 
    virtual void citeste(istream& intrare) = 0;

    friend ostream& operator<<(ostream& iesire, Animal* animal) {
        iesire << "Ce mananca? " << animal->mananca() << endl;
        iesire << "Cum se misca? " << animal->miscare() << endl;
        iesire << "Cum vorbeste? " << animal->comunicare() << endl;
        iesire << "Cum se inmulteste? " << animal->inmultire(true).first << endl;
        return iesire;
    }

    friend istream& operator>>(istream& intrare, Animal* animal) {
        animal->citeste(intrare);
        return intrare;
    }

    friend istream& operator>>(istream& intrare, Animal** animal) {
        string nume;
        intrare >> nume;
        Animal* nou = FabricaDeAnimale::creeaza(nume);
        intrare >> nou;
        *animal = nou;

        return intrare;
    }

    private:
    bool areColoanaVertebrala;
};

/**
 * Clase pentru increngatura
 */
class Vertebrate: public Animal {
    public:
    Vertebrate(): Animal::Animal(true) {}
};

class Nevertebrate: public Animal {
    public:
    Nevertebrate(): Animal::Animal(false) {}
};

/**
 * Clase pentru clasa
 */
class Pesti: public Vertebrate {
    public:
    Pesti(uint lungime): Vertebrate::Vertebrate(), lungime(lungime) {}
    pair<string, Animal*> inmultire(bool doarAfiseaza = false) const {
        return {"Face icre, adica oua, dar mai mici", nullptr};
    }

    string miscare() const  {
        return "Face vaj, vaj prin apa, da din coada";
    }

    string comunicare() const  {
        return "Glu, glu, glu";
    }

    uint obtineLungime() const {
        return lungime;
    }

    void citeste(istream& intrare) {
        intrare >> lungime;
    };

    protected:
    uint lungime;
};

class Mamifere: public Vertebrate {
    public:
    pair<string, Animal*> inmultire(bool doarAfiseaza = false) const {
        return {"Naste pui vii", nullptr};
    }
};

class Reptile: public Vertebrate {
    public:
    pair<string, Animal*> inmultire(bool doarAfiseaza = false) const {
        return {"Oua mici, oua medii, oua mari", nullptr};
    }

    string comunicare() const  {
        return "Sssssssssssss";
    }
};

class Pasari: public Vertebrate {
    public:
    pair<string, Animal*> inmultire(bool doarAfiseaza = false) const {
        return {"Face oua", nullptr};
    }

    string miscare() const  {
        return "Zboara puiule, zboara!";
    }
};

/**
 * Clase concrete ale unor indivizi
 */
class Ornitorinc: public Mamifere {
    public:
    string comunicare() const {
        return "Rrrrrrrr";
    }

    string miscare() const {
        return "Mai si merge, mai si'noata";
    }

    pair<string, Animal*> inmultire(bool doarAfiseaza = false) const {
        if (doarAfiseaza) return {"Face oua", nullptr};
        return {"Face oua", new Ornitorinc};
    }

    string mananca() const {
        return "Cam ce prinde";
    }

    void citeste(istream& intrare) {};
};

class PesteRapitor: public Pesti {
    public:
    PesteRapitor(): Pesti::Pesti(0) {}
    PesteRapitor(uint lungime): Pesti::Pesti(lungime) {}
    pair<string, Animal*> inmultire(bool doarAfiseaza = false) const {
        auto ret = Pesti::inmultire(doarAfiseaza);
        if (doarAfiseaza) return ret;
        return {ret.first, new PesteRapitor(lungime)};
    }

    string mananca() const {
        return "Pesti mai mici";
    }
};

class Sarpe: public Reptile {
    public:
    string miscare() const  {
        return "Fas, fas, taras pe jos";
    }

    string mananca() const {
        return "Tot ce are carne";
    }

    pair<string, Animal*> inmultire(bool doarAfiseaza = false) const {
        auto ret = Reptile::inmultire(doarAfiseaza);
        if (doarAfiseaza) return ret;
        return {ret.first, new Sarpe};
    }

    void citeste(istream& intrare) {};
};

Animal* FabricaDeAnimale::creeaza(const string& nume) {
    if (nume == "PESTE_RAPITOR") {
        return new PesteRapitor;
    } else if (nume == "ORNITORINC") {
        return new Ornitorinc;
    } else if (nume == "SARPE") {
        return new Sarpe;
    }

    return nullptr;
}

template <typename TipFisa>
class AtlasZoologic {
    public:
    AtlasZoologic& operator+=(const pair<Animal*, TipFisa> fisaNoua) {
        atlas.push_back(fisaNoua);
        return *this;
    }

    const list<pair<Animal*, TipFisa>>& obtineFise() const {
        return atlas;
    }

    private:
    list<pair<Animal*, TipFisa>> atlas;
};

struct FisaStandard {
    string descriere;
};

int main() {
    /* Exemplu de input
3
PESTE_RAPITOR 5 Acesta este un peste rapitor foarte periculos
ORNITORINC Perry Ornitorincul
SARPE Sssss, ssss, toata ziua sssss
    */

    list<Animal*> animale;
    AtlasZoologic<FisaStandard> atlas;
    uint cate;
    cin >> cate;

    for (uint i = 0; i < cate; i++) {
        Animal* nou;
        cin >> &nou;
        animale.push_back(nou);
        string descriere;
        getline(cin, descriere);
        atlas += {nou, {descriere}};
    }
    cout << endl;

    uint pestiRapitoriMaiMariDeUnMetru = 0;
    for (const auto animal: animale) {
        PesteRapitor* posibilPesteRapitor = dynamic_cast<PesteRapitor*>(animal);
        if (posibilPesteRapitor != nullptr) {
            pestiRapitoriMaiMariDeUnMetru += posibilPesteRapitor->obtineLungime() > 1;
        }
    }
    cout << "Pesti rapitori mai mari de un metru: " << pestiRapitoriMaiMariDeUnMetru << endl << endl;

    cout << "Afisare animale" << endl;
    for (const auto& fisa: atlas.obtineFise()) {
        cout << "-----" << endl;
        cout << "Descriere animal: " << fisa.second.descriere << endl;
        cout << fisa.first;
        cout << "-----" << endl << endl;
    }

    for (const auto& animal: animale) {
        delete animal;
    }

    return 0;
}