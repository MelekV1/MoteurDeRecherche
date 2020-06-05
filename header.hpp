#ifndef HEADER_HPP_INCLUDED
#define HEADER_HPP_INCLUDED
#include <iostream>
#include <iomanip>
#include <fstream>
#include <iterator>
#include <vector>
#include<map>
#include<set>
#include<cmath>
#include <string>
#include <algorithm>
using namespace std;

struct TermStat//Triplet statistique
{
  string fichier;
  string mot;
  double statistique;
};
struct resultat//structure pour realiser l'ordonancement de la structure de donnes vector
{
    string nomDeFichier;
    double score;
};
struct FichierDonne// structure pour realiser des extraction ,analyse multiple
{
    string Fichier;
    map<string,double> Donne;
};

/*******************************LECTEUR/EXTRACTEUR******************************************/
class Extracteur //la classe est abstraite
{

public:
  set<char> CarVide={'.' ,':',',',';' , '?' , '!','(',')','\n','\t','"'};
  set<string> MotVide={"the","a","with","for","le","la","in","for","to","is","and","et"};
  Extracteur();
  void nettoyer(string & );//suppression des caracteres vides qui n'ont aucun sens et qui affecte le temps de calcul
  virtual vector<string> extracter(string)=0;//methode virtuel pure car il n'y a pas aucun sens de definir le type d'extraction ici
  ~Extracteur();
};

class ExtracteurRequete:public Extracteur
{
public:
  ExtracteurRequete();
  vector<string> extracter(string);//extraction des mots a partir d'une chaine de caractere passee comme parametre
};

class ExtracteurDocument:public Extracteur
{
public:
  ExtracteurDocument();
  vector<string> extracter(string);//extraction des mots d'un document textuelle ou son chemin est passe comme parametre
  friend ostream& operator<<(ostream& flux ,vector<string>& );

};
/********************************Analyseur*********************************************/

class Analyseur //class abstraite
{
public:
  Analyseur();
  virtual map<string,double> analyserMap(vector<string>&)=0 ;
  // methode qui realise une analyse d'un vecteur de mots passe en parametre :
  //cree un dictionnaire pour chaque mots associe une statistique (occurence ou frequence )
  virtual vector<TermStat> analyserVector(string,vector<string>&)=0 ;
  // methode qui realise une analyse d'un vecteur de mots passe en parametre et le nom de fichier:
  //cree un vector qui contient des instances de type TermStat (triplet : mot ,fichier,statistique )
  ~Analyseur();
};

class AnalyseurOccurence:public Analyseur//Derive de la classe Analyseur
{
public:
  AnalyseurOccurence();//la statistique choisit ici est le nombre d'occurence de terme dans le fichier meme
  map<string,double>analyserMap(vector<string> &);
  vector< TermStat > analyserVector(string,vector<string>&);
};

class AnalyseurFrequence:public Analyseur//Derive de la classe Analyseur
{
public:
  AnalyseurFrequence();//la statistique choisit ici est le frequence d'occurence de terme dans le fichier meme
  map<string,double> analyserMap(vector<string>&);
  vector< TermStat > analyserVector(string,vector<string>&);
};
/******************************Index***********************************************/
class Index // classe abstraite Index
{
public:
  Index();
  set<string> MotCorpus;
  virtual void supprime(string)=0;//supprime un fichier
  virtual void afficheIndex()=0;//Afficher les statistiques d'un index
  virtual void afficher()=0;//Affichage en cascade sur le terminal des donnes
  virtual void restaurer()=0;//restaurer l'index a partir de fichier physique index , gardant la persistence
  virtual void sauvgarder()=0;//enregistrer l'index dans le fichier physique index
  ~Index();

};

class IndexStructureMap:public Index//Index ou la structure virtuelle d'index est une map<string,
{
private:
  map<string,map<string,double> >BDIndex;//structure de donnees 1
  int MotstotalIndexe;// le nombre de mots dans le corpus
public:
  IndexStructureMap();
  void indexer(string,map<string,double>);//indexere un seul fichier
  void indexer(vector<FichierDonne>&);//Indexer plusieur fichier
  void afficheIndex();
  void sauvgarder();
  void supprime(string);
  void restaurer();
  void afficher();
  map<string,map<string,double> > GetIndex();
  friend ostream& operator<<(ostream& flux ,map<string,map<string,double>>& v);
  ~IndexStructureMap();
};

class IndexStructureVector:public Index
{
private:
  vector<TermStat> BDIndex;//structure de donnees 2
  set<string> documents;
public:
  IndexStructureVector();
  void indexer(vector< vector<TermStat> > );//indexer plusieur fichier
  void indexer(vector<TermStat> );//indexer un seul fichier
  void supprime(string);
  void restaurer();
  void afficher();
  void afficheIndex();
  void sauvgarder();
  set<string>GetDocs();
  vector<TermStat>GetIndex();
  friend ostream& operator<<(ostream& flux ,vector<TermStat>& t);
  ~IndexStructureVector();
};
/******************************Ordonanceur***********************************************/
class ordonanceur //Classe abstraite
{
public:
    map<string,double>recherche;//structure dictionnaire qui contient pour chaque fichiers le score associe suit a une requete donnee
    ordonanceur();
    virtual void ordanancerMap(vector<string> ,IndexStructureMap&)=0;
    virtual void ordanancerVector(vector<string> ,IndexStructureVector&)=0;
    vector<string>  trier(map<string,double> &);
    void afficher();
    void afficherResultat(int = 0 );
    friend  ostream& operator<<(ostream& flux ,map<string,double>& );
    friend  ostream& operator<<(ostream& flux ,vector<string>& );
    ~ordonanceur();
};
class ordonanceurOccurence:public ordonanceur
{
public:
  ordonanceurOccurence();
  void ordanancerMap(vector<string> ,IndexStructureMap&);
  void ordanancerVector(vector<string> ,IndexStructureVector&);
};

class ordonanceurBinaire:public ordonanceur
{
public:
  ordonanceurBinaire();
  void ordanancerMap(vector<string> ,IndexStructureMap&);
  void ordanancerVector(vector<string> ,IndexStructureVector&);
};
class ordonanceurTFIDF:public ordonanceur
{
public:
    ordonanceurTFIDF();
    void ordanancerMap(vector<string> ,IndexStructureMap&);
    void ordanancerVector(vector<string> ,IndexStructureVector&);
    void normalization(map<string,map<string,double>>&);
};
/************************************GestionBibilotheque*****************************************/
class BibilothequeDeFichiers{
private:
    string CheminCorpus;
    set<string>Corpus;
public:
    BibilothequeDeFichiers(const string);
    void ajouter(const string );
    void ajouter(const vector<string> );
    void supprimer(const string );
    void supprimer(const vector<string> );
    void afficher();
    void sauvegarder();
    bool restaurer();
    void interface();
    set<string>GetFiles();
    string GetPath();
    bool verif(string);
    friend ostream& operator<<(ostream& ,set<string>& );
    ~BibilothequeDeFichiers();
};
/************************************Moteur de Recherche *****************************************/
class MoteurDeRecherche
{
    Extracteur* lecteur;
    Index *inx;
    ordonanceur *ordre;
    Analyseur *analyse;
public:
    MoteurDeRecherche(Index*,Analyseur*,ordonanceur*,Extracteur*);
    map<string, vector<string> > connecterBibliotheque();
    vector<string> interact();
    void SEmain();
    ~MoteurDeRecherche();
};

#endif // HEADER_HPP_INCLUDED
