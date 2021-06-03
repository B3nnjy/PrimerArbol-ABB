#include<stdio.h>
#include<winbgim.h>
#include<stdlib.h>
#include<time.h>

typedef struct nodo {
	struct nodo* izquierdo;
	struct nodo* derecho;
	int dato;
	int color;
	int x, y;
}Nodo;

Nodo* Nuevo();
Nodo* Insertar(int, Nodo*);
Nodo* Buscar(int dato, Nodo*, int);
Nodo* BuscarMayor(Nodo*);
Nodo* BuscarMenor(Nodo*);
Nodo* Suprimir(int, Nodo*);
Nodo* Cambiar(Nodo*, Nodo*);
Nodo* cordenadas(Nodo*, int, int, int);
void VerPostOrden(Nodo*);
void VerEnOrden(Nodo*);
void VerPreOrden(Nodo*);
void Error();
void Menu();
void drawArbol(Nodo*, int);
void verArbol(Nodo*);
Nodo* Color(Nodo*);

int main(){
	int num, opc;
	Nodo *p;
	p = NULL;

	initwindow(1400, 500);

	do {
		
		if(p == NULL){
			cleardevice();
			setcolor(15);
			settextstyle(2, 0, 12);
			outtextxy(getmaxx()/2-(textwidth("Arbol vacio")), getmaxy()/2, "Arbol Vacio");
		}else{
			p = Color(p);
			
			cleardevice();
			verArbol(p);
		}
		
		system("cls");
		Menu();
		scanf("%d", &opc);

		switch (opc) {
			case 1:
				system("cls");
				printf("Ingrese el dato a guardar:\t");
				scanf("%d", &num);

				if (Buscar(num, p, 0) == NULL) {
					p = Insertar(num, p);
					p = cordenadas(p, getmaxx()/2, 18, 0);
				}else {
					Buscar(num, p, 1);
					printf("El dato ya esta en el arbol\n");
				}

				getchar();
				getchar();
				break;
			case 2: 
				system("cls");
				printf("Ingrese el dato a buscar:\t");
				scanf("%d", &num);

				if (Buscar(num, p, 1) != NULL){
					printf("El dato %d, se a encontrado\n", Buscar(num, p, 0)->dato); 
				}else {
					printf("No se ha encontrado el dato %d\n", num);
				}

				getchar();
				getchar();
				break;
			case 3:
				system("cls");
				printf("Recorrido del arbol en Postorden\n");

				if (p != NULL) {
					VerPostOrden(p);
				}else {
					printf("El arbol esta vacio\n");
				}

				getchar();
				getchar();
				break;
			case 4:
				system("cls");
				printf("Recorrido del arbol en Orden\n");
	
				if (p != NULL) {
					VerEnOrden(p);
				}else {
					printf("El arbol esta vacio\n");
				}			

				getchar();
				getchar();
				break;
			case 5:
				system("cls");
				printf("Recorrido del arbol en Preorden\n");
				
				if (p != NULL) {
					VerPreOrden(p);
				}else {
					printf("El arbol esta vacio\n");
				}			

				getchar();
				getchar();
				break;
			case 6:
				system("cls");
				
				if (p != NULL) {
					printf("El dato mayor es: %d\n", BuscarMayor(p)->dato);
				}else {
					printf("El arbol esta vacio\n");
				}			

				getchar();
				getchar();
				break;
			case 7:
				system("cls");

				if (p != NULL) {
					printf("El dato menor es: %d", BuscarMenor(p)->dato);
				}else {
					printf("El arbol esta vacio\n");
				}			

				getchar();
				getchar();
				break;
			case 8:
				system("cls");
				printf("Inserte el dato a eliminar: ");
				scanf("%d", &num);

				if (Buscar(num, p, 1) != NULL){
					p = Suprimir(num, p);
					p = cordenadas(p, getmaxx()/2, 18, 0);
					printf("Dato Eliminado\n");
				}else {
					printf("El dato %d no esta guardado\n", num);
				}

				getchar();
				getchar();
				break;
			case 9:
				int numer;
				system("cls");
				printf("Llenado automatico!!\n");
				printf("Cuantos datos quiere que se agregar: ");
				scanf("%d", &num);
				
				
				for(int i = 0; i <=num; i++){
					numer = rand() % 99;
					if(Buscar(numer, p, 0) == NULL){
						p = Insertar(numer, p);	
						p = cordenadas(p, getmaxx()/2, 18, 0);
					}else{
						i--;
					}
				}
				getchar();
				getchar();
				break;
		}

	}while (opc != 10);
	
	closegraph();
	
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
		p->color = 0;
		printf("Dato guardado\n");
		return (p);
	}

	if (dato < p->dato) {
		p->izquierdo = Insertar(dato, p->izquierdo);
	}else {
		p->derecho = Insertar(dato, p->derecho);
	}

	return (p);
}

Nodo* cordenadas(Nodo* p, int x, int y, int div){
	if(p != NULL){
		p->x = x;
		p->y = y;
		div += 2;
		p->izquierdo = cordenadas(p->izquierdo, x-(p->x/(div*1)), y+40, div);
		p->derecho = cordenadas(p->derecho, x+(p->x/(div)), y+40, div+8);
	}
	
	return p;
}

Nodo* Color(Nodo* p){
	if(p != NULL){
		p->color = 0;
		
		p->derecho = Color(p->derecho);
		p->izquierdo = Color(p->izquierdo);
	}
	
	return p;
}


Nodo* Buscar(int dato, Nodo* p, int opc){
	if(p == NULL){
		return NULL;
	}

	if(dato == p->dato){
		if(opc == 1){
			p->color = 14;
			drawArbol(p, 200);
		}
		return p;
	}

	if (dato < p->dato) {
		return (Buscar(dato, p->izquierdo, opc));
	}else {
		return (Buscar(dato, p->derecho, opc));
	}
}

void VerPostOrden(Nodo* p){
	if (p == NULL) {
		return;
	}

	VerPostOrden(p->izquierdo);
	VerPostOrden(p->derecho);

	printf("%d ", p->dato);
	p->color = 14;
	drawArbol(p, 270);
}

void VerEnOrden(Nodo* p){
	if (p == NULL) {
		return;
	}

	VerEnOrden(p->izquierdo);
	printf("%d ", p->dato);
	p->color = 14;
	drawArbol(p, 270);
	VerEnOrden(p->derecho);
}

void VerPreOrden(Nodo* p){
	if (p == NULL) {
		return;
	}

	printf("%d ", p->dato);
	p->color = 14;
	drawArbol(p, 270);
	
	VerPreOrden(p->izquierdo);
	VerPreOrden(p->derecho);
}

Nodo* BuscarMayor(Nodo* p){
	if (p->derecho == NULL) {
		p->color = 14;
		drawArbol(p, 0);
		return p;
	}

	return BuscarMayor(p->derecho);
}

Nodo* BuscarMenor(Nodo* p){
	if (p->izquierdo == NULL) {
		p->color = 14;
		drawArbol(p, 0);
		return p;
	}

	return BuscarMenor(p->izquierdo);
}

Nodo* Suprimir(int dato, Nodo* p){
	if (p == NULL) {
		return NULL;
	}

	if (dato < p->dato) {
		p->izquierdo = Suprimir(dato, p->izquierdo);
	}

	if (dato > p->dato) {
		p->derecho = Suprimir(dato, p->derecho);
	}

	if (p->dato == dato) {
		p->color = 4;
		drawArbol(p, 200);
		if (p->derecho == NULL) {
			p = p->izquierdo;
		}else if (p->izquierdo == NULL) {
			p = p->derecho;
		}else {
			p->derecho = Cambiar(p, p->derecho);
		}
	}
	
	return p;
}

Nodo* Cambiar(Nodo* p, Nodo* s){
	if (s->izquierdo == NULL) {
		p->dato = s->dato;
		s = s->derecho;
		return s;
	}

	s->izquierdo = Cambiar(p, s->izquierdo);

	return s;
}

void drawArbol(Nodo* p, int seg){
	int x = p->x;
	int y = p->y;
	char text[3] = " ";
	
	if(p->derecho != NULL){
		setcolor(1);
		setlinestyle(1,0,2);
		line(x, y, p->derecho->x, p->derecho->y);
	}
	
	if(p->izquierdo != NULL){
		setcolor(1);
		setlinestyle(1,0,2);
		line(x, y, p->izquierdo->x, p->izquierdo->y);
	}
	
	
	setfillstyle(1, p->color);
	fillellipse(x, y, 18, 18);
	setcolor(1);
	setlinestyle(1,0,2);
	circle(x, y, 18);
	sprintf(text, "%d", p->dato);
	setcolor(3);
	settextstyle(2,0,7);
	outtextxy(x-8, y-10, text);
	
	delay(seg);
}

void verArbol(Nodo* p){
	if (p == NULL) {
		return;
	}

	drawArbol(p, 150);
	
	verArbol(p->izquierdo);
	verArbol(p->derecho);
}

void Menu(){
	printf("Escoja una opcion\n");
	printf("1.\tIngresar un dato\n");
	printf("2.\tBuscar un dato\n");
	printf("3.\tRecorrer el arbol en Postorden\n");
	printf("4.\tRecorrer el arbol en Orden\n");
	printf("5.\tRecorrer el arbol en Preorden\n");
	printf("6.\tBuscar dato mas grande\n");
	printf("7.\tBuscar el dato mas menor\n");
	printf("8.\tSuprimir un dato\n");
	printf("9.\tLlenar automaticamente\n");
	printf("10.\tSalir\n");
}
