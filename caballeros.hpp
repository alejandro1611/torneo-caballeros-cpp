// Convierte una cadena de caracteres a entero validando que sean solo dígitos.
int mi_atoi(tcad cadena)
{
    int numero = 0;
    int i = 0;
    bool error = false; // Bandera para controlar la lectura

    // El bucle sigue mientras no llegue al final Y no haya encontrado errores
    while (cadena[i] != '\0' && error==false)
    {
        // Validamos que el caracter sea estrictamente un digito
        if (cadena[i] >= '0' && cadena[i] <= '9')
        {
            numero = (numero * 10) + (cadena[i] - '0');
        }
        else
        {
            numero = 0;
            error = true; 
        }
        
        i++;
    }

    return numero; 
}

// Pide y valida la edad por consola asegurando que sea un número mayor a cero.
void ingresar_edad(int &edad)
{
    tcad entrada;

    do
    {
        cout << "Ingrese Edad: ";
        cin.getline(entrada, 30);

        if (strlen(entrada) == 0)
        {
            cout << "CAMPO VACIO. Ingrese una edad valida" << endl;
            edad = 0;
        }
        else
        {
            // Llamamos a tu modulo personalizado
            edad = mi_atoi(entrada);

            if (edad <= 0)
                cout << "Ingrese una edad correcta (solo numeros mayores a 0)" << endl;
        }

    } while (edad <= 0);
}


// Busca un caballero por su apodo único en el archivo y devuelve verdadero si lo encuentra.
bool buscar_apodo(tcad apodo)
{
    parchivo cab;
    caballero c;
    bool encontrado = false;

    cab = fopen("caballeros.dat", "rb");

    if (cab != NULL)
    {
        // Lectura anticipada
        fread(&c, sizeof(c), 1, cab);

        while (!feof(cab) && encontrado==false)
        {
            if (strcmp(c.apodo_unico, apodo) == 0)
                encontrado = true;

            if (encontrado==false)
                fread(&c, sizeof(c), 1, cab);
        }

        fclose(cab);
    }

    return encontrado;
}


// Solicita y carga por teclado todos los datos de un nuevo caballero validando que no existan repetidos.
void cargar(caballero &c)
{
    bool repetido;

    cin.ignore();
    do
    {
        cout << "Ingrese Apellido: ";
        cin.getline(c.apellido, 30);

        if (strlen(c.apellido) == 0)
            cout << "CAMPO VACIO. Ingrese un APELLIDO VALIDO" << endl;
    } while (strlen(c.apellido) == 0);


    do
    {
        cout << "Ingrese Nombre: ";
        cin.getline(c.nombre, 30);

        if (strlen(c.nombre) == 0)
            cout << "CAMPO VACIO. Ingrese un NOMBRE VALIDO" << endl;
    } while (strlen(c.nombre) == 0);


    do
    {
        do
        {
            cout << "Ingrese Apodo: ";
            cin.getline(c.apodo_unico, 30);

            if (strlen(c.apodo_unico) == 0)
                cout << "CAMPO VACIO. Ingrese un APODO VALIDO" << endl;

        } while (strlen(c.apodo_unico) == 0);
        repetido = buscar_apodo(c.apodo_unico);
        if (repetido==true)
            cout << "EL APODO YA EXISTE" << endl;
    } while (repetido==true);


    do
    {
        cout << "Ingrese Titulo Noble: ";
        cin.getline(c.titulo_noble, 30);
        if (strlen(c.titulo_noble) == 0)
            cout << "CAMPO VACIO. Ingrese un TITULO VALIDO" << endl;
    } while (strlen(c.titulo_noble) == 0);

    ingresar_edad(c.edad);
    c.mejor_puntaje = 0;
    c.puntaje_total = 0;
    c.cantidad_desafios_ganados = 0;
}


// Carga los datos editables de un caballero existente durante el proceso de modificación.
void cargar2(caballero &c)
{
    cout << "\nMODIFICAR CABALLERO" << endl;

    do
    {
        cout << "Ingrese Apellido: ";
        cin.getline(c.apellido, 30);

        if (strlen(c.apellido) == 0)
            cout << "CAMPO VACIO. Ingrese un APELLIDO VALIDO" << endl;
    } while (strlen(c.apellido) == 0);


    do
    {
        cout << "Ingrese Nombre: ";
        cin.getline(c.nombre, 30);

        if (strlen(c.nombre) == 0)
            cout << "CAMPO VACIO. Ingrese un NOMBRE VALIDO" << endl;
    } while (strlen(c.nombre) == 0);

    do
    {
        cout << "Ingrese Titulo Noble: ";
        cin.getline(c.titulo_noble, 30);

        if (strlen(c.titulo_noble) == 0)
            cout << "CAMPO VACIO. Ingrese un TITULO VALIDO" << endl;
    } while (strlen(c.titulo_noble) == 0);
    ingresar_edad(c.edad);

    cout << "\nCABALLERO MODIFICADO EXITOSAMENTE" << endl;
}


// Reordena todo el archivo binario de caballeros utilizando un árbol binario de búsqueda.
void ordenar_archivo()
{
    parchivo cab;
    parchivo temp;
    caballero c;
    pnodo_caballero raiz;

    cab = fopen("caballeros.dat", "rb");

    if (cab != NULL)
    {
        // Leemos para ver si el archivo tiene datos
        fread(&c, sizeof(c), 1, cab);

        if (!feof(cab))
        {
            fclose(cab);

            inicializar_abb(raiz);
            cargar_abb(raiz);

            temp = fopen("temporal.dat", "wb");

            if (temp != NULL)
            {
                escribir_enorden(raiz, temp);

                fclose(temp);
                
                liberar_abb(raiz);

                if (remove("caballeros.dat") == 0)
                {
                    if (rename("temporal.dat", "caballeros.dat") != 0)
                        cout << "ERROR AL REEMPLAZAR EL ARCHIVO" << endl;
                }
                else
                {
                    remove("temporal.dat");
                    cout << "ERROR AL ELIMINAR EL ARCHIVO ORIGINAL" << endl;
                }
            }
            else
            {
                liberar_abb(raiz);
                cout << "ERROR AL CREAR EL ARCHIVO TEMPORAL" << endl;
            }
        }
        else
            fclose(cab); // Si estaba vacío, solo cerramos
    }
}



// Agrega uno o varios caballeros nuevos al final del archivo binario y ordena el registro.
void alta(parchivo cab)
{
    caballero c;
    char rta;

    cab = fopen("caballeros.dat", "ab");

    if (cab != NULL)
    {
        do
        {
            cargar(c);

            fwrite(&c, sizeof(c), 1, cab);
            fflush(cab);

            cout << "\nCABALLERO AGREGADO EXITOSAMENTE" << endl;

            cout << "\nIngresar mas datos S/N: ";
            cin >> rta;

        } while (rta != 'N' && rta != 'n');

        fclose(cab);

        ordenar_archivo();
    }
    else
        cout << "ERROR AL ABRIR EL ARCHIVO" << endl;
}


// Muestra por consola todos los datos detallados de un caballero en particular.
void mostrar(caballero c)
{
    cout << "\nNombre: " << c.nombre << endl;
    cout << "Apellido: " << c.apellido << endl;
    cout << "Apodo: " << c.apodo_unico << endl;
    cout << "Titulo Noble: " << c.titulo_noble << endl;
    cout << "Edad: " << c.edad << endl;
    cout << "Mejor Puntaje: " << c.mejor_puntaje << endl;
    cout << "Puntaje Total: " << c.puntaje_total << endl;
    cout << "Cantidad de desafios ganados: " << c.cantidad_desafios_ganados << endl;
}


// Lee el archivo completo y lista en pantalla la información de todos los caballeros registrados.
void listar(parchivo cab)
{
    caballero c;

    cab = fopen("caballeros.dat", "rb");

    if (cab != NULL)
    {
        fread(&c, sizeof(c), 1, cab);

        if (!feof(cab))
        {
            while (!feof(cab))
            {
                mostrar(c);

                fread(&c, sizeof(c), 1, cab);
            }
        }
        else
            cout << "NO EXISTEN CABALLEROS REGISTRADOS" << endl;

        fclose(cab);
    }
    else
        cout << "NO EXISTEN CABALLEROS REGISTRADOS" << endl;
}


// Busca un caballero por su apodo en el archivo y muestra su información si lo encuentra.
void consultar(parchivo cab, tcad apodo)
{
    caballero c;
    bool encontrado = false;

    cab = fopen("caballeros.dat", "rb");

    if (cab != NULL)
    {
        fread(&c, sizeof(c), 1, cab);

        while (!feof(cab) && encontrado==false)
        {
            if (strcmp(c.apodo_unico, apodo) == 0)
            {
                mostrar(c);
                encontrado = true;
            }

            if (encontrado==false)
                fread(&c, sizeof(c), 1, cab);
        }

        if (encontrado==false)
            cout << "CABALLERO NO ENCONTRADO" << endl;

        fclose(cab);
    }
    else
        cout << "NO EXISTEN CABALLEROS REGISTRADOS" << endl;
}



// Busca un caballero por su apodo y permite modificar sus datos directamente en el archivo binario.
void modificar(parchivo cab, tcad apodo)
{
    caballero c;
    bool encontrado = false;

    cab = fopen("caballeros.dat", "rb+");

    if (cab != NULL)
    {
        fread(&c, sizeof(c), 1, cab);

        while (!feof(cab) && encontrado==false)
        {
            if (strcmp(c.apodo_unico, apodo) == 0)
            {
                mostrar(c);
                cargar2(c);

                fseek(cab, -sizeof(c), SEEK_CUR);
                fwrite(&c, sizeof(c), 1, cab);

                encontrado = true;
            }

            if (encontrado==false)
                fread(&c, sizeof(c), 1, cab);
        }

        if (encontrado==false)
            cout << "CABALLERO NO ENCONTRADO" << endl;

        fclose(cab);
    }
    else
        cout << "NO EXISTEN CABALLEROS REGISTRADOS" << endl;
}


// Elimina un caballero del archivo copiando los registros restantes a un archivo temporal.
void borrar(parchivo cab, tcad apodo)
{
    parchivo temp;
    caballero c;
    bool encontrado = false;

    cab = fopen("caballeros.dat", "rb");

    if (cab != NULL)
    {
        temp = fopen("temporal.dat", "wb");

        if (temp != NULL)
        {
            fread(&c, sizeof(c), 1, cab);

            while (!feof(cab))
            {
                if (strcmp(c.apodo_unico, apodo) == 0)
                    encontrado = true;
                else
                    fwrite(&c, sizeof(c), 1, temp);

                fread(&c, sizeof(c), 1, cab);
            }

            fclose(cab);
            fclose(temp);

            if (encontrado)
            {
                if (remove("caballeros.dat") == 0) 
                {
                    if (rename("temporal.dat", "caballeros.dat") == 0)
                        cout << "CABALLERO ELIMINADO CORRECTAMENTE" << endl;
                    else
                        // Mensaje si falla el rename
                        cout << "ERROR AL REEMPLAZAR EL ARCHIVO." << endl;
                }
                else
                {
                    // Borrar el temporal si falla el remove del original
                    remove("temporal.dat"); 
                    cout << "ERROR AL ELIMINAR EL ARCHIVO ORIGINAL" << endl;
                }
            }
            else
            {
                remove("temporal.dat");
                cout << "CABALLERO NO ENCONTRADO" << endl;
            }
        }
        else
        {
            fclose(cab);
            cout << "ERROR AL CREAR EL ARCHIVO TEMPORAL" << endl;
        }
    }
    else
        cout << "NO EXISTE EL ARCHIVO DE CABALLEROS" << endl;
}


// Recorre el archivo binario completo y retorna la cantidad total de caballeros registrados.
int contar_caballeros()
{
    parchivo cab;
    caballero c;
    int cantidad = 0;

    cab = fopen("caballeros.dat", "rb");

    if (cab != NULL)
    {
        fread(&c, sizeof(c), 1, cab);
        
        while (!feof(cab))
        {
            cantidad++;
            fread(&c, sizeof(c), 1, cab);
        }

        fclose(cab);
    }

    return cantidad;
}


// Actualiza las estadísticas, puntajes y desafíos ganados del caballero ganador en el archivo.
void actualizar_campeon(tcad apodo, int puntaje)
{
    parchivo cab;
    caballero c;
    bool encontrado = false;

    cab = fopen("caballeros.dat", "rb+");

    if (cab != NULL)
    {
        fread(&c, sizeof(c), 1, cab);

        while (!feof(cab) && encontrado==false)
        {
            if (strcmp(c.apodo_unico, apodo) == 0)
            {
                c.puntaje_total = c.puntaje_total + puntaje;
                c.cantidad_desafios_ganados++;

                if (puntaje > c.mejor_puntaje)
                    c.mejor_puntaje = puntaje;

                fseek(cab, -sizeof(c), SEEK_CUR);
                fwrite(&c, sizeof(c), 1, cab);

                encontrado = true;
            }

            if (!encontrado)
                fread(&c, sizeof(c), 1, cab);
        }

        fclose(cab);

        if (encontrado==true)
            cout << "PUNTAJE DEL CAMPEON ACTUALIZADO" << endl;
        else
            cout << "CAMPEON NO ENCONTRADO" << endl;
    }
    else
        cout << "ERROR AL ABRIR EL ARCHIVO" << endl;
}




