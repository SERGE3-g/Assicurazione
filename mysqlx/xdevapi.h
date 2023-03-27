#include <mysqlx/xdevapi.h>
using namespace mysqlx;

// definisco le informazioni di connessione al database
const string host = "localhost";
const unsigned int port = 3306;
const string user = "root";
const string password = "Gueaserge";
const string schema = "Assicurazione";

// creo una connessione al database
Session session(SessionOption::HOST, host, port, SessionOption::USER, user, SessionOption::PWD, password);
Schema mySchema = session.getSchema(schema);

// ottieni la tabella Polizze
Table polizze = mySchema.getTable("Polizze");

// ottieni la polizza con id = 1
RowResult result = polizze.select("id", "tipo", "premio", "copertura", "dataScadenza", "nomeAssicurato")
                          .where("id = :id")
                          .bind("id", 1)
                          .execute();

// ottieni la prima riga del risultato
Row row = result.fetchOne();


// ottieni i valori delle colonne
int id = row[0];
string tipo = row[1];
double premio = row[2];
double copertura = row[3];
string dataScadenza = row[4];
string nomeAssicurato = row[5];

// stampa i valori delle colonne
