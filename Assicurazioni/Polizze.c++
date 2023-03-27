/*Scegli un database relazionale: puoi scegliere tra diversi database relazionali, come MySQL, PostgreSQL o SQLite.

Crea le tabelle del database: crea le tabelle necessarie per gestire le informazioni sugli utenti e sulle polizze. Ad esempio, potresti creare una tabella "Utenti" con colonne come nome, cognome, indirizzo e una tabella "Polizze" con colonne come tipo, premio, copertura, data di scadenza e un campo di chiave esterna che si riferisce all'ID dell'utente.

Connettiti al database: utilizza una libreria di connessione al database come la libreria MySQL Connector/C++ o PostgreSQL C++ API per connetterti al database e gestire i dati.

Crea la classe Polizza: crea una classe Polizza che rappresenta una singola polizza assicurativa. La classe dovrebbe avere attributi come il tipo di assicurazione, il premio assicurativo, la copertura massima, la data di scadenza e un campo di chiave esterna che si riferisce all'ID dell'utente.

Implementa i metodi della classe Polizza: implementa i metodi necessari per permettere all'utente di effettuare operazioni come l'acquisto di una polizza, la modifica delle informazioni dell'assicurato, il pagamento del premio e la richiesta di risarcimento. Assicurati di utilizzare le funzioni di connessione al database per salvare le informazioni sulla polizza nel database.

Crea la classe Utente: crea una classe Utente che rappresenta un singolo utente dell'assicurazione. La classe dovrebbe avere attributi come nome, cognome, indirizzo e un campo di chiave primaria per identificare univocamente ogni utente.

Implementa i metodi della classe Utente: implementa i metodi necessari per permettere all'utente di effettuare operazioni come la registrazione, la modifica delle informazioni personali e la visualizzazione delle polizze possedute. Assicurati di utilizzare le funzioni di connessione al database per salvare le informazioni sull'utente nel database.

Crea l'interfaccia utente: crea un'interfaccia utente che permetta all'utente di interagire con il programma. Utilizza una libreria grafica come Qt per creare un'interfaccia grafica facile da usare.

Testa il programma: testa il programma utilizzando tecniche di testing come il testing unitario e il testing funzionale per assicurarti che funzioni correttamente.

Pubblica il programma e fornisci supporto ai clienti: pubblica il programma e fornisci un supporto ai clienti per risolvere eventuali problemi o rispondere alle loro domande. Assicurati di avere un team dedicato alla gestione e al supporto degli utenti.*/

#include <iostream>
#include <string>
//#include "mysqlx/xdevapi.h";
#include <mysqlx/xdevapi.h>
using namespace std;
using namespace mysqlx;

class Polizza {
    private:
        int id;
        string tipo;
        double premio;
        double copertura;
        string dataScadenza;
        string nomeAssicurato;
        

    public:
        // costruttore della classe
        Polizza(string tipo, double premio, double copertura, string dataScadenza, string nomeAssicurato) {
            this->id = 0; // il valore 0 indica che la polizza non è stata ancora salvata nel database
            this->tipo = tipo;
            this->premio = premio;
            this->copertura = copertura;
            this->dataScadenza = dataScadenza;
            this->nomeAssicurato = nomeAssicurato;
        }

        // metodi per ottenere informazioni sulla polizza
        string getTipo() {
            return tipo;
        }

        double getPremio() {
            return premio;
        }

        double getCopertura() {
            return copertura;
        }

        string getDataScadenza() {
            return dataScadenza;
        }

        string getNomeAssicurato() {
            return nomeAssicurato;
        }

        // metodo per salvare la polizza nel database
        void salvaPolizza() {
            // se la polizza non è ancora stata salvata nel database, inseriscila
            if (id == 0) {
                Table polizze = mySchema.getTable("Polizze");
                Row row = polizze.insert("tipo", "premio", "copertura", "dataScadenza", "nomeAssicurato")
                                   .values(tipo, premio, copertura, dataScadenza, nomeAssicurato)
                                   .execute();
                id = row[0];
            }
            // al contrario, aggiorna la polizza nel database
            else {
                Table polizze = mySchema.getTable("Polizze");
                polizze.update()
                        .set("tipo", tipo)
                        .set("premio", premio)
                        .set("copertura", copertura)
                        .set("dataScadenza", dataScadenza)
                        .set("nomeAssicurato", nomeAssicurato)
                        .where("id = :id")
                        .bind("id", id)
                        .execute();
            }
        }

        // metodo per eliminare la polizza dal database
        void eliminaPolizza() {
            Table polizze = mySchema.getTable("Polizze");
            polizze.remove()
                    .where("id = :id")
                    .bind("id", id)
                    .execute();
        }
};

class Utente {
    private:
        int id;
        string nome;
        string cognome;
        string indirizzo;

    public:
        // costruttore della classe
        Utente(string nome, string cognome, string indirizzo) {
            this->id = 0; // il valore 0 indica che l'utente non è stato ancora salvato nel database
            this->nome = nome;
            this->cognome = cognome;
            this->indirizzo = indirizzo;
        }

        // metodi per ottenere informazioni sull'utente
        string getNome() {
            return nome;
        }

        string getCognome() {
            return cognome;
        }

        string getIndirizzo() {
            return indirizzo;
        }

        // metodo per salvare l'utente nel database
        void salvaUtente() {
            // se l'utente non è ancora stato salvato nel database, inseriscilo
            if (id == 0) {
                Table utenti = mySchema.getTable("Utenti");
                Row row = utenti.insert("nome", "cognome", "indirizzo")
                                .values(nome, cognome, indirizzo)
                                .execute();
                id = row[0];
            }
            // al contrario, aggiorna l'utente nel database
            else {
                Table utenti = mySchema.getTable("Utenti");
                utenti.update()
                      .set("nome", nome)
                      .set("cognome", cognome)
                      .set("indirizzo", indirizzo)
                      .where("id = :id")
                      .bind("id", id)
                      .execute();
            }
        }

        // metodo per eliminare l'utente dal database
        void eliminaUtente() {
            Table utenti = mySchema.getTable("Utenti");
            utenti.remove()
                  .where("id = :id")
                  .bind("id", id)
                  .execute();
        }

        // metodo per ottenere le polizze dell'utente
        vector<Polizza> getPolizze() {
            vector<Polizza> polizze;
            Table polizzeTable = mySchema.getTable("Polizze");
            Result polizzeResult = polizzeTable.select("id", "tipo", "premio", "copertura", "dataScadenza", "nomeAssicurato")
                                               .where("nomeAssicurato = :nomeAssicurato")
                                               .bind("nomeAssicurato", nome + " " + cognome)
                                               .execute();
            for (Row polizzaRow : polizzeResult.fetchAll()) {
                Polizza polizza(polizzaRow[1], polizzaRow[2], polizzaRow[3], polizzaRow[4], polizzaRow[5]);
                polizza.id = polizzaRow[0];
                polizze.push_back(polizza);
            }
            return polizze;
        }
};

// variabili globali

Schema mySchema;
Session mySession;

// funzioni globali

void stampaMenu() {
    cout << "1. Aggiungi polizza" << endl;
    cout << "2. Aggiungi utente" << endl;
    cout << "3. Visualizza polizze" << endl;
    cout << "4. Visualizza utenti" << endl;
    cout << "5. Esci" << endl;
}

void aggiungiPolizza() {
    string tipo;
    double premio;
    double copertura;
    string dataScadenza;
    string nomeAssicurato;

    cout << "Inserisci il tipo di polizza: ";
    cin >> tipo;
    cout << "Inserisci il premio: ";
    cin >> premio;
    cout << "Inserisci la copertura: ";
    cin >> copertura;
    cout << "Inserisci la data di scadenza: ";
    cin >> dataScadenza;
    cout << "Inserisci il nome dell'assicurato: ";
    cin >> nomeAssicurato;

    Polizza polizza(tipo, premio, copertura, dataScadenza, nomeAssicurato);
    polizza.salvaPolizza();
}

void aggiungiUtente() {
    string nome;
    string cognome;
    string indirizzo;

    cout << "Inserisci il nome: ";
    cin >> nome;
    cout << "Inserisci il cognome: ";
    cin >> cognome;
    cout << "Inserisci l'indirizzo: ";
    cin >> indirizzo;

    Utente utente(nome, cognome, indirizzo);
    utente.salvaUtente();
}

void visualizzaPolizze() {
    Table polizze = mySchema.getTable("Polizze");
    Result polizzeResult = polizze.select("id", "tipo", "premio", "copertura", "dataScadenza", "nomeAssicurato").execute();
    for (Row polizzaRow : polizzeResult.fetchAll()) {
        cout << "ID: " << polizzaRow[0] << endl;
        cout << "Tipo: " << polizzaRow[1] << endl;
        cout << "Premio: " << polizzaRow[2] << endl;
        cout << "Copertura: " << polizzaRow[3] << endl;
        cout << "Data di scadenza: " << polizzaRow[4] << endl;
        cout << "Nome assicurato: " << polizzaRow[5] << endl;
        cout << endl;
    }
}

void visualizzaUtenti() {
    Table utenti = mySchema.getTable("Utenti");
    Result utentiResult = utenti.select("id", "nome", "cognome", "indirizzo").execute();
    for (Row utenteRow : utentiResult.fetchAll()) {
        cout << "ID: " << utenteRow[0] << endl;
        cout << "Nome: " << utenteRow[1] << endl;
        cout << "Cognome: " << utenteRow[2] << endl;
        cout << "Indirizzo: " << utenteRow[3] << endl;
        cout << endl;
    }
}

int main() {
    // connessione al database
    mySession = Session::getSession("mysqlx://root:root, password@localhost: Gueaserge port:33060");
    mySchema = mySession.getSchema("assicurazioni");

    // menu
    int scelta;
    do {
        stampaMenu();
        cout << "Inserisci la tua scelta: ";
        cin >> scelta;
        switch (scelta) {
            case 1:
                aggiungiPolizza();
                break;
            case 2:
                aggiungiUtente();
                break;
            case 3:
                visualizzaPolizze();
                break;
            case 4:
                visualizzaUtenti();
                break;
            case 5:
                break;
            default:
                cout << "Scelta non valida" << endl;
                break;
        }
    } while (scelta != 5);
    return 0;
}
