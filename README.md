# Zadatak 1 – Simulacija dugotrajnog posla s datotekama i signalima

## Opis zadatka

Program simulira dugotrajan posao (kao neki servis) koji koristi dvije datoteke:

- **obrada.txt** – u koju program dodaje kvadrate sljedećih brojeva (1, 4, 9, 16, …), svaki broj u novi red.
- **status.txt** – u koju program zapisuje informaciju o tome gdje je stao ili kako nastaviti. Na primjer, ako je zadnji broj u obrada.txt 100 (tj. kvadrat broja 10), u status.txt će biti zapisano 10, da program zna odakle nastaviti idući put.

Prije prvog pokretanja potrebno je ručno kreirati i inicijalizirati obje datoteke s početnom vrijednosti 1 ili -.

## Kako program radi

1. Program pri pokretanju otvara datoteke i iz **status.txt** čita spremljenu vrijednost.
2. Ako je vrijednost veća od 0, program nastavlja računati kvadrate od sljedećeg broja te rezultate dodaje u **obrada.txt**.
3. Prije nastavka rada u **status.txt** upisuje 0, što označava da je obrada u tijeku.
4. Program dodaje odgodu (npr. `sleep(5)`) između izračuna radi usporavanja izvođenja.
5. Na signal **SIGUSR1** program ispisuje trenutni broj koji obrađuje.
6. Na signal **SIGTERM** program zapisuje zadnji obrađeni broj u **status.txt** i završava rad.
7. Na signal **SIGINT** program prekida rad bez izmjena u **status.txt** (ostaje 0), što će prilikom sljedećeg pokretanja uzrokovati da program „analizira“ datoteku **obrada.txt** i nastavi od posljednjeg broja.

## Upute za pokretanje

gcc main.c -o program -lm


 


