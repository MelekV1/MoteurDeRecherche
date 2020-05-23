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
    void restaurer();
    void importer();
    set<string>GetFiles();
    string GetPath();
    ~BibilothequeDeFichiers();
};
/************************************GestionBibilotheque*****************************************/
BibilothequeDeFichiers::BibilothequeDeFichiers(string chemin):CheminCorpus(chemin)
    {}
/************************************GestionBibilotheque*****************************************/

void BibilothequeDeFichiers::ajouter(string document)
    {
      Corpus.emplace(document);
    }
/************************************GestionBibilotheque*****************************************/
void BibilothequeDeFichiers::ajouter(vector<string> documents)
    {
      for( vector<string>::iterator doc = documents.begin();doc != documents.end();++doc )
      ajouter(*doc);
    }
/************************************GestionBibilotheque*****************************************/
void BibilothequeDeFichiers::supprimer(string document)
    {
      set<string>::iterator obj ;
      obj=Corpus.find(document);
      if (obj!=Corpus.end())
      {
      Corpus.erase(obj);
      }
    }
/************************************GestionBibilotheque*****************************************/
void BibilothequeDeFichiers::supprimer(vector<string> documents)
    {
      for( vector<string>::iterator doc = documents.begin();doc != documents.end();++doc )
      supprimer(*doc);
    }
/************************************GestionBibilotheque*****************************************/
void BibilothequeDeFichiers::afficher()
    {
      string fichierlecture=CheminCorpus+"enregistrement";
      ifstream f(fichierlecture.c_str());
      if (f){
        string line;
        while(getline(f,line))
        {
            cout<<line<<endl;
        }
      }
      else{
        cout<<"ERREUR:Lecture Impossible"<<endl;
      }
    }
/************************************GestionBibilotheque*****************************************/
void BibilothequeDeFichiers::sauvegarder(){
      ofstream Fichier( ( CheminCorpus+"enregistrement" ).c_str() );
      set<string> ::iterator fich;
      for(fich = Corpus.begin() ; fich!=Corpus.end(); ++fich)
      {
        Fichier<<*fich<<endl;
      }
      Fichier.close();
    }
/************************************GestionBibilotheque*****************************************/
string BibilothequeDeFichiers::GetPath()
{
    return this->CheminCorpus;
}
/************************************GestionBibilotheque*****************************************/
set<string> BibilothequeDeFichiers::GetFiles()
    {
      return this->Corpus;
    }
/************************************GestionBibilotheque*****************************************/
void BibilothequeDeFichiers::restaurer()
{
  string refr;
  ifstream exfile(CheminCorpus+"/enregistrement");
  if(exfile)
  {
    string titre;
    while(getline(exfile,titre))
    {
      Corpus.emplace(titre);
    }
  }else{
      cout<<"ERREUR:Lecture Impossible"<< endl ;
    }
};
/************************************GestionBibilotheque*****************************************/
BibilothequeDeFichiers::~BibilothequeDeFichiers()
{
  sauvegarder();
  cout<<"Fichier sauvegarde"<<endl;
};
