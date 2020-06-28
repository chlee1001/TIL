import numpy as np
import pandas as pd
from sklearn.preprocessing import LabelEncoder
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.linear_model import LinearRegression, LogisticRegression
from sklearn.model_selection import cross_val_score
from sklearn.metrics import confusion_matrix, accuracy_score
from sklearn.metrics import classification_report
import matplotlib.pyplot as plt
import seaborn as sns

# Read csv file
df = pd.read_csv('Final_data.csv')
df = df.loc[:, ~df.columns.str.contains('^Unnamed')]

print(df)


# Probability of win according to a feature that has a numeric data type
def probStatus(dataset, group_by):
    df = pd.crosstab(index=dataset[group_by], columns=dataset.win).reset_index()
    df['probWin'] = df[1] / (df[1] + df[0])
    print(df)
    return df[[group_by, 'probWin']]


# Visualization: Win ratio changes with respect to towerKills changes.
sns.lmplot(data=probStatus(df, 'towerKills'), x='towerKills', y='probWin', fit_reg=False)
plt.xlim(0, 11)
plt.title('Win ratio on tower kills')
plt.show()

# Visualization: Win ratio changes with respect to dragonKills changes.
sns.lmplot(data=probStatus(df, 'dragonKills'), x='dragonKills', y='probWin', fit_reg=False)
plt.xlim(0, 7)
plt.title('Win ratio on dragon kills')
plt.show()


# Find the categorical columns
def categoricalColumns(data):
    cateCols = []
    for i in data.columns:
        if data[i].dtypes == bool:
            cateCols.append(i)
    return cateCols


# LabelEncoder (Categorical -> Numeric)
def labelEncoder(data, cateCols):
    label = LabelEncoder()
    for i in cateCols:
        label.fit_transform(list(data[i].values))
        data[i] = label.transform(list(data[i].values))


# Use a LabelEncoder to encode Categorical values to numeric values.
labelEncoder(df, categoricalColumns(df))

X = df.drop(['win'], axis=1)
y = df['win']

# Holdout
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=1)

# StandardScaler
scaler = StandardScaler()
X[['towerKills', 'inhibitorKills', 'baronKills', 'dragonKills', 'riftHeraldKills']] = scaler.fit_transform(
    X[['towerKills', 'inhibitorKills', 'baronKills', 'dragonKills', 'riftHeraldKills']])

X = pd.DataFrame(X, columns=['towerKills', 'inhibitorKills', 'baronKills', 'dragonKills', 'riftHeraldKills'])
fig, (ax1, ax2) = plt.subplots(ncols=2, figsize=(10, 10))
ax1.set_title('Before Scaling')
sns.kdeplot(X['towerKills'], ax=ax1)
sns.kdeplot(X['inhibitorKills'], ax=ax1)
sns.kdeplot(X['baronKills'], ax=ax1)
sns.kdeplot(X['dragonKills'], ax=ax1)
sns.kdeplot(X['riftHeraldKills'], ax=ax1)
ax2.set_title('After Standard Scaler')
sns.kdeplot(df['towerKills'], ax=ax2)
sns.kdeplot(df['inhibitorKills'], ax=ax2)
sns.kdeplot(df['baronKills'], ax=ax2)
sns.kdeplot(df['dragonKills'], ax=ax2)
sns.kdeplot(df['riftHeraldKills'], ax=ax2)

plt.show()

################### Analysis & Evaluation ####################

# LogisticRegression
model_LG = LogisticRegression()
model_LG.fit(X_train, y_train)
y_pred_LG = model_LG.predict(X_test)

print('Accuracy :', accuracy_score(y_test, y_pred_LG))
cm_LG = confusion_matrix(y_test, y_pred_LG)
print(cm_LG)

target_names = ['win', 'lose']
fig, ax = plt.subplots()
tick_marks = np.arange(len(target_names))
plt.xticks(tick_marks, target_names)
plt.yticks(tick_marks, target_names)
sns.heatmap(pd.DataFrame(cm_LG), annot=True, cmap='YlGnBu', fmt='g')
ax.xaxis.set_label_position("top")
plt.tight_layout()
plt.title("Confusion matrix", y=1.1)
plt.xlabel("Predict label")
plt.ylabel("Actual label")
plt.show()

print("Classification report")
print(classification_report(y_test, y_pred_LG, target_names=target_names))

cvs_LG = cross_val_score(model_LG, X, y, scoring=None, cv=10)
print("Accuracy score using 10-fold cv:", (np.mean(cvs_LG)))
print("-" * 60)

# Classification
# DecisionTreeClassifer : entropy-based
model_DT = DecisionTreeClassifier(criterion='entropy')

model_DT.fit(X_train, y_train)
y_pred_DT = model_DT.predict(X_test)

# Display confusin_matrix of two algorithms
cm_DT = confusion_matrix(y_test, y_pred_DT)
print(cm_DT)

target_names = ['win', 'lose']
print("Classification report")
print(classification_report(y_test, y_pred_DT, target_names=target_names))

# Use 10-fold cross validation
cvs_DT = cross_val_score(model_DT, X, y, scoring=None, cv=10)
print("Accuracy score using 10-fold cv:", (np.mean(cvs_DT)))
