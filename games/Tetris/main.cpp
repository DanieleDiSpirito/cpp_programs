#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "Resources.h"

#define MAX(x, y) ((x > y) ? x : y)
#define MIN(x, y) ((y > x) ? x : y)

#define szClassName TEXT("Tetris")
//definiamo il nome della classe in una "costante" (direttiva del preprocessore)
//per non sbagliare in seguito, tipo errori di battitura
#define UCHAR unsigned char
//Ultimi 3 bit
#define PSTYLE_VOID    0x0 //Punto vuoto
#define PSTYLE_RED     0x1 //Quadretto rosso
#define PSTYLE_YELLOW  0x2 //Giallo
#define PSTYLE_GREEN   0x3 //Verde
#define PSTYLE_CYAN    0x4 //Ciano, azzurro
#define PSTYLE_BLUE    0x5 //Blu
#define PSTYLE_VIOLET  0x6 //Viola, ma graficamente molto chiaro
#define PSTYLE_GRAY    0x7 //Grigio
//Quart'ultimo bit
#define PSTYLE_FALLING 0x8 //bin = 1000, il pezzo sta cadendo
#define PSTYLE_FIXED   0x0 //bin = 0000, il pezzo è fermo, di default è selezionata questa opzione
//se il numero è per esempio x x x x 1 0 0 1 0
//i primi 4 bit sono ignorati, il quinto è un 1, quindi il pezzo si muove, gli ultimi 3 010 = 2 quindi il pezzio è giallo
#define LASTTHREEBITS(num) (num & 0x7) //Restituisce gli ultimi 3 bit, servono per avere il colore
#define ISMOVING(num) ((num >> 3) & 0x1) //Restituisce il quart'ultimo bit, serve ad ottenere lo stato

#define HINIBBLE(x) (x >> 4)
#define LONIBBLE(x) (x & 0xF)

#define GameWidth  10 //Non modificate questi valori
#define GameHeight 18 //Sono rispetticamente larghezza e altezza del gioco.

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM); //procedura di gestione dei messaggi
int AddPiece(int); //Aggiunge un tetramino, che non è il cubetto ma l'insieme di quattro quadratini
//L'unico parametro che gli si passa rappresenta il tetramino. se la funziuone fallisce restituisce 0
void AddNextPiece(int); //Mostra all'utente il tetramino successivo
//L'unico parametro che gli si passa rappresenta il tetramino. la funzione non restituisce valore
#define TETROMINO_I 0 //4 blocchi su un unica riga,                                                      è identificato dal rosso
#define TETROMINO_O 1 //4 blocchi a formare un quadrato,                                                 è identificato dall'azzurro
#define TETROMINO_T 2 //4 blocchi che formano una T,                                                     è identificato dal grigio
#define TETROMINO_J 3 //4 blocchi che formano una L rovesciata,                                          è identificato dal giallo
#define TETROMINO_L 4 //4 blocchi che formano una L,                                                     è identificato dal viola
#define TETROMINO_S 5 //2 blocchi su una riga e altri 2 su quella sopra spostati di un blocco in avanti, è identificato dal verde
#define TETROMINO_Z 6 //4 blocchi che formano una S rovesciata,                                          è identificato dal blu

/* la griglia del tetris è un rettangolo 10 * 18
   creiamo un array che rappresenta linee e colonne */
UCHAR GameGrid[GameWidth][GameHeight], //Questo è un array multitimensionale statico
/* Una cosa importante da notare è che ciò che conta non è il pezzo (nel senso di tetramino),
   ma ogni quadretto che lo compone, quindi il tetramino a forma di L non è altro che 4 quadratini
   che se stanno lì o da un'altra parte fa lo stesso, perchè il dato non rappresenta tutto il pezzo ma solo le sue parti.
   in breve il computer non conosce il pezzo a froma di L, ma i 4 quadretti che la compongono                             */
/* Gamegrid[x][y] accede al quadratino che attualmente si trova alle coordinate x, y, restituisce un unsigned char.
   gli ultimi 3 bit rappresentano il colore, il quart'ultimo se è in movimento o no, i primi quattro sono vuoti           */
       NextPiece[4][4]; //Rappresentazione del pezzo successivo
#define GetBlock(x, y) (GameGrid[x][y])
#define GetNextPiece(x, y) (NextPiece[x][y])
int level, //contiene il numero del livello se il livello è negativo il gioco va oscuraro, ma non eliminato
    Lines, //le linee eliminate
    Score, TempScore, //Il punteggio, TempScore memorizza un punteggio temporaneo che può essere aggiunto alla fine
    NextPieceID, //L'identificatore del pezzo successivo
    Movies, //Il numero di mosse orizzontali, max = 3 per tick del timer
    dontactivate; //Se la finestra non va messa in pausa quando viene aperta un'altra finestra questa va impostata su 0

/* Rotazioni */
float RotX, RotY; /*il punto centrale dove avviene la rotazione, i valori interi indicano che la rotazione avviene nel centro della casella
                    i valori decimali indicano che la rotazione avviene nel punto di incontro di 4 caselle
                    NB la parte decimale di entrambe le variabili può essere solo .5 (ex 1.5; 3.5, ecc.) in caso contrario (2.8 per esempio)
                    il programma andrà in crash, c'è anche da dire che se una è decimale e l'altra no vi sarà il medesimo errore, quindi sono
                    considerate sbagliate per esempio le seguenti coppie   1.5; 3.0   4.0; 0.5;    5.5; 8.0
                    e corrette 1.5; 3.5     1.0; 5.0    7.5; 2.5
                    al fine di evitare i seguenti errori ho creato la seguente macro */
char Nrot; //HINIBBLE = Numero di ruotazioni che può avere un pezzo, p. es T ne ha 4, O non ne ha una, I ne ha 2, sono accettati solo i valori 1, 2 e 4
           //LONIBBLE = Numero di rotazioni effettuate, il contatore si azzera ad ogni giro completo
#define SetRot(x, y) (RotX = x, RotY = y, 0)
/*
  se conoscete l'operatore , sapete che quell'espressione assegna a RotX il valore x, a RotY il valore Y e restituisce 0
  questo perchè l'operatore , restituisce l'operando a destra es. (3, 5, 4) = 4 ovviamente dopo aver eseguito ogni espressione
  altrimenti (1)
*/

#define GetXRot RotX
#define GetYRot RotY
HINSTANCE hInst; //Istanza del processo
HWND MainWND; //Finestra principale

#define Xpos 30 //espressi in pixel
#define Ypos 12

void move_to_ground(); //Muove ogni pezzo in basso finchè non incontra un ostacolo (il suolo)
void move_down(int); //Muove ogni pezzo in basso di una sola casella, se il parametro è 0 non vi saranno punti extra
void move_left(); //Muove ogni pezzo a sinistra di una sola casella
void move_right(); //Muove ogni pezzo a destra di una sola casella
void rotate(); //Ruota i pezzi con centro di rotazione nel punto (RotX; RotY)
void paint(); //Ridisegna la finestra di gioco
void pause(); //Mette in pausa il gioco
void end_game(); //Termina il gioco
void new_game(); //Azzera tutto e comincia una nuova partita

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {
    HWND hwnd;               /* Puntatore alla finestra */
    MSG messages;            /* Qui vengono salvati i messaggi */
    WNDCLASSEX wincl;        /* La struttura che rappresenta la finestra */

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* Puntatore alla funzione chiamata per gestire i messaggi della finestra */
    wincl.style = CS_DBLCLKS;                 /* Riceve i doppi click, messaggi WM_LBUTTONDBCLICK e WM_RBUTTONDBCLICK */
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (hThisInstance, MAKEINTRESOURCE(IDI_MAIN_ICON));
    wincl.hIconSm = LoadIcon (hThisInstance, MAKEINTRESOURCE(IDI_MAIN_ICON));
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* Nessum Menu */
    wincl.cbClsExtra = 0;                      /* Nesun byte extra dopo l'allocazione della classe */
    wincl.cbWndExtra = 0;                      /* Nessun byte extra dopo l'allocazione della finestra */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
    /* Registriamo la finestra e se la procedura fallisce usciamo */
    if (!RegisterClassEx (&wincl)){
        MessageBox(NULL, "Errore durante la creazione della finestra", "ERRORE", MB_OK | MB_ICONERROR);
        return -1; //esce dalla funzione che essendo la Main vuol dire terminare il programma con stato -1
    }
    hInst = hThisInstance;
    /* La classe è ora registrata, creiamo la finestra */
    hwnd = CreateWindowEx (
           0,                   /* stili extra, WS_EX_... in questo caso non ci servono*/
           szClassName,         /* Nome della classe */
           "Sei una merda se giochi a sto gioco",            /* Caption, in pratica il testo in alto nella barra blu */
           WS_OVERLAPPED |      /* stile della finestra, WS_OVERLAPPED è lo stile standad per tutte le finestre */
           WS_CAPTION |
           WS_TILED |
           WS_SYSMENU,          /* finestra standard, ma non ridimensionabile, per una standard vera e propria usate WS_OVERAPPLEDWINDOW */
           150,                 /* posizione coord. X */
           100,                 /* posizione coord. Y */
           200,                 /* La larghezza della finestra */
           636,                 /* e la sua altezza in pixel */
           HWND_DESKTOP,        /* La finestra è una child-window del desktop */
           NULL,                /* Menù della finestra, in questo caso nessuno */
           hThisInstance,       /* istanza del programma */
           NULL                 /* nessun dato aggiuntivo */
           );
    MainWND = hwnd;
    /* Rendiamo la finestra visibile sullo schermo */
    ShowWindow (hwnd, nCmdShow);

    /* Facciamo partire il message loop. Andrà avanti finchè GetMessage() non restituirà 0 */
    while (GetMessage (&messages, NULL, 0, 0)) {
        TranslateMessage(&messages);
        DispatchMessage(&messages); //Il messaggio viene mandato alla procedura che lo gestirà (WindowProcedure)
    }

    return messages.wParam;
}
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    /*Questa è la funzione chiamata per gestire i messaggi ricevuti*/
    switch (message) //in base al messaggio agiremo di conseguenza, quindi prima controlliamo cosa abbiamo ricevuro
    {
        case WM_SHOWWINDOW: /* Messaggio inviato alla finestra al momento della sua appariazione a video, WM_CREATE quando viene creata */
        {
            new_game();
            break;
        }
        case WM_TIMER: /* Messaggio mandato ad ogni tick del timer */
        //Aggiorna la finestra di gioco
        {
            int x, y, temp, C = 0, delln = 0; //temp ha vari usi, serve quando una linea va eliminata o quando dobbiamo decidere se spostare in basso i tetramini
            RECT rect = {0,0,0,0};
            //La seconda cosa che facciamo è verificare la presenza di linee complete, questa operazione la svolgiamo all'inizio
            //Perchè se la facessimo alla fine avremmo già spostato verso il basso i pezzi completando una linea ed eliminandola
            //Senza permettere all'utente di vedere cosa è realmente accaduto
            DelLines:
            for (y = 0; y < GameHeight; y++){
                temp = 1;
                for(x = 0; x < GameWidth; x++)
                { //Per ogni elemento della linea
                    if ((LASTTHREEBITS(GameGrid[x][y])) == PSTYLE_VOID || ISMOVING(GameGrid[x][y])){ //Verifica che non ci sia un vuoto o un pezzo ancora in movimento
                        temp = 0; //e se ne trova uno vuoto la linea NON va eliminata
                        break; //e non ha senso andare avanti a cercare vuoti
                    }
                }
                if (temp)
                //Se temp è 0 vuol dire che sono stati trovati dei buchi, questo blocco viene eseguito se non è così
                { //pertanto si elimina la linea spostando in basso tutto ciò che sopra è fermo, perchè i pezzi che cadono verranno mossi dopo
                    int ln;
                    for(ln = y; ln /* ln != 0 */ ; ln--) {
                    	for(x = 0; x < GameWidth; x++){ //Per ogni elemento della linea

                            if ((ISMOVING(GameGrid[x][ln - 1]) == 0)){ //Verifica che il pezzzo sia fermo
                                GameGrid[x][ln] = GameGrid[x][ln - 1]; //ogni cubo viene spostato in basso coprendo la linea da eliminare
                                                                     //Che viene così eliminata
                            }
                        } //Fine for x
                    } //Fine for line
                    for(x = 0; x < GameWidth; x++){ //Per ogni elemento della linea
                            if ((ISMOVING(GameGrid[x][0]) == 0)){ //Verifica che il pezzzo sia fermo
                                GameGrid[x][0] = PSTYLE_VOID; //La prima riga viene svuotata ad esclusione dei pezzi che cadono
                            }
                        } //Fine for x
                    rect = {Xpos, Ypos, Xpos + 32 * GameWidth, Ypos + 32 * GameHeight};
                    Lines++;
                    delln++; //incrementiamo il contatore delle linee eliminate a questo turno
                    C = 1; //Almeno una linea è stata eliminata, quindi settiamo C a 1
                } //End if
                if (C){ //Se C è divesro da 0 almeno una linea è stata eliminata quindi
                    C = 0;
                    goto DelLines; //Ritorna indietro per verificare la presenza di altre linee complete
                }
            }
            /*  Calcoliamo il punteggio in base alle eliminazioni secondo la seguente tabella, con linee non intendo il
                valore assoluto ma quelle eliminate dopo il posizionamento del singolo pezzo
             livello    1 linea     2 linee     3 linee      4 linee
                1         40pt       100pt       300pt       1200pt
                2         80pt       200pt       600pt       2400pt
                3        120pt       300pt       900pt       3600pt
                4        160pt       400pt      1200pt       4800pt
                5        200pt       500pt      1500pt       6000pt
                ...       ...         ...         ...         ...
            */
            switch (delln){
                case 1:
                    Score += 40 * level;
                    break;
                case 2:
                    Score += 100 * level;
                    break;
                case 3:
                    Score += 300 * level;
                    break;
                case 4:
                    Score += 1200 * level;
            }
            if (level < 10 && level != (Lines / 10) + 1){
                KillTimer(MainWND, ID_GAME_TIMER);
                level++; //Il livello aumenta ogni 10 linee eliminate, il livello massimo è il decimo
                SetTimer(MainWND, ID_GAME_TIMER, 800 - 50 * level, NULL);
            }

            move_down(0);

            //SE NON CI SONO PEZZI DA SPOSTARE SI AGGIUNGONO TETRAMINI
            //Controlliamo che ci sia almeno un pezzo un movimento
            temp = 0;
            for (y = 0; y < GameHeight; y++){
                for (x = 0; x < GameWidth; x++){
                    if (ISMOVING(GameGrid[x][y])){
                        temp = 1;
                        goto EndOfCycles;
                    }
                }
            }
            EndOfCycles:

            if (!temp){ //Se tutti i pezzi sono fermi se ne aggiunge uno
                if (!(AddPiece(NextPieceID))){ //Il gioco termina quando non è più possibile aggiungere pezzi
                    dontactivate = 0; //Quando appare il messaggio non vogliamo togliere la visuale al giocatore,
                    // se non facessimo così messagebox attiverebbe una nuova finestra e automaticamente il computer oscurerà il gioco
                    KillTimer(hwnd, ID_GAME_TIMER); //Viene fermato il timer
                    MessageBox(hwnd, "GAME OVER", "Tetris", MB_OK | MB_ICONINFORMATION);
                    if (MessageBox(hwnd, "Vuoi cominciare una nuova partita?", "Tetris", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON1) == IDYES)
                        new_game();
                    else
                        PostQuitMessage(0); //Viene inviato alla finestra un messaggio di chiusura con stato 0
                    break;
                }
                AddNextPiece(rand());
                rect = {Xpos, Ypos, Xpos + 32 * GameWidth + 190, Ypos + 32 * GameHeight};
            }
            //Ridisegnamo la finestra
            InvalidateRect(hwnd, &rect, NULL);
        }
        case WM_KEYDOWN:{
            /*  Forse era più facile usare GetAsyncKeyState ad ogni tick del timer, ma in quel caso l'utente avrebbe dovuto
                tenere premuto un tasto per molto tempo, invece così basta cliccarlo una volta anche rilasciandolo subito */
            switch(LOWORD(wParam)){
                case VK_UP: //Nel caso in cui venga premuta la freccetta in alto
                    rotate(); //Viene ruotato l'oggetto
                    break;
                case VK_DOWN: //in basso
                    move_down(1);
                    break;
                case VK_LEFT: //a sinistra
                    move_left();
                    break;
                case VK_RIGHT: //a destra
                    move_right();
                    break;
                case VK_SPACE: //in basso fino a terra
                    move_to_ground();
                    KillTimer(hwnd, ID_GAME_TIMER);
                    SetTimer(hwnd,  ID_GAME_TIMER, 800 - 50 * level, NULL); //Ogni volta che si schiaccia lo spazio il timer riparte
                    SendMessage(hwnd, WM_TIMER, ID_GAME_TIMER, GetTickCount());
                    //Al momento della creazione del timer il messaggio WM_TIMER non viene mandato, quindi per non far aspettare l'utente
                    //lo mandiamo manualmente
                    break;
                case 'P': //se schiaccate il tasto p si va in pausa
                    pause();
                    break;
                case VK_ESCAPE: //Esc, si esce dal gioco
                    end_game();
                    break;
            }
            break;
        }
        case WM_PAINT:{
            paint(); //Ridisegnamo la finestra
            break;
        }
        case WM_ACTIVATE:{
            static int x = 0; //WA_ACTIVATE è lanciato anche all'avvio dell'applicazione, ma noi non vogliamo un avvio in pausa!
            if (( LOWORD(wParam) == WA_INACTIVE) && x && dontactivate){
                pause();
            }
            x = 1;
            break; }
        case WM_DESTROY:
            PostQuitMessage (0);       /* viene mandato WM_QUIT alla message queue */
            break;
        default:                      /* per i messaggi non gestiti */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
int AddPiece(int Type){
    Type = Type % 7;
    switch (Type){
    case TETROMINO_I:
        if (GetBlock(3, 0) | GetBlock(4, 0) | GetBlock(5, 0) | GetBlock(6, 0))
            return 0;
        GameGrid[3][0] =
        GameGrid[4][0] =
        GameGrid[5][0] =
        GameGrid[6][0] = PSTYLE_RED | PSTYLE_FALLING; //Assegnamento multiplo
        SetRot(4.5, 0.5); //Viene cambiato il centro di rotazione
        Nrot = 0x20;
        return 1;
    case TETROMINO_O:
        if (GetBlock(4, 0) | GetBlock(4, 1) | GetBlock(5, 0) | GetBlock(5, 1))
            return 0;
        GameGrid[4][0] =
        GameGrid[4][1] =
        GameGrid[5][0] =
        GameGrid[5][1] = PSTYLE_CYAN | PSTYLE_FALLING;
        SetRot(4.5, 0.5);
        Nrot = 0x00;
        return 1;
    case TETROMINO_T:
        if (GetBlock(3, 0) | GetBlock(4, 0) | GetBlock(4, 1) | GetBlock(5, 0))
            return 0;
        GameGrid[3][0] =
        GameGrid[4][0] =
        GameGrid[4][1] =
        GameGrid[5][0] = PSTYLE_GRAY | PSTYLE_FALLING;
        SetRot(4, 0);
        Nrot = 0x40;
        return 1;
    case TETROMINO_J:
        if (GetBlock(3, 0) | GetBlock(4, 0) | GetBlock(5, 0) | GetBlock(5, 1))
            return 0;
        GameGrid[3][0] =
        GameGrid[4][0] =
        GameGrid[5][0] =
        GameGrid[5][1] = PSTYLE_YELLOW | PSTYLE_FALLING;
        SetRot(4, 0);
        Nrot = 0x40;
        return 1;
    case TETROMINO_L:
        if (GetBlock(3, 0) | GetBlock(3, 1) | GetBlock(4, 0) | GetBlock(5, 0))
            return 0;
        GameGrid[3][0] =
        GameGrid[3][1] =
        GameGrid[4][0] =
        GameGrid[5][0] = PSTYLE_VIOLET | PSTYLE_FALLING;
        SetRot(4, 0);
        Nrot = 0x40;
        return 1;
    case TETROMINO_S:
        if (GetBlock(3, 1) | GetBlock(4, 1) | GetBlock(4, 0) | GetBlock(5, 0))
            return 0;
        GameGrid[3][1] =
        GameGrid[4][1] =
        GameGrid[4][0] =
        GameGrid[5][0] = PSTYLE_GREEN | PSTYLE_FALLING;
        SetRot(4.5, 0.5);
        Nrot = 0x20;
        return 1;
    case TETROMINO_Z:
        if (GetBlock(3, 0) | GetBlock(4, 0) | GetBlock(4, 1) | GetBlock(5, 1))
            return 0;
        GameGrid[3][0] =
        GameGrid[4][0] =
        GameGrid[4][1] =
        GameGrid[5][1] = PSTYLE_BLUE | PSTYLE_FALLING;
        SetRot(4.5, 0.5);
        Nrot = 0x20;
        return 1;
    }
    return 0;
}
void AddNextPiece(int Type){
    NextPieceID = Type %= 7;
    switch (Type){
    case TETROMINO_I:
        NextPiece[0][0] = PSTYLE_VOID;   NextPiece[1][0] = PSTYLE_VOID;   NextPiece[2][0] = PSTYLE_VOID;   NextPiece[3][0] = PSTYLE_VOID;
        NextPiece[0][1] = PSTYLE_RED;    NextPiece[1][1] = PSTYLE_RED;    NextPiece[2][1] = PSTYLE_RED;    NextPiece[3][1] = PSTYLE_RED;
        NextPiece[0][2] = PSTYLE_VOID;   NextPiece[1][2] = PSTYLE_VOID;   NextPiece[2][2] = PSTYLE_VOID;   NextPiece[3][2] = PSTYLE_VOID;
        NextPiece[0][3] = PSTYLE_VOID;   NextPiece[1][3] = PSTYLE_VOID;   NextPiece[2][3] = PSTYLE_VOID;   NextPiece[3][3] = PSTYLE_VOID;
        break;
    case TETROMINO_O:
        NextPiece[0][0] = PSTYLE_VOID;   NextPiece[1][0] = PSTYLE_VOID;   NextPiece[2][0] = PSTYLE_VOID;   NextPiece[3][0] = PSTYLE_VOID;
        NextPiece[0][1] = PSTYLE_VOID;   NextPiece[1][1] = PSTYLE_CYAN;   NextPiece[2][1] = PSTYLE_CYAN;   NextPiece[3][1] = PSTYLE_VOID;
        NextPiece[0][2] = PSTYLE_VOID;   NextPiece[1][2] = PSTYLE_CYAN;   NextPiece[2][2] = PSTYLE_CYAN;   NextPiece[3][2] = PSTYLE_VOID;
        NextPiece[0][3] = PSTYLE_VOID;   NextPiece[1][3] = PSTYLE_VOID;   NextPiece[2][3] = PSTYLE_VOID;   NextPiece[3][3] = PSTYLE_VOID;
        break;
    case TETROMINO_T:
        NextPiece[0][0] = PSTYLE_VOID;   NextPiece[1][0] = PSTYLE_VOID;   NextPiece[2][0] = PSTYLE_VOID;   NextPiece[3][0] = PSTYLE_VOID;
        NextPiece[0][1] = PSTYLE_GRAY;   NextPiece[1][1] = PSTYLE_GRAY;   NextPiece[2][1] = PSTYLE_GRAY;   NextPiece[3][1] = PSTYLE_VOID;
        NextPiece[0][2] = PSTYLE_VOID;   NextPiece[1][2] = PSTYLE_GRAY;   NextPiece[2][2] = PSTYLE_VOID;   NextPiece[3][2] = PSTYLE_VOID;
        NextPiece[0][3] = PSTYLE_VOID;   NextPiece[1][3] = PSTYLE_VOID;   NextPiece[2][3] = PSTYLE_VOID;   NextPiece[3][3] = PSTYLE_VOID;
        break;
    case TETROMINO_J:
        NextPiece[0][0] = PSTYLE_VOID;   NextPiece[1][0] = PSTYLE_VOID;   NextPiece[2][0] = PSTYLE_VOID;   NextPiece[3][0] = PSTYLE_VOID;
        NextPiece[0][1] = PSTYLE_YELLOW; NextPiece[1][1] = PSTYLE_YELLOW; NextPiece[2][1] = PSTYLE_YELLOW; NextPiece[3][1] = PSTYLE_VOID;
        NextPiece[0][2] = PSTYLE_VOID;   NextPiece[1][2] = PSTYLE_VOID;   NextPiece[2][2] = PSTYLE_YELLOW; NextPiece[3][2] = PSTYLE_VOID;
        NextPiece[0][3] = PSTYLE_VOID;   NextPiece[1][3] = PSTYLE_VOID;   NextPiece[2][3] = PSTYLE_VOID;   NextPiece[3][3] = PSTYLE_VOID;
        break;
    case TETROMINO_L:
        NextPiece[0][0] = PSTYLE_VOID;   NextPiece[1][0] = PSTYLE_VOID;   NextPiece[2][0] = PSTYLE_VOID;   NextPiece[3][0] = PSTYLE_VOID;
        NextPiece[0][1] = PSTYLE_VIOLET; NextPiece[1][1] = PSTYLE_VIOLET; NextPiece[2][1] = PSTYLE_VIOLET; NextPiece[3][1] = PSTYLE_VOID;
        NextPiece[0][2] = PSTYLE_VIOLET; NextPiece[1][2] = PSTYLE_VOID;   NextPiece[2][2] = PSTYLE_VOID;   NextPiece[3][2] = PSTYLE_VOID;
        NextPiece[0][3] = PSTYLE_VOID;   NextPiece[1][3] = PSTYLE_VOID;   NextPiece[2][3] = PSTYLE_VOID;   NextPiece[3][3] = PSTYLE_VOID;
        break;
    case TETROMINO_S:
        NextPiece[0][0] = PSTYLE_VOID;   NextPiece[1][0] = PSTYLE_VOID;   NextPiece[2][0] = PSTYLE_VOID;   NextPiece[3][0] = PSTYLE_VOID;
        NextPiece[0][1] = PSTYLE_VOID;   NextPiece[1][1] = PSTYLE_GREEN;  NextPiece[2][1] = PSTYLE_GREEN;  NextPiece[3][1] = PSTYLE_VOID;
        NextPiece[0][2] = PSTYLE_GREEN;  NextPiece[1][2] = PSTYLE_GREEN;  NextPiece[2][2] = PSTYLE_VOID;   NextPiece[3][2] = PSTYLE_VOID;
        NextPiece[0][3] = PSTYLE_VOID;   NextPiece[1][3] = PSTYLE_VOID;   NextPiece[2][3] = PSTYLE_VOID;   NextPiece[3][3] = PSTYLE_VOID;
        break;
    case TETROMINO_Z:
        NextPiece[0][0] = PSTYLE_VOID;   NextPiece[1][0] = PSTYLE_VOID;   NextPiece[2][0] = PSTYLE_VOID;   NextPiece[3][0] = PSTYLE_VOID;
        NextPiece[0][1] = PSTYLE_BLUE;   NextPiece[1][1] = PSTYLE_BLUE;   NextPiece[2][1] = PSTYLE_VOID;   NextPiece[3][1] = PSTYLE_VOID;
        NextPiece[0][2] = PSTYLE_VOID;   NextPiece[1][2] = PSTYLE_BLUE;   NextPiece[2][2] = PSTYLE_BLUE;   NextPiece[3][2] = PSTYLE_VOID;
        NextPiece[0][3] = PSTYLE_VOID;   NextPiece[1][3] = PSTYLE_VOID;   NextPiece[2][3] = PSTYLE_VOID;   NextPiece[3][3] = PSTYLE_VOID;
        break;
    }
}
void move_down(int scoreextra){
    int temp = 1, x, y;
    RECT rect = {0,0,0,0};
    for (y = GameHeight - 1; y >= 0; y--){  //Per ogni elemento nella colonna, il contatore funziona al contrario, si parte dal basso
        for(x = 0; x < GameWidth; x++){ //Quindi Per ogni elemento nella linea
            if ((ISMOVING(GameGrid[x][y]))){ //Verifica che il pezzo si stia muovendo
                if ((y + 1 >= GameHeight) //Se superiamo i limiti della griglia di gioco
                || (GameGrid[x][y + 1] != PSTYLE_VOID && (ISMOVING(GameGrid[x][y+1]) == 0))) //o se la casella è già occupata
                    temp = 0; //impostiamo temp a zero indicando quindi che la mossa non si può fare
                //Ricordo che se è vera la condizione prima dell'or la seconda non viene verificata, lo stesso vale per gli and, solo che la seconda non viene verificara quando la prima è falsa
            }
        }
    }
    if (temp){
        for (y = GameHeight - 2; y >= 0; y--){  //Per ogni elemento nella colonna, il contatore funziona al contrario, si parte dal basso
            for(x = 0; x < GameWidth; x++){ //Quindi Per ogni elemento nella linea
                if ((ISMOVING(GameGrid[x][y]))){ //Verifica che si stia muovendo, il quinto bit è 1 quando si muove, 0 quando è fermo
                    GameGrid[x][y + 1] = GameGrid[x][y]; //Copiamo il cubo nella cella sottostante
                    GameGrid[x][y] = PSTYLE_VOID; //e lo eliminiamo da quella precedente
                    if (rect.bottom | rect.left | rect.right | rect.top)
                    //Questo codice viene eseguito se almeno un lato è diverso da 0
                    {
                        rect = {MIN(rect.left, (x * 32 + Xpos)),
                                MIN(rect.top, (y * 32 + Ypos)),
                                MAX(rect.right, (x * 32 + Xpos + 32)),
                                MAX(rect.bottom, (y * 32 + Ypos + 64))};
                    } else {
                        rect = {Xpos + x * 32, Ypos + y * 32, Xpos + 32 + x * 32, Ypos + 64 + y * 32};

                    }
                }
            }
        }
        SetRot(GetXRot, GetYRot+1);
        Movies = 0;
        if (scoreextra)
            TempScore++;
    }else{
        for (y = GameHeight - 1; y >= 0; y--){  //Per ogni elemento nella colonna, il contatore funziona al contrario, si parte dal basso
            for(x = 0; x < GameWidth; x++){ //Quindi Per ogni elemento nella linea
                GameGrid[x][y] &= 0x7; //L'oggetto viene fermato
            }
        }
        Score+=TempScore;
        TempScore = 0;
    }
    InvalidateRect(MainWND, &rect, NULL);
}
void move_left(){

    if (Movies > 3)
        return;
    int temp = 1, x, y;
    RECT rect = {0,0,0,0};
    for (x = 0; x < GameWidth; x++){
        for (y = 0; y < GameHeight; y++){
            if ((ISMOVING(GameGrid[x][y]))) //Verifica che il cubo si stia muovendo
                if ((x <= 0) //Non si può spostare a sinistra un oggetto con coordinata x = 0
                || (GameGrid[x - 1][y] != PSTYLE_VOID && (ISMOVING(GameGrid[x - 1][y]) == 0)))
                    temp = 0;
        }
    }
    if (temp){ //Se gli elementi si possono muovere allora li sposta
        for (y = 0; y < GameHeight; y++){  //Per ogni elemento nella colonna, il contatore funziona al contrario, si parte dal basso
            for(x = 1; x < GameWidth; x++){ //Quindi Per ogni elemento nella linea
                if ((ISMOVING(GameGrid[x][y]))){ //Verifica che si stia muovendo, il quinto bit è 1 quando si muove, 0 quando è fermo
                    GameGrid[x - 1][y] = GameGrid[x][y]; //Copiamo il cubo nella cella adiacente a sinistra
                    GameGrid[x][y] = PSTYLE_VOID; //e lo eliminiamo da quella precedente
                    if (rect.bottom | rect.left | rect.right | rect.top)
                    //Questo codice viene eseguito se almeno un lato è diverso da 0
                    {
                        rect = {MIN(rect.left, (x * 32 + Xpos - 64)),
                                MIN(rect.top, (y * 32 + Ypos)),
                                MAX(rect.right, (x * 32 + Xpos + 32)),
                                MAX(rect.bottom, (y * 32 + Ypos + 32))};
                    } else {
                        rect = {Xpos + x * 32, Ypos + y * 32, Xpos + 32 + x * 32, Ypos + 64 + y * 32};
                    }
                }
            }
        }
        SetRot(GetXRot-1, GetYRot);
        Movies++;
    }
    InvalidateRect(MainWND, &rect, NULL);
}
void move_right(){
    if (Movies > 3)
        return;
    int temp = 1, x, y;
    RECT rect = {0,0,0,0};
    for (x = GameWidth - 1; x >= 0; x--){
        for (y = 0; y < GameHeight; y++){
            if ((ISMOVING(GameGrid[x][y]))) //Verifica che il cubo si stia muovendo
                if ((x + 1 >= GameWidth) //Non si può spostare a sinistra un oggetto con coordinata x = 0
                || (GameGrid[x + 1][y] != PSTYLE_VOID && (ISMOVING(GameGrid[x + 1][y]) == 0)))
                    temp = 0;
        }
    }
    if (temp){ //Se gli elementi si possono muovere allora li sposta
        for (y = 0; y < GameHeight; y++){  //Per ogni elemento nella colonna, il contatore funziona al contrario, si parte dal basso
            for(x = GameWidth - 2; x >= 0; x--){ //Quindi Per ogni elemento nella linea
                if ((ISMOVING(GameGrid[x][y]))){ //Verifica che si stia muovendo, il quinto bit è 1 quando si muove, 0 quando è fermo
                    GameGrid[x + 1][y] = GameGrid[x][y]; //Copiamo il cubo nella cella adiacente a destra
                    GameGrid[x][y] = PSTYLE_VOID; //e lo eliminiamo da quella precedente
                    if (rect.bottom | rect.left | rect.right | rect.top)
                    //Questo codice viene eseguito se almeno un lato è diverso da 0
                    {
                        rect = {MIN(rect.left, (x * 32 + Xpos)),
                                MIN(rect.top, (y * 32 + Ypos)),
                                MAX(rect.right, (x * 32 + Xpos + 98)),
                                MAX(rect.bottom, (y * 32 + Ypos + 32))};
                    } else {
                        rect = {Xpos + x * 32, Ypos + y * 32, Xpos + 32 + x * 32, Ypos + 64 + y * 32};
                    }
                }
            }
        }
        SetRot(GetXRot + 1 , GetYRot);
        Movies++;
    }
    InvalidateRect(MainWND, &rect, NULL);
}
void move_to_ground(){
    int temp, x, y;
    RECT rect = {0,0,0,0};
    while (1){
        temp = 1;
        for (y = GameHeight - 1; y >= 0; y--){  //Per ogni elemento nella colonna, il contatore funziona al contrario, si parte dal basso
            for(x = 0; x < GameWidth; x++){ //Quindi Per ogni elemento nella linea
                if ((ISMOVING(GameGrid[x][y]))){ //Verifica che si stia muovendo, il quinto bit è 1 quando si muove, 0 quando è fermo
                    if (y + 1 >= GameHeight)
                        temp = 0;
                    else if (GameGrid[x][y + 1] != PSTYLE_VOID && (ISMOVING(GameGrid[x][y+1]) == 0))
                        temp = 0;
                }
            }
        }
        if (temp){
            for (y = GameHeight - 2; y >= 0; y--){  //Per ogni elemento nella colonna, il contatore funziona al contrario, si parte dal basso
                for(x = 0; x < GameWidth; x++){ //Quindi Per ogni elemento nella linea
                    if ((ISMOVING(GameGrid[x][y]))){ //Verifica che si stia muovendo, il quinto bit è 1 quando si muove, 0 quando è fermo
                        GameGrid[x][y + 1] = GameGrid[x][y]; //Copiamo il cubo nella cella sottostante
                        GameGrid[x][y] = PSTYLE_VOID; //e lo eliminiamo da quella precedente
                        if (rect.bottom | rect.left | rect.right | rect.top)
                        //Questo codice viene eseguito se almeno un lato è diverso da 0
                        {
                            rect = {MIN(rect.left, (x * 32 + Xpos)),
                                    MIN(rect.top, (y * 32 + Ypos)),
                                    MAX(rect.right, (x * 32 + Xpos + 32)),
                                    MAX(rect.bottom, (y * 32 + Ypos + 64))};
                        } else {
                            rect = {Xpos + x * 32, Ypos + y * 32, Xpos + 32 + x * 32, Ypos + 64 + y * 32};

                        }
                    }
                }
            }
            TempScore+=2; //Viene aumentato il punteggio temporaneo;
        }else{
            for (y = GameHeight - 1; y >= 0; y--){  //Per ogni elemento nella colonna, il contatore funziona al contrario, si parte dal basso
                for(x = 0; x < GameWidth; x++){ //Quindi Per ogni elemento nella linea
                    GameGrid[x][y] &= 0x7;
                }
            }
            Score+=TempScore; //Si aggiunge il punteggio ottenuto ai punti totali
            TempScore = 0;
            break;
        }
    }
    InvalidateRect(MainWND, NULL, NULL);
    SetRot(0,0);
}
void rotate(){
    if (HINIBBLE(Nrot) == 1)
        return; //Il pezzo non si può ruotare (o se lo si facesse non avrevebbe effetto)
    else if(HINIBBLE(Nrot) == 2 && LONIBBLE(Nrot) == 1){ //Se abbiamo un pezzo che può ruotare solo 2 volte allora alla seconda torniamo indietro
        //vengono effettuate le rotazioni di 90° in senso antiorario
        //data la griglia di gioco
        //
        //  ##################
        //  #        |       #
        //  #        | D     #
        //  #     A  |       #
        //  #        |       #
        //  #--------+-------# --> Ypos = 4
        //  #        |       #
        //  #        |  C    #
        //  #      B |       #
        //  #        |       #
        //  #        |       #
        //  ##################
        //           |
        //           '-->Xpos = 8
        // le nuove coordinate di ogni punto si troveranno così:
        // A = (5; 2)
        // B = (6; 7) = (8 - 4 + A.y; 8 + 4 - A.x) = (Xpos - Ypos + y; Xpos + Ypos - x)
        // C = (11; 6) = (8 - 4 + B.y; 8 + 4 - B.x)
        // D = (10; 1) = (8 - 4 + C.y; 8 + 4 - C.x)
        int temp = 1, x, y;
        UCHAR TempGrid[GameWidth][GameHeight]; //Griglia temporanea
        for (x = 0; x < GameWidth; x++){ //Controlliamo che si possa effettuare la rotazione
            for (y = 0; y < GameHeight; y++){
                if ((ISMOVING(GameGrid[x][y])))
                    if (((int)(GetXRot - GetYRot + y) < 0 || (int)(GetXRot - GetYRot + y) >= GameWidth ||
                        (int)(GetXRot + GetYRot - x) < 0 || (int)(GetXRot + GetYRot - x) >= GameHeight) //Non si può spostare a sinistra un oggetto con coordinata x = 0
                    || (GameGrid[(int)(GetXRot - GetYRot + y)][(int)(GetXRot + GetYRot - x)] != PSTYLE_VOID && (ISMOVING(GameGrid[(int)(GetXRot - GetYRot + y)][(int)(GetXRot + GetYRot - x)]) == 0)))
                        temp = 0;
            }
        }
        if (temp){ //se i blocchetti si possono muovere
            //li copiamo nell'array temporaneo solo se non si muovono
            //Avremo quindi la mappa dei pezzi "statici"
            for (y = 0; y < GameHeight; y++){
                    for(x = 0; x < GameWidth; x++){
                        if (ISMOVING(GameGrid[x][y])){
                            TempGrid[x][y] = GameGrid[x][y];
                            GameGrid[x][y] = PSTYLE_VOID;
                        }
                }
            }
            for (y = 0; y < GameHeight; y++){  //Per ogni elemento nella colonna, il contatore funziona al contrario, si parte dal basso
                for(x = 0; x < GameWidth; x++){ //Quindi Per ogni elemento nella linea
                    if ((ISMOVING(TempGrid[x][y]))){ //Verifica che si stia muovendo, il quinto bit è 1 quando si muove, 0 quando è fermo
                        GameGrid[(int)(GetXRot - GetYRot + y)][(int)(GetXRot + GetYRot - x)] = TempGrid[x][y]; //Copiamo il cubo nella nuova cella temporanea
                    }
                }
            }
        }
        Nrot = 0x20; //Azzeriamo le rotazioni
    } else { //In tutti gli altri casi la rotazione è in senso orario
        //vengono effettuate le rotazioni di 90° in senso orario
        //data la griglia di gioco
        //
        //  ##################
        //  #        |       #
        //  #        | B     #
        //  #     A  |       #
        //  #        |       #
        //  #--------+-------# --> Ypos = 4
        //  #        |       #
        //  #        |  C    #
        //  #      D |       #
        //  #        |       #
        //  #        |       #
        //  ##################
        //           |
        //           '-->Xpos = 8
        // le nuove coordinate di ogni punto si troveranno così:
        // A = (5; 2)
        // B = (10; 1)  = (8 + 4 - 2; 4 - 8 + 5) ovvero (8 + 4 - A.y; 4 - 8 + A.x) -> (Xpos + Ypos - y; Xpos - Ypos + x)
        // C = (11; 6) = (8 + 4 - 1; 4 - 8 + 10)
        // D = (6; 7) = (8 + 4 - 6; 4 - 8 + 11)
        int temp = 1, x, y;
        UCHAR TempGrid[GameWidth][GameHeight];
        for (x = 0; x < GameWidth; x++){
            for (y = 0; y < GameHeight; y++){

                if ((ISMOVING(GameGrid[x][y]))) //Verifica che il cubo si stia muovendo
                    if (((int)(GetYRot + GetXRot - y) < 0 || (int)(GetYRot + GetXRot - y) >= GameWidth ||
                        (int)(GetYRot - GetXRot + x) < 0 || (int)(GetYRot - GetXRot + x) >= GameHeight) //Non si può spostare a sinistra un oggetto con coordinata x = 0
                    || (GameGrid[(int)(GetYRot + GetXRot - y)][(int)(GetYRot - GetXRot + x)] != PSTYLE_VOID && (ISMOVING(GameGrid[(int)(GetYRot + GetXRot - y)][(int)(GetYRot - GetXRot + x)]) == 0)))
                        temp = 0;
            }
        }
        if (temp){ //se i blocchetti si possono muovere
            //li copiamo nell'array temporaneo solo se non si muovono
            //Avremo quindi la mappa dei pezzi "statici"
            for (y = 0; y < GameHeight; y++){
                    for(x = 0; x < GameWidth; x++){
                        if (ISMOVING(GameGrid[x][y])){
                            TempGrid[x][y] = GameGrid[x][y];
                            GameGrid[x][y] = PSTYLE_VOID;
                        }
                }
            }
            for (y = 0; y < GameHeight; y++){  //Per ogni elemento nella colonna, il contatore funziona al contrario, si parte dal basso
                for(x = 0; x < GameWidth; x++){ //Quindi Per ogni elemento nella linea
                    if ((ISMOVING(TempGrid[x][y]))){ //Verifica che si stia muovendo, il quinto bit è 1 quando si muove, 0 quando è fermo
                        GameGrid[(int)(GetYRot + GetXRot - y)][(int)(GetYRot - GetXRot + x)] = TempGrid[x][y]; //Copiamo il cubo nella nuova cella temporanea
                    }
                }
            }
            if (HINIBBLE(Nrot) == 2)
                Nrot = 0x21;
        }
    }
    InvalidateRect(MainWND, NULL, NULL);
}
void pause(){
    if (level > 0){
        KillTimer(MainWND, ID_GAME_TIMER);
    }else
        SetTimer(MainWND, ID_GAME_TIMER, 800 - 50 * (-level), NULL);
    level = -level;
    InvalidateRect(MainWND, NULL, NULL); //Viene ridisegnata l'intera finestra
}
void end_game(){
    if (level > 0){
        KillTimer(MainWND, ID_GAME_TIMER);
        level = -level;
        InvalidateRect(MainWND, NULL, NULL); //Viene ridisegnata tutta la finestra
        if (MessageBox(MainWND, "Sei sicuro di voler uscire?", "Tetris", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
        //Viene chiesta conferma dell'azione che si sta per compiere e se l'utente conferma allora il programma viene terminato
        {
            PostQuitMessage(0);
        }
        else //Altrimenti si ritorna alla finestra di gioco
        {
            level = -level;
            InvalidateRect(MainWND, NULL, NULL); //Viene ridisegnata tutta la finestra
            SetTimer(MainWND, ID_GAME_TIMER, 800 - 50 * (-level), NULL);
        }
    }else
        SetTimer(MainWND, ID_GAME_TIMER, 800 - 50 * (-level), NULL);
}
void new_game(){
    int Width, Height;
    for (Width = 0; Width < GameWidth; Width++)
        for (Height = 0; Height < GameHeight; Height++)
            GameGrid[Width][Height] = PSTYLE_VOID; //Ogni elemento dell'array è inizializzato come elemento vuoto
    level = 1; //Si parte dal livello 1
    Lines = 0; //Si azzerano anche le linee
    Score = 0; //Ovviamente si parte da 0 punti
    srand(time(NULL));
    NextPieceID = rand();
    TempScore = 0;
    dontactivate = 1;
    InvalidateRect(MainWND, NULL, NULL);
    SetTimer(MainWND, //Finestra alla quale mandare il meaasggio a ogni tick
             ID_GAME_TIMER, //Id del timer, per riconoscerlo
             800 - 50 * level, //Intervallo in millisecondi, se il livello è 1 800 - 50 = 750
                               //Via via che aumenta il livello il timer diventa più veloce, i livelli sono 10
             NULL);
    SendMessage(MainWND, WM_TIMER, ID_GAME_TIMER, GetTickCount());
}
void paint(){
    HDC Hdc, //Handle per il Device Context
    CompHdc; //Compatible HDC, un Device Context compatibile con Hdc
    PAINTSTRUCT ps;
    HPEN hPen = CreatePen(PS_SOLID, 7, RGB(120, 120, 120));
    HBRUSH hBr = CreateSolidBrush(RGB(0,0,0));
    HFONT TextFont;
    RECT TextRect;
    char TxScore[16], TxLevel[12], TxLines[12];
    int x, y, //coordinate X e Y del punto che stiamo disegnando
        TxScoreLen, TxLevelLen, TxLinesLen;
    HBITMAP BlockRed    = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BLOCK_RED   )),
            BlockYellow = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BLOCK_YELLOW)),
            BlockGreen  = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BLOCK_GREEN )),
            BlockCyan   = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BLOCK_CYAN  )),
            BlockBlue   = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BLOCK_BLUE  )),
            BlockViolet = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BLOCK_VIOLET)),
            BlockGray   = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BLOCK_GRAY  ));
    Hdc = BeginPaint(MainWND, &ps);
    SelectObject(Hdc, hPen);
    SelectObject(Hdc, hBr);
    Rectangle(Hdc,
              Xpos - 5,
              Ypos - 5,
              Xpos + 32 * GameWidth + 5,
              Ypos + 32 * GameHeight + 5   ); //Finrestra di gioco
    Rectangle(Hdc,
              Xpos + 32 * GameWidth + 20,
              Ypos + 15,
              Xpos + 32 * GameWidth + 190,
              Ypos + 143   ); //Prossimo pezzo
    CompHdc = CreateCompatibleDC(Hdc); //viene creato un device context compatibile per potervi inserire l'immagine
    if (level <= 0) {
    //Quando il livello è minore di 0 il gioco viene oscurato
        TextRect = {Xpos + GameWidth * 16 - 200, Ypos + GameHeight * 16 - 50, Xpos + GameWidth * 16 + 200, Ypos + GameHeight * 16 + 50 };
        TextFont = CreateFont(100, //Altezza in logical unit
                              0, //Larghezza caratteri in logic unit, se è zero il computer fa una media
                              0, //Rotazione testo in decimi di grado (10 = 1°)
                              0, //Rotazione dei singoli caratteri in decimi di grado
                              FW_BLACK, //Grassetto, normale, magretto :) (FW_THIN) ecc. in pratica lo spessore, FW_BLACK è il massimo
                              FALSE, //Corsivo, se è TRUE il testo appare in corsivo
                              FALSE, //Sottolineatura, se true il testo apparirà sottolineato
                              FALSE, //Barrato, in pratica con una linea sopra, ma solo se questo parametro è TRUE
                              ANSI_CHARSET, //Charset
                              OUT_DEFAULT_PRECIS, //Precisione dell'output
                              CLIP_DEFAULT_PRECIS, //Comportamento con i caratteri tagliati per manzanza di spazio
                              PROOF_QUALITY, //La qualità dell'output
                              DEFAULT_PITCH | FF_MODERN, //famiglia dell carattere, FF_MODERN indica quei caratteri dove non varia lo spessore del tratto
                              TEXT("Calibri") //E finalmente il nome del carattere!
                             );
        SelectObject(Hdc, TextFont);
        SetBkMode(Hdc, TRANSPARENT);
        SetTextColor(Hdc, 0x004FFF);
        DrawText(Hdc, "PAUSA", 5, &TextRect, DT_CENTER);
    } else { //Altrimenti se è tutto normale
        for (x = 0; x < GameWidth; x++){ //Disegnamo la principale finestra di gioco
            for(y = 0; y < GameHeight; y++){
                switch(LASTTHREEBITS(GameGrid[x][y])){
                    case PSTYLE_RED:
                        SelectObject(CompHdc, BlockRed);
                        BitBlt(Hdc, x*32 + Xpos, y*32 + Ypos, 32, 32, CompHdc, 0, 0, SRCCOPY);
                        break;
                    case PSTYLE_YELLOW:
                        SelectObject(CompHdc, BlockYellow);
                        BitBlt(Hdc, x*32 + Xpos, y*32 + Ypos, 32, 32, CompHdc, 0, 0, SRCCOPY);
                        break;
                    case PSTYLE_GREEN:
                        SelectObject(CompHdc, BlockGreen);
                        BitBlt(Hdc, x*32 + Xpos, y*32 + Ypos, 32, 32, CompHdc, 0, 0, SRCCOPY);
                        break;
                    case PSTYLE_CYAN:
                        SelectObject(CompHdc, BlockCyan);
                        BitBlt(Hdc, x*32 + Xpos, y*32 + Ypos, 32, 32, CompHdc, 0, 0, SRCCOPY);
                        break;
                    case PSTYLE_BLUE:
                        SelectObject(CompHdc, BlockBlue);
                        BitBlt(Hdc, x*32 + Xpos, y*32 + Ypos, 32, 32, CompHdc, 0, 0, SRCCOPY);
                        break;
                    case PSTYLE_VIOLET:
                        SelectObject(CompHdc, BlockViolet);
                        BitBlt(Hdc, x*32 + Xpos, y*32 + Ypos, 32, 32, CompHdc, 0, 0, SRCCOPY);
                        break;
                    case PSTYLE_GRAY:
                        SelectObject(CompHdc, BlockGray);
                        BitBlt(Hdc, x*32 + Xpos, y*32 + Ypos, 32, 32, CompHdc, 0, 0, SRCCOPY);
                } //Fine switch
            } //fine for con contatore y
        }//fine for con contatore x
        TextFont = CreateFont(50, 0, 0, 0, FW_BLACK, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, TEXT("Calibri"));
        SelectObject(Hdc, hPen);
        SelectObject(Hdc, hBr);
        TxScoreLen = sprintf(TxScore, "Punti: %d", Score);
        TxLevelLen = sprintf(TxLevel, "Livello: %d", level);
        TxLinesLen = sprintf(TxLines, "Linee: %d", Lines);
        Rectangle(Hdc, Xpos + 32 * GameWidth + 40, Ypos + 155, Xpos + 32 * GameWidth + 150, Ypos + 200);
        Rectangle(Hdc, Xpos + 32 * GameWidth + 40, Ypos + 210, Xpos + 32 * GameWidth + 150, Ypos + 255);
        Rectangle(Hdc, Xpos + 32 * GameWidth + 40, Ypos + 265, Xpos + 32 * GameWidth + 150, Ypos + 310);
        SetBkMode(Hdc, TRANSPARENT);
        SetTextColor(Hdc, 0x004FFF);
        TextRect = {Xpos + 32 * GameWidth + 55, Ypos + 165, Xpos + 32 * GameWidth + 150, Ypos + 200};
        DrawText(Hdc, TxScore, TxScoreLen, &TextRect, DT_LEFT); //Mostriamo il punteggio
        TextRect = {Xpos + 32 * GameWidth + 55, Ypos + 220, Xpos + 32 * GameWidth + 150, Ypos + 255};
        DrawText(Hdc, TxLevel, TxLevelLen, &TextRect, DT_LEFT); //Mostriamo il livello
        TextRect = {Xpos + 32 * GameWidth + 55, Ypos + 275, Xpos + 32 * GameWidth + 150, Ypos + 310};
        DrawText(Hdc, TxLines, TxLinesLen, &TextRect, DT_LEFT); //Mostriamo le linee eliminate
        for (x = 0; x < 4; x++) //disegnamo la finestra che mostra il pezzo successivo
            for(y = 0; y < 4; y++){
                switch(LASTTHREEBITS(NextPiece[x][y])){
                    case PSTYLE_RED:
                        SelectObject(CompHdc, BlockRed);
                        BitBlt(Hdc,
                               x * 32 + Xpos + 32 * GameWidth + 40,
                               y * 32 + Ypos + 10,
                               32,
                               32,
                               CompHdc,
                               0,
                               0,
                               SRCCOPY
                              );
                        break;
                    case PSTYLE_YELLOW:
                        SelectObject(CompHdc, BlockYellow);
                        BitBlt(Hdc,
                               x * 32 + Xpos + 32 * GameWidth + 40,
                               y * 32 + Ypos + 10,
                               32,
                               32,
                               CompHdc,
                               0,
                               0,
                               SRCCOPY
                              );
                        break;
                    case PSTYLE_GREEN:
                        SelectObject(CompHdc, BlockGreen);
                        BitBlt(Hdc,
                               x * 32 + Xpos + 32 * GameWidth + 40,
                               y * 32 + Ypos + 10,
                               32,
                               32,
                               CompHdc,
                               0,
                               0,
                               SRCCOPY
                              );
                        break;
                    case PSTYLE_CYAN:
                        SelectObject(CompHdc, BlockCyan);
                        BitBlt(Hdc,
                               x * 32 + Xpos + 32 * GameWidth + 40,
                               y * 32 + Ypos + 10,
                               32,
                               32,
                               CompHdc,
                               0,
                               0,
                               SRCCOPY
                              );
                        break;
                    case PSTYLE_BLUE:
                        SelectObject(CompHdc, BlockBlue);
                        BitBlt(Hdc,
                               x * 32 + Xpos + 32 * GameWidth + 40,
                               y * 32 + Ypos + 10,
                               32,
                               32,
                               CompHdc,
                               0,
                               0,
                               SRCCOPY
                              );
                        break;
                    case PSTYLE_VIOLET:
                        SelectObject(CompHdc, BlockViolet);
                        BitBlt(Hdc,
                               x * 32 + Xpos + 32 * GameWidth + 40,
                               y * 32 + Ypos + 10,
                               32,
                               32,
                               CompHdc,
                               0,
                               0,
                               SRCCOPY
                              );
                        break;
                    case PSTYLE_GRAY:
                        SelectObject(CompHdc, BlockGray);
                        BitBlt(Hdc,
                               x * 32 + Xpos + 32 * GameWidth + 40,
                               y * 32 + Ypos + 10,
                               32,
                               32,
                               CompHdc,
                               0,
                               0,
                               SRCCOPY
                              );
                } //Fine switch
            } //fine for con contatore y
        //fine for con contatore x
    } //End if

    DeleteObject(hPen);
    DeleteObject(hBr);
    DeleteObject(TextFont);
    DeleteObject(BlockBlue);
    DeleteObject(BlockCyan);
    DeleteObject(BlockGray);
    DeleteObject(BlockGreen);
    DeleteObject(BlockRed);
    DeleteObject(BlockViolet);
    DeleteObject(BlockYellow);
    EndPaint(MainWND, &ps);
}
