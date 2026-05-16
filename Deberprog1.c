#include <stdio.h>
#include <string.h>
 
#define MAX_PRODUCTOS 5
#define MAX_NOMBRE 50
 
// Arreglos paralelos para almacenar datos de productos
char nombres[MAX_PRODUCTOS][MAX_NOMBRE];
int cantidades[MAX_PRODUCTOS];
float tiempo_fab[MAX_PRODUCTOS];
int recursos[MAX_PRODUCTOS];
int num_productos = 0;
 
// Prototipo de funciones
void ingresarProducto();
void mostrarProductos();
int buscarProducto(char nombre[]);
void editarProducto();
void eliminarProducto();
void calcularTotales();
int verificarCapacidad(float tiempo_disponible, int recursos_disponibles);
void limpiarBuffer();
 
int main() {
    int opcion;
    do {
        printf("\n=== SISTEMA DE OPTIMIZACIÓN DE PRODUCCIÓN ===\n");
        printf("1. Ingresar producto\n");
        printf("2. Mostrar productos\n");
        printf("3. Editar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Calcular totales y verificar capacidad\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();
 
        switch(opcion) {
            case 1: ingresarProducto(); break;
            case 2: mostrarProductos(); break;
            case 3: editarProducto(); break;
            case 4: eliminarProducto(); break;
            case 5: calcularTotales(); break;
            case 6: printf("Saliendo del sistema...\n"); break;
            default: printf("Opción inválida.\n");
        }
    } while(opcion != 6);
    return 0;
}
 
void limpiarBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
 
void ingresarProducto() {
    if(num_productos >= MAX_PRODUCTOS) {
        printf("Se alcanzó el máximo de %d productos.\n", MAX_PRODUCTOS);
        return;
    }
    printf("Nombre del producto: ");
    fgets(nombres[num_productos], MAX_NOMBRE, stdin);
    nombres[num_productos][strcspn(nombres[num_productos], "\n")] = 0;
 
    printf("Cantidad demandada: ");
    scanf("%d", &cantidades[num_productos]);
    printf("Tiempo de fabricación por unidad (horas): ");
    scanf("%f", &tiempo_fab[num_productos]);
    printf("Recursos por unidad: ");
    scanf("%d", &recursos[num_productos]);
    limpiarBuffer();
    num_productos++;
    printf("Producto ingresado correctamente.\n");
}
 
void mostrarProductos() {
    if(num_productos == 0) {
        printf("No hay productos registrados.\n");
        return;
    }
    printf("\n%-5s %-25s %-10s %-15s %-10s\n",
        "N°", "Nombre", "Cantidad", "Tiempo/u (h)", "Recursos/u");
    printf("--------------------------------------------------------------\n");
    for(int i = 0; i < num_productos; i++) {
        printf("%-5d %-25s %-10d %-15.2f %-10d\n",
            i+1, nombres[i], cantidades[i], tiempo_fab[i], recursos[i]);
    }
}
 
int buscarProducto(char nombre[]) {
    for(int i = 0; i < num_productos; i++) {
        // Búsqueda manual carácter por carácter
        int igual = 1;
        for(int j = 0; nombre[j] != '\0' || nombres[i][j] != '\0'; j++) {
            if(nombre[j] != nombres[i][j]) { igual = 0; break; }
        }
        if(igual) return i;
    }
    return -1;
}
 
void editarProducto() {
    char buscar[MAX_NOMBRE];
    printf("Nombre del producto a editar: ");
    fgets(buscar, MAX_NOMBRE, stdin);
    buscar[strcspn(buscar, "\n")] = 0;
    int idx = buscarProducto(buscar);
    if(idx == -1) {
        printf("Producto no encontrado.\n");
        return;
    }
    printf("Nuevo nombre (actual: %s): ", nombres[idx]);
    fgets(nombres[idx], MAX_NOMBRE, stdin);
    nombres[idx][strcspn(nombres[idx], "\n")] = 0;
    printf("Nueva cantidad (actual: %d): ", cantidades[idx]);
    scanf("%d", &cantidades[idx]);
    printf("Nuevo tiempo/u (actual: %.2f): ", tiempo_fab[idx]);
    scanf("%f", &tiempo_fab[idx]);
    printf("Nuevos recursos/u (actual: %d): ", recursos[idx]);
    scanf("%d", &recursos[idx]);
    limpiarBuffer();
    printf("Producto editado correctamente.\n");
}
 
void eliminarProducto() {
    char buscar[MAX_NOMBRE];
    printf("Nombre del producto a eliminar: ");
    fgets(buscar, MAX_NOMBRE, stdin);
    buscar[strcspn(buscar, "\n")] = 0;
    int idx = buscarProducto(buscar);
    if(idx == -1) {
        printf("Producto no encontrado.\n");
        return;
    }
    // Desplazar elementos hacia atrás
    for(int i = idx; i < num_productos - 1; i++) {
        strcpy(nombres[i], nombres[i+1]);
        cantidades[i] = cantidades[i+1];
        tiempo_fab[i] = tiempo_fab[i+1];
        recursos[i] = recursos[i+1];
    }
    num_productos--;
    printf("Producto eliminado correctamente.\n");
}
 
void calcularTotales() {
    if(num_productos == 0) {
        printf("No hay productos registrados.\n");
        return;
    }
    float tiempo_total = 0;
    int recursos_total = 0;
    for(int i = 0; i < num_productos; i++) {
        tiempo_total += tiempo_fab[i] * cantidades[i];
        recursos_total += recursos[i] * cantidades[i];
    }
    printf("\n=== RESULTADOS DE PRODUCCIÓN ===\n");
    printf("Tiempo total requerido: %.2f horas\n", tiempo_total);
    printf("Recursos totales necesarios: %d unidades\n", recursos_total);
 
    float t_disp;
    int r_disp;
    printf("\nIngrese tiempo disponible (horas): ");
    scanf("%f", &t_disp);
    printf("Ingrese recursos disponibles: ");
    scanf("%d", &r_disp);
    limpiarBuffer();
 
    if(verificarCapacidad(t_disp, r_disp)) {
        printf("\n✓ La fábrica PUEDE cumplir con la demanda.\n");
        printf("  Tiempo sobrante: %.2f h | Recursos sobrantes: %d\n",
            t_disp - tiempo_total, r_disp - recursos_total);
    } else {
        printf("\n✗ La fábrica NO puede cumplir con la demanda.\n");
        if(tiempo_total > t_disp)
            printf("  Déficit de tiempo: %.2f horas\n", tiempo_total - t_disp);
        if(recursos_total > r_disp)
            printf("  Déficit de recursos: %d unidades\n", recursos_total - r_disp);
    }
}
 
int verificarCapacidad(float tiempo_disponible, int recursos_disponibles) {
    float tiempo_total = 0;
    int recursos_total = 0;
    for(int i = 0; i < num_productos; i++) {
        tiempo_total += tiempo_fab[i] * cantidades[i];
        recursos_total += recursos[i] * cantidades[i];
    }
    return (tiempo_total <= tiempo_disponible && recursos_total <= recursos_disponibles);
}
