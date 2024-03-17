/*************************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
* Tekijä: Lassi Tuominen
* Opiskelijanumero: 001119893
* Päivämäärä: 10.3.2023
* Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat
* lähteet ja henkilöt, ja se näkyy tehtävässä seuraavalla tavalla: -
* Mahdollisen vilppiselvityksen varalta vakuutan, että olen tehnyt itse
* tämän tehtävän ja vain yllä mainitut henkilöt sekä lähteet ovat
* vaikuttaneet siihen yllä mainituilla tavoilla.
*/
/*************************************************************************/
/* Tehtävä HTPerus, tiedoston nimi HTPerusKirjasto.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HTPerusKirjasto.h"


int valikko(){
    int iValinta;
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Lue tiedosto\n");
    printf("2) Analysoi tiedot\n");
    printf("3) Kirjoita tulokset\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d",&iValinta);
    getchar();
    return(iValinta);
}

void tiedostoNimi(char *pTiedosto){
    printf("Anna tiedoston nimi: ");
    scanf("%s", pTiedosto);
    getchar();
    return;
}

SANALK *lueTiedosto(char *pTiedosto, SANALK *pAlku){
    char tiedostoLue[TIEDOSTOPITUUS];
    char aRivi[SANAPITUUS];
    char *p1 = NULL, *p2 = NULL;
    strcpy(tiedostoLue, pTiedosto);
    FILE *tiedosto;
    if((tiedosto = fopen(tiedostoLue, "r")) == NULL){
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    fgets(aRivi, SANAPITUUS, tiedosto);
    while(fgets(aRivi, SANAPITUUS, tiedosto) != NULL){
        p1 = strtok(aRivi, ";");
        p2 = strtok(NULL, ";");
        pAlku = lisaaSolmu(pAlku, p1, p2);
    }
    printf("Tiedosto '%s' luettu.\n\n", pTiedosto);
    fclose(tiedosto);
    return(pAlku);
}

SANALK *lisaaSolmu(SANALK *pAlku, char *p1, char *p2){
    SANALK *pUusi = NULL, *ptr = NULL;
    if((pUusi = (SANALK*)malloc(sizeof(SANALK))) == NULL){
        perror("Muistin varaus epäonnistui");
    }
    strcpy(pUusi->aSana, p1);
    pUusi->iLuokka = atoi(p2);
    pUusi->pSeuraava = NULL;
    if(pAlku == NULL){
        pAlku = pUusi;
    }else{
        ptr = pAlku;
        while(ptr->pSeuraava != NULL){
            ptr = ptr->pSeuraava;
        }
        ptr->pSeuraava = pUusi;
    }
    return(pAlku);
}


SANALUOKAT sanaluokkaAnalyysi(SANALK *pAlku, SANALUOKAT sanaluokkaTbl[9]){
    int i;
    SANALK *ptr = pAlku;
    for(i=0; i < 10; i++){
        sanaluokkaTbl[i].iLkm = 0;
    }
    while (ptr != NULL){
        sanaluokkaTbl[ptr->iLuokka-1].iLkm += 1;
        ptr = ptr->pSeuraava;
    }
    printf("Sanaluokittaiset lukumäärät analysoitu.\n\n");
    return(sanaluokkaTbl[9]);
}

struct tulos tilastotietoAnalyysi(struct tulos tulokset, SANALK *pAlku){
    SANALK *ptr = pAlku;
    strcpy(tulokset.aAakkos1,ptr->aSana);
    strcpy(tulokset.aAakkos2, ptr->aSana);
    strcpy(tulokset.aLyhyinSana, ptr->aSana);
    strcpy(tulokset.aPisinSana, ptr->aSana);
    tulokset.iKirjaintenMaara = 0;
    tulokset.iSanojenMaara = 0;
    while(ptr != NULL){
        tulokset.iSanojenMaara += 1;
        tulokset.iKirjaintenMaara += strlen(ptr->aSana);
        if(strcmp(ptr->aSana, tulokset.aAakkos1) < 0){
            strcpy(tulokset.aAakkos1, ptr->aSana);
        }
        else if(strcmp(ptr->aSana, tulokset.aAakkos2) > 0){
            strcpy(tulokset.aAakkos2, ptr->aSana);
        }
        if(strlen(ptr->aSana) > strlen(tulokset.aPisinSana)){
            strcpy(tulokset.aPisinSana, ptr->aSana); 
        }
        else if(strlen(ptr->aSana) < strlen(tulokset.aLyhyinSana)){
            strcpy(tulokset.aLyhyinSana, ptr->aSana);
        }
        ptr = ptr->pSeuraava;
    }
    tulokset.fPituusKa = (float)tulokset.iKirjaintenMaara/tulokset.iSanojenMaara;
    printf("Analysoitu %d sanaa.\n", tulokset.iSanojenMaara);
    return(tulokset);
}

void tiedostoKirjoitus(struct tulos tulokset, SANALUOKAT sanaluokkaTbl[], char *pTiedosto){
    char tiedostoKirjoita[30];
    tulostenTulostus(stdout, tulokset, sanaluokkaTbl);
    strcpy(tiedostoKirjoita, pTiedosto);
    FILE *tiedosto;
    if((tiedosto = fopen(tiedostoKirjoita, "w")) == NULL){
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    tulostenTulostus(tiedosto, tulokset, sanaluokkaTbl);
    printf("Tiedosto '%s' kirjoitettu.\n\n", pTiedosto);
    fclose(tiedosto);
    return;
}

void tulostenTulostus(FILE *parametri, struct tulos tulokset, SANALUOKAT sanaluokkaTbl[]){
    int i;
    fprintf(parametri, "Tilastotiedot %d sanasta:\n", tulokset.iSanojenMaara);
    fprintf(parametri,"Keskimääräinen sanan pituus on %.1f merkkiä.\n", tulokset.fPituusKa);
    fprintf(parametri,"Pisin sana '%s' on %ld merkkiä pitkä.\n", tulokset.aPisinSana, strlen(tulokset.aPisinSana));
    fprintf(parametri,"Lyhyin sana '%s' on %ld merkkiä pitkä.\n", tulokset.aLyhyinSana, strlen(tulokset.aLyhyinSana));
    fprintf(parametri,"Aakkosjärjestyksessä ensimmäinen sana on '%s'.\n", tulokset.aAakkos1);
    fprintf(parametri,"Aakkosjärjestyksessä viimeinen sana on '%s'.\n\n", tulokset.aAakkos2);
    fprintf(parametri, "Sanaluokka;Lkm\n");
    for(i=0; i < 10; i++){
        fprintf(parametri, "Luokka %d;%d\n", i+1, sanaluokkaTbl[i].iLkm);
    }
    return;
}

SANALK *tyhjennaLista(SANALK *pAlku){
    SANALK *ptr = pAlku;
    while(ptr != NULL){
        pAlku = ptr->pSeuraava;
        free(ptr);
        ptr = pAlku;
    }
    pAlku = NULL;
    return(pAlku);
}
/* eof */