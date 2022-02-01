#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Dec  9 09:12:29 2021
Análisis de datos de encuesta Partido Migala.
Encuesta cerrada al 07/12/2021.
@author: j6
"""

import pandas as pd
import geopandas as gpd
import matplotlib as mpl
import matplotlib.pyplot as plt
#import seaborn as sns
from textwrap import wrap

import numpy as np

df = pd.read_excel("Padron_Migala_07-12-21.xls", "Sheet1")
# Desechar columnas inservibles.
df = df[df.columns[3:-7]]

def rangoEdad(x):
    return int(np.floor((x-1)/5))

def rangoHoras(x):
    return int(np.floor((x-1)/5))

rangoEdadDict = {
    0:'1-5', 1:'6-10', 2:'11-15', 3:'16-20', 4:'21-25', 5:'26-30', 6:'31-35',
    7:'36-40', 8:'41-45', 9:'46-50', 10:'51-55', 11:'56-60', 12:'61-65',
    13:'66-70', 14:'71-75', 15:'76-80', 16:'81-85', 17:'86-90', 18:'91-95',
    19:'96-100', 20:'101-105'
}

rangoHorasDict = {
    -1:'0', 0:'1-5', 1:'6-10', 2:'11-15', 3:'16-20', 4:'21-25', 5:'26-30', 6:'31-35',
    7:'36-40', 8:'41-45', 9:'46-50', 10:'51-55', 11:'56-60', 12:'61-65',
    13:'66-70'
}

colorDefecto = '#be298a' #'#ab257a' #'#1f77b4'

def grafBarras(x, y, titulo, xtitulo, ytitulo, figsize=(6.2, 3), color=colorDefecto, 
               titlefntsize=9, titlepad=4, xlabfntsize=7, ylabfntsize=7, xlabpad=3, 
               leyendas_barras=True, xtickfntsize=6, xtickrot=0, xtickhalign='center',
               xtickvalign='center', xtlabelspad=3, ytickfntsize=6, barlabfntsize=6,
               xtfontfam='monospace', ytfontfam='monospace', xtfontsty='italic',
               ytfontsty='italic', savefig=''):

    y = list(y)
    fig, ax = plt.subplots(figsize=figsize)
    plt.bar(x, y, color=color)
    plt.setp(ax.xaxis.get_majorticklabels(), rotation=xtickrot, ha=xtickhalign, rotation_mode='anchor')
    plt.tick_params(axis='x', pad=xtlabelspad)
    plt.xticks(horizontalalignment=xtickhalign, x=0, fontstyle=xtfontsty, fontfamily=xtfontfam, fontsize=xtickfntsize)
    plt.yticks(fontstyle=ytfontsty, fontfamily=ytfontfam, fontsize=ytickfntsize)
    
    if leyendas_barras:
        for i in range(len(x)):
            plt.text(i, y[i] + 0.015*max(y), y[i], horizontalalignment='center',
                     fontsize=barlabfntsize, fontstyle='italic', fontfamily='monospace')
            
    plt.title(titulo, pad=titlepad, fontsize=titlefntsize, fontweight='medium', fontstyle='italic')
    plt.xlabel(xtitulo, labelpad=xlabpad, fontsize=xlabfntsize)
    plt.ylabel(ytitulo, labelpad=4, fontsize=ylabfntsize)
    if savefig: plt.savefig(savefig, format='pdf', bbox_inches='tight', transparent=True)
    #if savefig: plt.savefig('img.pgf')
    #plt.show()

def histograma(x, bins=2, titulo='', xtitulo='', ytitulo='', color=colorDefecto, 
               leyendas_barras=True, xtickrot=0, xtickhalign='center',
               xtickvalign='center', xtlabelspad=5):

    x = list(x)
    fig, ax = plt.subplots(figsize=(16.0, 8.0))
    plt.hist(x, bins, color=color)
    plt.setp(ax.xaxis.get_majorticklabels(), rotation=xtickrot, ha=xtickhalign, rotation_mode='anchor')
    plt.tick_params(axis='x', pad=xtlabelspad)
    if leyendas_barras:
        for i in range(len(x)):
            plt.text(i, x[i] + 0.01*max(x), x[i], horizontalalignment='center')
    plt.title(titulo)
    plt.xlabel(xtitulo)
    plt.ylabel(ytitulo)
    plt.show()
    
def corregirAcentos(s):
    return s.upper().encode('latin_1').decode().title()


#%% Información general

#for i in df.columns: print(i)
#df.info()

#%%
['ascii', 'big5', 'big5hkscs', 'cp037', 'cp273', 'cp424', 'cp437', 'cp500',
 'cp720', 'cp737', 'cp775', 'cp850', 'cp852', 'cp855', 'cp856', 'cp857',
 'cp858', 'cp860', 'cp861', 'cp862', 'cp863', 'cp864', 'cp865', 'cp866',
 'cp869', 'cp874', 'cp875', 'cp932', 'cp949', 'cp950', 'cp1006', 'cp1026',
 'cp1125', 'cp1140', 'cp1250', 'cp1251', 'cp1252', 'cp1253', 'cp1254',
 'cp1255', 'cp1256', 'cp1257', 'cp1258', 'cp65001', 'euc_jp', 'euc_jis_2004',
 'euc_jisx0213', 'euc_kr', 'gb2312', 'gbk', 'gb18030', 'hz', 'iso2022_jp',
 'iso2022_jp_1', 'iso2022_jp_2', 'iso2022_jp_2004', 'iso2022_jp_3',
 'iso2022_jp_ext', 'iso2022_kr', 'latin_1', 'iso8859_2', 'iso8859_3',
 'iso8859_4', 'iso8859_5', 'iso8859_6', 'iso8859_7', 'iso8859_8', 'iso8859_9',
 'iso8859_10', 'iso8859_11', 'iso8859_13', 'iso8859_14', 'iso8859_15',
 'iso8859_16', 'johab', 'koi8_r', 'koi8_t', 'koi8_u', 'kz1048', 'mac_cyrillic',
 'mac_greek', 'mac_iceland', 'mac_latin2', 'mac_roman', 'mac_turkish',
 'ptcp154', 'shift_jis', 'shift_jis_2004', 'shift_jisx0213', 'utf_32',
 'utf_32_be', 'utf_32_le', 'utf_16', 'utf_16_be', 'utf_16_le', 'utf_7',
 'utf_8', 'utf_8_sig']

#%% Configuración graficos

mpl.rcParams['figure.dpi'] = 200
mpl.rcParams['figure.figsize'] = (6.2, 3)           # (6.2, 3)
mpl.rcParams['savefig.pad_inches'] = 0.01
mpl.rcParams['font.family'] = ['sans-serif','monospace']
#mpl.rcParams['font.monospace'] = 'Computer Modern Typewriter'
#mpl.rcParams['font.serif'] = 'Computer Modern Roman'
mpl.rcParams['xtick.major.pad'] = 5
mpl.rcParams['ytick.major.pad'] = 2
mpl.rcParams['xtick.labelsize'] = 10
mpl.rcParams['axes.titlepad'] = 20
mpl.rcParams['axes.xmargin'] = 0.05
mpl.rcParams['axes.ymargin'] = 0.09
mpl.rcParams['axes.linewidth'] = 0.4
mpl.rcParams['xtick.major.width'] = 0.4
mpl.rcParams['ytick.major.width'] = 0.4
mpl.rcParams['xtick.major.size'] = 2
mpl.rcParams['ytick.major.size'] = 2

# Configuración gráficos LaTeX
mpl.use('pgf')
pgf_config = {
    'pgf.texsystem': 'lualatex',
    'text.usetex': False,        # Modo matemático para marcas de ejes.
    'pgf.rcfonts': False,       # Usar fuentes LaTeX en parámetros "rc" (falso para LuaLaTeX).
    'pgf.preamble': r'\usepackage{anyfontsize}',
    'font.family': ['sans-serif'],
    #'font.style': 'normal',
    #'font.serif': ['Computer Modern Roman'],              # Fuente(s) específica(s).
    #'font.sans-serif': ['Computer Modern Sans Serif'],         # Fuente(s) específica(s).
    #'font.monospace': ['Computer Modern Typewriter'],      # Fuente(s) específica(s).
    #'text.latex.preamble': [],
}
mpl.rcParams.update(pgf_config)

#%% Panorama de vacíos.

fig, ax = plt.subplots(figsize=(5.55, 3.45))
cmapNulos = mpl.colors.ListedColormap(['white', mpl.cm.Blues(0.9)])
cols = df.columns[::-1]
#cols = df.columns[44:46]
ax.pcolormesh(df[cols].T.notna(), cmap=cmapNulos, antialiased=True)
ax.set_title('Valores faltantes (hay dato o no hay dato)', fontsize=6, pad=4, fontstyle='italic')
ax.set_xlabel('Número de registro', fontsize=5, labelpad=2)
ax.set_ylabel('Columna', fontsize=5)
ax.tick_params(axis='x', labelsize=5, pad=2)
for t in ax.xaxis.get_ticklabels():
    t.set_family('monospace')
    t.set_style('italic')
ax.tick_params(axis='y', labelsize=2, pad=0.5, width=0.25)
ax.set_ylim(0, len(df.columns))
pos_yticks = np.array(range(len(cols))) + 0.5
ax.set_yticks(pos_yticks)
ax.set_yticklabels(cols)

axR = ax.twinx()
#axR.set_yscale('linear')
axR.set_ylim(0, len(df.columns))
#axR.yaxis.set_major_formatter(ScalarFormatter())        fontstyle='italic', fontfamily='manospace'
axR.tick_params(axis='y', labelsize=2, pad=0.5, width=0.25)
axR.set_ylabel('Porcentaje de vacíos', fontsize=5, labelpad=5, rotation=270)
for t in axR.yaxis.get_ticklabels():
    t.set_family('monospace')
    t.set_style('italic')
dflen = len(df)
labels = ['{:.2f}'.format(100*(dflen - df[c].notna().sum())/dflen) + '%' for c in cols]
axR.set_yticks(pos_yticks)
axR.set_yticklabels(labels)
plt.savefig('Presentación/img/Vacios.pdf', format='pdf', bbox_inches='tight', transparent=True)

#%% Edades

fecha_hoy = pd.to_datetime('today')
df['Fecha de nacimiento'] = df['Fecha de nacimiento'].str.replace('T00:00:00.000Z', '', case=False)
# Reemplazar fechas de nacimiento raras.
df.loc[df['Fecha de nacimiento'].str.split('-').str.get(0).astype(np.int) < 1920, 'Fecha de nacimiento'] = '1980-01-01'
df.loc[df['Fecha de nacimiento'].str.split('-').str.get(0).astype(np.int) > 2019, 'Fecha de nacimiento'] = '2010-01-01'

df['Fecha de nacimiento'] = pd.to_datetime(df['Fecha de nacimiento'], format='%Y-%m-%d')

datosEdad = pd.Series(pd.TimedeltaIndex(fecha_hoy - df['Fecha de nacimiento'], unit='D').days/365).round().astype(np.int)
edadPromedio = datosEdad.mean()
df.insert(1, 'Edad', datosEdad, True)
df.insert(2, 'Rango edad', datosEdad.apply(rangoEdad), True)

dfEdad_y = df.groupby('Rango edad')['Rango edad'].count()
dfEdad_x = [rangoEdadDict[i] for i in dfEdad_y.index]

# Gráfica
grafBarras(dfEdad_x, dfEdad_y, 'Edades', 'Rango edad', '\\# Encuestados',
           figsize=(6.2, 2.5), savefig='Presentación/img/Edades.pdf')

#%% Nacionalidad

dfNac_y = df['Nacionalidad'].value_counts(dropna=False)
dfNac_x = list(dfNac_y.index)
dfNac_x[2] = 'Nulos'

# Gráfica
colores = [colorDefecto]*len(dfNac_x)
colores[2] = 'gray'
grafBarras(dfNac_x, dfNac_y, 'Nacionalidades', 'Nacionalidad', '\\# Encuestados',
           color=colores, xtfontfam='sans-serif', xtfontsty='normal', savefig='Presentación/img/Nacionalidad.pdf')

#%% Género

dfGe_y = df['Género'].value_counts(dropna=False)
dfGe_x = list(dfGe_y.index)
dfGe_x[1] = 'Nulos'

# Gráfica
colores = [colorDefecto]*len(dfGe_x)
colores[1] = 'gray'
grafBarras(dfGe_x, dfGe_y, 'Género de los participantes', 'Género', '\\# Encuestados',
           color=colores, xtfontfam='sans-serif', xtfontsty='normal', savefig='Presentación/img/Genero.pdf')
#%% ¿Discapacidad?

dfDis_y = df['¿Discapacidad?'].value_counts(dropna=False)
dfDis_x = ['No', 'Nulos', 'Si']

# Gráfica
colores = [colorDefecto]*len(dfDis_x)
colores[1] = 'gray'
grafBarras(dfDis_x, dfDis_y, 'Participantes con discapacidad', '¿Discapacidad?',
           '\\# Encuestados', color=colores, xtfontfam='sans-serif', xtfontsty='normal',
           savefig='Presentación/img/Discapacidad.pdf')
#%% Entidad federativa

dfEF_y = df['Entidad federativa'].value_counts(dropna=False)
dfEF_x = list(dfEF_y.index)
dfEF_x[0] = 'Nulos'

# Gráfica
colores = [colorDefecto]*len(dfEF_x)
colores[0] = 'gray'
grafBarras(dfEF_x, dfEF_y, 'Entidad federativa', 'Estado', '\\# Encuestados', 
           figsize=(6.2, 2.6), color=colores, xtickfntsize=5, xtickrot=60, xtickhalign='right',
           xtlabelspad=1, barlabfntsize=4, xtfontfam='sans-serif', xtfontsty='normal',
           savefig='Presentación/img/Entidad_federativa.pdf')

#%% Mapa estados

dfEF = df.groupby('Entidad federativa')[['Entidad federativa']].count()
dfEF = dfEF.rename(columns={'Entidad federativa':'Conteo'})
dfEF = dfEF.rename(index={'Estado de México':'Edo. Mex.', 'Ciudad de México':'CDMX'})
dfEF = dfEF.drop('Vivo en el extranjero')

shapefile = gpd.read_file('maps/Estados/México_Estados.shp')
shapefile.loc[shapefile['ESTADO']=='Distrito Federal', 'ESTADO'] = 'CDMX'
shapefile.loc[shapefile['ESTADO']=='México', 'ESTADO'] = 'Edo. Mex.'
shapefile = shapefile.merge(right=dfEF, left_on='ESTADO', right_on='Entidad federativa', how='left')

fig, ax = plt.subplots(figsize=(7.2, 4))
ax.set_ymargin(0)
ax.axis('off')
shapefile.plot(ax=ax, linewidth=0.1, edgecolor='black', column='Conteo', cmap=mpl.cm.RdPu)
ax.set_title('Encuestados por entidad', fontsize=9, pad=4, fontstyle='italic')
# Barra de color.
fig = ax.get_figure()
#cax = fig.add_axes([0.9, 0.1, 0.03, 0.8])
sm = plt.cm.ScalarMappable(cmap=mpl.cm.RdPu, norm=plt.Normalize(vmin=0, vmax=shapefile['Conteo'].max()))
cbar = fig.colorbar(sm, pad=0.05, shrink=0.7)#, cax=cax)
cbar.set_label('\\# Encuestados', fontsize=6, labelpad=-27)
#cbar.ax.set_ylabel('\\# Encuestados')
cbar.ax.tick_params(labelsize=5)
for t in cbar.ax.yaxis.get_ticklabels():
    t.set_family('monospace')
    t.set_style('italic')
plt.savefig('Presentación/img/Mapa_Mexico.pdf', format='pdf', bbox_inches='tight', transparent=True)

#shapefile.head(5)
#shapefile.columns
#shapefile[['ESTADO', 'Conteo']]
#shapefile = shapefile.sort_values(by='shape_area', ascending = False)


#%% País de residencia y años viviendo en el extranjero.

col1 = 'País de residencia'
col2 = 'Años viviendo en el extranjero'
dfPR_y = df.groupby(col1).agg({col1:'count', col2:'mean'})
dfPR_y.index.names = ['Índice']
dfPR_y = dfPR_y.sort_values(by=col1, ascending = False)
dfPR_x = list(dfPR_y.index)
dfPR_x[0] = 'Nulos'

# Crear tabla
#%% Municipio o alcaldía

# Corregir nombres con regex.
dfMun_y = df.loc[df['Entidad federativa'] == 'Ciudad de México', 'Municipio o alcaldía']
dfMun_y = dfMun_y.str.replace(r'.*Gus(ts)?tavo.*A.*Madero.?', 'Gustavo A. Madero', case=False)
dfMun_y = dfMun_y.str.replace(r'.*Gus(ts)?tavo.*A.*Madero.?', 'Gustavo A. Madero', case=False)
dfMun_y = dfMun_y.str.replace(r'G.?A.?M.?', 'Gustavo A. Madero', case=False)
dfMun_y = dfMun_y.str.replace(r'.*\n?Benito.*', 'Benito Juárez', case=False)
dfMun_y = dfMun_y.str.replace(r'Iztapala.*', 'Iztapalapa', case=False)
dfMun_y = dfMun_y.str.replace(r'(Ve.*ano Carranza)|(vc)', 'Venustiano Carranza', case=False)
dfMun_y = dfMun_y.str.replace(r'Cua.*[eé]moc.*', 'Cuauhtémoc', case=False)
dfMun_y = dfMun_y.str.replace(r'Tlalp[aá]n', 'Tlalpan', case=False)
dfMun_y = dfMun_y.str.replace(r'Iztacalco', 'Iztacalco', case=False)
dfMun_y = dfMun_y.str.replace(r'.*Coyo.*', 'Coyoacán', case=False)
dfMun_y = dfMun_y.str.replace(r'Tl[aá]huac', 'Tláhuac', case=False)
dfMun_y = dfMun_y.str.replace(r'.*Ma..alena Contreras', 'La Magdalena Contreras', case=False)
dfMun_y = dfMun_y.str.replace(r'[AÁ]lvaro Obreg[oó]n', 'Álvaro Obregón', case=False)
dfMun_y = dfMun_y.str.replace(r'A.*alco', 'Azcapotzalco', case=False)
dfMun_y = dfMun_y.str.replace(r'I.*alco', 'Iztacalco', case=False)
dfMun_y = dfMun_y.str.replace(r'Miguel Hidalgo', 'Miguel Hidalgo', case=False)
dfMun_y = dfMun_y.str.replace(r'.*Tec[aá]mac', 'Tecámac', case=False)
dfMun_y = dfMun_y.str.replace(r'Milpa Alta', 'Milpa Alta', case=False)
dfMun_y = dfMun_y.str.replace(r'Tultitl[aá]n', 'Tultitlán', case=False)
dfMun_y = dfMun_y.str.replace(r'naucalpan de juarez', 'Naucalpan de Juárez', case=False)
dfMun_y = dfMun_y.str.replace(r'CANATLAN', 'Canatlán', case=False)
dfMun_y = dfMun_y.str.replace(r'Chalco, Edomex.', 'Chalco', case=False)
dfMun_y = dfMun_y.str.replace(r'Nicolás romero', 'Nicolás Romero', case=False)
dfMun_y = dfMun_y.str.replace(r'Sta Cruz Atoyac', 'Santa Cruz Atoyac', case=False)
dfMun_y = dfMun_y.str.replace(r'Cuatitlan Izcalli', 'Cuautitlán Izcalli', case=False)
dfMun_y = dfMun_y.str.replace(r'Cuajimalpa de Morelos', 'Cuajimalpa De Morelos', case=False)

dfMun_y = dfMun_y.value_counts(dropna=False)
#print(dfMun_y.to_string())
dfMun_x = list(dfMun_y.index)

# Gráfica
grafBarras(dfMun_x, dfMun_y, 'Participación CDMX', 'Municipio o alcaldía',
           '\\# Encuestados', figsize=(6.2, 2.5), xtickfntsize=5, xtickrot=60,
           xtickhalign='right', xlabpad=2,
           xtlabelspad=1, barlabfntsize=4, xtfontfam='sans-serif', xtfontsty='normal',
           savefig='Presentación/img/Municipio.pdf')

#%% Mapa CDMX

dfCDMX = pd.DataFrame(dfMun_y)
dfCDMX = dfCDMX.rename(columns={'Municipio o alcaldía':'Conteo'})
dfCDMX.index.names = ['Municipio']
shapefile = gpd.read_file('maps/Municipios/muni_2018gw.shp')
shapefile = shapefile[shapefile['NOM_ENT']=='Ciudad de MÃ©xico']
shapefile['NOM_MUN'] = shapefile['NOM_MUN'].apply(corregirAcentos)
shapefile = shapefile.merge(right=dfCDMX, left_on='NOM_MUN', right_on='Municipio', how='left')
shapefile.loc[shapefile['NOM_MUN']=='Gustavo A. Madero', 'NOM_MUN'] = 'Gustavo A.\nMadero'
shapefile.loc[shapefile['NOM_MUN']=='Venustiano Carranza', 'NOM_MUN'] = 'Venustiano\nCarranza'
shapefile.loc[shapefile['NOM_MUN']=='Miguel Hidalgo', 'NOM_MUN'] = 'Miguel\nHidalgo'
shapefile.loc[shapefile['NOM_MUN']=='Benito Juárez', 'NOM_MUN'] = 'Benito\nJuárez'
shapefile.loc[shapefile['NOM_MUN']=='Álvaro Obregón', 'NOM_MUN'] = 'Álvaro\nObregón'
shapefile.loc[shapefile['NOM_MUN']=='Cuajimalpa De Morelos', 'NOM_MUN'] = 'Cuajimalpa De\nMorelos'
shapefile.loc[shapefile['NOM_MUN']=='La Magdalena Contreras', 'NOM_MUN'] = 'La Magdalena\nContreras'
off = {'Gustavo A.\nMadero':(0.01,-0.02), 'Álvaro\nObregón':(0.025,0.027),
       'Cuajimalpa De\nMorelos':(0.018,0.023), 'La Magdalena\nContreras':(-0.013, -0.025),
       'Miguel\nHidalgo':(0.003,0)}

shapefile['center'] = shapefile['geometry'].centroid
shapefile_points = shapefile.copy()
shapefile_points.set_geometry('center', inplace = True)

fig, ax = plt.subplots(figsize=(6.7, 3.4))
ax.set_ymargin(0)
ax.axis('off')
shapefile.plot(ax=ax, linewidth=0.1, edgecolor='black', column='Conteo', cmap='Blues')
ax.set_title('Encuestados CDMX', fontsize=9, pad=10, fontstyle='italic')
texts = []
for x, y, label in zip(shapefile_points.geometry.x, shapefile_points.geometry.y, shapefile_points['NOM_MUN']):
    color = 'white' if label in {'Gustavo A.\nMadero', 'Iztapalapa'} else 'black'
    if label not in off.keys(): xoff, yoff = 0,0
    else: xoff, yoff = off[label]
    texts.append(plt.text(x + xoff, y + yoff, label, fontsize=3, color=color, horizontalalignment='center', verticalalignment='center'))
# Barra de color.
fig = ax.get_figure()
#cax = fig.add_axes([0.9, 0.1, 0.03, 0.8])
sm = plt.cm.ScalarMappable(cmap='Blues', norm=plt.Normalize(vmin=0, vmax=shapefile['Conteo'].max()))
cbar = fig.colorbar(sm, pad=0.08, shrink=0.7)#, cax=cax)
cbar.set_label('\\# Encuestados', fontsize=6, labelpad=-27)
#cbar.ax.set_ylabel('\\# Encuestados')
cbar.ax.tick_params(labelsize=5)
for t in cbar.ax.yaxis.get_ticklabels():
    t.set_family('monospace')
    t.set_style('italic')
plt.savefig('Presentación/img/Mapa_CDMX.pdf', format='pdf', bbox_inches='tight', transparent=True)

shapefile[['NOM_MUN', 'Conteo']]

#%% Ocupación

dfOc = df[['¿Estudiante?', '¿Sector privado?', '¿Sector público a nivel local?', 
             '¿Sector público a nivel Federal?', '¿Sector público a nivel organización/sindicato?',
             '¿Servicio social/beneficencia?', '¿Negocio propio?', '¿Servicios freelance?', '¿Desempleadx?',
             'Otro (ocupación)']]

# Valores nulos (NaN en todas las columnas de ocupación).
nulos = set(dfOc.loc[dfOc['¿Estudiante?'].isnull(), '¿Estudiante?'].index)
for i in dfOc.columns:
    nulos = nulos & set(dfOc.loc[dfOc[i].isnull(), i].index)

dfOc_y = [[dfOc[i].count(), i] for i in dfOc.columns]
dfOc_y.append([len(nulos), 'Nulos'])
dfOc_y.sort(reverse=True)
dfOc_x = [i[1] for i in dfOc_y]
dfOc_y = [i[0] for i in dfOc_y]

dfOc_x = [i.replace('?', '').replace('¿', '') for i in dfOc_x]
dfOc_x[-2] = 'Otra'
dfOc_x = ['\n'.join(wrap(i, 15)) for i in dfOc_x]

# Gráfica
colores = [colorDefecto]*len(dfOc_x)
colores[2] = 'gray'
grafBarras(dfOc_x, dfOc_y, 'Ocupaciones de los encuestados', 'Ocupación', '\\# Encuestados', 
           figsize=(6.2, 2.8), color=colores, xtickrot=30, xtickhalign='right', xtickfntsize=5,
           xtlabelspad=2, xtfontfam='sans-serif', xtfontsty='normal', savefig='Presentación/img/Ocupacion.pdf')

#%% Grado de estudios

dfGE_y = df['Último grado de estudios'].value_counts(dropna=False)
dfGE_x = list(dfGE_y.index)
dfGE_x[2] = 'Nulos'

# Gráfica
colores = [colorDefecto]*len(dfGE_x)
colores[2] = 'gray'
grafBarras(dfGE_x, dfGE_y, 'Último grado de estudios', 'Último grado de estudios',
           '\\# Encuestados', xtfontfam='sans-serif', xtfontsty='normal', color=colores,
           savefig='Presentación/img/Grado_estudios.pdf')

#%% ¿Trabajas en lo que estudiaste?

dfTE_y = df['¿Trabajas en lo que estudiaste?'].value_counts(dropna=False)
dfTE_x = list(dfTE_y.index)
dfTE_x[3] = 'Nulos'

# Gráfica
colores = [colorDefecto]*len(dfTE_x)
colores[3] = 'gray'
grafBarras(dfTE_x, dfTE_y, '¿Trabajas en lo que estudiaste?',
           '¿Trabajas en lo que estudiaste?', '\\# Encuestados',
           color=colores, xtfontfam='sans-serif', xtfontsty='normal',
           savefig='Presentación/img/Trabajas_en_lo_que_estudiaste.pdf')

#%% Área de estudio

dfAE = df[['Área I, Ciencias Físico - Matemáticas y de las Ingenierías',
           'Área II, Ciencias Biológicas, Químicas y de la Salud',
           'Área III Ciencias Sociales, Económicas y Administrativas', 
           'Área IV, Artes y Humanidades',
           'Área V, Actividades Agropecuarias',
           'Ninguna / No aplica']]

AreaI = 'Área I, Ciencias Físico - Matemáticas y de las Ingenierías'

# Valores nulos (NaN en todas las columnas de ocupación).
nulos = set(dfAE.loc[dfAE[AreaI].isnull(), AreaI].index)
for i in dfAE.columns:
    nulos = nulos & set(dfAE.loc[dfAE[i].isnull(), i].index)

dfAE_y = [[dfAE[i].count(), i] for i in dfAE.columns]
dfAE_y.append([len(nulos), 'Nulos'])
dfAE_y.sort(reverse=True)
dfAE_x = [i[1] for i in dfAE_y]
dfAE_y = [i[0] for i in dfAE_y]

dfAE_x = ['\n'.join(wrap(i, 20)) for i in dfAE_x]

# Gráfica
colores = [colorDefecto]*len(dfAE_x)
colores[2] = 'gray'
grafBarras(dfAE_x, dfAE_y, 'Áreas de estudio', 'Área de estudio', '\\# Encuestados', 
           color=colores, xtickhalign='center', xtfontfam='sans-serif', xtfontsty='normal',
           xtickfntsize=4.5, savefig='Presentación/img/Area_de_estudio.pdf')

#%% Actividades extra

dfAEx = df[['Deportivas',
           'Artísticas',
           'Producción de contenido', 
           'Sin actividades extra',
           'Otra (actividades extra)',
           'Actividad específica']]

# Valores nulos (NaN en todas las columnas de ocupación).
nulos = set(dfAEx.loc[dfAEx['Deportivas'].isnull(), 'Deportivas'].index)
for i in dfAEx.columns:
    nulos = nulos & set(dfAEx.loc[dfAEx[i].isnull(), i].index)

dfAEx_y = [[dfAEx[i].count(), i] for i in dfAEx.columns]
dfAEx_y.append([len(nulos), 'Nulos'])
dfAEx_y.sort(reverse=True)
dfAEx_x = [i[1] for i in dfAEx_y]
dfAEx_y = [i[0] for i in dfAEx_y]

dfAEx_x = ['\n'.join(wrap(i, 20)) for i in dfAEx_x]

dfAEx_x.append(dfAEx_x[0])
dfAEx_y.append(dfAEx_y[0])
dfAEx_x.pop(0)
dfAEx_y.pop(0)

dfAEx_x[5] = 'Otra'

# Gráfica
colores = [colorDefecto]*len(dfAEx_x)
colores[3] = 'gray'
grafBarras(dfAEx_x, dfAEx_y, 'Actividades extra', 'Actividad extra',
           '\\# Encuestados', figsize=(6.2, 2.5), color=colores,
           xtickhalign='center', xtfontfam='sans-serif', xtfontsty='normal',
           savefig='Presentación/img/Actividades_extra.pdf')

#%% Activismo (detalle)

dfAc = df[['¿Activismo?',
           'ONG’s u organización sin fines de lucro',
           'Partidista',
           'Administración pública', 
           'Trabajo comunitario',
           'Sindicato',
           'Cooperativas u organizaciones de la economía social y solidaria',
           'Ninguno',
           'Otras (activismo)']]

# Valores nulos (NaN en todas las columnas de ocupación).
nulos = set(dfAc.loc[dfAc[dfAc.columns[0]].isnull(), dfAc.columns[0]].index)
for i in dfAc.columns:
    nulos = nulos & set(dfAc.loc[dfAc[i].isnull(), i].index)

dfAc_y = [[dfAc[i].count(), i] for i in dfAc.columns]
dfAc_y.append([len(nulos), 'Nulos'])
dfAc_y.sort(reverse=True)
dfAc_x = [i[1] for i in dfAc_y]
dfAc_y = [i[0] for i in dfAc_y]

dfAc_x = [i.replace('?', '').replace('¿', '') for i in dfAc_x]
dfAc_x = ['\n'.join(wrap(i, 15)) for i in dfAc_x]

dfAc_x[9] = 'Otras'

# Gráfica
colores = [colorDefecto]*len(dfAc_x)
colores[1] = 'gray'
grafBarras(dfAc_x, dfAc_y, 'Actividades extra', 'Actividad extra', '\\# Encuestados',
           figsize=(6.2, 2.9), color=colores, xtickfntsize=4.5,
           xtfontfam='sans-serif', xtfontsty='normal', savefig='Presentación/img/Activismo.pdf')

#%% Actividades políticas y/o sociales

df['Actividades políticas y/o sociales'].isnull().value_counts(dropna=False)

#%% Oficio o conocimientos técnicos

df['Oficio o conocimientos técnicos'].isnull().value_counts(dropna=False)

#%% ¿Cómo te gustaría participar en este proyecto?

dfPar_y = df['¿Cómo te gustaría participar en este proyecto?'].value_counts(dropna=False)

dfPar_x = list(dfPar_y.index)
dfPar_x[1] = 'Nulos'
dfPar_x = ['\n'.join(wrap(i, 25)) for i in dfPar_x]

dfPar_x[2] = dfPar_x[2] + '.'

# Gráfica
colores = ['#d87fb9', 'gray', '#e5aad1', '#cb54a2', '#f2d5e8', colorDefecto]
grafBarras(dfPar_x, dfPar_y, '¿Cómo te gustaría participar en este proyecto?',
           '', '\\# Encuestados', xtickfntsize=4.5, color=colores,
           xtfontfam='sans-serif', xtfontsty='normal', savefig='Presentación/img/Como_te_gustaria_participar.pdf')

#%% ¿En qué actividad(es) te gustaría participar en este proyecto?

dfAct = df[['Trabajo de campo',
           'Organización en línea',
           'Diseño y/o comunicación',
           'Programación y desarrollo web', 
           'Labores administrativas',
           'Trámites frente a gobierno',
           'Otro (¿Cómo te gustaría participar?)']]

# Valores nulos (NaN en todas las columnas de ocupación).
nulos = set(dfAct.loc[dfAct[dfAct.columns[0]].isnull(), dfAct.columns[0]].index)
for i in dfAct.columns:
    nulos = nulos & set(dfAct.loc[dfAct[i].isnull(), i].index)

dfAct_y = [[dfAct[i].count(), i] for i in dfAct.columns]
dfAct_y.append([len(nulos), 'Nulos'])
dfAct_y.sort(reverse=True)
dfAct_x = [i[1] for i in dfAct_y]
dfAct_y = [i[0] for i in dfAct_y]

dfAct_x = ['\n'.join(wrap(i, 15)) for i in dfAct_x]
dfAct_x[-1] = 'Otras'

# Gráfica
colores = [colorDefecto]*len(dfAct_x)
colores[4] = 'gray'
grafBarras(dfAct_x, dfAct_y, '¿En qué actividad(es) te gustaría participar en este proyecto?',
           'Actividad', '\\# Encuestados', xtickfntsize=5, color=colores,
           xtfontfam='sans-serif', xtfontsty='normal',
           savefig='Presentación/img/En_que_actividades_te_gustaria_participar.pdf')

#%% Disponibilidad en la semana

dfDis = df[['Lunes',
           'Martes',
           'Miércoles',
           'Jueves', 
           'Viernes',
           'Sábado',
           'Domingo']]

# Filtrar solo conteos de horarios.
mesh = pd.concat([dfDis[i].value_counts(dropna=False) for i in dfDis.columns], axis=1)

# Índices de horarios.
x = list(dfDis['Lunes'].value_counts(dropna=False).index)
x.remove('Sin tiempo disponible')
x.pop(1)

# Añadir registro de totales de disponibilidad en toda la semana.
totals = [mesh.loc[mesh.index.isin(x)][i].sum() for i in dfDis.columns]
mesh = mesh.append(pd.DataFrame([totals], columns=dfDis.columns, index=['Total con disponibilidad']))

mesh = mesh.rename(index={mesh.index[1]:'Nulos'})

# Cambiar columnas por renglones.
mesh = mesh.transpose()
meshMax = mesh.values.max()

# Reordenar columnas.
c = mesh['Sin tiempo disponible']
mesh.drop('Sin tiempo disponible', axis=1, inplace=True)
mesh = pd.concat([mesh, c], axis=1)
c = mesh['Nulos']
mesh.drop('Nulos', axis=1, inplace=True)
mesh = pd.concat([mesh, c], axis=1)

# Normalizar y obtener color de cada celda.
meshRGB = mesh.copy()
meshRGB /= meshMax
for i in list(meshRGB.columns)[:-2]: meshRGB[i] = meshRGB[i].apply(mpl.cm.RdPu)
for i in list(meshRGB.columns)[-2:]: meshRGB[i] = meshRGB[i].apply(mpl.cm.Greys)
meshRGB = meshRGB.values.tolist()

xticklabs = ['\n'.join(wrap(i, 15)) for i in mesh.columns]
meshTextColors = np.full((len(mesh), len(mesh[mesh.columns[0]])), '#444444')
for i in range(len(meshTextColors)):
    meshTextColors[i][0] = 'white'
    meshTextColors[i][4] = 'white'

# Gráfica
fig, ax = plt.subplots(figsize=(6.2, 3))
#cmap = mpl.colors.ListedColormap(['red', 'green', 'blue', 'cyan']) # Documentar.
#cmap = mpl.colors.LinearSegmentedColormap.from_list('Comp', ['#f2d5e8', '#be298a'], N=5) # Documentar.
ax = plt.axes(xticks = [i for i in range(len(mesh.columns))],
         yticks = [j for j in range(len(mesh.index))],
         xticklabels=xticklabs, yticklabels=mesh.index)
plt.tick_params(axis='x', pad=3)
plt.xticks(horizontalalignment='center', x=0, fontfamily='sans-serif', fontsize=6)
plt.yticks(fontfamily='sans-serif', fontsize=6)
plt.title('Disponibilidad de los encuestados para participar en el proyecto',
          pad=8, fontsize=9, fontweight='medium', fontstyle='italic')
plt.xlabel('Horas de disponibilidad', labelpad=5, fontsize=7)
plt.ylabel('')
## Malla
plt.hlines(ax.get_xticks() + 0.5, ax.get_xticks().min()-0.5, ax.get_xticks().max()+0.5, colors='#666666', linewidth=0.3)
plt.vlines(ax.get_yticks() + 0.5, ax.get_yticks().min()-0.5, ax.get_yticks().max()+0.5, colors='#666666', linewidth=0.3)

plt.imshow(meshRGB, aspect=0.55)

# Barra de color.
frame = ax.get_position().bounds
ax1 = fig.add_axes([frame[0]+frame[2]+0.03, frame[1], 0.02, frame[3]])
norm = mpl.colors.Normalize(vmin=0, vmax=meshMax)
cbar = mpl.colorbar.ColorbarBase(ax1, cmap=mpl.cm.RdPu, norm=norm, orientation='vertical')
cbar.set_label('\\# Encuestados', fontsize=7, rotation=270, labelpad=10)
cbar.ax.tick_params(labelsize=6)
for l in cbar.ax.yaxis.get_ticklabels():
    l.set_family('monospace')
    l.set_style('italic')
# Texto.
for i in range(len(mesh.values)):
    for j in range(len(mesh.values[0])):
        ax.text(j, i, mesh.values[i][j], fontsize=6, color=meshTextColors[i][j],
                horizontalalignment='center', verticalalignment='center',
                fontfamily='monospace', fontstyle='italic')
plt.savefig('Presentación/img/Disponibilidad.pdf', format='pdf', bbox_inches='tight', transparent=True)
#plt.show()

#%% Disponibilidad (días por semana)

dfDisD = df[['Lunes',
           'Martes',
           'Miércoles',
           'Jueves', 
           'Viernes',
           'Sábado',
           'Domingo']]

dfDisD = dfDisD.replace('Sin tiempo disponible', np.nan)
dfDisD = dfDisD.notna()
dfDisD = dfDisD.replace(False, 0)
dfDisD = dfDisD.sum(axis=1)
dfDisD = dfDisD.value_counts()
dfDisD = pd.DataFrame(dfDisD)
dfDisD.index.names = ['Index']
dfDisD = dfDisD.sort_values(by=dfDisD.index.names[0])
dfDisD_x = np.array(list(dfDisD.index)).astype(int)

dfDisD = pd.Series(dfDisD[0])

# Gráfica
colores = [colorDefecto]*len(dfDisD)
colores[0] = 'gray'
grafBarras(dfDisD_x, dfDisD, 
           'Número de días por semana que pueden dedicar al partido (mínimo de 1 a 3 hrs. por día)', 
           'Total de días', '\\# Encuestados', color=colores, titlepad=6, savefig='Presentación/img/Disponibilidad_dias.pdf')

#%% Disponibilidad (horas por semana)

# Código ineficiente, corregir.

dfDisH = df[['Lunes',
           'Martes',
           'Miércoles',
           'Jueves', 
           'Viernes',
           'Sábado',
           'Domingo']]

dfDisH = dfDisH.replace('Sin tiempo disponible', 0)
dfDisH = dfDisH.replace('1 a 3 hrs', 2)
dfDisH = dfDisH.replace('4 a 6 hrs', 5)
dfDisH = dfDisH.replace('6 a 8 hrs', 7)
dfDisH = dfDisH.replace('8 o más hrs', 10)
dfDisH = dfDisH.replace(np.nan, 0)
dfDisH = dfDisH.sum(axis=1)
dfDisH = dfDisH.value_counts()

# Ordenar de acuerdo a horas.
dfDisH = pd.DataFrame(dfDisH)
dfDisH.index.names = ['Index']
dfDisH = dfDisH.sort_values(by=dfDisH.index.names[0])

# Obtener rangos de edad.
dfDisH_x = np.array(list(dfDisH.index)).astype(int)
dfDisH_x = [rangoHoras(dfDisH_x[i]) for i in range(len(dfDisH_x))]
dfDisH = pd.concat([dfDisH, pd.Series(dfDisH_x, index=dfDisH.index, name='EdadID')], axis=1)
dfDisH_x = [rangoHorasDict[dfDisH_x[i]] for i in range(len(dfDisH_x))]

dfDisH = pd.concat([dfDisH, pd.Series(dfDisH_x, index=dfDisH.index, name='Edad')], axis=1)
dfDisH = dfDisH.groupby('Edad').agg({0:'sum', 'EdadID':'mean'})

dfDisH = dfDisH.sort_values(by='EdadID')

dfDisH_x = dfDisH.index
dfDisH = list(dfDisH[0])

# Gráfica
colores = [colorDefecto]*len(dfDisH)
colores[0] = 'gray'
grafBarras(dfDisH_x, dfDisH, 
           'Horas por semana que pueden didicar al partido', 
           'Rango horas', '\\# Encuestados', figsize=(6.2, 2.5), color=colores, savefig='Presentación/img/Disponibilidad_horas.pdf')

#%% Conexión a Internet

dfCI = df[['Internet regular en casa',
           'Datos móviles para vivienda',
           'Teléfono celular con Internet',
           'Conexión escuela, plazas públicas o cybercafés', 
           'Me conecto a internet de forma esporádica',
           'Otro (conexión a Internet)']]

# Valores nulos (NaN en todas las columnas de ocupación).
nulos = set(dfCI.loc[dfCI[dfCI.columns[0]].isnull(), dfCI.columns[0]].index)
for i in dfCI.columns:
    nulos = nulos & set(dfCI.loc[dfCI[i].isnull(), i].index)

dfCI_y = [[dfCI[i].count(), i] for i in dfCI.columns]
dfCI_y.append([len(nulos), 'Nulos'])
dfCI_y.sort(reverse=True)
dfCI_x = [i[1] for i in dfCI_y]
dfCI_y = [i[0] for i in dfCI_y]

dfCI_x = ['\n'.join(wrap(i, 20)) for i in dfCI_x]
dfCI_x[-1] = 'Otro'

# Gráfica
colores = [colorDefecto]*len(dfCI_x)
colores[2] = 'gray'
grafBarras(dfCI_x, dfCI_y, 'Conexión a Internet',
           'Tipo de conexión', '\\# Encuestados', color=colores, xtickfntsize=5,
           xtfontfam='sans-serif', xtfontsty='normal',
           savefig='Presentación/img/Conexion_Internet.pdf')

#%% Nivel de faimiliaridad con TI

dfTI_y = df['Nivel de faimiliaridad con TI'].value_counts(dropna=False)
dfTI_x = list(dfTI_y.index)
dfTI_x[3] = 'Nulos'

# Gráfica
colores = [colorDefecto]*len(dfTI_x)
colores[3] = 'gray'
grafBarras(dfTI_x, dfTI_y, 'Nivel de faimiliaridad con TI', 'Nivel de faimiliaridad',
           '\\# Encuestados', color=colores, xtfontfam='sans-serif', xtfontsty='normal',
           savefig='Presentación/img/Familiaridad_TI.pdf')

#%% Redes sociales

dfRS = df[['Facebook',
           'Discord',
           'Zoom',
           'Google meet', 
           'Jitsi meet',
           'Facebook messenger',
           'Whatsapp',
           'Telegram',
           'Ninguna']]

# Valores nulos (NaN en todas las columnas de ocupación).
nulos = set(dfRS.loc[dfRS[dfRS.columns[0]].isnull(), dfRS.columns[0]].index)
for i in dfRS.columns:
    nulos = nulos & set(dfRS.loc[dfRS[i].isnull(), i].index)

dfRS_y = [[dfRS[i].count(), i] for i in dfRS.columns]
dfRS_y.append([len(nulos), 'Nulos'])
dfRS_y.sort(reverse=True)
dfRS_x = [i[1] for i in dfRS_y]
dfRS_y = [i[0] for i in dfRS_y]

dfRS_x = ['\n'.join(wrap(i, 10)) for i in dfRS_x]

# Gráfica
colores = [colorDefecto]*len(dfRS_x)
colores[7] = 'gray'
grafBarras(dfRS_x, dfRS_y, 'Redes sociales', 'Red social', '\\# Encuestados',
           color=colores, figsize=mpl.rcParams['figure.figsize'],
           xtfontfam='sans-serif', xtfontsty='normal',
           savefig='Presentación/img/Redes_sociales.pdf')

#%% Análisis de vacíos

df = df[df.columns[2:]]
df = df.notna()
dfnull = df.sum(axis=1)
#dfnull.head(10)
dfnull = dfnull[dfnull==0]
#len(dfnull)
dft = pd.read_excel("Padron_Migala_07-12-21.xls", "Sheet1")
dft = dft[['Start Date (UTC)', 'Submit Date (UTC)']]
dft['Start Date (UTC)'] = pd.to_datetime(dft['Start Date (UTC)'], infer_datetime_format=True)
dft['Submit Date (UTC)'] = pd.to_datetime(dft['Submit Date (UTC)'], infer_datetime_format=True)
dft['Delta'] = dft['Submit Date (UTC)'] - dft['Start Date (UTC)']
dft.loc[dft.index.isin(dfnull.index), 'Delta'].min()
#%% Pruebas

len(df)
#print()
#print(mpl.rcParams.keys())
#for i in df.columns: print(i, df.loc[df['CURP']=='LOLA940606HVZPPL18', i].values[0])