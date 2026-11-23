// Inicializa los punteros y el contador de la cola circular dejándola vacía.
void inicializar_cola(tcola &c)
{
    c.cantidad = 0;
    c.frente = 0;
    c.final = 0;
}

// Devuelve verdadero si la cola no tiene elementos cargados actualmente.
bool cola_vacia(tcola c)
{
    return c.cantidad==0;
}

// Devuelve verdadero si la cola alcanzó el límite máximo de jugadores permitidos.
bool cola_llena(tcola c)
{
    return c.cantidad==MAX_JUGADORES;
}

// Calcula la siguiente posición en la estructura circular volviendo al inicio si llega al límite.
int siguiente (int indice)
{
    if(indice==MAX_JUGADORES-1)
        indice=0;
    else 
        indice++;
    return indice;
}

// Inserta un nuevo jugador al final de la cola circular si todavía hay espacio disponible.
void encolar(tcola &c, tjugador j)
{
    if(cola_llena(c)==true)
    {
        cout<<"JUGADORES COMPLETADO"<<endl;
    }
    else
    {
        c.jugadores[c.final] = j;
        c.final = siguiente(c.final);
        c.cantidad++;
    }
    
}

// Extrae el jugador que se encuentra al frente de la cola circular actualizandola.
void desencolar(tcola &c, tjugador &j)
{
    if(cola_vacia(c)==true)
    {
        cout<<"NO HAY MAS JUGADORES"<<endl;
    }
    else
    {
        j = c.jugadores[c.frente];
        c.frente = siguiente(c.frente);
        c.cantidad--;
    }
}