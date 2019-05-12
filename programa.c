#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    int primos=2, input1, input2, numero1, numero2, *primosNumero1, *primosNumero2, contadorPrimos1=0, contadorPrimos2=0, i, j, k;
    int mcd=1, mcm=1, *primosGlobal, contadorPrimosGlobal=0;

    //Asignamos memoria al arreglo de los factores primos del numero 1
    primosNumero1 = (int*)calloc(contadorPrimos1, sizeof(int)); 
    //Pedimos el primer numero
    printf("Dame el primer numero: ");
    scanf("%d", &input1);
    numero1=input1;
    //El programa busca todos los factores del input1, hasta que el numero se haga 1, dando a entender que ya de dividio con todos sus posibles factores
    while(numero1!=1){
        if(numero1%primos == 0){
            primosNumero1 = (int*)realloc(primosNumero1, (contadorPrimos1+1)*sizeof(int));
            primosNumero1[contadorPrimos1] = primos;
            numero1=numero1/primos;
            contadorPrimos1++;
        }
        else{
            primos++;
        }
    }
    //Reiniciamos el valor de los primos a 2 
    primos=2;
    //Asignamos memoria al arreglo de los factores primos del numero 2
    primosNumero2 = (int*)calloc(contadorPrimos2, sizeof(int));
    //Pedimos el segundo numero
    printf("Dame el primer numero: ");
    scanf("%d", &input2);
    numero2=input2;
    //El programa busca todos los factores del input2, hasta que el numero se haga 1, dando a entender que ya de dividio con todos sus posibles factores
     while(numero2 != 1){
        if(numero2%primos == 0){
            primosNumero2 = (int*)realloc(primosNumero2, (contadorPrimos2+1)*sizeof(int));
            primosNumero2[contadorPrimos2] = primos;
            numero2=numero2/primos;
            contadorPrimos2++;
        }
        else{
            primos++;
        }
    }
    //Asignamos memoria al arreglo de todos los primos de los 2 numeros (sin repeticiones de los primos)
    primosGlobal = (int*)calloc(contadorPrimosGlobal, sizeof(int));
    //Buscamos los primos del primer numero y los asignamos al arreglo primosGlobal, estos si se llegan a repetir, solo seran agregados una vez
    for(i=0;i<contadorPrimos1;i++){
        if(i==0){
            primosGlobal = (int*)realloc(primosGlobal, (contadorPrimosGlobal+1)*sizeof(int));
            primosGlobal[contadorPrimosGlobal]=primosNumero1[i];
            contadorPrimosGlobal++;
        }
        else{
            if(primosNumero1[i] != primosNumero1[i-1]){
                primosGlobal = (int*)realloc(primosGlobal, (contadorPrimosGlobal+1)*sizeof(int));
                primosGlobal[contadorPrimosGlobal]=primosNumero1[i];
                contadorPrimosGlobal++;
            }            
        }
    }
    //Buscamos los primos del segundo numero, iterando y comparando con el arreglo de primosGlobal, si se repiten en el arreglo global, no se agregan, sino, se agregaran.
    int repeated;
    for(i=0;i<contadorPrimos2;i++){
        repeated=0;
        for(j=0; j<contadorPrimosGlobal;j++){
            if(primosNumero2[i] == primosGlobal[j]){
                repeated=1;
                break;
            }
        }
        if(repeated==0){
            primosGlobal = (int*)realloc(primosGlobal, (contadorPrimosGlobal+1)*sizeof(int));
            primosGlobal[contadorPrimosGlobal] = primosNumero2[i];
            contadorPrimosGlobal++;
        }
    }
    //Creamos los arreglos de los exponentes (veces que se repite) de cada primo para cada arreglo de factores
    int expPrimos1[contadorPrimosGlobal], expPrimos2[contadorPrimosGlobal];
    //inicializamos cada elementos de cada arreglo con 0
    for(i=0;i<contadorPrimosGlobal;i++){
        expPrimos1[i]=0;
        expPrimos2[i]=0;
    }
    //asignamos las repeticiones de cada factor para cada arreglo
    for(i=0;i<contadorPrimosGlobal;i++){
        for (j = 0; j < contadorPrimos1; j++){
            if(primosGlobal[i] == primosNumero1[j]){
                expPrimos1[i]++;
            }
        }
        for (j = 0; j < contadorPrimos2; j++){
            if(primosGlobal[i] == primosNumero2[j]){
                expPrimos2[i]++;
            }
        }
    }
    //MCD
    for(i=0;i<contadorPrimosGlobal;i++){
        if(expPrimos1[i]<=expPrimos2[i]){
            for(j=1; j<=expPrimos1[i]; j++){
                mcd=mcd*primosGlobal[i];
            }
        }
        else{
            for(j=1; j<=expPrimos2[i]; j++){
                mcd=mcd*primosGlobal[i];
            }
        }
    }

    //MCM
    for(i=0;i<contadorPrimosGlobal;i++){
        if(expPrimos1[i]>= expPrimos2[i]){
            for(j=1; j<=expPrimos1[i]; j++){
                mcm=mcm*primosGlobal[i];
            }
        }
        else{
            for(j=1; j<=expPrimos2[i]; j++){
                mcm=mcm*primosGlobal[i];
            }
        }
    }
    //imprimir primos solo con su exponente y no repeticiones
    //Se imprimen los factores de cada numero
    printf("\n");
    printf("Los factores de %d son: ", input1);
    for (i = 0; i < contadorPrimosGlobal; i++){
        if(expPrimos1[i] > 1){
            printf("(%d^%d)", primosGlobal[i], expPrimos1[i]);
        }
        else if (expPrimos1[i] == 1){
            printf("(%d)", primosGlobal[i]);
        }
    }
    printf("\n");
    printf("Los factores de %d son: ", input2);
    for (i = 0; i < contadorPrimosGlobal; i++){
        if(expPrimos2[i] > 1){
            printf("(%d^%d)", primosGlobal[i], expPrimos2[i]);
        }
        else if (expPrimos2[i] == 1){
            printf("(%d)", primosGlobal[i]);
        }
    }

    printf("\nmcd: %d", mcd);
    printf("\nmcm: %d", mcm);

    getch();
    return 0;
}
