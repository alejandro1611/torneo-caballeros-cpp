/* Trabajo Final Integrador 2026 - Estructura de Datos
   La Rueda del Destino
   Alumno: Cruz, Alejandro Imanol
   DNI: 46175538
   LU: APU005989

   Archivo: main.cpp - menus principales y flujo del programa */

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

#include "tipos.hpp"
#include "ABBcaballeros.hpp"
#include "pila.hpp"
#include "cola.hpp"
#include "rueda.hpp"
#include "caballeros.hpp"
#include "desafio.hpp"
#include "campeones.hpp"

// Prototipos del Menu principal y los submenús
void menu_principal(char &op);
void submenu_orden_caballeros();
void submenu_el_desafio_de_merlin();


//Punto de entrada del programa. Inicializa la semilla aleatoria y lanza el menú principal.
int main()
{

    srand(time(NULL));
    char opcion;

    do
    {
        menu_principal(opcion);
        switch (opcion)
        {
        case '1':
            submenu_orden_caballeros();
            break;
        case '2':
            if (contar_caballeros() >= 2)
                submenu_el_desafio_de_merlin();
            else
                cout << "SE NECESITAN AL MENOS 2 CABALLEROS REGISTRADOS" << endl;
            break;
        case '3':
            campeones_legendarios();
            break;
        case '4':
            cout << "Saliendo del programa..." << endl; 
            /* No liberamos aqui las estructuras ya que cada operación 
            libera lo que usa al finalizar (Listas, Pilas, ABB, etc) */
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
        }
    } while (opcion != '4');

    return 0;
}

void menu_principal(char &op)
{
    cout << "\n****MENU PRINCIPAL****" << endl;
    cout << "1. La Orden de Caballeros" << endl;
    cout << "2. El desafio de Merlin" << endl;
    cout << "3. El mural de Campeones" << endl;
    cout << "4. Salir" << endl;
    cout << "Ingrese su opcion: ";
    cin >> op;
}


//ABMC=Altas-Bajas-Modificaciones-Consultas
void submenu_orden_caballeros() //Gestiona el submenú para las operaciones de ABMC sobre el archivo de caballeros.
{
    parchivo cab=NULL;
    char opcion;
    tcad apodo;
    do
    {
        cout << "\n****SUBMENU: La Orden de Caballeros****" << endl;
        cout << "a) Agregar Caballero" << endl;
        cout << "b) Consultar Caballero" << endl;
        cout << "c) Modificar Caballero" << endl;
        cout << "d) Listar Caballeros" << endl;
        cout << "e) Eliminar Caballero" << endl;
        cout << "f) Regresar al menu principal" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 'a':
            cout << "\nAgregar caballero" << endl;
            alta(cab);
            break;
        case 'b':
            cout << "\nConsultar caballero" << endl;
            cout << "Ingrese APODO a consultar:";
            cin.ignore();
            cin.getline(apodo, 30);
            consultar(cab, apodo);
            break;
        case 'c':
            cout << "\nModificar caballero" << endl;
            cout << "Ingrese APODO a modificar:";
            cin.ignore();
            cin.getline(apodo, 30);
            modificar(cab, apodo);
            break;
        case 'd':
            cout << "\nListado Caballeros" << endl;
            listar(cab);
            break;
        case 'e':
            cout << "\nEliminar caballero" << endl;
            cout << "Ingrese APODO a eliminar:";
            cin.ignore();
            cin.getline(apodo, 30);
            borrar(cab, apodo);
            break;
        case 'f':
            cout << "\nRegresando al menu principal..." << endl;
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
        }
    } while (opcion != 'f');
}


/*submenu_el_desafio_de_Merlin: Administra la preparación y ejecución de las partidas, garantizando 
la correcta validación de las estructuras dinámicas (Rueda) y los jugadores elegidos.*/
void submenu_el_desafio_de_merlin()
{
    char opcion;
    telegidos elegidos;
    int cantidad = 0;
    prueda r;

    inicializar_rueda(r);

    do
    {
        cout << "\n****SUBMENU: El desafio de Merlin****" << endl;
        cout << "a) Elegir caballeros" << endl;
        cout << "b) Crear y Mostrar la Rueda del Destino" << endl;
        cout << "c) Iniciar el Desafio de Merlin" << endl;
        cout << "d) Regresar al menu principal" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 'a':
            liberar_rueda(r);
            elegir_caballeros(elegidos, cantidad);
            break;

        case 'b':
            if (cantidad>=2)
            {
                cargar_aleatoriamente(r, cantidad);
                cout << "\n**** RUEDA DEL DESTINO ****" << endl;
                mostrar_rueda(r);
            }
            else
                cout << "PRIMERO DEBE ELEGIR LOS CABALLEROS" << endl;
            break;
        case 'c':
            if (cantidad >= 2 && r != NULL) // Validamos la cantidad y si la rueda existe en memoria
            {
                jugar_desafio(r, elegidos, cantidad);

                /* DECISIÓN DE DISEÑO: Después de cada partida, se fuerza a 0 la cantidad de 
                jugadores elegidos y se libera la rueda. Esto asegura que la selección se borre 
                totalmente, obligando al usuario a elegir nuevos participantes y evitando 
                arrastrar datos basuras o estados obsoletos en la siguiente partida.*/

                liberar_rueda(r);
                cantidad = 0;
            }
            else
                cout << "DEBE ELEGIR LOS CABALLEROS Y CREAR LA RUEDA PRIMERO" << endl;
            break;
        case 'd':
            liberar_rueda(r);
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
        }
    } while (opcion != 'd');
}
