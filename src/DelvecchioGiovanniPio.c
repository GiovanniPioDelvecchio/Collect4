/*
 ============================================================================
 Name        : DelvecchioGiovanniPio.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//tipi di dato utilizzati
typedef char* stringa;
typedef char** campo;
typedef struct
{
	int righe;
	int colonne;
	int ngiocatori;
	char* giocatori;
	int xconzero;
	int yconzero;
}impostazioni;


//funzione necessaria per spostarsi lungo le posizioni della console
void gotoxy(int x, int y);

//operazioni su alcuni elementi dell' interfaccia
void stampaSchermataIniziale(impostazioni imp);
void stampaTitolo();

void stampaMessaggioDiPareggio(impostazioni imp);
void stampaMessaggioDiVittoria( campo cmp,impostazioni imp);

//operazioni sul tipo di dato impostazioni
impostazioni scrivereValoreRighe(impostazioni imp, int valore);
int leggereValoreRighe(impostazioni imp);
impostazioni scrivereValoreColonne(impostazioni imp, int valore);
int leggereValoreColonne(impostazioni imp);
impostazioni scrivereValoreNgiocatori(impostazioni imp, int valore);
int leggereValoreNgiocatori(impostazioni imp);
void allocareGiocatori(impostazioni *imp);
impostazioni scrivereValoreGiocatori(impostazioni imp, int numplayer ,char g);
char leggereValoreGiocatori(impostazioni imp, int numplayer);
impostazioni scrivereValoreXconzero(impostazioni imp, int valore);
int leggereValoreXconzero(impostazioni imp);
impostazioni scrivereValoreYconzero(impostazioni imp, int valore);
int leggereValoreYconzero(impostazioni imp);


//Funzioni riguardanti il tipo di dato file
void creaFileDefault(FILE *def, stringa nomdef);
char richiestaImpostazioni(impostazioni imp);
void cambioImpostazioni(FILE *imps, stringa nomfile, impostazioni imp);
int acquisizioneInteroConVincoli(int min, int max);
void scritturaInteroSuFile(FILE *imps, int num);
char acquisizioneGiocatore();
void scritturaCarattereSuFile(FILE *imps, char car);
impostazioni inizializzaImpostazioni(FILE *imps, impostazioni imp);
void creaDefaultSeManca(FILE *def, stringa nomdef);
impostazioni gestisciImpostazioni(FILE *imps, stringa nomfile, stringa nomdef, char richiestai ,impostazioni imp);


//operazioni necessarie per stampare la griglia di gioco ed i suoi elementi
void scrivereStringa(stringa str, int pos, char valore);
void inizializzazioneStringaPrimaRiga(stringa str, int col);
void inizializzazioneStringaUltimaRiga(stringa str, int col);
void inizializzazioneStringaRigaVerticale(stringa str, int col);
void inizializzazioneStringaRigaInterstiziale(stringa str, int col);
void stampaCampo( int rig, int col, int xconzero, int yconzero);
void stampaRiferimentoColonne(int col, int xconzero, int yconzero, int yoffset);
void stamparePedina(campo cmp, int rmax, int c, int xconzero, int yconzero);

//operazioni sul tipo di dato campo
void allocazioneMemoriaCampo(campo* cmp, int rig, int col);
void scrivereValoreCampo(campo cmp, int r, int c, char valore);
int leggereValoreCampo(campo cmp, int r, int c);
void inizializzazioneCampo(campo cmp, int rmax, int cmax);
void scriverePedinaCampo(campo cmp,int rmax ,int c, char pedina);

//operazioni che compongono il gameplay
int richiestaPosizione(campo cmp, impostazioni imp, char giocatore);
void svolgimentoPartita(impostazioni imp, campo cmp);
void eseguiTurno(impostazioni imp, campo cmp, int ngiocatore);





//controlli sul campo per valutare se la partita è finita o meno e con che esito
int controlloCampo(campo cmp, int rig, int col, char giocatore);
int controlloPareggio(campo cmp, impostazioni imp);
int controllaCampoPerGiocatore(campo cmp, impostazioni imp);




int main(void) {
	FILE *imps;
	FILE *def;
	impostazioni imp;
	stringa nomfile;
	stringa nomdef;
	campo cmp;
	int xconzero;
	int yconzero;
	int xoffset;
	int yoffset;
	char richiestai;
	int dimstring;



	xconzero = 15;
	yconzero = 4;


	imp = scrivereValoreXconzero(imp, xconzero);
	imp = scrivereValoreYconzero(imp, yconzero);


	stampaSchermataIniziale(imp);


	system("pause");
	system("cls");

	stampaTitolo();
	dimstring = 24;
	nomdef = (stringa)malloc(dimstring*sizeof(char));
	nomdef = "impostazioni_default.f4";

	def = NULL;
	creaDefaultSeManca(def,  nomdef);

	dimstring = 16;
	nomfile = (stringa)malloc(dimstring*sizeof(char));
	nomfile = "impostazioni.f4";
	richiestai = richiestaImpostazioni(imp);

	imps = NULL;
	imp =  gestisciImpostazioni(imps,  nomfile,  nomdef,  richiestai , imp);



	system("pause");
	system("cls");


	stampaTitolo();



	xoffset = 25;
	imp = scrivereValoreXconzero(imp ,xconzero + xoffset);
	stampaCampo(leggereValoreRighe(imp), leggereValoreColonne(imp), leggereValoreXconzero(imp), leggereValoreYconzero(imp));
	allocazioneMemoriaCampo(&cmp,leggereValoreRighe(imp),leggereValoreColonne(imp));
	inizializzazioneCampo(cmp, leggereValoreRighe(imp), leggereValoreColonne(imp));


	svolgimentoPartita(imp, cmp);


	if(controlloPareggio(cmp, imp)==1)
	{
		stampaMessaggioDiVittoria(cmp, imp);
	}
	else
	{
		stampaMessaggioDiPareggio(imp);
	}

	xoffset = -15;
	yoffset = 21;
	gotoxy(leggereValoreXconzero(imp) + xoffset, leggereValoreYconzero(imp)+ yoffset);


	system("pause");
	return 0;
}

//Menù iniziale

void stampaSchermataIniziale(impostazioni imp)
{
	int xconzero;
	int yconzero;
	int xoffset;
	int yoffset;

	xconzero = leggereValoreXconzero(imp);
	yconzero = leggereValoreYconzero(imp);

	xoffset = 23;
	yoffset = 3;
	gotoxy(xconzero + xoffset, yconzero+yoffset);
	puts("______  _____ ______  ______  ___      ___ ");
	yoffset = yoffset +1;
	gotoxy(xconzero + xoffset, yconzero+yoffset);
	puts("|  ___||  _  || ___ \\|___  / / _ \\    /   |");
	yoffset = yoffset +1;
	gotoxy(xconzero + xoffset, yconzero+yoffset);
	puts("| |_   | | | || |_/ /   / / / /_\\ \\  / /| |");
	yoffset = yoffset +1;
	gotoxy(xconzero + xoffset, yconzero+yoffset);
	puts("|  _|  | | | ||    /   / /  |  _  | / /_| |");
	yoffset = yoffset +1;
	gotoxy(xconzero + xoffset, yconzero+yoffset);
	puts("| |    \\ \\_/ /| |\\ \\ ./ /___| | | | \\___  |");
	yoffset = yoffset +1;
	gotoxy(xconzero + xoffset, yconzero+yoffset);
	puts("\\_|     \\___/ \\_| \\_|\\_____/\\_| |_/     |_/");

	yoffset = yoffset +1;
	gotoxy(xconzero + xoffset, yconzero+yoffset);

}

//Funzioni sulle impostazioni di gioco
impostazioni scrivereValoreRighe(impostazioni imp, int valore)
{
	imp.righe = valore;
	return imp;
}

int leggereValoreRighe(impostazioni imp)
{
	int valore;
	valore = imp.righe;
	return valore;
}

impostazioni scrivereValoreColonne(impostazioni imp, int valore)
{
	imp.colonne = valore;
	return imp;
}


int leggereValoreColonne(impostazioni imp)
{
	int valore;
	valore = imp.colonne;
	return valore;
}

impostazioni scrivereValoreNgiocatori(impostazioni imp, int valore)
{
	imp.ngiocatori = valore;
	return imp;
}

int leggereValoreNgiocatori(impostazioni imp)
{
	int valore;
	valore = imp.ngiocatori;
	return valore;
}

void allocareGiocatori(impostazioni *imp)
{
	imp->giocatori = (char*)malloc(leggereValoreNgiocatori(*imp)*sizeof(char));
}

impostazioni scrivereValoreGiocatori(impostazioni imp, int numplayer ,char g)
{
	*(imp.giocatori + numplayer - 1) = g;
	return imp;
}

char leggereValoreGiocatori(impostazioni imp, int numplayer)
{
	char g;
	g = *(imp.giocatori + numplayer - 1);
	return g;
}

impostazioni scrivereValoreXconzero(impostazioni imp, int valore)
{
	imp.xconzero = valore;
	return imp;
}

int leggereValoreXconzero(impostazioni imp)
{
	int valore;
	valore = imp.xconzero;
	return valore;
}

impostazioni scrivereValoreYconzero(impostazioni imp, int valore)
{
	imp.yconzero = valore;
	return imp;
}

int leggereValoreYconzero(impostazioni imp)
{
	int valore;
	valore = imp.yconzero;
	return valore;
}

//Funzioni riguardanti il tipo di dato file
void creaFileDefault(FILE *def, stringa nomdef)
{
	int stdriga;
	int stdcolonna;
	int stdngiocatori;
	char stdgiocatore1;
	char stdgiocatore2;
	int xconzero;
	int yconzero;

	stdriga = 6;
	stdcolonna = 7;
	stdngiocatori = 2;
	stdgiocatore1 = 'x';
	stdgiocatore2 = 'o';
	xconzero = 15;
	yconzero = 4;

	def = fopen(nomdef, "w");
	scritturaInteroSuFile(def, stdriga);
	scritturaInteroSuFile(def, stdcolonna);
	scritturaInteroSuFile(def, stdngiocatori);
	scritturaCarattereSuFile(def, stdgiocatore1);
	scritturaCarattereSuFile(def, stdgiocatore2);
	scritturaInteroSuFile(def, xconzero);
	scritturaInteroSuFile(def, yconzero);
	fclose(def);
}


char richiestaImpostazioni(impostazioni imp)
{
	int xoffset;
	int yoffset;
	char risposta;


	xoffset = - leggereValoreXconzero(imp);
	yoffset = 1-leggereValoreYconzero(imp);
	gotoxy(leggereValoreXconzero(imp) + xoffset, leggereValoreYconzero(imp) + yoffset);
	printf("Vuoi cambiare le impostazioni? (premere s per si, n per no e r per giocare con le impostazioni di default)");
	do{
		risposta = getch();
		printf("%c", risposta);

	}while(risposta != 's' && risposta != 'n' && risposta != 'r');
	printf("\n");
	return risposta;
}

void cambioImpostazioni(FILE *imps, stringa nomfile, impostazioni imp)
{
	int xoffset;
	int yoffset;
	int nrighe;
	int ncolonne;
	int ngiocatori;
	int i;
	char tempgiocatore;
	int minvincolo;
	int maxvincolo;

	xoffset = -leggereValoreXconzero(imp);
	yoffset = 3 - leggereValoreXconzero(imp);

	gotoxy(leggereValoreXconzero(imp) + xoffset, leggereValoreYconzero(imp) + yoffset);
	printf("Inserire il numero di righe: ");
	printf("\n");

	minvincolo = 0;
	maxvincolo = 8;
	nrighe = acquisizioneInteroConVincoli(minvincolo, maxvincolo);
	scritturaInteroSuFile(imps, nrighe);

	printf("\n");
	printf("Inserire il numero di colonne: ");
	printf("\n");

	maxvincolo = 15;
	ncolonne = acquisizioneInteroConVincoli(minvincolo, maxvincolo);
	scritturaInteroSuFile(imps, ncolonne);

	printf("\n");
	printf("Inserire il numero di giocatori: ");
	printf("\n");

	maxvincolo = 10;
	ngiocatori = acquisizioneInteroConVincoli(minvincolo,maxvincolo);
	scritturaInteroSuFile(imps, ngiocatori);

	i = 0;
	while(i < ngiocatori)
	{
		printf("\n");
		printf("Inserire giocatore: ");
		printf("\n");
		tempgiocatore = acquisizioneGiocatore();
		scritturaCarattereSuFile(imps, tempgiocatore);
		i = i + 1;
	}

	scritturaInteroSuFile(imps, leggereValoreXconzero(imp));
	scritturaInteroSuFile(imps, leggereValoreYconzero(imp));
}

int acquisizioneInteroConVincoli(int min, int max)
{
	int valore;
	char* str;
	str = (char*)malloc(2*sizeof(char));

	do{
	gets(str);
	valore = atoi(str);
	}while(valore  <= min || valore > max );
	return valore;
}

void scritturaInteroSuFile(FILE *imps, int num)
{

	fprintf(imps,"%d", num);
	fprintf(imps,"\n");
}

void creaDefaultSeManca(FILE *def, stringa nomdef)
{
	def = fopen(nomdef, "r");
	if(def == NULL)
	{
		creaFileDefault(def, nomdef);
		def = fopen(nomdef, "r");
	}
	fclose(def);
}

impostazioni gestisciImpostazioni(FILE *imps, stringa nomfile, stringa nomdef, char richiestai ,impostazioni imp)
{
	if(richiestai  == 's')
		{
			imps = fopen(nomfile, "w");
			cambioImpostazioni(imps, nomfile, imp);
			fclose(imps);
			imps = fopen(nomfile, "r");

		}
		else
		{
			if(richiestai == 'n')
			{
				imps = fopen(nomfile, "r");
				if(imps == NULL)
				{
					imps = fopen(nomdef, "r");
				}
			}
			else
			{
				imps = fopen(nomdef, "r");
			}
		}

		imp = inizializzaImpostazioni(imps, imp);
		fclose(imps);
		return imp;
}

char acquisizioneGiocatore()
{
	char giocatore;

	giocatore = getch();
	printf("%c", giocatore);
	printf("\n");

	return giocatore;
}

void scritturaCarattereSuFile(FILE *imps, char car)
{

	fprintf(imps,"%c", car);
	fprintf(imps,"\n");
}



impostazioni inizializzaImpostazioni(FILE *imps, impostazioni imp)
{
	int nrighe;
	int ncolonne;
	int ngiocatori;
	char tempgiocatore;
	int i;
	int xconzero;
	int yconzero;


	fscanf(imps, "%d", &nrighe);
	imp = scrivereValoreRighe(imp, nrighe);



	fscanf(imps, "%d", &ncolonne);
	imp = scrivereValoreColonne(imp, ncolonne);



	fscanf(imps, "%d", &ngiocatori);
	imp = scrivereValoreNgiocatori(imp, ngiocatori);


	allocareGiocatori(&imp);
	 i = 0;
	 while(i < leggereValoreNgiocatori(imp))
	 {
		 do{
			 tempgiocatore = fgetc(imps);
		 }while(tempgiocatore == '\n');
		 imp = scrivereValoreGiocatori(imp, i + 1, tempgiocatore);

		 i = i + 1;
	 }

	 fscanf(imps, "%d", &xconzero);
	 imp = scrivereValoreXconzero(imp, xconzero);

	 fscanf(imps, "%d", &yconzero);
	 imp = scrivereValoreYconzero(imp, yconzero);

	 return imp;

}

//Funzioni riguardanti la stampa del campo

void scrivereStringa(stringa str, int pos, char valore)
{
	*(str + pos) = valore;
}

void inizializzazioneStringaPrimaRiga(stringa str, int col)
{
	int i;
	char angolodes;
	char angolosin;
	char lineaorizz;
	char perpbasso;

	angolodes = 218;
	angolosin= 191;
	lineaorizz = 196;
	perpbasso = 194;

	scrivereStringa(str, 0 , angolodes);
	scrivereStringa(str, (col*2) , angolosin);
	i = 1;
	while(i < (col*2))
	{
		if(i %2 != 0)
		{
			scrivereStringa(str, i, lineaorizz);
		}
		else
		{
			scrivereStringa(str, i , perpbasso);
		}
		i = i + 1;
	}
	scrivereStringa(str, (col*2)+1 , '\0');
}

void inizializzazioneStringaUltimaRiga(stringa str, int col)
{
	int i;
	char angolodes;
	char angolosin;
	char lineaorizz;
	char perpalto;

	angolodes = 192;
	angolosin = 217;
	lineaorizz = 196;
	perpalto = 193;

	scrivereStringa(str, 0 , angolodes);
	scrivereStringa(str, (col*2) , angolosin);
	i = 1;
	while(i < (col*2))
	{
		if(i %2 != 0)
		{
			scrivereStringa(str, i , lineaorizz);
		}
		else
		{
			scrivereStringa(str, i , perpalto);
		}
		i = i+1;
	}

	scrivereStringa(str, (col*2)+1 , '\0');
}

void inizializzazioneStringaRigaVerticale(stringa str, int col)
{
	int i;
	char lineavert;
	char spazio;

	lineavert = 179;
	spazio = ' ';

	i = 0;
	while(i <= (col*2))
	{
		if(i %2 == 0)
		{
			scrivereStringa(str, i , lineavert);
		}
		else
		{
			scrivereStringa(str, i , spazio);
		}
		i = i+1;
	}
	scrivereStringa(str, (col*2)+1 , '\0');
}

void inizializzazioneStringaRigaInterstiziale(stringa str, int col)
{
	int i;
	char perpdes;
	char perpsin;
	char lineaorizz;
	char perp;

	perpdes = 195;
	perpsin = 180;
	lineaorizz = 196;
	perp = 197;

	scrivereStringa(str, 0 , perpdes);
	scrivereStringa(str, (col*2) , perpsin);
	i = 1;
	while(i < (col*2))
	{
		if(i %2 != 0)
		{
			scrivereStringa(str, i , lineaorizz);
		}
		else
		{
			scrivereStringa(str, i , perp);
		}
		i = i+1;
	}
	scrivereStringa(str, (col*2)+1 , '\0');
}

void stampaCampo(int rig, int col, int xconzero, int yconzero)
{
	stringa pstr;
	stringa ustr;
	stringa vstr;
	stringa istr;
	int i;
	int yoffset;
	pstr = (stringa )malloc(((col * 2) + 3)*sizeof(char));
	ustr = (stringa )malloc(((col * 2) + 3)*sizeof(char));
	vstr = (stringa )malloc(((col * 2) + 3)*sizeof(char));
	istr = (stringa )malloc(((col * 2) + 3)*sizeof(char));

	inizializzazioneStringaPrimaRiga( pstr,  col);
	inizializzazioneStringaUltimaRiga( ustr,  col);
	inizializzazioneStringaRigaVerticale( vstr,  col);
	inizializzazioneStringaRigaInterstiziale( istr,  col);




	gotoxy(xconzero, yconzero);
	printf("%s", pstr);
	printf("\n");

	yoffset = 1;
	i = 2;
	while(i <= rig*2 )
	{
		gotoxy(xconzero, yconzero + yoffset);
		if(i % 2 == 0)
		{
			printf("%s", vstr);
			printf("\n");
		}
		else
		{
			printf("%s", istr);
			printf("\n");
		}
		yoffset = yoffset + 1;
		i = i + 1;
	}

	gotoxy(xconzero, yconzero + yoffset);
	printf("%s", ustr);
	printf("\n");
	yoffset = yoffset +1;
	gotoxy(xconzero, yconzero + yoffset);
	stampaRiferimentoColonne( col,  xconzero,  yconzero, yoffset);

	free(pstr);
	free(ustr);
	free(vstr);
	free(istr);
}

void stampaRiferimentoColonne(int col, int xconzero, int yconzero, int yoffset)
{
	int cifremensig;
	int xoffset;
	int riferimento;
	int i;


	i= 1;
	xoffset = i;
	cifremensig = 0;
	printf(" ");
	while(i <= col)
	{

		gotoxy(xconzero + xoffset, yconzero + yoffset);
		if(i/10>0)
		{
			riferimento = i/10;
			printf("%d", riferimento);
			cifremensig = cifremensig +1;

		}
		else
		{
			riferimento = i;
			printf("%d",riferimento);
		}
		xoffset = i + i + 1;
		i = i + 1;
	}

	xoffset = xoffset - (2*cifremensig) ;
	yoffset = yoffset + 1;

	i = 0;
	while(i < cifremensig)
	{
		gotoxy(xconzero + xoffset, yconzero + yoffset);
		riferimento = i;
		printf("%d", riferimento);
		xoffset = xoffset + 2;
		i = i + 1;
	}

}

void stamparePedina(campo cmp, int rmax, int c, int xconzero, int yconzero)//funzione di scrittura di una pedina nel campo
{

	char pedina;
	int r;
	int i;
	int xoffset;
	int yoffset;
	i = 0;
	while((i < rmax)&&(leggereValoreCampo(cmp, i, c) == ' '))
	{
		i = i + 1;
	}
	r = i;



	pedina = leggereValoreCampo(cmp,r,c);

	yoffset = r + (r + 1);
	xoffset = c + (c + 1);

	gotoxy(xconzero + xoffset, yconzero + yoffset);
	printf("%c", pedina);

}



//Funzioni sul campo da gioco

void allocazioneMemoriaCampo(campo* cmp, int rig, int col)
{
	int i;

	*cmp = (char**)malloc((rig + 1) * sizeof(char*));

	i = 0;
	while( i < rig)
	{
		*(*cmp + i) = (char*)malloc((col + 1) * sizeof(char));
		i = i + 1;
	}
}

void scrivereValoreCampo(campo cmp, int r, int c, char valore) //funzione di accesso ai dati di cmp
{
	*(*(cmp + r) + c) = valore;
}

int leggereValoreCampo(campo cmp, int r, int c) //funzione di accesso ai dati di cmp
{
	int valore;
	valore = *(*(cmp + r) + c);
	return valore;
}

void inizializzazioneCampo(campo cmp, int rmax, int cmax)//inizializza il campo con valori pari alla casella vuota (codice ascii = 32)
{
	int i;
	int j;
	char spazio;
	spazio = 32;
	i = 0;
	while(i < rmax)
	{
		j = 0;
		while(j < cmax)
		{
			scrivereValoreCampo(cmp, i, j, spazio);
			j = j + 1;
		}
		i = i + 1;
	}
}

void scriverePedinaCampo(campo cmp,int rmax ,int c, char pedina) //funzione di inserimento di una pedina in cmp
{
	int i;
	char spazio;
	spazio = ' ';
	i = 0;
	while((i < rmax)&&(leggereValoreCampo(cmp, i, c) == spazio))
	{
		i = i + 1;
	}

	scrivereValoreCampo(cmp, i-1, c, pedina);

}




//eventi del turno del giocatore1

int richiestaPosizione(campo cmp, impostazioni imp, char giocatore)
{
	int col;
	int xconzero;
	int yconzero;
	int posizione;
	int xoffset;
	int yoffset;
	char spazio;
	char *str;
	int noninseribile;

	col = leggereValoreColonne(imp);
	xconzero = leggereValoreXconzero(imp);
	yconzero = leggereValoreYconzero(imp);
	str = (char*)malloc(2*sizeof(char));


	do
	{

		xoffset=-20;
		yoffset=-3;
		gotoxy(xconzero + xoffset, yconzero + yoffset);
		printf("%c ", giocatore);
		printf(" e' il tuo turno, in che colonna vuoi inserire la pedina?");

		yoffset= yoffset + 1;
		gotoxy(xconzero + xoffset, yconzero + yoffset);
		gets(str);
		posizione = atoi(str);

		posizione = posizione - 1;

		spazio = 32;
		if(leggereValoreCampo(cmp, 0, posizione) == spazio)
		{
			noninseribile = 0;
		}
		else
		{
			noninseribile = 1;
		}



		yoffset = yoffset + 1;
		gotoxy(xconzero + xoffset, yconzero + yoffset);
		if((posizione >= 0) && (posizione < col && (noninseribile == 0) ))
		{
			printf("                               ");

		}
		else
		{
			printf("Posizione non valida, riprovare");

		}

	}while((posizione<0) ||( posizione>=col)||(noninseribile == 1));

	free(str);
	return posizione;


}

void svolgimentoPartita(impostazioni imp, campo cmp)
{
	int i;
	do{
		i = 1;
		while(i <= leggereValoreNgiocatori(imp))
		{
			eseguiTurno( imp,  cmp,  i);
			i= i + 1;
		}
	}while((controllaCampoPerGiocatore(cmp, imp) == 0) && (controlloPareggio(cmp,  imp)));
}

void eseguiTurno(impostazioni imp, campo cmp, int ngiocatore)
{
	int temppos;
	temppos = richiestaPosizione(cmp, imp, leggereValoreGiocatori(imp, ngiocatore));
	scriverePedinaCampo(cmp, leggereValoreRighe(imp), temppos, leggereValoreGiocatori(imp,ngiocatore));
	stamparePedina(cmp, leggereValoreRighe(imp), temppos, leggereValoreXconzero(imp), leggereValoreYconzero(imp));
}

//Interfaccia di gioco

void stampaTitolo()
{
	gotoxy(0,0);
	printf("F O R Z A 4");
}

//Svolgimento del gioco

int controlloCampo(campo cmp, int rig, int col, char giocatore)
{
	int esito; //la partita è in corso? 1 per si, 0 per vittoria giocatore
	int i;
	int j;

	esito = 1;
	i = 0;
	while(i<rig)
	{
		j=0;
		while((j+3)<col)
		{
			if((leggereValoreCampo(cmp, i, j) == giocatore)&&(leggereValoreCampo(cmp, i, j +1 ) == giocatore)&&(leggereValoreCampo(cmp, i, j + 2 ) == giocatore)&&(leggereValoreCampo(cmp, i, j + 3 ) == giocatore))
			{
				esito = 0;
			}
			j = j + 1;
		}
		i = i + 1;
	}

	i = 0;
	while((i+3)<rig)
	{
		j=0;
		while(j<col)
		{
			if((leggereValoreCampo(cmp, i, j) == giocatore)&&(leggereValoreCampo(cmp, i+1, j) == giocatore)&&(leggereValoreCampo(cmp, i+2, j) == giocatore)&&(leggereValoreCampo(cmp, i+3, j) == giocatore))
			{
				esito = 0;
			}
			j = j + 1;
		}
		i = i + 1;
	}
	i = 0;
	while((i+3)<rig)
	{
		j=0;
		while((j+3)<col)
		{
			if((leggereValoreCampo(cmp, i, j) == giocatore)&&(leggereValoreCampo(cmp, i+1, j+1) == giocatore)&&(leggereValoreCampo(cmp, i+2, j+2) == giocatore)&&(leggereValoreCampo(cmp, i+3, j+3) == giocatore))
			{
				esito = 0;
			}
			j = j + 1;
		}
		i = i + 1;
	}
	i = 0;
	while((i+3)<rig)
	{
		j=0;
		while(j<col)
		{
			if((j-3)>=0)
			{
				if((leggereValoreCampo(cmp, i, j) == giocatore)&&(leggereValoreCampo(cmp, i+1, j-1) == giocatore)&&(leggereValoreCampo(cmp, i+2, j-2) == giocatore)&&(leggereValoreCampo(cmp, i+3, j-3) == giocatore))
				{
					esito = 0;
				}
			}
			j = j + 1;
		}
		i = i + 1;
	}
	return esito;
}

int controlloPareggio(campo cmp, impostazioni imp)
{
	int esito; //se si verifica un pareggio esito assume il valore 0
	int i;
	int j;
	esito = 0;
	i = 0;
	while(i < leggereValoreRighe(imp))
	{
		j=0;
		while(j<leggereValoreColonne(imp))
		{
			if(leggereValoreCampo(cmp, i ,j) == ' ')
			{
				esito = 1;
			}
			j = j + 1;
		}
		i = i + 1;
	}
	return esito;
}

int controllaCampoPerGiocatore(campo cmp, impostazioni imp)
{
	int esito;
	int i;
	i = 1;
	esito = 0;
	while(i<= leggereValoreNgiocatori(imp)&&(esito == 0))
	{
		if( controlloCampo(cmp, leggereValoreRighe(imp), leggereValoreColonne(imp), leggereValoreGiocatori(imp, i)) == 0)
		{
			esito = i;
		}
		i = i + 1;
	}

	return esito;
}

void stampaMessaggioDiVittoria( campo cmp,impostazioni imp)
{
	char vinc;
	int ngiocatore;
	int xoffset;
	int yoffset;
	xoffset = -15;
	yoffset = 20;
	ngiocatore = controllaCampoPerGiocatore(cmp, imp);
	gotoxy(leggereValoreXconzero(imp) + xoffset, leggereValoreYconzero(imp) + yoffset);
	vinc = leggereValoreGiocatori(imp, ngiocatore);
	printf("%c ", vinc );
	printf(" e' il vincitore!");

}

void stampaMessaggioDiPareggio(impostazioni imp)
{
	int xoffset;
	int yoffset;
	xoffset = -15;
	yoffset = 20;
	gotoxy(leggereValoreXconzero(imp) + xoffset, leggereValoreYconzero(imp) + yoffset);
	printf("E' un pareggio!");
}

//Funzione gotoxy

void gotoxy(int x, int y)
{
    HANDLE h;
    COORD coord;

    h = GetStdHandle(STD_OUTPUT_HANDLE);
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(h, coord);
}
