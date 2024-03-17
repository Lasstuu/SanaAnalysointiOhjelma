# Tekijä: Lassi Tuominen
# PVM: 10.3.2023

HTPerustaso: HTPerustaso.o HTPerusKirjasto.o
	gcc -o HT HTPerustaso.o HTPerusKirjasto.o
HTPerustaso.o: HTPerustaso.c HTPerusKirjasto.h
	gcc -c HTPerustaso.c -std=c99 -pedantic -Wall
HTPerusKirjasto.o: HTPerusKirjasto.c HTPerusKirjasto.h
	gcc -c HTPerusKirjasto.c -std=c99 -pedantic -Wall