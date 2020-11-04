import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Load data with using columns

original_data = pd.read_csv("match_winner_data_version1.csv",
                            usecols=['win', 'firstBlood', 'firstTower', 'firstInhibitor', 'towerKills',
                                     'inhibitorKills',
                                     'baronKills', 'dragonKills', 'riftHeraldKills', 'gameId'])
print(original_data.head())

# Categorical Feature: win, firstBlood, firstTower, firstInhibitor
# Numerical Feature: towerKills, inhibitorKills, baronKills, dragonKills, riftHeraldKills, gameId

# Missing Data detection
# Find columns with missing value
columnMD = original_data.columns[original_data.isnull().any()]
print(columnMD)

# Among the missing values, numerical data: towerKills, inhibitorKills, baronKills, dragonKills
# Fill with mean (Rounds mean to nearest integer)
original_data['towerKills'].fillna((original_data['towerKills'].mean().round(0)), inplace=True)
original_data['inhibitorKills'].fillna((original_data['inhibitorKills'].mean().round(0)), inplace=True)
original_data['baronKills'].fillna((original_data['baronKills'].mean().round(0)), inplace=True)
original_data['dragonKills'].fillna((original_data['dragonKills'].mean().round(0)), inplace=True)

# Finding the wrong game that is not divided by win or lose and any others (Check using towerkills)

for i in range(len(original_data)):
    print(i)
    if original_data['towerKills'][i] < 5.0:
        original_data.drop(i, inplace=True)

original_data.to_csv("original_data_remove_wrongGame.csv", mode='w')  # 1차...

second_data = pd.read_csv("original_data_remove_wrongGame.csv")
second_data.columns = ['index', 'win', 'firstBlood', 'firstTower', 'firstInhibitor', 'towerKills',
                       'inhibitorKills',
                       'baronKills', 'dragonKills', 'riftHeraldKills', 'gameId']

print(second_data.head())

# Find rows with missing value
rowMD = second_data[second_data.isnull().any(axis=1)]


def findCategoricalMD(fIndex, fgameId):
    tempData = pd.read_csv("match_loser_data_version1.csv",
                           usecols=['firstBlood', 'firstTower', 'firstInhibitor', 'gameId'
                                    ])

    for i in range(len(tempData)):
        if tempData['gameId'][i] == fgameId:
            print(tempData.loc[[i], :])
            firstBlood = tempData['firstBlood'][i]
            firstTower = tempData['firstTower'][i]
            firstInhibitor = tempData['firstInhibitor'][i]

            # nan일 경우 값 변경
            # loser data T --> F // F --> T
            if second_data.loc[fIndex, 'firstBlood']:
                if firstBlood:
                    firstBlood = False
                elif not firstBlood:
                    firstBlood = True
                second_data['firstBlood'] = second_data['firstBlood'].replace(np.nan, firstBlood)

            if second_data.loc[fIndex, 'firstTower']:
                if firstTower:
                    firstTower = False
                elif not firstTower:
                    firstTower = True
                second_data['firstTower'] = second_data['firstTower'].replace(np.nan, firstTower)

            if second_data.loc[fIndex, 'firstInhibitor']:
                if firstInhibitor:
                    firstInhibitor = False
                elif not firstInhibitor:
                    firstInhibitor = True
                second_data['firstInhibitor'] = second_data['firstInhibitor'].replace(np.nan, firstInhibitor)


for i in range(len(second_data)):
    try:
        if rowMD['index'][i]:
            findCategoricalMD(i, rowMD['gameId'][i])
    except KeyError:
        continue

second_data.to_csv("fix_missing_data.csv", mode='w')  # 2차....

win_data = pd.read_csv("fix_missing_data.csv",
                       usecols=['win', 'firstBlood', 'firstTower', 'firstInhibitor', 'towerKills', 'inhibitorKills',
                                'baronKills', 'dragonKills', 'riftHeraldKills', 'gameId'])
lose_data = pd.read_csv("match_loser_data_version1.csv",
                        usecols=['win', 'firstBlood', 'firstTower', 'firstInhibitor', 'towerKills', 'inhibitorKills',
                                 'baronKills', 'dragonKills', 'riftHeraldKills', 'gameId'])

merged = pd.merge(win_data, lose_data, on='gameId')
merged.to_csv("win_lose_final_data.csv", mode='w')  # 3차....

data = pd.read_csv("win_lose_final_data.csv",
                   usecols=['win_x', 'firstBlood_x', 'firstTower_x', 'firstInhibitor_x', 'towerKills_x',
                            'inhibitorKills_x',
                            'baronKills_x', 'dragonKills_x', 'riftHeraldKills_x', 'win_y', 'firstBlood_y',
                            'firstTower_y', 'firstInhibitor_y', 'towerKills_y', 'inhibitorKills_y',
                            'baronKills_y', 'dragonKills_y', 'riftHeraldKills_y'])
print(data.head())
columnMD = data.columns[data.isnull().any()]
print(columnMD)
data['win_y'] = data['win_y'].fillna('Fail')

win_data = pd.DataFrame(columns=['win', 'firstBlood', 'firstTower', 'firstInhibitor', 'towerKills',
                                 'inhibitorKills',
                                 'baronKills', 'dragonKills', 'riftHeraldKills'])
lose_data = pd.DataFrame(columns=['win', 'firstBlood', 'firstTower', 'firstInhibitor', 'towerKills',
                                  'inhibitorKills',
                                  'baronKills', 'dragonKills', 'riftHeraldKills'])

win_data['win'] = data['win_x']
win_data['win'] = win_data['win'].replace('Win', 1)
win_data['firstBlood'] = data['firstBlood_x']
win_data['firstTower'] = data['firstTower_x']
win_data['firstInhibitor'] = data['firstInhibitor_x']
win_data['towerKills'] = data['towerKills_x']
win_data['inhibitorKills'] = data['inhibitorKills_x']
win_data['baronKills'] = data['baronKills_x']
win_data['dragonKills'] = data['dragonKills_x']
win_data['riftHeraldKills'] = data['riftHeraldKills_x']

lose_data['win'] = data['win_y']
lose_data['win'] = lose_data['win'].replace('Fail', 0)
lose_data['firstBlood'] = data['firstBlood_y']
lose_data['firstTower'] = data['firstTower_y']
lose_data['firstInhibitor'] = data['firstInhibitor_y']
lose_data['towerKills'] = data['towerKills_y']
lose_data['inhibitorKills'] = data['inhibitorKills_y']
lose_data['baronKills'] = data['baronKills_y']
lose_data['dragonKills'] = data['dragonKills_y']
lose_data['riftHeraldKills'] = data['riftHeraldKills_y']

final_data = pd.concat([win_data, lose_data], ignore_index=True)
final_data.to_csv("Final_data.csv", mode='w')  # 4차....

# ---------------Complete Preprocessing--------------------
# ---------------------------------------------------------
