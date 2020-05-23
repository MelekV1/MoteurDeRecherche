#include "header.hpp"
int main()
{

ExtracteurRequete Erq;
ExtracteurDocument Erd;
vector<string> req =Erq.extracter("odin is with us in the northen realms");
vector<string> doc1=Erd.extracter("biblio/odyssey.txt");
vector<string> doc2=Erd.extracter("biblio/valhalla.txt");
vector<string> doc3=Erd.extracter("biblio/origin.txt");

Analyseur *An;
ordonanceur *od;

/*******************TEST STRUCTURE MAP *************************/
/*
IndexStructureMap ism;
AnalyseurOccurence ano;
ordonanceurOccurence ordo;
An=&ano;
od=&ordo;

map<string,double>analyse1 =An->analyserMap(doc1);
map<string,double>analyse2 =An->analyserMap(doc2);
map<string,double>analyse3 =An->analyserMap(doc3);

ism.indexer("odyssey.txt",analyse1);
ism.indexer("valhalla.txt",analyse2);
ism.indexer("origin.txt",analyse3);
ism.supprime("odyssey.txt");
od->ordanancerMap(req ,ism);
*/
/*******************TEST STRUCTURE Vector***********************/

IndexStructureVector isv;
AnalyseurOccurence ano;
ordonanceurOccurence ordo;
An=&ano;
od=&ordo;

vector< TermStat >analyse1 =An->analyserVector("odyssey.txt",doc1);
vector< TermStat >analyse2 =An->analyserVector("valhalla.txt",doc2);
vector< TermStat >analyse3 =An->analyserVector("origin.txt",doc3);

isv.indexer(analyse1);
isv.indexer(analyse2);
isv.indexer(analyse3);
isv.sauvgarder();
od->ordanancerVector(req ,isv);



od->afficher();
  return 0;
}
