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
/*                       Juan-Carlos Giraldo <jcgiraldo@javeriana.edu.co>     */
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
/*                        Juan Carlos Giraldo                                 */
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

/*********************************  estadosFinitos.h **************************/
/*                                                                            */
/*   Purpose:Archivo que permite el procesamiento de las fuentes de corriente */
/*                                                                            */
/*   Origin:  Modulo diseñado, testado e implementado por                     */
/*                        Camilo Ramírez                                      */
/*                        Edward Duarte                                       */
/*                        David Orozco                                        */
/*                        Nicolas Pedraza                                     */
/*                        Juan Carlos Giraldo                                 */
/*                                                                            */
/*   Notes:   None                                                            */
/*                                                                            */
/*   Register of Revisions (Debugging Process):                               */
/*                                                                            */
/*   DATE       RESPONSIBLE  COMMENT                                          */
/*   -----------------------------------------------------------------------  */
/*   May 16/21  C.Ramirez                                                     */
/*              E.Duarte                                                      */
/*              D.Orozco                                                      */
/*              N.Pedraza                                                     */
/*              J.Girarldo   Initial implementation                           */
/*                                                                            */
/******************************************************************************/

#ifndef ESTADOSFINITOS
#define ESTADOSFINITOS

/**************************** Symbolic  Constants *****************************/

/* --------------------- Predefined structure ------------------------------- */

typedef enum {
    caso1, caso2, caso3, caso4, caso5, caso6, caso7
} solucionEstado;

/************************** Prototypes of Functions ***************************/

/* ---------------------------- Public Functions ---------------------------- */

/*FN****************************************************************************
*
*   void estadosFinitos(int* n,
*                       double **mat,double* result);
*
*   Purpose: Solucionar el sistema de eucaciones lineales de la matriz
*            mediante maquinas de estados finitos
*
*   Return:  Null
*
*   Register of Revisions (16 Mayo 2021):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May --/21  -----------  16 Mayo 2021
*
*******************************************************************************/

void estadosFinitos(int* n,
                    double **mat,double*result)
{
    solucionEstado estado = caso1;//inicializar la estructura en el caso 1
    register int jj=0, ii=0, diagonal=0;//variables para recorrer la matriz
    double temporal;//variable temporal
    int k = 1;
    int x=0;
    int y = 0;//variables para recorrer la matriz
    double aux0=0, aux1=0, aux2=0, ayuda=0;//variables auxiliares
    int finish = 0;//variable que determina el fin del ciclo
    while (finish == 0) {//comienzo del ciclo
        switch (estado) {
            /*Realización de gauss - Codigo creado por Juan Carlos Giraldo*/
            case caso1:
                diagonal = 0;//inicializar variable
                estado = caso2;
                break;
            case caso2:
                if (diagonal < *n - 1) {//condición que comprueba la diagonal
                    ii = diagonal + 1;//incluir condición inicial
                    estado = caso3;
                } else {
                    ii = *n - 1;//incluir condición inicial
                    estado = caso5;
		}break;
            case caso3:
                if (ii < *n) {//condición que comprueba las filas 
                    temporal = mat[ii][diagonal] / mat[diagonal][diagonal];
                    //asignación de la variable temporal
                    jj = diagonal;//incluir condición inicial
                    estado = caso4;
                } else {
                    diagonal++;//añadir a una variable contador
                    estado = caso2;
                }
                break;
            case caso4:
                if (jj < *n + 1) {//condición que comprueba las columnas
                    mat[ii][jj] = mat[ii][jj] - temporal * mat[diagonal][jj];
                    //remplazo de la matriz
                    jj++;//añadir a una variable contador
                    estado = caso4;
                } else {
                    ii++;//añadir a una variable contador
                    estado = caso3;
                }
                break;
            /*Realización del back-sustitution*/
            case caso5:
                if (ii >= 0) {//condición que mira las filas
                    aux0 = mat[ii][ii];//asignación de la variable auxiliar 0
                    aux1 = mat[ii][ii + k];//asignación de la variable auxiliar 1
                    if (k == 1) {//condición para operar los auxiliares
                        aux2 = aux1 / aux0;//asignación de la variable auxiliar 2
                        result[x]=aux2;//asignación del arreglo del resultado
                        jj = *n - 1;//incluir condición inicial
                        estado = caso6;
                    } else {
                        y = ii + 1;//incluir condición inicial
                        estado = caso7;
                    }
                } else {
                    finish = 1;//terminar ciclo
                }
                break;
            case caso6:
                if (jj >= 0) {//condición que mira las columnas
                    ayuda = (mat[jj][*n - k] * aux2);//asignar la variable ayuda
                    mat[jj][*n - k] = ayuda;//cambiar el valor de la matriz
                    jj--;//quitar a variable contador
                    estado = caso6;
                } else {
                    k++;//añadir a variable contador
                    x++;//añadir a variable contador
                    ii--;//quitar a variable contador
                    estado = caso5;
                }
                break;
            case caso7:
                if (y < *n) {//condición para operar auxilixares
                    ayuda = mat[ii][y];//asignar la variable ayuda
                    aux1 -= ayuda;//asignar la variable auxiliar 1
                    y++;//añadir a variable contador
                    estado = caso7;
                } else {
                    aux2 = aux1 / aux0;//asignar la variable auxiliar 2
		            result[x]=aux2;//asignación del arreglo del resultado
                    jj = ii;//incluir condición inicial
                    estado = caso6;
                }
                break;
        }
    }
}/*estadosFinitos*/

#endif/*ESTADOSFINITOS*/