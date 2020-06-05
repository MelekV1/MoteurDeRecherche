#include "header.hpp"
/**********************************Flux*******************************************/

ostream& operator<<(ostream& flux ,vector<TermStat>& t){
  for (vector<TermStat>::iterator it =t.begin() ; it!=t.end() ; ++it )
  {
    flux<<setw(15)<<it->mot<<" "<<setw(10)<<it->fichier<<" "<<it->statistique<<endl;
  }
  return flux;
}

ostream& operator<<(ostream& flux ,set<string>& s){
 for (set<string>::iterator it =s.begin() ; it!=s.end() ; ++it )
 {
   flux<<*it<<endl;
 }
 return flux;
};

 ostream& operator<<(ostream& flux ,map<string,double>& some){
   for (map<string,double>::iterator it =some.begin() ; it!=some.end() ; ++it )
   {
     flux<<it->first;
     flux<<" ";
     flux<<it->second;
     flux<<endl;
   }
   return flux;
 };

ostream& operator<<(ostream& flux ,vector<string>& v){
  for (vector<string>::iterator it =v.begin() ; it!=v.end() ; ++it )
  {
    flux<<*it<<endl;
  }
  return flux;
};
ostream& operator<<(ostream& flux ,map<string,map<string,double>>& v){

for(map<string,map<string,double> >::iterator elem =v.begin();elem!=v.end();++elem)
    {
      for( map<string,double>::iterator elemj=(elem->second).begin();elemj!=(elem->second).end() ; ++elemj)
        flux<<setw(15)<<elemj->first<<" "<<setw(10)<<elem->first<<" "<<elemj->second<<endl;
    }
    return flux;
};
/***********************************Extracteur/Lecteur******************************************/
Extracteur::Extracteur(){};
Extracteur::~Extracteur(){};

void Extracteur::nettoyer(string &brute){

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

ExtracteurRequete::ExtracteurRequete(){};
ExtracteurDocument::ExtracteurDocument(){};

vector<string> ExtracteurRequete::extracter(string requete){
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

vector<string> ExtracteurDocument::extracter(string CheminFichier){
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
    set<string>:: iterator fetch = MotVide.find(mot);
    if (fetch ==MotVide.end() ){
        toutLesMots.push_back(mot);
    }
  }
  Fichier.close();
  return toutLesMots;
};
/***********************************Analyseur******************************************/
Analyseur::Analyseur(){};
Analyseur::~Analyseur(){};
AnalyseurOccurence::AnalyseurOccurence(){};

map<string,double> AnalyseurOccurence::analyserMap(vector<string> &vecteurDeMots){
    map<string,double>occurences;
    for(vector<string>::iterator itr=vecteurDeMots.begin() ; itr!=vecteurDeMots.end() ; ++itr)
    {
      ++occurences[*itr];
    }
    return occurences;
};

vector< TermStat > AnalyseurOccurence::analyserVector(string titre , vector<string>&vecteurDeMots){
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
AnalyseurFrequence::AnalyseurFrequence(){};

map<string,double> AnalyseurFrequence::analyserMap(vector<string> &vecteurDeMots){
  map<string,double>occurences;
  double  n=vecteurDeMots.size();
  for(vector<string>::iterator it=vecteurDeMots.begin() ; it!=vecteurDeMots.end() ; ++it)
  {
    occurences[*it]+=1/n;
  }
  return occurences;
};

vector< TermStat > AnalyseurFrequence::analyserVector(string titre ,vector<string>&vecteurDeMots){
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
Index::Index(){};
Index::~Index(){};
IndexStructureVector::IndexStructureVector(){};
void IndexStructureVector::indexer(vector<TermStat>v){

  for(vector<TermStat>::iterator it =v.begin() ; it!=v.end() ; ++it )
  {
  BDIndex.push_back(*it);
  MotCorpus.emplace(it->mot);
  documents.emplace(it->fichier);
  }
};
void IndexStructureVector::indexer(vector< vector<TermStat>> files){
  while (!files.empty()){
     indexer(files.back());
     files.pop_back();
  }
}
void IndexStructureVector::supprime(string fichierASupprimer){
    for(vector<TermStat>::iterator i = BDIndex.begin(); i != BDIndex.end(); ++i)
    {
        if(fichierASupprimer == i->fichier)
        {
            BDIndex.erase(i);
        }
    }
};
void IndexStructureVector::afficheIndex(){
  cout<<BDIndex;

};

void IndexStructureVector::sauvgarder(){
  ofstream Fichier("index");
  Fichier<<BDIndex;
  Fichier.close();
};
/**********************************Index*******************************************/
void IndexStructureVector::restaurer(){
  ifstream Fichier("index");
  string terms;
  vector<string> pilemot;
  while(Fichier>>terms){
      pilemot.push_back(terms);
  }
  int n=pilemot.size();
  for (int i=0 ; i< n ; i=i+3){
    TermStat ts;
    ts.mot=pilemot[i];
    MotCorpus.emplace(ts.mot);
    ts.fichier=pilemot[i+1];
    documents.emplace(ts.fichier);
    ts.statistique=stof(pilemot[i+2]);
    BDIndex.push_back(ts);
  }
};
set<string> IndexStructureVector::GetDocs(){
    return documents;
}
vector<TermStat> IndexStructureVector::GetIndex(){
    return BDIndex;
}
IndexStructureVector::~IndexStructureVector(){
  sauvgarder();
};
void IndexStructureVector:: afficher (){
    cout<<"Statistique de l'index \n"<<endl;
    cout<<"___________________________________________________________"<< endl;
    cout<<"Nombre de document textuelles                             :"<<documents.size()<<endl;
    cout<<"Nombre de terme(mots sans repetition) dans le Corpus      :"<<MotCorpus.size()<<endl;
    cout<<"Total nombre de mots dans le corpus                       :"<<BDIndex.size()<<endl;
    cout<<"___________________________________________________________"<< endl;

};
IndexStructureMap::IndexStructureMap():MotstotalIndexe(0){};
void IndexStructureMap::indexer(string fichier ,map<string,double> metadata){
  BDIndex[fichier]=metadata;
  MotstotalIndexe+=metadata.size();
  for(map<string,double>::iterator seek = metadata.begin() ; seek!=metadata.end() ;++seek ){
    MotCorpus.emplace(seek->first);
  }
}
void IndexStructureMap::indexer(vector<FichierDonne> &files){
  while (!files.empty()){
     indexer(files.back().Fichier ,files.back().Donne);
     files.pop_back();
  }
}
void IndexStructureMap::afficheIndex(){
    if(BDIndex.size()>0){
        cout<<BDIndex;
    }else{
    cout<<"Index Vide"<<endl;
    }
};
void IndexStructureMap::sauvgarder(){
    ofstream Fichier("index");
    Fichier<<BDIndex;
    Fichier.close();
};
void IndexStructureMap::supprime(string iFichier){
    map<string,map<string,double> > :: iterator fetch = BDIndex.find(iFichier);
    if( fetch == BDIndex.end() ){
        cout<<"Le fichier n'existe pas dans l'index"<<endl;
    }
    else{
     BDIndex.erase(iFichier);
    }
};
void IndexStructureMap::restaurer(){
  ifstream Fichier("index");
  string terms;
  vector<string> pilemot;
  while(Fichier>>terms){
    pilemot.push_back(terms);
  }
  int compteur=0;
  int n=pilemot.size();
  for (int i=0 ; i< n ; i=i+3){
  BDIndex[pilemot[i+1]][ pilemot[i] ]=stof(pilemot[i+2]);
  MotCorpus.emplace(pilemot[i]);
  ++compteur;
  }
  MotstotalIndexe=compteur;

};
map<string,map<string,double>> IndexStructureMap::GetIndex(){
    return BDIndex;
};

IndexStructureMap::~IndexStructureMap(){
    sauvgarder();
};
void IndexStructureMap::afficher(){
   cout<<"Statistique de l'index \n"<<endl;
   cout<<"____________________________________________________________"<< endl;
   cout<<"Nombre de document textuelles                              :"<<BDIndex.size()<<endl;
   cout<<"Nombre de terme(mots sans repetition) dans le Corpus.      :"<<MotCorpus.size()<<endl;
   cout<<"Total nombre de mots dans le corpus                        :"<<MotstotalIndexe<<endl;
   cout<<"____________________________________________________________"<< endl;

 };
ordonanceur::ordonanceur(){};
void ordonanceur::afficher(){
    cout<<"Document\tScore\n";
    cout<<"____________________________________________________________"<< endl;
    cout<<recherche;
    cout<<"____________________________________________________________"<< endl;
};

/******************************Ordonanceur***********************************************/
void ordonanceur::afficherResultat(int k){

    vector<string>similarite=trier(recherche);
    if (k==0){cout<<similarite;}
    else{
    cout<<"Resultat de recherche \nclassement par ordre de pertinence decroissant               " << endl;
    cout<<"____________________________________________________________"<< endl;
    int limite =similarite.size();
    if ( ( k==0) || ( k >= limite ) )
        cout<<similarite;
    else{
        for (int j=0 ; j<k ;++j){
            cout<<similarite[j]<<endl;
        }
    }
}
};
vector<string> ordonanceur::trier(map<string,double> &similarite){
    multimap<double, string> intermediare;
    map<string, double> :: iterator it;
    for (it=similarite.begin(); it!=similarite.end(); it++){
       intermediare.insert(make_pair(it->second, it->first));
    }

    multimap<double, string> :: reverse_iterator iter;
    vector<string>res;
    for (iter=intermediare.rbegin(); iter!=intermediare.rend(); iter++){
       //if(iter->first!=0){ //<---elimine les zero resultats
           res.push_back(iter->second);
       //}
    }
    return res;
}

ordonanceur::~ordonanceur(){};
ordonanceurOccurence::ordonanceurOccurence(){};
void ordonanceurOccurence::ordanancerMap(vector<string> requete,IndexStructureMap & ism){
    map<string,map<string,double>>ix=ism.GetIndex();
    for(map<string,map<string,double> >::iterator fichier = ix.begin(); fichier != ix.end(); ++fichier){
        recherche[fichier->first]=0;
        for(vector<string>::iterator mot = requete.begin(); mot != requete.end(); ++mot){
            map<string,double> ::iterator i = (fichier->second).find (*mot);
            if (i != (fichier->second).end() ){
                recherche[fichier->first]+=(i->second);
            }else{recherche[fichier->first]+=0;}
        }
    }
}

void ordonanceurOccurence::ordanancerVector(vector<string> requete,IndexStructureVector&isv){
  vector<TermStat> stat=isv.GetIndex();
  for (vector<string>::iterator j = requete.begin();j != requete.end();++j){
      for(vector<TermStat>::iterator i = stat.begin();i != stat.end();++i){
          if(i->mot == *j ){
            recherche[i->fichier]+=i->statistique;
            }else{recherche[i->fichier]+=0;}
      }
  }
}

ordonanceurBinaire::ordonanceurBinaire(){};
void ordonanceurBinaire::ordanancerMap(vector<string> requete,IndexStructureMap & ism){
    map<string,map<string,double>>ix=ism.GetIndex();
    for(map<string,map<string,double> >::iterator fichier = ix.begin(); fichier != ix.end(); ++fichier){
        recherche[fichier->first]=0;
        for(vector<string>::iterator mot = requete.begin(); mot != requete.end(); ++mot){
            map<string,double> ::iterator i = (fichier->second).find (*mot);
            if (i != (fichier->second).end() ){
                recherche[fichier->first] += 1;
            }else{recherche[fichier->first]+=0;}
        }
    }
}
void ordonanceurBinaire::ordanancerVector(vector<string> requete,IndexStructureVector & isv){
    vector<resultat> ordre;
    vector<TermStat> stat=isv.GetIndex();
    set<string>docs=isv.GetDocs();
    for (set<string>::iterator doc=docs.begin();doc!=docs.end();++doc){
        recherche[*doc]=0;
        for (vector<string>::iterator mot = requete.begin(); mot != requete.end(); ++mot){
            vector<TermStat>::iterator fetch = stat.begin();
            bool found=false;
            while(fetch!=stat.end() && found !=true ){
                if(fetch->mot == *mot && fetch->fichier==*doc){
                    found=true;
                    recherche[*doc]+=1;
                }else{recherche[*doc]+=0;}
                ++fetch;
            }
        }
    }
}
ordonanceurTFIDF::ordonanceurTFIDF(){}
void ordonanceurTFIDF::normalization(map <string , map<string ,double>>& VecteurIndex){
    map <string , map<string ,double > >::iterator fich;
    for (fich=VecteurIndex.begin() ; fich != VecteurIndex.end() ; ++fich){
        double sumsqr=0;
        map<string , double > ::iterator mot ;
        for (mot = (fich->second).begin() ; mot != (fich->second).end() ; mot ++){
            sumsqr+=(mot->second)*(mot->second);
        }
        sumsqr=sqrt(sumsqr);
        for (mot = (fich->second).begin() ; mot != (fich->second).end() ; mot ++){
            (VecteurIndex[fich->first])[mot->first]/=sumsqr;
        }
    }
}
void ordonanceurTFIDF::ordanancerMap(vector<string> requete,IndexStructureMap & ism){
    map<string , map<string , double> >VecteurIndex=ism.GetIndex();
    normalization(VecteurIndex);
    map<string,double>idf;
    for(vector<string>::iterator mot = requete.begin(); mot != requete.end(); ++mot){
        int NbDocumentContenantWord=0;
        map<string , map<string , double> >::iterator files;
        for(files=VecteurIndex.begin() ; files != VecteurIndex.end() ; ++files ){
            map<string ,double > ::iterator fetch ;
            fetch=(files->second).find(*mot);
            if ( fetch!=(files->second).end())
                ++NbDocumentContenantWord;
        }
        if(NbDocumentContenantWord==0) NbDocumentContenantWord=1;
        idf[*mot]=log(VecteurIndex.size() / NbDocumentContenantWord );
    }
    for(map<string,map<string,double> >::iterator fichier = VecteurIndex.begin(); fichier != VecteurIndex.end(); ++fichier){
        recherche[fichier->first]=0;
        for(vector<string>::iterator mot = requete.begin(); mot != requete.end(); ++mot){
            map<string,double> ::iterator i = (fichier->second).find (*mot);
            if (i != (fichier->second).end() ){
                recherche[fichier->first]+=VecteurIndex[fichier->first][*mot]*idf[*mot];
            }else{
                recherche[fichier->first]+=0;
            }
        }
    }


}
void ordonanceurTFIDF::ordanancerVector(vector<string> requete,IndexStructureVector & isv){
    vector<resultat> ordre;
    vector<TermStat> stat=isv.GetIndex();
    set<string>docs=isv.GetDocs();
    //pas necessaire de l'implementer
}
/************************************GestionBibilotheque*****************************************/
BibilothequeDeFichiers::BibilothequeDeFichiers(const string chemin):CheminCorpus(chemin){
  bool restore=restaurer();
  if(!restore){
    cout<<"             Bibliotheque initialement vide"<<endl;
   cout<<"____________________________________________________________"<< endl;
  }
}
void BibilothequeDeFichiers::ajouter(string document){Corpus.emplace(document);}
void BibilothequeDeFichiers::ajouter(vector<string> documents){
      for( vector<string>::iterator doc = documents.begin();doc != documents.end();++doc )
        ajouter(*doc);
    }
void BibilothequeDeFichiers::supprimer(string document){
      set<string>::iterator obj ;
      obj=Corpus.find(document);
      if (obj!=Corpus.end()){
        Corpus.erase(obj);
      }
    }
void BibilothequeDeFichiers::supprimer(vector<string> documents){
      for( vector<string>::iterator doc = documents.begin();doc != documents.end();++doc )
        supprimer(*doc);
    }
void BibilothequeDeFichiers::afficher(){
     cout<<"                fiche de bibliotheque"<<endl;
     cout<<"____________________________________________________________"<< endl;
     cout<<"Bibliotheque contient "<<Corpus.size()<<" document"<<endl;
     cout<<"____________________________________________________________"<< endl;
     if (!Corpus.empty()){
        cout<<Corpus;
     }else{
        cout<<"             vide"<<endl;
     }
    cout<<"____________________________________________________________"<< endl;
    }
/************************************GestionBibilotheque*****************************************/
void BibilothequeDeFichiers::sauvegarder(){
      string path=CheminCorpus+"/enregistrement" ;
      ofstream Fichier( path.c_str() );
      set<string> ::iterator fich;
      for(fich = Corpus.begin() ; fich!=Corpus.end(); ++fich)
      {
          Fichier<<*fich<<endl;
      }
      Fichier.close();
    }
/************************************GestionBibilotheque*****************************************/
void BibilothequeDeFichiers::interface(){
  char choix;
  do{
  choix='0';
  cout<< "             Gestion de la bibliotheque              " << endl;
  cout<<"____________________________________________________________"<< endl;
  cout<< "1-ajouter\t2-supprimer" << endl;
  cout<< "3-afficher\t4-quitter" << endl;
  cout<<"____________________________________________________________\n>>";
  cin >> choix;
  switch(choix){
      case '1' :{
          string elt;
          vector<string> documents;
          cout<<"____________________________________________________________"<< endl;
          cout<< "Donnez chaque nom de  documents a ajouter \ninserer stop si vous voulez terminer le processus: \n" << endl;
          cout<<"____________________________________________________________"<< endl;
          while(elt != "stop"){
              getline(cin,elt);
              documents.push_back(elt);
          }
          documents.pop_back();
          documents.erase(documents.begin());
          ajouter(documents);
          break;
          }
      case '2' :{
          vector<string> documents;
          string elt;
          cout<<"____________________________________________________________"<< endl;
          cout << "Donnez chaque nom de  documents a supprimer \ninserer stop si vous voulez terminer le processus: \n" << endl;
          cout<<"____________________________________________________________"<< endl;
          while(elt != "stop"){
              getline(cin,elt);
              documents.push_back(elt);
          }
          documents.pop_back();
          supprimer(documents);
          break;
          };
      case '3' :{
            afficher();
            break;
          };
      case '4' :{
            cout<<"             Quitter le mode gestion bibliotheque             "<<endl;
            cout<<"____________________________________________________________"<< endl;

            break;
          };
    default:{
            cout<<"             Verifier votre clavier                 "<<endl;
            cout<<"____________________________________________________________"<< endl;
            break;
        };
  };
  }while(choix!='4');
}
string BibilothequeDeFichiers::GetPath(){
    return this->CheminCorpus;
}
set<string> BibilothequeDeFichiers::GetFiles(){
      return this->Corpus;
}
bool BibilothequeDeFichiers::restaurer(){
  string refr;
  string path=CheminCorpus+"/enregistrement";
  ifstream exfile(path.c_str());
  if(exfile)
  {
  string titre;
  int valid=0;
  while(getline(exfile,titre))
    {
      ++valid;
      Corpus.emplace(titre);
    }
    if (valid==0) return false;
    return true;
  }else{
  cout<<"              Erreur:Lecture Impossible"<< endl ;
  cout<<"____________________________________________________________"<< endl;
  return false;
  }
}
BibilothequeDeFichiers::~BibilothequeDeFichiers(){
  sauvegarder();
  cout<<"               Bibliotheque sauvegardee                  "<<endl;
  cout<<"____________________________________________________________"<< endl;

};
bool BibilothequeDeFichiers::verif(string fichier){
  ifstream f(fichier.c_str());
  if(!f){
    f.close();
    return false;
  }
  f.close();
  return true;
}
/******************************Moteur de recherche***********************************************/
MoteurDeRecherche::MoteurDeRecherche(Index *i,Analyseur *a,ordonanceur *o,Extracteur *e)
{
    inx=i;
    ordre=o;
    analyse=a;
    lecteur=e;
};
map<string, vector<string> > MoteurDeRecherche::connecterBibliotheque(){
    string library("biblio");
    ExtracteurDocument ed;
    lecteur=&ed;
    map<string, vector<string> >FExtractee;
    BibilothequeDeFichiers BDF(library.c_str());
    BDF.interface();
    set<string> toextract=BDF.GetFiles();
    set<string>::iterator ItFichier;
    for(ItFichier=toextract.begin() ; ItFichier!=toextract.end() ; ++ItFichier){
        string path = "biblio/"+(*ItFichier);
        FExtractee [*ItFichier]=lecteur->extracter(path);
    }
    return FExtractee;
};
void MoteurDeRecherche::SEmain(){
        cout<<"            Connection au base de fichier "<<endl;
        cout<<"____________________________________________________________"<< endl;
        map<string , vector< string > >BaseFichier=connecterBibliotheque();
        cout<<"            la base de fichier est connecte "<<endl;
        cout<<"____________________________________________________________"<< endl;
        char choix1;
        AnalyseurFrequence anf;
        AnalyseurOccurence ano;
        ordonanceurOccurence oc;
        ordonanceurBinaire ob;

        cout<<"             Configurez votre outil de recherche"<<endl;
        cout<<"____________________________________________________________"<< endl;
        do{
        cout<<"1-Standard\n2-TFIDF\n3-Exit"<<endl;
        cout<<"____________________________________________________________\n>>";
        cin>>choix1;
        switch (choix1){
            case '1':{

                cout<<"Choisir le mode d'analyse                                  :\n "<<endl;
                cout<<"1-Frequence d'apparition \t2-Nombre d'occurence"<<endl;
                cout<<"____________________________________________________________\n>>";
                char choix3;
                cin>>choix3;
                switch(choix3){
                case '1':{
                    cout<<"\n                Selection d'analyseur frequence\n"<<endl;
                    analyse = &anf;
                    break;
                }
                case '2':{
                    cout<<"\n.               Selection d'analyseur occurence"<<endl;
                    analyse=&ano;
                    break;
                    }
                default:
                    break;
                }

                char choix2;
                cout<<"Choisir le mode de recherche                               :\n "<<endl;
                cout<<"1-Occurence \t2-Binaire"<<endl;
                cout<<"____________________________________________________________\n>>";
                cin>>choix2;
                switch (choix2){
                case '1':{
                    cout<<"\n.               Selection d'ordonanceur occurence"<<endl;
                    ordre=&oc;
                    break;
                    }
                case'2':{
                    cout<<"\n.               Selection d'ordonanceur binaire"<<endl;
                    ordre=&ob;
                    break;
                    }
                default:
                    break;
                }

                char resp;
                cout<<"Choisir une structure de donnees                           : "<<endl;
                cout<<"1-Index Structure Map \t2-Index Structure Vector"<<endl;
                cout<<"____________________________________________________________\n>>";
                cin>>resp;
                switch (resp){
                case '1' :{
                        IndexStructureMap ism;
                        inx = &ism;
                        vector <FichierDonne >VFD;
                        for(map<string, vector<string> >::iterator iterate =BaseFichier.begin() ; iterate!=BaseFichier.end() ; ++iterate ){
                          map<string ,double > Donnees =analyse->analyserMap(iterate->second);
                          FichierDonne FD;
                          FD.Fichier=iterate->first;
                          FD.Donne=Donnees;
                          VFD.push_back( FD );
                        }
                        ism.indexer(VFD);
                        inx->afficher();
                        cout<<"____________________________________________________________"<< endl;
                        char answer;
                        cout<<"\n                        Recherche"<<endl;
                        cout<<"Voulez vous effectuer une recherche                   (o/n)?\n>>";
                        cin>>answer;
                        while(answer=='o'||answer=='O'||answer=='0'){
                            vector<string>req = interact();
                            ordre->ordanancerMap(req,ism);
                            int k;
                            cout<<"nombre de resultats voulu   :"<<endl;
                            cin>>k;
                            cout<<"                      Resultats"<<endl;
                            ordre->afficherResultat(k);
                            char avancee;
                            cout<<"voire plus de detaille sur le resultat                 (o/n)?\n>>"<<endl;
                            cin>>avancee;
                            if(avancee=='o'){ordre->afficher();};
                            cout<<"____________________________________________________________"<< endl;
                            cout<<"Voulez vous effectuer une recherche                    (o/n)?\n>>";
                            cin>>answer;
                        }
                        break;
                }

                case '2' :{
                        IndexStructureVector isv ;
                        inx=&isv ;
                        vector <vector<TermStat>>VVTD;
                        for(map<string, vector<string> >::iterator iterate =BaseFichier.begin() ; iterate!=BaseFichier.end() ; ++iterate ){
                          vector<TermStat>VTD;
                          VTD=analyse->analyserVector(iterate->first,iterate->second);
                          VVTD.push_back( VTD );
                        }

                        isv.indexer(VVTD);
                        inx->afficher();
                        cout<<"____________________________________________________________"<< endl;
                        char answer;
                        cout<<"\n                        Recherche"<<endl;
                        cout<<"Voulez vous effectuer une recherche                    (o/n)?\n>>";
                        cin>>answer;
                        while(answer=='o'||answer=='O'||answer=='0'){
                            vector<string>req = interact();
                            ordre->ordanancerVector(req,isv);
                            int k;
                            cout<<"nombre de resultats voulu   :"<<endl;
                            cin>>k;
                            cout<<"                      Resultats"<<endl;
                            ordre->afficherResultat(k);
                            char avancee;
                            cout<<"voire plus de detaille sur le resultat                (o/n)?\n>>"<<endl;
                            cin>>avancee;
                            if(avancee=='o'){ordre->afficher();};
                            cout<<"____________________________________________________________"<< endl;
                            cout<<"Voulez vous effectuer une recherche                    (o/n)?\n>>";
                            cin>>answer;
                        }
                        break;
                    }
                default  :
                    break;
                }
                break;
            }
            case '2':{
                cout<<"Mode de recherche   :\nTerm Frequency Inverse Document Frequency---TFIDF\n"<<endl;
                IndexStructureMap ism;
                ordonanceurTFIDF otfidf;
                AnalyseurOccurence ano;
                AnalyseurFrequence anf;
                cout<<"Choisir le mode d'analyse                                  :"<<endl;
                cout<<"1-Frequence d'apparition \t2-Nombre d'occurence"<<endl;
                cout<<"____________________________________________________________\n>>";
                char choix3;
                cin>>choix3;
                switch(choix3){
                case '1':{
                cout<<"                Selection d'analyseur frequence"<<endl;
                cout<<"____________________________________________________________"<< endl;
                analyse = &anf;
                break;
                }

                case '2':{
                cout<<"                 Selection d'analyseur occurence"<<endl;
                cout<<"____________________________________________________________"<< endl;
                analyse=&ano;
                break;
                }
                default:
                    break;
                }
                ordre = &otfidf;
                inx = &ism;
                vector <FichierDonne >VFD;
                for(map<string, vector<string> >::iterator iterate =BaseFichier.begin() ; iterate!=BaseFichier.end() ; ++iterate ){
                      map<string ,double > Donnees =analyse->analyserMap(iterate->second);
                      FichierDonne FD;
                      FD.Fichier=iterate->first;
                      FD.Donne=Donnees;
                      VFD.push_back( FD );
                  }
                ism.indexer(VFD);
                inx->afficher();
                cout<<"____________________________________________________________"<< endl;
                char answer;
                cout<<"\n                        Recherche"<<endl;
                cout<<"Voulez vous effectuer une recherche                    (o/n)?\n>>";
                cin>>answer;
                while(answer=='o'||answer=='O'||answer=='0'){
                    vector<string>req = interact();
                    ordre->ordanancerMap(req,ism);
                    int k;
                    cout<<"nombre de resultats voulu   :"<<endl;
                    cin>>k;
                    cout<<"                      Resultats"<<endl;
                    ordre->afficherResultat(k);
                    char avancee;
                    cout<<"voire plus de detaille sur le resultat             (o/n)?\n>>";
                    cin>>avancee;
                    if(avancee=='o'){ordre->afficher();};
                    cout<<"____________________________________________________________"<< endl;
                    cout<<"Voulez vous effectuer une recherche                    (o/n)?\n>>";
                    cin>>answer;
                }
                break;
                };
            case '3':{
                cout<<"               Quitter le menu de configuration "<<endl;
                cout<<"____________________________________________________________"<< endl;
                break;
                };
            default:{
                cout<<"                     Verifier votre clavier..."<<endl;
                cout<<"____________________________________________________________"<< endl;
                break;
                };
            }
        }while(choix1!='3');
        cout<<"                   Quitter moteur de recherche                "<<endl;
        cout<<"____________________________________________________________"<< endl;
}

vector<string> MoteurDeRecherche::interact(){
      ExtracteurRequete er;
      lecteur = &er;
      string requete;
      cout<<"inserer votre requete                                         \n>>";
      cin.ignore();
      getline(cin,requete);
      vector<string>req =lecteur->extracter(requete);
      return req;
}
MoteurDeRecherche::~MoteurDeRecherche(){};
