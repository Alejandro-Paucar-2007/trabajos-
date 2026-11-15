#include <stdio.h>
#include "funciones.h"

float validarFloatRango(float a, float b){
    float num;
    int val;
    do
    {
        val = scanf("%f",&num);
        while((getchar())!='\n');
        if (num < a || num > b || val != 1)
        {
            printf("Error: El valor ingresado es incorrecto\n");
        }
        
    } while (num < a || num > b || val != 1);
    return num;
}

void leercadena(char *cadena, int n){
    fgets(cadena, n, stdin);
    int i = 0;
    while (cadena[i] != '\0') {
        if (cadena[i] == '\n') {
            cadena[i] = '\0';
            break;
        }
        i++;
    }
}

void recortarCadena(char *cad){
    int inicio = 0, fin = 0, i = 0;
    while (cad[inicio] == ' ' || cad[inicio] == '\t') inicio++;
    while (cad[fin] != '\0') fin++;
    while (fin > inicio && (cad[fin - 1] == ' ' || cad[fin - 1] == '\t')) fin--;
    while (inicio < fin) {
        cad[i] = cad[inicio];
        i++;
        inicio++;
    }
    cad[i] = '\0';
}

int compararCadenas(char *cad1, char *cad2){
    int i = 0;
    while (cad1[i] != '\0' && cad2[i] != '\0') {
        char c1 = cad1[i];
        char c2 = cad2[i];
        
        if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
        
        if (c1 != c2) {
            return 0;
        }
        i++;
    }
    return (cad1[i] == '\0' && cad2[i] == '\0') ? 1 : 0;
}


void copiarCadena(char *destino, char *origen){
    int i = 0;
    while (origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

void registrarProducto(int *id, char nombres[][100], int *demanda, float *tiempo_u, float *recursos_u, int *contP){
    if (*contP >= 5) {
        printf("Error: Ya se registraron los 5 productos maximos de la fabrica.\n");
        return;
    }
    printf("Ingrese los datos del producto %d:\n", *contP + 1);
    id[*contP] = *contP;
    printf("Nombre del producto: ");
    leerNombreProducto(nombres, *contP, nombres[*contP], -1);
    printf("Cantidad demandada: ");
    demanda[*contP] = (int)validarFloatRango(1, 100000);
    printf("Tiempo de fabricacion por unidad (horas): ");
    tiempo_u[*contP] = validarFloatRango(0.01, 10000);
    printf("Recursos necesarios por unidad: ");
    recursos_u[*contP] = validarFloatRango(0.01, 10000);
    (*contP)++;
}

int existeNombre(char nombres[][100], int contP, char *nombre, int ignorar){
    for (int i = 0; i < contP; i++) {
        if (i != ignorar && compararCadenas(nombre, nombres[i]) == 1) {
            return 1;
        }
    }
    return 0;
}

void leerNombreProducto(char nombres[][100], int contP, char *destino, int ignorar){
    char temp[100];
    int valido;
    do {
        valido = 1;
        leercadena(temp, 100);
        recortarCadena(temp);
        if (temp[0] == '\0') {
            printf("Error: El nombre no puede estar vacio.\n");
            valido = 0;
        } else if (existeNombre(nombres, contP, temp, ignorar)) {
            printf("Error: Ya existe un producto con ese nombre.\n");
            valido = 0;
        }
        if (!valido) {
            printf("Ingrese nuevamente el nombre: ");
        }
    } while (!valido);
    copiarCadena(destino, temp);
}

void mostrarProductos(int *id, char nombres[][100], int *demanda, float *tiempo_u, float *recursos_u, int n, int contP){
    if (contP == 0) {
        printf("No hay productos registrados.\n");
        return;
    }
    printf("ID\t\tNombre\t\tDemanda\t\tTiempo/U\tRecursos/U\n");
    for (int i = n; i < contP; i++)
    {
        printf("%d\t\t%s\t\t%d\t\t%.2f\t\t%.2f\n", id[i],nombres[i],demanda[i],tiempo_u[i],recursos_u[i]);
    }
}

int buscarProducto(int *id, char nombres[][100], int *demanda, float *tiempo_u, float *recursos_u, int contP){
    if (contP == 0) {
        printf("Error: No hay productos registrados para buscar.\n");
        return -1;
    }

    printf("Seleccione el metodo de busqueda 1.ID/2.Nombre: ");
    int opc = (int)validarFloatRango(1, 2);
    int iden = -1;
    switch (opc)
    {
    case 1:
        printf("Ingrese un numero del 0-%d: ", contP - 1);
        iden = (int)validarFloatRango(0, contP - 1);
        mostrarProductos(id, nombres, demanda, tiempo_u, recursos_u, iden, iden + 1);
        break;
    case 2:
       printf("Ingrese el nombre del producto: ");
        char nombreB[100];
        leercadena(nombreB, 100);
        recortarCadena(nombreB);
        if (nombreB[0] == '\0') {
            printf("Error: El nombre no puede estar vacio.\n");
        } else {
            for (int i = 0; i < contP; i++)
            {
                if(compararCadenas(nombreB, nombres[i]) == 1){
                    mostrarProductos(id, nombres, demanda, tiempo_u, recursos_u, i, i + 1);
                    iden = i;
                    break;
                }
            }
            if (iden == -1) {
                printf("Error: Producto no encontrado.\n");
            }
        }
        break;
    default:
        break;
    }
    return iden;
}

void editarProducto(int *id, char nombres[][100], int *demanda, float *tiempo_u, float *recursos_u, int contP){
    if (contP == 0) {
        printf("Error: No hay productos registrados para editar.\n");
        return;
    }
    printf("--- Buscar producto a editar ---\n");
    int posicion = buscarProducto(id, nombres, demanda, tiempo_u, recursos_u, contP);
    
    if (posicion != -1) {
        printf("Seleccione que desea editar:\n");
        printf("1.Nombre\n2.Demanda\n3.Tiempo de fabricacion\n4.Recursos necesarios\n5.Todo\n>> ");
        int opc = (int)validarFloatRango(1, 5);
        switch (opc)
        {
        case 1:
            printf("Nuevo nombre: ");
            leerNombreProducto(nombres, contP, nombres[posicion], posicion);
            break;
        case 2:
            printf("Nueva cantidad demandada: ");
            demanda[posicion] = (int)validarFloatRango(1, 100000);
            break;
        case 3:
            printf("Nuevo tiempo de fabricacion: ");
            tiempo_u[posicion] = validarFloatRango(0.01, 10000);
            break;
        case 4:
            printf("Nuevos recursos necesarios: ");
            recursos_u[posicion] = validarFloatRango(0.01, 10000);
            break;
        case 5:
            printf("Nuevo nombre: ");
            leerNombreProducto(nombres, contP, nombres[posicion], posicion);
            printf("Nueva cantidad demandada: ");
            demanda[posicion] = (int)validarFloatRango(1, 100000);
            printf("Nuevo tiempo de fabricacion: ");
            tiempo_u[posicion] = validarFloatRango(0.01, 10000);
            printf("Nuevos recursos necesarios: ");
            recursos_u[posicion] = validarFloatRango(0.01, 10000);
            break;
        default:
            break;
        }
        printf("Producto editado correctamente.\n");
    }
}

void eliminarProducto(int *id, char nombres[][100], int *demanda, float *tiempo_u, float *recursos_u, int *contP){
    if (*contP == 0) {
        printf("Error: No hay productos registrados para eliminar.\n");
        return;
    }
    printf("--- Buscar producto a eliminar ---\n");
    int posicion = buscarProducto(id, nombres, demanda, tiempo_u, recursos_u, *contP);
    
    if (posicion != -1) {
        for (int i = posicion; i < (*contP) - 1; i++) {
            copiarCadena(nombres[i], nombres[i + 1]);
            demanda[i] = demanda[i + 1];
            tiempo_u[i] = tiempo_u[i + 1];
            recursos_u[i] = recursos_u[i + 1];
        }
        (*contP)--;
        for (int i = 0; i < *contP; i++) {
            id[i] = i;
        }
        printf("Producto eliminado correctamente.\n");
    }
}

void evaluarViabilidad(int *demanda, float *tiempo_u, float *recursos_u, int contP){
    if (contP == 0) {
        printf("Error: Primero debe registrar productos.\n");
        return;
    }

    float tiempoDisponible, recursosDisponibles;
    float tiempoTotal = 0, recursosTotales = 0;

    printf("Ingrese el limite de tiempo de produccion disponible en la fabrica (horas): ");
    tiempoDisponible = validarFloatRango(0.1, 1000000);
    printf("Ingrese la cantidad limitada de recursos disponibles en la fabrica: ");
    recursosDisponibles = validarFloatRango(0.1, 1000000);

    for (int i = 0; i < contP; i++) {
        tiempoTotal += demanda[i] * tiempo_u[i];
        recursosTotales += demanda[i] * recursos_u[i];
    }

    printf("\n--- Resultados de Produccion ---\n");
    printf("Tiempo total de fabricacion requerido: %.2f horas\n", tiempoTotal);
    printf("Cantidad total de recursos necesarios: %.2f unidades\n", recursosTotales);

    if (tiempoTotal <= tiempoDisponible && recursosTotales <= recursosDisponibles) {
        printf("Resultado: La fabrica SI puede cumplir con la demanda.\n");
    } else {
        printf("Resultado: La fabrica NO puede cumplir con la demanda.\n");
        if (tiempoTotal > tiempoDisponible) {
            printf("- Excede el tiempo disponible por %.2f horas.\n", tiempoTotal - tiempoDisponible);
        }
        if (recursosTotales > recursosDisponibles) {
            printf("- Excede los recursos disponibles por %.2f unidades.\n", recursosTotales - recursosDisponibles);
        }
    }
}