# Columnas Aquifer Auser.
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
    26:'Period',
    27:'Sum_Rain',
    28:'Sum_Hydro'
}

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
                 'Temperature_Orentano',
                 #'Temperature_Monte_Serra',
                 #'Temperature_Ponte_a_Moriano',
                 #'Temperature_Lucca_Orto_Botanico',
                 'Volume_POL',
                 #'Volume_CC1',
                 #'Volume_CC2',
                 #'Volume_CSA',
                 #'Volume_CSAL',
                 #'Hydrometry_Monte_S_Quirico',
                 #'Hydrometry_Piaggione',
                 #'Period',
                 'Sum_Rain',
                 'Sum_Hydro'
                 ]

###############################################################################

# Columnas Aquifer Doganella.
cols = {
	-1:'Date',
	0:'Rainfall_Monteporzio',
	1:'Rainfall_Velletri',
	2:'Depth_to_Groundwater_Pozzo_1',
	3:'Depth_to_Groundwater_Pozzo_2',
	4:'Depth_to_Groundwater_Pozzo_3',
	5:'Depth_to_Groundwater_Pozzo_4',
	6:'Depth_to_Groundwater_Pozzo_5',
	7:'Depth_to_Groundwater_Pozzo_6',
	8:'Depth_to_Groundwater_Pozzo_7',
	9:'Depth_to_Groundwater_Pozzo_8',
	10:'Depth_to_Groundwater_Pozzo_9',
	11:'Volume_Pozzo_1',
	12:'Volume_Pozzo_2',
	13:'Volume_Pozzo_3',
	14:'Volume_Pozzo_4',
	15:'Volume_Pozzo_5+6',
	16:'Volume_Pozzo_7',
	17:'Volume_Pozzo_8',
	18:'Volume_Pozzo_9',
	19:'Temperature_Monteporzio',
	20:'Temperature_Velletri',
	21:'Period',
	22:'Sum_Rain',
	23:'Sum_Hydro',
}
train_columns = [
	#'Rainfall_Monteporzio',
	#'Rainfall_Velletri',
	#'Depth_to_Groundwater_Pozzo_1',
	#'Depth_to_Groundwater_Pozzo_2',
	#'Depth_to_Groundwater_Pozzo_3',
	#'Depth_to_Groundwater_Pozzo_4',
	#'Depth_to_Groundwater_Pozzo_5',
	#'Depth_to_Groundwater_Pozzo_6',
	#'Depth_to_Groundwater_Pozzo_7',
	#'Depth_to_Groundwater_Pozzo_8',
	#'Depth_to_Groundwater_Pozzo_9',
	#'Volume_Pozzo_1',
	#'Volume_Pozzo_2',
	#'Volume_Pozzo_3',
	#'Volume_Pozzo_4',
	#'Volume_Pozzo_5+6',
	#'Volume_Pozzo_7',
	#'Volume_Pozzo_8',
	#'Volume_Pozzo_9',
	#'Temperature_Monteporzio',
	#'Temperature_Velletri',
	#'Period',
	#'Sum_Rain',
	#'Sum_Hydro',
]

###############################################################################

# Columnas Aquifer Luco.

cols = {
	-1:'Date',
	0:'Rainfall_Simignano',
	1:'Rainfall_Siena_Poggio_al_Vento',
	2:'Rainfall_Mensano',
	3:'Rainfall_Montalcinello',
	4:'Rainfall_Monticiano_la_Pineta',
	5:'Rainfall_Sovicille',
	6:'Rainfall_Ponte_Orgia',
	7:'Rainfall_Scorgiano',
	8:'Rainfall_Pentolina',
	9:'Rainfall_Monteroni_Arbia_Biena',
	10:'Depth_to_Groundwater_Podere_Casetta',
	11:'Depth_to_Groundwater_Pozzo_1',
	12:'Depth_to_Groundwater_Pozzo_3',
	13:'Depth_to_Groundwater_Pozzo_4',
	14:'Temperature_Siena_Poggio_al_Vento',
	15:'Temperature_Mensano',
	16:'Temperature_Pentolina',
	17:'Temperature_Monteroni_Arbia_Biena',
	18:'Volume_Pozzo_1',
	19:'Volume_Pozzo_3',
	20:'Volume_Pozzo_4',
	21:'Period',
	22:'Sum_Rain',
	23:'Sum_Hydro'
}
train_columns = [
	#'Rainfall_Simignano',
	#'Rainfall_Siena_Poggio_al_Vento',
	#'Rainfall_Mensano',
	#'Rainfall_Montalcinello',
	#'Rainfall_Monticiano_la_Pineta',
	#'Rainfall_Sovicille',
	#'Rainfall_Ponte_Orgia',
	#'Rainfall_Scorgiano',
	#'Rainfall_Pentolina',
	#'Rainfall_Monteroni_Arbia_Biena',
	#'Depth_to_Groundwater_Podere_Casetta',
	#'Depth_to_Groundwater_Pozzo_1',
	#'Depth_to_Groundwater_Pozzo_3',
	#'Depth_to_Groundwater_Pozzo_4',
	#'Temperature_Siena_Poggio_al_Vento',
	#'Temperature_Mensano',
	#'Temperature_Pentolina',
	#'Temperature_Monteroni_Arbia_Biena',
	#'Volume_Pozzo_1',
	#'Volume_Pozzo_3',
	#'Volume_Pozzo_4',
	#'Period',
	#'Sum_Rain',
	#'Sum_Hydro'
]

###############################################################################

# Columnas Aquifer Petrignano.

cols = {
	-1:'Date',
	0:'Rainfall_Bastia_Umbra',
	1:'Depth_to_Groundwater_P24',
	2:'Depth_to_Groundwater_P25',
	3:'Temperature_Bastia_Umbra',
	4:'Temperature_Petrignano',
	5:'Volume_C10_Petrignano',
	6:'Hydrometry_Fiume_Chiascio_Petrignano',
	7:'Period',
	8:'Sum_Rain',
	9:'Sum_Hydro'
}
train_columns = [
	#'Rainfall_Bastia_Umbra',
	#'Depth_to_Groundwater_P24',
	#'Depth_to_Groundwater_P25',
	#'Temperature_Bastia_Umbra',
	#'Temperature_Petrignano',
	#'Volume_C10_Petrignano',
	#'Hydrometry_Fiume_Chiascio_Petrignano',
	#'Period',
	#'Sum_Rain',
	#'Sum_Hydro'
]
    
###############################################################################

# Columnas Lake Bilancino.

cols = {
	-1:'Date',
	0:'Rainfall_S_Piero',
	1:'Rainfall_Mangona',
	2:'Rainfall_S_Agata',
	3:'Rainfall_Cavallina',
	4:'Rainfall_Le_Croci',
	5:'Temperature_Le_Croci',
	6:'Lake_Level',
	7:'Flow_Rate',
	8:'Period',
	9:'Sum_Rain',
	10:'Sum_Hydro'
}
train_columns = [
	#'Rainfall_S_Piero',
	#'Rainfall_Mangona',
	#'Rainfall_S_Agata',
	#'Rainfall_Cavallina',
	#'Rainfall_Le_Croci',
	#'Temperature_Le_Croci',
	#'Lake_Level',
	#'Flow_Rate',
	#'Period',
	#'Sum_Rain',
	#'Sum_Hydro'
]

###############################################################################

# Columnas River Arno.

cols = {
	-1:'Date',
	0:'Rainfall_Le_Croci',
	1:'Rainfall_Cavallina',
	2:'Rainfall_S_Agata',
	3:'Rainfall_Mangona',
	4:'Rainfall_S_Piero',
	5:'Rainfall_Vernio',
	6:'Rainfall_Stia',
	7:'Rainfall_Consuma',
	8:'Rainfall_Incisa',
	9:'Rainfall_Montevarchi',
	10:'Rainfall_S_Savino',
	11:'Rainfall_Laterina',
	12:'Rainfall_Bibbiena',
	13:'Rainfall_Camaldoli',
	14:'Temperature_Firenze',
	15:'Hydrometry_Nave_di_Rosano',
	16:'Period',
	17:'Sum_Rain',
	18:'Sum_Hydro'
}
train_columns = [
	#'Rainfall_Le_Croci',
	#'Rainfall_Cavallina',
	#'Rainfall_S_Agata',
	#'Rainfall_Mangona',
	#'Rainfall_S_Piero',
	#'Rainfall_Vernio',
	#'Rainfall_Stia',
	#'Rainfall_Consuma',
	#'Rainfall_Incisa',
	#'Rainfall_Montevarchi',
	#'Rainfall_S_Savino',
	#'Rainfall_Laterina',
	#'Rainfall_Bibbiena',
	#'Rainfall_Camaldoli',
	#'Temperature_Firenze',
	#'Hydrometry_Nave_di_Rosano',
	#'Period',
	#'Sum_Rain',
	#'Sum_Hydro'
]

###############################################################################

# Columnas Water Spring Amiata.

cols = {
	-1:'Date',
	0:'Rainfall_Castel_del_Piano',
	1:'Rainfall_Abbadia_S_Salvatore',
	2:'Rainfall_S_Fiora',
	3:'Rainfall_Laghetto_Verde',
	4:'Rainfall_Vetta_Amiata',
	5:'Depth_to_Groundwater_S_Fiora_8',
	6:'Depth_to_Groundwater_S_Fiora_11bis',
	7:'Depth_to_Groundwater_David_Lazzaretti',
	8:'Temperature_Abbadia_S_Salvatore',
	9:'Temperature_S_Fiora',
	10:'Temperature_Laghetto_Verde',
	11:'Flow_Rate_Bugnano',
	12:'Flow_Rate_Arbure',
	13:'Flow_Rate_Ermicciolo',
	14:'Flow_Rate_Galleria_Alta',
	15:'Period',
	16:'Sum_Rain',
	17:'Sum_Hydro'
}
train_columns = [
	#'Rainfall_Castel_del_Piano',
	#'Rainfall_Abbadia_S_Salvatore',
	#'Rainfall_S_Fiora',
	#'Rainfall_Laghetto_Verde',
	#'Rainfall_Vetta_Amiata',
	#'Depth_to_Groundwater_S_Fiora_8',
	#'Depth_to_Groundwater_S_Fiora_11bis',
	#'Depth_to_Groundwater_David_Lazzaretti',
	#'Temperature_Abbadia_S_Salvatore',
	#'Temperature_S_Fiora',
	#'Temperature_Laghetto_Verde',
	#'Flow_Rate_Bugnano',
	#'Flow_Rate_Arbure',
	#'Flow_Rate_Ermicciolo',
	#'Flow_Rate_Galleria_Alta',
	#'Period',
	#'Sum_Rain',
	#'Sum_Hydro'
]

###############################################################################

# Columnas Water Spring Lupa.

cols = {
	-1:'Date',
	0:'Rainfall_Terni',
	1:'Flow_Rate_Lupa',
	2:'Period',
	3:'Sum_Rain',
	4:'Sum_Hydro'
}
train_columns = [
	#'Rainfall_Terni',
	#'Flow_Rate_Lupa',
	#'Period',
	#'Sum_Rain',
	#'Sum_Hydro'
]

###############################################################################

# Columnas Water Spring Madonna di Canneto.

cols = {
	-1:'Date',
	0:'Rainfall_Settefrati',
	1:'Temperature_Settefrati',
	2:'Flow_Rate_Madonna_di_Canneto',
	3:'Period',
	4:'Sum_Rain',
	5:'Sum_Hydro'
}
train_columns = [
	#'Rainfall_Settefrati',
	#'Temperature_Settefrati',
	#'Flow_Rate_Madonna_di_Canneto',
	#'Period',
	#'Sum_Rain',
	#'Sum_Hydro'
]









