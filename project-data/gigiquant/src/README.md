# Proiect PA: Gigiquant
Acest proiect are scopul de a ilustra concepte discutate la cursul de PA din anul 1, semestrul 2. Proiectul are un context economic, fiind format\
din 4 task-uri, fiecare folosind o structura de date invatata la curs pentru a modela diferite aplicatii sau idei din economie.
## Task 1: Sharpe Ratio
Primul task va calcula un indicator numit Sharpe ratio, capabil sa arate cat de profitabila\
este o investie bazata pentru un set de valori  portofoliului analizat pe mai multe zile.\
\
Fisierul de intrare trebuie sa aiba pe prima linie numarul total de observatii si pe linii separate\
valoarea portofoliului in fiecare zi.
## Task 2: Arbitraj
Al doilea task foloseste stive si cozi pentru a modela valorile a 3 piete in diferite zile. Pe\
baza acestor valori pot fi gasite oportunitati de arbitraj.\
\
Fisierul de intrare are numele pietei si valorile sale in diferite zile pe linii separate pentru\
fiecare dintre cele 3 piete.
## Task 3: Diversificarea portofoliului
Printr-un arbore binar de cautare sunt simulate miscarile la dreapta si la stanga a 10 actiuni.\
O miscare la stanga reprezinta o scadere a valorii actiunii,iar o miscare la dreapta reprezinta o crestere.\
\
Prima linie din fisierul de intrare are numele actinilor separate printr-o virgula, urmate de linii\
cu valorile actiunilor intr-un numar oarecare de zile.
## Task 4: Lanturi Markov
Lanturile Markov sunt mod matematic de a calcula probabilitatile intre stari. In cazul nostru, starile\
sunt intervale de preturi pentru o actiune si putem arata relatiile dintre stari printr-un graf. Astfel,\
putem afla probabilitatea ca o actiune sa se afle intr-un interval de pret la un moment dat.\
\
In fisierul de intrare trebuie specificat pe rand,pe linii separate, numarul de observatii, dimensiunea intervalului,numarul de zile in care\
verificata probabilitatea de final,probabilitatea de inceput,probabilitatea de final si observatiile.
## Cum poate fi rulat programul?
Executabilul creat pe baza fisierelor surse(sa zicem ca se numeste proiect_PA.exe) trebuie rulat in linia de comanda\
astfel : *./proiect_PA.exe fisierXX.in fisier.out*\
\
In functie de ce valori puneti in loc de XX se va rula unul dintre task-uri:\
\
Task 1 -> 1-5\
\
Task 2 -> 6-10\
\
Task 3 -> 11-15\
\
Task 4 -> 16-20