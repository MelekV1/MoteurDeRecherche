#include "header.hpp"
/**********************************Flux*******************************************/

ostream& operator<<(ostream& flux ,vector<TermStat>& t)
{
  for (vector<TermStat>::iterator it =t.begin() ; it!=t.end() ; ++it )
  {
    flux<<setw(23)<<it->mot<<" "<<setw(7)<<it->fichier<<" "<<setw(5)<<it->statistique<<endl;
  }
  return flux;
}
/**********************************Flux*******************************************/
ostream& operator<<(ostream& flux ,set<string>& s)
{
 for (set<string>::iterator it =s.begin() ; it!=s.end() ; ++it )
 {
   flux<<*it<<endl;
 }
 return flux;
};
/**********************************Flux*******************************************/
 ostream& operator<<(ostream& flux ,map<string,double>& some)
 {
   for (map<string,double>::iterator it =some.begin() ; it!=some.end() ; ++it )
   {
     flux<<it->first;
     flux<<" ";
     flux<<it->second;
     flux<<endl;
   }
   return flux;
 };
 /**********************************Flux*******************************************/
 ostream& operator<<(ostream& flux ,vector<string>& v)
{
  for (vector<string>::iterator it =v.begin() ; it!=v.end() ; ++it )
  {
    flux<<*it<<endl;
  }
  return flux;
};
/***********************************Extracteur/Lecteur******************************************/
Extracteur::Extracteur(){};
/***********************************Extracteur/Lecteur******************************************/
void Extracteur::nettoyer(string &brute)
{
    set<char> CarVide={'.' ,':',',',';' , '?' , '!','(',')','\n','\t'};
    for (string:: iterator car=brute.begin() ; car!=brute.end() ; ++car )
    {
      set<char>:: iterator fetch = CarVide.find(*car);
      if (fetch !=CarVide.end() )
        {
          brute.erase(car);
          brute.insert(car,' ');

        }
    }
};
/***********************************Extracteur/Lecteur******************************************/
Extracteur::~Extracteur(){};
/***********************************Extracteur/Lecteur******************************************/
ExtracteurRequete::ExtracteurRequete(){};
/***********************************Extracteur/Lecteur******************************************/
vector<string> ExtracteurRequete::extracter(string requete)
{
  vector<string> toutLesMots;
  transform(requete.begin() ,requete.end(),requete.begin(),::tolower);
  nettoyer(requete);
  size_t pos = 0;
  string delimiter = " ";
  string token;

  while ((pos = requete.find(delimiter)) != string::npos)
    {
        token = requete.substr(0, pos);
        toutLesMots.push_back(token);
        requete.erase(0, pos + 1);
        }
    toutLesMots.push_back(requete);
  return toutLesMots;
};
/***********************************Extracteur/Lecteur******************************************/
ExtracteurDocument::ExtracteurDocument(){};
/***********************************Extracteur/Lecteur******************************************/
vector<string> ExtracteurDocument::extracter(string CheminFichier)
{
  vector<string> toutLesMots;
  string mot;
  ifstream Fichier(CheminFichier);
  ofstream redirect("redirect");
  while (getline(Fichier,mot) )
  {
      transform(mot.begin() ,mot.end(),mot.begin(),::tolower);
      nettoyer(mot);
      redirect<<mot<<endl;
  }
  Fichier.close();
  redirect.close();
  ifstream f("redirect");
  while (f>>mot )
  {
    toutLesMots.push_back(mot);
  }
  Fichier.close();
  return toutLesMots;
};
/***********************************Analyseur******************************************/
Analyseur::Analyseur(){};
/***********************************Analyseur******************************************/
Analyseur::~Analyseur(){};
/***********************************Analyseur******************************************/
AnalyseurOccurence::AnalyseurOccurence(){};
map<string,double> AnalyseurOccurence::analyserMap(vector<string> &vecteurDeMots)
{
    map<string,double>occurences;
    for(vector<string>::iterator it=vecteurDeMots.begin() ; it!=vecteurDeMots.end() ; ++it)
    {
      ++occurences[*it];
    }
    return occurences;
};
/***********************************Analyseur******************************************/
vector< TermStat > AnalyseurOccurence::analyserVector(string titre , vector<string>&vecteurDeMots)
{
  map<string,double> facility=analyserMap(vecteurDeMots);
  vector<TermStat>stats;
  for(map<string,double>::iterator doc = facility.begin();doc != facility.end();++doc)
  {
      TermStat ts;
      ts.mot=doc->first;
      ts.fichier=titre;
      ts.statistique=doc->second;
      stats.push_back(ts);
  }
  return stats;
};
/***********************************Analyseur******************************************/
AnalyseurFrequence::AnalyseurFrequence(){};
/***********************************Analyseur******************************************/
map<string,double> AnalyseurFrequence::analyserMap(vector<string> &vecteurDeMots)
{
  map<string,double>occurences;
  double  n=vecteurDeMots.size();
  for(vector<string>::iterator it=vecteurDeMots.begin() ; it!=vecteurDeMots.end() ; ++it)
  {
    occurences[*it]+=1/n;
  }
  return occurences;
};
/***********************************Analyseur******************************************/
vector< TermStat > AnalyseurFrequence::analyserVector(string titre ,vector<string>&vecteurDeMots)
{
  map<string,double> facility=analyserMap(vecteurDeMots);
  vector<TermStat>stats;
  for(map<string,double>::iterator doc = facility.begin();doc != facility.end();++doc)
  {
      TermStat ts;
      ts.mot=doc->first;
      ts.fichier=titre;
      ts.statistique=doc->second;
      stats.push_back(ts);
  }
  return stats;
};
/**********************************Index*******************************************/
IndexStructureVector::IndexStructureVector(){};
/**********************************Index*******************************************/
void IndexStructureVector::indexer(vector<TermStat>v)
{
  for(vector<TermStat>::iterator it =v.begin() ; it!=v.end() ; ++it )
  {
  BDIndex.push_back(*it);
  MotCorpus.emplace(it->mot);
  documents.emplace(it->fichier);
  }
};
/**********************************Index*******************************************/
void IndexStructureVector::supprime(string fichierASupprimer)
{
    for(vector<TermStat>::iterator i = BDIndex.begin(); i != BDIndex.end(); ++i)
    {
        if(fichierASupprimer == i->fichier)
        {
            BDIndex.erase(i);
        }
    }
};
/**********************************Index*******************************************/

void IndexStructureVector::afficheIndex()
{
  cout<<BDIndex;
};
/**********************************Index*******************************************/

void IndexStructureVector::sauvgarder()
{
  ofstream Fichier("index");
  Fichier<<BDIndex;
  Fichier.close();
};
/**********************************Index*******************************************/
void IndexStructureVector::restaurer(){
  ifstream Fichier("index");
  string terms;
  vector<string> pilemot;
  while(Fichier>>terms)
  {
      pilemot.push_back(terms);
  }
  int n=pilemot.size();
  for (int i=0 ; i< n ; i=i+3)
  {
    TermStat ts;
    ts.mot=pilemot[i];
    MotCorpus.emplace(ts.mot);
    ts.fichier=pilemot[i+1];
    documents.emplace(ts.fichier);
    ts.statistique=stof(pilemot[i+2]);
    BDIndex.push_back(ts);
  }
};
/**********************************Index*******************************************/
vector<TermStat> IndexStructureVector::GetIndex()
{
    return BDIndex;
}
/**********************************Index*******************************************/
IndexStructureVector::~IndexStructureVector(){
  sauvgarder();
};
/**********************************Index*******************************************/
void IndexStructureVector:: afficher ()
{
  cout<<"Statistique de l'index \n";
  cout<<documents.size()<<endl;
  cout<<MotCorpus.size()<<endl;
  cout<<BDIndex.size()<<endl;
};
/**********************************Index*******************************************/
IndexStructureMap::IndexStructureMap():MotstotalIndexe(0){};
/**********************************Index*******************************************/
void IndexStructureMap::indexer(string fichier ,map<string,double> metadata)
{
  BDIndex[fichier]=metadata;
  MotstotalIndexe+=metadata.size();
  for(map<string,double>::iterator seek = metadata.begin() ; seek!=metadata.end() ;++seek )
  {
    MotCorpus.emplace(seek->first);
  }
}
/**********************************Index*******************************************/
void IndexStructureMap::afficheIndex(){
    if(BDIndex.size()>0)
    {
        for( map< string , map<string,double> >::iterator elem =BDIndex.begin();elem!=BDIndex.end();++elem)
        {
          for( map<string,double>::iterator elemj=(elem->second).begin() ; elemj!=(elem->second).end() ; ++elemj )
            cout<<setw(15)<<elemj->first<<setw(15)<<elem->first<<"  "<<setw(15)<<elemj->second<<"\n";
        }
    }else{
    cout<<"Index Vide"<<endl;
    }
};
/**********************************Index*******************************************/
void IndexStructureMap::sauvgarder()
{
    ofstream Fichier("index");
    for(map<string,map<string,double> >::iterator elem =BDIndex.begin();elem!=BDIndex.end();++elem)
    {
      for( map<string,double>::iterator elemj=(elem->second).begin();elemj!=(elem->second).end() ; ++elemj)
        Fichier<<setw(7)<<elemj->first<<" "<<setw(23)<<elem->first<<" "<<setw(4)<<elemj->second<<endl;
    }
    Fichier.close();
};
/**********************************Index*******************************************/
void IndexStructureMap::supprime(string iFichier)
{
    map<string,map<string,double> > :: iterator fetch = BDIndex.find(iFichier);
    if( fetch == BDIndex.end() ){
        cout<<"Le fichier n'existe pas dans l'index"<<endl;
    }
    else{
     BDIndex.erase(iFichier);
    }
};
/**********************************Index*******************************************/
void IndexStructureMap::restaurer()
{
  ifstream Fichier("index");
  string terms;
  vector<string> pilemot;
  while(Fichier>>terms)
  {
    pilemot.push_back(terms);
  }
  int compteur=0;
  int n=pilemot.size();
  for (int i=0 ; i< n ; i=i+3)
  {
  BDIndex[pilemot[i+1]][ pilemot[i] ]=stof(pilemot[i+2]);
  MotCorpus.emplace(pilemot[i]);
  ++compteur;
  }
  MotstotalIndexe=compteur;

};
/**********************************Index*******************************************/
  map<string,map<string,double>> IndexStructureMap::GetIndex()
  {
    return BDIndex;
  };

  IndexStructureMap::~IndexStructureMap()
  {
   sauvgarder();
 };
 /**********************************Index*******************************************/
void IndexStructureMap::afficher()
 {
   cout<<"Statistique de l'index \n";
   cout<<BDIndex.size()<<endl;
   cout<<MotCorpus.size()<<endl;
   cout<<MotstotalIndexe<<endl;
 };
/*****************************************************************************/
ordonanceur::ordonanceur(){};
/*****************************************************************************/
void ordonanceur::afficher()
{
    cout<<recherche;
};
/*****************************************************************************/
ordonanceur::~ordonanceur(){};
/*****************************************************************************/
ordonanceurOccurence::ordonanceurOccurence(){};
/*****************************************************************************/
void ordonanceurOccurence::ordanancerMap(vector<string> requete,IndexStructureMap & ism)
{
    map<string,map<string,double>>ix=ism.GetIndex();
    double c;
    for(map<string,map<string,double> >::iterator fichier = ix.begin(); fichier != ix.end(); ++fichier)
    {
        c = 0;
        for(vector<string>::iterator mot = requete.begin(); mot != requete.end(); ++mot)
        {
            map<string,double> ::iterator i = (fichier->second).find (*mot);
            if (i != (fichier->second).end() )
            {
                c += (i->second);
            }
        }
        recherche[fichier->first]=c;
    }
}
/*****************************************************************************/
bool compareByStat(resultat &a, resultat &b)
{
  return a.score < b.score;

}
/*****************************************************************************/
void ordonanceurOccurence::ordanancerVector(vector<string> requete,IndexStructureVector&isv)
{
  vector<resultat> ordre;
  vector<TermStat> stat=isv.GetIndex();
  for (vector<string>::iterator j = requete.begin();j != requete.end();++j)
  {
      //moy = 0;
      for(vector<TermStat>::iterator i = stat.begin();i != stat.end();++i)
      {
          if(i->mot == *j )
          {
            recherche[i->fichier]+=i->statistique;
            }
      }
  }
}
