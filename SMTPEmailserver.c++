#include <iostream>
#include <string>
#include "smtp.h"


int main() {
    // Configuro l'account email di origine e di destinazione
    std::string from = "from@guea.com";
    std::string to = "to@serge.com";

    // Configuro il server SMTP e le credenziali di accesso
    std::string server = "smtp.sergeguea.com"; // Il server SMTP
    std::string username = "username";
    std::string password = "password";

    // Creo un oggetto EmailMessage e imposto i campi del messaggio
    EmailMessage message;            // Creo un oggetto EmailMessage
    message.setFrom(from);          // Imposto il mittente
    message.addTo(to);              // Imposto il destinatario

    message.setSubject("Test email from guea");// Imposto l'oggetto
    message.setBody("Ciao from Serge!");

    // Creo un oggetto SmtpClient e invio il messaggio
    SmtpClient smtp(server, 587);
    smtp.authenticate(SmtpClient::AuthMethod::PLAIN, username, password);
    smtp.sendMessage(message);

    std::cout << "Email inviata!" << std::endl;

    return 0;
}
