# Nodal-analysis-in-resistive-circuits-through-finite-state-machines

Purpose:

  *The purpose of this project was to solve any circuit by means of a nodal analysis programmed in C, so that the value of the voltage found in each node is returned. The basis of the program consists of receiving the netlist and by means of the programming carried out to return the result of the voltage in the node through the gauss and Back Substitution process, this process is carried out by means of dynamic memory.
   For the solution of the netlist, it is analyzed if it is current or resistance respectively in order to place it in the matrix, after this the input and output nodes are analyzed in order to locate on the diagonal those nodes where it belongs with its positive inverse value In the same way, its negative inverse value is located in those nodes where it is present and if it is not found, it takes the value of 0.
   With this matrix obtained, the Gaussian elimination and the Back Substitution carried out by finite states continue to be realized by which the value of the voltage at the node and the time it takes to run the program are returned.

Files: You will find 3 files.


    a) proyecto2: This file has 17 files. Some of them are .h, others .txt, 1 is a read me in spanish, and the last one is the main code "electricalMaze.c".
        * The .txt named as maze are the files wich has the information of a netlist, some are bigger than others. If you have your own netlist you will have to remember that this code is made to work only with resistors and current sources. The resistors have to start with a R  an the current sorces has to start with an I. the second column has the number of the node on the positive terminal and the third one has the negative terminal of the object of the line. Finallt, the last column has the value of the resistence or  current involved.
        * The .h files are libraries made by my group and I to simplyfy the main code, each one of them are correcly commented for a better understanding.
        * The electricalMaze.c is the main code witch all the libraries are called and used. if you want to try and see how long it takes your pc to process the bigger maze files you can follow this steps:
            1) Have the gcc installed on your computer.
            2) Using the command console, enter the path of the files inside the "project2" folder.
            3) Paste in the console the following command: "gcc -Ofast electricalMaze.c -o ejec.exe" or alternatively: "gcc electricalMaze.c -o ejec.exe"
            4) paste in the console the following command: "ejec.exe"
            5) When executing, the program will ask you for a file where the information is saved (netlist), there you can write any of the following examples that are in the project:
                  a) "maze.txt"
                  b) "maze1.txt"
                  c) "maze2.txt"
                  d) "maze3.txt"
                  e) "maze4.txt"
                  f) "maze5.txt"
                  g) "maze6.txt"
                  h) "maze7.txt"
                  i) "maze8.txt"
            6) Wait for the code to execute. Once finished, you will get the results of the voltage at each node, as well as the time it took for your computer to execute that code.
    b) proyecto2SinMaquina: this file contains a code with less organisation than the first one and also doesn't use a finite state machine. to run it you have to follow the same steps as the previous one.
  
    c) Informe.pdf: This file has the report of all the proyect (in spanish) with the next points:
        1)  Abstract
        2)  Introduction
        3)  Credits
        4)  General objectives
        5)  Specific objectives
        6)  Context
        7)  State of art
        8)  Theorical framework
        9)  Common errors
        10) Flowchart
        11) Description of the code
        12) Results
        13) Analysis
        14) Conclution
        15) References
This code was possible thanks to : Camilo Ramirez, David Orozco and Nicolas Pedraza. Their information will be in the report.
