# Este script genera el archivo informacion_archivos_repositorio.csv, 
# el cual contiene información del estado de todos los archivos del 
# repositorio Programación, antes de y en su creación.
#
# Actualmente solo se conserva como documentación y referencia, ya que 
# sus archivos de entrada no están disponibles.

import pandas as pd
pd.options.display.max_columns = 10
import numpy as np
import re

# Importar CSV's
df_todos_orig = pd.read_csv("todos_archivos_carpeta_original.csv", sep='|')
df_todos_repo = pd.read_csv("todos_archivos_commit_0.csv", sep='|')

# Registros adicionales de cada uno
set_rutas_orig = set(df_todos_orig["ruta"])
set_rutas_repo = set(df_todos_repo["ruta"])
adicionales_orig = set_rutas_orig - set_rutas_repo
adicionales_repo = set_rutas_repo - set_rutas_orig

# Construir CSV final

# Funciones para procesamiento de tabla
def obtener_nombre_archivo(ruta):
    prueba_patron_1 = re.search(r".*[^.]/([^/]+)$", ruta)
    prueba_patron_2 = re.search(r"\./(.+)$", ruta)
    
    if prueba_patron_1: return prueba_patron_1.group(1)
    elif prueba_patron_2: return prueba_patron_2.group(1)
    else: return "N/A"

def obtener_ruta(ruta):
    prueba_patron_1 = re.search(r"(.*[^.]/)[^/]+$", ruta)
    prueba_patron_2 = re.search(r"\./.+$", ruta)
    
    if prueba_patron_1: return prueba_patron_1.group(1)
    elif prueba_patron_2: return "./"
    else: return "total"

def es_muestreado(tamano_orig, tamano_repo, estatus_commit_0):
    if tamano_orig != tamano_repo and estatus_commit_0 == "monitoreado":
        return "monitoreado_muestreado"
    else: 
        return estatus_commit_0

def es_generado(nombre_archivo):
    casos_particulares = {
        "MallasLatex.tex", 
        "01MallasLatex.tex", 
        "GraficadorMatricesGnuplot.gpl", 
        "casos.pl"
    }
    if re.fullmatch(r".*\.(aux|log|out|div|gz|eps|pdf|csv)", nombre_archivo) or \
        re.fullmatch(r"malla(Ventana|Refuerzo)\.pl", nombre_archivo) or \
        re.fullmatch(r"[0-9][0-9]?,[0-9][0-9]?\.(pl|txt)", nombre_archivo) or \
        re.fullmatch(r"baseConocimientoMallas(Filtradas)?[0-9]?\.pl", nombre_archivo) or \
        re.fullmatch(r"(LimitesPasos|EvaluacionMallas)[0-9]?\.txt", nombre_archivo) or \
        re.fullmatch(r"comparacionAlgoritmos.*\.(txt|tex)", nombre_archivo) or \
        nombre_archivo in casos_particulares:
        return True
    else: 
        return False

def extensiones(nombre_archivo):
    return re.fullmatch(r".*(\..*)", nombre_archivo).group(1)

df = \
    df_todos_repo.merge(
        df_todos_orig, 
        how = "left", 
        on = "ruta", 
        suffixes = ("_repo", "_orig")
    )

# Correcciones debidas al merge
df["tamaño_original_orig"] = df["tamaño_original_orig"].replace({np.nan: 0})
df["tamaño_original_orig"] = df["tamaño_original_orig"].astype(np.int64)

# Insertar columna "nombre_archivo" y actualizar la columna "ruta"
df["nombre_archivo"] = df["ruta"].apply(obtener_nombre_archivo)
df["ruta"] = df["ruta"].apply(obtener_ruta)

# Renombrado de etiquetas de la columna "estatus_commit_0"
mapeo_status = {'?':"ignorado", 'H':"monitoreado", 'T':"N/A"}
df["estatus_commit_0"] = df["estatus_commit_0"].replace(mapeo_status)

# Generación de etiqueta "monitoreado_muestreado" en columna "estatus_commit_0"
df["estatus_commit_0"] = \
    df.apply(
        lambda x: 
        es_muestreado(
            x["tamaño_original_orig"], 
            x["tamaño_original_repo"], 
            x["estatus_commit_0"]
        ), 
        axis=1
    )
df.loc[df["nombre_archivo"] == ".gitignore", "estatus_commit_0"] = "monitoreado"

# Inclusión de columna "es_generado"
df["es_generado"] = df["nombre_archivo"].apply(es_generado)

# Borrado de información
df.drop("tamaño_original_repo", axis=1, inplace=True)
df.drop(df[df.ruta == "total"].index, inplace=True)

# Renombrado y reestructuración de columnas
df = df.rename(columns={"tamaño_original_orig": "tamaño_original"})
df = df[[
    "nombre_archivo", 
    "tamaño_original", 
    "estatus_commit_0", 
    "es_generado", 
    "ruta"
]]

# Escritura de CSV final
df.to_csv("informacion_archivos_repositorio.csv", sep='|', index=False)
