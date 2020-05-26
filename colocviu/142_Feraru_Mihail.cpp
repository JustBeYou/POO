/* Feraru Mihail 142
gcc version 9.3.1 20200408 (Red Hat 9.3.1-2) (GCC), c++14
Gusatu Marian */

#include <bits/stdc++.h>

using namespace std;

/* Interfata pentru a permite unui obiect sa fie scris/citit dintr-un/intr-un stream */
class Streamable {
    public:
    virtual void read(istream& in) = 0;
    virtual void write(ostream& out) const = 0;
};

istream& operator>> (istream& in, Streamable& obj) {
    obj.read(in);
    return in;
}

ostream& operator<< (ostream& out, const Streamable& obj) {
    obj.write(out);
    return out;
}

istream& operator>> (istream& in, Streamable* obj) {
    obj->read(in);
    return in;
}

ostream& operator<< (ostream& out, const Streamable* obj) {
    obj->write(out);
    return out;
}


class Masca: public Streamable {
    public:
    Masca() = default;
    Masca(const string& tipProtectie): tipProtectie(tipProtectie) {}
    Masca(const Masca& other) {
        tipProtectie = other.tipProtectie;
    }

    string obtineTipProtectie() const;

    void read(istream& in) override;
    void write(ostream& out) const override;

    // pentru a asigura verificarea cu dynamic_cast
    virtual uint versiune() { return 1; }

    private:
    string tipProtectie;
};

string Masca::obtineTipProtectie() const {
    return tipProtectie;
}

void Masca::read(istream& in) 
{
    in >> tipProtectie;
}


void Masca::write(ostream& out) const
{
    out << "Masca " << tipProtectie << endl;
}

class MascaChirurgicala: public Masca {
    public:
    MascaChirurgicala() = default;
    MascaChirurgicala(const string& tipProtectie, const string& culoare, const uint nrPliuri):
        Masca(tipProtectie),
        culoare(culoare),
        nrPliuri(nrPliuri)
    {}
    MascaChirurgicala(const MascaChirurgicala& other): Masca(other) {
        culoare = other.culoare;
        nrPliuri = other.nrPliuri;
    }

    void read(istream& in) override;
    void write(ostream& out) const override;

    uint versiune() { return 2; }

    private:
    string culoare;
    uint nrPliuri;
};

void MascaChirurgicala::read(istream& in)
{
    Masca::read(in);
    in >> culoare >> nrPliuri;
}


void MascaChirurgicala::write(ostream& out) const
{
    Masca::write(out);
    out << " chirurgicala " << culoare << " " << nrPliuri << endl;
}

class MascaPolicarbonat: public Masca {
    public:
    MascaPolicarbonat(): Masca("ffp0") {}
    MascaPolicarbonat(const string& tipPrindere): 
        Masca("ffp0"),
        tipPrindere(tipPrindere)
    {}
    MascaPolicarbonat(const MascaPolicarbonat& other): Masca(other) {
        tipPrindere = other.tipPrindere;
    }

    void read(istream& in) override;
    void write(ostream& out) const override;

    virtual uint versiune() { return 2; }

    private:
    string tipPrindere;
};

void MascaPolicarbonat::read(istream& in) 
{
    in >> tipPrindere;
}


void MascaPolicarbonat::write(ostream& out) const 
{
    Masca::write(out);
    out << " policarbonat " << tipPrindere << endl;
}

class Dezinfectant {
    public:
    Dezinfectant() = default;
    Dezinfectant(const uint64_t nrSpeciiTotal, const uint64_t nrSpeciiUcise, const vector<string>& ingrediente, const vector<string>& suprafete):
        nrSpeciiTotal(nrSpeciiTotal),
        nrSpeciiUcise(nrSpeciiUcise),
        ingrediente(ingrediente),
        suprafete(suprafete)
    {}

Dezinfectant(const Dezinfectant& other) = default;

    double eficienta() const;

    private:
    uint64_t nrSpeciiTotal;
    uint64_t nrSpeciiUcise;
    vector<string> ingrediente;
    vector<string> suprafete;
};

double Dezinfectant::eficienta() const
{
    return static_cast<double>(nrSpeciiUcise) / static_cast<double>(nrSpeciiTotal);
}

class DezinfectantBacterii: public Dezinfectant {
    public:
    DezinfectantBacterii(const uint64_t nrSpeciiUcise, const vector<string>& ingrediente, const vector<string>& suprafete): 
        Dezinfectant(static_cast<uint64_t>(1e9), nrSpeciiUcise, ingrediente, suprafete) {}
};

class DezinfectantVirusuri: public Dezinfectant {
    public:

    DezinfectantVirusuri(const uint64_t nrSpeciiUcise, const vector<string>& ingrediente, const vector<string>& suprafete): 
        Dezinfectant(static_cast<uint64_t>(1.5 * 1e6), nrSpeciiUcise, ingrediente, suprafete) {}
};

class DezinfectantFungi: public Dezinfectant {
    public:
    DezinfectantFungi(const uint64_t nrSpeciiUcise, const vector<string>& ingrediente, const vector<string>& suprafete): 
        Dezinfectant(static_cast<uint64_t>(1e8), nrSpeciiUcise, ingrediente, suprafete) {}
};

class Data {
    public:
    class DataInvalida {};

    Data() = default;
    Data(const Data& other) = default;
    Data(const uint zi, const uint luna, const uint an):
        zi(zi), luna(luna), an(an) {
        
        if (zi > 31 or luna > 12) throw DataInvalida();
    }

    private:
    uint zi;
    uint luna;
    uint an;
};

class Achizitie {
    public:
    Achizitie(const uint zi, const uint luna, const uint an, const string& numeClient):
        numeClient(numeClient),
        data{zi, luna, an}
        {}
    Achizitie() = default;
    Achizitie(const Achizitie& other) = default;

    Achizitie& operator+= (Dezinfectant* dezinfectant);
    Achizitie& operator+= (Masca* masca);
    bool operator== (const Achizitie& rhs) const;
    bool operator< (const Achizitie& rhs) const;
    bool operator> (const Achizitie& rhs) const;

    string nume() const;

    private:
    string numeClient;
    Data data;
    vector<Masca*> masti;
    vector<Dezinfectant*> dezinfectanti;
    double totalPlata;
};

Achizitie& Achizitie::operator+= (Dezinfectant* dezinfectant) 
{
    dezinfectanti.push_back(dezinfectant);

    uint pret = 100;
    if (dezinfectant->eficienta() < 0.9) {
        pret = 10;
    } else if (dezinfectant->eficienta() < 0.95) {
        pret = 20;
    } else if (dezinfectant->eficienta() < 0.975) {
        pret = 30;
    } else if (dezinfectant->eficienta() < 0.99) {
        pret = 40;
    } else if (dezinfectant->eficienta() < 0.9999) {
        pret = 50;
    }
    totalPlata += static_cast<double>(pret);

    return *this;
}

Achizitie& Achizitie::operator+= (Masca* masca) 
{
    masti.push_back(masca);

    uint pret = 0;
    if (dynamic_cast<MascaPolicarbonat*>(masca)) {
        auto mascaPoli = dynamic_cast<MascaPolicarbonat*>(masca);
        pret = 20;
    } else if (dynamic_cast<MascaChirurgicala*>(masca)) {
        auto mascaChir = dynamic_cast<MascaChirurgicala*>(masca);
        if (mascaChir->obtineTipProtectie() == "ffp1") {
            pret = 5;
        } else if (mascaChir->obtineTipProtectie() == "ffp2") {
            pret = 10;
        } else if (mascaChir->obtineTipProtectie() == "ffp3") {
            pret = 15;
        } else {
            throw runtime_error("Tip protectie invalid!");
        }
        
    } else {
        throw runtime_error("Tip masca nerecunoscut la rulare!");
    }
    totalPlata += static_cast<double>(pret);

    return *this;
}

string Achizitie::nume() const {
    return numeClient;
}

bool Achizitie::operator== (const Achizitie& rhs) const {
    return totalPlata == rhs.totalPlata;
}

bool Achizitie::operator< (const Achizitie& rhs) const {
    return totalPlata < rhs.totalPlata;
}

bool Achizitie::operator> (const Achizitie& rhs) const {
    return totalPlata > rhs.totalPlata;
}

void demo() {
    MascaChirurgicala mc1("ffp1", "rosu", 11), mc2("ffp2", "verde brotăcel", 55), mc3(mc1), mc4, mc5;
    mc4 = mc2;
    cin >> mc5;
    cout << mc1 << mc2 << mc4;
    MascaPolicarbonat* mp1=new MascaPolicarbonat(), * mp2=new MascaPolicarbonat();MascaPolicarbonat* mp3 = new MascaPolicarbonat("elastic");
    cin >> mp1 >> mp2;
    cout <<mp1;

    Dezinfectant* d1 = new DezinfectantBacterii(100000000, vector<string>({"sulfatinon-ionici", "sulfati cationici", "parfumuri", "Linalool", "Metilpropanol butilpentil"}), vector<string>({"lemn, sticla, metal, ceramica, marmura"}));
    Dezinfectant* d2 = new DezinfectantVirusuri(50000000, vector<string>({"AlkilDimetilm Benzil Crlorura de amoniu", "parfumuri", "Butilpentil metilpropinal"}), vector<string>({"lemn, sticla, ceramica, marmura"}));
    Dezinfectant* d3 = new DezinfectantFungi(1400000, vector<string>({"Alkil Etil Benzil Crlorura de amoniu", "parfumuri", "Butilpentil metilpropinal"}),vector<string>({"sticla, plastic"}));
    cout << d1->eficienta() << " " << d2->eficienta() << " " << d3->eficienta() << "\n";

    Achizitie* a1 = new Achizitie(26, 5, 2020, "PlushBio SRL");
    *a1 += mp1; //se adauga masca de policarbonat mp1 in lista de masti achizitionate
    *a1 += (&mc1); //se adauga masca chirugicala mc1 in lista
    *a1 += d3; // se adauga dezinfectantu de fungi d3 in lista de dezinfectanti achizitionati
    Achizitie* a2 = new Achizitie(25, 5, 2020, "Gucci");
    *a2 += d1;
    *a2 += d2;
    *a2 += d2;
    Achizitie a3, a4(*a1);
    a3 = *a2;
    if(*a1 < *a2) {
    cout << a1->nume() << " are valoarea facturii mai mica.\n";
    }else if (*a1 == *a2) {
    cout << a1->nume() << " si " << a2->nume() << " au aceasi valoare a facturii.\n";
    } else {
    cout << a2->nume() << " are valoarea facturii mai mica.\n";
    }
}

int main() {
    cout << "--- Demo --- " << endl;
    demo();

    cout << "--- Meniu ---" << endl;

    /* De aici incepe codul scris urat :( */
    vector<Dezinfectant*> stocDezinfectant;
    vector<Masca*> stocMasca;
    vector<Achizitie> achizitii;

    bool running = true;
    while (running) {
        uint optiune;
        cout << "Optiune (conform cerintei, 11 - exit): "; cin >> optiune;
        
        string tip;
        Masca* m;
        Dezinfectant* d;
        std::vector<Dezinfectant *>::iterator best;

        switch (optiune)
        {
        case 1:
            /* N-am avut timp sa fac citirea, dar e acelasi lucru ca la masti */
            cin >> tip;
            if (tip == "virusi") {
                stocDezinfectant.push_back(d);
            } else if (tip == "fungi") {

            } else if (tip == "bacterii") {

            }
            break;
        case 2: 
            cin >> tip;
            if (tip == "chirurgicala") {
                m = new MascaChirurgicala;
                cin >> m;
                stocMasca.push_back(m);
            } else if (tip == "policarbonat") {
                m = new MascaPolicarbonat;
                cin >> m;
                stocMasca.push_back(m);
            }
            break;

        case 3:
            /* din nou, n-am mai avut timp de citire */
        break;
        case 4:
            // daca ar merge citirea ar fi functional
            best = max_element(stocDezinfectant.begin(), stocDezinfectant.end());
            cout << *best << endl;
        break;

        case 5:
            // nu mai am timp, voiam sa elegant veiniturile cu std::reduce :(

        case 11:
            running = false;
            break;
        
        default:
            break;
        }
    }

    return 0;
}