#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <typeinfo>
#include <windows.h>
#include <fstream>

using namespace std;
ifstream f;

class haine;

class masina;

class proces
{

    char tip[30];
    float detergent;
    float durata;
public:
    friend void calcare(haine&);
    friend float timpTotal(haine&);
    friend int plasare(haine*,masina&);
    friend void proceseParcurse(haine&);
    proces()
    {
        strcpy(tip,"0");
    }
};

class haine
{
protected:
    char *culoare;
    proces procese[4];
    float greutate;
    float detergentNecesar;
    float timpCalcare;
    bool inMasina;
    int client;  ///Cu aceasta variabila tinem minte clientul caruia ii apartine haina, pentru a o plasa corespunzator in matricea finala
public:
    void setClient(int cl)
    {
        this->client=cl;
    }
    int getClient()
    {
        return this->client;
    }
    int getDetergent()
    {
        return this->detergentNecesar;
    }

    friend int eGol(haine**,int,int );
    friend void calcare(haine&);
    friend float timpTotal(haine&);
    friend void afisare(haine&);
    friend void proceseParcurse(haine&);
    friend int plasare(haine* ha,masina& ma);
    friend istream& operator>>(istream&, haine&);
    friend ostream& operator<<(ostream&, haine&);
    haine& operator=(const haine& ob)
    {
        this->client=ob.client;
        this->culoare=ob.culoare;
        this->detergentNecesar=ob.detergentNecesar;
        this->greutate=ob.greutate;
        for(int i=0;i<4;i++)
        {this->procese[i]=ob.procese[i];}
        this->timpCalcare=ob.timpCalcare;
    }
    virtual void f() {}
};



void afisare(haine &ob)
{
    cout<<endl;
    cout<<"Culoare: "<<ob.culoare<<endl;
    cout<<"Greutate(kg): "<<ob.greutate<<endl<<"Detergent necesar pentru spalare(grame): "<<ob.detergentNecesar<<endl<<"Timp necesar pentru calcare(minute): "<<ob.timpCalcare<<endl;
}

float timpTotal(haine& ob)
{
    float timp=0;
    for(int i=0; i<4; i++)
    {
        if(strcmp(ob.procese[i].tip,"0")!=0)
        {
            timp=timp+ob.procese[i].durata;
        }
    }
    return timp;
}

void proceseParcurse(haine &ob)
{
    cout<<endl<<typeid(ob).name();

    for(int i=0; i<4; i++)
    {
        if(strcmp(ob.procese[i].tip,"0")!=0)
        {
            cout<<endl<<endl;
            cout<<ob.procese[i].tip<<endl<<"Detergent utilizat: "<<ob.procese[i].detergent<<endl<<"Timpul executarii: "<<ob.procese[i].durata<<endl;
        }
    }
}

istream& operator>>(istream& in, haine& ob)
{
    in>>ob.culoare;
    return in;
}

ostream& operator<<(ostream& out, haine& ob)
{
    out<<"Culoare: "<<ob.culoare<<endl<<"Greutate(kg): "<<ob.greutate<<endl<<"Detergent necesar pentru spalare(grame): "<<ob.detergentNecesar<<endl<<"Timp necesar pentru calcare(minute): "<<ob.timpCalcare<<endl;
    return out;
}

class camasa:public haine
{

public:
    camasa(char* culoare);


};


camasa::camasa(char*culoare="Nedefinit")
{
    this->culoare=new char;
    strcpy(this->culoare,culoare);
    this->greutate=0.2;
    this->detergentNecesar=50;
    this->timpCalcare=(120*greutate)/60;
    this->inMasina=false;
}
class rochie:public haine
{

public:
    rochie(char* culoare);


};

rochie::rochie(char*culoare="Nedefinit")
{

    this->culoare=new char;
    strcpy(this->culoare,culoare);
    this->greutate=0.45;
    this->detergentNecesar=50;
    this->timpCalcare=(140*greutate)/60;
    this->inMasina=false;
}
class pantaloni:public haine
{

public:
    pantaloni(char* culoare);


};

pantaloni::pantaloni(char*culoare="Nedefinit")
{

    this->culoare=new char;
    strcpy(this->culoare,culoare);
    this->greutate=0.35;
    if(strcmp(this->culoare,"deschisa")==0)
        this->detergentNecesar=50;
    else
        this->detergentNecesar=100;
    this->timpCalcare=(90*greutate)/60;
    this->inMasina=false;
}

class palton:public haine
{

public:
    palton(char* culoare);
friend istream& operator>>(istream&, palton&);
friend ostream& operator<<(ostream&, palton&);

};
istream& operator>>(istream& in, palton& ob)
{
    in>>ob.culoare;
    return in;
}

ostream& operator<<(ostream& out, palton& ob)
{
    out<<"Culoare: "<<ob.culoare<<endl<<"Greutate(kg): "<<ob.greutate<<endl<<"Detergent necesar pentru spalare(grame): "<<ob.detergentNecesar<<endl<<"Timp necesar pentru calcare(minute): "<<ob.timpCalcare<<endl;
    out<<"Haina este grea";
    return out;
}

palton::palton(char*culoare="Nedefinit")
{

    this->culoare=new char;
    strcpy(this->culoare,culoare);
    this->greutate=1.2;
    this->detergentNecesar=100*greutate;
    this->timpCalcare=0;
    this->inMasina=false;
}

class geaca:public haine
{

public:
    geaca(char* culoare);


};

geaca::geaca(char*culoare="Nedefinit")
{

    this->culoare=new char;
    strcpy(this->culoare,culoare);
    this->greutate=0.8;
    this->detergentNecesar=100*greutate;
    this->timpCalcare=0;
    this->inMasina=false;
}
class costum:public haine
{

public:
    costum(char* culoare);


};

costum::costum(char*culoare="Nedefinit")
{

    this->culoare=new char;
    strcpy(this->culoare,culoare);
    this->greutate=0.95;
    this->detergentNecesar=100*greutate;
    this->timpCalcare=(150*0.6+90*0.35)/60;
    this->inMasina=false;
}

class masina
{
protected:
    float capacitate;
    float spatiuOcupat;
    float timpFunctionare;
    haine **haineIn;
    int nrHaine;
    bool ocupat;
public:
    float getSpatiuOcupat()
    {
        return spatiuOcupat;
    }
    float getCapacitate()
    {
        return capacitate;
    }
    int getNrHaine()
    {
        return nrHaine;
    }

    friend haine* scoatere(masina &ma);
    friend void arataContinut(masina&);
    friend void pornire(masina&,masina&);
    friend void afisare(masina&);
    friend int plasare(haine* ha,masina& ma);
    virtual ~masina() {};
    friend istream& operator>>(istream&, masina&);
    friend ostream& operator<<(ostream&, masina&);
    masina& operator=(const masina& ob)
    {
       this->capacitate=ob.capacitate;
       this->spatiuOcupat=ob.spatiuOcupat;
       this->timpFunctionare=ob.timpFunctionare;
       this->nrHaine=ob.nrHaine;
       for(int i=0;i<nrHaine;i++)
       {
           this->haineIn[i]=ob.haineIn[i];
       }
    }
};

void arataContinut(masina& ob)
{
    // system("cls");
    if (ob.nrHaine==0)
        cout<<"Masina este goala!";

    else
    {
        cout<<"Spatiu ocupat: "<<ob.spatiuOcupat<<" din "<<ob.capacitate<<endl;
        for(int i=0; i<ob.nrHaine; i++)
        {
            cout<<endl;

            cout<<typeid(*ob.haineIn[i]).name();
        }
    }
}

int eGol(haine **a,int m,int n)
{
    for(int i=0; i<m; i++)
    {
        for(int j=0; i<n; j++)
        {
            if(strcmp(a[i][j].culoare,"nedefinit")!=0)
                return 0;
        }
    }
    return 1;
}
void afisare(masina& ob)
{
    cout<<endl;
    cout<<"Capacitate(Kg): "<<ob.capacitate<<endl<<"Timp functionare(min): "<<ob.timpFunctionare<<endl;

}

istream& operator>>(istream& in, masina& ob)
{
    return in;
}
ostream& operator<<(ostream& out, masina& ob)
{
    out<<(haine&)ob;
    out<<"Haina este de categorie grea";
    return out;
}


class spalat:public masina
{
public:
    spalat();
};

spalat::spalat()
{
    haineIn=new haine*[100];
    capacitate=6;
    spatiuOcupat=0;
    nrHaine=0;
    timpFunctionare=200;
    ocupat=false;
}

class spalatGreu:public masina
{
public:
    spalatGreu();
};

spalatGreu::spalatGreu()
{
    haineIn=new haine*[100];
    capacitate=10;
    spatiuOcupat=0;
    nrHaine=0;
    timpFunctionare=230;
    ocupat=false;
}


class stors:public masina
{
public:
    stors();
};

stors::stors()
{
    haineIn=new haine*[100];
    capacitate=6;
    spatiuOcupat=0;
    nrHaine=0;
    timpFunctionare=30;
    ocupat=false;
}

class uscat:public masina
{
    int incapere;
public:
    uscat();
    friend void afisare(uscat&);
};

void afisare(uscat& ob)
{
    cout<<endl;
    cout<<"Capacitate(obiecte): "<<ob.incapere<<endl<<"Timp functionare(min): "<<ob.timpFunctionare<<endl;

}

uscat::uscat()
{
    haineIn=new haine*[100];
    capacitate=20;
    spatiuOcupat=0;
    nrHaine=0;
    timpFunctionare=60;
    ocupat=false;
}

int plasare(haine* ha,masina& ma)    ///Functie care plaseaza un obiect de tip haine* intr-o masina corespunzatoare in functiile de procesele prin care aceasta a trecut deja.
{
    if(strcmp(ha->procese[0].tip,"0")==0)
    {
        ///cout<<"intra";
        if(typeid(*ha)==typeid(camasa)||typeid(*ha)==typeid(rochie)||typeid(*ha)==typeid(pantaloni))
        {
            ///cout<<"intra";
            if(typeid(ma)==typeid(spalat) && ma.capacitate>ha->greutate)
                ///cout<<"intra";
                if(strcmp(ha->culoare,ma.haineIn[0]->culoare)==0 || ma.nrHaine==0)
                {
                    ///cout<<"intra";
                    strcpy(ha->procese[0].tip,"spalare");
                    ha->procese[0].detergent=ha->detergentNecesar;
                    ha->procese[0].durata=ma.timpFunctionare;
                    ma.haineIn[ma.nrHaine]=ha;
                    ma.spatiuOcupat=ma.spatiuOcupat+ha->greutate;
                    ma.nrHaine++;

                    return 1;

                }
        }
        if(typeid(*ha)==typeid(palton)||typeid(*ha)==typeid(geaca)||typeid(*ha)==typeid(costum))
        {
            if(typeid(ma)==typeid(spalatGreu) && ma.capacitate>ha->greutate)
                if(strcmp(ha->culoare,ma.haineIn[0]->culoare)==0 || ma.nrHaine==0)
                {
                    strcpy(ha->procese[0].tip,"spalare");
                    ha->procese[0].detergent=ha->detergentNecesar;
                    ha->procese[0].durata=ma.timpFunctionare;
                    ma.haineIn[ma.nrHaine]=ha;
                    ma.spatiuOcupat=ma.spatiuOcupat+ha->greutate;
                    ma.nrHaine++;

                    return 1;

                }
        }
        if(typeid(*ha)==typeid(costum))
        {
            if(typeid(ma)==typeid(spalat) && ma.capacitate>ha->greutate)
                if(typeid(ma.haineIn[ma.nrHaine])==typeid(costum) || ma.nrHaine==0)
                {
                    strcpy(ha->procese[0].tip,"spalare");
                    ha->procese[0].detergent=ha->detergentNecesar;
                    ha->procese[0].durata=ma.timpFunctionare;
                    ma.haineIn[ma.nrHaine]=ha;
                    ma.spatiuOcupat=ma.spatiuOcupat+ha->greutate;
                    ma.nrHaine++;

                    return 1;
                }
        }
    }
    if(strcmp(ha->procese[0].tip,"0")!=0 && strcmp(ha->procese[1].tip,"0")==0)
    {
        if(typeid(*ha)==typeid(camasa)||typeid(*ha)==typeid(rochie)||typeid(*ha)==typeid(pantaloni)||typeid(*ha)==typeid(costum))
            if(typeid(ma)==typeid(stors) && ma.capacitate>ha->greutate)
            {
                strcpy(ha->procese[1].tip,"stoarcere");
                ha->procese[1].detergent=0;
                ha->procese[1].durata=ma.timpFunctionare;
                ma.haineIn[ma.nrHaine]=ha;
                ma.spatiuOcupat=ma.spatiuOcupat+ha->greutate;
                ma.nrHaine++;

                return 1;
            }
        if(typeid(*ha)==typeid(palton)||typeid(*ha)==typeid(geaca))
            if(typeid(ma)==typeid(uscat) && ma.capacitate>ma.nrHaine)
            {
                strcpy(ha->procese[1].tip,"uscare");
                ha->procese[1].durata=ma.timpFunctionare;
                ha->procese[1].detergent=0;
                ma.haineIn[ma.nrHaine]=ha;
                ma.nrHaine++;

                return 1;
            }
    }
    if(strcmp(ha->procese[1].tip,"0")!=0 && strcmp(ha->procese[2].tip,"0")==0)
    {
        if(typeid(*ha)==typeid(camasa)||typeid(*ha)==typeid(rochie)||typeid(*ha)==typeid(pantaloni)||typeid(*ha)==typeid(costum))
            if(typeid(ma)==typeid(uscat) && ma.capacitate>ma.nrHaine)
            {
                strcpy(ha->procese[2].tip,"uscare");
                ha->procese[2].detergent=0;
                ha->procese[2].durata=ma.timpFunctionare;
                ma.haineIn[ma.nrHaine]=ha;
                ma.nrHaine++;

                return 1;
            }
    }

    return 0;

}

void calcare(haine& ha)
{
    if(strcmp(ha.procese[3].tip,"0")==0)
    {
        strcpy(ha.procese[3].tip,"calcare");
        ha.procese[3].detergent=0;
        ha.procese[3].durata=ha.timpCalcare;
    }
}

void pornire(masina& ma,masina& ma2)
{

    int i;
    for(i=0; i<ma.nrHaine; i++)
    {
        haine* aux=ma.haineIn[i];
     ///   cout<<"\n"<<typeid(*aux).name()<<"\n"; ->afiseaza elementele masinii din care se muta (folosit pentru testare)

        if(plasare(aux,ma2))
        {
            cout<<"\n plasam in masina "<<typeid(ma2).name();               ///Functie care "porneste" masina, scotand toate hainele din ea si predandu-le urmatoarei masini
            cout<<"\n"<<typeid(*aux).name()<<"\n";
            proceseParcurse(*aux);

        }
    }
    ma.spatiuOcupat=0;
    ma.nrHaine=0;


}

haine* scoatere(masina &ma)             ///Functie care scoate ultimul obiect din masina. Folosita pentru a scoate obiectele din masinile de uscat fara a le muta in alta masina.
{
    haine* a;
    if(ma.nrHaine==0)
    {

        a=new camasa("nedefinit");
        return a;
    }
    if(typeid(*(ma.haineIn[ma.nrHaine]))==typeid(palton)||typeid(*(ma.haineIn[ma.nrHaine]))==typeid(geaca))
    {
        a=new haine;
        a=ma.haineIn[ma.nrHaine];
        ma.nrHaine--;
        return a;
    }
    if(typeid(*(ma.haineIn[ma.nrHaine]))==typeid(camasa)||typeid(*(ma.haineIn[ma.nrHaine]))==typeid(rochie)||typeid(*(ma.haineIn[ma.nrHaine]))==typeid(pantaloni)||typeid(*(ma.haineIn[ma.nrHaine]))==typeid(costum))
    {
        a=new haine;
        calcare(*(ma.haineIn[ma.nrHaine]));
        a=ma.haineIn[ma.nrHaine];
        ma.nrHaine--;
        return a;
    }

}

bool doarCifre(char* s)
{
    int i;
    for(i=0;i<strlen(s);i++)
    {
        if (strchr("0123456789",s[i])==0) return false;
    }
    return true;
}

int main()
{
    cout << "Hello world!" << endl;
    /*camasa test("inchisa");
    afisare(test);
    rochie test2("deschisa");
    afisare(test2);
    pantaloni test3("deschisa");
    afisare(test3);
    palton test4("inchisa");
    afisare (test4);
    palton test5("deschisa");
    afisare (test5);
    costum test6("inchisa");    ///ZONA PENTRU TESTE
    afisare (test6);*/
    /*camasa a;
    cin>>a;
    cout<<a;*/
    /*spalat test;
    afisare(test);
    spalatGreu test1;
    afisare(test1);
    stors test2;
    afisare(test2);
    uscat test3;
    afisare (test3);*/
/*    masina **v;
    int n;
    char s[30];
    int i;
    cout<<"Cate masini doriti?:"<<endl;
    cout<<"(Numarul ales trebuie sa fie pozitiv)"<<endl;
    int ok=0;
    do
{
    try{
    cin>>s;
    n=atoi(s);

       if(n<=0){
           throw(n);
       }
       ok=0;
   }

   catch(int n)
   {
       cout<<"NUMARUL trebuie sa fie POZITIV!"<<endl;
       ok=1;
   }


}while(ok);
    v=new masina *[n];
    for(i=0; i<n; i++)                                                  ///Generator de masini
    {                                                                   ///Un multiplu de 4 va genera un rand de masini.
        if(i%4==0)
        {
            v[i]=new spalat();
            v[i]=dynamic_cast<spalat*>(v[i]);
        }
        if(i%4==1)
        {
            v[i]=new spalatGreu();
            v[i]=dynamic_cast<spalatGreu*>(v[i]);
        }
        if(i%4==2)
        {
            v[i]=new stors();
            v[i]=dynamic_cast<stors*>(v[i]);
        }
        if(i%4==3)
        {
            v[i]=new uscat();
            v[i]=dynamic_cast<uscat*>(v[i]);
        }
    }

    system("cls");
    cout<<"Foarte bine! Avem urmatoarele masini: "<<endl<<endl;
    for (i=0; i<n; i++)
    {
        cout<<typeid(*v[i]).name()<<' ';
    }
    Sleep(5000);
    system("cls");
    f.open("fisier.txt");
    int nr;
    char sir[30]; ///Tipul de haine
    char col[30]; ///culoare
    haine ***rufe;
    f>>nr;
    rufe= new haine **[nr];
    int contor[nr]; ///nr de haine pentru fiecare angajat in parte.
    haine ***curat;

    haine *aux;
    for(int i=0; i<nr; i++)
    {
        int elem;
        f>>elem;
        contor[i]=elem;
        rufe[i]=new haine *[elem];

        cout<<"CLIENTUL "<<i+1<<":"<<endl<<endl;
        for(int j=0; j<elem; j++)
        {
            f>>sir;
            f>>col;
            cout<<sir<<" de culoare "<<col<<endl;
            if(strcmp(sir,"camasa")==0)                                   ///Citirea si alocarea unei matrici de tipuri de haine
            {                                                               ///Liniile reprezinta clientii si coloanele hainele acestora.
                rufe[i][j]=new camasa(col);
                rufe[i][j]=dynamic_cast<camasa*>(rufe[i][j]);
                rufe[i][j]->setClient(i);
            }
            if(strcmp(sir,"rochie")==0)
            {
                rufe[i][j]=new rochie(col);
                rufe[i][j]=dynamic_cast<rochie*>(rufe[i][j]);
                rufe[i][j]->setClient(i);
            }
            if(strcmp(sir,"pantaloni")==0)
            {
                rufe[i][j]=new pantaloni(col);
                rufe[i][j]=dynamic_cast<pantaloni*>(rufe[i][j]);
                rufe[i][j]->setClient(i);
            }
            if(strcmp(sir,"costum")==0)
            {
                rufe[i][j]=new costum(col);
                rufe[i][j]=dynamic_cast<costum*>(rufe[i][j]);
                rufe[i][j]->setClient(i);

            }
            if(strcmp(sir,"geaca")==0)
            {
                rufe[i][j]=new geaca(col);
                rufe[i][j]=dynamic_cast<geaca*>(rufe[i][j]);
                rufe[i][j]->setClient(i);
            }
            if(strcmp(sir,"palton")==0)

            {
                rufe[i][j]=new palton(col);
                rufe[i][j]=dynamic_cast<palton*>(rufe[i][j]);
                rufe[i][j]->setClient(i);
            }
        }
    }

    curat= new haine **[nr];
    for(int i=0; i<nr; i++)
    {
        curat[i]=new haine*[contor[i]];
    }

    Sleep(5000);
    system("cls");
    int etapa=1;

    while(!eGol(*rufe,nr,contor[nr]))
    {
        cout<<"ETAPA "<<etapa<<":"<<endl;
        Sleep(1000);
        for(int i=0; i<nr; i++)
        {

            cout<<"CLIENT "<<i+1<<":"<<endl;
            for(int j=0; j<contor[i]; j++)
            {
                for(int k=0; k<n; k++)
                {
                    if(plasare(rufe[i][j],*v[k]))
                    {
                        /*proceseParcurse(*rufe[i][j]);*/                          ///Preia hainele din matricea rufelor murdare formata mai sus.
/*                     cout<<endl<<"Adaugam in masina cu nr "<<k+1<<endl;      ///cat timp aceasta nu este goala efectueaza cicluri de scoatere si
                        rufe[i][j]=new camasa("nedefinit");                     /// depunere in alte masini ale rufelor
                        break;

                    }
                }
                for(int k=0; k<n; k++)
                {

                    ///  cout<<v[k]->getSpatiuOcupat()<<endl;
                    if(v[k]->getSpatiuOcupat()>(v[k]->getCapacitate())/2&&typeid(*v[k])!=typeid(uscat))  ///Muta hainele in masina urmatoare necesara
                    {
                        cout<<endl<<"Pornim masina cu nr "<<k+1<<endl;
                        for(int w=0; w<n; w++)
                        {
                            pornire(*v[k],*v[w]);
                        }
                       // cout<<endl<<"ATAT CU MASINA"<<endl;
                    }
                    if(v[k]->getSpatiuOcupat()>(v[k]->getCapacitate())/2&&typeid(*v[k])==typeid(uscat)) ///Atunci cand scoate haine din masina de uscat le calca si le scoate in matricea finala "Curat"
                    {
                        while((*v[k]).getNrHaine()>0)
                        {
                            aux=scoatere(*v[k]);
                            curat[(*aux).getClient()][contor[(*aux).getClient()]-1]=aux;
                        }

                    }



                }
            }
            etapa++;
            Sleep(5000);
            system("cls");

        }
    }

    for(int i=0; i<nr; i++)
    {
        float detergent=0;
        float timp=0;
        cout<<"Hainele clientului "<<i+1<<":"<<endl;    ///Afisam elementele finale pentru fiecare client, impreuna cu totalul de timp petrecut in masini si de detergentul utilizat
        for(int j=0; j<contor[i]; j++)
        {
            cout<<typeid(*curat[i][j]).name()<<endl;
            proceseParcurse(*curat[i][j]);
            detergent=detergent+((*curat[i][j]).getDetergent());
            timp=timp+timpTotal(*curat[i][j]);
        }
        cout<<"Timp total comanda: "<<timp<<endl<<"Detergent utilizat: "<<detergent;
    }

*/

    camasa test("inchisa");
    palton test2("inchisa");
    palton test1=test2;
    cout<<test<<endl<<endl<<test2<<endl<<endl<<test1;
    return 0;
}







