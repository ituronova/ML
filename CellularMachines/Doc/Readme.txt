Soubor:  readme.txt
Datum:   12.4.2014
Autor:   Lenka Turo�ova, xturon02@stud.fit.vutbr.cz
Projekt: Projekt, predmet BIN
--------------------------------------------------------
Popis
C�lem projektu bylo navrhnout p�echodov� pravidla pro 
celul�rn� automat (1D �i 2D, bin�rn� �i v�cestavov�) 
jeho� v�voj bude vykazovat ur�it� zaj�mav� netrivi�ln� 
emergentn� chov�n� (nap�. realizace v�po�tu, nov� zp�sob 
replikace struktury/smy�ky, samoorganizace...). 

Program je implementov�n v jazyce C. K jeho spu�t�n� 
nejsou pot�eba ��dn� p��davn� knihovny, v�e se nach�z�
v souboru main.c, kter� je pot�eba pouze pomoc� skriptu
Makefile p�elo�it.


Popis paremetru
--------------------------------------------------------
Program lze spustit pomoci tohoto prikazu:
./main 
--------------------------------------------------------

Pot�ebn� parametry lze nastavit p��mo v �vodn� ��sti
programu:

  Parametr             N�zev                   Default 
--------------------------------------------------------
POPSIZE           po�et jedinc�                  8           
GENERATIONS		  po�et generac�                1000
PMUT		      pravd�podobnost mutace         50
MUTAGENES		  po�et zmutovan�ch ��sel        8
PCROSS            pravd�podobnost k��en�        50
STEPS             po�et simul. krok� CA          16
REPLICS           min. po�adovan�ch replik       1
CAINIT            inicializa�n� stav CA          -
--------------------------------------------------------

Jsou k dispozici nasledujici soubory:
main.c               vlastni program
readme.txt           kratky popis programu spolecne s parametry
Presentation.pdf     prezentace
Makefile             makefile