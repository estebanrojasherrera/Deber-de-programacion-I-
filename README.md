# Taller-S4-programacion-I-
**Sistema de Optimización de Producción**

Ingeniería en Inteligencia Artificial - UDLA. 

Este sistema permite gestionar y optimizar la línea de producción de una fábrica para un máximo de 5 productos. El proyecto destaca por su enfoque en la **Planificación Operativa**, permitiendo evaluar la viabilidad técnica de la demanda mediante el cálculo automatizado de requerimientos de tiempo y recursos frente a la capacidad real de la planta.

## Funcionalidades
* **Gestión de Productos:** Ingreso, visualización, edición y eliminación de datos de manufactura en memoria.
* **Análisis de Capacidad:** Cálculo automatizado del tiempo total (horas) y recursos necesarios para cumplir con la demanda proyectada.
* **Simulación de Viabilidad:** Motor de validación que contrasta los requerimientos totales contra la disponibilidad de la fábrica, reportando superávits o déficits exactos.
* **Motor de Búsqueda:** Localización manual de productos por coincidencia exacta de caracteres para la posterior edición o baja del registro.
* **Robustez de Interfaz:** Control estricto del buffer de entrada (`stdin`) mediante funciones personalizadas de limpieza para evitar desbordamientos o saltos de lectura.

---
**Autores:**
* Matías Moya
* Esteban Rojas
* Anthony Loor
