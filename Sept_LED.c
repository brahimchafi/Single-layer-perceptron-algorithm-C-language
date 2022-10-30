#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> 
#define ligne 10
#define colonne 8

int main (){
    
    //--------------------------creation A, W, O, d, X, epsilon--------------------------
    int i,j;
    float epsilon    =   0.2;
    float cpt_A;
    int   O[ligne]; 
    float A[ligne];
    float W[colonne];
    srand(time(NULL));
    for( i = 0 ; i < colonne ; i++ ) {
        W[i]=rand() % 6;
    }
    int   d[ligne]   =   {0,1,0,1,0,1,0,1,0,1};
    int   X[ligne][colonne]= {{1,1,1,1,1,1,1,0},{1,0,1,1,0,0,0,0},{1,1,1,0,1,1,0,1},{1,1,1,1,1,0,0,1},
                              {1,0,1,1,0,0,1,1},{1,1,0,1,1,0,1,1},{1,1,0,1,1,1,1,1},{1,1,1,1,0,0,0,0},
                              {1,1,1,1,1,1,1,1},{1,1,1,1,1,0,1,1}};

    //--------------------------Check for O--------------------------
    int check(float a){
        if(a>=0) return 1;
        else return 0;
    }

    //--------------------------Remplissage de A[]--------------------------
    float* Remplissage_A(float A[],float nW[],int index ){
        for(i=index ; i<ligne ; i++){
            for(j=0 ; j<colonne ; j++){
                cpt_A += nW[j]*X[i][j];
            }
            A[i]=cpt_A;
        }
        return A;
    }

    //--------------------------Fonction check pour remplir O--------------------------
    int* Remplissage_O(float A[]){

        for ( i = 0; i < ligne; i++){
            O[i]=check(A[i]);
        }
        return O;
    }

    //--------------------------Affichage X--------------------------
    for(i=0; i<colonne; i++){
        printf("X%d\t",i);
    }
    printf("Valeur\n");
    for(i=0; i<ligne; i++){
        for(j=0; j<colonne; j++){
            printf("%d",X[i][j]);
            printf(j<colonne-1?"\t":"    =>   %d ",i);
        }
        printf("\n");
        //printf("%f\n",A[i]);
    }
        
    //--------------------------Print A et O et d--------------------------
    printf("\nA\t");printf("O\t");printf("D\n");
    float *Ax= Remplissage_A(A,W,0);
    int *Ox= Remplissage_O(A);
    for ( i = 0; i < ligne; i++){
        printf("%.1f\t",*(Ax + i));printf("%d\t",*(Ox + i));printf("%d\n",d[i]);
    }

    //--------------------------Fonction Correction W --------------------------
    void Correction_W(int index){

        for(j=0;j<colonne;j++){
            W[j]=W[j]+(epsilon*((d[index]-O[index])*X[index][j]));
        }
    }
    //--------------------------Fonction Correction--------------------------
    printf("-----------------------------------------------\n");


    void Correction(float *A,float *W,int *O){
        int stop=0;
        int allCorrect= false;
        int i,index;
        A=Remplissage_A(A,W,0);
        O=Remplissage_O(A);
        while (!allCorrect){
            for ( i = 0; i < ligne; i++){
                if(d[i]!=O[i]){
                    index=i;
                    Correction_W(index);
                    A = Remplissage_A(A,W,index);
                    O = Remplissage_O(A);
                    stop++;
                }
            }
            if(stop==0){
                allCorrect=true;
            }
            stop=0;
        }
    }

    //--------------------------Appel Fonction--------------------------
    Correction(A,W,O);

    //--------------------------Apres correction--------------------------
    printf("Apres correction : \n");
    printf("-----------------------------------------------\n");
    printf("\nA\t");printf("O\t");printf("D\n");

    for ( i = 0; i < ligne; i++){
        printf("%.1f\t",*(A + i));
        printf("%d\t",*(O + i));
        printf("%d\n",d[i]);
    }

}