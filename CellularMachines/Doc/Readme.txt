Soubor:  readme.txt
Datum:   12.4.2014
Autor:   Lenka Turoòova, xturon02@stud.fit.vutbr.cz
Projekt: Projekt, predmet BIN
--------------------------------------------------------
Popis
Cílem projektu bylo navrhnout pøechodová pravidla pro 
celulární automat (1D èi 2D, binární èi vícestavový) 
jehož vývoj bude vykazovat urèité zajímavé netriviální 
emergentní chování (napø. realizace výpoètu, nový zpùsob 
replikace struktury/smyèky, samoorganizace...). 

Program je implementován v jazyce C. K jeho spuštìní 
nejsou potøeba žádné pøídavné knihovny, vše se nachází
v souboru main.c, který je potøeba pouze pomocí skriptu
Makefile pøeložit.


Popis paremetru
--------------------------------------------------------
Program lze spustit pomoci tohoto prikazu:
./main 
--------------------------------------------------------

Potøebné parametry lze nastavit pøímo v úvodní èásti
programu:

  Parametr             Název                   Default 
--------------------------------------------------------
POPSIZE           poèet jedincù                  8           
GENERATIONS		  poèet generací                1000
PMUT		      pravdìpodobnost mutace         50
MUTAGENES		  poèet zmutovaných èísel        8
PCROSS            pravdìpodobnost køížení        50
STEPS             poèet simul. krokù CA          16
REPLICS           min. požadovaných replik       1
CAINIT            inicializaèní stav CA          -
--------------------------------------------------------

Jsou k dispozici nasledujici soubory:
main.c               vlastni program
readme.txt           kratky popis programu spolecne s parametry
Presentation.pdf     prezentace
Makefile             makefile