-------------------------------------------------------------------------------
    Inteligencia Artificial CI-5437
    Proyecto 1
    Integrantes:
        * Chiseng Ng Yu               09-11245
        * María Lourdes Garcia Florez 10-10264
        * Carlos Ferreira             11-10323
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
    Instrucciones 
-------------------------------------------------------------------------------

--- Actividad 1 y 2 ---

    1) Ubicarse en la carpeta /Actividad1y2
    2) Se compila con los siguientes comandos:
        make 11puzzle.countNod
        make 24PancakePuzzle.countNod
        make 28PancakePuzzle.countNod
        make 22TopSpin.countNod
        make 26TopSpin.countNod
        make tower14_4.countNodHanoi
        make tower16_4.countNodHanoi
        NOTA: se debe cambiar --fwd_history_len por 1 y 2 respectivamente y volver a compilar para obtener los arboles con N = 1 y N = 2. Inicialmente se encuentra en N = 0.
    3) Se ejecutan de la siguiente manera:
        ./11puzzle.countNod 20 12
        ./24PancakePuzzle.countNod 6 24
        ./28PancakePuzzle.countNod 6 28
        ./22TopSpin.countNod 7 22
        ./26TopSpin.countNod 7 26
        ./tower14_4.countNodHanoi 12 4 14
        ./tower16_4.countNodHanoi 12 4 16

--- Actividad 3 ---

    1) Ubicarse en la carpeta /Actividad3
    2) Se compila con los siguientes comandos:
        make 11puzzle.dfid
        make pancake16.dfid
        make topSpin.dfid
        make tower14_4.dfid
    3) Se ejecutan de la siguiente manera:
        [lineaInicial] [lineaFinal] ./11puzzle.dfid [archivoEntrada] [archivoSalida] 
        [lineaInicial] [lineaFinal] ./pancake16.dfid [archivoEntrada] [archivoSalida] 
        [lineaInicial] [lineaFinal] ./topSpin.dfid [archivoEntrada] [archivoSalida] 
        [lineaInicial] [lineaFinal] ./tower14_4.dfid [archivoEntrada] [archivoSalida] 

--- Actividad 4 ---

    1) Ubicarse en la carpeta /Actividad4
    2) Se compila con los siguientes comandos:
        make [nombrePsvn].[programa en /global]
    3) Se ejecutan de la siguiente manera:
        [lineaInicial] [lineaFinal] ./[nombrePrograma] [archivoEntrada] [archivoSalida] [algoritmo] [heuristica]

    NOTA: Las corredas de A* dan  segmentation fault

Los resultados de las corridas de las actividade se encuentran en las carpetas correspondientes.

-------------------------------------------------------------------------------