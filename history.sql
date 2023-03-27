/* 2023-03-27 16:14:30 [30 ms] */ 
CREATE TABLE user(

id INT NOT NULL AUTO_INCREMENT,
nome VARCHAR(255) NOT NULL,
cognome VARCHAR(255) NOT NULL,
email VARCHAR(255) NOT NULL,
password VARCHAR(255) NOT NULL,
PRIMARY KEY (id)
);
/* 2023-03-27 16:26:50 [66 ms] */ 


/*CREATE TABLE polizze(
  id INT PRIMARY KEY AUTO_INCREMENT,
    tipo VARCHAR(255),
    premio DOUBLE,
    copertura DOUBLE,
    dataScadenza DATE,
    nomeAssicurato VARCHAR(255)
);*/

CREATE TABLE persone(
  id INT PRIMARY KEY AUTO_INCREMENT,
  nome VARCHAR(255),
  cognome VARCHAR(255),
  numeroTelefono VARCHAR(255),
  indirizzo VARCHAR(255),
  citta VARCHAR(255),
  cap VARCHAR(255), 
  email VARCHAR(255),
  password VARCHAR(255)
  
);

