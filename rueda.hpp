// Inicializa el puntero de la rueda del destino dejándolo en nulo.
void inicializar_rueda(prueda &rueda)
{
    rueda = NULL;
}

// Recorre y libera de forma segura toda la memoria de la lista circular doble de la rueda.
void liberar_rueda(prueda &rueda)
{
    prueda aux;

    while (rueda != NULL)
    {
        aux = rueda;

        if (rueda->sig == rueda)
        {
            rueda = NULL;
        }
        else
        {
            rueda->ant->sig = rueda->sig;
            rueda->sig->ant = rueda->ant;

            rueda = rueda->sig;
        }

        delete (aux);
    }
}

// Inserta un nuevo nodo con su respectiva runa manteniendo la estructura circular doblemente enlazada.
void insertar_runa(prueda &rueda, char runa)
{
    prueda nuevo;

    nuevo = new tnodorueda;
    nuevo->runa = runa;

    if (rueda == NULL)
    {
        nuevo->sig = nuevo;
        nuevo->ant = nuevo;
        rueda = nuevo;
    }
    else
    {
        nuevo->sig = rueda;
        nuevo->ant = rueda->ant;

        rueda->ant->sig = nuevo;
        rueda->ant = nuevo;
    }
}

// Carga las runas de forma proporcional y aleatoria en la rueda según la cantidad de jugadores.
void cargar_aleatoriamente(prueda &rueda, int M)
{
    liberar_rueda(rueda);
    tcontador_runas cont;
    int total;
    int azar;
    char runa;

    cont.Aurum = M * 4;
    cont.Veridian = M * 2;
    cont.Vita = M * 25 / 10;
    cont.Calamitas = M * 25 / 10;

    total = cont.Aurum + cont.Veridian + cont.Vita + cont.Calamitas;

    while (total > 0)
    {
        azar = rand() % total;

        if (azar < cont.Aurum)
        {
            runa = 'M';
            cont.Aurum--;
        }
        else
        {
            azar = azar - cont.Aurum;

            if (azar < cont.Veridian)
            {
                runa = 'T';
                cont.Veridian--;
            }
            else
            {
                azar = azar - cont.Veridian;

                if (azar < cont.Vita)
                {
                    runa = 'C';
                    cont.Vita--;
                }
                else
                {
                    runa = 'B';
                    cont.Calamitas--;
                }
            }
        }

        insertar_runa(rueda, runa);

        total--;
    }
}

// Recorre la rueda circular e imprime por pantalla todas las runas disponibles actualmente.
void mostrar_rueda(prueda rueda)
{
    prueda aux;

    if (rueda == NULL)
    {
        cout << "LA RUEDA ESTA VACIA" << endl;
    }
    else
    {
        aux = rueda;

        do
        {
            switch (aux->runa)
            {
            case 'M':
                cout << "Aurum (Monedas)";
                break;

            case 'T':
                cout << "Veridian (Treboles)";
                break;

            case 'C':
                cout << "Vita (Corazones)";
                break;

            case 'B':
                cout << "Calamitas (Bombas)";
                break;
            }

            cout << endl;

            aux = aux->sig;

        } while (aux != rueda);
    }
}

// Simula el giro de la rueda seleccionando una runa al azar, extrayéndola y reajustando la estructura.
void girar(prueda &rueda, char &runa)
{
    prueda aux;
    int cantidad = 0;
    int posicion;

    if (rueda != NULL)
    {
        aux = rueda;

        do
        {
            cantidad++;
            aux = aux->sig;

        } while (aux != rueda);

        posicion = rand();

        aux = rueda;

        for (int i = 0; i < posicion; i++)
        {
            aux = aux->sig;
        }

        runa = aux->runa;

        if (aux->sig == aux)
        {
            rueda = NULL;
        }
        else
        {
            aux->ant->sig = aux->sig;
            aux->sig->ant = aux->ant;

            if (aux == rueda)
                rueda = aux->sig;
        }

        delete (aux);
    }
}
