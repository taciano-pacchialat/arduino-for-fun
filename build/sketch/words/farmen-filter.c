#line 1 "/home/taci/repos/game-station/words/farmen-filter.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct n {
    char dato[200];
    struct n *sig;
} nodo;

void inicializar(nodo **);
void agregarAdelante(char*, nodo **);
void agregarAtras(char*, nodo **);
void mostrarLista(nodo *);
void leerSinRepetir(nodo **);
int estaEnLaLista(char *, nodo *);
void escribirEnArchivo(nodo *);

int main() {
    nodo *lista;
    inicializar(&lista);
    leerSinRepetir(&lista);
    escribirEnArchivo(lista);

    liberarLista(&lista);
    return 0;
}

void inicializar(nodo **lista) {
    *lista = NULL;
}

void agregarAdelante(char *elemen, nodo **lista) {
    nodo *nue = (nodo *)malloc(sizeof(nodo));
    strcpy(nue->dato, elemen);
    nue->sig = *lista;
    *lista = nue;
}

void agregarAtras(char *elemen, nodo **lista) {
    nodo *nue = (nodo *)malloc(sizeof(nodo));
    strcpy(nue->dato, elemen);
    nue->sig = NULL;

    if (*lista == NULL) {
        agregarAdelante(elemen, lista);
        return;
    }

    nodo *actual = *lista;
    while (actual->sig != NULL) {
        actual = actual->sig;
    }
    actual->sig = nue;
}

int estaEnLaLista(char *palabra, nodo *lista) {
    nodo *actual = lista;
    while (actual != NULL) {
        if (strcmp(palabra, actual->dato) == 0) {
            return 1;
        }
        actual = actual->sig;
    }
    return 0;
}

void leerSinRepetir(nodo **lista) {
    FILE *f = fopen("palabras.txt", "r");
    if (f == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char palabra[100];
    while (fscanf(f, "%s", palabra) == 1) {
        if (!estaEnLaLista(palabra, *lista)) {
            agregarAtras(palabra, lista);
            printf("%s\n", palabra);
        }
    }
    fclose(f);
}

void escribirEnArchivo(nodo *lista) {
    FILE *arch = fopen("sinRepetir.txt", "w");
    if (arch == NULL) {
        printf("No se pudo crear el archivo.\n");
        return;
    }

    nodo *actual = lista;
    while (actual != NULL) {
        fputs(actual->dato, arch);
        fputs("\n", arch);
        actual = actual->sig;
    }
    fclose(arch);
}


 void liberarLista(nodo **lista) {
     nodo *actual = *lista;
        while (actual != NULL) {
       nodo *temp = actual;
         actual = actual->sig;
         free(temp);
     }
     *lista = NULL;
 }

void mostrarLista(nodo *lista) {
    nodo *actual = lista;
    while (actual != NULL) {
        printf("%s ", actual->dato);
        if (actual->sig != NULL) {
            printf(",");
        }
        actual = actual->sig;
    }
    printf("\n");
}
