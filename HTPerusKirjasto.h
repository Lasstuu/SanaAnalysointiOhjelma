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
/* Tehtävä HTPerus, tiedoston nimi HTPerusKirjasto.h */
#ifndef HTPERUSKIRJASTO_H
#define HTPERUSKIRJASTO_H
#define SANAPITUUS 100
#define TIEDOSTOPITUUS 30

typedef struct sanaLk {
    char aSana[SANAPITUUS];
    int iLuokka;
    struct sanaLk *pSeuraava;
}SANALK;

typedef struct sanaluokat {
    char aLuokka[30];
    int iLkm;
}SANALUOKAT;

struct tulos {
    int iSanojenMaara, iKirjaintenMaara;
    float fPituusKa;
    char aPisinSana[SANAPITUUS], aLyhyinSana[SANAPITUUS], aAakkos1[SANAPITUUS], aAakkos2[SANAPITUUS];
};

int valikko();
void tiedostoNimi(char *pTiedosto);
SANALK *lueTiedosto(char *pTiedosto, SANALK *pAlku);
SANALK *lisaaSolmu(SANALK *pAlku, char *p1, char *p2);
struct tulos tilastotietoAnalyysi(struct tulos tulokset, SANALK *pAlku);
SANALUOKAT sanaluokkaAnalyysi(SANALK *pAlku, SANALUOKAT sanaluokkaTbl[9]);
void tiedostoKirjoitus(struct tulos tulokset, SANALUOKAT sanaluokkaTbl[9], char *pTiedosto);
void tulostenTulostus(FILE *tiedosto, struct tulos tulokset, SANALUOKAT sanaluokkaTbl[9]);
SANALK *tyhjennaLista(SANALK *pAlku);

#endif
/* eof */