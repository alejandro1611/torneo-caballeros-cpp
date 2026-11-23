typedef char tcad[30];

//Define un puntero a archivo para gestionar las operaciones de lectura y escritura.
typedef FILE *parchivo;

//Almacena la información completa y estadísticas de cada caballero del archivo binario.
typedef struct caballero
{
    tcad apellido;
    tcad nombre;
    tcad apodo_unico; // campo clave
    tcad titulo_noble;
    int edad;
    int mejor_puntaje;
    int puntaje_total;
    int cantidad_desafios_ganados;
};


// ABB de caballeros
typedef struct tnodo_caballero *pnodo_caballero;
typedef struct tnodo_caballero{
    caballero caballero_completo;
    pnodo_caballero izq;
    pnodo_caballero der;
};

// Agrupa los contadores numéricos para calcular la proporción de cada tipo de runa en la rueda.
typedef struct tcontador_runas {
    int Aurum;
    int Veridian;
    int Vita;
    int Calamitas;
};

//Representa un nodo de la lista circular doble que compone la rueda con su runa y punteros al siguiente y anterior.
typedef struct tnodorueda *prueda;
typedef struct tnodorueda
{
    char runa;
    prueda sig;
    prueda ant;
};

//Representa un nodo individual de la pila encargado de almacenar un protector del jugador.
typedef struct tnodopila *ppila;
typedef struct tnodopila
{
    int dato;
    ppila sig;
};

//Almacena el estado dinámico y estadísticas en tiempo de ejecución de un participante durante el desafío.
typedef struct tjugador
{
    tcad apodo;
    int vidas;
    int puntaje;
    ppila tope;
    int cantidad_protectores;
};


const int MAX_JUGADORES=20;

typedef int tindices[MAX_JUGADORES]; // Arreglo de índices numéricos para gestionar desempates.
typedef tjugador tparticipantes[MAX_JUGADORES]; // Arreglo que almacena temporalmente a los participantes sobrevivientes.

typedef tjugador telegidos[MAX_JUGADORES]; // Arreglo que contiene a los caballeros seleccionados para la partida.
typedef tjugador tcola_jugadores[MAX_JUGADORES]; // Arreglo base utilizado internamente por la cola circular de jugadores

//Define la estructura de cola circular estática para gestionar los turnos de los jugadores en las rondas.
typedef struct tcola
{
    tcola_jugadores jugadores;
    int frente;
    int final;
    int cantidad;
};



