import tkinter as tk
from tkinter import ttk
import parqueadero

TOTAL_CELDAS = 20

ventana = tk.Tk()
ventana.title("Visualizador Parqueadero")
ventana.geometry("700x500")

titulo = tk.Label(
    ventana,
    text="Estado del Parqueadero",
    font=("Arial", 18, "bold")
)
titulo.pack(pady=10)

resumen = tk.Label(
    ventana,
    text="Ocupadas: 0 | Disponibles: 20",
    font=("Arial", 12, "bold")
)
resumen.pack(pady=5)

celdas_libres_label = tk.Label(
    ventana,
    text="Celdas libres: 1, 2, 3, ..., 20",
    font=("Arial", 10),
    wraplength=650,
    justify="center"
)
celdas_libres_label.pack(pady=5)

tabla = ttk.Treeview(
    ventana,
    columns=("placa", "hora", "celda"),
    show="headings"
)

tabla.heading("placa", text="Placa")
tabla.heading("hora", text="Hora Entrada")
tabla.heading("celda", text="Celda Ocupada")

tabla.pack(fill="both", expand=True, padx=20, pady=20)

def actualizar():
    for item in tabla.get_children():
        tabla.delete(item)

    datos = parqueadero.obtenerDatosParqueadero()
    lineas = datos.strip().split("\n")

    celdas_ocupadas = set()

    for linea in lineas:
        if linea.strip() != "":
            partes = linea.split("|")
            if len(partes) == 3:
                placa, hora, celda = partes
                tabla.insert("", "end", values=(placa, hora, celda))

                try:
                    celdas_ocupadas.add(int(celda))
                except ValueError:
                    pass

    celdas_libres = []

    for i in range(1, TOTAL_CELDAS + 1):
        if i not in celdas_ocupadas:
            celdas_libres.append(i)

    resumen.config(
        text=f"Ocupadas: {len(celdas_ocupadas)} | Disponibles: {len(celdas_libres)}"
    )

    celdas_libres_label.config(
        text="Celdas libres: " + ", ".join(map(str, celdas_libres))
    )

    ventana.after(1000, actualizar)

actualizar()
ventana.mainloop()
