// Inicializa la raíz del Árbol Binario de Búsqueda en nulo.
void inicializar_abb(pnodo_caballero &raiz)
{
    raiz = NULL;
}

// Inserta recursivamente un caballero en el ABB ordenándolo por su apodo único.
void insertar_abb(pnodo_caballero &raiz, caballero c)
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
        if (strcmp(c.apodo_unico, raiz->caballero_completo.apodo_unico) < 0)
            insertar_abb(raiz->izq, c);
        else
        {
            if (strcmp(c.apodo_unico, raiz->caballero_completo.apodo_unico) > 0)
                insertar_abb(raiz->der, c);
        }
    }
}

// Libera recursivamente toda la memoria ocupada por los nodos del ABB en Pos-orden.
void liberar_abb(pnodo_caballero &raiz)
{
    if (raiz != NULL)
    {
        liberar_abb(raiz->izq);
        liberar_abb(raiz->der);

        delete(raiz);
        raiz = NULL;
    }
}

// Lee los registros del archivo binario de caballeros y los carga ordenadamente en el ABB.
void cargar_abb(pnodo_caballero &raiz)
{
    parchivo cab;
    caballero c;

    liberar_abb(raiz);

    cab = fopen("caballeros.dat", "rb");

    if (cab != NULL)
    {
        fread(&c, sizeof(c), 1, cab);

        while (!feof(cab))
        {
            insertar_abb(raiz, c);

            fread(&c, sizeof(c), 1, cab);
        }

        fclose(cab);
    }
}

// Recorre el ABB (En-Orden) para exportar los caballeros ordenados hacia un archivo destino.
void escribir_enorden(pnodo_caballero raiz, parchivo destino)
{
    if (raiz != NULL)
    {
        escribir_enorden(raiz->izq, destino);

        fwrite(&raiz->caballero_completo, sizeof(caballero), 1, destino);

        escribir_enorden(raiz->der, destino);
    }
}



