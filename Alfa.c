/*
** NAUTILUS ALFA
** © Pensiero Profondo
*/

#define VELOCITA_MARCIA 60
#define VELOCITA_ROTAZIONE 40
#define CIRCONFERENZA_RUOTA 10 // In centimetri.
#define SOGLIA_OSTACOLO 30

#pragma config(Sensor, S1,	sensoreAllineamento,	sensorTouch)
#pragma config(Sensor, S2,	sensoreToccoDestro,	sensorTouch)
#pragma config(Sensor, S2,	sensoreToccoSinistro,	sensorTouch)


/* Lista dei Motori e sensori su Alfa:
** A) PINZA
** B) MOTORE DESTRA
** C) MOTORE SINSITRA
** Sen1) ULTRASUONI
** Sen2) TOCCO ANTERIORE DESTRO
** Sen3) TOCCO ANTERIORE SINISTRO
** Sen4) COMUNICAZIONE HS
*/

/* Lista delle Azioni su Beta:
** 0) Nessuna azione, ATTESA.
** 1) Calibrazione braccio.
** 2) Apri Braccio.
** 3) Chiudi Braccio.
** 4) Apri Pinza.
** 5) Chiudi Pinza.
*/

int Sen0, Sen1, Sen2;
int Sen3, Sen4, Sen5;

byte Inviare[4];
byte Ricevere[4];

int A, C;

/* PROTOTIPI */

void aspetta(int Millisecondi);
void leggiSensori();
void leggiMessaggio();
void inviaMessaggio();
void beta(int Azione);
task Ricevi();
task Invia();
task Sensori();
void cammina(int Velocita);
void fermo();
int centimetri2gradi ( int Centimetri );
int gradi2centimetri ( int Gradi );
void vaiAvanti ( int Centimetri );
void vaiIndietro ( int Centimetri );
void ruota(int Gradi);
void giraDestra();
void giraSinistra();
bool presenteOstacolo();
void allinea();
void aspettaPulsante();
void pulisci();
void pulisciRiga (int riga);
void scrivi(int riga, const char* stringa);
void calibraBraccio();
void apriBraccio();
void apriPinza();
void chiudiPinza();

/* FUNZIONI FONDAMENTALI */

//Implementata!
void aspetta ( int Millisecondi ) {
	wait1Msec(Millisecondi);
}

void leggiSensori () {
	Sen0 = SensorValue[sensoreAllineamento];
	Sen1 = SensorValue[sensoreToccoDestro];
	Sen2 = SensorValue[sensoreToccoSinistro];
}

/* FUNZIONI DI COMUNICAZIONE */
void leggiMessaggio () {
	if (nxtGetAvailHSBytes() >= 4) {
	  	nxtReadRawHS(Ricevere, 4);
	  	Sen3 = Ricevere[0];
	  	Sen4 = Ricevere[1];
	  	Sen5 = Ricevere[2];
	  	C = Ricevere[3];
  	}
}

void inviaMessaggio  () {
	Inviare[0] = Sen0;
	Inviare[1] = Sen1;
	Inviare[2] = Sen2;
	Inviare[3] = A;
	nxtWriteRawHS(Inviare, 4);
}

/* Esegue un'azione su Beta. */
void beta ( int Azione ) {
	A = Azione;
	while ( C != Azione ) {
		aspetta(10);
	}
	A = 0;
	aspetta(50);
}

/* TASK COMUNICAZIONE */
task Ricevi () {
	while ( 1 ) {
		leggiMessaggio();
		EndTimeslice();
	}
}

task Invia() {
	// Imposta gli Ultimi.
	int lSen0, lSen1, lSen2, lA;
	lSen0 = lSen1 = lSen2 = lA = -1;
	while ( 1 ) {
		// Se qualcosa è stato modificato...
		if ( Sen0 != lSen0 || Sen1 != lSen1 || Sen2 != lSen2 || A != lA ) {
			lSen0 = Sen0;
			lSen1 = Sen1;
			lSen2 = Sen2;
			lA = A;
			inviaMessaggio();
		}
		EndTimeslice();
	}
}

/* TASK AGGIORNAMENTO */
task Sensori () {
	while ( 1 ) {
		leggiSensori();
		EndTimeslice();
	}
}

/* FUNZIONI DI MOVIMENTO */
void cammina ( int Velocita ) {
	nSyncedTurnRatio = 100;
	nMotorEncoder[motorB] = Velocita;
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
	nSyncedTurnRatio = 100;
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = centimetri2gradi(Centimetri);
	motor[motorB] = VELOCITA_MARCIA * sgn(Centimetri);
	while(nMotorRunState[motorB] != runStateIdle)  {}
	fermo();
}

void vaiIndietro ( int Centimetri ) {
	vaiAvanti ( -Centimetri );
}

void ruota ( int Gradi ) {
	nSyncedTurnRatio = -100;
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = Gradi;
	motor[motorB] = VELOCITA_ROTAZIONE * sgn(Gradi);
	while(nMotorRunState[motorB] != runStateIdle)  {}
	fermo();
}

void giraDestra () {
	ruota ( 90 );
}

void giraSinistra () {
	ruota ( -90 );
}

bool presenteOstacolo () {
	if ( Sen0 <= SOGLIA_OSTACOLO ) {
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
		velocita *= -0.6;
	}
	fermo();
}

bool pulsantePremuto() {
	if ( nNxtButtonPressed == 3 ) {
		return 1;
	} else {
		return 0;
	}
}

void aspettaPulsante () {
	while ( !pulsantePremuto() ) {
		aspetta(5);
	}
	aspetta(150);
}

//nuova!
void pulisci(){
	eraseDisplay();
	//Pulisce l'intero schermo
}

//Nuova!
void pulisciRiga (int riga){
	nxtDisplayClearTextLine(riga);
//Pulisce la riga indicata
}

//Implementata!
void scrivi(int riga, const char* stringa) {
	nxtDisplayTextLine(riga, stringa);
	//Pulisce la riga indicata e vi scrive.
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

	pulisci();
	scrivi(2,"Benvenuti in Nautilus.");
	aspetta(1000);
	scrivi(4,"Accensione motori...");
	aspetta(1000);

	/* IMPOSTAZIONE MOTORI */
	SensorType[Sen4] = sensorHighSpeed;
	nxtHS_Mode = hsRawMode;
	// Modalita' frenata
	bFloatDuringInactiveMotorPWM = false;
	nSyncedMotors = synchBC;

	/* IMPOSTA VALORI A ZERO */
	Sen0 = Sen1 = Sen2 = Sen3 = Sen4 = Sen5 = 0;
	A = C = 0;

	/* AVVIA I TASK */
	StartTask(Sensori);
	StartTask(Ricevi);
	StartTask(Invia);

	pulisci();
	scrivi(2, "Aperto braccio Nautilus BETA?");
	aspettaPulsante();
	scrivi(4, "Accendere Nautilus BETA. Fatto?");
	aspettaPulsante();
	scrivi(6, "Check comunicazione.");
	aspetta(1000);
	beta(42);

	/* Avvia calibrazione */
	pulisci();
	scrivi("Calibrazione braccio...");
	calibraBraccio();

	/* PRONTO */
	pulisci();
	scrivi("Nautilus pronto. Start?");
	aspettaPulsante();

	/* SERIE DI AZIONI */

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
	pulisci();
	scrivi(2,"Nautilus BYE.");
	aspetta(3000);

}