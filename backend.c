/***************************************************************************//**
  @file     backend
  @brief   backend generico para raspi y para allegro
  @author   Alejandro Alatsis
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include"backend.h"

//hola
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static void falta_envido (int);+

void crear_enemigo(int);
void crear_muro(void);
    


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static int space[LARGO][ANCHO];


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void inimat(void){ //inicializa la mat como vacia
    int i=0, j=0;
    for(i=0;i<LARGO;++i){     
        for(j=0;j<ANCHO;++j){
            space[i][j]=0;
        }       
    }
}
/////////////////////////////////////////////////////////////////////
void ininiv(int nivel){//inicializa las naves enemigas y la del jugador
    //harcodeo la nave del player
    space[LARGO-1][ANCHO/2]=PLAYER;
           crear_enemigo(nivel);
           crear_muro();
       /*case -1://PARA TESTEAR :)
            space[3][7]=ENEMYSHOT;
            space[11][15]=PSHOT;
           for(i=13;i<15;++i){
                for(j=1;j<LARGO;j+=3){//seteo defensas
                    space[i][j]=MURO;
                    ++j;
                    space[i][j]=MURO;
                    ++j;
                    space[i][j]=MURO;
                }       
            }*/ 
}
///////////////////////////////////////////////////////////////////////////////////
int ciclonaves (void){//mueva las naves en la matriz
    int mov,i,j;
    int exit=0;
    static int direccion =DER;
    static int bajar=0;//defino si bajo o no 1 para si
    if(bajar==0){//si no tiene q bajar
        if(direccion==DER){//muevo las naves a la derecha
            mov=DER;
            for(i=(LARGO-2);i>=0;--i){
                for(j=(ANCHO-1);j>=0;--j){ 
                    if((space[i][j]>=1)&&(space[i][j]<=5)){//si hay nave
                        movmat(i,j,mov); 
                        if((space[i][ANCHO-1]>=1)&&(space[i][ANCHO-1]<=4)){//si hay algo en la ultima col
                            direccion=IZQ;//invierto direccion
                            bajar=1;//indico q tengo q bajar
                        }
                    }
                }
            }
        }else{//muevo las naves a la izquierda
            mov =IZQ;
            for(i=(LARGO-2);i>=0;--i){
                for(j=0;j<ANCHO;++j){
                    if((space[i][j]>=1)&&(space[i][j]<=5)){//si hay nave                       
                        movmat(i,j,mov); 
                        if((space[i][0]>=1)&&(space[i][0]<=4)){//si hay algo en la primer col
                            direccion=DER;//invuerto direccion
                            bajar=1;//indico q tengo q bajar
                        }
                    }
                }
            }
        }
    }else{//tiene q bajar
        mov=ABAJO;
        for(i=(LARGO-2);i>=0;--i){
            for(j=0;j<ANCHO;++j){
                if((space[i][j]>=1)&&(space[i][j]<=5)){//si hay nave                           
                    movmat(i,j,mov);                         
                }               
            }
        }
        for(i=(LARGO-1),j=0;j<ANCHO;++j){
            if((space[i][j]>=1)&&(space[i][j]<=5)){//si hay nave 
                exit=1;//marco salir
            }
        }
    }
    return exit;
}
////////////////////////////////////////////////////////////////////////////////////////
void nav_nod(void){    //spawnea nave nod y mueve nave nod
    int i,j,haynavenod,num;
    int mov=DER;
    for(j=0;j<ANCHO;++j){//me fijo si hay una nave nod en juego
        if(space[0][j]==NAVNOD){
            haynavenod=1;//marco que hay nave nod
        }else{
            haynavenod=0;//no hay una nave
        }
    }
    if(haynavenod==0){//si no hay nave me fijo de spawnear una
        space[0][0]=NAVNOD;
        space[0][1]=NAVNOD;       
    }
    for(i=(LARGO-2);i>=0;--i){
        for(j=(ANCHO-1);j>=0;--j){
            if(space[i][j]==NAVNOD){//si es la nave nodriza, siempre se mueve de izq a der
                if(j==(ANCHO-1)){//si la nave nod esta al borde desaparece
                    space[i][j-1]=0;
                    space[i][j]=0;
                }else{
                    movmat(i,j,mov);
                }   
            }
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void ciclodisp (int *vidas,int *puntaje){//mueve los disparos y cambia puntaje y vidas
    int i,j,mov;
    for(i=(LARGO-1);i>=0;--i){
        for(j=(ANCHO-1);j>=0;--j){
            if(space[i][j]==ESHOT){//si hay un disparo enemigo
                mov=ABAJO;
                if(i==(LARGO-1)){//si estoy en la ultima fila lo desaparezco
                    space[i][j]=0;
                }else{//si estoy en otra fila
                    if(space[i+1][j]==0){//si adelante del disparo no hay nada
                        movmat(i,j,mov);
                    }else{//hay algo
                        if(space[i+1][j]==PLAYER){//si es el jugador
                            space[i][j]=0;
                            *vidas-=1;//pierde una vida
                        }else{//si es un escudo
                            space[i][j]=0;
                            space[i+1][j]=0;//rompe el escudo
                        }
                    }
                }
            }
        }
    }
    for(i=0;i<LARGO;++i){
        for(j=0;j<ANCHO;++j){
            if(space[i][j]==PSHOT){//si hay un disparo de jugador
                mov=UP;
                if(i==0){//estoy en la primer fil 
                    space[i][j]=0;
                }else{
                    if(space[i-1][j]==0){//si adelante del disparo no hay nada
                        movmat(i,j,mov);
                    }else{//hay algo
                        if((space[i-1][j]==ENEMY)||(space[i-1][j]==ENEMYSHOT)||(space[i-1][j]==NAVNOD)||(space[i-1][j]==ENEMY_2)||(space[i-1][j]==ENEMY_3)){//si es enemigo cambiar si se agregan mas tipos de nemigos
                            *puntaje+=((space[i-1][j])*10);
                            if(space[i-1][j]==NAVNOD){//si es la nave nod
                                if(space[i-1][j-1]==NAVNOD){//me fijo donde esta la otra parte de la nave nod
                                    space[i][j]=0;
                                    space[i-1][j]=0;//mato al enemigo
                                    space[i-1][j-1]=0;//mato la otra parte de la nav nod
                                }else{
                                    space[i][j]=0;
                                    space[i-1][j]=0;//mato al enemigo
                                    space[i-1][j+1]=0;//mato la otra parte de la nav nod
                                }
                            }else{//si es otra nave
                                space[i][j]=0;
                                space[i-1][j]=0;//mato al enemigo
                            }
                        }else{//si es un escudo
                            space[i][j]=0;
                            space[i-1][j]=0;//rompe el escudo
                        }
                    }
                }
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////
void verparams(int *naves,int *puntaje){//se fija si pasaste al siguiente nivel y de actualizar las naves q disparan
    int i,j;
    *naves=0;//pongo que hay 0 naves
    int vacio =0;//1 si hay naves 0 si no
    static int prom=1;//1 si tengo q promover una nave para q dispare
    for(i=0;i<LARGO;++i){
        for(j=0;j<ANCHO;++j){
            if((space[i][j]>=1)&&(space[i][j]<=5)){//si hay naves
                vacio=1;//marco q no incremento el nivel
                *naves+=1;//cuento las naves
            }
        }
    }
    //ojo aca q me manejo con cols primero y despues fils
    for(i=0;i<ANCHO;++i){
        for(j=(LARGO-2);j>=0;--j){
            if(space[j][i]==ENEMYSHOT){//si hay un enemigo q dispara en esa col
                prom=0;//no necesito promover a otro para q dispare
            }
            if( (space[j][i]==ENEMY) || (space[j][i]==ENEMY_2) || (space[j][i]==ENEMY_3)){//cambiar si agrego mas tipos de enemigos
                if(prom==1){//si no encontre ninguna nave q dispara antes q esta
                    *puntaje-=(ENEMYSHOT-space[i][j])*10;
                    space[j][i]=ENEMYSHOT; //promuevo esa nave para q dispare                    
                    prom=0;//ya no necesito promover otra
                }
            }
        }
        prom=1;//parto diciendo q en esa col hay naves q necesiten ser promovidas
    }
}
//////////////////////////////////////////////////////////////////////////////
void navdisp(int *vidas,int *puntaje,int *nivel,int numrandom){//determina cuando las naves disparan y cuando aparece la nave nodriza
    int i,j;
    int haynavenod=0;//1 para si
    int num=0;//numero random
    //srand(time(NULL));
    for(i=0;i<LARGO;++i){
        for(j=0;j<ANCHO;++j){
            if(space[i][j]==ENEMYSHOT){
                num = rand() %100 + 1;//genero un num random entre 1 y 100
                num +=numrandom;
                if(num<=20){//20% de q dispare
                    if(space[i+1][j]==PLAYER){
                        *vidas-=1;//pierde una vida
                    }else{
                        space[i+1][j]=ESHOT;//spawneo un disparo
                    }
                }
            }
        }
    }   
}
/////////////////////////////////////////////////////////////////////////////////////
void pmov(int *puntaje,int mov){//movimiento y disparo del jugador
    int disparo=0;//1 si hay diapro ya en juego
    int i,j;
    //aca ir a allegro o raspberry
    for(i=0;i<LARGO;++i){//sacar estos for para multidisparo añadir breack point para testeo
        for(j=0;j<ANCHO;++j){
            if(space[i][j]==PSHOT){
                disparo=1;//marco q ya hay un disparo en juego
            }
        }
    } 
      //mov= algo de allegro
    //mov= voy a algo de raspi, falta programar
    switch(mov){//me fijo que tipo de mov recibo
        case 0://no me muevo
            break;
        case 1://me muevo a derecha
            for(j=ANCHO-1;j>=0;--j){
                if(j==(ANCHO-1)){//si estoy a la derecha de todo no me muevo

                }else{
                    if(space[LARGO-1][j]==PLAYER){//si es la nave la muevo a la der
                        space[LARGO-1][j+1]=PLAYER;
                        space[LARGO-1][j]=0;
                    }
                }
            }
            break;
        case 2://me muevo a la izq
            for(j=0;j<ANCHO;++j){
                if(j==0){//si estoy a la izquierda de todo no me muevo

                }else{
                    if(space[LARGO-1][j]==PLAYER){//si es la nave la muevo a la izq
                        space[LARGO-1][j-1]=PLAYER;
                        space[LARGO-1][j]=0;
                    }
                }
            }
            break;
        case 3://disparo sin moverme (arriba)
            for(j=0;j<ANCHO;++j){               
                if(space[LARGO-1][j]==PLAYER){//si es la nave disparo
                    if(disparo==0){//si no hay un disparo en juego
                        if((space[LARGO-2][j]>=1)&&(space[LARGO-2][j]<=5)){//si hay un enemigo justo adelante
                            *puntaje+=((space[LARGO-2][j])*5);//sumo puntos
                            space[LARGO-2][j]=0;//mato la nave
                        }else{
                            if(space[LARGO-2][j]==MURO){//si hay muro
                                space[LARGO-2][j]=0;//rompe el muro
                            }else{
                                space[LARGO-2][j]=PSHOT;//spawneo el disparo del jugador
                            }
                        }
                    }
                }                
            }
            break;
        case 4://disparo y me muevo a la derecha
            for(j=ANCHO-1;j>=0;--j){
                if(j==(ANCHO-1)){//si estoy a la derecha de todo no me muevo
                    if(space[LARGO-1][j]==PLAYER){//si es la nave disparo
                        if(disparo==0){//si no hay un disparo en juego
                            if((space[LARGO-2][j]>=1)&&(space[LARGO-2][j]<=5)){//si hay un enemigo justo adelante
                                *puntaje+=((space[LARGO-2][j])*5);//sumo puntos
                                space[LARGO-2][j]=0;//mato la nave
                            }else{
                                if(space[LARGO-2][j]==MURO){//si hay muro
                                    space[LARGO-2][j]=0;//rompe el muro
                                }else{
                                    space[LARGO-2][j]=PSHOT;//spawneo el disparo del jugador
                                }
                            }
                        }
                    }
                }else{
                    if(space[LARGO-1][j]==PLAYER){//si es la nave disparo
                        if(disparo==0){//si no hay un diapro en juego
                            if((space[LARGO-2][j]>=1)&&(space[LARGO-2][j]<=5)){//si hay un enemigo justo adelante
                                *puntaje+=((space[LARGO-2][j])*5);//sumo puntos
                                space[LARGO-2][j]=0;//mato la nave
                                space[LARGO-1][j+1]=PLAYER;//muevo a la der
                                space[LARGO-1][j]=0;
                            }else{
                                if(space[LARGO-2][j]==MURO){//si hay muro
                                    space[LARGO-2][j]=0;//rompo muro
                                    space[LARGO-1][j+1]=PLAYER;//muevo a la der
                                    space[LARGO-1][j]=0;
                                }else{
                                    space[LARGO-2][j]=PSHOT;//spawneo el disparo del jugador
                                    space[LARGO-1][j+1]=PLAYER;//muevo a la der
                                    space[LARGO-1][j]=0;
                                }
                            }
                        }else{//si hay un disparo solo me muevo
                            space[LARGO-1][j+1]=PLAYER;//muevo a la der
                            space[LARGO-1][j]=0;
                        }
                    }
                }
            }
        break;
        case 5://disparo y me muevo a la izq
            for(j=0;j<ANCHO;++j){
                if(j==0){//si estoy a la izq de todo no me muevo
                    if(space[LARGO-1][j]==PLAYER){//si es la nave disparo
                        if(disparo==0){//si no hay disparo
                            if((space[LARGO-2][j]>=1)&&(space[LARGO-2][j]<=5)){//si hay un enemigo justo adelante
                                *puntaje+=((space[LARGO-2][j])*5);//sumo puntos
                                space[LARGO-2][j]=0;//mato la nave
                            }else{
                                if(space[LARGO-2][j]==MURO){//si hay muro
                                    space[LARGO-2][j]=0;//rompo muro
                                }else{
                                    space[LARGO-2][j]=PSHOT;//spawneo el disparo del jugador
                                }
                            }
                        }
                    }
                }else{
                    if(space[LARGO-1][j]==PLAYER){//si es la nave disparo
                        if(disparo==0){//si no hay un disparo
                            if((space[LARGO-2][j]>=1)&&(space[LARGO-2][j]<=5)){//si hay un enemigo justo adelante
                                *puntaje+=((space[LARGO-2][j])*5);//sumo puntos
                                space[LARGO-2][j]=0;//mato la nave
                                space[LARGO-1][j-1]=PLAYER;//muevo a la izq
                                space[LARGO-1][j]=0;
                            }else{
                                if(space[LARGO-2][j]==MURO){//si hay muro
                                    space[LARGO-2][j]=0;//rompo muro
                                    space[LARGO-1][j-1]=PLAYER;//muevo a la izq
                                    space[LARGO-1][j]=0;
                                }else{
                                    space[LARGO-2][j]=PSHOT;//spawneo el disparo del jugador
                                    space[LARGO-1][j-1]=PLAYER;//muevo a la izq
                                    space[LARGO-1][j]=0;
                                }
                            }
                        }else{//si hay un disparo solo muevo
                            space[LARGO-1][j-1]=PLAYER;//muevo a la izq
                            space[LARGO-1][j]=0;
                        }
                    }
                }
            }
        break;
        default:
            break;
            
    }
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
#ifdef TESTEO
void printmat(void){//para testeo
    int m=0;
    int n=0;
    for(m=0;m<LARGO;++m){     /*mientras el contador de filas sea distinto a la cant. de filas, me fijo en las columnas*/
        for (n=0;n<ANCHO;++n){    /*mientras el contador de cols. sea distinto a la cant. de cols.imprime lo que haya en ese lugar de la matriz*/
            printf("%d", space[m][n]);
        }
        printf("\n");
    }
    printf("\n");
}
#endif
/////////////////////////////////////////////////////////////////////////////
void crear_enemigo(int nivel) {
    int i,j;
    if(nivel > 5){ // limita la cantidad de niveles a 5 para evitar desbordamientos del stack
        nivel=5;
    }
    
    for(i=nivel;i<(nivel+3);i+=2){     
        for(j=1;j<ANCHO;j+=SEP_RASP){//seteo enemigos
            if(i==nivel){
                space[i][j]=ENEMY_3;
            }else{
                if(i==(nivel+2))
                {
                    if(nivel>2){
                        space[i][j]=ENEMY_2;
                    }else{
                        space[i][j]=ENEMY;
                    }                                
                }                       
            }
        }       
    }
    for(i=(nivel+4);i<(nivel+5);++i){
        for(j=1;j<ANCHO;j+=SEP_RASP){
            space[i][j]=ENEMYSHOT;
        }
    }
}
/////////////////////////////////////////////////////////////////////////////
void crear_muro(void)
{
    int i,j;
    for(i=13;i<15;++i){     
        for(j=1;j<ANCHO;j+=3){//seteo defensas
            space[i][j]=MURO;
            ++j;
            space[i][j]=MURO;
            ++j;
            space[i][j]=MURO;
        }       
    }
    
}
//////////////////////////////////////////////////////////////////////////////
void movmat(int largo,int ancho,int mov){//mueve elementos de la matriz a izquierda derecha arriba o abajo
    switch(mov){
        case DER:
           space[largo][ancho+1]=space[largo][ancho];//muevo lo que haya ahi
           space[largo][ancho]=0;//borro su anterior posicion
        break;
        case IZQ:
           space[largo][ancho-1]=space[largo][ancho];
           space[largo][ancho]=0; 
        break;
        case UP:
           space[largo-1][ancho]=space[largo][ancho];
           space[largo][ancho]=0; 
        break;
        case ABAJO:
           space[largo+1][ancho]=space[largo][ancho];
           space[largo][ancho]=0; 
        break;
        default:
        break;
            
                
    }
}
int getmat(int i,int j){
    int dato;
    return dato=space[i][j];
}
//////////////////////////////////////////////////////////////////
#ifdef RASPI
void matniv(void){// escribe LV UP
    int i=0;
    for(i=4;i<8;++i){
        switch(i){
            case 4:/*dcoord_t myPoint = {i, j};
                disp_write(myPoint, D_ON);*/
                space[i][1]=space[i][5]=space[i][7]=space[i][9]=space[i][11]=space[i][13]=space[i][14]=1;
                break;
            case 5:
                space[i][1]=space[i][5]=space[i][7]=space[i][9]=space[i][11]=space[i][13]=space[i][15]=1;
                break;
            case 6:
                space[i][1]=space[i][5]=space[i][7]=space[i][9]=space[i][11]=space[i][13]=space[i][14]=1;
                break;
            case 7:
                space[i][1]=space[i][2]=space[i][3]=space[i][6]=space[i][9]=space[i][10]=space[i][11]=space[i][13]=1;
                break;
            default:
                break;
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
void printnum(int num,int digit[]){//imprimi un digito en la pos correspondiente
    int a,b,c,d;
    a=digit[0];
    b=digit[1];
    c=digit[2];
    d=digit[3];
    switch(num){
        case 0://escribo 0
            space[10][a]=space[11][a]=space[12][a]=space[13][a]=space[14][a]=1;
            space[10][c]=space[11][c]=space[12][c]=space[13][c]=space[14][c]=1;
            space[10][b]=space[14][b]=1;
            break;
        case 1://escribo 1
            space[10][a]=space[11][a]=space[12][a]=space[13][a]=space[14][a]=1;
            break;
        case 2://escribo 2
            space[11][a]=space[14][a]=1;
            space[10][b]=space[12][b]=space[14][b]=1;
            space[10][c]=space[13][c]=space[14][c]=1;
            space[11][d]=space[14][d]=1;
            break;
        case 3://escribo 3
            space[10][a]=space[11][a]=space[12][a]=space[13][a]=space[14][a]=1;
            space[10][b]=space[12][b]=space[14][b]=1;
            space[10][c]=space[12][c]=space[14][c]=1;
            space[10][d]=space[12][d]=space[14][d]=1;
            break;
        case 4://escribo 4
            space[10][a]=space[11][a]=space[12][a]=space[13][a]=space[14][a]=1;
            space[11][b]=1;
            space[10][c]=space[11][c]=1;
            break;
        case 5://escribo 5
            space[10][a]=space[13][a]=1;
            space[10][b]=space[12][b]=space[14][b]=1;
            space[10][c]=space[12][c]=space[14][c]=1;
            space[10][d]=space[11][d]=space[14][d]=1;
            break;
        case 6://escribo 6
            space[10][a]=space[12][a]=space[13][a]=space[14][a]=1;
            space[10][b]=space[12][b]=space[14][b]=1;
            space[10][c]=space[11][c]=space[12][c]=space[13][c]=space[14][c]=1;
            break;
        case 7://escribo 7
            space[12][a]=1;
            space[10][b]=space[11][b]=space[12][b]=space[13][b]=space[14][b]=1;
            space[10][c]=space[12][c]=1;
            space[10][d]=1;
            break;
        case 8://escribo 8
            space[10][a]=space[11][a]=space[13][a]=space[14][a]=1;
            space[10][b]=space[12][b]=space[14][b]=1;
            space[10][c]=space[11][c]=space[13][c]=space[14][c]=1;
            break;
        case 9://escribo 9
            space[10][a]=space[11][a]=space[12][a]=space[13][a]=space[14][a]=1;
            space[10][b]=space[12][b]=1;
            space[10][c]=space[11][c]=space[12][c]=1;
            break;
        default:
            break;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////
void printscore(int puntaje){//imprime el puntaje
    int num=0;//aisla digitos para pasar a matriz
    inimat();
    int auxmat [4];//para determinar que cols usar degun el digito
    int i;
    for(i=4;i<=8;++i){
        switch(i){//escribe PTS
            case 4:
                space[i][1]=space[i][2]=space[i][6]=space[i][5]=space[i][7]=space[i][10]=space[i][11]=space[i][12]=1;
                break;
            case 5:
                space[i][1]=space[i][3]=space[i][6]=space[i][9]=1;
                break;
            case 6:
                space[i][1]=space[i][2]=space[i][6]=space[i][10]=space[i][11]=1;
                break;
            case 7:
                space[i][1]=space[i][6]=space[i][12]=1;
                break;
            case 8:
                space[i][1]=space[i][6]=space[i][9]=space[i][10]=space[i][11]=1;
                break;                
            default:
                break;
        }
    }
    for(i=0;i<3;++i){//pasa digit de der a izq 3 digitos
        num=(puntaje%10);
        puntaje=(puntaje/10);
        switch(i){
            case 0:
                auxmat[0]=15;
                auxmat[1]=14;
                auxmat[2]=13;
                auxmat[3]=12;
                printnum(num,auxmat);
                break;
            case 1:
                auxmat[0]=9;
                auxmat[1]=8;
                auxmat[2]=7;
                auxmat[3]=6;
                printnum(num,auxmat);
                break;
            case 2:
                auxmat[0]=3;
                auxmat[1]=2;
                auxmat[2]=1;
                auxmat[3]=0;
                printnum(num,auxmat);
                break;
            default:
                break;
        }
    }
    printmat();
    sleep(3);
}
#endif