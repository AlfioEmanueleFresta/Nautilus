/*
** NAUTILUS ALFA
** © Pensiero Profondo
*/

/* TODO COSTANTI */
#define VELOCITA_MARCIA 60
#define VELOCITA_ROTAZIONE 40
#define CIRCONFERENZA_RUOTA 10 // In centimetri.
#define SOGLIA_OSTACOLO 30

/* Lista dei Motori e sensori su Alfa: 
** A) IDRAULICO
** B) MOTORE DESTRA
** C) MOTORE SINSITRA
** S0) ULTRASUONI
** S1) TOCCO ANTERIORE DESTRO
** S2) TOCCO ANTERIORE SINISTRO
** S4) COMUNICAZIONE HS
*/

/* Lista delle Azioni su Beta:
** 0) Nessuna azione, ATTESA.
** 1) Calibrazione braccio.
** 2) Apri Braccio.
** 3) Chiudi Braccio.
** 4) Apri Pinza.
** 5) Chiudi Pinza.
*/

int S0, S1, S2;
int S3, S4, S5;

int Inviare[4];
int Ricevere[4];

int A, C;

/* FUNZIONI FONDAMENTALI */
void aspetta ( int Millisecondi ) {
	// TODO 
}

void leggiSensori () {
	// TODO
}

/* FUNZIONI DI COMUNICAZIONE */
void leggiMessaggio () {
	// TODO: se presenti messaggi in coda...
	// TODO, legge e posiziona in Ricevere[8],
	// Poi spatte in S3, S4, S5, C.
	// TODO: cancella la coda.
}

void inviaMessaggio  () {
	// TODO
	// Crea Inviare[8]
	// Manda S0, S1, S2, A
}

/* Esegue un'azione su Beta. */
void beta ( int Azione ) {
	// TODO
	// Imposta A.
	// Aspetta che C diventi A.
	// Reimposta A = 0;
	// Aspetta qualche millisecondo...
}

/* TASK COMUNICAZIONE */
task Ricevi () {
	while ( 1 ) {
		leggiMessaggio();
		// TODO Fine timeslice.
	}
}

task Invia() {
	// Imposta gli Ultimi.
	int lS0, lS1, lS2, lA;
	lS0 = lS1 = lS2 = lA = -1;
	while ( 1 ) {
		// Se qualcosa è stato modificato...
		if ( S0 != lS0 || S1 != lS1 || S2 != lS2 || A != lA ) {
			lS0 = S0;
			lS1 = S1;
			lS2 = S2;
			lA = A;
			inviaMessaggio();
		}
		// TODO Fine timeslice.
	}
}

/* TASK AGGIORNAMENTO */
task Sensori () {
	while ( 1 ) {
		leggiSensori();
		// TODO Fine timeslice.
	}
}


/* FUNZIONI DI MOVIMENTO */
void cammina ( int Velocita ) {
	// Imposta movimento sincronizzato
	// a velocità...
	// TODO Sync 1:1
}

void fermo() {
	cammina(0);
}


int centimetri2gradi ( int Centimetri ) {
	return ( Centimetri * 360 / CIRCONFERENZA_RUOTA );
}

int gradi2centimetri ( int Gradi ) {
	return ( Gradi * CIRCONFERENZA_RUOTA / 360 );
}

void vaiAvanti ( int Centimetri ) {
	// TODO IMPOSTA GIRI A ZERO
	//				TODO
	while ( abs(gradi2centimetri([GIRIPERCORSI])) < abs(Centimetri) ) {
		cammina(VELOCITA_MARCIA);
	}
	fermo();
}

void vaiIndietro ( int Centimetri ) {
	vaiAvanti ( -Centimetri );
}

void ruota ( int Gradi ) {
	// TODO Rapporto Sync 1:-1
	// TODO Imposta giri a zero
	while ( abs([GRADIPERCORSI]) < abs(Gradi) ) {
		// TODO Cammina...
		// Velocità: VELOCITA_ROTAZIONE * sgn(Gradi)
	}
	fermo();
}

void giraDestra () {
	ruota ( 90 );
}

void giraSinistra () {
	ruota ( -90 );
}

bool presenteOstacolo () {
	if ( S0 <= SOGLIA_OSTACOLO ) {
		return 1;
	} else {
		return 0;
	}
}
	
void allinea () {
	vaiIndietro ( 5 );
	int velocita = 80;
	while ( velocita > 5 ) {
		while ( presenteOstacolo() ) {
			cammina(velocita);
		}
		// Inverte e dimezza velocità.
		velocita *= -0.5;
	}
	fermo();
}

void aspettaPulsante () {
	// TODO
	while ( !pulsantePremuto ) {
		aspetta(5);
	}
	aspetta(150);
}

void scrivi(const char* stringa) {
	// TODO
}

/* ADATTATORI AZIONI BETA */
void calibraBraccio () {
	beta(1);
}

void apriBraccio() {
	beta(2);
}

void chiudiBraccio() {
	beta(3);
}

void apriPinza() {
	beta(4);
}

void chiudiPinza() {
	beta(5);
}


/* TASK PRINCIPALE */

task main () {

	scrivi("Benvenuti in Nautilus.");
	aspetta(1000);
	scrivi("Accensione motori...");
	aspetta(1000);

	/* IMPOSTAZIONE MOTORI */
	// TODO Imposta Comunicazione HS
	// TODO Sincronizza BC.
	// TODO Motori Frenati.
		
	/* IMPOSTA VALORI A ZERO */
	S0 = S1 = S2 = S3 = S4 = S5 = 0;
	A = C = 0;
	
	/* AVVIA I TASK */
	startTask(Sensori);
	startTask(Ricevi);
	startTask(Invia);
	
	scrivi("Aperto braccio Nautilus BETA?");
	aspettaPulsante();
	scrivi("Accendere Nautilus BETA. Fatto?");
	aspettaPulsante();
	scrivi("Check comunicazione.");
	aspetta(1000);
	beta(42);
	
	/* Avvia calibrazione */
	scrivi("Calibrazione braccio...");
	calibraBraccio();
	
	/* PRONTO */
	scrivi("Nautilus pronto. Start?");
	aspettaPulsante();
	
	/* SERIE DI AZIONI */
	// TODO RISOLVI IL PERCORSO.
	
	// Per ora gioca un po'.
	vaiAvanti(15);
	vaiIndietro(10);
	giraDestra();
	giraSinistra();
	giraSinistra();
	giraDestra();
	giraSinistra();
	giraSinistra();
	vaiAvanti(5);
	giraDestra();
	giraDestra();
	
	
	
	
	/* MORTE */
	scrivi("Nautilus BYE.");
	aspetta(3000);
	
}
