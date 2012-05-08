Nautilus
========

Nautilus è il nome del robot presentato dalla squadra 'Pensiero Profondo' dell'ITIS E. Fermi di Giarre (CT),
in occasione della competizione 'Minirobotics 2012' presso l'Università di Catania. 

Il nome Nautilus è un riferimento a 'Ventimila leghe sotto i mari', mentre 'Pensiero profondo', ovvero il nome
scelto per il team è un riferimento al supercomputer utilizzato in 'Guida galattica per autostoppisti'
per calcolare la risposta alla domanda fondamentale sulla vita, l'universo e tutto quanto.


Codice
========

Codice di Nautilus (controllori Alfa e Beta).

Nautilus utilizza due controllori NXT, programmati in linguaggio C (RoboC)
e collegati tramite cavo HS sulla porta 4.
Ogni controllore è programmato in multitasking, ed esegue quattro task:

 * Invia
 * Riceve
 * Sensori
 * main

Dove Invia è il task che si occupa di inviare i valori delle variabili interne al loro
cambiamento, Ricevi di ottenere quelle nel buffer della coda in ricezione. Sensori
si occupa di rivelare il valore ottenuto dai sensori ed aggiornare le variabili
locali al controllore. Main si occupa di preparare il robot per l'avvio, controllare
l'interconnessione ed eseguire il corpo vero e proprio del programma (su Alpha).