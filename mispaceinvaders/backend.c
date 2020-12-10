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
void ininiv(int space[][ANCHO],int nivel){//inicializa las naves enemigas y la del jugador
    //harcodeo la nave del player
    space[15][7]=PLAYER;
    //
    int i,j;
   switch(nivel){
       case 1:
           for(i=1;i<4;i+=2){     
                for(j=1;j<LARGO;j+=4){//seteo enemigos
                    space[i][j]=ENEMY;
                }       
            }
           for(i=5;i<6;++i){
               for(j=1;j<LARGO;j+=4){
                   space[i][j]=ENEMYSHOT;
               }
           }
           for(i=13;i<15;++i){     
                for(j=1;j<LARGO;j+=3){//seteo defensas
                    space[i][j]=MURO;
                    ++j;
                    space[i][j]=MURO;
                    ++j;
                    space[i][j]=MURO;
                }       
            }
           break;
       case 2:
           for(i=1;i<6;i+=2){     
                for(j=1;j<LARGO;j+=4){//seteo enemigos
                    space[i][j]=ENEMY;
                }       
            }
           for(i=7;i<8;++i){
               for(j=1;j<LARGO;j+=4){
                   space[i][j]=ENEMYSHOT;
               }
           }
           for(i=13;i<15;++i){     
                for(j=1;j<LARGO;j+=3){//seteo defensas
                    space[i][j]=MURO;
                    ++j;
                    space[i][j]=MURO;
                    ++j;
                    space[i][j]=MURO;
                }       
            }
           break;
       case 3:
            for(i=1;i<6;i+=2){     
                for(j=1;j<LARGO;j+=3){//seteo enemigos
                    space[i][j]=ENEMY;
                }       
            }
            for(i=7;i<8;++i){
               for(j=1;j<LARGO;j+=3){
                   space[i][j]=ENEMYSHOT;
               }
           }
            for(i=13;i<15;++i){     
                for(j=1;j<LARGO;j+=3){//seteo defensas
                    space[i][j]=MURO;
                    ++j;
                    space[i][j]=MURO;
                    ++j;
                    space[i][j]=MURO;
                }       
            }
           break;
       case -1://testeo
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
            for(i=1;i<8;i+=2){     
                for(j=1;j<LARGO;j+=3){//seteo enemigos
                    space[i][j]=ENEMY;
                }       
            }
            for(i=7;i<8;++i){
               for(j=1;j<LARGO;j+=3){
                   space[i][j]=ENEMYSHOT;
               }
           }
            for(i=13;i<15;++i){     
                for(j=1;j<LARGO;j+=3){//seteo defensas
                    space[i][j]=MURO;
                    ++j;
                    space[i][j]=MURO;
                    ++j;
                    space[i][j]=MURO;
                }       
            }
           break;
               
   } 
}
int ciclonaves (int space[LARGO][ANCHO],int direccion){//mueva las naves en la matriz
    int i=0;
    int j=0;
    int omit=0;//si ya movi a la nave nod 1 para si
    int bajar=0;//defino si bajo o no 1 para si
    if(direccion==DER){//si va para la derecha me fijo la col de la derecha
        for(i=0;i<ANCHO;++i){
            if((space[i][ANCHO-1]>=1)&&(space[i][ANCHO-1]<=4)){//si hay algo en la ultima col
                direccion=IZQ;//invierto direccion
                bajar=1;//indico q tengo q bajar
            }
        }
    }else{//me fijo en la col de la izquierda
        for(i=0;i<ANCHO;++i){//si va para la izq
            if((space[i][0]>=1)&&(space[i][0]<=4)){//si hay algo en la primer col
                direccion=DER;//invuerto direccion
                bajar=1;//indico q tengo q bajar
            }
        }
    }
    for(i=(ANCHO-2),j=0;j<LARGO;++j){//verifico la penultima fil
        if((space[i][j]>=1)&&(space[i][j]<=4)){//si hay naves en la penultima fil no bajo
            bajar=0;
        }
    }
    if(bajar==0){//si no tiene q bajar
        if(direccion==DER){//muevo las naves a la derecha
            for(i=(ANCHO-2);i>=0;--i){
                for(j=(ANCHO-1);j>=0;--j){
                    if((space[i][j]>=1)&&(space[i][j]<=5)){//si hay nave
                        if(space[i][j]==NAVNOD){//si es la nave nodriza, siempre se mueve de izq a der
                            if(j==(ANCHO-1)){//si la nave nod esta al borde desaparece
                                space[i][j-1]=0;
                                space[i][j]=0;
                            }else{
                                space[i][j+1]=space[i][j];//muevo la nave
                                space[i][j]=0;//borro la posicion anterior de esa nave;
                            }   
                        }else{
                            space[i][j+1]=space[i][j];//muevo la nave
                            space[i][j]=0;//borro la posicion anterior de esa nave;
                        }
                    }
                }
            }
        }else{//muevo las naves a la izquierda
            for(i=(ANCHO-2);i>=0;--i){
                for(j=0;j<ANCHO;++j){
                    if((space[i][j]>=1)&&(space[i][j]<=5)){//si hay nave
                        if(space[i][j]==NAVNOD){//si es la nave nod va de izq a der
                            if(j==(ANCHO-1)){//si la nave nod esta al borde desaparece
                                space[i][j-1]=0;
                                space[i][j]=0;
                            }else{
                                if(omit==0){//si no movi la nave nod
                                    omit=1;//marco que ya la movi
                                    space[i][j+2]=space[i][j+1]=space[i][j];//muevo la nave
                                    space[i][j]=0;//borro la posicion anterior de esa nave;
                                }
                            }
                        }else{
                            space[i][j-1]=space[i][j];//muevo la nave
                            space[i][j]=0;//borro la posicion anterior de esa nave;
                        }
                    }
                }
            }
        }
    }else{//tiene q bajar
            for(i=(ANCHO-2);i>=0;--i){
                    for(j=0;j<ANCHO;++j){
                        if((space[i][j]>=1)&&(space[i][j]<=5)){//si hay nave
                            if(space[i][j]==NAVNOD){//si es la nave nod
                                if(j==(ANCHO-1)){//si la nave nod esta al borde desaparece
                                    space[i][j-1]=0;
                                    space[i][j]=0;
                                }else{
                                    if(omit==0){//si no movi la nave nod
                                        omit=1;//marco q ya la movi
                                        space[i][j+2]=space[i][j+1]=space[i][j];//muevo la nave
                                        space[i][j]=0;//borro la posicion anterior de esa nave;
                                    }
                                }
                            }else{
                                space[i+1][j]=space[i][j];//muevo la nave
                                space[i][j]=0;//borro la posicion anterior de esa nave;
                            }
                        }
                    }
                }
    }
    return direccion;
}
void ciclodisp (int space[LARGO][ANCHO],int *vidas,int *puntaje){//mueve los disparos y cambia puntaje y vidas
    int i,j;
    for(i=(LARGO-1);i>=0;--i){
        for(j=(ANCHO-1);j>=0;--j){
            if(space[i][j]==ESHOT){//si hay un disparo enemigo
                if(i==15){//si estoy en la ultima fila lo desaparezco
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
                        if((space[i-1][j]==ENEMY)||(space[i-1][j]==ENEMYSHOT)||(space[i-1][j]==NAVNOD)){//si es enemigo cambiar si se agregan mas tipos de nemigos
                            *puntaje+=((space[i-1][j])*5);
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
int verparams(int space[][ANCHO],int nivel){//se fija si pasaste al siguiente nivel y de actualizar las naves q disparan
    int i,j;
    int vacio =0;//1 si hay naves 0 si no
    int prom=1;//1 si tengo q promover una nave para q dispare
    for(i=0;i<LARGO;++i){
        for(j=0;j<ANCHO;++j){
            if((space[i][j]>=1)&&(space[i][j]<=5)){//si hay naves
                vacio=1;//marco q no incremento el nivel
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
            if(space[j][i]==ENEMY){//cambiar si agrego mas tipos de enemigos
                if(prom==1){//si no encontre ninguna nave q dispara antes q esta
                    space[j][i]=ENEMYSHOT; //promuevo esa nave para q dispare
                    prom=0;//ya no necesito promover otra
                }
            }
        }
        prom=1;//parto diciendo q en esa col hay naves q necesiten ser promovidas
    }
    return nivel;
}
void navdisp(int space [][ANCHO],int *vidas,int *puntaje,int *nivel){//determina cuando las naves disparan y cuando aparece la nave nodriza
    int i,j;
    int haynavenod=0;//1 para si
    int num=0;//numero random
    for(i=0;i<LARGO;++i){
        for(j=0;j<ANCHO;++j){
            if(space[i][j]==ENEMYSHOT){
                srand(j+i+*puntaje);//no uso NULL, pq hace q todas las naves disparen al mismo tiempo
                num = rand() %100 + 1;//genero un num random entre 1 y 100
                if(num<=40){//40% de q dispare
                    if(space[i][j+1]==PLAYER){
                        *vidas-=1;//pierde una vida
                    }
                    space[i+1][j]=ESHOT;//spawneo un disparo
                }
            }
        }
    }
    for(j=0;j<ANCHO;++j){//me fijo si hay una nave nod en juego
        if(space[0][j]==NAVNOD){
            haynavenod=1;//marco que hay nave nod
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
}
void pmov(int space [][ANCHO],int *puntaje){//movimiento y disparo del jugador
    int disparo=0;//1 si hay diapro ya en juego
    int i,j;
    int mov=0;//determina q hace, para testeo, borrar despues 
    for(i=0;i<LARGO;++i){//sacar estos for para multidisparo
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
        case 3://disparo sin moverme
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
void printscore(int space [][ANCHO],int puntaje){//imprime el puntaje
    int num=0;//aisla digitos para pasar a matriz
    inimat(space);
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
                printnum(space,num,auxmat);
                break;
            case 1:
                auxmat[0]=9;
                auxmat[1]=8;
                auxmat[2]=7;
                auxmat[3]=6;
                printnum(space,num,auxmat);
                break;
            case 2:
                auxmat[0]=3;
                auxmat[1]=2;
                auxmat[2]=1;
                auxmat[3]=0;
                printnum(space,num,auxmat);
                break;
            default:
                break;
        }
    }
    printmat(space);
}
int exit_cond(int *vidas){//devuelve si se sale del programa o no
    int exit=1;
    if(*vidas==0){
        exit=0;
    }
    return exit;
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

void matniv(int space[][ANCHO]){// escribe LV UP
    int i=0;
    for(i=4;i<8;++i){
        switch(i){
            case 4:
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
void printnum(int space[][ANCHO],int num,int digit[]){//imprimi un digito en la pos correspondiente
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
