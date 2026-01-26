CREATE DATABASE Biblioteca;


CREATE TABLE Utenti(
    ID_Utente int not null auto_increment,
    Nome varchar(20) not null,
    Cognome varchar(20) not null,
    Citta varchar(20) not null,
    Telefono varchar(15) not null,


    PRIMARY KEY(ID_Utente)
)ENGINE InnoDB;




CREATE TABLE Libri(
    ID_Libro int not null auto_increment,
    Titolo varchar(30) not null,
    Autore varchar(30) not null,
    Genere varchar(30) not null,


    PRIMARY KEY(ID_Libro)
)ENGINE INNODB;


CREATE TABLE Scaffali(
    ID_Scaffale int not null auto_increment,
    Stanza int not null,
    Armadio int not null,


    PRIMARY KEY(ID_Scaffale)
)ENGINE INNODB;


CREATE TABLE Copie(
    ID_Copia int not null auto_increment,


    ID_Scaffale int,
    ID_Libro int,


    PRIMARY KEY(ID_Copia),
    FOREIGN KEY(ID_Scaffale) REFERENCES Scaffali(ID_Scaffale),
    FOREIGN KEY(ID_Libro) REFERENCES Libri(ID_Libro)
)ENGINE INNODB;


CREATE TABLE Prestiti(
    ID_Prestito int not null auto_increment,
    Data_Inizio date not null,
    Durata int not null,
    Data_Restituzione date,
   
    ID_Utente int,
    ID_Copia int,


    PRIMARY KEY(ID_Prestito),
    FOREIGN KEY(ID_Utente) REFERENCES Utenti(ID_Utente),
    FOREIGN KEY(ID_Copia) REFERENCES Copie(ID_Copia)
)ENGINE INNODB;




--- Insert ---


INSERT INTO Utenti(Nome,Cognome,Citta,Telefono)
VALUES
("Piero","Armadilli","Fiumefreddo","3945098743"),
("Giovanna","Di Roberti","Fiumefreddo","3945397509"),
("Marianna","Pasquale", "Riposto","3459875655"),
("Filippo","Pascoli","Riposto","3984554234"),
("Giuseppe","Alfonsi","Giarre","334598612"),
("Antonio","Marocco","Giarre","2235598793"),
("Marco","Rosselli","Giarre","3456455345"),
("Lucia","Marinetti","Acireale","3345667546"),
("Andrea","Costanzo","Acireale","4542459808"),
("Massimo","Trovato","Fiumefreddo","5546589001"),
("Daniela","Costanza","Fiumefreddo","3338977089"),
("Massimo","Alfonsi","Fiumefreddo","4345640998"),
("Gianna","Pascoli","Fiumefreddo","6569890823"),
("Martina","Gomez","Fiumefreddo","4349888340"),
("Andrea","Dei Campi","Fiumefreddo","3934440989"),
("Giacomo","Tirreni","Fiumefreddo","0953454534"),
("Armando","Verona","Fiumefreddo","3456876117"),
("Rossanna","Maccarone","Fiumefreddo","5439875502"),
("Irelia","Ronaldi","Catania","4560983456");


INSERT INTO Libri(Titolo,Autore,Genere)
VALUES
("I Promessi Sposi","Alessandro Manzoni","Romanzo"),
("La Monaca di Monza","Alessandro Manzoni","Narrativa"),
("La Divina Commedia","Dante Alighieri","Poesia"),
("Inferno","Dante Alighieri","Poesia"),
("Purgatorio","Dante Alighieri","Poesia"),
("Paradiso","Dante Alighieri","Poesia"),
("De Vulgari Eloquentia","Dante Alighieri","Trattato"),
("Convivio","Dante Alighieri","Poesia"),
("Decameron","Giovanni Boccaccio","Romanzo"),
("Canzoniere","Francesco Petrarca","Poesia"),
("Odissea","Omero","Poema"),
("Illiade","Omero","Poema"),
("Eneide","Publio Virgilio Marone","Poema"),
("Il Piccolo Principe","Antoine de Saint-Exupéry","Novella"),
("Il Ritratto Di Dorian Gray","Oscar Wilde","Narrativa"),
("Moby Dick","Herman Melville","Avventura"),
("Frankenstein","Mary Shelley","Fantascienza"),
("Don Chisciotte Della Mancia","Miguel De Cervantes","Romanzo");


INSERT INTO Scaffali(Stanza,Armadio)
VALUES  
(1,1), (2,1), (3,1), (4,1), (5,1), (6,1), (7,1),
(1,2), (2,2), (3,2), (4,2), (5,2), (6,2), (7,2),
(1,3), (2,3), (3,3), (4,3), (5,3), (6,3), (7,3),
(1,4), (2,4), (3,4), (4,4),
(1,5), (2,5), (3,5), (4,5);




INSERT INTO Copie(ID_Libro,ID_Scaffale)
VALUES
(1,1), (1,1), (1,1), (1,1), (1,1), (1,2), (1,2),
(2,1), (2,1), (2,1), (2,2),
(3,2), (3,2), (3,3), (3,3), (3,3), (3,4),
(4,3), (4,4), (4,4), (4,4),
(5,5), (5,5), (5,5),
(6,6), (6,6), (6,7), (6,7), (6,7),
(7,7), (7,7), (7,7),
(8,8), (8,8), (8,8), (8,9), (8,9),
(9,9), (9,9), (9,9), (9,10),
(10,10), (10,10),
(11,11), (11,11), (11,12),
(12,12), (12,12), (12,12), (12,13),
(13,13), (13,13),
(14,14),
(15,14), (15,14), (15,15), (15,15), (15,15), (15,16),
(16,16), (16,17), (16,17),
(17,17), (17,18),
(18,18), (18,19), (18,19);




INSERT INTO Prestiti(ID_Utente,ID_Copia,Data_Inizio,Durata,Data_Restituzione)
VALUES
(1,1,'2022-02-10',60,'2022-04-10'),
(2,2,'2022-04-11',60,'2022-06-11'),
(3,3,'2021-05-15',40,'2021-08-22'),
(4,3,'2021-08-23',50,'2021-12-01'),
(5,4,'2022-02-02',90,'2022-05-02'),
(6,9,'2020-04-14',60,'2020-06-20'),
(7,12,'2021-03-09',45,'2021-04-22'),
(8,14,'2021-03-05',20,'2021-03-25'),
(9,20,'2022-02-01',15,'2022-02-15'),
(12,30,'2019-04-27',50,'2019-10-23'),
(13,4,'2018-04-04',60,'2018-06-01'),
(14,7,'2019-05-27',30,'2019-06-06');



INSERT INTO Prestiti(ID_Utente,ID_Copia,Data_Inizio,Durata)
VALUES
(1,1,'2023-03-24',70),
(5,2,'2023-02-19',60),
(7,3,'2023-02-15',60),
(13,4,'2023-01-20',80),
(15,5,'2023-03-15',60),
(12,25,'2023-01-23',90),
(14,45,'2023-01-27',60),
(17,7,'2023-01-05',30),
(10,13,'2023-01-07',60),
(13,28,'2023-01-11',45),
(15,37,'2023-03-20',60),
(16,38,'2023-02-28',60),
(17,35,'2023-02-04',90),
(18,42,'2023-03-21',45),
(19,25,'2023-01-15',90),
(10,22,'2023-03-15',50),
(11,24,'2023-02-22',90);


--- Query ---


-- A) Numero dei libri presi in prestito dai vari utenti nel corrente mese di Gennaio. Fornire Un elenco del tipo id_utente, nome, n_libri:

SELECT U.ID_Utente, U.Nome, COUNT(P.ID_Copia) AS n_libri
FROM Utenti U
INNER JOIN Prestiti P ON U.ID_Utente = P.ID_Utente
WHERE MONTH(P.Data_Inizio) = 1
  AND YEAR(P.Data_Inizio) = YEAR(CURDATE())
GROUP BY U.ID_Utente, U.Nome;

-- B) Elenco delle copie che sono state effettivamente restituite dopo la data presunta di scadenza del prestito (di ciascuna copia
-- mostrare il titolo e il nome dell utente che l ha presa in prestito)

SELECT L.Titolo, U.Nome, U.Cognome
FROM Prestiti P
INNER JOIN Copie C ON P.ID_Copia = C.ID_Copia
INNER JOIN Libri L ON C.ID_Libro = L.ID_Libro
INNER JOIN Utenti U ON U.ID_Utente = P.ID_Utente
WHERE P.Data_Restituzione IS NOT NULL 
AND P.Data_Restituzione > DATE_ADD(P.Data_Inizio, INTERVAL P.Durata DAY);



-- C) Una copia viene detta disponibile se non è correntemente in prestito: produrre l elenco delle copie non disponibili del libro
-- 'I promessi sposi' (ciascuna di tali copie mostrare il codice)

SELECT P.ID_Prestito,C.ID_Copia, L.ID_Libro, L.Titolo
FROM Prestiti P
INNER JOIN Copie C ON P.ID_Copia = C.ID_Copia
INNER JOIN Libri L ON C.ID_Libro = L.ID_Libro
WHERE  L.Titolo = "I Promessi Sposi" AND P.Data_Restituzione = NULL
ORDER BY P.ID_Prestito;


-- D) I titoli dei libri di cui la biblioteca possiede almeno 3 copie (elenco del tipo titolo, numero copie)

SELECT L.Titolo, count(C.ID_Copia) AS NumeroCopie
FROM Libri L 
INNER JOIN Copie C ON L.ID_Libro = C.ID_Libro
GROUP BY L.Titolo
HAVING count(C.ID_Copia) >= 3;


-- E) Lista degli utenti che hanno avuto in prestito almeno uno dei volumi contenuti negli scaffali della stanza 7

SELECT DISTINCT(U.ID_Utente), U.Nome, U.Cognome
FROM Utenti U 
INNER JOIN Prestiti P ON U.ID_Utente = P.ID_Utente
INNER JOIN Copie C ON C.ID_Copia = P.ID_Copia
INNER JOIN Scaffali S ON S.ID_Scaffale = C.ID_Scaffale
WHERE S.Stanza = 7


-- F) Titolo dei libri le cui copie non sono collocate tutte nel medesimo scaffale

SELECT L.Titolo
FROM Libri L
INNER JOIN Copie C ON L.ID_Libro = C.ID_Libro
GROUP BY L.ID_Libro, L.Titolo
HAVING COUNT(DISTINCT C.ID_Scaffale) > 1;



-- G) Titolo del/i libro/i più prestato/i tenendo conto dei prestiti complessivi delle varie copie.

SELECT L.Titolo, COUNT(P.ID_Prestito) AS NumPrestiti
FROM Libri L
JOIN Copie C ON L.ID_Libro = C.ID_Libro
JOIN Prestiti P ON P.ID_Copia = C.ID_Copia
GROUP BY L.ID_Libro, L.Titolo
HAVING COUNT(P.ID_Prestito) = (
    SELECT MAX(tot)
    FROM (
        SELECT COUNT(P2.ID_Prestito) AS tot
        FROM Copie C2
        JOIN Prestiti P2 ON P2.ID_Copia = C2.ID_Copia
        GROUP BY C2.ID_Libro
    ) AS x
);










