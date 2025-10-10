# Práctica 3 — Informática II  

Sistema de Registro de Usuarios para Cajero Electrónico  
![Estado](https://img.shields.io/badge/Estado-Finalizado-brightgreen)

Este proyecto académico fue desarrollado como parte de la **Práctica 3 del curso Informática II**. Implementa un sistema de gestión de usuarios para un cajero electrónico con acceso diferenciado para administradores y clientes. El sistema fue desarrollado en dos versiones: una usando arreglos de caracteres (`char[]`) y otra usando clases `String`.

El proyecto permite la administración, registro y operación de usuarios en un entorno simulado de cajero electrónico. Incluye validaciones, manejo de excepciones, encriptación y actualización automática de los datos almacenados en archivos.

Los administradores acceden mediante el archivo `sudo.txt`, el cual contiene las credenciales encriptadas. Una vez autenticados, pueden registrar nuevos usuarios en el archivo `usuarios.txt`, con formato `cédula, clave, saldo (COP)`. Los clientes, por su parte, pueden iniciar sesión para consultar su saldo o realizar retiros, pagando un costo de 1000 COP por cada operación. Todas las modificaciones se reflejan directamente en el archivo de usuarios.

Las transacciones se gestionan de manera segura, aplicando métodos de codificación vistos en clase. El sistema verifica el formato y contenido de los datos de entrada, garantizando integridad y consistencia de la información. Cada operación incluye manejo de errores y validaciones automáticas que previenen accesos o formatos inválidos.

El sistema fue desarrollado en dos versiones: 

1. Usando arreglos de caracteres (`char[]`).
2. Usando clases `String`.

---

## Funcionalidades

### 1. Acceso como administrador

- El acceso se valida mediante el archivo `sudo.txt`.
- El archivo contiene usuario y contraseña encriptados.
- Se realiza la verificación abriendo el archivo y comparando con la clave ingresada.

### 2. Registro de usuarios

- Una vez validado el administrador, se pueden registrar usuarios del cajero con el siguiente formato:

cédula, clave, saldo (COP)

### 3. Operaciones de usuarios

Los clientes del sistema pueden:

- Consultar saldo.
- Retirar dinero especificando la cantidad deseada.

### 4. Actualización de la información

- Cada ingreso al cajero (consultar o retirar) tiene un costo de 1000 COP.
- El saldo del usuario se actualiza en cada transacción.

### 5. Transacciones seguras

- Toda la información (claves, registros, transacciones) se almacena encriptada.
- Se aplican dos métodos de codificación vistos en clase.

---

## Archivos del sistema

- `sudo.txt` → contiene usuario y clave del administrador encriptados.
- `usuarios.txt` → contiene los registros de usuarios (cédula, clave, saldo).
- `main.cpp` → programa principal (dos versiones: con `char[]` y con `String`).
- `funciones.cpp / funciones.h` → funciones auxiliares de encriptación, desencriptación, validaciones y operaciones.

---

## Requisitos implementados

- Dos versiones: manejo con `char[]` y con `String`.
- Métodos de codificación: se implementaron los dos métodos vistos en clase.
- Manipulación de cadenas: uso de funciones de clasificación y modificación.
- Gestión de archivos: lectura/escritura sin errores.
- Manejo de excepciones: se incluyeron al menos 3 excepciones (ej. archivo no encontrado, saldo insuficiente, acceso denegado).
- Lectura de archivo `sudo.txt` para ingreso de administrador.
- Registro, operaciones y actualización de usuarios correctas.
- Uso de GitHub: manejo del repositorio con commits y control de versiones.

---
1. **Clonar el repositorio**
   ```bash
   git clone https://github.com/B-Alejandro/Practica-3.git
   
2. Ingresar como administrador  
Usuario y contraseña validados contra `sudo.txt`.

3. Registrar usuarios  
Ingresar cédula, clave y saldo inicial.

4. Acceso como cliente  
Autenticarse con cédula y clave.  
Realizar operaciones de consulta o retiro (con actualización automática del saldo).

---

## Autores

- Alejandro Bedoya Zuluaga
- Jose Manuel Giraldo Ospina

