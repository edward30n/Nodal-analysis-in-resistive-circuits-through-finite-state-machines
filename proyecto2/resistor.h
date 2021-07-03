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

/****************************** resistor.h  ***********************************/
/*                                                                            */
/*   Purpose: Archivo que permite el procesamiento de las resistencias        */
/*                                                                            */
/*   Origin:  Modulo diseñado, testado e implementado por                     */
/*                        Camilo Ramírez                                      */
/*                        Edward Duarte                                       */
/*                        David Orozco                                        */
/*                        Nicolas Pedraza                                     */
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
/*              N.Pedraza   Initial implementation                            */
/*                                                                            */
/******************************************************************************/
#ifndef RESISTOR
#define RESISTOR
/* ---------------------- Predefined Sizes of Strings ------------------------ */

/* --------------------- Predefined Sizes of Matrices ----------------------- */

/************************** Prototypes of Functions ***************************/

/* ---------------------------- Public Functions ---------------------------- */

/*FN****************************************************************************
*
*   void resistor(char **token, 
*             int *retPositivo,
*             int *retNegativo, 
*             double *resis, 
*             double **mat,
*	      char del[])
*
*   Purpose: Llenar la matriz cuando detecta una resistencia
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
void resistor(char **token, 
             int *retPositivo,
             int *retNegativo, 
             double *resis, 
             double **mat,
	     char del[]) {

    *token = strtok(NULL, del);// leer el primer nodo
    *retPositivo = atoi(*token);//asignar el primer nodo
    *token = strtok(NULL, del);// leer el segundo nodo
    *retNegativo = atoi(*token);// asignar el segundo nodo
    *token = strtok(NULL, del);// leer el valor de la resistencia
    *resis = atof(*token);// asignar el valor de la resistencia
    if (*retPositivo != 0) {//condición para determinar si es tierra
        mat[*retPositivo - 1][*retPositivo - 1] += (1 / *resis);
        //asignar el valor a la diagonal
    }
    if (*retNegativo != 0) {//condición para determinar si es tierra
        mat[*retNegativo - 1][*retNegativo - 1] += (1 / *resis);
        //asignar el valor a la diagonal
    }
    if (*retNegativo != 0 && *retPositivo != 0) {
        //condición para determinar si es tierra
	mat[*retNegativo - 1][*retPositivo - 1] -= (1 / *resis);
        mat[*retPositivo - 1][*retNegativo - 1] -= (1 / *resis);
        //asignar el valor a las otras partes del nodo
    }
}/*resistor*/

#endif/*RESISTOR*/