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
/* Tehtävä HTPerus, tiedoston nimi HTPerustaso.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HTPerusKirjasto.h"


int main(void){
    SANALUOKAT sanaluokkaTbl[10];
    SANALK *pAlku = NULL;
    struct tulos tulokset;
    char aTiedosto[TIEDOSTOPITUUS];
    char *pTiedosto = aTiedosto;
    int iValinta;
    do {
        iValinta = valikko();
        if (iValinta == 1) {
            pAlku = tyhjennaLista(pAlku);
            tiedostoNimi(pTiedosto);
            pAlku = lueTiedosto(pTiedosto, pAlku);
        }
        else if (iValinta == 2){
            if(pAlku == NULL){
                printf("Ei analysoitavaa, lue tiedosto ennen analyysiä.\n\n");
                continue;
            }
            tulokset = tilastotietoAnalyysi(tulokset, pAlku);
            sanaluokkaTbl[9] = sanaluokkaAnalyysi(pAlku, sanaluokkaTbl);

        }
        else if (iValinta == 3){
            if(!tulokset.iKirjaintenMaara){
                printf("Ei kirjoitettavia tietoja, analysoi tiedot ennen tallennusta.\n\n");
                continue;
            }
            tiedostoNimi(pTiedosto);
            tiedostoKirjoitus(tulokset, sanaluokkaTbl, pTiedosto);
        }
        else if (iValinta == 0) {
            printf("Lopetetaan.\n");
        }
        else{
            printf("Tuntematon valinta, yritä uudestaan.\n\n");
        }
    } while (iValinta != 0);
    pAlku = tyhjennaLista(pAlku);
    printf("\nKiitos ohjelman käytöstä.");
}
/* eof */