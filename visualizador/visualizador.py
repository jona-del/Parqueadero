import tkinter as tk
from tkinter import ttk
import os
from ctypes import CDLL, c_char_p

os.add_dll_directory(r"C:\msys64\ucrt64\bin")

ruta_dll = os.path.abspath("dll/parqueadero_dll.dll")
dll = CDLL(ruta_dll)
dll.obtenerDatosParqueadero.restype = c_char_p

ventana = tk.Tk()
ventana.title("Visualizador Parqueadero")
ventana.geometry("600x400")

titulo = tk.Label(
    ventana,
    text="Estado del Parqueadero",
    font=("Arial", 18, "bold")
)
titulo.pack(pady=10)

tabla = ttk.Treeview(
    ventana,
    columns=("placa", "hora", "celda"),
    show="headings"
)

tabla.heading("placa", text="Placa")
tabla.heading("hora", text="Hora Entrada")
tabla.heading("celda", text="Celda")

tabla.pack(fill="both", expand=True, padx=20, pady=20)

def actualizar():
    for item in tabla.get_children():
        tabla.delete(item)

    datos = dll.obtenerDatosParqueadero().decode("utf-8")

    lineas = datos.strip().split("\n")

    for linea in lineas:
        if linea.strip() != "":
            partes = linea.split("|")
            if len(partes) == 3:
                placa, hora, celda = partes
                tabla.insert("", "end", values=(placa, hora, celda))

    ventana.after(1000, actualizar)

actualizar()
ventana.mainloop()