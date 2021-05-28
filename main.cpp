#include <cstdlib>
#include<stdio.h>
#include<stdlib.h>

typedef struct nodo {
	struct nodo* izquierdo;
	struct nodo* derecho;
	int dato;
}Nodo;

Nodo* Nuevo();
Nodo* Insertar(int, Nodo*);
bool Buscar(int dato, Nodo*);
void Error();
void Menu();

int main(){
	int num, opc;
	Nodo *p;
	p = NULL;

	do {
		system("clear");
		Menu();
		scanf("%d", &opc);

		switch (opc) {
			case 1:
				system("clear");
				printf("Ingrese el dato a guardar:\t");
				scanf("%d", &num);
				p = Insertar(num, p);
				getchar();
				break;
			case 2: 
				system("clear");
				printf("Ingrese el dato a buscar:\t");
				scanf("%d", &num);
				Buscar(num, p);
				getchar();
				break;
		}

	}while (opc != 3);
	
	return 0;
}

void Error(){
	perror("Memoria insuficiente!!\n");
	exit(1);
}

Nodo* Nuevo(){
	Nodo *p;
	p = (Nodo*) malloc(sizeof(Nodo));
	if(!p) Error();
	return (p);
}

Nodo* Insertar(int dato, Nodo *p){
	if(p == NULL){
		p = Nuevo();
		p->derecho = NULL;
		p->izquierdo = NULL;
		p->dato = dato;
		printf("Se a guardado el dato\n");
		getchar();
		return (p);
	}

	if (dato < p->dato) {
		p->izquierdo = Insertar(dato, p->izquierdo);
	}else {
		p->derecho = Insertar(dato, p->derecho);
	}

	return (p);
}

bool Buscar(int dato, Nodo* p){
	if(p == NULL){
		printf("Dato no encontrado\n");
		getchar();
		return false;
	}

	if(dato == p->dato){
		printf("El dato se encuentra en el arbol\n");
		getchar();
		return true;
	}

	if (dato < p->dato) {
		return (Buscar(dato, p->izquierdo));
	}else {
		return (Buscar(dato, p->derecho));
	}
}

void Menu(){
	printf("Escoja una opcion\n");
	printf("1.\tIngresar un dato\n");
	printf("2.\tBuscar un dato\n");
	printf("3.\tSalir\n");
}
