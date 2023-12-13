/**
 * Soubor:  main.c
 * Datum:   12.4.2014
 * Autor:   Lenka Turonova, xturon02@stud.fit.vutbr.cz
 * Projekt: Projekt, predmet BIN
 * Popis:   Program implementuje CA, kteremu je jako
 *          vstup poskytnut iniciacni stav CA a
 *          pomoci genetickeho algoritmu se program
 *          snazi nalezt optimalni sadu pravidel,
 *          podle kterych je definovan nasledujici stav
 *          CA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <time.h>

//////////////////////////////////////////////////////////////
// VZOROVA IMPLEMENTACE JEDNODUCHEHO GENETICKEHO ALGORITMU  //
// JAZYK C, PREKLAD S OHLEDEM NA NORMU C99                  //
// (c) MICHAL BIDLO, 2011                                   //
// UVEDENY KOD SMI BYT POUZIT VYHRADNE PRO POTREBY PROJEKTU //
// V KURZU BIOLOGII INSPIROVANE POCITACE NA FIT VUT V BRNE  //
//////////////////////////////////////////////////////////////

#ifndef PARAMS_H
#define PARAMS_H

// pro vypis prubehu evoluce na stdout, jinak zakomentujte
#define DEBUG

//----------------------- parametry genetickeho algoritmu ----------------------
// velikost populace
#define POPSIZE 8
// maximalni pocet generaci
#define GENERATIONS 100
// pravdepodobnost mutace
#define PMUT 50
// pocet mutovanych genu v chromozomu
#define MUTAGENES 8
// pravdepodobnost krizeni
#define PCROSS 50
// pocet jedincu v turnajove selekce
#define TOUR 4
// delka chromozomu
#define CHLEN 20
// pocet pravidel
#define RULES 26
// rozmery matice
#define MATRIX 24
// pocet parametru
#define PARAM 18
// index pro next state
#define NS 18
// index pro fitness funkci
#define FF 19
// pocet kroku CA pro simulaci
#define STEPS 16
// minimalni pocet klonu struktury
#define REPLICS 1

// inicializacni stava CA

#define CAINIT  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

/*
#define CAINIT  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},\
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
*/
#endif

/** globalni promenne */
int CA[][MATRIX+2] = {CAINIT};  // CA s okraji
int CA_new[MATRIX+2][MATRIX+2];
int CA_old[MATRIX+2][MATRIX+2]; // pomocne CA
int pattern_h = 0;            // vyska vzoru
int pattern_w = 0;            // sirka vzoru
int pattern_s[2] = {24,24};   // pocatek vzoru
int pattern[MATRIX][MATRIX];  // ulozeny vzor
int population[POPSIZE*RULES*CHLEN]; // populace
int population_new[POPSIZE*RULES*CHLEN]; // nova populace
int best[RULES*CHLEN];       // nejlepsi jedinec
int best_ever = 0;            // nejlepsi FF
int max_replicated = 1;       // pozadovany pocet replik
int replicated = 0;           // pocet replik
int best_replicated = 0;      // nejvetsi pocet replik
int generation = 0;           // pocet generaci
int unit = 100;               // mez pro generovani cisla
int inv1[RULES*CHLEN];        // vybrani jedinci
int inv2[RULES*CHLEN];
int run = 0;                  // aktualni beh GA
int results[4];               // vysledky
int runs = 100;               // pocet behu GA

/**
 * Generuje cele cislo v rozsahu low-high vcetne
 */
int urandom(int low, int high)
{
    time_t timer;
    struct tm y2k;
    int seconds;

    y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
    y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

    time(&timer);

    seconds = difftime(timer,mktime(&y2k));
    return (((abs(rand()+seconds)) % (high - low + 1)) + low);
}

/**
 * Inicializace CA
 */
 void initCA()
 {
   int i = 0;
   int j = 0;

   for(i=0;i<=MATRIX+1;i++)
   {
      for(j=0;j<=MATRIX+1;j++)
      {
        CA[i][j] = 0;
      }
   }
 }

/**
 * Vykresleni CA
 */
 void printCA()
 {
    int i=0;
    int j=0;
    for(i=1;i<=MATRIX;i++) // kazdy radek
    {
      printf("|");
      for(j=1;j<=MATRIX;j++) // kazdy sloupec
        printf("%d|", CA[i][j]);
      printf("\n");
    }
 }

/**
 * Vykresleni CA_old
 */
 void printCA_old()
 {
    int i=0;
    int j=0;
    for(i=1;i<=MATRIX;i++) // kazdy radek
    {
      printf("|");
      for(j=1;j<=MATRIX;j++) // kazdy sloupec
        printf("%d|", CA_old[i][j]);
      printf("\n");
    }
 }

 /**
 * Vykresleni CA_new
 */
 void printCA_new()
 {
    int i=0;
    int j=0;
    for(i=1;i<=MATRIX;i++) // kazdy radek
    {
      printf("|");
      for(j=1;j<=MATRIX;j++) // kazdy sloupec
        printf("%d|", CA_new[i][j]);
      printf("\n");
    }
 }

/**
 * Vypis populace
 */
void printPopulation()
{
  int i = 1;
  for(i=1;i<=POPSIZE*RULES*CHLEN;i++)
  {
    printf("%d ", population[i]);
    if(i%(CHLEN)== 0)
      printf("\n");
    if(i%(CHLEN*RULES)== 0)
      printf("\n");
  }
  printf("\n\n");
}

/**
 * Vypis jedince
 */
void printBest()
{
  int i,j = 0;
  printf("\n--------- Nejlepsi jedinec -----------\n\n");
  for(i=1;i<=RULES*CHLEN;i++)
  {
    if(i%(CHLEN)== 0)
      printf("\n");
    else if(i%(CHLEN*RULES)== 0)
      printf("\n");
    else
      printf("%d ", best[i]);
  }
  printf("\n--------------------------------------\n");
}

/**
 * Inicializace vzoru
 */
void findPattern()
{
  int i,j=0;

  // zjisteni velikost vzoru
  for(i=1;i<=MATRIX;i++)
  {
     for(j=1;j<=MATRIX;j++)
     {
       if(CA[i][j] == 1)
       {
          if(pattern_w < j)
            pattern_w = j; // sirka
          if(pattern_h < i)
            pattern_h = i; // vyska
          if(pattern_s[0] > i)
            pattern_s[0] = i; // pocatecni radek vzoru
          if(pattern_s[1] > j)
            pattern_s[1] = j; // pocatecni sloupec vzoru
       }
     }
  }
  // ulozeni vzoru do samostatne struktury
  for(i=pattern_s[0];i<=pattern_h+2;i++)
  {
     for(j=pattern_s[1];j<=pattern_w+2;j++)
     {
        if(i == 0 || j == 0 || i == pattern_h+2 || j == pattern_w+2)
          pattern[i-pattern_s[0]][j-pattern_s[1]] = 0;
        else
          pattern[i-pattern_s[0]+1][j-pattern_s[1]+1] = CA[i][j];
     }
  }
  // prepocet vysky a sirky vzoru
  pattern_h -= pattern_s[0]-3;
  pattern_w -= pattern_s[1]-3;
}

/**
 * Inicializace pocatecni populace
 */
void initPopulation()
{
  int i,j,k = 0;
  for(i=1;i<=POPSIZE*RULES*CHLEN;i++)
  {
    if(i%2 == 0)
       population[i] = urandom(0,4);
    else
       population[i] = urandom(0,1);
  }
  for(i= 0;i<POPSIZE;i++)
  {  // fitness funkce
    population[i*RULES*CHLEN+CHLEN] = 0;
  }
}

/**
 * Zastaveni GA
 */
int stop()
{
    int countRep = (best_replicated-1 < 0?0:best_replicated-1);
    if(best[CHLEN] > best_ever)
    {
      best_ever = best[CHLEN];
    }
    if (best_replicated > max_replicated || generation == GENERATIONS)
    {
      printf("\n--------------------------------------"
			 "\n------------- Vyhodnoceni  -----------\n"
			 "                %d.behu "
			 "\n--------------------------------------\n"
			, run+1);
      if (best_replicated > max_replicated)
      {
          printf(" USPECH  "
                 "\n--------------------------------------\n"
                 " Generace     |  %d \n"
                 " Fitness      |  %d \n"
                 " Pocet replik |  %d "
                 "\n--------------------------------------\n",
                 generation, best_ever, countRep);
          printBest();
      }
      else printf(" NEUSPECH  "
                 "\n--------------------------------------\n"
                 " Generace     |  %d \n"
                 " Fitness      |  %d \n"
                 " Pocet replik |  %d "
                 "\n--------------------------------------\n"
                 " Pozadovanych |  %d "
                 "\n--------------------------------------\n",
                 generation, best_ever, countRep, max_replicated);
          printf(" Jedincu      |  %d\n"
                 " Generaci     |  %d\n"
                 " Pocet mutaci |  %d\n"
                 " Kroku        |  %d\n"
                 " Krizeni      |  %d\%\n"
				 " Mutace       |  %d\%\n",
                 POPSIZE, GENERATIONS, MUTAGENES, STEPS, PCROSS, PMUT);
      return 1;
    }
    return 0;
}

/**
 * Zkopirovani CA do CA_new
 */
void copyCA()
{
  int i,j=0;
  for(i=0;i<MATRIX+2;i++)
  {
    for(j=0;j<MATRIX+2;j++)
    {
      CA_old[i][j] = CA[i][j];
    }
  }
}

/**
 * Zkopirovani CA_new do CA_old
 */
void copyCA_new()
{
  int i,j=0;
  for(i=0;i<MATRIX+2;i++)
  {
    for(j=0;j<MATRIX+2;j++)
    {
      CA_old[i][j] = CA_new[i][j];
    }
  }
}

/**
 * Krok vypoctu pro jednu bunku
 * numInd       - cislo zkoumaneho jedince s pravidly
 * i, j         - radek a sloupec aktualni bunky CA
 * funkce vraci novy stav bunky
 */
int stepCA(int numInd, int i, int j)
{
  int p, c, d, k = 0;
  int ok = 1; // pravidlo splneno
  int neRow, neCol = 0;
  int index[9][2] = {{-1,-1},{-1,0},{-1,1}, // pole indexu sousedu
                     {0,-1}, {0,0}, {0,1},
                     {1,-1}, {1,0}, {1,1}};

  // jednotliva pravidla
  for(p = 0;p < RULES;p++)
  {
    ok = 1;
    for(k = 0; k < PARAM/2; k++)
    {
      neRow = i+index[k][0]; // radek souseda
      neCol = j+index[k][1]; // sloupec souseda
      // hodnota: population[numInd*RULES*CHLEN+p*CHLEN+2*k+1]
      // operace: population[numInd*RULES*CHLEN+p*CHLEN+2*k+2]
      if(numInd != -1)
      {
        c = population[numInd*RULES*CHLEN+p*CHLEN+2*k+2];
        d = population[numInd*RULES*CHLEN+p*CHLEN+2*k+1];
      }
      else
      {
        c = best[p*CHLEN+2*k+2];
        d = best[p*CHLEN+2*k+1];
      }
      switch(c)
      {
         case 0: // operace roven
          if(CA_old[neRow][neCol] != d)
            ok = 0;
          break;
         case 1: // operace neroven
          if(CA_old[neRow][neCol] == d)
            ok = 0;
          break;
         case 2: // operace mensi, roven
          if(CA_old[neRow][neCol] > d)
            ok = 0;
          break;
         case 3: // operace vetsi, roven
          if(CA_old[neRow][neCol] < d)
            ok = 0;
          break;
      }
      if(ok == 0) // nejaka podminka nebyla splnena
       break;
    }
    if(ok == 1) // okoli splnuje vsechny podminky
    {
      if(numInd != -1)
        return population[numInd*RULES*CHLEN+p*CHLEN+CHLEN-1]; // vrat next value
      else
        return best[p*CHLEN+CHLEN-1];
    }
  }
  // zadne pravidlo nevyhovuje
  return CA_old[i][j];
}

/**
 * Prevzata fitness funkce
 */
int fitnessFunction(int index, int printable)
{
  int fit = 0, best_fit = 0, best_repl = 0;
  int i,j,s,r,c,k,pc,pr;
  int _pfit = 0;

  copyCA(); // zkopirovani CA do pomocne promenne
  for (s = 0; s < STEPS; s++) // postupne simuluje CA_STEPS kroku CA
  {
      fit = 0; // fitness funkce inicializace
      replicated = 0; // pocet replikovanych vzoru inicializace

      // pro kazdou bunku vypocti novy stav
      for(i=1;i<=MATRIX;i++)
      {
        for(j=1;j<=MATRIX;j++)
        {
          CA_new[i][j] = stepCA(index, i, j); // spusteni CA pro 1 krok
        }
      }
      copyCA_new();
//******************************************************************************
      int pfit[REPLICS] = { 0 }; // ulozeni score  REPLICS nejlepsich replik
      for (r = 1; r <= MATRIX - pattern_h + 1; r++) // postupuje po celem CA az po
      {												       // nejzazsi bod, kde muze vzor v CA zacinat
          for (c = 1; c <= MATRIX - pattern_w + 1; c++)
          {
             _pfit = 0; // prubezne score kontrolovaneho pole
             for (pr = 0; pr < pattern_h; pr++) // postupne porovnavani celeho vzoru s akt. polem
                for (pc = 0; pc < pattern_w; pc++)
                    if (pattern[pr][pc] == -1 || CA_old[r+pr][c+pc] == pattern[pr][pc]) // porovnani
                        _pfit++; // navyseni score akt. pole
             for (k = 0; k < REPLICS; k++) // postupne ulozeni score REPLICS nejlepsich replik
             {
                if (_pfit > pfit[k]) // pokud je score vetsi nez ulozene
                {
                   for (j = REPLICS - 1; j > k; j--) // posunuti pole nejlepsich score
                      pfit[j] = pfit[j - 1];
                   pfit[k] = _pfit; // vlozeni lepsiho score
                }
             }
             if (_pfit == pattern_w * pattern_h) // pokud se nalezl vzor, zvysi se hodnota citace
             {
               replicated++;
             }
          }
      }
      for (k = 0; k < REPLICS; k++) // ff podle poctu replik
          fit += pfit[k];
      fit += replicated * pattern_w * pattern_h; // pridani score castecnych replik

//******************************************************************************
      if (fit > best_fit)
      {
         best_fit = fit;
         best_repl = replicated;
      }
    }
    replicated = best_repl; // pocet replik
    return best_fit;
}

/**
 * Mutace populace (krome prvniho/nejlepsiho)
 */
void mutation()
{
    int i = 1;
    if (urandom(0, unit) <= PMUT)  // mutace s pravdepodobnosti PMUT
    {
      for (i = 0; i < MUTAGENES; i++)
      {
          int g1 = urandom(0, RULES-1);
          int g2 = urandom(1, CHLEN-1);
          int g3 = urandom(0, RULES-1);
          int g4 = urandom(1, CHLEN-1);
          if((RULES*CHLEN+g1*CHLEN+g2)%2 == 0)
             inv1[g1*CHLEN+g2] = urandom(0,4);
          else
             inv1[g1*CHLEN+g2] = urandom(0,1);

          if((RULES*CHLEN+g3*CHLEN+g4)%2 == 0)
             inv1[g3*CHLEN+g4] = urandom(0,4);
          else
             inv1[g3*CHLEN+g4] = urandom(0,1);
      }
    }
}

/**
 * Krizeni
 */
void crossover()
{
    // zde standardni jednobodove krizeni
    int cpoint = urandom(2, RULES*CHLEN - 1);
    int inv3[RULES*CHLEN];
    int i = 0;

    for(i=1;i<=cpoint;i++)
    {
        inv3[i] = inv1[i];
        inv1[i] = inv2[i];
        inv2[i] = inv3[i];
    }
}

/**
 * Spusteni genetickeho algoritmu
 */
int GA_algorithm()
{
    int i,j,t = 0,k = 0;
    generation = 0;     // pocet generaci
    int _tour = TOUR;  // zaklad turnaje
    for(i=1;i<=RULES*CHLEN;i++) // inicializace nejlepsiho jedince
    {
      best[i] = 0;
    }
    initPopulation();      // inicializace populace

    do
    {
      generation++;
      // vypocet fitness funkce pro kazdeho jedince
      for(i=0;i<POPSIZE;i++)
      {
        population[i*RULES*CHLEN+CHLEN] = fitnessFunction(i, 0);  // vypocet FF

        if (population[i*RULES*CHLEN+CHLEN] >= best[CHLEN])      // vyber nejlepsiho
        {
            for(j=1;j<=RULES*CHLEN;j++)
            {
               best[j] = population[i*RULES*CHLEN+j]; // nejlepsi FF
               best_replicated = replicated;          // pocet replik
            }
        }
      }
      /** tvorba nove populace */
      for (i = 0; i < POPSIZE; i += 2)
      {
        int ind1 = -1;
        int ind2 = -1;
        // turnajovy vyber jedincu
        for (t = 0; t < _tour; t++)
        {
          int i1 = urandom(0, POPSIZE - 1);
          if(ind1 == -1) ind1 = i1;
          else if(ind2 == -1) ind2 = i1;
          else if(population[i1*RULES*CHLEN+CHLEN] > population[ind1*RULES*CHLEN+CHLEN])
            ind1 = i1;
          else if(population[i1*RULES*CHLEN+CHLEN] > population[ind2*RULES*CHLEN+CHLEN])
            ind2 = i1;
        }
        // prekopirovani dvou vybranych jedincu do pomocnych
        for(j=1;j<=RULES*CHLEN;j++)
        {
          inv1[j] = population[ind1*RULES*CHLEN+j];
          inv2[j] = population[ind2*RULES*CHLEN+j];
        }
        /** krizeni */
        if (urandom(0, unit) < PCROSS)
        {
          crossover();
        }
        /** mutace */
        mutation();
        k = 1;
        for(j=1;j<=RULES*CHLEN;j++)
        {
          population_new[i*RULES*CHLEN+k] = inv1[j];
          population_new[i*RULES*CHLEN+k+RULES*CHLEN] = inv2[j];
          k++;
        }
      }
      // prekopirovani nove populace do stare
      for(i=1;i<=POPSIZE*RULES*CHLEN;i++)
      {
        population[i] = population_new[i];
      }
    }
    while(!stop());
    //printPopulation();
    if (best_replicated > max_replicated)
      return 1;
    else
      return 0;
}

/**
 * Hlavni funkce
 */
int main(int argc, char *argv[])
{
  int i=0;
  int suc = 0;
  int countSuccess = 0;
  for(i=0;i<4;i++)
    results[i] = 0;
  for(run=0;run< runs;run++) // 100 nezavislych behu
  {
    best_ever = 0;
    replicated = 0;
    best_replicated = 0;
    generation = 0;

    findPattern();   // nacteni vzoru z CA
    suc = GA_algorithm();  // geneticky algoritmus
    countSuccess += suc;
    results[0] = RULES;
    results[1] = countSuccess;
    if(suc == 1)
    {
      results[2] += 1;
      results[3] += generation + 1;
    }
  }
  printf("\n--------------------------------------\n");
  printf("\n--------------------------------------\n\n");
  printf("  Úspìšný bìhù             | %d/100 \n", results[2]);
  if(results[2] != 0 )
    printf("  Prùmìrný poèet generací | %d \n", results[3]/results[2]);
  printf("  Prùmìrný poèet generací | nedef. \n");
  printf("\n--------------------------------------\n");
  printf("\n--------------------------------------\n");
  return 0;
}
