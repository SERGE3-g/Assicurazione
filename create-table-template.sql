-- Active: 1679926215349@@localhost@3306@Assicurazione
/*CREATE TABLE user(

id INT NOT NULL AUTO_INCREMENT,
nome VARCHAR(255) NOT NULL,
cognome VARCHAR(255) NOT NULL,
email VARCHAR(255) NOT NULL,
password VARCHAR(255) NOT NULL,
PRIMARY KEY (id)
);*/

CREATE TABLE polizze(
  id INT PRIMARY KEY AUTO_INCREMENT,
    tipo VARCHAR(255),
    premio DOUBLE,
    copertura DOUBLE,
    dataScadenza DATE,
    nomeAssicurato VARCHAR(255)
);