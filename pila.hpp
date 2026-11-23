// Inicializa la pila asignando un valor nulo al puntero de la cima.
void inicializar_pila(ppila &p)
{
    p=NULL;
}

// Devuelve verdadero si la pila se encuentra vacía.
bool pila_vacia(ppila p)
{
    return p==NULL;
}

// Agrega un nuevo nodo en la cima de la pila para representar un protector.
void apilar(ppila &p)
{
    ppila nuevo;

    nuevo = new tnodopila;

    nuevo->dato = 1;
    nuevo->sig = p;

    p = nuevo;
}

// Extrae y elimina el elemento que se encuentra en la cima de la pila.
void desapilar(ppila &p)
{
    ppila aux;

    if (pila_vacia(p)==false)
    {
        aux = p;
        p = p->sig;
        delete(aux);
    }
}

// Recorre toda la pila liberando dinámicamente la memoria de cada nodo.
void liberar_pila(ppila &p)
{
    ppila aux;

    while (pila_vacia(p)==false)
    {
        aux = p;
        p = p->sig;
        delete(aux);
    }
}