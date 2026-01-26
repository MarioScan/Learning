Preparazione prova di itinere

da Lezione 1: 

# 1) Introduzione alle basi di dati

Le **basi di dati** sono **insiemi organizzati di dati**, che **esistono** e si **evolvono** nel **tempo**, 
sono **necessari** per **organizzare** dati di una struttura: le aziende, le banche, gli e-commerce, gli ospedali, etc., hanno bisogno dei dati per lo svolgimento delle loro attività.
Notiamo che i **dati sono fondamentali per ogni tipo di attività**.

Possiamo definire le **basi di dati** come **contenitori**, i quali, non solo **contengono** degli **insiemi di risorse** per lo **svolgimento di una attività**, ma anche dalle **regole** di questa **attività**.
 *Esempio:* 
		*Presa una piattaforma di scommesse, è permesso la registrazione ai soli maggiorenni, questo dato deve essere anche gestito nella base di dati.*
			
- **Sistema Aziendale, Organizzativo, Informativo e Informatico:**
	L'**insieme di risorse e regole** di una **attività**, viene chiamato **"Sistema Organizzativo"**.
	Quell'aspetto del **Sistema Organizzativo** che si occupa di **gestire** l'**aspetto** delle **informazioni** **dell'attività**, prende il nome di **"Sistema Informativo"**, il quale bisogna ben distinguere dal **Sistema Informatico**, e quindi da una qualsiasi **automazione**.
	*Infatti:*
		*Nel passato le banche, gli archivi come l'anagrafe, e simili, gestivano dati da ben prima dell'esistenza dei computer.*  
	La **porzione automatizzata** del **Sistema Informativo**, prende il nome di **Sistema Informatico**.
	
    -In sostanza, abbiamo quattro tipi di sistemi:
	* **Sistema Aziendale:** è l'insieme di tutti gli aspetti **organizzativi** ,**informativi**, **produttivi**,**decisionali**, etc., che permettono all'azienda di **funzionare** e **raggiungere** i suoi **obiettivi**.
	   
	* **Sistema Organizzativo:** definisce il funzionamento dell'azienda, quindi: i **ruoli**, le **procedure**, le **responsabilità** di ogni componente dell'azienda, le **relazioni tra persone e reparti**, etc. In pratica, **concretizza gli obiettivi aziendali** in attività concrete da svolgere.
	  
	* **Sistema Informativo:** è composto da tutti quegli elementi e individui che si occupano di **raccogliere**, **elaborare** e **distribuire** tutte quelle informazioni **indispensabili** per l'azienda, nel prendere **decisioni** e gestire le **attività**. 
	  
	* **Sistema Informatico:** è la parte che **automatizza** il **Sistema Informativo**, comprende **hardware**, **software**, **reti**, **base di dati** e tutto quello che permette di automatizzare il processo produttivo tramite questi strumenti appena elencati. 

L'aspetto fondamentale per cui viene fatta questa divisione, consiste nello standardizzare e razionalizzare, i diversi aspetti di una azienda.

- **Differenza tra dato e informazione:** 
	- **Dato:** **elemento grezzo** informativo, **privo di significato** se considerato da **solo**.
	 Rappresenta un **fatto**, una **misurazione**, un'**osservazione** che non è ancora stato interpretato o collegato ad altri elementi.
	  
	- **Informazione:** è il risultato della **raccolta**, ed **elaborazione** dei dati, permette di **interpretare** i **dati** per restituirne un **significato**, **necessaria** per la presa di **decisioni** o di **analisi**.

Quindi la **base di dati**, attraverso la **raccolta** e l'**organizzazione** dei **dati**, ci permette di **ottenere** delle **informazioni** di vitale importanza per il **funzionamento** e la **presa decisionale** dell'**azienda**.

I **dati** costituiscono una **risorsa strategica** **durevole** nel **tempo**, pertanto è **fondamentale organizzarli** e **gestirli** in maniera **strutturata** e **sicura**.

- I **DBMS (Database Management System):** 
	I **sistemi** di **gestione** di **basi di dati**, noti come **DBMS**, sono dei **software complessi** progettati per la **creazione**, **organizzazione** e **gestione efficiente** di **grandi quantità di dati**.
	
	Le informazioni di un DBMS devono essere **immagazzinate** su **dischi** o **nastri** in maniera **persistente nel tempo**, anche a seguito di **crash** o **danneggiamenti**, le informazioni non devono essere perdute.
	
	UN DBMS deve garantire l'**accesso**, **sicuro e coerente**, dei dati tra più utenti, gestendo problemi come:
	- **Accesso concorrente:** più utenti possono accedere e modificare contemporaneamente la stessa risorsa.
	- **Ridondanza e coerenza dei dati:** evitare duplicazioni (ridondanze) ed eventuali **conflitti** dei dati.
	- **Affidabilità:** permettere di **recuperare** e **ripristinare** i dati (uso di **backups**) in caso di **errore** o **interruzione** del sistema DBMS.  
	
	- Esempio 1: 
		*Si immagini un **conto corrente condiviso** da due persone.
		Se entrambi si **collegano contemporaneamente** ed effettuano operazioni in maniera **concorrente**: per esempio un prelievo e un bonifico.
		Il sistema deve essere in grado di **sincronizzare** le transazioni, al fine di evitare **incoerenze** o **comportamenti imprevisti**, come un **saldo errato** o addirittura il **fallimento dell'operazione**.*
	
	- Esempio 2: 
		*Il contatore dei **"like"** di **YouTube**, mostrati sotto un video qualsiasi, non è una informazione costantemente aggiornata. 
		Questo accade perché l'informazione è considerata come **non essenziale**, quindi viene **replicata** su diversi **server** per migliorare la **scalabilità** e le **prestazioni** del sistema, a discapito della **affidabilità** di questa informazione. 
		Per questa ragione si possono notare **ritardi** o **discrepanze temporanee** tra il numero dei **"like"** reali e quelli visualizzati.*
	

**Requisiti di un DBMS (Database Management System):**
  - **Affidabilità:** garantire **resistenza** ai **malfunzionamenti** hardware e software, garentendone così la **persistenza** e il **recupero** dei dati. 
  - **Privatezza e sicurezza:** applicare **regole di controllo** e **autorizzazione** per tutelare la **riservatezza** delle risorse e impedire **accessi non autorizzati**.
  - **Efficiente:** **ottimizzare** l'utilizzo delle **risorse** e del **tempo di elaborazione**, riducendo al minimo i tempi di risposta. 
  - **Efficace:** deve rendere **produttive e semplificate** le attività dei suoi **utilizzatori**, **utenti** e **sviluppatori** che interagiscono con la **base di dati**.

**Categorie di DBMS:**
Esistono molte categorie di DBMS, ma questi due che vedremo sono i principali del mondo dei DBMS, e sono:

- **Modelli Relazionali:** questi modelli si basano sul modello **relazionale** composto da **Tabelle, righe e colonne**, e utilizza il **linguaggio SQL** . 
	Tra i suoi più noti DBMS troviamo:
	1. **MySQL:** il più diffuso DBMS al mondo, utilizzato anche a livello di grandi aziende.
	2. **PostgreSQL:** open source e moderno, utilizzato anche da **Instagram, Spotify, Reddit**.
	3. **SQLite:** è un piccolo DBMS molto pratico, integrato nei **telefoni**, **app** e **browsers**, lo troviamo per esempio, sia in **iOS** che **Android** e browser come **Firefox**. 
	4. **Microsoft SQL Server:** molto usato in ambito aziendale, per banche, imprese, etc.
	5. **Oracle Database:** è tra gli standard per le grandi aziende, costoso ma solido.
	6. **MariaDB:** "fork*" open source, praticamente figlia di MySQL, migliorata performance, compatibilità e trasparenza open-source, rispetto a MySQL, in continua crescita.
	- **IBM DB2** (menzione d'onore): è tra i primi DBMS sviluppati negli anni '70, ha continuato a svilupparsi dalla sua uscita.  
	
	*Nota: Termine "**fork**" intende dire che nasce a seguito di un altro progetto, che ha successivamente preso un'altra strada. In questo caso MariaDB nasce da un gruppo di sviluppatori di MySQL che ha preso il codice sorgente di questo, e lo ha modificato fino a raggiungere una sua versione diversa dall'originale, chiamata MariaDB.*  
	     
- **Modello Non Relazionali (NoSQL):** utilizza un approccio non relazionale (**Not only SQL**), quindi non utilizzano tabelle, ma bensì **salvano** i **dati** come **documenti**, **chiavi-valori**, **grafi** o **colonne**.
  Tra i più famosi vediamo:
	1. **MongoDB**: il più famoso tra i **DBMS NoSQL**, orientato ai **documenti JSON**. Usato da Ebay, Uber, etc.
	2. **Redis:** **rapidissimo key-value store**, spesso usato come **cache** o motore **in-memory**.   
	3. **Cassandra:** **scalabile e distribuito**, usato da Netflix, Instagram 
	4. **Firestore:** proprietà di Google, utilizzato per **app mobile/web in tempo reale** (real-time).
	5. **ElasticSearch:** **motore di ricerca e analisi** di testi, usato per logs e analytics.
	6. **Neo4j:** database a **grafo**, utile per **reti sociali**, **relazioni complesse**, **analisi** di collegamenti.

	Nota: Molte aziende, come Instagram (Meta), Spotify, in questo caso, utilizzano spesso diversi DBMS in base alle necessità. 
	In particolare: 
	Instagram utilizza:
	-  $PostgreSQL$ come DB principale per **Utenti, post, commenti, relazioni tra utenti** (seguiti, seguaci, etc.);
	- $Cassandra$ per i feed, messaggi e notifiche, dove servono **alte prestazioni in scrittura** e **scalabilità orizzontale*.
	- $Redis$ per **cache** e **sessioni**, per sfruttare accessi super rapidi in RAM.

	*Nota: la scalabilità di un database si divide in **orizzontale** e **verticale**, vedremo meglio più avanti, basti sapere che in generale, quella **orizzontale** si basa sul distribuire le informazioni su più server; mentre, quella **verticale** si basa sul potenziare la macchina database già esistente.*


* **Concorrenza tra SQL e NoSQL:**
	Nel 2015 si pensava che i modelli non relazionali avrebbero superato e reso obsoleti quelli relazionali, ma al 2025 la situazione non è cambiata, in quanto i modelli Relazionali sono diventati più efficienti, rimangono infatti nelle top 5:
	1. **Oracle Database**
	2. **MySQL**
	3. **Microsoft SQL Server**
	4. **PostgreSQL**
	5. **MongoDB** $←$ $NoSQL$**
	Dove solo al quinto posto troviamo il primo **DBMS** non **SQL** 


- Il **modello dei dati:** 
	Il **modello dei dati** è un **formalismo matematico** che serve a **descrivere** e **manipolare** i **dati** all’interno di un **database**, ed è la **base teorica** su cui si costruiscono tutti i DBMS
	Esso è composto da due **componenti principali**:
	- **Strutturale (o statica):** descrive **come sono organizzati** i dati.
	- **Manipolativa (o dinamica):** definisce le **operazioni eseguibili sui dati**.
	*Le componenti strutturali e manipolative vengono concretizzate in SQL con il DDL e DML, vedremo a breve.*
	
- **Livelli del modello dei dati:** 
	I **dati** di un **database** non vengono semplicemente memorizzati tutti insieme. 
	Un **DBMS**, al fine di rispettare i tre criteri che avevamo indicato prima: 
	 - **Accesso concorrente;**
	- **Ridondanza e coerenza dei dati;**
	- **Affidabilità.**
	
	deve **organizzare** i **dati** in modo **strutturato e coerente**, nei DMBS SQL, in tre livelli:
	 
	 - **Modello Concettuale:** livello più alto, permette di **rappresentare** i **dati indipendentemente dal sistema**. Permette di rappresentare i **requisiti** di una **esigenza** e trasformarlo nel modello successivo, il **Modello Logico**. 
	   Per la rappresentazione delle relazioni tra i dati si usa il modello **UML** . 
	    
	- **Modello Logico:** riflette l'**organizzazione dei dati** in maniera più **strutturata**, utilizzando nei DBMS di tipo SQL, le **Tabelle** e le **relazioni tra di esse**.
	  Il modello logico **descrive** i concetti di **entità, attributi e relazioni**, considerando vincoli di integrità e tipologie di dati.
	  Per passare al modello successivo, il **Modello Relazionale**, si utilizza un modello intermedio, noto come **Modello Logico-Relazionale**. 
	
	- **Modello Relazionale:** **concretizza** il **Modello Logico**, si basa sul **costruttore relazione** che permette di **organizzare i dati** in **insiemi di "record" omogenei**, composti da **righe e colonne**, dove:
		  - **Colonne**: rappresentano il **tipo di informazione** (attributi);
		  - **Righe**: rappresentano i **record**, le unità complete di dati.
	 Permette di utilizzare degli **operatori per la manipolazione dei dati**. 

- **Architettura di un DBMS:** 
	Abbiamo visto come un DBMS organizza i dati in tre livelli, vediamo adesso com'è effettivamente organizzato il DBMS nel complesso, in tre **schemi** o **livelli**:
	
	- **Schema logico:** è la **struttura complessiva** della **base di dati**, coincide con il **livello Logico** del DB, è composto dalle **tabelle, relazioni, vincoli, chiavi,** etc.), è il cuore del DBMS ed è **indipendente dall'hardware**.
	  
	- **Schema interno:** è la **struttura fisica** del DBMS, descrive come vengono **memorizzati i dati sul disco**, utilizzando **indici, blocchi, pagine, formati di file**, etc. 
	  
	- **Schema esterno:** è la **visione personalizzata** dei dati, visibile e generalmente **diversa per ogni utente**. Questo schema, a differenza del **livello logico e fisico**, è opzionale, dipende esclusivamente dal tipo di esigenza. 
	
	Questi **schemi** o **livelli** devono avere una **Indipendenza Logica (e fisica)**, in quanto i **livelli superiori** non debbono essere **influenzati** da **cambiamenti nei livelli inferiori**.
	Quindi:
	-  Al **livello logico**, è possibile poter cambiare il **modello logico** quindi modificare **tabelle, relazioni**, etc. senza dover **modificare** i **programmi applicativi** o le **viste**.
	  Esempio:
		*Cambiare il nome di una colonna o aggiungere una nuova tabella, non influiscono sul funzionamento dell'applicazione.*
	- Al **livello fisico**, cambiare la **rappresentazione fisica**, quindi **file, indici, struttura su disco**, non modifica il **modello logico**.
	  Ad esempio:
		*Cambiare la memorizzare dei dati da un disco HDD ad un altro, magari SSD, o l'aggiunta di un indice, non influisce sul modello logico.*


- Una **"vista"** è una **Tabella Virtuale** (v-table o virtual table), permette di **mostrarci solamente i dati che ci interessano** e di mettere in **relazione** diverse **tabelle reali** del database.
  Possiamo fare per esempio: 
	   - Creare una **tabella virtuale derivata** da una **tabella reale**, con delle colonne ridotte e mostrarci solo le informazioni interessate;
	- Combinare altre tabelle e le relative colonne, per ottenere delle informazioni che ci interessano, senza duplicarle fisicamente.  

- **Linguaggi per la gestione di un DB:**
	Per **manipolare i dati** di un DBMS distinguiamo due linguaggi:
	- **DDL (Data-Definition Language):** si occupa della definizione di **attributi, classi, records**.
	- **DML (Data-Manipulation Language):** **interrogazioni** (Query) al DBMS, **gestione delle informazioni**: attributi, classi, records.

- **Il modello relazionale dei dati:**
	Un **modello relazionale dei dati** è un insieme di **meccanismi di astrazione**, simili alle strutture dati nella programmazione, per **definire una base di dati**.
	Il **modello relazionale** è composto da un **insieme** predefinito di **operatori** e di **vincoli di integrità**, necessari per garantire la **coerenza** e la **correttezza** dei dati.
	
	Viene introdotto nel 1970 da Edgar F. Codd, viene diffuso nei DMBS commerciali nel **1982**.
	Esso implementa il **concetto di Indipendenza dei dati**, ed è tutt'oggi, il **modello di dati più diffuso**.

- Esempio di relazione matematica:
	*Siano i due insiemi:*
	$A =$ { $a , b$ }
	$B =$ {$x,y,z$}
	
	*Possiamo calcolare il **prodotto cartesiano** $A$ $×$ $B$, ottenendo tutte le possibili coppie ordinate:*
	| $a$ $x$ |
	| $a$ $y$ |
	| $a$ $z$ |
	| $b$ $x$ |
	| $b$ $y$ |
	| $b$ $z$ |
	*Una **relazione $r$** appartenente a $A$ $×$ $B$ può essere, ad esempio:*
	| $a$ $x$ |
	| $b$ $y$ |
	| $b$ $z$ |
								
- Gli insiemi $A$ e $B$ sono chiamati **"Domini dell'Insieme"**. 
  Ogni **dominio** rappresenta un **tipo di dato distinto** e presenta un **ruolo differente** in base alla nella **"tupla"**.
	*Esempio:* 
	Siano presi in considerazione i due dati: *"Mario", "Maria"*.
	- Se le colonne non hanno attributi che le descrivono non è possibile distinguere il significato, se per esempio abbiamo una coppia ***nome*** e ***cognome***, come capiamo chi è il primo e qual è il secondo?
	  
	- Se invece, aggiungiamo un nome ad ogni dominio otteniamo una Struttura non posizionale, dove posso scambiare le colonne senza creare ambiguità di alcun tipo.

| $Nome$ | $Cognome$ |
| ------ | --------- |
| Mario  | Maria     |

----

Un modello dei dati permette di organizzare i dati di interesse e descriverne la struttura. 
Ogni modello di dati fornisce dei meccanismi di strutturazione i quali permettono di definire nuovi tipi sulla base di tipi predefiniti e costruttori di tipo.
Il modello relazionale è il modello più diffuso e più interessante a livello didattico, permette infatti di definire tipi per mezzo del **costruttore relazione**, il quale, a sua volta, permette di organizzare i dati in insiemi di record a struttura fissa. 
Una relazione viene generalmente rappresentata, come nel modello relazionale, per mezzo di una tabella, in cui:
- righe rappresentano specifici record o n-uple;
- colonne corrispondono ai campi dei record.
L'ordine delle righe e delle colonne è sostanzialmente irrilevante.

Oltre al modello relazione, che è il più diffuso e preso come modello di riferimento didattico, esistono altri tipi di modelli:
- **Modello gerarchico**: basato su strutture ad albero.
- **Modello reticolare** (o **CODASYL**): basato sull'uso di grafi, sviluppato successivamente al modello gerarchico.
- **Modello a oggetti**: sviluppato come evoluzione del modello relazionale, estendendo alle basi di dati, il paradigma della programmazione ad oggetti (Object Oriented Programming, OOP).
- **Modello XML:** nasce come rivisitazione del modello gerarchico, i dati vengono presentati insieme alla loro descrizione e non devono sottostare rigidamente ad un'unica struttura logica, per questo motivo si dice che il modello XML è "auto-descrittivo" e "semi-strutturato".
- **Modelli semi-strutturati**: sviluppati nel contesto del **NoSQL**, che cerca di superare in specifici contesti applicativi, alcune delle limitazioni dei modelli relazionali, sia in termini di prestazione che rigidità di organizzazione dei dati.
Tutti questi modelli sono disponibili su DBMS commerciali e vengono definiti **Modelli logici** per sottolineare che, le strutture utilizzate per questi modelli, pur essendo astratte, riflettono una particolare organizzata (ad alberi, a grafi, a tabelle o ad oggetti). 
Più recentemente ai **modelli logici**, sono stati introdotti altri modelli di dati, detti "**Modelli concettuali**", utilizzati per descrivere i dati in maniera completamente indipendente dalla scelta del modello logico. Sono modelli utilizzati solo a livello di progettazione delle basi di dati, utili ad analizzare nel miglior modo, la realtà di interesse, senza limitazioni dei modelli logici, dunque, senza limitazioni di tipo realizzativo. 

[...]

----

# 2) Il modello relazionale

Il modello relazionale si basa su due concetti: relazione e tabella, dove la nozione di relazione deriva dalla teoria degli insiemi, mentre quello di tabella è intuitivo.
Il modello relazionale risponde alla necessità dell'indipendenza dei dati, prevedendo una distinzione, nella descrizione dei dati, fra livello fisico e livello logico. 
Gli utenti e i programmatori che sviluppano le applicazioni, fanno riferimento solamente al livello logico, infatti i dati descritti al livello logico sono poi organizzati per mezzo di strutture fisiche, le quali, per accedervi non è necessario conoscerle. 

In matematica, dati due insiemi $D_1$ e $D_2$ (chiamati **domini** della relazione), il prodotto cartesiano di $D_1$ e $D_2$ si scrive $D_1 \times D_2$ e produce l'insieme delle coppie ordinate $(v_1,v_2)$, dove $v_1 \in D_1$ e $v_2 \in D_2$.   
$$\{(v_1,v_2) \; | \; v_1 \in D_1 , v_2 \in D_2\}$$

Per esempio, $A = \{1,2,4\}$ e $B = \{a,b\}$, il prodotto cartesiano $A \times B$ è costituito dall'insieme delle coppie:
$$\{ (1,a), (1,b), (2,a), (2,b), (4,a), (4,b) \}$$

| $D_1 \times D_2$ |     |
| ---------------- | --- |
| 1                | a   |
| 1                | b   |
| 2                | a   |
| 2                | b   |
| 4                | a   |
| 4                | b   |
Dati i due insiemi $A$ e $B$ una possibile relazione matematica sui due insiemi potrebbe essere l'insieme delle coppie $\{(1,a),(1,b),(4,b)\}$.
Le possibilità di insiemi sono infinite e, anche se le basi di dati avendo un limite alla memorizzazione dei dati, sono necessariamente finite, a livello teorico si possono comunque assumere anch'esse come infinite. 

Dati $n>0$ insiemi $D_1, D_2, ..., D_n$ non necessariamente distinti, il prodotto cartesiano $D_1, D_2, ..., D_n$ , è costituito dall'insieme delle n-uple (o ennuple) $(v_1, v_2, ..., v_n)$ tali che, $v_i \in D_i$ per $1 \leq i \leq n$ . 
Una relazione matematica sui domini $D_1, D_2, ..., D_n$ è un sottoinsieme del prodotto cartesiano $D_1 \times D_2 \;\times\; ... \; \times\; D_n$ 

- Il numero delle colonne della relazione è definito **"Grado della relazione"**. 
- Il numero di elementi, cioè il numero di ennuple della relazione, viene chiamato **"Cardinalità della relazione"**. 

Nel modello relazionale non è definito alcun ordinamento fra le ennuple, difatti, due tabelle con le stesse righe ma in ordine diverso rappresentano la stessa relazione. 
Senza un'opportuna ridenominazione delle colonne, allora l'ordinamento farebbe la differenza, questo tuttavia è un comportamento indesiderato, ragion per cui nel modello relazionale ad ogni Dominio bisogna assegnarvi un nome, detto **attributo**. 


- **Univocità delle righe** (o dei **record**):
	Le ennuple di una relazione devono essere distinte l'una dall'altra, non è possibile averne due uguali fra loro, vedremo l'utilizzo di **identificatori univoci**. 
	Di base i record possono avere valori in comune, una persona può condividere nome e cognome con un'altra, si tratta di un caso di omonimia, senza una corretta gestione di identificatori univoci, queste due persone potrebbero essere trattate come un'unica entità dal DB. 

Uno schema relazionale è costituito da un simbolo $R$ detto **nome della relazione**, e da un insieme di attributi $X = \{A_1,A_2,...,\;A_n\}$, indicato $R(X)$.
- Ciascun **attributo** $A_i$ è associato ad un **dominio**.
- Uno schema di base di dati è un insieme di schemi di relazione, quindi, possiamo scrivere: $$R = \{R_1(X_1), R_2(X_2),...,R_n(X_n)\}$$
- I nomi delle relazioni hanno lo scopo principale di distinguere le diverse relazioni della base di dati.
- Un'**istanza di relazione** (o solo relazione) su uno schema $R(X)$ è dunque l'insieme di tuple 
  $r$ su $X$. Indicato $r(X)$.  
- Un'**instanza di base di dati** su uno **schema** $R = \{R_1(X_1), R_2(X_2),...,R_n(X_n)\}$ è un insieme di relazione **r** $= \{r_1,r_2,...,r_n\}$, dove ogni $r_i$ per $1\leq i \leq n$ è una relazione sullo schema $R_i(X_i)$. 

Esempio: 
$$R = \{R_1(X_1), R_2(X_2),...,R_n(X_n)\}$$ R = {
		Studenti(Matricola, Cognome, Nome, Data di nascita),
		Esami(Studente, Voto, Corso),
		Corsi(Codice, Titolo, Docente)  
	}

Rappresentato in delle tabelle:

| Studenti  |      |         |             |
| --------- | ---- | ------- | ----------- |
| Matricola | Nome | Cognome | DataNascita |

| Esami    |      |       |
| -------- | ---- | ----- |
| Studente | Voto | Corso |

| Corsi  |        |         |
| ------ | ------ | ------- |
| Codice | Titolo | Docente |
I quali fanno tutti parte del mondo R. 

I dati da rappresentare in una base di dati variano a seconda degli specifici obiettivi prefissati. 

___

#### Informazioni incomplete e valori nulli

Le informazioni devono essere rappresentate per mezzo di tuple di dati omogenee, ogni relazione può rappresentare solo tuple corrispondenti allo schema della relazione stessa, tuttavia, in molti casi i dati disponibili possono non corrispondere esattamente al formato previsto. 
Un dato può avere:
- valore sconosciuto;
- valore inesistente;
- senza informazione (ignoto se sconosciuto o inesistente)
Per rappresentare questi casi viene utilizzato un valore speciale detto **valore nullo** $NULL$. 

Preso la tabella dall'esempio precedente, potremmo voler aggiungere un nuovo attributo:

| Studenti  |       |         |             |                                          |
| --------- | ----- | ------- | ----------- | ---------------------------------------- |
| Matricola | Nome  | Cognome | DataNascita | Telefono                                 |
| 1009384   | Mario | Rossi   | 23-04-2001  | +39 394021923                            |
| 1094503   | Emma  | Marroni | 24-12-2004  | +39 456123987                            |
| 1090345   | Luigi | Verdi   | 02-12-1998  | <span style = "color: red"> NULL </span> |
Quando viene definita una relazione è opportuno specificare quali attributi ammettano valori nulli, tenendo bene in considerazione, che i valori nulli potrebbero rendere difficile, se non impossibile, l'esistenza di quella informazione nel database, è infatti necessario ridurre il numero di valori nulli al minimo.

----

#### Vincoli di integrità 

I vincoli di integrità stabiliscono quali situazioni non possono essere ammesse nel database, sostanzialmente dettano le regole da rispettare. 
Per esempio, si potrebbe avere la necessità di memorizzare su una tabella esami verbalizzati, i voti degli studenti di un corso di laurea.
Troviamo evidente che non ci possano essere voti al disotto di 18, tantomeno sopra il 30 (31 se lo si vuole considerare come indicatore di un 30 e lode).

Dunque, possiamo dire che, il vincolo di integrità detta le proprietà che devono essere soddisfatte dalle istanze che rappresentano informazioni corrette per l'applicazione. 
Ogni vincolo può essere visto come un predicato che associa ad ogni istanza, il valore **vero** o **falso**. 
Se il **predicato** è **vero**, allora l'istanza **soddisfa** il vincolo.

Ad uno schema di base di dati viene generalmente associato un'insieme di vincoli e vengono considerate corrette o ammissibili, tutte quelle istanze che soddisfano tutti i vincoli.

I vincoli di integrità si differenziano in due categorie: 
- **Intrarelazionale:** se il suo soddisfacimento è definito rispetto a singole relazioni, talvolta il coinvolgimento riguarda le tuple o addirittura i **valori**, allora parliamo nel primo caso di **vincolo di tupla**, nel secondo di **vincoli su valori (o dominio)**: 
	- **Vincolo di tupla:** è un vincolo valutato su ciascuna tupla indipendentemente alle altre.
		  es. 
			  - voto pari a 36: inammissibile;
			  - 28 e lode: inammissibile;
			  - due studenti diversi con la stessa matricola: inammissibile. -> utilizzo di identificatori univoci, detti **superchiave** o **chiave**. 
	- **Vincolo su valori** (o vincolo di **dominio**): vincolo definito con riferimento a singoli valori, impone una restrizione sul dominio dell'attributo.
		   es. 
			   - voti nell'attributo Voto sono compresi solamente tra 18 e 30 *(31 se lo si considera come 30 e lode)* 
- **Interrelazionale:** se il suo soddisfacimento coinvolge più relazioni.
		es. 
		    - Riferimento errato: presenza di uno studente nella tabella Esami, che tuttavia non esiste nella tabella Studenti. Indesiderabile.  

#### Chiave e vincoli di chiave:
- Un insieme $K$ di attributi è **superchiave** di una relazione $r$ se e solo se $r$ non contiene due tuple distinte $t_1$ e $t_2$ tali che $t_1[K] = t_2[K]$. 
- $K$ si dice essere **superchiave minimale** di $r$ se non esiste un'altra superchiave $K'$ di $r$ che sia contenuta in $K$ come sottoinsieme proprio.
- $K$ è **chiave** di $r$ se questa è **superchiave minimale**.

	Potrebbe capitare che in una tabella, di avere gli di attributi, ad esempio coppia nome e cognome, tutti univoci; tuttavia, una base di dati deve essere progettata al fine di non incorre mai in situazioni che violino i vincoli di integrità.

	**Ogni relazione ha sempre una chiave** e per **ciascuno schema di relazione** l'**insieme di tutti gli attributi è superchiave** per ogni relazione.
	Inoltre, poiché ogni relazione è un insieme di elementi fra loro diversi, per ogni relazione
    $r(X)$, l'insieme $X$ di tutti gli attributi su cui è definita la chiave è senz'altro una superchiave per essa.
	Ci sono due scenari:
	1. L'insieme è chiave, quindi è confermata esistenza della chiave;
	2. L'insieme non è chiave, in questo contiene un'altra superchiave, allora procediamo ricorsivamente.
I valori attraverso cui vengono stabilite le corrispondenze fra tuple di relazioni diverse sono valori delle chiavi delle relazioni cui si fa riferimento dall'esterno.  

Una chiave non ammette valori nulli.
- Gli attributi che costituiscono la chiave primaria vengono solitamente evidenziati con la sottolineatura. 
- La maggior parte dei **riferimenti tra relazione** avviene **attraverso** i valori della **chiave primaria**. 
- In quasi tutti i casi è possibile trovare attributi i cui valori sono utili alla identificazione univoca, quando ciò non accade, è necessario introdurre un attributo aggiuntivo, per esempio un 
  **codice**, non necessariamente significativo dal punto di vista dell'applicazione, generato e attribuito a ciascuna tupla all'atto dell'inserimento, *es. matricola studente, il codice fiscale, numero di targa, etc.*
- Una **chiave** non può <u>MAI</u> avere **valore nullo**.

Non tutti i sistemi DBMS sul mercato permettono di indicare esplicitamente la chiave primaria.

---

#### Vincoli di integrità referenziale (vincoli interrelazionali):

Un vincolo di integrità referenziale, in inglese, **referential integrity constraint** o semplicemente conosciuto come **"Foreign key"** e tradotto in **"Chiave esterna"**.
Preso un'insieme di attributi $X$ di una relazione $R_1$ e un'altra relazione $R_2$ il vincolo di integrità referenziale è soddisfatto se i valori su $X$ di ciascuna tupla dell'istanza di $R_1$ compaiono come valori della **chiave (primaria)** dell'istanza $R_2$. 
Nel dettaglio:
1. Chiave di $R_2$ è unica e composta da un solo attributo $B$, allora il **vincolo di integrità referenziale** fra l'attributo $A$ di $R_1$ e la relazione $R_2$ è soddisfatto se e solo se:
   per ogni tupla $t_1$ in $R_1$ per cui $t_1[A]$ non è nullo, esiste una tupla $t_2$ in $R_2$ tale che $t_1[A] = t_2[B]$.
2. Nel caso di più chiavi di $R_2$ composte da attributi di $R_1$ il procedimento è analogo, con il controllo su ogni chiave. 

 In relazioni con più chiavi è opportuno indicare una delle chiavi come primaria e che i riferimenti siano diretti verso di essa. 

---------------

# 3) Algebra e calcolo relazionale

Le basi di dati, come abbiamo visto, vengono utilizzate per rappresentare informazioni di interesse per le applicazioni che gestiscono dati, dunque i linguaggi che ne specificano le operazioni (di interrogazione e aggiornamento) costituiscono una componente essenziale.
- Un aggiornamento è una funzione che, data un'istanza di base di dati, produce un'altra istanza di base di dati, sullo stesso schema;
- Un'interrogazione invece, prende anch'esso un'istanza di base di dati e produce una relazione su un dato schema.

L'**algebra relazionale** è un **linguaggio procedurale**, basato su concetti di tipo **algebrico**, in cui le operazioni complesse vengono specificate descrivendo il procedimento da seguire per ottenere la soluzione. 

Il **calcolo relazionale**, invece, è un **linguaggio dichiarativo**, in cui le espressioni **descrivono le proprietà del risultato**, piuttosto che la procedura per ottenerlo.  
Questo linguaggio si basa sul **calcolo dei predicati del primo ordine**, e presenta due versioni:
1. la prima derivata direttamente dal calcolo dei predicati;
2. la seconda cerca di superare le limitazioni della prima

Vedremo poi dal punto di vista pratico, con il linguaggio SQL come possa risultare utile combinare gli aspetti dichiarativi del calcolo a quelli procedurali dell'algebra.

---

## Algebra relazionale:

Come abbiamo anticipato, l'**algebra relazionale** è un **linguaggio procedurale**, basato su concetti di tipo **algebrico**, in cui le operazioni complesse vengono specificate descrivendo il procedimento da seguire per ottenere la soluzione. 
Il **linguaggio** è **costituito** da un **insieme di operatori**, definiti su **relazioni che producono ancora relazioni come risultati**, in questo modo è **possibile costruire espressioni** che **coinvolgono più operatori**, allo **scopo** di formulare **interrogazioni più complesse**.

Operatori dell'algebra relazionale:
- Operatori insiemistici: unione ($\cup$) , intersezione ($\cap$), differenza ($-$)
- ( $\large\rho^1$ ) Ridenominazione   
- ( $\large\sigma^2$ ) Selezione
- ( $\Pi^3$ ) Proiezione
- Operatori di join ($\bowtie$): 
    - join naturale (natural join);
    - prodotto cartesiano
    - semijoin
    - theta-join
    - equi-join
- Divisione (operatore ridondante).

*$^1$ Simbolo greco "rho" ($\rho$).*
*$^2$ Simbolo greco "sigma" minuscolo $\sigma$.*
*$^3$ Simbolo greco "Pi" maiuscolo $\Pi$ diverso da quello minuscolo $\pi$.*  

----

### Operatori insiemistici: unione, intersezione, differenza:

Le **relazioni** sono insiemi quindi ha senso che esistano **operatori insiemistici tradizionali** come **unione**, **differenza** e **intersezione**.
Una **relazione** è un **insieme di tuple omogenee**, quindi **definite sugli stessi attributi**, dunque questi **operatori non possono essere definiti su qualunque coppia di relazioni** perché non avrebbe senso dal punto di vista del modello relazionale. 
Dunque, **nell'algebra relazionale sono considerati ammissibili** solamente le **applicazioni** **degli operatori insiemistici a coppie di operandi** **definite** sugli **stessi attributi**.
Vediamo adesso le operazioni:

- **Unione ($\cup$):**
  L'unione di due relazioni $r_1$ e $r_2$ definite sullo stesso insieme di attributi $X$ è indicata con $$r_1 \cup r_2$$questa è una relazione ancora su $X$ contenente le tuple che appartengono a $r_1$ o $r_2$ oppure ad entrambe.
  
- **Intersezione ($\cap$):**
  L'intersezione di $r_1(X)$ e $r_2(X)$ è indicata con: $$r_1 \cap r_2$$ relazione contenente le tuple in comune a $r_1$ e $r_2$. 
  
- **Differenza ($-$):**
  La differenza di $r_1(X)$ e $r_2(X)$ è indicata con: $$r_1 - r_2$$
  è una relazione contenente le tuple che appartengono a $r_1$ e <u>NON</u> appartengono a $r_2. 

---
  
### Ridenominazione ($\rho$): 
La ridenominazione è particolarmente utile, non solo per la sua proprietà intrinseca di cambiare il nome di un attributo, ma soprattutto per rendere gli elementi facilmente manipolabili attraverso le operazioni insiemistiche, rendendo infatti, due attributi con nome diverso di due diverse tabelle, uguale, per permettere le operazioni insiemistiche e lasciando inalterato il contenuto delle relazioni. 
Per esempio: 
Prese due relazioni, la prima composta dagli attributi Padre, Figlio e la seconda composta da Madre, Figlio, sarebbe impossibile operarvi se non ridenominando le tabelle.

| Paternità |         |
| --------- | ------- |
| Padre     | Figlio  |
| Adamo     | Caino   |
| Adamo     | Abele   |
| Abramo    | Isacco  |
| Abramo    | Ismaele |

| Maternità |         |
| --------- | ------- |
| Madre     | Figlio  |
| Eva       | Caino   |
| Eva       | Set     |
| Sara      | Isacco  |
| Agar      | Ismaele |

Vogliamo unire madre e padre nello stesso attributo: Genitore.
Allora rinominiamo sia "Padre" che "Madre" in "Genitore", dunque facciamo l'unione delle due tabelle: 

In algebra relazionale scriviamo il nuovo nome da assegnare, puntata da una freccia con l' attributo da rinominare :

$\large \rho_{Genitore\;\leftarrow\; Padre}$ (Paternità)

| Genitore | Figlio  |
| -------- | ------- |
| Adamo    | Caino   |
| Adamo    | Abele   |
| Abramo   | Isacco  |
| Abramo   | Ismaele |
Stessa cosa per la Madre:
$\large \rho_{Genitore\;\leftarrow\; Madre}$ (Maternità) 

| Genitore | Figlio  |
| -------- | ------- |
| Eva      | Caino   |
| Eva      | Set     |
| Sara     | Isacco  |
| Agar     | Ismaele |

e procediamo con l'unione delle due relazioni ottenute:
$\large \rho_{Genitore\;\leftarrow\; Padre}$ (Paternità) $\cup$ $\large \rho_{Genitore\;\leftarrow\; Madre}$ (Maternità) 

| Genitore | Figlio  |
| -------- | ------- |
| Adamo    | Caino   |
| Adamo    | Abele   |
| Abramo   | Isacco  |
| Abramo   | Ismaele |
| Eva      | Caino   |
| Eva      | Set     |
| Sara     | Isacco  |
| Agar     | Ismaele |

È possibile ridenominare più attributi allo stesso tempo, semplicemente dividendoli in ordine, con una semplice virgola. 
Ad esempio:

**Impiegati:**

| Cognome | Agenzia | Stipendio |
| ------- | ------- | --------- |
|         |         |           |
$\large\rho_{Sede,\; Retribuzione\; \leftarrow\; Agenzia, \; Stipendio}$ (Impiegati) 
Diventando quindi:

| Cognome | Sede | Retribuzione |
| ------- | ---- | ------------ |
|         |      |              |

---

### Selezione

La selezione produce un sottoinsieme delle tuple, su tutti gli attributi, generando delle "decomposizioni orizzontali", l'operatore è denotato dal simbolo greco sigma $\large\sigma$ , dove al suo pedice troviamo la "**condizione di selezione**", che ci permette di ottenere una relazione in cui la condizione è soddisfatta.
- Le condizioni di selezione possono prevedere confronti fra attributi e confronto fra attributi e costanti. 
- Accetta gli operatori di confronto: ( $=,\;\neq,\;\;<,\;>,\;\leq,\;\geq$ ).
- Possibile svolgere più operazioni, quindi più confronti, utilizzando operatori: ( $\land,\,\lor$ ).
- Ammesso anche l'operatore di negazione ( $\neg$ ).
*Ad esempio:*
- **Fra attributi**: $prezzo > costo$ *(dove sia prezzo che costo sono attributi)*;
- **Fra attributi e costanti**: $prezzo > 40$.

In generale, la selezione è definita: $\Large \sigma_F$$\large(r)$, dove:
- Sigma ($\large\sigma$) è l'operatore di selezione;
- **F** è una formula proposizionale condizionale;
- **r** è una relazione;
- il risultato della selezione produce una relazione sugli stessi attributi di **r** che soddisfano la proposizione **F**. 

| Impiegati |         |             |           |
| --------- | ------- | ----------- | --------- |
| Nome      | Cognome | AnnoNascita | Stipendio |
| Mario     | Rossi   | 1998        | 1800      |
| Luigi     | Verdi   | 1978        | 2500      |
| Emma      | Marroni | 2001        | 1900      |
| Nicola    | Gialli  | 2004        | 2150      |
| Veronica  | Neri    | 1989        | 2700      |
Vogliamo sapere chi guadagna più di 1900 euro.

$\large\sigma_{Stipendio>1900}$(Impiegati)

| Impiegati |         |             |           |
| --------- | ------- | ----------- | --------- |
| Nome      | Cognome | AnnoNascita | Stipendio |
| Luigi     | Verdi   | 1978        | 2500      |
| Nicola    | Gialli  | 2004        | 2150      |
| Veronica  | Neri    | 1989        | 2700      |

Vogliamo sapere anche chi tra loro abbia almeno 30 anni, dunque:

$\large\sigma_{Stipendio\,>\,1900\; \land\; 2025\,-\,AnnoNascita\,\geq\, 30}$ (Impiegati)

*2025 si intende come anno corrente, nel linguaggio per le interrogazioni si utilizzerà poi un modo più accurato.*

| Impiegati |         |             |           |
| --------- | ------- | ----------- | --------- |
| Nome      | Cognome | AnnoNascita | Stipendio |
| Luigi     | Verdi   | 1978        | 2500      |
| Veronica  | Neri    | 1989        | 2700      |

----

### Proiezione

La proiezione permette di "**decomporre verticalmente" le relazioni**, ciò vuol dire, la tabella mostra tutti i suoi record, tuttavia soltanto con gli attributi che ci interessano proiettare. 
Dati una relazione $r(X)$ e un sottoinsieme  $Y$ di $X$, la **proiezione** di $r$ su $Y$ è indicata come
$$\large\Pi_Y(r)$$ contiene l'insieme di tuple su $Y$ ottenute dalle tuple di $r$, considerando solo i valori su $Y$:
$$\large\Pi_Y(r) = \{\,t[Y]\;|\;t\in r\,\}$$
Il risultato di una proiezione può contenere lo stesso o un numero inferiore di tuple rispetto a quelle dell'operando, il secondo caso avviene quando i valori di alcune **tuple sono uguali su tutti gli attributi della proiezione**. 
Il numero di tuple del **risultato** della **proiezione** sarà SEMPRE **uguale** a quello dell'operando, nel caso in cui venga **proiettato** ALMENO la **chiave della relazione**, in quanto ogni tupla rimarrà univocamente distinta dalle altre.
Esempi:

| Impiegati                                |                                          |             |           |
| ---------------------------------------- | ---------------------------------------- | ----------- | --------- |
| Nome                                     | Cognome                                  | AnnoNascita | Stipendio |
| <span style= "color: red"> Mario </span> | <span style= "color: red"> Rossi </span> | 1998        | 1800      |
| Luigi                                    | Verdi                                    | 1978        | 2500      |
| Emma                                     | Marroni                                  | 2001        | 1900      |
| Nicola                                   | Gialli                                   | 2004        | 2150      |
| Veronica                                 | Neri                                     | 1989        | 2700      |
| <span style= "color: red"> Mario </span> | <span style= "color: red"> Rossi </span> | 2003        | 1500      |
|                                          |                                          |             |           |
Eseguiamo una proiezione degli attributi nome e cognome:

$\large\Pi_{Nome,\,Cognome}$(Impiegati)

| Impiegati                                |                                          |
| ---------------------------------------- | ---------------------------------------- |
| Nome                                     | Cognome                                  |
| <span style= "color: red"> Mario </span> | <span style= "color: red"> Rossi </span> |
| Luigi                                    | Verdi                                    |
| Emma                                     | Marroni                                  |
| Nicola                                   | Gialli                                   |
| Veronica                                 | Neri                                     |
La coppia (Nome, Cognome) non è infatti sufficiente a rendere la tupla univocamente identificabile.

Aggiungendo un attributo Codice, in cui ogni codice è unico, e lo proiettiamo, la situazione è differente:

| Impiegati |          |         |             |           |
| --------- | -------- | ------- | ----------- | --------- |
| Codice    | Nome     | Cognome | AnnoNascita | Stipendio |
| 1003      | Mario    | Rossi   | 1998        | 1800      |
| 2032      | Luigi    | Verdi   | 1978        | 2500      |
| 1034      | Emma     | Marroni | 2001        | 1900      |
| 1234      | Nicola   | Gialli  | 2004        | 2150      |
| 4321      | Veronica | Neri    | 1989        | 2700      |
| 2834      | Mario    | Rossi   | 2003        | 1500      |
$\large\Pi_{Codice,\,Nome,\,Cognome}$(Impiegati)

| Impiegati |          |         |
| --------- | -------- | ------- |
| Codice    | Nome     | Cognome |
| 1003      | Mario    | Rossi   |
| 2032      | Luigi    | Verdi   |
| 1034      | Emma     | Marroni |
| 1234      | Nicola   | Gialli  |
| 4321      | Veronica | Neri    |
| 2834      | Mario    | Rossi   |

O anche semplicemente:
$\large\Pi_{Codice}$(Impiegati)

| Impiegati |
| --------- |
| Codice    |
| 1003      |
| 2032      |
| 1034      |
| 1234      |
| 4321      |
| 2834      |
Anche il solo attributo **Codice** sarebbe sufficiente a distinguere ogni tupla.


---

### Join 

Il join è l'operatore che permette di correlare dati contenuti in relazioni diverse, sulla base di valori uguali in attributi con lo stesso nome. L'operatore è denotato con il simbolo $\large\bowtie$. 

Esistono alcune varianti di join:
- Join (natural join), utile per riflessioni di tipo astratto
- Theta-Join più rilevante dal punto di vista pratico

Il **risultato del join** è costituito da una **relazione sull'unione degli insiemi di attributi degli operandi** e le sue tuple sono ottenute combinando le tuple degli operandi con valori uguali sugli attributi comuni. 

Il join naturale di due relazioni $\large r_1(X_1)$ e $\large r_2(X_2)$ si scrive $\large r_1 \bowtie r_2$ ed è una relazione definita sull'unione degli insiemi $X_1$ e $X_2$ (semplicemente $X_1X_2$). 
$$\large r_1 \bowtie r_2 = \{\,t\; su\; X_1X_2 \; | \; \exists \,t_1 \in r_1 \;\; e \;\; t_2 \in r_2 \; | \; t[X_1] = t_1 \;\;e\;\; t[X_2] = t_2\,\}   $$
							oppure:

$$\large r_1 \bowtie r_2 = \{\,t\; su\; X_1X_2 \; | \;t[X_1] \in r_1 \;\; e \;\; t[X_2] \in r_2\,\}   $$
Le tuple del risultato sono ottenute combinando tuple degli operandi con valori uguali sugli attributi comuni, cioè presi gli attributi comuni $X_{1,2}$ allora  $X_{1,2} = X_1 \cap X_2$ .

- Grado di relazione join:
	Il grado della relazione ottenuta come risultato di un join è minore o uguale alla somma dei gradi dei due operandi, come visto prima, due attributi omonimi appaiono solo una volta nel risultato. 

Scrivere $r_1 \bowtie r_2$ oppure $r_2 \bowtie r_1$ in una **natural join** è la stessa cosa (commutativo); analogamente,  $r_1 \bowtie (r_2 \bowtie r_3)$ è uguale a dire: $(r_1 \bowtie r_2) \bowtie r_3$ (associativo). 

*Esempio di join naturale:*

$\large r_1$

| Impiegato | Reparto    |
| --------- | ---------- |
| Rossi     | vendite    |
| Neri      | produzione |
| Bianchi   | produzione |
$\large r_2$ 

| Reparto    | Capo  |
| ---------- | ----- |
| produzione | Mori  |
| vendite    | Bruni |
$\large r_1 \bowtie r_2$

| Impiegato | Reparto    | Capo  |
| --------- | ---------- | ----- |
| Rossi     | vendite    | Bruni |
| Neri      | produzione | Mori  |
| Bianchi   | produzione | Mori  |

Vediamo come Reparto appare una sola volta nella join anche se entrambe le relazioni lo includevano.

----

### Join completi e incompleti:

Una join si dice completa se per ogni tupla $\large t_1$ di $\large r_1$, esiste una tupla $\large t$ in $\large r_1 \bowtie r_2$ tale che:
$t[X_1] = t_1$ e $t[X_2] = t_2$ .
Questa proprietà non è sempre verificata perché richiede una corrispondenza fra le tuple delle due relazioni.
- **Join vuoto:**
	Nel caso in cui alcune tuple degli operandi non sono in comune, allora queste non contribuiranno al risultato, e vengono chiamate *dangling* (dondolanti), pertanto, esiste anche il caso limite che nessuna tupla sia in comune tra le due relazioni $r_1$ e $r_2$ , risultando così in una relazione $\large r_1 \bowtie r_2$ vuota. 
- **Prodotto cartesiano:**
	All'estremo opposto della relazione vuota, troviamo il caso in cui, ciascuna delle tuple di ciascuno degli operandi sia combinabile con tutte le tuple dell'altro, risultando dunque in una relazione avente un numero di tuple pari al prodotto delle cardinalità degli operandi delle due relazioni. 

- Cardinalità di una join:
	Dunque una join tra due relazioni $r_1$ e $r_2$ può contenere un **numero di tuple** compreso tra 
	**0 e $|r_1| \times |r_2|$** . 
	In particolare:
	- Se la join di $r_1$ e $r_2$ è **completo** allora contiene almeno un numero di tuple pari al MASSIMO fra $|r_1|$ e $|r_2|$, dunque $max(|r_1|, |r_2|)$ . 
	- Se $X_1 \cap X_2$ **contiene una chiave** per $r_2$, allora il join di $r_1(X_1)$ e $r_2(X_2)$ contiene al **massimo** $|r_1|$ tuple.
	- Se $X_1 \cap X_2$ **coincide con una chiave** per $r_2$ e **sussiste il vincolo di riferimento** tra $X_1 \cap X_2$ e la chiave di $r_2$ allora il join contiene **ESATTAMENTE** $|r_1|$ tuple.

 ----

### Join esterno:

La caratteristica del join di tralasciare le tuple di una relazione che non compaiono nell'altra relazione è una caratteristica del join ma che, tuttavia, può essere pericoloso in alcuni casi, omettendo informazioni rilevanti. 
Per questo motivo esiste una variante dell'operatore join, detto join esterno o **outer join**, che prevede che tutte le tuple che non contribuiscono al risultato siano estese con valori nulli, in tre varianti:
1. **Left Join ($\large r_1 \bowtie_{left} r_2$)**: estende solo le tuple del primo operando, quindi preso $r_1 \bowtie r_2$, estende solo $r_1$. 
2. **Right Join ($\large r_1 \bowtie_{right} r_2$)**: estende solo le tuple del secondo operando, quindi preso $r_1 \bowtie r_2$, estende solo $r_2$.
3. **Full Join ($\large r_1 \bowtie_{full} r_2$)**: estende le tuple di entrambe le relazioni, sia $r_1$ che $r_2$ . 

Esempio: 

| Impiegato | Reparto    |
| --------- | ---------- |
| Rossi     | vendite    |
| Neri      | produzione |
| Bianchi   | produzione |

| Reparto    | Capo  |
| ---------- | ----- |
| produzione | Mori  |
| acquisti   | Bruni |

Procediamo con la Join: $\large r_1 \bowtie r_2$

| Impiegato | Reparto    | Capo |
| --------- | ---------- | ---- |
| Neri      | produzione | Mori |
| Bianchi   | produzione | Mori |
Vediamo la differenza del risultato con le varianti di join viste:

1. $\large r_1 \bowtie_{left} r_2$

| Impiegato | Reparto    | Capo                                        |
| --------- | ---------- | ------------------------------------------- |
| Rossi     | vendite    | <span style = "color: tomato"> null </span> |
| Neri      | produzione | Mori                                        |
| Bianchi   | produzione | Mori                                        |
   
2. $\large r_1 \bowtie_{right} r_2$

| Impiegato                                   | Reparto    | Capo  |
| ------------------------------------------- | ---------- | ----- |
| Neri                                        | produzione | Mori  |
| Bianchi                                     | produzione | Mori  |
| <span style = "color: tomato"> null </span> | acquisti   | Bruni |

2. $\large r_1 \bowtie_{full} r_2$

| Impiegato                                   | Reparto    | Capo                                        |
| ------------------------------------------- | ---------- | ------------------------------------------- |
| Rossi                                       | vendite    | <span style = "color: tomato"> null </span> |
| Neri                                        | produzione | Mori                                        |
| Bianchi                                     | produzione | Mori                                        |
| <span style = "color: tomato"> null </span> | acquisti   | Bruni                                       |

---

### Semi-Join:

Un **operatore derivato** dalla join è il **semi-Join**, che consiste nel **restituire le tuple** di una **relazione** che partecipano al join naturale di tale relazione con un'altra. 
Definito dal simbolo $\Large \ltimes$. 

Preso l'esempio precedente, produce dunque: 

| Impiegato | Reparto    |
| --------- | ---------- |
| Rossi     | vendite    |
| Neri      | produzione |
| Bianchi   | produzione |

| Reparto    | Capo  |
| ---------- | ----- |
| produzione | Mori  |
| acquisti   | Bruni |

Join: $\large r_1 \bowtie r_2$

| Impiegato | Reparto    | Capo |
| --------- | ---------- | ---- |
| Neri      | produzione | Mori |
| Bianchi   | produzione | Mori |

Allora la Semi-Join: $\large r_1 \ltimes r_2$ 

| Impiegato | Reparto    |
| --------- | ---------- |
| Neri      | produzione |
| Bianchi   | produzione |

Come detto infatti, si occupa di mostrare solamente le tuple $r_1$ che si trovano in relazione con quelle di $r_2$ , si potrebbe vedere come una join che proietta solo gli attributi del primo operando.

--- 

### Theta-Join:

Un prodotto cartesiano ha solitamente poca utilità, tuttavia seguito da una selezione può rivelarsi utile, ed è proprio questo il Theta-Join, un operatore derivato della Join. 
La sua formula è composta dunque dal prodotto cartesiano delle due relazioni $r_1$ e $r_2$ e da una formula proposizionale condizionale $F$, in formula: $$\large r_1 \mathop{\bowtie}_F r_2 = \sigma_F(r_1 \bowtie r_2)$$

----------

### Equi-Join: 
L'equi-join non è altro che un Theta-Join in cui la condizione di selezione $F$ è una **congiunzione di atomi di uguaglianza**, cioè: $$\large r_1 \mathop{\bowtie}_{F_1\,\land \, F_2 } r_2 = \sigma_F(r_1 \bowtie r_2)$$
Tecnicamente non ci sono limitazioni al numero di congiunzioni di atomi di uguaglianza, ma nella rappresentazione ne indichiamo simbolicamente due.


---

### Divisione:

L'operazione di divisione è poco utilizzata in quanto esprimibile per mezzo degli altri operatori e  può essere visto come **inverso del prodotto cartesiano**. 

Dati due insiemi di attributi disgiunti $X_1$ e $X_2$ , una relazione $r$ su $X_1X_2$ e una relazione $r_2$ su $X_2$ , la divisione $\large r \div r_2$ è una relazione su $X_1$ che contiene le tuple ottenute come proiezione di tuple di $r$ che si ottengono con tutte le tuple di $r_2$ per formare tuple di $r$: 
$$r \div r_2 = \{\, t_1 \in X_1 \; | \; \forall t_2 \in r \; \exists \, t \in r \; | \; t[X_1] = t_1 e t[X_2] = t_2 \, \}$$

($r_1$) Sedi e uffici:


| Filiale | Ufficio  |
| ------- | -------- |
| Roma    | Acquisti |
| Roma    | Vendite  |
| Roma    | Studi    |
| Milano  | Acquisti |
| Milano  | Vendite  |
| Milano  | Studi    |
| Napoli  | Acquisti |
| Napoli  | Vendite  |

($r_2$) Uffici:

| Ufficio  |
| -------- |
| Acquisti |
| Vendite  |
| Studi    |

$Sedi \div Uffici$ 

| Filiale |
| ------- |
| Milano  |
| Roma    |
L'istanza "Napoli" non compare, in quanto, su tale filiale non c'è l'ufficio "Studi". 

---

### Esercizi Algebra Relazionale


----

# SQL

Si noti che il **linguaggio SQL** sia **case-insensitive**, cioè che i suoi comandi non sono influiti dal maiuscolo o minuscolo, dunque scrivere "`create table`" o "`CREATE TABLE`" è del tutto analogo.

CREATE DATABASE nomeDatabase;

CREATE TABLE nomeTabella(col1, col2, ..., col$_n$);
CREATE TABLE IF NOT EXISTS nomeTabella(col1, col2, ..., col$_n$);

per eliminarle:
"DROP DATABASE nomeDatabase"
"DROP TABLE nomeTabella"

col1 può assumere dei tipi:

| Tipo         | Descrizione                                                                                                                                                                                                                                  | Range                            | Esempio                                                |
| ------------ | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------- | ------------------------------------------------------ |
| int          | valore interi, famiglia TINYINT (valori da 0 a 255),                                                                                                                                                                                         | da 0 a 4294967295                | 10, -10                                                |
| decimal      | valore decimali esatti                                                                                                                                                                                                                       | 38 caratteri rappresentabili     | 2.3, 3.001                                             |
| float(A,B)   | valori decimale approssimati, dove A rappresenta numero massimo <br>di caratteri rappresentabili e B il numero di caratteri<br>dopo la virgola. Se vengono scritti valori con virgola <br>più precisi, verranno arrotondati automaticamente. | 1.79×10$^{308}$ <br>             | `float(8,3)` otteniamo<br>valori di tipo:<br>99999.999 |
| varchar(max) | stringhe char con max caratteri da dichiarare (65,535)                                                                                                                                                                                       |                                  | "Ciao mondo!"                                          |
| char(n)      | stringa di lunghezza fissa di n caratteri                                                                                                                                                                                                    |                                  | 'A1234'                                                |
| date         | date scritte nel formato 'YYYY-MM-DD'                                                                                                                                                                                                        |                                  | '2025-12-29'                                           |
| year         | analogo a date ma solo per l'anno 'YYYY'                                                                                                                                                                                                     |                                  | '1999'<br>'2000'<br>'2025'                             |
| text         | testo senza parametro di caratteri massimi.<br>.<br>Nella stessa famiglia troviamo anche `MEDIUMTEXT` (16,777,215 caratteri) e<br>`LONGTEXT` (4,294,967,295 caratteri rappresentabili, praticamente un enciclopedia infinita!)               | 65,535 caratteri rappresentabili | "Ciao mondo!!!!"                                       |

Vincoli di integrità (**constraints**):

| Tipo         | Descrizione                                                                                                                                                                                                                   | Esempio                                                                                                                |
| ------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------- |
| **NOT NULL** | Un valore non può essere nullo, non può essere<br>lasciato in bianco durante l'inserimento.                                                                                                                                   | Chiave primaria non può essere NULL!                                                                                   |
| **UNIQUE**   | Valore unico per istanza, come un numero di telefono<br>che tuttavia non è chiave primaria, in quanto un numero <br>di telefono può cambiare, ma un codice univoco no.                                                        | Numero di telefono è generalmente unico per ogni individuo                                                             |
| **DEFAULT**  | Assegna un valore di default in caso il campo sia lasciato<br>vuoto.                                                                                                                                                          | Un dipendente con campo "mansione" lasciato in bianco potrebbe essere <br>memorizzato come "Impiegato".                |
| **CHECK**    | Esegue una verifica che il valore inserito sia corretto,<br>secondo le condizioni date                                                                                                                                        | Si potrebbe voler svolgere un controllo sul <br>salario:<br>`salary INT NOT NULL CHECK (salary >= 1000 <= 2000) `<br>  |
| PRIMARY KEY  | Indica che il campo è Chiave Primaria, possibile da indicare anche <br>dopo con il metodo:<br>`PRIMARY KEY(nomeCampo)`                                                                                                        | `ID_Dipendente NOT NULL PRIMARY KEY`                                                                                   |
| FOREIGN KEY  | Indica che il campo indicato è la chiave primaria di un'altra relazione, indicando con <br>REFERENCE relazioneAppartenenza(nomeCampo)<br>dove il nomeCampo indica il nome che viene utilizzato nella tabella di appartenenza. | `FOREIGN KEY(id_dipendente) REFERENCES Dipendenti(id_dipendente)`<br>*Lo vedremo meglio con l'esempio completo sotto.* |

Nel dettaglio vediamo esempio:

`CREATE TABLE IF NOT EXISTS Dipendenti(`
  `-- Autoincrement su tutti gli ID, 1, 2, 3 ...`
  `id_dipendente INT UNSIGNED NOT NULL AUTO_INCREMENT,`
  `nome VARCHAR(30) NOT NULL,`
  `cognome VARCHAR(30) NOT NULL,` 
  `stipendio DECIMAL(10,2) NOT NULL,`
  `dataAssunzione DATE NOT NULL,`
  `mansione VARCHAR(40) NOT NULL DEFAULT 'Impiegato',`
  `PRIMARY KEY(id_dipendente)`
`);`



Operatori utilizzati nella condizione WHERE:

| Operatore | Descrizione                            | Esempio                                   |
| --------- | -------------------------------------- | ----------------------------------------- |
| `=`       | uguale                                 | nome = "Mario"                            |
| `>`       | maggiore di                            | salario > 1000                            |
| `<`       | minore di                              | salario < 2000                            |
| `>=`      | maggiore o uguale di                   | Eta >= 30                                 |
| `<=`      | minore o uguale di                     | salario1 <= salario2                      |
| `!=`      | diverso da                             | sede != "Roma"                            |
| `LIKE`    | valori che contengono una certa chiave | WHERE nome LIKE 'Mar'                     |
| `IN`      | lista di valori da cercare             | WHERE sede IN ('Roma', 'Milano','Napoli') |
| `BETWEEN` | range dei valori da cercare            | WHERE salario BETWEEN 2000 AND 3000       |
- `!=` può anche essere sostituito da un `NOT` che precede poi un attributo = attributo o costante.
	Esempio: WHERE NOT sede = "Roma" 


Esempio completo:

> [!tip] Codice completo:
> >[!brown] Impiegati gestiscono Clienti
> >-- Query di creazione tabelle -- 
> >CREATE TABLE IF NOT EXISTS Dipendenti(
> >   -- Autoincrement su tutti gli ID, 1, 2, 3 ...
> >   id_dipendente INT UNSIGNED NOT NULL AUTO_INCREMENT,
> >  nome VARCHAR(30) NOT NULL,
> > cognome VARCHAR(30) NOT NULL, 
> >   stipendio DECIMAL(10,2) NOT NULL,
> >  dataAssunzione DATE NOT NULL,
> >  mansione VARCHAR(40) NOT NULL DEFAULT 'Impiegato',
> >  PRIMARY KEY(id_dipendente)
> >);
 >> 
> > CREATE TABLE IF NOT EXISTS Clienti(
> >  id_cliente INT UNSIGNED NOT NULL AUTO_INCREMENT,
> >  -- denominazione della ditta --
> >  denominazione VARCHAR(255) NOT NULL UNIQUE,
> >  p_iva VARCHAR(16) NOT NULL UNIQUE,
> >  indirizzo VARCHAR(255) NOT NULL,
> >  sede VARCHAR(30) NOT NULL,
> >   -- un numero di telefono può iniziare con uno zero, dunque non può essere int --
> >  telefono VARCHAR(10) NOT NULL UNIQUE,
> >  PRIMARY KEY(id_cliente)
> >);
> >
> >CREATE TABLE IF NOT EXISTS Rapporto_clienti(
> >  id_rapporto INT UNSIGNED NOT NULL AUTO_INCREMENT,
> >  id_cliente INT UNSIGNED NOT NULL,
> >  id_dipendente INT UNSIGNED NOT NULL,
> >
> >  PRIMARY KEY(id_rapporto),
> >
> >  FOREIGN KEY(id_cliente) REFERENCES Clienti(id_cliente),
> >  FOREIGN KEY(id_dipendente) REFERENCES Dipendenti(id_dipendente)
> >);
> >



### Inserimento dei dati nelle tabelle:

Utilizzo del comando `INSERT INTO` accompagnato dal nome della tabella e come parametri i campi in cui fare l'inserimento, dunque segue il comando `VALUES` accompagnato dagli inserimenti, in ordine dei campi inseriti come parametri.

- Inserimento singolo:
	Query di inserimento tabella Clienti: 
	
	`INSERT INTO Clienti(denominazione, p_iva, indirizzo, sede, telefono)`
	`VALUES ("Riot Games", "00113484034", "Via Roma 44", "Roma", "0951231230");`

- Inserimento a cascata: 
	
	`INSERT INTO Clienti(denominazione, p_iva, indirizzo, sede, telefono)`
	`VALUES` 
	  `("Riot Games",  "00113484034", "Via Roma 44", "Roma", "0951231230"),`
	  `("Valve", "022387494002", "Via Europa 43", "Milano", "0934583954"),`
	  `("Meta", "123452345555", "Via Cavour 98", "Catania", "0987665436");`

alla creazione di una tabella si può voler specificare determinati limiti che un campo può avere, per esempio non possiamo avere una età negativa o sopra i 150 anni ovviamente. 
Utilizziamo un **constraint** a cui possiamo anche attribuirgli un nome per facilitarne la modifica o cancellazione, con il comando:


> [!tip] Constraint di una colonna 
> CONSTRAINT nomeVariabileConstraint CHECK(condizione);

Questo si può scrivere in seguito, o direttamente tra i constraint di un attributo. 
Ricordiamo che una colonna si dichiara nella formula: **nome tipo constraint**

> [!redwood] Esempio constraint:
> stipendio DECIMAL(6,2) NOT NULL CHECK(stipendio >= 1200 AND stipendio <= 2000),
> 

Se la tabella è già stata creata, come vedremo con l'uso di ALTER TABLE, basti scrivere:

> [!redwood] Aggiunta constraint post creazione 
> **ALTER TABLE** nomeTabella
> **ADD CONSTRAINT** nomeConstraint **CHECK**(stipendio >= 1200 **AND** stipendio <= 2000)**


----

#### Interrogazione del DB:

#### 1. Selezione 

Il simbolo $*$ nella selezione permette di selezionare tutte quante le colonne, o i campi, della relazione, o tabella. 

> [!brown] SELECT
> 
> **SELECT** campoDaSelezionare
> **FROM** nomeTabella
> **WHERE** condizione
> 
> *Esempio:* 
> 
> **SELECT** id_cliente, denominazione, sede
> **FROM** clienti
> **WHERE** sede = "Roma" AND id_cliente <= 10;


#### 2. Ordinamento dei dati

L'ordinamento viene effettuato con il comando ORDER BY nomeCampo e poi il metodo di ordinamento:
- **ASC:** ascendente o crescente;
- **DESC:** discendente o decrescente.

> [!Info] ORDER BY - Una sola colonna
> **SELECT** *
> **FROM** dipendenti
> **ORDER BY** stipendio **ASC**

> [!Info] ORDER BY - Colonne multiple
> **SELECT** *
> **FROM** dipendenti
> **ORDER BY** nome, cognome **DESC**

#### 3. Limit 

Permette di limitare la ricerca ad un gruppo limitato di record, sostanzialmente seleziona i primi $n$ record. 


> [!Hint] Sintassi Limit
> LIMIT $n$ 

Da notare che non stiamo trattando una funzione con dei parametri ma il valore è scritto di seguito alla parola chiave **LIMIT**. 

*Esempio:* vogliamo vedere i primi 5 dipendenti con lo stipendio maggiore.

> [!Hint] Limit
> 
> **SELECT** *
> **FROM** dipendenti
> **ORDER BY** stipendio **DESC LIMIT** 5

Limit offset permette di aggiungere un secondo argomento alla parola chiave **LIMIT**, quindi 
$n_1$ e $n_2$, dove $n_1$ indica le **righe da saltare** e $n_2$ quelle da mostrare dopo le $n_1$ righe saltate. 

> [!Hint] Limit
> 
> **SELECT** *
> **FROM** dipendenti
> **ORDER BY** stipendio **DESC LIMIT** 1,2

Stiamo mostrando il secondo e il terzo impiegato per stipendio maggiore, escludendo il primo. 

#### 4. Distinct e count

Permette di mostrare i record che si ripetono, una sola volta. Nel caso in cui proiettassimo per esempio solo la sede delle aziende, vogliamo poter vedere la città di provenienza solo una volta. 
- Il **count** ci permette di sapere il numero di record della relazione. 

> [!redwood] Distinct 
> SELECT DISTINCT sede 
> FROM Clienti  

Risultato:

| Sede          |
| ------------- |
| Roma<br>      |
| Milano<br>    |
| Catania<br>   |
| Parigi<br>    |
| Varsavia<br>  |
| Tokyo<br>     |
| Berlino<br>   |
| Zurigo<br>    |
| Amsterdam<br> |
| Stoccolma     |
Se volessimo per esempio sapere il numero di sedi distinte, allora potremmo fare:

> [!redwood] Distinct e count
> 
> SELECT COUNT(DISTINCT sede)
> FROM Clienti

#### 5. Update 

La parola chiave **update** ci permette di **aggiornare una tabella**.

> [!NOTE] Update
> UPDATE Clienti
> SET sede = 'Roma'
> WHERE ID_cliente = 2

Per modificare più righe, basta utilizzare una condizione WHERE adeguata, per esempio:

> [!NOTE] Update
> UPDATE Clienti
> SET sede = 'Roma'
> WHERE ID_cliente BETWEEN 3 AND 6

Per modificare più colonne:

> [!NOTE] Update
> UPDATE Clienti
> SET sede = 'Roma', indirizzo = 'via Augusta'
> WHERE ID_cliente BETWEEN 3 AND 6


> [!Warning] Attenzione
> **Importantissimo** non dimenticare la condizione WHERE, altrimenti andrà a modificare tutti i record! 


#### 6. Delete 

Comando per la cancellazione di un attributo, una colonna, una tabella o addirittura l'intero record.
In generale:

DELETE FROM nome 
WHERE condizione

Esempio: 



> [!Warning] Attenzione
> **Importantissimo** non dimenticare la condizione WHERE, altrimenti verranno rimossi TUTTI gli elementi!

Notiamo che eseguendo una delete su una o più righe, gli eventuali valori con auto increment rimossi non vanno a resettare il contatore, ma rimarrà allo oscuro di questa operazione. 
Per voler avere un auto_increment pulito utilizzeremo il comando **Truncate**


> [!Pink] Delete
> DELETE FROM Clienti
> WHERE  ID_cliente = 5

Risultato:

SELECT id_cliente, denominazione, sede
FROM Clienti


| id_cliente                          | denominazione   | sede          |
| ----------------------------------- | --------------- | ------------- |
| 1	<br>                              | Riot Games      | Roma<br>      |
| 2                                   | Valve           | Milano<br>    |
| 3                                   | Meta            | Roma<br>      |
| 4                                   | Ubisoft         | Roma<br>      |
| <span style = "color: red">6</span> | Samsung         | Roma<br>      |
| 7                                   | Microsoft       | Berlino<br>   |
| 8                                   | Apple inc.      | Zurigo<br>    |
| 9                                   | HyperX          | Amsterdam<br> |
| 10                                  | MSI Corporation | Stoccolma     |


#### 7. Truncate

Funziona esattamente come il DELETE senza condizione, ma aggiorna l'auto_increment, dunque possiamo ricreare e ripopolare la tabella con gli indici a partire da 1.  

Vantaggi:
- Molto più veloce di DELETE
- Resetta auto-increment
- Bypassa solitamente i trigger
Svantaggi:
- Non può essere filtrato con condizioni (no WHERE)
- elimina TUTTA la tabella
 
- Truncate è un comando di DDL (Data Definition Language)
- Delete è un comando di DML (Data Manipulation Language) 

> [!Pink] Truncate
> TRUNCATE TABLE Clienti

Risultato:

| id_cliente | denominazione | sede |
| ---------- | ------------- | ---- |
|            |               |      |

*Tabella vuota!*

Tuttavia adesso possiamo ripopolare la tabella, avendo l'indice immediatamente successivo al valore precedente a quello eliminato.  

| id_cliente                          | denominazione   | sede          |
| ----------------------------------- | --------------- | ------------- |
| 1	<br>                              | Riot Games      | Roma<br>      |
| 2                                   | Valve           | Milano<br>    |
| 3                                   | Meta            | Roma<br>      |
| 4                                   | Ubisoft         | Roma<br>      |
| <span style = "color: red">5</span> | Samsung         | Roma<br>      |
| 7                                   | Microsoft       | Berlino<br>   |
| 8                                   | Apple inc.      | Zurigo<br>    |
| 9                                   | HyperX          | Amsterdam<br> |
| 10                                  | MSI Corporation | Stoccolma     |

#### 8. JOIN (o INNER JOIN)

Andiamo ad unire diverse tabelle con la JOIN: 

**Scrivere JOIN o INNER JOIN è del tutto analogo.**

- INNER JOIN ci permette di prendere solo valori in comune tra le due tabelle, dunque se ho un valore NULL nella prima tabella, quel valore non sarà mostrato nella INNER JOIN.  

![[Pasted image 20251130010330.png]]
*Fonte: https://www.tutorialrepublic.com/sql-tutorial/sql-inner-join-operation.php*
Formula generale:

> [!Hint] Inner Join (prende solo le parti in comuni)
> 
> SELECT campi
> FROM tabella1
> INNER JOIN tabella2 ON condizione

Esempio:

Database: 

| ID_dipendente | nome   | Cognome | stipendio | dataAssunzione | mansione                 | id_ufficio |
| ------------- | ------ | ------- | --------- | -------------- | ------------------------ | ---------- |
| 1             | Mario  | Rossi   | 2800.00   | 2010-10-02     | Economy Advisor          | 1          |
| 2             | Luigi  | Verdi   | 3290.00   | 2020-12-20     | Senior Developer Advisor | 2          |
| 3             | Emma   | Marroni | 4800.00   | 2018-08-08     | Business Lawyer          | 3          |
| 4             | Gianni | Rossi   | 3000.00   | 2010-04-18     | Project Advisor          | 2          |
| 5             | Ella   | Verdi   | 3500.00   | 2022-02-22     | Senior General Advisor   | 2          |
| 6             | Marco  | Marroni | 1980.00   | 2025-09-28     | Project Advisor          | NULL       |

| ID_ufficio | nome_ufficio         |
| ---------- | -------------------- |
| 1          | Web Developing       |
| 2          | Project Management   |
| 3          | Business Association |
| 4          | Marketing            |

> [!Hint] Esempio di INNER JOIN
> **SELECT** dipendenti.id_dipendente, dipendenti.nome, dipendenti.mansione, uffici.nome_ufficio
> **FROM** dipendenti
> **INNER** JOIN uffici **ON** dipendenti.id_ufficio = uffici.ID_ufficio;

Tabella ottenuta: 

| ID_dipendente | nome   | Cognome | mansione                 | nome_ufficio         |
| ------------- | ------ | ------- | ------------------------ | -------------------- |
| 1             | Mario  | Rossi   | Economy Advisor          | Web Developing       |
| 2             | Luigi  | Verdi   | Senior Developer Advisor | Project Management   |
| 3             | Emma   | Marroni | Business Lawyer          | Business Association |
| 4             | Gianni | Rossi   | Project Advisor          | Project Management   |
| 5             | Ella   | Verdi   | Senior General Advisor   | Project Management   |


> [!tip] Ridenominazione delle relazioni (o tabelle)
> È possibile ridenominare una tabella per semplificarne la scrittura con la parola chiave AS,
>  1. dunque alla select scrivere la tabella già come rinominata; 
>  2. poi alla FROM nomeTabella AS nuovoNome.


#### 9. LEFT JOIN: 

Permette di aggiungere anche i valori della prima tabella che non sono comuni ad entrambe le tabelle e riempie i campi mancanti con NULL.

![[Pasted image 20251130010417.png]]

>[!pink] LEFT JOIN
>**SELECT** t1.nome, t1.cognome, t1.mansione, t2.nome_ufficio
> **FROM** dipendenti **AS** t1
> **LEFT** JOIN **uffici** **AS** t2
> **ON** t1.id_ufficio = t2.id_ufficio 

| ID_dipendente | nome   | Cognome | mansione                 | nome_ufficio         |
| ------------- | ------ | ------- | ------------------------ | -------------------- |
| 1             | Mario  | Rossi   | Economy Advisor          | Web Developing       |
| 2             | Luigi  | Verdi   | Senior Developer Advisor | Project Management   |
| 3             | Emma   | Marroni | Business Lawyer          | Business Association |
| 4             | Gianni | Rossi   | Project Advisor          | Project Management   |
| 5             | Ella   | Verdi   | Senior General Advisor   | Project Management   |
| 6             | Marco  | Marroni | Project Advisor          | NULL                 |
#### 10. RIGHT JOIN:

Come la left join ma riguarda la seconda tabella:

![[Pasted image 20251130010430.png]]

> [!info] RIGHT JOIN
> **SELECT** t1.nome, t1.cognome, t1.mansione, t2.nome_ufficio
> **FROM** dipendenti **AS** t1
> **RIGHT JOIN** uffici **AS** t2
> **ON** t1.id_ufficio = t2.id_ufficio

| ID_dipendente | nome   | Cognome | mansione                 | nome_ufficio         |
| ------------- | ------ | ------- | ------------------------ | -------------------- |
| 1             | Mario  | Rossi   | Economy Advisor          | Web Developing       |
| 2             | Luigi  | Verdi   | Senior Developer Advisor | Project Management   |
| 3             | Emma   | Marroni | Business Lawyer          | Business Association |
| 4             | Gianni | Rossi   | Project Advisor          | Project Management   |
| 5             | Ella   | Verdi   | Senior General Advisor   | Project Management   |
| NULL          | NULL   | NULL    | NULL                     | Marketing            |

> [!Warning] FULL JOIN 
> La FULL JOIN non è supportato in MySQL, può essere ricavato utilizzando le UNION.

#### 11. FULL JOIN:

Permette di includere anche i valori non in comune ad entrambe le tabelle. 
Non è supportato in MySQL, può essere ricavato utilizzando le UNION.

![[Pasted image 20251130010455.png]]

Tecnicamente andrebbe scritto in questo modo:

SELECT t1.nome, t1.cognome, t1.mansione, t2.nome_ufficio
FROM dipendenti as t1
FULL JOIN uffici as t2
ON t1.id_ufficio = t2.id_ufficio 

TUTTAVIA, MySQL non lo supporta nella maggior parte dei BDMS, dunque combiniamo **LEFT JOIN** e **RIGHT JOIN** con una **UNION**:

> [!redwood] FULL JOIN
> 
> **SELECT** t1.nome, t1.cognome, t1.mansione, t2.nome_ufficio
> **FROM** dipendenti **AS** t1
> **LEFT** JOIN **uffici** **AS** t2
> **ON** t1.id_ufficio = t2.id_ufficio 
> 
> **UNION ALL** 
>   
> **SELECT** t1.nome, t1.cognome, t1.mansione, t2.nome_ufficio
> **FROM** dipendenti **AS** t1
> **RIGHT JOIN** uffici **AS** t2
> **ON** t1.id_ufficio = t2.id_ufficio

#### 12. CROSS JOIN (Prodotto Cartesiano):

Il cross join permette di fare il prodotto cartesiano tra due tabelle, come visto in algebra relazionale, esso è generalmente poco utile. Tuttavia ecco esempio di utilizzo:

![[Pasted image 20251130105030.png]]

> [!brown] CROSS JOIN
> 
> **SELECT** t1.nome, t1.cognome, t1.mansione, t2.nome_ufficio
> **FROM** dipendenti **AS** t1 
> **CROSS JOIN** uffici **AS** t2 
> **WHERE** t1.id_dipendente = 1 
> 
> *dove* **AS** *permette di rinominare una tabella, non è obbligatorio ma semplifica la scrittura.*


---

#### 13. LIKE

Il comando **LIKE** permette di ricercare da uno o più campi, un **pattern** cioè permette anche da una parte parziale di una parola, a trovare dei record che la contengono in quel campo.

Formula generale: 

> [!tip] **WHERE** campo **LIKE** pattern

**Tipi di pattern:**

Utilizziamo un **carattere** o una **combinazione di caratteri** accompagnate dagli operatori:
- `%` : seguita dal carattere (`%C`) indica che la stringa è presente prima del carattere e finisce con esso, viceversa (`C%`) indica che il carattere si trova all'inizio della stringa.
  Importante: al posto di % può **anche esserci nulla**.
- `_`: indica la possibilità di **un solo carattere**. 
  
Vediamo meglio il tutto in tabella:  

| Simbologia | Significato                                                                                                                                       | Esempio Parola chiave      | Esempio risultato                                                                                                                     |
| ---------- | ------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------- | ------------------------------------------------------------------------------------------------------------------------------------- |
| `'C%'`     | Trova parole che iniziano per ...                                                                                                                 | `'da%'`                    | <span style = "color: red">Da</span>rio,<br><span style = "color: red">Da</span>vide,<br><span style = "color: red">Da</span>miano    |
| `'%C'`     | Parole che terminano per ...                                                                                                                      | `'%o'`                     | Mari<span style = "color: red">o</span>,<br>Dari<span style = "color: red">o</span>,<br>Robert<span style = "color: red">o</span>     |
| `'%C%'`    | Trova parole che contengono ...                                                                                                                   | `'%ar%'`                   | M<span style = "color: red">ar</span>io,<br><span style = "color: red">Ar</span>mando,<br><br>                                        |
| `'C_'`     | Parole che iniziano per ... e contengono AL MASSIMO UN SOLO carattere finale                                                                      | `'Mari_'`                  | Mari<span style = "color: red">a</span>,<br>Mari<span style = "color: red">o</span><br>                                               |
| `'_C'`     | Parole che terminano per ... e contengono AL MASSIMO UN SOLO carattere iniziale                                                                   | `'_ario'`                  | D<span style = "color: red">ario</span>,<br>M<span style = "color: red">ario</span>                                                   |
| `'_C_'`    | Parole che contengono ... e hanno UN SOLO carattere sia all'inizio che alla fine                                                                  | `'_an_'`<br>`'_nn_'`       | D<span style = "color: red">an</span>a,<br>A<span style = "color: red">nn</span>a                                                     |
| `'%C_'`    | Parole che contengono ... e hanno AL MASSIMO un SOLO un carattere **finale**                                                                      | `'%ar_'`                   | S<span style = "color: red">ar</span>a,<br>Chi<span style = "color: red">ar</span>a,<br>Barb<span style = "color: red">ar</span>a<br> |
| `'_C%`     | parole che contengono ... e hanno al massimo UN SOLO carattere **iniziale**                                                                       | `'a'`<br><br>`'ar'`        | D<span style = "color: red">a</span>miano,<br>L<span style = "color: red">a</span>ura,<br>M<span style = "color: red">ar</span>ta     |
| `'C_..._'` | Non c'è un limite di simboli `'_'`, si rileva utile in quanto si contrappone al simbolo `'%'` che invece non ha controllo sul limite di caratteri | `'M____'` ,<br>M e 4 `'_'` | <span style = "color: red">M</span>ario,<br><span style = "color: red">M</span>arta,<br><span style = "color: red">M</span>arco       |
| `'__C_'`   | Analogamente a riga sopra, non ci sono limitazioni all'uso dell'operatore `'_'`                                                                   | `'__h_'`                   | Jo<span style = "color: red">h</span>n<br>                                                                                            |
| `'C_C'`    | Operatore di carattere singolo può anche stare nel mezzo di caratteri                                                                             | `'P_ttore'`                | <span style = "color: red">P</span>i<span style = "color: red">ttore</span>                                                           |
*$^1$C indica un carattere o una combinazione.
$^2$ con l'uso dell'operatore `'_'` si intende anche un carattere vuoto, non dev'essere necessariamente occupato da un carattere.*

> [!warning] Importante
> Come già detto **SQL è CASE-INSENSITIVE**, dunque scrivere:
> `'%ar%'` 
> `'%Ar%'` 
> `'%AR%'` 
> è del tutto analogo in SQL 

Esempio:

> [!redwood] LIKE
> **SELECT** nome, stipendio
> **FROM** dipendenti
> **WHERE** nome **LIKE** '%ma%'

Risultato:

| Nome  | Stipendio |
| ----- | --------- |
| Mario | 2800.00   |
| Emma  | 4800.00   |
| Marco | 1980.00   |

#### 14. Alter Table

Alter table ci permette di modificare le tabelle:
1. Aggiungere nuove colonne;
2. Cambiare posizione di una colonna;
3. Aggiungere nuovi vincoli (costraint)
4. Rimuovere una colonna
5. Cambiare tipo di dato di una colonna
6. Rinominare una colonna
7. Rinominare la tabella

Utilizzando gli operatori:
- **ADD**
- **MODIFY**
- **AFTER**

> [!tip] ALTER TABLE nomeTabella ADD colonna nomeTipo constraint 
> 

Tabella di esempio:

| id_rapporto | id_cliente | id_dipendente |
| ----------- | ---------- | ------------- |
| 1           | 1          | 1             |
| 2           | 2          | 1             |
| 3           | 3          | 2             |
| 4           | 4          | 3             |

1. Aggiungere nuove colonne;

> [!pink] ALTER TABLE - ADD nomeTabella tipo constraint
> **ALTER TABLE** rapporto_clienti **ADD** note TEXT 

| id_rapporto | id_cliente | id_dipendente | <span style = "color: tomato">note</span> |
| ----------- | ---------- | ------------- | ----------------------------------------- |
| 1           | 1          | 1             |                                           |
| 2           | 2          | 1             |                                           |
| 3           | 3          | 2             |                                           |
| 4           | 4          | 3             |                                           |

2. Cambiare posizione di una colonna;

> [!Pink] ALTER TABLE - MODIFY nomeTabella tipo AFTER tabellaDaSeguire
> **ALTER TABLE** rapporto_clienti 
> **MODIFY** note TEXT **AFTER** ID_rapporto

| id_rapporto | <span style = "color: tomato">note</span> | id_cliente | id_dipendente |
| ----------- | ----------------------------------------- | ---------- | ------------- |
| 1           |                                           | 1          | 1             |
| 2           |                                           | 2          | 1             |
| 3           |                                           | 3          | 2             |
| 4           |                                           | 4          | 3             |
3. Aggiungere nuovi vincoli (costraint)

> [!Pink] ALTER TABLE - ADD costraint (nomeTabella)
> **ALTER TABLE** clienti
> **ADD UNIQUE** (telefono)

Adesso il campo telefono (se prima non lo era) adesso è sicuramente unico, SQL non ci dice se il campo era già di quel constraint. 

4. Rimuovere una colonna

> [!Pink] ALTER TABLE - DROP COLUMN nomeColonna
> **ALTER TABLE** rapporto_clienti
> **DROP COLUMN** note

| id_rapporto | id_cliente | id_dipendente |
| ----------- | ---------- | ------------- |
| 1           | 1          | 1             |
| 2           | 2          | 1             |
| 3           | 3          | 2             |
| 4           | 4          | 3             |

5. Cambiare tipo di dato di una colonna

> [!Pink] ALTER TABLE - MODIFY nomeTabella tipo
> **ALTER TABLE** rapporto_clienti
> **MODIFY** note **varchar**(1000)

Adesso il campo note è passato da tipo TEXT ad un tipo VARCHAR di massimo 1000 caratteri.

6. Rinominare una colonna

> [!Pink] ALTER TABLE - RENAME COLUMN/ CHANGE
>Nuove versioni SQL 8.0+:
>accetta:
>**ALTER TABLE** rapporto_clienti 
>**RENAME COLUMN** note **TO** reminder
>
>quelle vecchie invece:
>
   **ALTER TABLE** rapporto_clienti
>**CHANGE** note reminder varchar(1000)

7. Rinominare la tabella

> [!Pink] ALTER TABLE - RENAME nomeTabella
> ALTER TABLE dipendenti 
> RENAME impiegati
> 

---

> [!redwood] Esempio di aggiunta attributo ad un elemento raggiunto tramite tabella associata:
> 
> update rapporto_clienti
> set note = "Microsoft"
> where id_cliente = (
>   SELECT id_cliente 
>   FROM clienti
>   WHERE denominazione = "Microsoft"
> );

---

#### 15. GROUP BY - Funzioni di aggregazione 

Una funzione di aggregazione è una funzione che esegue un calcolo su un insieme di valori e restituisce un singolo valore.

Le funzioni di aggregazione vengono spesso utilizzate con la "`GROUP BY`" dopo la clausola dell'istruzione `SELECT` . 
Il comando "`GROUP BY`" **suddivide il set di risultati in gruppi di valori** e la funzione di aggregazione può essere **utilizzata per restituire un singolo valore per ciascun gruppo**.

Le funzioni di aggregazione più utilizzate sono:

- `MIN()`: restituisce valore più PICCOLO all'interno della colonna selezionata.
- `MAX()`: restituisce valore più GRANDE all'interno della colonna selezionata.
- `COUNT()`: restituisce il NUMERO di righe di una selezione.
- `SUM()`: restituisce la SOMMA totale di una colonna.
- `AVG()`: restituisce la MEDIA numerica dei valori di una colonna.


> [!Brown] MIN()
> SELECT MIN(stipendio)
> FROM dipendenti

> [!brown] AVG()
> select avg(stipendio)
> from dipendenti

E così via, hanno tutti lo stesso modo di utilizzo.

Trucchetto per mostrare la tabella e sotto come record la media, o un'altra funzione su di essi:

> [!pink] Come mostrare media stipendio sotto la tabella dipendenti
> SELECT *
>  FROM dipendenti
> 
>   UNION ALL
>   
> SELECT 
> 	  NULL AS id_dipendente,
> 	  'MEDIA' AS nome, 
> 	  'STIPENDI' AS cognome, 
> 	  round(avg(stipendio)) as stipendio,
> 	  NULL as dataAssunzione,
> 	  NULL as mansione, 
> 	  NULL as id_ufficio
> FROM dipendenti


> [!Warning] Attenzione: 
> Questo si può fare ancora più facilmente con la clausola **ROLLUP** che si occupa proprio di questo. Lo vedremo più avanti. 

Visualizzato:

| ID_dipendente | nome   | Cognome   | stipendio | dataAssunzione | mansione                 | id_ufficio |
| ------------- | ------ | --------- | --------- | -------------- | ------------------------ | ---------- |
| 1             | Mario  | Rossi     | 2800.00   | 2010-10-02     | Economy Advisor          | 1          |
| 2             | Luigi  | Verdi     | 3290.00   | 2020-12-20     | Senior Developer Advisor | 2          |
| 3             | Emma   | Marroni   | 4800.00   | 2018-08-08     | Business Lawyer          | 3          |
| 4             | Gianni | Rossi     | 3000.00   | 2010-04-18     | Project Advisor          | 2          |
| 5             | Ella   | Verdi     | 3500.00   | 2022-02-22     | Senior General Advisor   | 2          |
| 6             | Marco  | Marroni   | 1980.00   | 2025-09-28     | Project Advisor          | NULL       |
| NULL          | MEDIA  | STIPENDIO | 3228.00   | NULL           | NULL                     | NULL       |
*Per voler creare uno spazio tra la tabella dipendenti e quella media, possiamo fare la union con una tabella dipendenti che mostra tutti i campi AS NULL o meglio NULL AS nomeCampo*. 

Oppure se lo si vuole mettere come attributo a parte, che appaia ad ogni record:

> [!Pink] Dipendenti con attributo stipendio medio
> **SELECT** * , (**SELECT** avg(stipendio) **FROM** dipendenti) AS "**stipendio** medio"
> **FROM** dipendenti
> 

Visualizzazione:

| ID_dipendente | nome   | Cognome | stipendio | dataAssunzione | mansione                 | id_ufficio | stipendio medio |
| ------------- | ------ | ------- | --------- | -------------- | ------------------------ | ---------- | --------------- |
| 1             | Mario  | Rossi   | 2800.00   | 2010-10-02     | Economy Advisor          | 1          | 3228.333333     |
| 2             | Luigi  | Verdi   | 3290.00   | 2020-12-20     | Senior Developer Advisor | 2          | 3228.333333     |
| 3             | Emma   | Marroni | 4800.00   | 2018-08-08     | Business Lawyer          | 3          | 3228.333333     |
| 4             | Gianni | Rossi   | 3000.00   | 2010-04-18     | Project Advisor          | 2          | 3228.333333     |
| 5             | Ella   | Verdi   | 3500.00   | 2022-02-22     | Senior General Advisor   | 2          | 3228.333333     |
| 6             | Marco  | Marroni | 1980.00   | 2025-09-28     | Project Advisor          | NULL       | 3228.333333     |

> [!tip] Importanza del GROUP BY
> Il group by mi permette di raggruppare le voci ridondanti, cioé i nomi che si ripetono
> 


> [!redwood] Utilizzo del GROUP BY per mostrare i nomi degli uffici 
> SELECT x.nome_ufficio
FROM uffici as x 
left join dipendenti as y 
ON x.ID_ufficio = y.ID_ufficio
GROUP BY x.nome_ufficio 

Risultato:

| nome_ufficio         |
| -------------------- |
| Web Developing       |
| Project Management   |
| Business Association |
| Marketing            |
Vogliamo sapere quanti dipendenti ha ogni ufficio:
basta aggiungere alla selezione una funzione `count(y.id_dipendente)`:

> [!redwood] Uffici e numero dipendenti assegnati
> SELECT x.nome_ufficio, count(y.id_dipendente) AS "Numero dipendenti"
> FROM uffici as x 
> left join dipendenti as y 
> ON x.ID_ufficio = y.ID_ufficio
> GROUP BY x.nome_ufficio 
> 

| nome_ufficio         | Numero dipendenti |
| -------------------- | ----------------- |
| Web Developing       | 1                 |
| Project Management   | 0                 |
| Business Association | 3                 |
| Marketing            | 1                 |

- HAVING è simile al WHERE ma agisce direttamente al gruppo creato con GROUP BY, quindi per voler visualizzare per esempio quanti uffici ci sono con più di 2 impiegati potremmo fare:

> [!redwood] Uffici con almeno due dipendenti
> SELECT x.nome_ufficio, count(y.id_dipendente) as numero_dipendenti
> FROM uffici as x 
> left join dipendenti as y 
> ON x.ID_ufficio = y.ID_ufficio
> GROUP BY x.nome_ufficio 
> HAVING numero_dipendenti > 2
> 

#### 16. ALIAS 

Già anticipati, ma ritengo opportuno esplicitarli in un paragrafo a sé. 

L'alias può essere utilizzato per ridenominare, al fine di semplificare una query o una VISTA (View).
È possibile applicare l'alias sia a colonne che a tabelle, abbiamo per esempio visto:

> [!Hint] Esempio di ALIAS di una Tabella
> 
> **SELECT** t1.nome
> FROM dipendenti AS t1

Oppure una tabella:

> [!Hint] Esempio di ALIAS di una Colonna
> SELECT nome, **DATE_FORMAT**(dataAssunzione, '**%e %M**, **%Y**') **AS** "Data assunzione"
> **FROM** dipendenti;

Il comando `DATE_FORMAT(colonnaDate, '%e %M, %Y')`, dove
`%e` rappresenta il giorno
`%M` il mese
`%Y` l'anno

---

#### 17. VIEW (o VISTE)
Le **viste** sono tabelle virtuali le cui definizioni sono salvate nel database, ma non contengono effettivamente dei dati.
Permettono di memorizzare nel database query complesse usate di frequente. 
Si creano con il comando:


> [!tip] CREATE VIEW nomeVista AS selezione
> Per eliminarla, semplicemente:
>- **DROP VIEW nomeVista;** 
 
Dove in selezione troveremo la query da eseguire per ottenere la tabella.

Esempio: 

Abbiamo la tabella relazione_clienti contenente la chiave primaria dipendente e quella cliente, potremmo voler visualizzare la relazione senza dover ogni volta scrivere la query, dunque scriviamo:

> [!brown] Query dipendenti lavorano per aziende
> SELECT t1.id_dipendente, t1.nome, t1.cognome, t1.stipendio, t3.denominazione AS nome_azienda
> FROM dipendenti as t1
> LEFT JOIN rapporto_clienti as t2 
> ON t1.id_dipendente = t2.id_dipendente 
> LEFT JOIN clienti as t3 
> ON t2.id_cliente = t3.id_cliente

è la query, adesso creiamo una la nostra VIEW (o vista):

> [!brown] VIEW: Dipendenti impiegati nelle aziende
> CREATE OR REPLACE VIEW dipendentiImpiegati AS 
> SELECT t1.id_dipendente, t1.nome, t1.cognome, t1.stipendio, t3.denominazione AS nome_azienda
> FROM dipendenti as t1
> LEFT JOIN rapporto_clienti as t2 
> ON t1.id_dipendente = t2.id_dipendente 
> LEFT JOIN clienti as t3 
> ON t2.id_cliente = t3.id_cliente


> [!warning] Importante utilità delle VISTE (o VIEW)
> È possibile aggiornare i dati delle diverse tabelle, direttamente lavorando sulla VISTA, che in questo caso funge sostanzialmente da PUNTATORE. 
> Dunque fare una UPDATE su dei record all'interno della VIEW, permetterà di aggiornarle nelle loro tabelle fisiche di appartenenza. 
> 
> Esempio:
> 
> UPDATE dipendentiimpiegati SET stipendio = 6000
> WHERE id_dipendente = 1

| ID_dipendente | nome   | Cognome | stipendio                                  | dataAssunzione | mansione                 | id_ufficio |
| ------------- | ------ | ------- | ------------------------------------------ | -------------- | ------------------------ | ---------- |
| 1             | Mario  | Rossi   | <span style = "color: red"> 6000.00</span> | 2010-10-02     | Economy Advisor          | 1          |
| 2             | Luigi  | Verdi   | 3290.00                                    | 2020-12-20     | Senior Developer Advisor | 2          |
| 3             | Emma   | Marroni | 4800.00                                    | 2018-08-08     | Business Lawyer          | 3          |
| 4             | Gianni | Rossi   | 3000.00                                    | 2010-04-18     | Project Advisor          | 2          |
| 5             | Ella   | Verdi   | 3500.00                                    | 2022-02-22     | Senior General Advisor   | 2          |
| 6             | Marco  | Marroni | 1980.00                                    | 2025-09-28     | Project Advisor          | NULL       |
Adesso, se andiamo a controllare la tabella fisica Dipendenti, notiamo che Mario Rossi (ID = 1) avrà DAVVERO uno stipendio di 6000! 


> [!warning] Non è sempre possibile aggiornare i dati attraverso la Vista
> Teoricamente è possibile eseguire operazioni di **INSERT**, **UPDATE** e **DELETE** tramite le viste, tuttavia **non tutte le viste sono modificabili**. 
> In generale non sono modificabili se contengono:
> - Clausole del tipo: **DISTINCT**, **GROUP BY**, **HAVING**; 
> - Funzioni aggregate del tipo: **AVG()**, **COUNT()**, **SUM()**, **MIN()**, **MAX()**, etc.;
> - Operatori: **UNION**, **UNION ALL**, **CROSSJOIN**, **EXCEPT**, **INTERSECT** (*alcuni dei quali non abbiamo ancora visto*)
>   Sottoquery della clausola **WHERE** che si riferiscono a tabelle della clausola **FROM**. 

#### 17. Data e tempo
In un DB è molto importante saper immagazzinare informazioni temporali come il tempo e i giorni, vediamo adesso le tipologie presenti in SQL e come utilizzarli:


| Tipo      | Formato               | Valori ammessi                                      |
| --------- | --------------------- | --------------------------------------------------- |
| DATE      | YYYY-MM-DD            | da 1000-01-01 a 9999-12-31                          |
| TIME      | HH:MM:SS or HHH:MM:SS | -838:59:59 a 838:59:59                              |
| DATETIME  | YYYY-MM-DD HH:MM:SS   | da 1000-01-01 00:00:00 <br>a    9999-12-31 23:59:59 |
| TIMESTAMP | YYYY-MM-DD HH:MM:SS   | da 1970-01-01 00:00:00<br>a    2037-12-31 23:59:59  |
| YEAR      | YYYY                  | da 1901 a 2155                                      |
Intuibilmente YYYY anno, MM mese, DD giorno.

Tra le funzioni associate troviamo quella per tracciare un evento, per esempio la creazione di un record nella tabella:
- **NOW()**:
- **YEAR**(), **MONTH**(), **DAYOFMONTH**();
- **MONTHNAME**(), **DAYNAME**();
- **HOUR**(), **MINUTE**(), **SECOND**().

> [!Info] Funzione NOW() - tenere traccia creazione di un record
> INSERT INTO utente(nome, dataNascita, data_inserimento) 
> VALUES ('Mario Rossi', '1995-04-16', NOW());

Tuttavia inserire come parametro la funzione NOW() ad ogni inserimento è RIDONDANTE e inutilmente ripetitivo, dunque possiamo gestirlo direttamente nella creazione della tabella:

> [!Info] Tabella con data inserimento e modifica  
> CREATE TABLE IF NOT EXISTS utenti (
> id INT(4) NOT NULL PRIMARY KEY AUTO_INCREMENT, 
> nome VARCHAR(50) NOT NULL, 
> dataNascita DATE NOT NULL, 
> dataInserimento DATETIME DEFAULT CURRENT_TIMESTAMP, 
> dataModifica TIMESTAMP DEFAULT CURRENT_TIMESTAMP 
> 							ON UPDATE CURRENT_TIMESTAMP 
> );
> 

la data di modifica si rivela molto utile per esempio, si potrebbero gestire l'ultimo accesso, oppure ogni modifica al profilo, per esempio la biografia o la foto profilo in un Social. 

> [!Info] Funzione YEAR() - Selezione dell'anno di assunzione dipendenti
> **SELECT** nome, **YEAR**(dataAssunzione)
> **FROM** dipendenti

Risultato: 

| Nome   | AnnoAssunzione |
| ------ | :------------: |
| Mario  |      2010      |
| Luigi  |      2020      |
| Emma   |      2018      |
| Gianni |      2010      |
| Ella   |      2022      |
| Marco  |      2025      |
In modo analogo funzionano tutte le altre funzioni correlate. 

Come prima menzionato, il comando `DATE_FORMAT`:

Il comando `DATE_FORMAT(colonnaDate, '%e %M, %Y')`, dove
`%e` rappresenta il giorno
`%M` il mese
`%Y` l'anno

#### 18. Clonazione di una tabella
La clonazione di una tabella si rileva particolarmente utile per non utilizzare la tabella principale, magari per operazioni di test o comunque per non andare a modificare quella originale, magari in uso da utenti in tempo reale.  

> [!tip] Clonazione di struttura e dati della tabella 
> CREATE TABLE tabella_clone_dipendenti LIKE dipendenti

Questa non è una vista, ma una tabella fisica vera e propria. 

Potremmo anche creare una tabella che copia solamente i dati di quella originale, senza ALCUN VINCOLO (constraint) o chiave.


> [!tip] Clonazione dei soli dati di una tabella
> **CREATE TABLE** tabella_clone_dipendenti 
> **SELECT** * **FROM** dipendenti


#### 19. Tabelle temporanee
Le tabelle temporanee sono tabelle cloni che, una volta chiusa la sessione di lavoro, viene cancellata. 

> [!Pink] Tabella temporanea
> **CREATE TEMPORARY TABLE** temp1
> 
> Cancellazione (avviene automaticamente a fine sessione, ma utile se non devo terminare):
> **DELETE TEMPORARY TABLE** temp1;

Le tabelle temporanee solitamente non appaiono nella lista delle tabelle.  
Tutte le altre funzioni e operazioni sono analoghe a quelle di una normale tabella. 

---
----

Altri comandi: 

#### 20. READ ONLY MODE

Nel server SQL (NO MySQL o MariaDB) si può rendere una tabella o un database bloccato a solo lettura, ma il comando può differire in base all'ambiente, nella workbench MySQL per esempio il comando è:

> [!redwood] READ ONLY DB (o TABLE)
> **ALTER TABLE** myDB **READ ONLY** = 1


#### 21. RESTORE TABLE

Nei DB SQL ad ogni operazione non c'è di default un "torna indietro", quindi supponiamo per caso di avere una tabella piena di dati, e stiamo andando ad eliminare una riga: 
può capitare che per sbaglio ci si dimentichi la clausola WHERE o che questa includa anche elementi che non volevamo eliminare o alterare.

Di default infatti la **clausola** **"AUTOCOMMIT"** che corrisponde a "**CONFERMA AUTOMATICA**", 
è settato a VERO, ma è spesso una cosa indesiderata, perché l'errore umano è sempre dietro l'angolo. 
Dunque possiamo eseguire il comando:


> [!TIP] **SET** AUTOCOMMIT = OFF;  
> 

Adesso ad ogni query, se vogliamo mantenere il lavoro svolto dobbiamo eseguire il salvataggio MANUALMENTE, con il comando **COMMIT**


> [!tip] COMMIT - salvataggio manuale modifiche DB
> **COMMIT**;

Dunque, qualora avessimo eseguito delle operazioni e volessimo tornare indietro, basti eseguire il comando **ROLLBACK**: 

> [!tip] ROLLBACK - ripristina al salvataggio 
> **ROLLBACK**;

#### 22. ROLLUP:

La clausola ROLLUP è un'estensione della clausola GROUP BY, permette di produrre un'altra riga che mostri il risultato finale, es. di una somma (SUM) o una media (AVG).
La clausola ROLLUP si dice "**valore super-aggregato**". 

> [!pink] ROLLUP - general use 
> SELECT id, SUM(amount)
> FROM tabella
> GROUP BY id WITH ROLLUP

Esempio:

Senza ROLLUP:

| id_impiegato | stipendio |
| ------------ | --------- |
| 1            | 6000.00   |
| 2            | 3290.00   |
| 3            | 4800.00   |
| 4            | 3000.00   |
| 5            | 3500.00   |
| 6            | 1980.00   |
Con ROLLUP

| id_impiegato | stipendio                                  |
| ------------ | ------------------------------------------ |
| 1            | 6000.00                                    |
| 2            | 3290.00                                    |
| 3            | 4800.00                                    |
| 4            | 3000.00                                    |
| 5            | 3500.00                                    |
| 6            | 1980.00                                    |
| NULL         | <span style = "color: red">22570.00</span> |

#### 23. ON DELETE - Cancellazione di chiavi presenti in altre relazioni:
Tratta un argomento molto delicato per quanto riguarda la gestione del DB: 
- La **cancellazione di chiavi primarie** (`PK`) che **partecipano** come **chiavi esterne** (`FK`) in **altre** **tabelle** (o relazioni).
Normalmente il tentativo di **cancellare** una **chiave presente** in un'**altra tabella** **genera** un **errore**.
Ad esempio:
Vogliamo cancellare il dipendente con `ID_dipendente = 2` dalla tabella **Dipendenti**, questo generà errore in quanto `ID_dipendente = 2` è presente nella tabella **Rapporto_clienti**.

> [!FAILURE] Errore!
> Cannot delete or update a parent row: a foreign key constraint fails 
> (`db_uni`.`rapporto_clienti`, CONSTRAINT `rapporto_clienti_ibfk_2` FOREIGN KEY (`id_dipendente`) REFERENCES `dipendenti` (`id_dipendente`))
> 
> Praticamente:
> 
>"**Impossibile cancellare o modificare riga genitore**: è una chiave esterna nella tabella `rapporto_clienti`"

Possiamo forzare il DB a ignorare i vincoli di referenzialità, utilizzando il comando:

> [!tip] SET foreign_key_checks = 0;
> 

Dopodiché effettuare la cancellazione e ricordarsi di ripetere il comando assegnando questa volta **1** per riattivare il controllo sui **vincoli** di **referenzialità**. 

Questo ci permette di cancellare la riga in soggetto dalla tabella di origine (`Dipendenti`) ma non va a cancellare la riga nelle tabelle in cui viene fatto riferimento provocando una **violazione del vincolo di referenzialità!** 

> [!info] Come risolvere? Clausola ON DELETE:
> Utilizzando la clausola **ON DELETE** all'interno della tabella, dunque alla creazione o con una alterazione alla tabella (ALTER TABLE), otteniamo due approcci diversi:
>>[!pink] ON DELETE SET NULL :
>>Quando la chiave esterna viene eliminata al suo posto assegna `NULL`. 
>
>>[!pink] ON DELETE CASCADE : 
>>Quando la chiave esterna viene eliminata, elimina l'intera riga.

 Nella tabella dove si fa uso della chiave esterna scriviamo dopo il classico:
>[!pink] ON DELETE - usato durante creazione tabella
>**FOREIGN KEY** chiaveEsterna **REFERENCES** nomeTabella(chiaveEsterna) 
> **ON DELETE SET NULL** 
 -- oppure **ON DELETE CASCADE**. 

*Si ricorda che il simbolo `--` inizia il commento in SQL.*

Se invece avessimo già la tabella e dunque vogliamo modificarla procediamo aggiungendo un **CONSTRAINT** o vincolo:

> [!pink] ON DELETE - alterazione tabella 
> 
> **ALTER TABLE** nomeTabella
> **ADD CONSTRAINT** nomeVincoloChiave --facoltativo ma utile
> **FOREIGN** **KEY**(nomeChiave) **REFERENCES** tabellaChiave(nomeChiave)
> **ON DELETE SET NULL** --oppure **ON DELETE CASCADE**

Vediamo il funzionamento con le tabelle:

| id_rapporto | id_cliente | id_dipendente                        |
| ----------- | ---------- | ------------------------------------ |
| 1           | 1          | 1                                    |
| 2           | 2          | 1                                    |
| 3           | 3          | <span style = "color: red">2 </span> |
| 4           | 4          | 3                                    |
| 5           | 5          | <span style = "color: red">2 </span> |
| 6           | 6          | 4                                    |
| 7           | 7          | 3                                    |
| 8           | 8          | 4                                    |
| 9           | 9          | 5                                    |
| 10          | 10         | 6                                    |
Eliminiamo id_dipendente 2:

Caso 1) Sostituzione chiave con `NULL`: 

| id_rapporto | id_cliente | id_dipendente                           |
| ----------- | ---------- | --------------------------------------- |
| 1           | 1          | 1                                       |
| 2           | 2          | 1                                       |
| 3           | 3          | <span style = "color: red">NULL </span> |
| 4           | 4          | 3                                       |
| 5           | 5          | <span style = "color: red">NULL </span> |
| 6           | 6          | 4                                       |
| 7           | 7          | 3                                       |
| 8           | 8          | 4                                       |
| 9           | 9          | 5                                       |
| 10          | 10         | 6                                       |

Caso 2) Riga eliminata dalla tabella:

| id_rapporto | id_cliente | id_dipendente |
| ----------- | ---------- | ------------- |
| 1           | 1          | 1             |
| 2           | 2          | 1             |
| 4           | 4          | 3             |
| 6           | 6          | 4             |
| 7           | 7          | 3             |
| 8           | 8          | 4             |
| 9           | 9          | 5             |
| 10          | 10         | 6             |

#### 24. STORED PROCEDURES:

Una **STORED PROCEDURE** o semplicemente **PROCEDURA** è utilizzata per salvare delle query (o interrogazioni) che vengono usate spesso. 

Permette di dare il nome ad una intera query, e viene trattata come una funzione. Necessita della clausola **CALL** per essere chiamata. 
Esempio:
>[!tip] CALL get_clienti();

Per creare una procedura serve prima di tutto una query utile, questa sarà query si troverà dopo la definizione della procedura:


> [!tip] CREATE PROCEDURE nomeProcedura()

e la query sarà delimitata da un **BEGIN** all'inizio e un **END** alla fine.

> [!brown] Query da salvare:
> **CALL** get_clienti();
> **BEGIN**
>  -- tab --  **SELECT** * **FROM** Clienti;
> **END;**

C'è un problema: abbiamo due chiusure `;` , entrambe corrette la prima termina la query, la seconda termina la procedura. 
Questo problema non accade con tutti i DBMS, dipende dalla versione di SQL (solitamente in MySQL e MariaDB).
In caso di problemi con le chiusure `;` utilizziamo la clausola 

> [!TIP] DELIMITER
> `DELIMITER` `$$`  (più utilizzato)
> oppure:
> `DELIMITER` `//` 

Scrivendo dunque la procedura in questo modo:

> [!brown] Query da salvare:
> `DELIMITER` `$$`
> **CALL** get_clienti();
> **BEGIN**
>  -- tab --  **SELECT** * **FROM** Clienti;
> **END `$$`
> DELIMITER ;

 Per eliminare la procedura, basta un semplice: 
 **DROP PROCEDURE** nomeProcedura

> [!warning] Parametri in una procedura:
> Possiamo passare dei parametri alla nostra Procedura, per esempio per svolgere una ricerca all'interno della nostra Query salvata: 
>  
>  > [!redwood] Esempio procedura con parametro 
>  > `DELIMITER` `$$`
>  > **CREATE PROCEDURE** get_clienti(IN id INT)
>  >**BEGIN**
 > > **select** * **from** clienti
 > > **WHERE** id_cliente = id;
>  >**end** `$$`
>  >**DELIMITER**;
>
> Dunque alla chiamata a funzione possiamo passare il parametro, in questo caso di tipo **INT**: 
>>[!redwood] Chiamata a Procedura con parametro:
>>**CALL** get_clienti(2);
>
> Stiamo andando a chiamare la procedura che va a selezionare tutti gli attributi del cliente con `ID = 2`. 

Analogamente si possono trattare tutti gli altri tipi di dato e senza un limite di parametri, altro esempio:

> [!brown] Esempio con stringhe come parametri:
> `DELIMITER` `$$` 
> **CREATE PROCEDURE** get_clienti(**IN** nomeAzienda **VARCHAR**(255), **IN** citta **VARCHAR**(50))
> **BEGIN** 
 > **SELECT** * 
 > **FROM** clienti
 > **WHERE** denominazione = nomeAzienda **AND** sede = citta;
>`END` `$$`
>**DELIMITER** ;

Dunque:

> [!brown] CALL get_clienti("Microsoft", "Roma");

Vantaggi delle procedure:
- ridurre il traffico sulla rete, migliorando le prestazioni generali;
- rendere l'accesso alle informazioni del DB più sicure, in quanto l'admin può decidere quali informazioni mostrare ad un utente o ad una applicazione.
Svantaggi:
- Aumenta la memoria usata ad ogni connessione. 
#### 25. TRIGGERS




----
Fonti:
- Introduzione e Algebra Relazionale:
	$^1$Appunti lezione UniCT corso di laurea triennale L-31, prof. Alaimo 
	$^2$Libro "Basi di Dati" VI edizione di Paolo Azteni, Stefano Ceri, etc.
- Parte SQL:
	$^3$TutorialRepublic: https://www.tutorialrepublic.com/sql-tutorial/
	$^4$W3School: https://www.w3schools.com/sql/
	$^5$YouTube (Edoardo Midali): https://www.youtube.com/watch?v=fLalNzuRdsw
	$^6$YouTube (Bro Code): https://www.youtube.com/watch?v=5OdVJbNCSso
