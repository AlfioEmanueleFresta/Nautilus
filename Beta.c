/*
** NAUTILUS BETA
** © Pensiero Profondo
*/

/* TODO COSTANTI */
#define VELOCITA_BRACCIO 60
#define VELOCITA_PINZA 40
#define GRADI_BRACCIO 30
#define GRADI_PINZA 20
#define VELOCITA_CALIBRAZIONE 5

/* Lista dei Motori e sensori su Beta: 
** A) PINZA
** B) BRACCIO 1
** C) BRACCIO 2
** S0) TOCCO CALIBRAZIONE
** S1) /
** S2) /
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
	// TODO, legge e posiziona in Ricevere[8],
	// Poi spatte in S0, S1, S2, A.
	// Passa il timeslice()
}

void inviaMessaggio  () {
	// TODO
	// Crea Inviare[8]
	// Manda S3, S4, S5, C
	// Passa il timeslice()
}

/* Invia il callback */
void callback ( int Azione ) {
	// TODO
	// Imposta C.
	// Aspetta che A torni a 0.
}

/* TASK COMUNICAZIONE */
task Ricevi () {
	while ( 1 ) {
	
		// Ricevi...
		leggiMessaggio();
	
		// Se un'azione è stata intrapresa...
		if ( A != 0 ) {
	
			// Scegli azione da intraprendere...
			switch ( A ) {
				case 1:
					scrivi("BETA:Calibrazione braccio.");
					calibraBraccio();
				break;
				case 2:
					scrivi("BETA:Apertura braccio.");
					apriBraccio();
				break;
				case 3:
					scrivi("BETA:Chiusura braccio.");
					chiudiBraccio();
				break;
				case 4:
					scrivi("BETA:Apertura pinza.");
					apriPinza();
				break;
				case 5:
					scrivi("BETA:Chisura pinza.");
					chiudiPinza();
				break;
				case 42:
					scrivi("Connesso.");
				break;
			}
	
			// Torna il callback, aspetta...
			scrivi("BETA:Callback.");
			callback( A );
		} else {
			scrivi("BETA:Attesa...");
		}
	
		// TODO Fine timeslice.
	}
}

task Invia () {
	// Imposta gli ultimi.
	int lS3, lS4, lS5, lC;
	lS3 = lS4 = lS5 = lC = -1;
	while ( 1 ) {
		// Se qualcosa è stato modificato...
		if ( S3 != lS3 || S4 != lS4 || S5 != lS5 || lC |= C ) {
			lS3 = S3;
			lS4 = S4;
			lS5 = S5;
			lC = C;
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


/* FUNZIONI DI AZIONE */
void muoviBraccio ( int Gradi ) {
	// TODO
}

void apriBraccio () {
	muoviBraccio ( GRADI_BRACCIO );
}

void chiudiBraccio () {
	muoviBraccio ( -GRADI_BRACCIO );
}

void muoviPinza ( int Gradi ) {
	// TODO
}

void apriPinza () {
	muoviPinza ( GRADI_PINZA );
}

void chidiPinza () {
	muoviPinza ( -GRADI_PINZA );
}

void calibraBraccio () {
	while ( !S3 ) {
		// TODO Muovi braccio a velocita -VELOCITA_CALIBRAZIONE
	}
	// TODO FERMA BRACCIO
}


void scrivi(const char* stringa) {
	// TODO
}

/* TASK PRINCIPALE */

task main () {

	scrivi("Accensione BETA...");
	aspetta(300);

	/* IMPOSTAZIONE MOTORI */
	// TODO Imposta Comunicazione HS
	// TODO Sincronizza BC, rapporto 1:1
		
	/* IMPOSTA VALORI A ZERO */
	S0 = S1 = S2 = S3 = S4 = S5 = 0;
	A = C = 0;
	
	/* AVVIA I TASK */
	startTask(Sensori);
	startTask(Ricevi);
	startTask(Invia);
	
	/* Avvisa accensione.... */
	scrivi("Nautilus BETA pronto...");
	
	/* Rimani in attesa, esegui i comandi. */
	while ( 1 ) {
		// Esegui gli altri task.
		// TODO Fine timeslice.
	}
	
}
