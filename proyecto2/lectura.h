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

/********************************* lectura.h  *********************************/
/*                                                                            */
/*   Purpose: Archivo que permite la lectura y determina el nodo maximo       */
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
#ifndef LECTURA_H
#define LECTURA_H
/**************************** Symbolic  Constants *****************************/

/* ---------------------- Predefined Sizes of Strings ------------------------*/

#define TAM 60

/* --------------------- Predefined Sizes of Matrices ----------------------- */

/************************** Prototypes of Functions ***************************/

/* ---------------------------- Public Functions ---------------------------- */

/*FN****************************************************************************
*
*   void lectura(char[60] arch,char[] del)
*
*   Purpose: Leer el maze para poder extraer los datos de la netlist
*
*   Return:  la cantidad de nodos (n)
*
*   Register of Revisions (16 Mayo 2021):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May --/21  -----------  16 Mayo 2021
*
*******************************************************************************/
int lectura(char arch[60],char del[] ) {
    FILE *fApu;
    fApu = fopen(arch, "r");//apertura del archivo
    char linea[TAM];//Tamaño de la linea
    char *token;//Creación del token
    long ret;//Crear variable ret 
    long ret1;//Crear variable ret1 
    int n = -1;//Creación de la variable n
    while (!feof(fApu)) {//ciclo que perdura hasta le final del archivo
        fgets(linea, TAM, fApu);//obtener la linea a leer
        linea[strcspn(linea,"\n")] = 0;//obtener limite de la linea
        token = strtok(linea,del);//printf(token);
        token = strtok(NULL,del);//cambiar hasta el valor de los nodo
        ret = atoi(token);//almacenar el valor
        if (ret > n) {//condición que busca el valor maximo
            n = ret;//asignación del valor maximo
        }
	token = strtok(NULL,del);//cambiar hasta el valor del segundo nodo
	ret1 = atoi(token);//almacenar el valor
	if (ret1 > n) {//condición que busca el valor maximo en el segundo nodo
            n = ret1;//asignación del valor maximo para el segundo nodo
        }
	
    }
    fclose(fApu);//Cierre del archivo
    return n;//retornar el valor maximo
}/*lectura*/

#endif /*LECTURA_H*/ 