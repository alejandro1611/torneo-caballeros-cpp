# ⚔️ La Rueda del Destino: La Batalla de las Sombras

Proyecto desarrollado en **C++** para la materia **Estructura de Datos**, correspondiente a la carrera Analista Programador Universitario de la Universidad Nacional de Jujuy (UNJu).

## 📖 Descripción

*La Rueda del Destino: La Batalla de las Sombras* es un sistema de gestión de caballeros y competencias ambientado en un mundo medieval.

El programa permite administrar un registro de caballeros, organizar desafíos en los que los participantes deben enfrentarse a una rueda de runas y mantener un historial de campeones según sus mejores puntajes.

El proyecto fue desarrollado con el objetivo de aplicar diferentes estructuras de datos, operaciones sobre archivos binarios y administración dinámica de memoria.

## 🎮 Funcionalidades principales

El sistema está dividido en tres módulos principales:

### 1. 🛡️ Orden de Caballeros
Permite administrar el registro de caballeros mediante operaciones de ABMC:

- **Alta:** incorporación de nuevos caballeros.
- **Baja:** eliminación de caballeros registrados.
- **Modificación:** actualización de sus datos.
- **Consulta:** búsqueda de caballeros por su apodo único.
- **Listado:** visualización de los caballeros registrados en orden alfabético.

Los registros se almacenan en un archivo binario (`caballeros.dat`). Para mantener el orden alfabético se utiliza un Árbol Binario de Búsqueda (ABB) auxiliar.

### 2. 🧙 Desafío de Merlín
Permite seleccionar caballeros registrados y enfrentarlos en una competencia basada en una rueda de runas.

Cada participante comienza con dos vidas y debe superar los efectos de las diferentes runas:

| Runa | Nombre | Efecto |
|---|---|---|
| M | Aurum | Suma 10 puntos. |
| T | Veridian | Duplica el puntaje actual. |
| C | Vita | Otorga un protector, hasta un máximo de 3. |
| B | Calamitas | Consume un protector o, si no tiene, resta una vida. |

El desafío continúa hasta que queda un único participante o se agotan las runas. En caso de empate en el puntaje final, se realizan tiradas aleatorias para determinar al campeón.

### 3. 🏆 Mural de Campeones
Permite consultar el historial de campeones y visualizar un ranking según el mejor puntaje obtenido.

El ranking puede mostrarse en dos sentidos:

- **Creciente:** de menor a mayor puntaje.
- **Decreciente:** de mayor a menor puntaje.

Se utiliza un ABB organizado por puntaje, con el apodo único como segundo criterio de ordenamiento para contemplar posibles empates.

## 🧩 Estructuras de datos implementadas

Uno de los principales objetivos del proyecto es aplicar distintas estructuras de datos de acuerdo con las necesidades de cada módulo.

| Estructura | Aplicación |
|---|---|
| Árbol Binario de Búsqueda (ABB) | Ordenamiento de caballeros y ranking de campeones. |
| Cola circular | Organización y rotación de turnos durante los desafíos. |
| Pila dinámica | Administración individual de protectores de cada participante. |
| Lista doblemente enlazada circular | Representación de la rueda de runas. |
| Arreglos | Almacenamiento temporal de participantes y resolución de empates. |
| Archivos binarios | Persistencia de los registros de caballeros. |

También se implementan operaciones recursivas para la inserción, recorrido y liberación de memoria de los árboles.

## 📁 Organización del proyecto

El código se encuentra modularizado mediante archivos de cabecera (`.hpp`):

| Archivo | Responsabilidad |
|---|---|
| `main.cpp` | Programa principal y navegación por los menús. |
| `tipos.hpp` | Definición de estructuras, tipos y constantes. |
| `ABBcaballeros.hpp` | Operaciones del ABB de caballeros. |
| `pila.hpp` | Operaciones de la pila de protectores. |
| `cola.hpp` | Operaciones de la cola de participantes. |
| `rueda.hpp` | Operaciones de la rueda de runas. |
| `caballeros.hpp` | Gestión del registro de caballeros. |
| `desafio.hpp` | Lógica y desarrollo de los desafíos. |
| `campeones.hpp` | Gestión y visualización del mural de campeones. |

## ⚙️ Tecnologías utilizadas

- **Lenguaje:** C++
- **Archivos:** archivos binarios mediante operaciones de lectura y escritura.
- **Memoria dinámica:** `new` y `delete`.
- **Programación:** modular y recursiva.
- **Control de versiones:** Git y GitHub.

## 🚀 Compilación y ejecución

Es necesario contar con un compilador de C++, como GCC o Clang.

Desde la terminal, ubicarse en la carpeta del proyecto y ejecutar:

```bash
g++ -std=c++11 main.cpp -o rueda_destino
```

Luego, ejecutar el programa:

**macOS / Linux:**
```bash
./rueda_destino
```

**Windows:**
```bash
rueda_destino.exe
```

> Nota: la compilación debe realizarse desde la carpeta que contiene los archivos del proyecto. Los archivos binarios de datos se utilizan durante la ejecución.

## 🎯 Objetivos académicos

Este trabajo integrador permitió poner en práctica los contenidos de la materia Estructura de Datos, especialmente:

- Implementación y manipulación de estructuras dinámicas.
- Uso de árboles binarios de búsqueda.
- Administración de pilas y colas.
- Manejo de listas enlazadas circulares.
- Lectura y escritura de archivos binarios.
- Recursividad y liberación de memoria dinámica.
- Modularización y organización del código.

## 👨‍💻 Autor

**Alejandro Imanol Cruz**

Analista Programador Universitario – Universidad Nacional de Jujuy (UNJu).

Proyecto académico desarrollado en 2026 para la materia Estructura de Datos.
