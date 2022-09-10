# ArboriBinari_SD3
/*Anton Dumitrita 324CB*/

Punctaj local: Test: 110/135 Bonus: 8/20

-tema contine explicatii si in comentariile din cod
-arb.c-
alocDir: aloca structura de tip Dir
alocFile: aloca structura de tip File 
searchDir: parcurge un arbore de directoare si intoarce 0 daca exista in acesta
un director cu numele "name" dat ca parametru, 1 in caz contrar
searchFile: aceeasi idee ca searchDir doar ca pe un arbore de fisiere
InsertFile: insereaza iterativ fisierul cu numele "name" in arborele cu radacina "file"
InsertDir: insereaza iterativ directorul cu numele "name" in arborele cu radacina "dir"
printFiles, printDirs: afiseaza in ordine lexicografica continutul arborelui de 
fisere/directoare
minFile, minDir: returneaza nodul cel mai din stanga(cu cea mai mica valoare lexicografica)
deleteFile, deleteDir: sterge nodul cu numele "name" din arborele de fisiere/directoare
freeDir, freeFile: elibereaza memoria pentru un nod fiser/director
searchHelperFile, searchHelperDir: intoarce referinta catre nodul cu numele "name" din arborele de fisiere/directoare

-tema3.c-
main:   initializeaza directorul root
        citeste de la stdin comenzile cu parametrii corespunzatori si apeleaza
        functiile care le implementeaza 
touch: foloseste functiile searchDir si searchFile pentru a verifica existenta
        unui fisier cu numele "name", iar in cazul in care acesta nu exista deja 
        initializeaza un nod cu numele fisierului si il insereaza in arbore folosind
        functia InsertFile

mkdir: insereaza un director cu numele "name" in arbore in cazul in care acesta
        nu exista deja
ls: afiseaza fiserle si directoarele din directorul curent folosind functiile
    prinDirs si printFiles

rm: verifica existenta fiserului in directorul curent
    daca exista in elimina folosind functia deleteFile

rmdir: verifica existenta directorului in directorul curent
        sterge directourul cautat, daca acesta exista, cu intreg continutul sau folosind 
        functia deleteDir
    
cd: schimba directorul curent in directorul cu numele "name"
    pentru cazul "..": director curent devine parintele directourului curent
    altfel, cauta cu functia searchHelperDir referinta catre directorul cu numele "name"
    care va devenii noul director curent

pwd: returneaza o variabila sir de caractere "path" ce va contine calea catre 
    directorul cautat
    salveaza toti parintii directorului pana la root in variabila pathContent
    concateneaza valorile salvate anterior, in ordine inversa, la variabila path 
    
    







