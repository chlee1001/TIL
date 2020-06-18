import numpy as np
import pandas as pd

# Load data with using columns
data = pd.read_csv("match_winner_data_version1.csv",
                   usecols=['win', 'firstBlood', 'firstTower', 'firstInhibitor', 'towerKills', 'inhibitorKills',
                            'baronKills', 'dragonKills', 'riftHeraldKills', 'gameId'])
print(data.head())

# Categorical Feature: win, firstBlood, firstTower, firstInhibitor
# Numerical Feature: towerKills, inhibitorKills, baronKills, dragonKills, riftHeraldKills, gameId

# Missing Data detection
# Find columns with missing value
columnMD = data.columns[data.isnull().any()]
# print(columnMD)


# Among the missing values, numerical data: towerKills, inhibitorKills, baronKills, dragonKills
# Fill with mean (Rounds mean to nearest integer)
data['towerKills'].fillna((data['towerKills'].mean().round(0)), inplace=True)
data['inhibitorKills'].fillna((data['inhibitorKills'].mean().round(0)), inplace=True)
data['baronKills'].fillna((data['baronKills'].mean().round(0)), inplace=True)
data['dragonKills'].fillna((data['dragonKills'].mean().round(0)), inplace=True)

# Finding the wrong game that is not divided by win or lose and any others (Check using toowerkills)
for i in range(len(data)):
    if data['towerKills'][i] < 5.0:
        data.drop(i, inplace=True)

data.to_csv("new.csv", mode='w') # 1차...


data = pd.read_csv("new.csv")
# print(data.head())

# Find rows with missing value
rowMD = data[data.isnull().any(axis=1)]


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
            if data.loc[fIndex, 'firstBlood']:
                if firstBlood:
                    firstBlood = False
                elif not firstBlood:
                    firstBlood = True
                data['firstBlood'] = data['firstBlood'].replace(np.nan, firstBlood)

            if data.loc[fIndex, 'firstTower']:
                if firstTower:
                    firstTower = False
                elif not firstTower:
                    firstTower = True
                data['firstTower'] = data['firstTower'].replace(np.nan, firstTower)

            if data.loc[fIndex, 'firstInhibitor']:
                if firstInhibitor:
                    firstInhibitor = False
                elif not firstInhibitor:
                    firstInhibitor = True
                data['firstInhibitor'] = data['firstInhibitor'].replace(np.nan, firstInhibitor)


for i in range(len(data)):
    try:
        if rowMD['index'][i]:
            findCategoricalMD(i, rowMD['gameId'][i])
    except KeyError:
        continue

data.to_csv("new1.csv", mode='w') # 2차....

# ---------------Complete Preprocessing--------------------
# ---------------------------------------------------------

data = pd.read_csv("new1.csv",
                   usecols=['win', 'firstBlood', 'firstTower', 'firstInhibitor', 'towerKills', 'inhibitorKills',
                            'baronKills', 'dragonKills', 'riftHeraldKills', 'gameId'])
print(data.head())

