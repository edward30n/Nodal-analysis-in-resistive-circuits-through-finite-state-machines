
/* Ruler 1         2         3         4         5         6         7        */

/******************************************************************************/
/*                                                                            */
/*                _____   _____    _____       _                              */
/*               |  __ \ / ____|  / ____|     | |                             */
/*               | |  | | |      | (___   ___ | |_   _____ _ __               */
/*               | |  | | |       \___ \ / _ \| \ \ / / _ \ '__|              */
/*               | |__| | |____   ____) | (_) | |\ V /  __/ |                 */
/*               |_____/ \_____| |_____/ \___/|_| \_/ \___|_|   (C)           */
/*                                                                            */
/*    Written in 2021 by Camilo Ramirez, <camilo_ramirez@javeriana.edu.co>    */
/*                       Edward Duarte, <edwardduarte@javeriana.edu.co>       */
/*                       David Orozco, <davidorozco@javeriana.edu.co>         */
/*                       Nicolas Pedraza <pedraza_n@javeriana.edu.co>         */
/*                                                                            */
/*                                                                            */
/* Letters created with "Big" font using http://www.network-science.de/ascii/ */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*    DC Solver provides a minimalistic simulator using nodal formulation.    */
/*                                                                            */
/*    Copyright (C) 2021 Camilo Ramirez                                       */
/*                       Edward Duarte                                        */
/*                       David Orozco                                         */
/*                       Nicolas Pedraza                                      */
/*                                                                            */
/*    This file is part of DC Solver.                                         */
/*                                                                            */
/*    DC Solver is free software: you can redistribute it and/or modify       */
/*    it under the terms of the GNU General Public License as published by    */
/*    the Free Software Foundation, either version 3 of the License, or       */
/*    (at your option) any later version.                                     */
/*                                                                            */
/*    DC Solver is distributed in the hope that it will be useful,            */
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
/*    GNU General Public License for more details.                            */
/*                                                                            */
/*    You should have received a copy of the GNU General Public License       */
/*    along with DC Solver.  If not, see <http://www.gnu.org/licenses/>.      */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
/* ------------------------ Inclusion of Own Headers ------------------------ */

#include "lectura.h"
#include "iSource.h"
#include "resistor.h"
#include "resistIsour.h"
#include "estadosFinitos.h"

/************************** Prototypes of Functions ***************************/

/* ---------------------------- Public Functions ---------------------------- */

/******************************* Main Function ********************************/

/*FN****************************************************************************
*
*   Purpose: Simulate DC circuits using the nodal matrix formulation
*
*   Plan:
*           Part 1: Handle arguments in command line
*           Part 2: Read file and prepare netlist array
*           Part 3: Print netlist from data in array to verify
*           Part 4: Prepare matrix with elements from netlist array
*           Part 5: Solve the matrix
*           Part 6: Deliver results to user
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
/*   May 16/21  C.Ramirez                                                     */
/*              E.Duarte                                                      */
/*              D.Orozco                                                      */
/*              N.Pedraza                                                     */
/*              J.Girarldo   Initial implementation                           */
/*                                                                            */
/******************************************************************************/

 int main(int argc, char *argv[]) {
    system("color F0"); // Cambio del color en la Consola de comandos.
    char del[] = " "; char arch[60];
    printf("Escriba el nombre del archivo con su respectiva extension\n");
    //Imprime las instrucicones al usuario
    scanf("%s",arch); //Lee el archivo que se ingresa por consola de comandos
    clock_t start, end;//Reloj para contabilizar el tiempo
    FILE *fApu = fopen(arch, "r");//apertura del archivo
    double cpu_time_used;//variable donde se almacena el tiempo
    int n;//varaiable donde se almacena el maximo valor de los nodos
    char linea[TAM];//variable char donde se almacena la linea
    char *token;//crear apuntador token
    char a[60] = "";//char que almacena las lineas
    int retPositivo = 0;//variable donde se almacena el nodo positivo
    int retNegativo = 0;//variable donde se almacena el nodo negativo
    double resis;//variable donde se almacena el valor de la resistencia o fuente de
    //corriente
    n = lectura(arch,del);//se le asigna el valor resultante de la función lectura
    double **mat = (double **) malloc(n * sizeof(double *));//se da memoria a la variable
    for (int i = 0; i < n; ++i) mat[i] = (double *) malloc((n + 1) * sizeof(double));
    //se crea la matriz mediante memoria dinamica
    double *result = (double *) malloc(n * sizeof(double));
    //double result[4];
    while (!feof(fApu)) {//ciclo que dura hasta el final del archivo
        resistIsour(&fApu, linea, a, &token, &retPositivo, &retNegativo, &resis, mat,&n,del);
        //se llama la función resisIsour
    }
    fclose(fApu);//se cierra el documento
    //system("cls");//Limpia la consola de comandos
    printf("\nCalculando");Sleep(500);printf(".");Sleep (500);
    printf(".");Sleep (500);printf(".\n");
    start = clock();//se inicializa el cronometro
    estadosFinitos(&n,mat,result);//se llama la función estadosFinitos
    end = clock();//se finaliza la muestra de tiempo
    free(mat);//se libera la memoria
    printf("Tus incognitas son: \n");//Impresión de los resultados
    for (int i = 0; i < n; i++) {//For para recorrer el vector con los resultados
        printf(" Voltaje en el nodo %d= %fV\n", i + 1, result[i]);// Impresión de cada res.
    }
    cpu_time_used = ((long double) (end - start)) / CLOCKS_PER_SEC;//se calcula el tiempo
    printf("el tiempo en segundos fue: %.4Lf s \n", cpu_time_used);//se imprime el tiempo
    free(result);
    system("pause");//se pausa para observar el tiempo y los resultados
    return 0;
}/*main*/