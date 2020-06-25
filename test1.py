import pandas as pd
from sklearn import preprocessing
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split

# Load data with using columns
data = pd.read_csv("Final_data.csv",
                   usecols=['win', 'firstBlood', 'firstTower', 'firstInhibitor', 'towerKills', 'inhibitorKills',
                            'baronKills', 'dragonKills', 'riftHeraldKills'])
print(data.head())

# Scaling
# Make DF...with Height, Weight

df = pd.DataFrame(columns=['win', 'firstBlood', 'firstTower', 'firstInhibitor', 'towerKills',
                           'inhibitorKills',
                           'baronKills', 'dragonKills', 'riftHeraldKills'])

df['win'] = data['win']
df['firstBlood'] = data['firstBlood']
df['firstTower'] = data['firstTower']
df['firstInhibitor'] = data['firstInhibitor']
df['towerKills'] = data['towerKills']
df['inhibitorKills'] = data['inhibitorKills']
df['baronKills'] = data['baronKills']
df['dragonKills'] = data['dragonKills']
df['riftHeraldKills'] = data['riftHeraldKills']

# StandardScaler
scaler = preprocessing.StandardScaler()
scaled_df = scaler.fit_transform(df)
scaled_df = pd.DataFrame(scaled_df,
                         columns=['win', 'firstBlood', 'firstTower', 'firstInhibitor', 'towerKills', 'inhibitorKills',
                                  'baronKills', 'dragonKills', 'riftHeraldKills'])

fig, (ax1, ax2) = plt.subplots(ncols=2)
ax1.set_title('Before StandardScaling')
ax1.grid(True)
sns.kdeplot(df['win'], ax=ax1)
sns.kdeplot(df['firstBlood'], ax=ax1)
sns.kdeplot(df['firstTower'], ax=ax1)
sns.kdeplot(df['firstInhibitor'], ax=ax1)
sns.kdeplot(df['towerKills'], ax=ax1)
sns.kdeplot(df['inhibitorKills'], ax=ax1)
sns.kdeplot(df['baronKills'], ax=ax1)
sns.kdeplot(df['dragonKills'], ax=ax1)
sns.kdeplot(df['riftHeraldKills'], ax=ax1)

ax2.set_title('After StandardScaling')
ax2.grid(True)
sns.kdeplot(scaled_df['win'], ax=ax2)
sns.kdeplot(scaled_df['firstBlood'], ax=ax2)
sns.kdeplot(scaled_df['firstTower'], ax=ax2)
sns.kdeplot(scaled_df['firstInhibitor'], ax=ax2)
sns.kdeplot(scaled_df['towerKills'], ax=ax2)
sns.kdeplot(scaled_df['inhibitorKills'], ax=ax2)
sns.kdeplot(scaled_df['baronKills'], ax=ax2)
sns.kdeplot(scaled_df['dragonKills'], ax=ax2)
sns.kdeplot(scaled_df['riftHeraldKills'], ax=ax2)
plt.show()
# print(df)
# print(scaled_df)


# Split train data set and test data set
X = scaled_df[['firstBlood', 'firstTower', 'firstInhibitor', 'towerKills', 'inhibitorKills',
               'baronKills', 'dragonKills', 'riftHeraldKills']]
y = scaled_df[['win']]
# print(X)
# print(y)

x_train, x_test, y_train, y_test = train_test_split(X, y, train_size=0.8, test_size=0.2, random_state=1)

model_LR = LinearRegression()
model_LR.fit(x_train, y_train)
y_predicted = model_LR.predict(x_test)

# my_data1 = [[False, True, True, 9, 1, 0, 3, 2]]
# my_predict1 = model_LR.predict(my_data1)
# print(my_predict1)
# my_data1 = [[False, False, False, 1, 0, 0, 1, 0]]
# my_predict1 = model_LR.predict(my_data1)
# print(my_predict1)

plt.scatter(y_test, y_predicted, alpha=0.4)
plt.xlabel("game Data")
plt.ylabel("Win or Lose")
plt.title("MULTIPLE LINEAR REGRESSION")
plt.show()

print(model_LR.score(x_train, y_train))


#
# modelKM = KMeans(n_clusters=3, algorithm='auto')
# modelKM.fit(X)
# predict = pd.DataFrame(modelKM.predict(x_test))
# predict.columns = ['predict']
#
# r = pd.concat([X, predict], axis=1)
#
# plt.scatter(r['firstBlood'], r['firstTower'], r['firstInhibitor'], r['towerKills'], r['inhibitorKills'],
#             r['baronKills'], r['dragonKills'], r['riftHeraldKills'], rc=r['predict'], alpha=0.5)
#
# # centers = pd.DataFrame(modelKM.cluster_centers_,
# #                        columns=['firstBlood', 'firstTower', 'firstInhibitor', 'towerKills', 'inhibitorKills',
# #                                 'baronKills', 'dragonKills', 'riftHeraldKills'])
# # center_x = centers['Sepal length']
# # center_y = centers['Sepal width']
# # plt.scatter(center_x, center_y, s=50, marker='D', c='r')
#
# plt.show()
