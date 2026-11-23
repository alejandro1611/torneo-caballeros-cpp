// Aplica los efectos correspondientes sobre el jugador según la runa obtenida de la rueda.
void aplicar_runa(tjugador &j, char runa, bool &eliminado)
{
    eliminado = false;

    switch (runa)
    {
    case 'M':
        j.puntaje = j.puntaje + 10;
        cout << "RUNA AURUM: +10 PUNTOS" << endl;
        break;

    case 'T':
        j.puntaje = j.puntaje * 2;
        cout << "RUNA VERIDIAN: PUNTAJE DUPLICADO" << endl;
        break;

    case 'C':
        if (j.cantidad_protectores < 3)
        {
            apilar(j.tope);
            j.cantidad_protectores++;

            cout << "RUNA VITA: OBTUVISTE UN PROTECTOR" << endl;
        }
        else
        {
            cout << "RUNA VITA: YA TENES 3 PROTECTORES" << endl;
        }
        break;

    case 'B':
        cout << "RUNA CALAMITAS: PERDISTE UN PROTECTOR O UNA VIDA" << endl;

        if (j.cantidad_protectores > 0)
        {
            desapilar(j.tope);
            j.cantidad_protectores--;
        }
        else
        {
            j.vidas--;
            if (j.vidas == 0)
                eliminado = true;
        }
        break;
    }
}

// Carga inicializa y pasa los caballeros elegidos a la cola de juego del desafío.
void armar_cola(tcola &cola, telegidos elegidos, int cantidad)
{
    tjugador j;

    inicializar_cola(cola);

    for (int i = 0; i < cantidad; i++)
    {
        j = elegidos[i];

        encolar(cola, j);
    }
}

// Permite seleccionar y validar los caballeros participantes que ingresarán al desafío.
void elegir_caballeros(telegidos &elegidos, int &cantidad)
{
    bool encontrado;
    bool repetido;
    int registrados;
    int maximo;

    registrados = contar_caballeros();

    maximo = MAX_JUGADORES;
    if (registrados < maximo)
        maximo = registrados;

    cout << "\nCaballeros registrados: " << registrados << endl;
    cout << "Cantidad de caballeros participantes (2 a " << maximo << "): ";

    while (!(cin >> cantidad) || cantidad < 2 || cantidad > maximo)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "CANTIDAD INVALIDA. INGRESE NUEVAMENTE: ";
    }

    cin.ignore();

    for (int i = 0; i < cantidad; i++)
    {
        do
        {
            cout << "Ingrese el apodo del caballero " << i + 1 << ": ";

            cin.getline(elegidos[i].apodo, 30);

            encontrado = buscar_apodo(elegidos[i].apodo);

            repetido = false;

            for (int j = 0; j < i; j++)
            {
                if (strcmp(elegidos[i].apodo, elegidos[j].apodo) == 0)
                    repetido = true;
            }

            if (strlen(elegidos[i].apodo) == 0)
                cout << "EL APODO NO PUEDE ESTAR VACIO" << endl;
            else
            {
                if (!encontrado)
                    cout << "EL CABALLERO NO EXISTE" << endl;
                else
                {
                    if (repetido)
                        cout << "EL CABALLERO YA FUE SELECCIONADO" << endl;
                }
            }

        } while (strlen(elegidos[i].apodo) == 0 || !encontrado || repetido);

        elegidos[i].vidas = 2;
        elegidos[i].puntaje = 0;
        inicializar_pila(elegidos[i].tope);
        elegidos[i].cantidad_protectores = 0;
    }
}


// Resuelve empates mediante tiradas aleatorias interactivas hasta definir un único ganador.
int desempatar(tparticipantes participantes,tindices indices, int cantidad)
{
    tindices tiros;
    tindices empatados;
    int mayor;
    int nueva_cantidad;
    int ganador;

    while (cantidad > 1)
    {
        mayor = -1;
        nueva_cantidad = 0;

        cout << "\n**** DESEMPATE ****" << endl;

        for (int i = 0; i < cantidad; i++)
        {
            cout << "\nTurno de " << participantes[indices[i]].apodo << ": presione ENTER para tirar..." << endl;
            cin.get();

            tiros[i] = rand() % 100 + 1;

            cout << participantes[indices[i]].apodo << " obtuvo: " << tiros[i] << endl;

            if (tiros[i] > mayor)
                mayor = tiros[i];
        }

        for (int i = 0; i < cantidad; i++)
        {
            if (tiros[i] == mayor)
            {
                empatados[nueva_cantidad] = indices[i];
                nueva_cantidad++;
            }
        }

        cantidad = nueva_cantidad;

        for (int i = 0; i < cantidad; i++)
            indices[i] = empatados[i];
    }

    ganador = indices[0];

    return ganador;
}

// Muestra por pantalla las estadísticas actuales de vidas, puntaje y protectores del caballero.
void mostrar_estado(tjugador j)
{
    cout << "Vidas: " << j.vidas << endl;
    cout << "Puntaje: " << j.puntaje << endl;
    cout << "Protectores: " << j.cantidad_protectores << endl;
}

// Imprime el nombre completo y descriptivo correspondiente a la letra de la runa obtenida.
void mostrar_nombre_runa(char runa)
{
    switch (runa)
    {
        case 'M':
            cout << "RUNA OBTENIDA: AURUM" << endl;
            break;

        case 'T':
            cout << "RUNA OBTENIDA: VERIDIAN" << endl;
            break;

        case 'C':
            cout << "RUNA OBTENIDA: VITA" << endl;
            break;

        case 'B':
            cout << "RUNA OBTENIDA: CALAMITAS" << endl;
            break;
    }
}

// Gestiona el flujo completo del turno de un caballero al girar la rueda y aplicar su runa.
void ejecutar_turno(tjugador &j, prueda &rueda, bool &eliminado)
{
    char runa;

    cout << "\n********************************" << endl;
    cout << "TURNO DE: " << j.apodo << endl;
    cout << "********************************" << endl;

    mostrar_estado(j);

    cout << "\nPresione ENTER para girar la rueda..." << endl;
    cin.get();

    girar(rueda, runa);

    mostrar_nombre_runa(runa);

    // Llamamos a aplicar_runa
    aplicar_runa(j, runa, eliminado);

    cout << "\n**** ESTADO ACTUAL DEL CABALLERO ****" << endl;
    mostrar_estado(j);
}

// Procesa los puntajes finales de los sobrevivientes, resuelve empates y corona al campeón.
void coronar_campeon(tcola &cola)
{
    tjugador j;
    tparticipantes participantes;
    tjugador campeon;
    
    int cantidad_participantes = 0;
    int mayor_puntaje;
    tindices indices;
    int cantidad_empatados = 0;
    int ganador;

    // Recuperamos los jugadores que siguen en la cola.
    while (!cola_vacia(cola))
    {
        desencolar(cola, j);
        participantes[cantidad_participantes] = j;
        cantidad_participantes++;
    }

    // Buscamos el mayor puntaje.
    mayor_puntaje = participantes[0].puntaje;
    
    for (int i = 1; i < cantidad_participantes; i++)
    {
        if (participantes[i].puntaje > mayor_puntaje)
            mayor_puntaje = participantes[i].puntaje;
    }

    // Identificamos a los caballeros empatados.
    for (int i = 0; i < cantidad_participantes; i++)
    {
        if (participantes[i].puntaje == mayor_puntaje)
        {
            indices[cantidad_empatados] = i;
            cantidad_empatados++;
        }
    }

    // Determinamos al campeon.
    if (cantidad_empatados == 1)
        ganador = indices[0];
    else
    {
        cout << "\nHAY UN EMPATE EN EL PUNTAJE MAXIMO" << endl;
        ganador = desempatar(participantes, indices, cantidad_empatados);
    }

    campeon = participantes[ganador];

    cout << "\n**** CAMPEON DE CAMELOT ****" << endl;
    cout << "Caballero: " << campeon.apodo << endl;
    cout << "Puntaje obtenido: " << campeon.puntaje << endl;

    // Se liberan las pilas de todos los participantes.
    for (int i = 0; i < cantidad_participantes; i++)
        liberar_pila(participantes[i].tope);

    // Solo se contabiliza el puntaje del campeon.
    actualizar_campeon(campeon.apodo, campeon.puntaje);
}

// Controla el bucle principal de rondas, turnos y eliminaciones durante el desafío.
void jugar_desafio(prueda &rueda, telegidos elegidos, int cantidad)
{
    tcola cola;
    tjugador j;
    bool eliminado;
    int vivos = cantidad;
    int ronda = 1;
    int turnos_ronda;

    armar_cola(cola, elegidos, cantidad);

    // Limpiamos el ENTER pendiente del menu.
    cin.ignore(1000, '\n');

    cout << "\n**** COMIENZA EL DESAFIO DE MERLIN ****" << endl;
    cout << "Presione ENTER para comenzar..." << endl;
    cin.get();

    while (vivos > 1 && rueda != NULL)
    {
        cout << "\n================================" << endl;
        cout << "           RONDA " << ronda << endl;
        cout << "================================" << endl;

        turnos_ronda = cola.cantidad;

        for (int i = 0; i < turnos_ronda && vivos > 1 && rueda != NULL; i++)
        {
            desencolar(cola, j);

            // Un modulo aparte se encarga de los turnos
            ejecutar_turno(j, rueda, eliminado);

            if (eliminado)
            {
                vivos--;
                liberar_pila(j.tope);
                j.tope = NULL;

                cout << "\n************************************" << endl;
                cout << "   " << j.apodo << " HA SIDO ELIMINADO" << endl;
                cout << "************************************" << endl;
            }
            else
            {
                encolar(cola, j);
            }

            cout << "\nTURNO FINALIZADO" << endl;
            cout << "Caballeros restantes: " << vivos << endl;

            if (vivos > 1 && rueda != NULL)
            {
                cout << "\nPresione ENTER para continuar..." << endl;
                cin.get();
            }
        }

        ronda++;
    }

    // La asignacion de campeon la realiza otro modulo
    coronar_campeon(cola);

    // La rueda se libera al finalizar cada partida.
    liberar_rueda(rueda);
}