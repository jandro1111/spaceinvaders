/***************************************************************************//**
  @file     backend
  @brief   backend generico para raspi y para allegro
  @author   Alejandro Alatsis
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include"backend.h"

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

void crear_enemigo(int, int [][ANCHO]);
void crear_muro(int [][ANCHO]);
    


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static int temperaturas_actuales[4];+


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void inimat(int space[][ANCHO]){ //inicializa la mat como vacia
    int i=0, j=0;
    for(i=0;i<LARGO;++i){     
        for(j=0;j<ANCHO;++j){
            space[i][j]=0;
        }       
    }
}
/////////////////////////////////////////////////////////////////////
void ininiv(int space[][ANCHO],int nivel){//inicializa las naves enemigas y la del jugador
    //harcodeo la nave del player
    space[LARGO-1][ANCHO/2]=PLAYER;
    //
    int i,j;
    switch(nivel){
       case 1:
           crear_enemigo(nivel,space);
           crear_muro(space);
           break;
       case 2:
           crear_enemigo(nivel,space);
           crear_muro(space);
           
           break;
       case 3:
            crear_enemigo(nivel,space);
            crear_muro(space);
           break;
       case -1://PARA TESTEAR :)
           /* space[3][7]=ENEMYSHOT;
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
           break;
        default:
           crear_enemigo(nivel,space);
           crear_muro(space);
           break;
               
   } 
}
///////////////////////////////////////////////////////////////////////////////////
int ciclonaves (int space[LARGO][ANCHO],int direccion){//mueva las naves en la matriz
    int i=0;
    int j=0;
    int bajar=0;//defino si bajo o no 1 para si
    if(direccion==DER){//si va para la derecha me fijo la col de la derecha
        for(i=0;i<LARGO;++i){
            if((space[i][ANCHO-1]>=1)&&(space[i][ANCHO-1]<=4)){//si hay algo en la ultima col
                direccion=IZQ;//invierto direccion
                bajar=1;//indico q tengo q bajar
            }
        }
    }else{//me fijo en la col de la izquierda
        for(i=0;i<LARGO;++i){//si va para la izq
            if((space[i][0]>=1)&&(space[i][0]<=4)){//si hay algo en la primer col
                direccion=DER;//invuerto direccion
                bajar=1;//indico q tengo q bajar
            }
        }
    }
    for(i=(LARGO-2),j=0;j<ANCHO;++j){//verifico la penultima fil
        if((space[i][j]>=1)&&(space[i][j]<=4)){//si hay naves en la penultima fil no bajo
            bajar=0;
        }
    }
    if(bajar==0){//si no tiene q bajar
        if(direccion==DER){//muevo las naves a la derecha
            for(i=(LARGO-2);i>=0;--i){
                for(j=(ANCHO-1);j>=0;--j){                   
                        space[i][j+1]=space[i][j];//muevo la nave
                        space[i][j]=0;//borro la posicion anterior de esa nave;                       
                    }
                }
        }else{//muevo las naves a la izquierda
            for(i=(LARGO-2);i>=0;--i){
                for(j=0;j<ANCHO;++j){
                    if((space[i][j]>=1)&&(space[i][j]<=5)){//si hay nave                       
                        space[i][j-1]=space[i][j];//muevo la nave
                        space[i][j]=0;//borro la posicion anterior de esa nave;                        
                    }
                }
            }
        }
    }else{//tiene q bajar
            for(i=(LARGO-2);i>=0;--i){
                    for(j=0;j<ANCHO;++j){
                        if((space[i][j]>=1)&&(space[i][j]<=5)){//si hay nave                           
                            space[i+1][j]=space[i][j];//muevo la nave
                            space[i][j]=0;//borro la posicion anterior de esa nave;                           
                        }
                    }
                }
    }
    return direccion;
}
////////////////////////////////////////////////////////////////////////////////////////
void nav_nod(int space[][ANCHO]){    //spawnea nave nod y mueve nave nod
    int i,j,haynavenod,num;
    for(j=0;j<ANCHO;++j){//me fijo si hay una nave nod en juego
        if(space[0][j]==NAVNOD){
            haynavenod=1;//marco que hay nave nod
        }else{
            haynavenod=0;//no hay una nave
        }
    }
    if(haynavenod==0){//si no hay nave me fijo de spawnear una
        srand(time(NULL));
        num=rand() %100 + 1;
        if(num<=10){//10% de q aparezca
            space[0][0]=NAVNOD;
            space[0][1]=NAVNOD;
        }
    }
    for(i=(LARGO-2);i>=0;--i){
        for(j=(ANCHO-1);j>=0;--j){
            if(space[i][j]==NAVNOD){//si es la nave nodriza, siempre se mueve de izq a der
                if(j==(ANCHO-1)){//si la nave nod esta al borde desaparece
                    space[i][j-1]=0;
                    space[i][j]=0;
                }else{
                    space[i][j+1]=space[i][j];//muevo la nave
                    space[i][j]=0;//borro la posicion anterior de esa nave;
                }   
            }
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void ciclodisp (int space[LARGO][ANCHO],int *vidas,int *puntaje){//mueve los disparos y cambia puntaje y vidas
    int i,j;
    for(i=(LARGO-1);i>=0;--i){
        for(j=(ANCHO-1);j>=0;--j){
            if(space[i][j]==ESHOT){//si hay un disparo enemigo
                if(i==(LARGO-1)){//si estoy en la ultima fila lo desaparezco
                    space[i][j]=0;
                }else{//si estoy en otra fila
                    if(space[i+1][j]==0){//si adelante del disparo no hay nada
                        space[i+1][j]=space[i][j];//muevo el disp
                        space[i][j]=0;//borro la anterior posicion del disp
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
                if(i==0){//estoy en la primer fil 
                    space[i][j]=0;
                }else{
                    if(space[i-1][j]==0){//si adelante del disparo no hay nada
                        space[i-1][j]=space[i][j];//muevo el disp
                        space[i][j]=0;//borro la anterior posicion del disp
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
    if(*puntaje>=1000){//si tengo mas de 1000 puntos gano 1 vida y vuelvo el puntaje a 0
        *vidas+=1;
        *puntaje=0;
    }
}
////////////////////////////////////////////////////////////////////////////////////
int verparams(int space[][ANCHO],int nivel,int *naves,int *puntaje){//se fija si pasaste al siguiente nivel y de actualizar las naves q disparan
    int i,j;
    *naves=0;//pongo que hay 0 naves
    int vacio =0;//1 si hay naves 0 si no
    int prom=1;//1 si tengo q promover una nave para q dispare
    for(i=0;i<LARGO;++i){
        for(j=0;j<ANCHO;++j){
            if((space[i][j]>=1)&&(space[i][j]<=5)){//si hay naves
                vacio=1;//marco q no incremento el nivel
                *naves+=1;//cuento las naves
            }
        }
    }
    if(vacio==0){//si no hay mas naves
        ++nivel;//subo de nivel
#ifdef RASPI       
        matniv(space);//lv up , SOLO PARA RASPI, hacer de otra forma en allegro
        printmat(space);
        sleep(3);
#endif
        inimat(space);//borro el mundo
        ininiv(space,nivel);//cargo el nuevo nivel
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
    return nivel;
}
//////////////////////////////////////////////////////////////////////////////
void navdisp(int space [][ANCHO],int *vidas,int *puntaje,int *nivel,int numrandom){//determina cuando las naves disparan y cuando aparece la nave nodriza
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
void pmov(int space [][ANCHO],int *puntaje,int *ops){//movimiento y disparo del jugador
    int disparo=0;//1 si hay diapro ya en juego
    int i,j;
    int mov=0;//determina q hace, para testeo, borrar despues 
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
//////////////////////////////////////////////////////////////////////////////
void exit_cond(int *vidas,int *exit,int *pausa){//devuelve si se sale del programa o no;
    if(*vidas==0){
        *exit=0;
        *pausa=0;//si pierdo marco como que el juego esta en pausa
    }
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void printmat(int space[][ANCHO]){//para testeo
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
/////////////////////////////////////////////////////////////////////////////
void crear_enemigo(int nivel,int space[][ANCHO]) 
{
    int i,j,p;
    if(nivel > 5){ // limita la cantidad de niveles a 5 para evitar desbordamientos del stack
        p=nivel;
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
    nivel=p; // conservo el valor original del nivel
   
}
/////////////////////////////////////////////////////////////////////////////
void crear_muro(int space[][ANCHO])
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

