#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pandas as pd
import numpy as np
#import scipy as sp
from sklearn.metrics import mean_absolute_error#, mean_squared_error
from sklearn.preprocessing import MinMaxScaler
from statsmodels.tsa.filters.hp_filter import hpfilter
from statsmodels.tsa.seasonal import seasonal_decompose
from statsmodels.tsa.holtwinters import SimpleExpSmoothing, ExponentialSmoothing
from statsmodels.tsa.stattools import adfuller, grangercausalitytests
from statsmodels.tsa.statespace.tools import diff
from statsmodels.tsa.ar_model import AutoReg, AR#, ARResults
from statsmodels.tsa.api import VAR#, DynamicVAR
from statsmodels.tsa.statespace.varmax import VARMAX#, VARMAXResults
from statsmodels.tsa.arima_model import ARMA, ARIMA#, ARMAResults, ARIMAResults
from statsmodels.tsa.statespace.sarimax import SARIMAX
from pmdarima import auto_arima
import matplotlib as mpl
import matplotlib.pyplot as plt
import seaborn as sns
from keras import Model, layers, models#, optimizers, Sequential
from keras.layers import Input, Dense, LSTM, Concatenate #, SimpleRNN, GRU, Activation, Layer
from keras.utils import plot_model
from keras.utils.generic_utils import get_custom_objects
from keras.preprocessing.sequence import TimeseriesGenerator
import keras.backend as K
from keras.callbacks import ModelCheckpoint #, ReduceLROnPlateau
from keras.models import load_model
from scipy.fft import fft, fftfreq, ifft
import os
import time

import warnings
warnings.filterwarnings('ignore', 'statsmodels.tsa.ar_model.AR', FutureWarning)
warnings.filterwarnings('ignore', 'statsmodels.tsa.arima_model.ARMA', FutureWarning)
warnings.filterwarnings('ignore', 'statsmodels.tsa.arima_model.ARIMA', FutureWarning)

dataBase = {
    0:"acea-water-prediction/Aquifer_Auser.csv",
    1:"acea-water-prediction/Aquifer_Doganella.csv",
    2:"acea-water-prediction/Aquifer_Luco.csv",
    3:"acea-water-prediction/Aquifer_Petrignano.csv",
    4:"acea-water-prediction/Lake_Bilancino.csv",
    5:"acea-water-prediction/River_Arno.csv",
    6:"acea-water-prediction/Water_Spring_Amiata.csv",
    7:"acea-water-prediction/Water_Spring_Lupa.csv",
    8:"acea-water-prediction/Water_Spring_Madonna_di_Canneto.csv"
}

# Import table.
df = pd.read_csv(dataBase[7])
# Convert 'Date' column to "datetime" type and make it index.
df['Date'] = pd.to_datetime(df['Date'], format='%d/%m/%Y')
df.set_index('Date', inplace=True)

cols = {
    -1:'Date',
    0:'Rainfall_Gallicano',
    1:'Rainfall_Pontetetto',
    2:'Rainfall_Monte_Serra',
    3:'Rainfall_Orentano',
    4:'Rainfall_Borgo_a_Mozzano',
    5:'Rainfall_Piaggione',
    6:'Rainfall_Calavorno',
    7:'Rainfall_Croce_Arcana',
    8:'Rainfall_Tereglio_Coreglia_Antelminelli',
    9:'Rainfall_Fabbriche_di_Vallico',
    10:'Depth_to_Groundwater_LT2',
    11:'Depth_to_Groundwater_SAL',
    12:'Depth_to_Groundwater_PAG',
    13:'Depth_to_Groundwater_CoS',
    14:'Depth_to_Groundwater_DIEC',
    15:'Temperature_Orentano',
    16:'Temperature_Monte_Serra',
    17:'Temperature_Ponte_a_Moriano',
    18:'Temperature_Lucca_Orto_Botanico',
    19:'Volume_POL',
    20:'Volume_CC1',
    21:'Volume_CC2',
    22:'Volume_CSA',
    23:'Volume_CSAL',
    24:'Hydrometry_Monte_S_Quirico',
    25:'Hydrometry_Piaggione',
    26:'t',
    27:'Sum_Rain',
    28:'Sum_Hydro'
}

# Target column key.
target = 1

def alarm(alarm_duration = 0.5, freq = 640, repeats = 5):
    for i in range(repeats):
        os.system('play -nq -t alsa synth {} sine {}'.format(alarm_duration, freq))
        time.sleep(0.5)

#%%
#%% Check missing values.

df.loc[df[cols[target]].notna(), cols[target]]
df.loc[df[cols[target]].isnull(), cols[target]]

#%%
#%% Visualize missing data.

df.index = df.index.strftime("%Y-%m-%d")

f, ax = plt.subplots(nrows=1, ncols=1, figsize=(16,5))
ax.tick_params(axis='x', labelsize=5)
#ax.set_xticks(df.index)
ax = sns.heatmap(df.T.isna(), cmap='Blues', xticklabels=366)
#ax.set_xticklabels(df['Date'])
#ax.xaxis.set_major_locator(mpl.dates.YearLocator())
#ax.xaxis.set_major_formatter(mpl.dates.DateFormatter('%d-%m-%Y'))
ax.set_title('Missing Values', fontsize=16)

for tick in ax.yaxis.get_major_ticks():
    tick.label.set_fontsize(14)
plt.show()

#%%
#%% Aquifer Auser data cleaning.

df['Rainfall_Monte_Serra'] = df['Rainfall_Monte_Serra'].interpolate()
# Fill the hole with same period of the previous year and interpolate in 'Rainfall_Piaggione'.
baseAux = df.loc[(df.index >= '2008-01-01') & (df.index <='2008-12-31'), 'Rainfall_Piaggione']
df.loc[(df.index >= '2009-01-02') & (df.index <='2009-12-31'), 'Rainfall_Piaggione'] = baseAux.values

# Convert outliers to NaN and interpolate missing values in 'Depth_to_Groundwater_LT2'.
df.loc[df[cols[10]] > -1, cols[10]] = np.nan
df[cols[10]] = df[cols[10]].interpolate()

# Convert outliers to NaN and interpolate missing values in 'Depth_to_Groundwater_SAL'.
df.loc[df[cols[11]] > -1, cols[11]] = np.nan
df[cols[11]] = df[cols[11]].interpolate()

# Copy previous valley into the biggest hole in 'Depth_to_Groundwater_PAG', then interpolate.
df.loc[(df.index >= '2014-03-21') & (df.index <= '2014-11-16') & (df[cols[12]].isnull()), cols[12]] = df.iloc[5555:5710, 12].values
df['Depth_to_Groundwater_PAG'] = df['Depth_to_Groundwater_PAG'].interpolate()

# Convert outliers to NaN and interpolate missing values in 'Depth_to_Groundwater_CoS'.
df.loc[df[cols[13]] > -1, cols[13]] = np.nan
df[cols[13]] = df[cols[13]].interpolate()

# Include a point to get a better patern and interpolate missing values in 'Depth_to_Groundwater_DIEC'.
df.loc['2020-03-29', cols[14]] = -3.9
df[cols[14]] = df[cols[14]].interpolate()

# Remove outlayers and fill them with immediately previous points in 'Volume_POL' e interpolar.
df.loc[df['Volume_POL'] < -1e+06, 'Volume_POL'] = np.nan
df.iloc[8031:8153, 19] = df.iloc[7880:8002, 19].values
df['Volume_POL'] = df['Volume_POL'].interpolate()

df['Hydrometry_Monte_S_Quirico'] = df['Hydrometry_Monte_S_Quirico'].interpolate()

# Shift one unit upwards and fill the hole with the same previous period in 'Hydrometry_Piaggione'.
df.iloc[4500:, 25] = df.iloc[4500:, 25] + 1
df.iloc[3772:4684, 25] = df.iloc[2859:3771, 25].values
df.iloc[2602, 25] = 0.11
df.iloc[1032, 25] = 0.8
df['Hydrometry_Piaggione'] = df['Hydrometry_Piaggione'].interpolate()

#%%
#%% Aquifer Doganella data cleaning.

df[cols[0]] = df[cols[0]].interpolate()
df[cols[1]] = df[cols[1]].interpolate()
df[cols[2]] = df[cols[2]].interpolate()

# Convert outliers to NaN and interpolate in Depth_to_Groundwater_Pozzo_2.
df.loc[df[cols[3]] < -110, cols[3]] = np.nan
df[cols[3]] = df[cols[3]].interpolate()

# Convert peaks afeter 2018 to NaN, add a point to interpolate and get a more congruent series in 
# Depth_to_Groundwater_Pozzo_3.
#df.loc[df[cols[4]] > -103, cols[4]] = np.nan
df.loc[(df.index > '2018') & (df[cols[4]] > -110), cols[4]] = np.nan
df.loc['2019-09-19', cols[4]] = -112.3
df[cols[4]] = df[cols[4]].interpolate()

df[cols[5]] = df[cols[5]].interpolate()

# Remove the sharp valley near 2018 and interpolate in Depth_to_Groundwater_Pozzo_5.
df.loc[(df.index >= '2017-06-01') & (df.index <='2018-06-01') & (df[cols[6]] < -104), cols[6]] = np.nan
df[cols[6]] = df[cols[6]].interpolate()

# Convert outliers to NaN and interpolate in Depth_to_Groundwater_Pozzo_6.
df.loc[(df.index >= '2019-01-01') & (df.index <='2020-01-01') & (df[cols[7]] > -92), cols[7]] = np.nan
df[cols[7]] = df[cols[7]].interpolate()

df[cols[8]] = df[cols[8]].interpolate()

# Convert outliers to NaN and interpolate in Depth_to_Groundwater_Pozzo_8.
df.loc[df[cols[9]] < -106, cols[9]] = np.nan
df[cols[9]] = df[cols[9]].interpolate()

df[cols[10]] = df[cols[10]].interpolate()

# Interpolate all volume series.
df.iloc[:, 11:19] = df.iloc[:, 11:19].interpolate()

#%%
#%% Aquifer Luco data cleaning.

# Replace the biggest hole of NaN's with the same period from 2011 to 2012 and interpolate in Rainfall_Simignano.
df.loc['2013-01-01':'2014-01-30', cols[0]] = df.loc['2011-01-01':'2012-01-30', cols[0]].values
df[cols[0]] = df[cols[0]].interpolate()

# Interpolate all rainfalls, except Pentolia, which will be ignored.
df.iloc[:, 1:8] = df.iloc[:, 1:8].interpolate()
df[cols[9]] = df[cols[9]].interpolate()
# Todos los valores de Rainfall_Pentolia a 0.
df[cols[8]] = 0

df.loc[:'2019-01-13', cols[10]] = df.loc[:'2019-01-13', cols[10]].interpolate()
df[cols[11]] = df[cols[11]].interpolate()

# Quitar outliers, llenar los huecos más grandes con los periodos inmediatos anteriores al revés (espejo) e 
# interpolar en Depth_to_Groundwater_Pozzo_3.
df.loc[(df.index >= '2018-12-01') & (df.index < '2019-01-31') & (df[cols[12]] > -9), cols[12]] = np.nan
df.loc['2019-08-21':'2019-11-10', cols[12]] = df.loc['2018-10-01':'2018-12-21', cols[12]].iloc[::-1].values + 0.8
df.loc['2020-04-07':'2020-04-26', cols[12]] = df.loc['2020-03-19':'2020-04-07', cols[12]].iloc[::-1].values
df[cols[12]] = df[cols[12]].interpolate()

df[cols[13]] = df[cols[13]].interpolate()

#%%
#%% Aquifer Petrignano data cleaning.

# Convert outliers to NaN in Volume_C10_Petrignano.
df.loc[df[cols[5]] == 0, cols[5]] = np.nan

# Fill the biggest NaN hole with the immediately next period flipped (like a mirror) in 
# Hydrometry_Fiume_Chiascio_Petrignano.
df.loc[df[cols[6]] == 0, cols[6]] = df.loc['2015-09-22':'2016-02-18', cols[6]].iloc[::-1].values

# Interpolate all columns.
df = df.interpolate()

#%%
#%% Lake Bilancino data cleaning.

df = df.interpolate()

#%%
#%% River Arno data cleaning.

# Fill the biggest NaN hole in 2008 with a similar period from 2005, convert outliers to NaN and interpolate in 
# Hydrometry_Nave_di_Rosano.
df.loc['2008-07-03':'2008-12-31', cols[15]] = df.loc['2005-06-03':'2005-12-01', cols[15]].values
df.loc[df[cols[15]] == 0, cols[15]] = np.nan
df[cols[15]] = df[cols[15]].interpolate()

#%%
#%% Water Spring Amiata data cleaning.

# Fill the NaN holes with similar periods in Flow_Rate_Bugnano.
df.loc['2018-08-01':'2018-08-31', cols[11]] = df.loc['2018-05-01':'2018-05-31', cols[11]].values + 0.003
df.loc['2018-12-01':'2018-12-31', cols[11]] = df.loc['2018-03-01':'2018-03-31', cols[11]].values - 0.035
df.loc['2019-01-01':'2019-01-31', cols[11]] = df.loc['2018-03-01':'2018-03-31', cols[11]].values - 0.05

# Fill the NaN holes with similar periods in Flow_Rate_Arbure.
df.loc['2018-04-01':'2018-04-30', cols[12]] = df.loc['2017-10-01':'2017-10-30', cols[12]].values + 0.8
df.loc['2018-08-01':'2018-08-31', cols[12]] = df.loc['2017-11-01':'2017-12-01', cols[12]].values - 0.4
df.loc['2018-08-31', cols[12]] = df.loc['2018-08-30', cols[12]]

df.loc['2018-12-01':'2018-12-31', cols[12]] = df.loc['2018-11-01':'2018-12-01', cols[12]].values - 0.1
df.loc['2018-12-31':'2019-01-31', cols[12]] = df.loc['2018-10-30':'2018-11-30', cols[12]].values

# Fill the NaN holes with similar periods in and descend the anomaly in Flow_Rate_Ermicciolo.
df.loc['2016-02-01':'2016-02-29', cols[13]] = df.loc['2016-03-01':'2016-03-29', cols[13]].values - 0.1
df.loc['2016-08-01':'2016-10-31', cols[13]] = df.loc['2016-03-01':'2016-05-31', cols[13]].values - 0.05
df.loc['2019-09-01':'2019-12-31', cols[13]] -= 2.5

#%%
#%% Water Spring Lupa data cleaning.

df = df.interpolate()

#%%
#%% Water Madonna di Canneto data cleaning.

# Just interpolate in Flow_Rate_Madonna_di_Canneto.
df[cols[2]] = df[cols[2]].interpolate()

#%%
#%% Append accumulated rain and hydrometry columns.

size_win = 182
df['Sum_Rain'] = 0
df['Sum_Hydro'] = 0
#for i in range(1): df['Sum_Rain'] += df[cols[i]].rolling(size_win).sum()
#for i in range(24, 26): df['Sum_Hydro'] += df[cols[i]].rolling(size_win).sum()
df['Sum_Hydro'] += df[cols[target]].rolling(size_win).sum()

#%%
#%% continuation.

corr_R_min = [10000, 0]
corr_H_min = [10000, 0]
corr_R_max = [0, 0]
corr_H_max = [0, 0]

caus_R_min = [10000, 0]
caus_H_min = [10000, 0]
caus_R_max = [0, 0]
caus_H_max = [0, 0]

for j in range (1, 100):
    size_win = j
    df['Sum_Rain'] = 0
    df['Sum_Hydro'] = 0
    for i in range(10): df['Sum_Rain'] += df[cols[i]].rolling(size_win).sum()
    for i in range(24, 26): df['Sum_Hydro'] += df[cols[i]].rolling(size_win).sum()
    result = df[cols[target]].iloc[size_win+1:].corr(df['Sum_Rain'])
    if abs(result) < corr_R_min[0]:
        corr_R_min[0] = result; corr_R_min[1] = j
    if abs(result) > corr_R_max[0]:
        corr_R_max[0] = result; corr_R_max[1] = j
    result = df['Sum_Hydro'].corr(df[cols[target]].iloc[size_win+1:])
    if abs(result) < corr_H_min[0]:
        corr_H_min[0] = result; corr_H_min[1] = j
    if abs(result) > corr_H_max[0]:
        corr_H_max[0] = result; corr_H_max[1] = j
    results = grangercausalitytests(df[[cols[target], 'Sum_Rain']].iloc[size_win:], maxlag=3, verbose=False)
    if abs(results[1][0]['ssr_ftest'][1]) < caus_R_min[0]:
        caus_R_min[0] = results[1][0]['ssr_ftest'][1]; caus_R_min[1] = j
    if abs(results[1][0]['ssr_ftest'][1]) > caus_R_max[0]:
        caus_R_max[0] = results[1][0]['ssr_ftest'][1]; caus_R_max[1] = j
    results = grangercausalitytests(df[[cols[target], 'Sum_Hydro']].iloc[size_win:], maxlag=3, verbose=False)
    if abs(results[1][0]['ssr_ftest'][1]) < caus_H_min[0]:
        caus_H_min[0] = results[1][0]['ssr_ftest'][1]; caus_H_min[1] = j
    if abs(results[1][0]['ssr_ftest'][1]) > caus_H_max[0]:
        caus_H_max[0] = results[1][0]['ssr_ftest'][1]; caus_H_max[1] = j
    
    if not j%10: print(j)

print('corr_R_min =', corr_R_min)
print('corr_R_max =', corr_R_max)
print('corr_H_min =', corr_H_min)
print('corr_H_max =', corr_H_max, '\n')

print('caus_R_min =', caus_R_min)
print('caus_R_max =', caus_R_max)
print('caus_H_min =', caus_H_min)
print('caus_H_max =', caus_H_max)

#df['Diff'] = df['Sum_Rain'] - df['Sum_Hydro']

#%%
#%% Trim domain.

#df = df.loc['2012-06-01':'2020-07-01']

# Depth_to_Groundwater_LT2
#df = df.loc['2015-04-16':'2020-07-01']
# Depth_to_Groundwater_SAL
#df = df.loc['2013-08-02':'2020-07-01']
# Depth_to_Groundwater_SAL
#df = df.loc['2015-10-10':'2020-07-01']

# Depth_to_Groundwater_Pozzo_1
#df = df.loc['2017-06-01':'2020-07-01']
# Depth_to_Groundwater_Pozzo_2
#df = df.loc['2015-01-01':'2020-07-01']
# Depth_to_Groundwater_Pozzo_3
#df = df.loc['2017-01-01':'2020-07-01']
# Depth_to_Groundwater_Pozzo_4
#df = df.loc['2017-01-01':'2020-07-01']
# Depth_to_Groundwater_Pozzo_5
#df = df.loc['2017-05-20':'2020-07-01']
# Depth_to_Groundwater_Pozzo_6
#df = df.loc['2017-05-21':'2020-07-01']
# Depth_to_Groundwater_Pozzo_7
#df = df.loc['2017-05-23':'2020-07-01']
# Depth_to_Groundwater_Pozzo_8
#df = df.loc['2017-08-01':'2020-07-01']
# Depth_to_Groundwater_Pozzo_9
#df = df.loc['2018-05-20':'2020-07-01']

# Depth_to_Groundwater_Podere_Casetta
#df = df.loc['2008-02-21':'2019-01-01']

# Depth_to_Groundwater_P24
#df = df.loc['2014-04-21':'2020-07-01']
# Depth_to_Groundwater_P25
#df = df.loc['2014-04-21':'2020-07-01']

# Lake_Level
#df = df.loc['2013-03-18':'2020-07-01']
# Flow_Rate
#df = df.loc['2002-06-03':'2020-07-01']


# Hydrometry_Nave_di_Rosano
#df = df.loc['2015-04-16':'2020-07-01']

# Flow_Rate_Bugnano
#df = df.loc['2018-03-01':'2020-07-01']
# Flow_Rate_Arbure
#df = df.loc['2018-06-01':'2020-07-01']
# Flow_Rate_Ermicciolo
#df = df.loc['2018-04-01':'2020-07-01']
# Flow_Rate_Galleria_Alta
#df = df.loc['2015-01-01':'2020-07-01']

# Flow_Rate_Lupa
df = df.loc['2020-03-05':'2020-07-01']

# Flow_Rate_Madonna_di_Canneto
#df = df.loc['2019-11-05':'2020-07-01']

df_orig = df.copy()

#%%
#%% Insert scalar time column.

df.insert(len(df.columns), 't', np.array(range(len(df))).astype('float64'), True) 

#%%
#%% Visualize.

#print(mpl.rcParams.keys())
mpl.rcParams['figure.dpi'] = 200
mpl.rcParams['figure.figsize'] = [8.0, 4.0]
mpl.rcParams['xtick.major.pad'] = 1
mpl.rcParams['xtick.labelsize'] = 5
#mpl.rcParams['date.autoformatter.year'] = '%Y'

def visualizeCol(table, numCol):
    plt.figure().subplots().xaxis.set_major_locator(mpl.dates.YearLocator());
    plt.tick_params(axis='x', labelrotation=30);
    plt.title(table.columns[numCol])
    plt.plot(table[table.columns[numCol]])
    plt.show()

def visualizeCols(table):
    plt.title(df.index.name)
    plt.plot(df.index, df.index)
    for col in table.columns:
        plt.figure().subplots().xaxis.set_major_locator(mpl.dates.YearLocator());
        plt.tick_params(axis='x', labelrotation=30);
        plt.title(col)
        plt.plot(table[col]);
        plt.show();

#visualizeCols(df)
visualizeCol(df, target)

#%% Set train and target columns.

train_columns = [#'Rainfall_Gallicano', 
                 #'Rainfall_Pontetetto', 
                 #'Rainfall_Monte_Serra', 
                 #'Rainfall_Orentano', 
                 #'Rainfall_Borgo_a_Mozzano', 
                 #'Rainfall_Piaggione', 
                 #'Rainfall_Calavorno', 
                 #'Rainfall_Croce_Arcana', 
                 #'Rainfall_Tereglio_Coreglia_Antelminelli', 
                 #'Rainfall_Fabbriche_di_Vallico',
                 #'Depth_to_Groundwater_LT2',
                 #'Depth_to_Groundwater_SAL',
                 #'Depth_to_Groundwater_PAG',
                 #'Depth_to_Groundwater_CoS',
                 #'Depth_to_Groundwater_DIEC',
                 #'Temperature_Orentano',
                 #'Temperature_Monte_Serra',
                 #'Temperature_Ponte_a_Moriano',
                 #'Temperature_Lucca_Orto_Botanico',
                 #'Volume_POL',
                 #'Volume_CC1',
                 #'Volume_CC2',
                 #'Volume_CSA',
                 #'Volume_CSAL',
                 #'Hydrometry_Monte_S_Quirico',
                 #'Hydrometry_Piaggione',
                 't',
                 #'Sum_Rain',
                 #'Sum_Hydro'
                 ]

target_columns = [cols[target]]

# Missing values test for train and target columns.
for col in train_columns + target_columns:
    if(df[col].isnull().values.any()): print(f'There are NaN values in {col}.')

# Replace missing values with zeros.
#train_data = train_data.fillna(0)
#validation_data = validation_data.fillna(0)

#%%
#%% Several input layers (not several nodes in one input layer, but several input layers with one or more nodes).

# Columnas que integran cada capa de entrada.
inputLayer = []
inputLayer.append(cols[0:9 + 1] + cols[15:16 + 1] + cols[19:20 + 1] + cols[24:25 + 1])

#%%
#%% Sub-sampling.

freq_sample = 'W'
df = df.resample(rule=freq_sample).mean()
df_orig = df.copy()

#%% Smoothing and component split.

#%% Hodrick-Prescott filter.

# Lambda values: 6.25 (annual), 100 (biannual), 129600 (monthly), 
# 33177600 (weekly), 110930628906.25 (dayly).

# Smoothed columns.
l_cols = [cols[target]]

for col in l_cols:
    cycle, trend = hpfilter(df[col], lamb=110930628906.25)
    fig, ax = plt.subplots(2,1)
    plt.suptitle('Hodrick-Prescott filter')
    plt.subplot(211, xticklabels=[])
    plt.ylabel('Trend')
    plt.plot(trend)
    plt.subplot(212)
    plt.ylabel('Ciclic')
    plt.plot(cycle)
    plt.show()
    
    plt.title('Hodrick-Prescott filter')
    plt.plot(df[col], label = 'Original')
    plt.plot(trend, label = 'Filtered')
    plt.legend()
    plt.show()
    
    print('MAE: ' + str(mean_absolute_error(df[col], trend)))
    
    trend[trend == trend['2020-01-01':].max()]
    df[col] = trend

#%%
#%% continuation: Second filter just to cyclic component.

cycle2, trend2 = hpfilter(cycle, lamb=129600)
fig, ax = plt.subplots(2,1)
plt.suptitle('Hodrick-Prescott filter')
plt.subplot(211, xticklabels=[])
plt.ylabel('Trend')
plt.plot(trend2)
plt.subplot(212)
plt.ylabel('Ciclic')
plt.plot(cycle2)
plt.show()

plt.title('Hodrick-Prescott filter')
plt.plot(cycle, label = 'Original')
plt.plot(trend2, label = 'Filtered')
plt.legend()
plt.show()

#%%
#%% FFT

N = len(trend2)

yf = fft(trend2.to_numpy())
xf = fftfreq(N, 1)

y2f = ifft(yf)

plt.plot(xf, yf)
plt.show()

high_freq_fft = yf.copy()
high_freq_fft[np.abs(yf) < 20] = 0
plt.plot(xf, high_freq_fft)
plt.show()
y_high_freq = ifft(high_freq_fft)

plt.title('FFT')
plt.plot(trend2.to_numpy(), label='Real')
plt.plot(y_high_freq, label='Forecast')
plt.legend()
plt.show()

# Re-build signal.

signal = np.array([])
point = 0
for k in range(len(xf)):
    for n in range(len(yf)):
        point += yf[n].real*np.cos(xf[n]*k) + yf[n].imag*np.sin(xf[n]*k)
    signal = np.append(signal, point)
    point = 0

plt.plot(signal)
    
#%%
#%% ETS decomposition.

ets_decompose = seasonal_decompose(df[cols[target]], model='aditive')     # Test 'aditive' and 'multiplicative'.
#ets_decompose.plot();
fig, ax = plt.subplots(3,1)
plt.suptitle('ETS decomposition')
plt.subplot(311, xticklabels=[])
plt.ylabel('Trend')
plt.plot(ets_decompose.trend)
plt.subplot(312, xticklabels=[])
plt.ylabel('Seasonal')
x_min = ets_decompose.trend[ets_decompose.trend.notna()].index.min()
x_max = ets_decompose.trend[ets_decompose.trend.notna()].index.max()
plt.plot(ets_decompose.seasonal[x_min:x_max])
plt.subplot(313)
plt.ylabel('Residual')
plt.plot(ets_decompose.resid)
plt.show()
#plt.plot(ets_decompose.trend + ets_decompose.seasonal + ets_decompose.resid)

#%%
#%% Simple smoothing: Exponentially Weighted Moving Averages (EWMA).

span = 12
alpha = 2/(span+1)
ewma = SimpleExpSmoothing(df[cols[target]]).fit(smoothing_level=alpha, optimized=False).fittedvalues.shift(-1)
plt.title('Simple smoothing (EWMA)')
plt.plot(ewma)
plt.show()

# Double smoothing.
des = ExponentialSmoothing(df[cols[target]], trend='add').fit().fittedvalues.shift(-1)
plt.title('Double smoothing (EWMA)')
plt.plot(des)
plt.show()

# Triple smoothing.
tes = ExponentialSmoothing(df[cols[target]], trend='add', seasonal='add', seasonal_periods=52).fit().fittedvalues
plt.title('Triple smoothing (EWMA)')
plt.plot(tes)
plt.show()

#%%
#%% Correlation and covarianze.

# Correlation.

# Correlation matrix.
correlations = df.corr()

# Visualize.
names = df.columns
fig = plt.figure()
ax = fig.add_subplot(111)
cax = ax.matshow(correlations, vmin=-1, vmax=1)
fig.colorbar(cax)
ticks = np.arange(0,len(names))
plt.tick_params(axis='x', labelrotation=90, pad=3);
plt.tick_params(axis='y', pad=3);
ax.set_xticks(ticks)
ax.set_yticks(ticks)
ax.set_xticklabels(names, fontsize=4)
ax.set_yticklabels(names, fontsize=4)
plt.show()

def maxCorr(data_base, not_shift_cols):

    max_shift = int(len(data_base)/4)
    max_corr = data_base.corr()
    
    for i in range(len(max_corr.columns)): max_corr[cols[i]] = 0.0
    
    for i in range(-max_shift, max_shift):
        
        shifted_db = data_base
        for j in range(len(shifted_db.columns)):
        
            if j not in not_shift_cols: shifted_db[cols[j]] = shifted_db[cols[j]].shift(i)
        
        correlation = shifted_db.corr()
        
        for k in range(len(correlation.columns)):
            for l in range(len(correlation.columns)):
                
                if abs(correlation.loc[cols[k], cols[l]]) > abs(max_corr.loc[cols[k], cols[l]]):
                    max_corr.loc[cols[k], cols[l]] = correlation.loc[cols[k], cols[l]].copy()
    
    return max_corr

correlations = maxCorr(df, [10, 11, 12, 13, 14])

# Visualizar.
names = df.columns
fig = plt.figure()
ax = fig.add_subplot(111)
cax = ax.matshow(correlations, vmin=-1, vmax=1)
fig.colorbar(cax)
ticks = np.arange(0,len(names))
plt.tick_params(axis='x', labelrotation=90, pad=3);
plt.tick_params(axis='y', pad=3);
ax.set_xticks(ticks)
ax.set_yticks(ticks)
ax.set_xticklabels(names, fontsize=4)
ax.set_yticklabels(names, fontsize=4)
plt.show()

#%%
#%% Rolling window correlation.

correlation = df.rolling(250).corr(df[cols[target]])
#correlation = df.pct_change().rolling(250).corr(df[cols[target]].pct_change())

#plt.plot(correlation)
#plt.plot(correlation[cols[target]])
#plt.show()

# Covarianze matrix.
covariance = df.cov()

# Visualize.
names = df.columns
fig = plt.figure()
ax = fig.add_subplot(111)
cax = ax.matshow(covariance)
fig.colorbar(cax)
ticks = np.arange(0,len(names))
plt.tick_params(axis='x', labelrotation=90, pad=3);
plt.tick_params(axis='y', pad=3);
ax.set_xticks(ticks)
ax.set_yticks(ticks)
ax.set_xticklabels(names, fontsize=4)
ax.set_yticklabels(names, fontsize=4)
plt.show()

#%%
#%% Seasonality and causality tests.

#%% Augmented Dickey-Fuller seasonality test.

DFtest = adfuller(df[cols[target]], autolag='AIC')
if DFtest[1] < 0.05: print("La serie es estacionaria.\n")
else: print("La serie no es estacionaria.\n")

#%%
#%% Granger causality test (if prediction accounts for exogenous data).

compare_columns = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25]
for i in compare_columns:
    
    results = grangercausalitytests(df[[cols[11],cols[i]]], maxlag=3, verbose=False)
    
    count_valid = 0
    for j in range(1,len(results)+1):
        if (results[j][0]['ssr_ftest'][1] < 0.05): count_valid += 1
    
    if count_valid > 0: print(cols[i] + " es causal en", count_valid, "lags. p=", results[j][0]['ssr_ftest'][1])
    else: print(cols[i] + " no es causal. p=", results[j][0]['ssr_ftest'][1])

#%%
#%% Make series stationary.

# Save original.
df_orig = df
#df = df_orig

# By differentiation.
df = diff(df, k_diff=1)

#%%
#%% Prepare train and validation bases.

#%% Scale data to [0,1] (optional).

# Scale all columns (except index) to ~[0,1] range, to feed neural networks.
scaler = MinMaxScaler()
scaler.fit(df.iloc[:,:])
df.iloc[:,:] = scaler.transform(df.iloc[:,:])

# Scale all columns except 't'.
scaler.fit(df[target_columns + train_columns[:-1]])
df[target_columns + train_columns[:-1]] = scaler.transform(df[target_columns + train_columns[:-1]])

#%% Divide base in train and validation ("aux" if it's required to use the other columns).

#point_start = '2017-06-01'
point_partition = '2020-06-01'
second_point = '2020-06-15'     # If there is test data.
point_end = '2020-07-01'

train_data_aux = df[:point_partition]
validation_data_aux = df[point_partition:second_point]

test_data_aux = df[second_point:point_end]

train_target_data =  train_data_aux[target_columns]
train_data = train_data_aux[train_columns]
validation_target_data = validation_data_aux[target_columns]
validation_data = validation_data_aux[train_columns]

test_target_data = test_data_aux[target_columns]
test_data = test_data_aux[train_columns]

# Visualizar entrenemiento y validación.
plt.plot(train_target_data[cols[target]], label='Train')
plt.plot(validation_target_data[cols[target]], label='Validation')
plt.legend()
plt.show()

#%% Columns for several input layers in neural networks.

train_input_layers = []
validation_input_layers = []
for i in range(len(inputLayer)):
    train_input_layers.append(train_data[inputLayer[i]])
    validation_input_layers.append(validation_data[inputLayer[i]])

#%% Preprocessing of train and validation bases.

# Transforma base into NumPy.
train_data = train_data.to_numpy()
train_target_data = train_target_data.to_numpy()
validation_data = validation_data.to_numpy()
validation_target_data = validation_target_data.to_numpy()

test_data = test_data.to_numpy()
test_target_data = test_target_data.to_numpy()

#%% For various input layers in neural networks.

for i in range(len(train_input_layers)):
    train_input_layers[i] =  train_input_layers[i].to_numpy()
    validation_input_layers[i] = validation_input_layers[i].to_numpy()

#%%
#%% Autoregression (AR)

# Deprecated version.

model = AR(train_data)
ar= model.fit(method='mle')
start = len(train_data)
end = len(train_data) + len(validation_data) - 1
predictions = ar.predict(start=start, end=end, dynamic=False).rename('AR Predictions')

# How many parameters are there?
print(f'Lag: {ar.k_ar}')
print(f'Coefficients:\n{ar.params}')

plt.title('AR')	
plt.plot(df[cols[target]].loc[point_partition:], label='Original')
plt.plot(predictions, label='Forecast')
plt.legend()
plt.show()

# New version.

model = AutoReg(train_data, lags=25, old_names=False)
ar = model.fit()

start = len(train_data)
end = len(train_data) + len(validation_data) - 1
predictions = ar.predict(start=start, end=end, dynamic=False).rename('AR Predictions')

print(ar.aic, ar.hqic, ar.bic)

plt.title('AR')	
plt.plot(df[cols[target]].loc[point_partition:], label='Original')
plt.plot(predictions, label='Forecast')
plt.legend()
plt.show()

#%%
#%% Vectorial autoregression (VAR).

# Make Seasonality test.
for col in train_columns:
    dftest = adfuller(df[col], autolag='AIC')
    if dftest[1] > 0.05: print(col, "no es estacionaria.")

n_val = len(validation_data)

# Prove various "p" values and use the model with best "AIC" and "BIC" ranks.
model = VAR(train_data)
for i in range(1,55):
	results = model.fit(i)
	print('Order =', i)
	print('AIC: ', results.aic)
	print('BIC: ', results.bic)

# Verify what series are in the model modelo.
model.endog_names

# Prove differents "p" values.
for p_ in range(1,54):
    # Train with the best model.
    p = 54                      # Give "p" parameter.
    results = model.fit(p_)
    #results.summary()
    
    # Predict.
    lag_order = results.k_ar
    z = results.forecast(y=train_data.values[-lag_order:], steps=n_val)		# 'steps': How many points to predict?.
    
    # Convert to 'DataFrame'.
    df_forecast = pd.DataFrame(z, index=validation_data.index, columns=train_columns)
    
    # Revert diferentiation to original series (repeat the times that you have done the diferentiation).
    for col in target_columns:
        df_forecast[col] = df_orig[col].iloc[-n_val-1] + df_forecast[col].cumsum()
    
    # Visualize.
    plt.title(f'p = {p_}')
    plt.plot(df_orig[col].loc[point_partition:], label='Original')
    plt.plot(df_forecast[col], label='Forecast')
    plt.legend()
    plt.show()
    
    print("MAE: " + str(mean_absolute_error(df_orig[col].loc[point_partition:], df_forecast[col])), " p = ", p_)

# Experiments joining two predictions for two "p" values.

results1 = model.fit(19)
lag_order1 = results1.k_ar
z1 = results1.forecast(y=train_data.values[-lag_order1:], steps=n_val)
df_forecast1 = pd.DataFrame(z1, index=validation_data.index, columns=train_columns)

results2 = model.fit(40)
lag_order2 = results2.k_ar
z2 = results2.forecast(y=train_data.values[-lag_order2:], steps=n_val)
df_forecast2 = pd.DataFrame(z2, index=validation_data.index, columns=train_columns)

df_forecast = pd.concat([df_forecast1.loc[:'2019-10-13'], df_forecast2.loc['2019-10-20':]])

for col in target_columns:
    df_forecast1[col] = df_orig[col].iloc[-n_val-1] + df_forecast1[col].cumsum()
    df_forecast2[col] = df_orig[col].iloc[-n_val-1] + df_forecast2[col].cumsum()
    df_forecast[col] = df_orig[col].iloc[-n_val-1] + df_forecast[col].cumsum()

#plt.title(f'p = {p_}')
plt.plot(df_orig[col].loc[point_partition:], label='Original')
plt.plot(df_forecast[col], label='Forecast')
plt.legend()
plt.show()

print("MAE: " + str(mean_absolute_error(df_orig[col].loc[point_partition:], df_forecast[col])), " p = ", p_)

#%%
#%% Vector Auto-Regressive Moving Average (VARMA).

# Seasonality test.
for col in train_columns:
    dftest = adfuller(df[col], autolag='AIC')
    if dftest[1] > 0.05: print(col, "no es estacionaria.")

# Verify "d" term of ARIMA model in order to see how many differentiations will be required.
for col in target_columns:
    print(auto_arima(df[col], maxiter=1000).summary())

# Make differentiations if it's required.

n_val = len(validation_data)

model = VARMAX(train_data, order=(1,3), trend='c')     # Put the parameters obtained in "order".
results = model.fit(maxiter=1000, disp=False)
results.summary()

df_forecast = results.forecast(n_val)

# Revert the diferentiatión to the original series (repeat the times the diferentiation has been realized).
for col in target_columns:
    df_forecast[col] = df_orig[col].iloc[-n_val-1] + df_forecast[col].cumsum()

# Visualize.
plt.title('VARMA')	
plt.plot(df_orig[col].loc[point_partition:], label='Original')
plt.plot(df_forecast[col], label='Forecast')
plt.legend()
plt.show()

print("MAE: " + str(mean_absolute_error(df_orig[col].loc[point_partition:], df_forecast[col])))

#%%
#%% ARMA.

# It doesn't requires the series to be stationary.
#df = df_orig

auto_arima(df[cols[target]], seasonal=True).summary()

model = ARMA(train_data[cols[target]], order=(1,2))
results = model.fit()
results.summary()

# Predict.
start = len(train_data)
end = len(train_data) + len(validation_data) - 1
predictions = results.predict(start=start, end=end).rename('ARMA Predictions')
		
# Visuaize predictions vs real data.
plt.title('ARMA')
plt.plot(validation_data, label='Original')
plt.plot(predictions, label='Forecast')
plt.legend()
plt.show()

print("MAE: " + str(mean_absolute_error(validation_data[cols[target]], predictions)))

#%%
#%% ARIMA.

stepwise_fit = auto_arima(df[cols[target]], start_p = 0, start_q = 0,
                          			max_p = 2, max_q = 2, m = 2,   # If "m" is a big number, it will take too much memory.
                          			seasonal = True,				# Change to true if there are periodic data.
                          			d = None, trace = True,
                          			error_action = 'ignore',		# Don't inform if an order didn't work.
                          			suppress_warnings = True,		# Without convergence warnings.
                          			stepwise = True)

model = ARIMA(train_data, order=(2,2,0))
results = model.fit()
results.summary()
		
start = len(train_data)
end = len(train_data) + len(validation_data) - 1
predictions = results.predict(start=start, end=end, dynamic=False, typ='levels').rename('ARIMA Predictions')

plt.title('ARIMA')	
plt.plot(validation_data, label='Original')
plt.plot(predictions, label='Forecast')
plt.legend()
plt.show()

print("MAE: " + str(mean_absolute_error(validation_data[cols[target]], predictions)))

#%%
#%% SARIMA.

# Get the 7 parameters.
auto_arima(df[cols[target]], seasonal=True).summary()

model = SARIMAX(train_data, order=(1,2,2), seasonal_order=(1,0,[],7))
results = model.fit()
results.summary()

start = len(train_data)
end = len(train_data) + len(validation_data) - 1
prediction = results.predict(start=start, end=end, dynamic=False, typ='levels').rename('SARIMA Predictions') 

plt.title('SARIMA')	
plt.plot(validation_data, label='Original')
plt.plot(predictions, label='Forecast')
plt.legend()
plt.show()

print("MAE: " + str(mean_absolute_error(validation_data[cols[target]], predictions)))

#%%
#%% SARIMAX.

# Allows adding more than one variable.

exog_columns = train_columns
exog_columns.remove(cols[target])

# Get the 7 parameters.
auto_arima(df[cols[target]], exogenous=df[exog_columns], seasonal=True, m=5).summary()

model = SARIMAX(train_data[cols[target]], exog=train_data[exog_columns], order=(1,1,3), 
                seasonal_order=(2,0,[],7), enforce_invertibility=False)

results = model.fit()
results.summary()

start=len(train_data)
end=len(train_data) + len(validation_data) - 1
exog_forecast = validation_data[exog_columns]
predictions = results.predict(start=start, end=end, exog=exog_forecast).rename('SARIMAX Predictions')

plt.title('SARIMAX')	
plt.plot(validation_data[cols[target]], label='Original')
plt.plot(predictions, label='Forecast')
plt.legend()
plt.show()

print("MAE: " + str(mean_absolute_error(validation_data[cols[target]], predictions)))

#%%
#%% Recurrent Neural Network.

#%% Prepare LSTM tensors.

# Mini-series length (only for LSTM).
len_mini_series_dic = {'W':52, 'SM':26, 'M':12}
len_mini_series = len_mini_series_dic[freq_sample]
#len_mini_series = 0

# Generate outputs for predictions of more than one point.
win = 8     # Window size (predictions number).
#targets_train = np.array([train_data[i:i+win, 0] for i in range(len(train_data) - win + 1)])
#targets_validation = np.array([validation_data[i:i+win, 0] for i in range(len(validation_data) - win + 1)])

# Mini-series generator for LSTM.
generatorTrain = TimeseriesGenerator(train_data, train_target_data, length=len_mini_series, batch_size=1)
generatorValidation = TimeseriesGenerator(validation_data, targets=validation_target_data, length=len_mini_series, batch_size=1)

# If there are several outputs.
#generatorTrain = TimeseriesGenerator(train_data[:-win+1], targets_train, length=len_mini_series, batch_size=1)
#generatorValidation = TimeseriesGenerator(validation_data[:-win+1], targets_validation, length=len_mini_series, batch_size=1)

#print(generatorTrain[0])

#%%
#%% Recurrent net.

epoc = 100  
batch_s = 1        # It's included in miniseries.

il = Input(shape=(len_mini_series, train_data.shape[1]))    # shape=(len_mini_series, train_data.shape[1])
# Several input layers.
#il1 = Input(shape=train_input_layers[0].shape[-1])
#il2 = Input(shape=train_input_layers[1].shape[-1])

l1 = LSTM(100, activation='tanh', return_sequences=False)(il)
#l1 = GRU(100, activation='relu', return_sequences=False)(il)
#l1 = SimpleRNN(100, activation='relu', return_sequences=False)(il)

# Sine and cosine layers.
#l2 = Dense(100, activation=K.cos)(l1)
#l3 = Dense(100, activation=K.sin)(l1)
#lc1 = Concatenate()([l2, l3])

#l2 = Dense(50, activation='relu')(l1)
#l3 = Dense(50, activation='relu')(l2)

ol = Dense(1, activation='linear')(l1)

model = Model(inputs=il, outputs=ol, name='CustomNN')
# Various input layers.
#model = Model(inputs=[il1, il2], outputs= ol, name='CustomNN')

get_custom_objects().update({'cos':K.cos, 'sin':K.sin})

callbacks_list = [
    ModelCheckpoint(filepath='my_model.h5', monitor='val_loss', save_best_only=True),
    #ReduceLROnPlateau(monitor='val_loss', factor=0.8, patience=25)
]

model.compile(optimizer='adam', loss='mae')
history = model.fit(generatorTrain,  epochs=epoc, batch_size=None, 
                    validation_data=generatorValidation, callbacks=callbacks_list)
#history = model.fit(train_data, train_target_data, batch_size=batch_s,  epochs=epoc, 
#                    validation_data=(validation_data, validation_target_data), callbacks=callbacks_list)
# Various input layers.
#history = model.fit(train_input_layers, train_target_data,  epochs=epoc, batch_size=batch_s, 
#                    validation_data=(validation_input_layers, validation_target_data), callbacks=callbacks_list)

model = load_model('my_model.h5')

# Model info.
model.summary()

# Visualize net.
#plot_model(model, show_shapes=True)

# Evaluate in a test data base.
#test_acc = model.evaluate(validation_data, validation_target_data)
#print(test_acc)

# Save model.
#model.save('RNN.h5')

# Visualize training and validation error.
mpl.rcParams['xtick.labelsize'] = 'medium'
history_dict = history.history
#print(history_dict.keys())
loss_values = history_dict['loss']
val_loss_values = history_dict['val_loss']
epochs = range(1, len(history_dict['loss']) + 1)
plt.plot(epochs, loss_values, 'bo', label='Training loss')
plt.plot(epochs, val_loss_values, 'b', label='Validation loss')
plt.title('Training and validation loss')
plt.xlabel('Epochs')
plt.ylabel('MAE')
plt.legend()
plt.show()

#%%
#%% Forecast new values and visualize them.

#%% Past miniseries prediction case to predict one point data at a time.

# Prepare data.
num_predictions = 50

acumulado_pred = np.array([])
acumulado_real = np.array([])
data = np.concatenate((train_data[-len_mini_series:], validation_data))
for j in range(len(data) - len_mini_series - num_predictions):
    current_batch = data[j:j+len_mini_series].reshape((1, len_mini_series, validation_data.shape[1]))
    validation_predictions = []
    for i in range(num_predictions):
    
        # Get prediction one point ahead.
        current_pred = model.predict(current_batch)[0]
        #current_pred = model.predict(current_batch)[0][-1]      # Several LSTM.
    
        # Append prediction.
        validation_predictions.append(current_pred)
    
        # Update miniseries in order to include the prediction and remove the first point.
        current_batch = np.append(current_batch[:,1:,:], [[current_pred]], axis=1)
        
    if j % num_predictions == 0:
        acumulado_pred = np.concatenate((acumulado_pred, np.array(validation_predictions).ravel()))
        acumulado_real = np.concatenate((acumulado_real, 
                                         data[j+len_mini_series:j+len_mini_series + num_predictions].ravel()))

# Visualize.
#mpl.rcParams['xtick.labelsize'] = 'medium'
#plt.figure().subplots().xaxis.set_major_formatter(mpl.dates.DateFormatter('%Y-%m-%d'));
#plt.tick_params(axis='x', labelrotation=30);
#plt.plot(validation_data_aux.index[:num_predictions], 
#         scaler.inverse_transform(validation_data[:num_predictions])[:,0], label='Real')
#plt.plot(validation_data_aux.index[:num_predictions], 
#         scaler.inverse_transform(validation_predictions)[:,0], label='Predicción')

plt.plot(acumulado_real, label='Real')
plt.plot(acumulado_pred, label='Forecast')
plt.legend()
plt.title('Validation Aquifer Auser (LSTM net): ' + target_columns[0])
plt.show()

# Several columns.
#for i,j in zip(validation_predictions, range(len(validation_predictions))):
#    validation_predictions[j] = i[0]

print('MAE: ' + str(mean_absolute_error(acumulado_real, acumulado_pred)))

#%%
#%% Prediction based on exogenous data.

validation = validation_data
real = validation_target_data
data = np.concatenate((train_data[-len_mini_series:], validation_data))
validation_predictions = []
for j in range(len(data) - len_mini_series):
    current_batch = data[j:j+len_mini_series].reshape((1, len_mini_series, validation_data.shape[1]))
    current_pred = model.predict(current_batch)[0,0]
    validation_predictions.append(current_pred)

plt.title('Dense Neural Network')
plt.plot(real, label='Original')
plt.plot(validation_predictions, label='Forecast')
plt.legend()
plt.show()

print('MAE: ' + str(mean_absolute_error(validation_predictions, real)))

#%%
#%% Various predicted data points case.

validation_predictions = []
current_batch = train_data[-len_mini_series:].reshape((-1, len_mini_series, validation_data.shape[1]))

current_pred = model.predict(current_batch)[0]

plt.plot(validation_data[:win], label='Real')
plt.plot(current_pred, label='Forecast')
plt.legend()
plt.show()

print('MAE: ' + str(mean_absolute_error(validation_data[:win], current_pred)))

acumulado_pred = np.array([])
acumulado_real = np.array([])
data = np.concatenate((train_data, validation_data))
for i in range(len(data) - len_mini_series - win):
    current_batch = data[i:i+len_mini_series].reshape((1, len_mini_series, validation_data.shape[1]))
    current_pred = model.predict(current_batch)[0]
    if (i%win==0):
        acumulado_pred = np.concatenate((acumulado_pred, current_pred))
        acumulado_real = np.concatenate((acumulado_real, data[i+len_mini_series:i+len_mini_series+win].ravel()))
    #print('MAE: ' + str(mean_absolute_error(data[i+len_mini_series:i+len_mini_series+win], current_pred)))

plt.plot(acumulado_real[-53:], label='Real')
plt.plot(acumulado_pred[-53:], label='Forecast')
plt.title('Validación Aquifer Auser (LSTM net): ' + target_columns[0])
plt.legend()
plt.show()

print('MAE: ' + str(mean_absolute_error(acumulado_real[-53:], acumulado_pred[-53:])))

#%%
#%% Dense Neural Network.

model = models.Sequential()
model.add(layers.Dense(train_data.shape[-1], activation='linear'))
#model.add(layers.Dense(50, activation='relu'))
model.add(layers.Dense(50, activation=K.sin))
#model.add(layers.Dense(50, activation='tanh'))
model.add(layers.Dense(1, activation='linear'))

model.compile(optimizer='adam', loss='mae')
history = model.fit(train_data, train_target_data,  epochs=300, batch_size=5, validation_data=(validation_data, validation_target_data))

# Model info.
model.summary()

# Visualize training and validation error.
#print(history_dict.keys())
history_dict = history.history
loss_values = history_dict['loss']
val_loss_values = history_dict['val_loss']
epochs = range(1, len(history_dict['loss']) + 1)
plt.plot(epochs, loss_values, 'bo', label='Training loss')
plt.plot(epochs, val_loss_values, 'b', label='Validation loss')
plt.title('Training and validation loss')
plt.xlabel('Epochs')
plt.ylabel('MAE')
plt.legend()
plt.show()

# Visualize net.
plot_model(model, show_shapes=True)

# Evaluate on a test base.
#test_acc = model.evaluate(validation_data, validation_target_data)
#print(test_acc)

#%%
#%% Custom dense NN.

epoc = 500
batch_s = 21

def cuadratic(x):
    return 0.00000001*x*x

get_custom_objects().update({'cos':K.cos, 'sin':K.sin, 'cuadratic':cuadratic})

il = Input(shape=train_data.shape[-1])

# Several input layers.
#il1 = Input(shape=train_input_layers[0].shape[-1])
#il2 = Input(shape=train_input_layers[1].shape[-1])

l1 = Dense(100, activation='sin')(il)
l2 = Dense(100, activation='cos')(il)
#l3 = Dense(1, activation='linear')(il)
l4 = Dense(1, activation='cuadratic')(il)
#l5 = Dense(100, activation='relu')(l4)
#l6 = Dense(100, activation='relu')(l5)
lc1 = Concatenate()([l1, l2, l4])

ol = Dense(1, activation='linear')(lc1)

model = Model(inputs=il, outputs=ol, name='CustomNN')
# Several input layers.
#model = Model(inputs=[il1, il2], outputs= ol, name='CustomNN')

callbacks_list = [
    ModelCheckpoint(
        filepath='my_model.h5',
        monitor='val_loss',
        save_best_only=True
    ),

#   ReduceLROnPlateau(
#        monitor='val_loss',
#        factor=0.8,
#        patience=10
#    )
]

model.compile(optimizer='adam', loss='mae')
history = model.fit(train_data, train_target_data,  epochs=epoc, batch_size=batch_s, validation_data=(validation_data, validation_target_data), callbacks=callbacks_list)
# Several input layers.
#history = model.fit(train_input_layers, train_target_data,  epochs=epoc, batch_size=batch_s, validation_data=(validation_input_layers, validation_target_data), callbacks=callbacks_list)

model = load_model('my_model.h5')

# Model info.
model.summary()

# Visualize training and validation errors.
#print(history_dict.keys())
history_dict = history.history
loss_values = history_dict['loss']
val_loss_values = history_dict['val_loss']
epochs = range(1, len(history_dict['loss']) + 1)
plt.plot(epochs[10:], loss_values[10:], 'bo', label='Training loss')
plt.plot(epochs[10:], val_loss_values[10:], 'b', label='Validation loss')
plt.title('Training and validation loss')
plt.xlabel('Epochs')
plt.ylabel('MAE')
plt.legend()
plt.show()

# Visualize net.
plot_model(model, show_shapes=True)

#%%
#%% Genetic Algorithm.

pobl_inic = 50
num_parejas = 25
num_hijos_pareja = 1
prob_mutacion = 0.05
num_generaciones = 1

max_batch_size = int(len(train_data)/2)
max_sin = 0
max_cos = 0

# Gene sintaxis:
    # [Batch size, Sine functions number, Cosine functions number]

# Gene limints, both limits are included.
gen_limits = [[1, max_batch_size], [0, max_sin], [0, max_cos]]

def cuadratic(x):
    return x*x         # 0.00000001*x*x

get_custom_objects().update({'cos':K.cos, 'sin':K.sin, 'cuadratic':cuadratic})

# Create individual from gene, returning a list with the gene, model and its evaluation.
def crearIndividuo(gen):

    epoc = 500
    
    il = Input(shape=train_data.shape[-1])
    
    l1 = Dense(gen[1], activation=K.sin)(il)
    l2 = Dense(gen[2], activation=K.cos)(il)
    l3 = Dense(1, activation='cuadratic')(il)
    lc1 = Concatenate()([l1, l2, l3])
    
    ol = Dense(1, activation='linear')(lc1)
    
    model = Model(inputs=il, outputs=ol)
    
    callbacks_list = [ModelCheckpoint(filepath='best_model.h5', monitor='val_loss', save_best_only=True)]
    
    model.compile(optimizer='adam', loss='mae')
    history = model.fit(train_data, train_target_data, verbose=0, epochs=epoc, batch_size=gen[0], validation_data=(validation_data, validation_target_data), callbacks=callbacks_list)
    
    model = load_model('best_model.h5')
    os.remove('best_model.h5')

    return [gen, model, min(history.history['val_loss'])]

# Function for sorting genes based on their evaluation value.
def customOrder(elem):
    return elem[2]

# Initialize individual list.
pobl = [[None, None, 0.0] for i in range(pobl_inic)]

# Initialize descendants list.
desc = [[None, None, 0.0] for i in range(num_parejas*num_hijos_pareja)]

# Initialize population.
for i in range(pobl_inic):

    print("Creando población inicial, individuo", i+1, '.')
    
    batch_s = np.random.randint(max_batch_size) + 1
    num_sin = np.random.randint(max_sin + 1)
    num_cos = np.random.randint(max_cos + 1)
    pobl[i] = crearIndividuo([batch_s, num_sin, num_cos])
    #pobl[i] = crearIndividuo([batch_s, num_sin])
    
    print(pobl[i][0], pobl[i][2])

# Descendants generation process through generations.
for i in range(num_generaciones):
    print("Población (generación", i,"):")
    for p in range(pobl_inic): print(pobl[p][0], pobl[p][2])
    # Parents selection and reproduction.
    for j in range(num_parejas):
        
        # Parents selection.
        ind1 = 0; ind2 = 0
        while ind1 == ind2:
            ind1 = np.random.randint(pobl_inic)
            ind2 = np.random.randint(pobl_inic)
        
        # Create the descendants.
        for k in range(num_hijos_pareja):
            
            # Gene creation from parents.
            gen = [0 for i in range(len(pobl[0][0]))]   # Empty gene.
            for l in range(len(gen)):
                # Coin toss.
                if np.random.randint(2):
                    gen[l] = pobl[ind1][0][l] if np.random.randint(2) else pobl[ind2][0][l]
                else:
                    gen[l] = int((pobl[ind1][0][l] + pobl[ind2][0][l])/2)
                
            # Mutate descendants.
            if np.random.rand() <= prob_mutacion:
                elem = np.random.randint(len(gen))
                gen[elem] = np.random.randint(gen_limits[elem][0], gen_limits[elem][1]+1)
            
            desc[j*num_hijos_pareja + k] = crearIndividuo(gen)
    
    # Replace worst evaluated population with best evaluated descendants.
    pobl_aux = pobl + desc
    print("Descendencia (generación", i,"):")
    for d in range(len(desc)): print(desc[d][0], desc[d][2])
    pobl_aux.sort(key=customOrder)
    
    pobl = pobl_aux[:pobl_inic]

print("Población final:")
for p in range(len(pobl)): print(pobl[p][0], pobl[p][2])

# Choose best model based on specific metric.
scores = [[0.0,0] for i in range(len(pobl))]    # Save scores and models index.
for i in range(len(pobl)):
    
    train_pred = pobl[i][1].predict(train_data)
    train_score = 0.25*mean_absolute_error(train_target_data, train_pred)
    validation_pred = pobl[i][1].predict(validation_data)
    validation_score = 0.25*mean_absolute_error(validation_target_data, validation_pred)
    test_pred = pobl[i][1].predict(test_data)
    test_score = 0.5*mean_absolute_error(test_target_data, test_pred)
    score = train_score + validation_score + test_score
    
    scores[i] = [score, i]

scores.sort()

print(f'Best score correspond to model with index {scores[0][1]}.')

alarm()

#%%
#%% Predict new values (1-1 prediction for LSTM).

varias_capas_entrada = False
aux1 = 2   # Key for changing the prediction domain.
num_model = 3

# Just validation domain.
if aux1 == 1:
    validation = validation_data if varias_capas_entrada == False else validation_input_layers
    real = validation_target_data
    # Para base de validación + prueba.
    validation = df['t'].loc[point_partition:].to_numpy()
    real = df[cols[target]].loc[point_partition:].to_numpy()

# Train + validation domain.
if aux1 == 2:
    if varias_capas_entrada == False:
        validation = np.concatenate((train_data, validation_data, test_data))
    else:
        validation = []
        for i in range(len(train_input_layers)):
            validation.append(np.concatenate((train_input_layers[i], validation_input_layers[i])))
        
    real = np.concatenate((train_target_data, validation_target_data, test_target_data))

# Future prediction (if it applies).
if aux1 == 3:
    x = np.array(list(range(test_data[-1].astype(int)[0], test_data[-1].astype(int)[0] + 60, 7))).astype(float)
    validation = np.concatenate((train_data.ravel(), validation_data.ravel(), test_data.ravel(), x))
    real = np.concatenate((train_target_data, validation_target_data))
    # Para base de validación + prueba.
    real = np.concatenate((train_target_data.ravel(), df[cols[target]].loc[point_partition:].to_numpy()))

forecast = pobl[num_model][1].predict(validation)
#forecast = model.predict(validation)

#forecast = scaler.inverse_transform(forecast)
#real = scaler.inverse_transform(df[[cols[target]]])

plt.title('Dense Neural Network')
plt.plot(real, label='Original')
plt.plot(forecast, label='Forecast')
plt.legend()
plt.show()

if aux1 < 3: print('MAE: ' + str(mean_absolute_error(real, forecast)))
else: 
    validation = validation_data
    real = validation_target_data
    # For train + validation base.
    validation = df_orig['t'].loc[point_partition:].to_numpy()
    real = df[cols[target]].loc[point_partition:].to_numpy()
    #forecast = model.predict(validation)
    forecast = pobl[num_model][1].predict(validation)
    print('MAE: ' + str(mean_absolute_error(real, forecast)))


#%% Save model.

print(scores)
pobl[0][1].summary()
pobl[0][1].save('model.h5')
