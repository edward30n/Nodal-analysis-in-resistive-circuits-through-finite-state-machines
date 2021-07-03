#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define TAM 60
clock_t start, end;
double cpu_time_used;
int n;
int lectura() {
    FILE *fApu;
    fApu = fopen("maze4.txt","r");
    char linea[TAM];
    char *token;
    long ret;
    int n = -1;
    while (!feof(fApu)) {
        fgets(linea, TAM, fApu);
        linea[strcspn(linea, "\n")] = 0;
        //Corroborar leida exitosa
        //puts(linea);
        token = strtok(linea, " ");
        //printf("token: %s\n", token);
        token = strtok(NULL, " ");
        ret = atoi(token);
        if (ret > n) {
            n = ret;
        }

    }
    // printf("%d", n);
    fclose(fApu);
    return n;
}
int main()
{
    n = lectura();
    //printf("%d",  n);
    double **mat;
    mat = (double **) malloc(n * sizeof(double *));

    for (int i = 0; i < n; ++i) {
        mat[i] = (double *) malloc((n + 1) * sizeof(double));
    }
    double **matA;
    matA = (double **) malloc(n * sizeof(double *));

    for (int i = 0; i < n; ++i) {
        matA[i] = (double *) malloc((n + 1) * sizeof(double));
    }
    for (int i = 0; i <n ; ++i) {
    for (int j = 0; j < n+1; ++j) {
           mat[i][j]=0.0;
    }
    }
    /*for (int i = 0; i <n ; ++i) {
    for (int j = 0; j < n+1; ++j) {
           printf(" %.1f", mat[i][j]);
    }
    printf("\n");
    }*/
    //printf("job is done");
 FILE *fApu;
    fApu = fopen(
            "maze4.txt",
            "r");
    char linea[TAM];
    char *token;
    char a[30] = "";
    int retPositivo = 0;
    int retNegativo = 0;
    int pru=0;
    double resis;

    while (!feof(fApu)) {
        fgets(linea, TAM, fApu);
        linea[strcspn(linea, "\n")] = 0;
        //Corroborar leida exitosa
        /*puts(linea);*/
        token = strtok(linea, " ");
        strcpy(a, token);
        if (a[0] == 'I') {
            token = strtok(NULL, " ");
            retPositivo = atoi(token);
            token = strtok(NULL, " ");
            retNegativo = atoi(token);
            token = strtok(NULL, " ");
            resis = atof(token);
            if(retPositivo!=0){
                mat[retPositivo-1][n]+=resis;
            }
            if(retNegativo!=0){
                mat[retNegativo-1][n]-=resis;
            }
        } else if (a[0] == 'R') {
            token = strtok(NULL, " ");
            retPositivo = atoi(token);
            token = strtok(NULL, " ");
            retNegativo = atoi(token);
            token = strtok(NULL, " ");
            resis = atof(token);
            if(retPositivo!=0){
                mat[retPositivo-1][retPositivo-1]+=(1/resis);
            }
            if(retNegativo!=0){
                mat[retNegativo-1][retNegativo-1]+=(1/resis);
            }
            if(retNegativo!=0 && retPositivo!=0)
            {
               mat[retNegativo-1][retPositivo-1]-=(1/resis);
               mat[retPositivo-1][retNegativo-1]-=(1/resis);
            }

        } else {}
       // printf("%d", n);
    }
    fclose(fApu);

// metodo de soluci�n matricial
start = clock();
    register int jj, ii, diagonal;
    double temporal;
    double incog[n];

   for( diagonal = 0; diagonal < n - 1; diagonal++ )
    for( ii = diagonal + 1; ii < n; ii++ ) {
        temporal = mat[ii][diagonal] / mat[diagonal][diagonal];
        for( jj = diagonal; jj < n+1; jj++ )
            mat[ii][jj] = mat[ii][jj] - temporal * mat[diagonal][jj];
    }
    /*for( ii = n - 1; ii >= 0; ii-- ) {
    temporal = mat[ii][n+1];
    for( jj = ii + 1; jj < n + 1; jj++ )
        temporal = temporal - mat[ii][jj] * mat[jj][n+1];
    mat[ii][n+1] = temporal / mat[ii][ii];
}*/

   /** printf("\n\n  Tu matriz seria la siguiente:  \n\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n+1;j++)
        {
            printf("  %f  ", mat[i][j]);
        }
        printf("\n");
    }
     printf("\n\n\n\n\n");**/
     /*for (int i = 0; i <n ; ++i) {
        for (int j = 0; j < n+1; ++j) {
            printf(" %f", mat[i][j]);
        }
    printf("\n");
    }*/
    int k=1;
    int x=0;
    double aux0, aux1, aux2, ayuda;

    for(int i=n-1;i>=0;i--)
    {
        aux0 = mat[i][i];
        aux1 = mat[i][i+k];
        if(k==1)
        {
            aux2 = aux1/aux0;
          //  printf("%f,%f.%f \n",aux1,aux0,aux2);
            incog[x] = aux2;
            for(int j=n-1;j>=0;j--)
            {
                ayuda = mat[j][n-k];
                ayuda = ayuda*aux2;
                mat[j][n-k] = ayuda;
            }
            k++;
            x++;
        }
        else
        {
            for(int y=i+1;y<n;y++)
            {
                ayuda = mat[i][y];
                aux1 = aux1-ayuda;
            }
            aux2 = aux1/aux0;
           // printf("%f,%f.%f \n",aux1,aux0,aux2);
            incog[x] = aux2;
            for(int j=i;j>=0;j--)
            {
                ayuda = mat[j][n-k];
                ayuda = ayuda*aux2;
                mat[j][n-k] = ayuda;
            }
            k++;
            x++;
        }
    }
    end = clock();
    printf("\n  Tus incognitas son:  ");
    for(int i=0;i<n;i++)
    {
        printf("\n  Incognita numero %d=  %f\n\n", i+1, incog[i]);
    }
    cpu_time_used = ((long double) (end - start)) / CLOCKS_PER_SEC;
    printf("el tiempo en segundos fue: %.25Lf",cpu_time_used);
    return 0;
}
