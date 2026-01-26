CREATE TABLE Filiali(
    ID_Filiale int not null auto_increment,
    Nome varchar(30) not null,
    Citta varchar(20) not null,
    Patrimonio float not null,

    PRIMARY KEY(ID_Filiale)
)ENGINE INNODB;

CREATE TABLE Prestiti(
    ID_Prestito int not null auto_increment,
    Cod_Ufficio int not null,
    Euro float not null,
    DataApertura date not null,
    DataChiusura date not null,
    ID_Filiale int,

    PRIMARY KEY(ID_Prestito),
    FOREIGN KEY(ID_Filiale) REFERENCES Filiali(ID_Filiale)
)ENGINE INNODB;

CREATE TABLE Clienti(
    ID_Cliente int not null auto_increment,
    Nome varchar(20) not null,
    Cognome varchar(20) not null,
    Indirizzo varchar(40) not null,
    Email varchar(40) not null,
    DataNascita date not null,
    CodiceFiscale varchar(17),
    Citta varchar(20) not null,

    PRIMARY KEY(ID_Cliente)
)ENGINE INNODB;

CREATE TABLE Effettuano(
    ID_Effettuano int not null auto_increment,
    ID_Prestito int,
    ID_Cliente int,

    PRIMARY KEY(ID_Effettuano),

    FOREIGN KEY(ID_Prestito) REFERENCES Prestiti(ID_Prestito),
    FOREIGN KEY(ID_Cliente) REFERENCES Clienti(ID_Cliente)

)ENGINE INNODB;

CREATE TABLE ContiCorrenti(
    ID_Conto int not null auto_increment,
    SaldoEuro float not null,
    ID_Filiale int,

    PRIMARY KEY(ID_Conto),

    FOREIGN KEY(ID_Filiale) REFERENCES Filiali(ID_Filiale)
)ENGINE INNODB;

CREATE TABLE Intestano(

    ID_Intestano int not null auto_increment,
    ID_Conto int,
    ID_Cliente int,

    PRIMARY KEY(ID_Intestano),

    FOREIGN KEY(ID_Conto) REFERENCES ContiCorrenti(ID_Conto),
    FOREIGN KEY(ID_Cliente) REFERENCES Clienti(ID_Cliente)

)ENGINE INNODB;



/////////////////////////////////////////////////



INSERT INTO Filiali(Nome,Citta,Patrimonio)
    VALUES
    ("Intesa San Paolo", "Catania", 25000000.78),
    ("Intesa San Paolo", "Napoli", 525000000.55),
    ("Unicredit", "Milano",54200000.00),
    ("Unicredit","Giarre", 98000.90),
    ("Banco BPM", "Acireale", 55980900.88),
    ("Banco BPM", "Giarre", 67000.00),
    ("Livorno Bank", "Livorno", 999999.00),
    ("Livorno Banche", "Livorno", 5400000.00),
    ("Banca Riposto","Riposto",65000.00),
    ("Credem Banca", "Catania", 80080022.43),
    ("Giarre banche","Giarre", 98000.90),
    ("Banca Monte dei Paschi", "Giarre", 67000.00),
    ("Banca Di Firenze","Firenze",653634.00),
    ("Unicredit Firenze","Firenze",3634524.00),
    ("Banco BPM Firenze","Firenze",45364324.00);




INSERT INTO Prestiti(Cod_Ufficio,Euro,DataApertura,DataChiusura,ID_Filiale)
    VALUES
    (1,5000.00,20101009,20151009,1),
    (1,20000.00,20101118,20130504,2),
    (2,50000,20130609,20180805,7),
    (2,60000,20140808,20200809,1),
    (3,70000,20090115,20220505,3),
    (3,55000,20080909,20230606,5),
    (4,66000,20040913,20140505,4),
    (4,89000,20101210,20221012,6);




INSERT INTO Clienti(Nome,Cognome,Indirizzo,Citta,Email,DataNascita,CodiceFiscale)
    VALUES
    ("Pino","Bianchi","Via Cavour, 44","Giarre","PinoBianchi88@gmail.com",19880422,"BNCPNI88D04E017X"),
    ("Rosa","Maccarone","Via Roma, 22", "Acireale", "RosaMaccarone92@gmail.com",19920913,"MCCRSO92P53A028Y"),
    ("Gianni","Barbagianni","Via Empoli, 67", "Catania","GianniBarbagianni79@yahoo.it",19791122,"BRBGNN79S22C351L"),
    ("Luigi","Verdi","Via Gioele, 88", "Giarre","LuigiVerdi96@libero.it",19960715,"VRDLGU96L15E017S"),
    ("Marta","Villaggio","Via Domenica, 38","Acireale","MartaVillaggio67@gmail.com",19670525,"VLLMRT67E65A028G"),
    ("Pina","Rossi","Via Gennaio, 32","Catania","PinaRossi99@hotmail.it",19990226,"RSSPNI99B66C351Q"),
    ("Roberto","Bianchi","Via Conte, 102","Milano","RobertoBianchi91@yahoo.it",19911230,"BNCRRT91T30F205V");


INSERT INTO ContiCorrenti(SaldoEuro,ID_Filiale)
    VALUES
    (54200.98,1),
    (20198.88,1),
    (5823.78,2),
    (194540.50,2),
    (28354.15,2),
    (32445.1,3),
    (42342.22,3),
    (34233.21,4),
    (423420.3,4),
    (98764.55,5),
    (765864.43,5),
    (3124.01,6),
    (53245.00,6),
    (42345.98,7),
    (5342523.65,7),


    (342344,13),
    (4553,14),
    (243567,15),


    (1234,13),
    (3456,14),
    (34567,15);




INSERT INTO Intestano(ID_Conto,ID_Cliente)
    VALUES
    (1,1),
    (1,2),
    (2,2),
    (2,6),
    (3,1),
    (3,3),
    (4,4),
    (4,3),
    (4,5),
    (5,7),
    (5,6),
    (5,1),


    (16,6),
    (17,6),
    (18,6),


    (19,5),
    (20,5),
    (21,5);


INSERT INTO Effettuano(ID_Prestito,ID_Cliente)
    VALUES
    (1,1),
    (1,2),
    (2,3),
    (4,4),
    (5,4),
    (6,5),
    (6,6);





///////////////////////////////////////////////////////

A) Per ogni prestito, il valore del prestito e i dati identificativi dei clienti che lo hanno stipulato


SELECT Euro, C.ID_Cliente, C.Nome, C.Cognome
FROM Prestiti P JOIN Effettuano E USING(ID_Prestito) JOIN Clienti C USING(ID_Cliente);




B) Elenco di tutti i clienti che hanno almeno un deposito e almeno un prestito


SELECT C.ID_Cliente, C.Nome,C.Cognome, CC.ID_Conto
FROM Clienti C JOIN Intestano I USING(ID_Cliente) JOIN ContiCorrenti CC USING(ID_Conto)
WHERE CC.SaldoEuro > 0 AND ID_Cliente IN (
                                           SELECT ID_Cliente
                                           FROM Clienti C JOIN Effettuano E USING(ID_Cliente) JOIN Prestiti P USING(ID_Prestito)
)
ORDER BY C.ID_Cliente;




C) Elenco di tutti i clienti titolari di almeno un deposito ma non di un prestito


SELECT C.ID_Cliente, C.Nome,C.Cognome, CC.ID_Conto
FROM Clienti C JOIN Intestano I USING(ID_Cliente) JOIN ContiCorrenti CC USING(ID_Conto)
WHERE CC.SaldoEuro > 0 AND ID_Cliente NOT IN (
                                           SELECT ID_Cliente
                                           FROM Clienti C JOIN Effettuano E USING(ID_Cliente) JOIN Prestiti P USING(ID_Prestito)
)
ORDER BY C.ID_Cliente;


D) Per ogni filiare, il numero dei titolari di conti correnti (contare ogni cliente una sola volta)


SELECT COUNT(distinct C.ID_Cliente) AS NumClienti, F.ID_Filiale
FROM Clienti C JOIN Intestano I USING(ID_Cliente)JOIN ContiCorrenti CC USING(ID_Conto) JOIN Filiali F USING(ID_Filiale)
GROUP BY(F.ID_Filiale)


E) Elenco di tutte le filiali che hanno un patrimonio maggiore del più piccolo capitale delle filiali di Livorno


SELECT DISTINCT(ID_Filiale) AS IDFiliale, Nome, Citta, Patrimonio
FROM Filiali
WHERE Patrimonio > (SELECT MIN(Patrimonio)
                    FROM Filiali
                    WHERE Citta = "Livorno"
                    )


F) Il nome della/e filiale/i con il saldo medio più alto


SELECT ID_Filiale, Nome, Citta, Patrimonio
FROM Filiali
WHERE Patrimonio > (SELECT AVG(Patrimonio)
                   FROM Filiali
                   )




G) Elenco dei clienti che hanno un deposito presso tutte le filiali di Firenze


SELECT c.ID_Cliente, c.nome, c.cognome
FROM Clienti c
WHERE (
  SELECT COUNT(DISTINCT f.ID_Filiale)
  FROM Filiali f
    JOIN ContiCorrenti cc USING(ID_Filiale)
    JOIN Intestano i USING(ID_Conto)
  WHERE f.citta = 'Firenze' AND i.ID_Cliente = c.ID_Cliente
) = (
  SELECT COUNT(*)
  FROM Filiali
  WHERE citta = 'Firenze'
)


H) Saldo medio dei vari clienti che vivono a Siena e hanno almeno due depositi


SELECT c.ID_Cliente, c.nome, c.cognome, c.citta, AVG(SaldoEuro) AS SaldoMedio
FROM Clienti C JOIN Intestano I USING(ID_Cliente) JOIN ContiCorrenti CC USING(ID_Conto)
WHERE citta="Giarre"
GROUP BY(ID_Cliente)
HAVING COUNT(ID_Conto) >= 2


I) Numero dei titolari di deposito per ogni filiare dove il saldo medio dei depositi sia superiore a 6500 euro


SELECT count(distinct ID_Cliente) AS IDCliente, C.Nome, C.Cognome, AVG(CC.SaldoEuro) AS MediaSaldo
    FROM Clienti C 
        JOIN Intestano I USING(ID_Cliente)
        JOIN ContiCorrenti CC USING(ID_Conto)
        JOIN Filiali F USING(ID_Filiale)

    GROUP BY C.ID_Cliente
    HAVING AVG(CC.SaldoEuro) > 6500