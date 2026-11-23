/*Archivo: campeones.hpp - Módulo para gestionar el Mural de Campeones Legendarios (ABB)*/

/*Procedimiento: insertar_abb_por_puntaje
  Objetivo: Inserta un caballero en el árbol binario de búsqueda ordenando por mejor puntaje. Si hay empate en puntaje, ordena alfabéticamente por apodo.*/
void insertar_abb_por_puntaje(pnodo_caballero &raiz, caballero c)
{
    if (raiz == NULL)
    {
        raiz = new tnodo_caballero;
        raiz->caballero_completo = c;

        raiz->izq = NULL;
        raiz->der = NULL;
    }
    else
    {
        if (c.mejor_puntaje < raiz->caballero_completo.mejor_puntaje)
            insertar_abb_por_puntaje(raiz->izq, c);
        else
        {
            if (c.mejor_puntaje > raiz->caballero_completo.mejor_puntaje)
                insertar_abb_por_puntaje(raiz->der, c);
            else
            {
                // Si tienen el mismo puntaje, ordenamos por apodo.
                if (strcmp(c.apodo_unico, raiz->caballero_completo.apodo_unico) < 0)
                    insertar_abb_por_puntaje(raiz->izq, c);
                else
                    insertar_abb_por_puntaje(raiz->der, c);
            }
        }
    }
}


/*Función: cargar_abb_campeones
  Objetivo: Lee el archivo secuencialmente y carga en el ABB a aquellos caballeros que tengan al menos 1 desafío ganado. Devuelve la cantidad de campeones insertados.*/
int cargar_abb_campeones(pnodo_caballero &raiz)
{
    parchivo cab;
    caballero c;
    int cantidad = 0;

    cab = fopen("caballeros.dat", "rb");

    if (cab != NULL)
    {
        while (fread(&c, sizeof(c), 1, cab) == 1)
        {
            if (c.cantidad_desafios_ganados > 0)
            {
                insertar_abb_por_puntaje(raiz, c);
                cantidad++;
            }
        }
        fclose(cab);
    }
    return cantidad;
}


/*Procedimiento: mostrar_campeones_creciente
  Objetivo: Realiza un recorrido En-Orden (Izquierda-Raiz-Derecha) para mostrar los campeones de menor a mayor puntaje.*/
void mostrar_campeones_creciente(pnodo_caballero raiz)
{
    if (raiz != NULL)
    {
        mostrar_campeones_creciente(raiz->izq);

        cout << "Apodo: "<< raiz->caballero_completo.apodo_unico << endl;
        cout << "Nombre: "<< raiz->caballero_completo.nombre << endl;
        cout << "Apellido: "<< raiz->caballero_completo.apellido << endl;
        cout << "Mejor puntaje: "<< raiz->caballero_completo.mejor_puntaje << endl;
        cout << "Desafios ganados: "<< raiz->caballero_completo.cantidad_desafios_ganados << endl;
        cout << "-----------------------------" << endl;

        mostrar_campeones_creciente(raiz->der);
    }
}


/*Procedimiento: mostrar_campeones_decreciente
  Objetivo: Realiza un recorrido En-Orden inverso (Derecha-Raiz-Izquierda) para mostrar los campeones de mayor a menor puntaje.*/
void mostrar_campeones_decreciente(pnodo_caballero raiz)
{
    if (raiz != NULL)
    {
        mostrar_campeones_decreciente(raiz->der);

        cout << "Apodo: "<< raiz->caballero_completo.apodo_unico << endl;
        cout << "Nombre: "<< raiz->caballero_completo.nombre << endl;
        cout << "Apellido: "<< raiz->caballero_completo.apellido << endl;
        cout << "Mejor puntaje: "<< raiz->caballero_completo.mejor_puntaje << endl;
        cout << "Desafios ganados: "<< raiz->caballero_completo.cantidad_desafios_ganados << endl;
        cout << "-----------------------------" << endl;

        mostrar_campeones_decreciente(raiz->izq);
    }
}


/*Procedimiento: campeones_legendarios
  Objetivo: Coordina la carga del árbol de campeones desde el archivo y gestiona el menú para mostrar el mural en el orden deseado. Libera la memoria al finalizar.*/
void campeones_legendarios()
{
    pnodo_caballero raiz;
    char orden;
    int cantidad;

    inicializar_abb(raiz);

    cantidad = cargar_abb_campeones(raiz);

    if (cantidad == 0)
        cout << "\nNO HAY CAMPEONES LEGENDARIOS REGISTRADOS" << endl;
    else
    {
        do
        {
            cout << "\n**** CAMPEONES LEGENDARIOS ****" << endl;
            cout << "1) Orden creciente" << endl;
            cout << "0) Orden decreciente" << endl;
            cout << "Ingrese el orden: ";
            cin >> orden;

        } while (orden != '0' && orden != '1');

        cout << "\n**** MURAL DE CAMPEONES ****" << endl;

        if (orden == '1')
            mostrar_campeones_creciente(raiz);
        else
            mostrar_campeones_decreciente(raiz);
    }

    liberar_abb(raiz);
}

