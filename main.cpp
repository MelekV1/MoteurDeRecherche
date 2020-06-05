#include "header.hpp"
#include <chrono>



int main()
{

/*******************Gestion de la Bibliotheque de fichiers***********************/
/*
BibilothequeDeFichiers BDF("biblio");//<-----------Instance bibliotheque est creee
//BDF.interface();//interaction utilisateur gestion bibliotheque
BDF.restaurer();//restaurer si il y a des fichiers dans le chemin bibliotheque


BDF.ajouter("Alphabet.txt");              //ajouter les noms de fichiers
BDF.ajouter("Audi AI.txt");
BDF.ajouter("bitcoin blockchain.txt");
BDF.ajouter("covid-19.txt");
BDF.ajouter("seat.txt");
BDF.ajouter("Tesla Motors, Inc.txt");
BDF.ajouter("Bayerische Motoren Werke.txt");
BDF.ajouter("HP Inc.txt");
BDF.ajouter("MSI.txt");
BDF.ajouter("sony.txt");

BDF.afficher();                         //Affichage de la bibliotheque

//BDF.supprimer("xxxx");//<--------------supprimer ce fichier

//le destructeur de la classe bibliotheque lance la methode sauvegarde
//les fichiers sont enregistrer dans un fichiers dans le corpus nomme enregistrement

*/
/*******************Moteur de recherche***********************/

Analyseur *anz=NULL;
ordonanceur *ord=NULL;
Index *inx=NULL;
Extracteur *ext=NULL;

MoteurDeRecherche MDR(inx,anz,ord,ext);

MDR.SEmain();

/*******************Lecture et extraction***********************/
/*
Extracteur *e ;

ExtracteurRequete Erq;
ExtracteurDocument Erd;

e=&Erq;
//choisire une phrase qui a une relation avec ce document text ""origin.txt""
vector<string> req =e->extracter("In 49 BCE, Bayek, a Medjay charged with protecting the Siwa Oasis");//extraction de la requete
                                                                                                    //cette requete est prise de origin.txt
                                                                                                    //covid-19 contient le terme 49
                                                                                                    //Attack on titans contient le terme protecting
                                                                                                    //odyssey contient le terme BCE Bayek

e=&Erd;
//extraction de 20 fichiers textes

vector<string> doc1=e->extracter("biblio/odyssey.txt");//3998 mots
vector<string> doc2=e->extracter("biblio/valhalla.txt");//2734 mots
vector<string> doc3=e->extracter("biblio/origin.txt");//3539 mots
vector<string> doc4=e->extracter("biblio/blackflag.txt");//5081 mots
vector<string> doc5=e->extracter("biblio/syndicate.txt");//4330 mots
vector<string> doc6=e->extracter("biblio/deep learning.txt");//6939 mots
vector<string> doc7=e->extracter("biblio/higher ground.txt");
vector<string> doc8=e->extracter("biblio/nba.txt");
vector<string> doc9=e->extracter("biblio/Attack on titans.txt");
vector<string> doc10=e->extracter("biblio/MSI.txt");
vector<string> doc11=e->extracter("biblio/dark.txt");
vector<string> doc12=e->extracter("biblio/sony.txt");
vector<string> doc13=e->extracter("biblio/seat.txt");
vector<string> doc14=e->extracter("biblio/Tesla Motors, Inc.txt");
vector<string> doc15=e->extracter("biblio/Audi AI.txt");
vector<string> doc16=e->extracter("biblio/bitcoin blockchain.txt");
vector<string> doc17=e->extracter("biblio/covid-19.txt");
vector<string> doc18=e->extracter("biblio/Alhpabet.txt");
vector<string> doc19=e->extracter("biblio/Bayerische Motoren Werke.txt");
vector<string> doc20=e->extracter("biblio/HP Inc.txt");
*/
/*******************TEST STRUCTURE MAP *************************/
/*
Analyseur *An   ;ordonanceur *od    ;Index *inx;
IndexStructureMap ism       ;AnalyseurOccurence ano     ;ordonanceurBinaire ordo;
An=&ano     ;od=&ordo    ;inx=&ism;

map<string,double>analyse1 =An->analyserMap(doc1);
map<string,double>analyse2 =An->analyserMap(doc2);
map<string,double>analyse3 =An->analyserMap(doc3);
map<string,double>analyse4 =An->analyserMap(doc4);
map<string,double>analyse5 =An->analyserMap(doc5);
map<string,double>analyse6 =An->analyserMap(doc6);
map<string,double>analyse7 =An->analyserMap(doc7);
map<string,double>analyse8 =An->analyserMap(doc8);
map<string,double>analyse9 =An->analyserMap(doc9);
map<string,double>analyse10 =An->analyserMap(doc10);
map<string,double>analyse11 =An->analyserMap(doc11);
map<string,double>analyse12 =An->analyserMap(doc12);
map<string,double>analyse13 =An->analyserMap(doc13);
map<string,double>analyse14 =An->analyserMap(doc14);
map<string,double>analyse15 =An->analyserMap(doc15);
map<string,double>analyse16 =An->analyserMap(doc16);
map<string,double>analyse17 =An->analyserMap(doc17);
map<string,double>analyse18 =An->analyserMap(doc18);
map<string,double>analyse19 =An->analyserMap(doc19);
map<string,double>analyse20 =An->analyserMap(doc20);


ism.indexer("odyssey.txt",analyse1);
ism.indexer("valhalla.txt",analyse2);
ism.indexer("origin.txt",analyse3);
ism.indexer("blackflag.txt",analyse4);
ism.indexer("syndicate.txt",analyse5);
ism.indexer("deep learning.txt",analyse6);

ism.indexer("higher ground.txt",analyse7);
ism.indexer("nba.txt",analyse8);
ism.indexer("Attack on titans.txt",analyse9);
ism.indexer("MSI.txt",analyse10);
ism.indexer("dark.txt",analyse11);
ism.indexer("sony.txt",analyse12);
ism.indexer("seat.txt",analyse13);
ism.indexer("Tesla Motors ,Inc.txt",analyse14);
ism.indexer("Audi AI.txt",analyse15);
ism.indexer("bitcoin blockchain.txt",analyse16);
ism.indexer("covid-19.txt",analyse17);
ism.indexer("Alphabet.txt",analyse18);
ism.indexer("Bayerische Motoren Werke.txt",analyse19);
ism.indexer("HP Inc.txt",analyse20);
//ism.supprime("blackflag.txt");//Supprimer un fichier de l'index

inx->afficher();//affichers des statistiques sur l'index


od->ordanancerMap(req ,ism);

od->afficherResultat(3);//affichage les  premieres nombre de titres de fichiers suivant l'ordre de pertinence
                        //le nombre de titres est un parametre
od->afficher();//Affichage avanceé ,le score est inclus
*/
/*******************TEST STRUCTURE Vector***********************/
/*
Analyseur *An   ;ordonanceur *od    ;Index *inx;
IndexStructureVector isv;
AnalyseurOccurence ano;
ordonanceurBinaire ordo;
An=&ano     ;od=&ordo    ;inx=&isv;



vector< TermStat >analyse1 =An->analyserVector("odyssey.txt",doc1);vector< TermStat >analyse2 =An->analyserVector("valhalla.txt",doc2);vector< TermStat >analyse3 =An->analyserVector("origin.txt",doc3);
vector< TermStat >analyse4 =An->analyserVector("blackflage.txt",doc4);vector< TermStat >analyse5 =An->analyserVector("syndicate.txt",doc5);vector< TermStat >analyse6 =An->analyserVector("deep learning.txt",doc6);
vector< TermStat >analyse7 =An->analyserVector("higher ground.txt",doc7);vector< TermStat >analyse8 =An->analyserVector("nba.txt",doc8);vector< TermStat >analyse9 =An->analyserVector("Attack on titans.txt",doc9);
vector< TermStat >analyse10 =An->analyserVector("MSI.txt",doc10);vector< TermStat >analyse11 =An->analyserVector("dark.txt",doc11);vector< TermStat >analyse12 =An->analyserVector("sony.txt",doc12);
vector< TermStat >analyse13 =An->analyserVector("seat.txt",doc13);vector< TermStat >analyse14 =An->analyserVector("Tesla Motors, Inc.txt",doc14);vector< TermStat >analyse15 =An->analyserVector("Audi AI.txt",doc15);
vector< TermStat >analyse16 =An->analyserVector("bitcoin blockchain.txt",doc16);vector< TermStat >analyse17 =An->analyserVector("covid-19.txt",doc17);vector< TermStat >analyse18 =An->analyserVector("Alhpabet.txt",doc18);
vector< TermStat >analyse19 =An->analyserVector("Bayerische Motoren Werke.txt",doc19);vector< TermStat >analyse20 =An->analyserVector("HP Inc.txt",doc20);

isv.indexer(analyse1);isv.indexer(analyse2);isv.indexer(analyse3);isv.indexer(analyse4);isv.indexer(analyse5);isv.indexer(analyse6);isv.indexer(analyse7);isv.indexer(analyse8);isv.indexer(analyse9);isv.indexer(analyse10);
isv.indexer(analyse11);isv.indexer(analyse12);isv.indexer(analyse13);isv.indexer(analyse14);isv.indexer(analyse15);isv.indexer(analyse16);isv.indexer(analyse17);isv.indexer(analyse18);isv.indexer(analyse19);isv.indexer(analyse20);

//isv.afficheIndex();
//isv.sauvgarder();
isv.afficher();
od->ordanancerVector(req ,isv);

od->afficher();//Affichage avanceé ,le score est inclus
od->afficherResultat(3);//affichage les  premieres nombre de titres de fichiers suivant l'ordre de pertinence
                        //le nombre de titres est un parametre
*/
/*******************TEST TFIDF***********************/
/*
Analyseur *An   ;ordonanceur *od    ;Index *inx;
IndexStructureMap ism   ;AnalyseurFrequence ano  ;ordonanceurTFIDF ordo;
An=&ano ;od=&ordo    ;inx=&ism;


map<string,double>analyse1 =An->analyserMap(doc1);
map<string,double>analyse2 =An->analyserMap(doc2);
map<string,double>analyse3 =An->analyserMap(doc3);
map<string,double>analyse4 =An->analyserMap(doc4);
map<string,double>analyse5 =An->analyserMap(doc5);
map<string,double>analyse6 =An->analyserMap(doc6);
map<string,double>analyse7 =An->analyserMap(doc7);
map<string,double>analyse8 =An->analyserMap(doc8);
map<string,double>analyse9 =An->analyserMap(doc9);
map<string,double>analyse10 =An->analyserMap(doc10);
map<string,double>analyse11 =An->analyserMap(doc11);
map<string,double>analyse12 =An->analyserMap(doc12);
map<string,double>analyse13 =An->analyserMap(doc13);
map<string,double>analyse14 =An->analyserMap(doc14);
map<string,double>analyse15 =An->analyserMap(doc15);
map<string,double>analyse16 =An->analyserMap(doc16);
map<string,double>analyse17 =An->analyserMap(doc17);
map<string,double>analyse18 =An->analyserMap(doc18);
map<string,double>analyse19 =An->analyserMap(doc19);
map<string,double>analyse20 =An->analyserMap(doc20);


ism.indexer("odyssey.txt",analyse1);
ism.indexer("valhalla.txt",analyse2);
ism.indexer("origin.txt",analyse3);
ism.indexer("blackflag.txt",analyse4);
ism.indexer("syndicate.txt",analyse5);
ism.indexer("deep learning.txt",analyse6);
ism.indexer("higher ground.txt",analyse7);
ism.indexer("nba.txt",analyse8);
ism.indexer("Attack on titans.txt",analyse9);
ism.indexer("MSI.txt",analyse10);
ism.indexer("dark.txt",analyse11);
ism.indexer("sony.txt",analyse12);
ism.indexer("seat.txt",analyse13);
ism.indexer("Tesla Motors ,Inc.txt",analyse14);
ism.indexer("Audi AI.txt",analyse15);
ism.indexer("bitcoin blockchain.txt",analyse16);
ism.indexer("covid-19.txt",analyse17);
ism.indexer("Alphabet.txt",analyse18);
ism.indexer("Bayerische Motoren Werke.txt",analyse19);
ism.indexer("HP Inc.txt",analyse20);
//ism.supprime("blackflag.txt");//Supprimer un fichier de l'index

inx->afficher();//affichers des statistiques sur l'index


od->ordanancerMap(req ,ism);


//inx->afficheIndex();
//auto start = std::chrono::high_resolution_clock::now();



//auto finish = std::chrono::high_resolution_clock::now();

//std::chrono::duration<double> elapsed = finish - start;
//std::cout << "Elapsed time: " << elapsed.count() << " s\n";


od->afficher();//Affichage avanceé ,le score est inclus
od->afficherResultat(3);//affichage les  premieres nombre de titres de fichiers suivant l'ordre de pertinence
                        //le nombre de titres est un parametre


*/
/*******************************Test Corpus proposee***********************************/
/*
Extracteur *e ;
Analyseur *An   ;ordonanceur *od    ;Index *inx;
IndexStructureMap ism   ;AnalyseurFrequence ano  ;ordonanceurTFIDF ordo;
An=&ano ;od=&ordo    ;inx=&ism;
ExtracteurRequete Erq;
ExtracteurDocument Erd;

auto start = std::chrono::high_resolution_clock::now();

e=&Erq;
vector<string> req =e->extracter("Hypochlorous acid is a chemical compound Its chemical formula is HClO or HOCl I");//extraction de la requete

e=&Erd;
int compteur ;
for (compteur =0  ; compteur < 70000 ;++compteur){
  string fichier="biblio/corpus/"+to_string(compteur)+".txt";
  cout<<fichier<<endl;
  vector<string> doc=e->extracter(fichier);
  map<string,double>analyse1 =An->analyserMap(doc);
  ism.indexer(fichier,analyse1);
};
od->ordanancerMap(req ,ism);
od->afficherResultat(3);

auto finish = std::chrono::high_resolution_clock::now();
std::chrono::duration<double> elapsed = finish - start;
std::cout << "Elapsed time: " << elapsed.count() << " s\n";

*/
return 0;
}
