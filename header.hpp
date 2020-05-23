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

struct TermStat
{
  string fichier;
  string mot;
  double statistique;
};
struct resultat
{
    string nomDeFichier;
    double score;
};
/*****************************************************************************/

/*****************************************************************************/
class Extracteur
{
public:
  Extracteur();
  void nettoyer(string & );
  virtual vector<string> extracter(string)=0;
  ~Extracteur();
};

class ExtracteurRequete:public Extracteur
{
public:
  ExtracteurRequete();
  vector<string> extracter(string);
};

class ExtracteurDocument:public Extracteur
{
public:
  ExtracteurDocument();
  vector<string> extracter(string);
};
/*****************************************************************************/
class Analyseur
{
public:
  Analyseur();
  virtual map<string,double> analyserMap(vector<string>&)=0 ;
  virtual vector<TermStat> analyserVector(string,vector<string>&)=0 ;
  ~Analyseur();
};

class AnalyseurOccurence:public Analyseur
{
public:
  AnalyseurOccurence();
  map<string,double>analyserMap(vector<string> &);
  vector< TermStat > analyserVector(string,vector<string>&);
};

class AnalyseurFrequence:public Analyseur
{
public:
  AnalyseurFrequence();
  map<string,double> analyserMap(vector<string>&);
  vector< TermStat > analyserVector(string,vector<string>&);
};
/*****************************************************************************/
class Index
{
public:
  set<string> MotCorpus;
  set<string> MotVide;
  virtual void supprime(string)=0;
  virtual void afficheIndex()=0;
  virtual void afficher()=0;
  virtual void restaurer()=0;
  virtual void sauvgarder()=0;


};
/*****************************************************************************/
class IndexStructureMap:public Index
{
private:
  map<string,map<string,double> >BDIndex;
  int MotstotalIndexe;
public:
  IndexStructureMap();
  void indexer(string,map<string,double>);
  void afficheIndex();
  void sauvgarder();
  void supprime(string);
  void restaurer();
  void afficher();
  map<string,map<string,double> > GetIndex();
  ~IndexStructureMap();
};
/*****************************************************************************/
class IndexStructureVector:public Index
{
private:
  vector<TermStat> BDIndex;
  set<string> documents;
public:
  IndexStructureVector();
  void indexer(vector<TermStat>);
  void supprime(string);
  void restaurer();
  void afficher();
  void afficheIndex();
  void sauvgarder();

  vector<TermStat>GetIndex();
  ~IndexStructureVector();
};
/*****************************************************************************/
class ordonanceur
{
public:
    map<string,double>recherche;
    ordonanceur();
    virtual void ordanancerMap(vector<string> ,IndexStructureMap&)=0;
    virtual void ordanancerVector(vector<string> ,IndexStructureVector&)=0;
    void afficher();
    ~ordonanceur();
};
/*****************************************************************************/
class ordonanceurOccurence:public ordonanceur
{
public:
  ordonanceurOccurence();
  void ordanancerMap(vector<string> ,IndexStructureMap&);
  void ordanancerVector(vector<string> ,IndexStructureVector&);
  //bool compareByStat(resultat &, resultat &);
};
/*****************************************************************************/
//class ordonanceurBinaire
//class ordonanceurTFIDF

#endif // HEADER_HPP_INCLUDED
