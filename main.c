#include <stdio.h>
#include "funciones.h"

int main (int argc, char *argv[]) {

    int id[5];
    char nombres[5][100];
    int demanda[5];
    float tiempo_u[5];
    float recursos_u[5];
    int contP = 0, opc, opc2;

    do
    {
        printf("Seleccione una opcion:\n");
        printf("1.Registrar producto\n");
        printf("2.Mostrar productos\n");
        printf("3.Buscar producto\n");
        printf("4.Editar producto\n");
        printf("5.Eliminar producto\n");
        printf("6.Calcular tiempo, recursos y viabilidad\n");
        printf(">> ");
        opc = (int)validarFloatRango(1, 6);
        switch (opc)
        {
        case 1:
            registrarProducto(id, nombres, demanda, tiempo_u, recursos_u, &contP);
            break;
        case 2:
            mostrarProductos(id, nombres, demanda, tiempo_u, recursos_u, 0, contP);
            break;
        case 3:
            buscarProducto(id, nombres, demanda, tiempo_u, recursos_u, contP);
            break;
        case 4:
            editarProducto(id, nombres, demanda, tiempo_u, recursos_u, contP);
            break;
        case 5:
            eliminarProducto(id, nombres, demanda, tiempo_u, recursos_u, &contP);
            break;
        case 6:
            evaluarViabilidad(demanda, tiempo_u, recursos_u, contP);
            break;
        default:
            break;
        }
        printf("Desea seleccionar otra opcion 1.Si/2.No: ");
        opc2 = (int)validarFloatRango(1, 2);
    } while (opc2 == 1);

    return 0;
}