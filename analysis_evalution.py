import numpy as np
import pandas as pd
from sklearn.preprocessing import LabelEncoder
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier, BaggingClassifier
from sklearn.linear_model import LinearRegression, LogisticRegression
from sklearn.model_selection import cross_val_score
from sklearn.metrics import confusion_matrix, accuracy_score
from sklearn.metrics import classification_report
import matplotlib.pyplot as plt
import seaborn as sns

# Read csv file
data = pd.read_csv('Final_data.csv')
data = data.loc[:, ~data.columns.str.contains('^Unnamed')]

print(data)

# Using Pearson Correlation
plt.figure(figsize=(12, 10))
cor = data.corr()
sns.heatmap(cor, annot=True, cmap=plt.cm.Reds)
plt.show()

# Correlation with output variable
cor_target = abs(cor["win"])
# Selecting highly correlated features
relevant_features = cor_target[cor_target > 0.4]
print(
    relevant_features)  # win: 1.000000 / firstTower: 0.468613 / firstInhibitor: 0.784156 / towerKills: 0.833098 / inhibitorKills: 0.673570 / baronKills: 0.419577 / dragonKills: 0.514895

df = pd.DataFrame(data, columns=['win', 'firstTower', 'firstInhibitor', 'towerKills', 'inhibitorKills', 'baronKills',
                                 'dragonKills'])

print(df.head)


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
X[['towerKills', 'inhibitorKills', 'baronKills', 'dragonKills']] = scaler.fit_transform(
    X[['towerKills', 'inhibitorKills', 'baronKills', 'dragonKills']])

# kdeplot - Before, After Scaling 
X = pd.DataFrame(X, columns=['towerKills', 'inhibitorKills', 'baronKills', 'dragonKills'])
fig, (ax1, ax2) = plt.subplots(ncols=2, figsize=(10, 10))
ax1.set_title('Before Scaling')
sns.kdeplot(X['towerKills'], ax=ax1)
sns.kdeplot(X['inhibitorKills'], ax=ax1)
sns.kdeplot(X['baronKills'], ax=ax1)
sns.kdeplot(X['dragonKills'], ax=ax1)
ax2.set_title('After Standard Scaler')
sns.kdeplot(df['towerKills'], ax=ax2)
sns.kdeplot(df['inhibitorKills'], ax=ax2)
sns.kdeplot(df['baronKills'], ax=ax2)
sns.kdeplot(df['dragonKills'], ax=ax2)

plt.show()


# Draw result
def showResult(confusionMatrix, name):
    target_names = ['win', 'lose']
    fig, ax = plt.subplots()
    tick_marks = np.arange(len(target_names))
    plt.xticks(tick_marks, target_names)
    plt.yticks(tick_marks, target_names)
    sns.heatmap(pd.DataFrame(confusionMatrix), annot=True, cmap='YlGnBu', fmt='g')
    ax.xaxis.set_label_position("top")
    plt.tight_layout()
    plt.title("Confusion matrix : {0}".format(name), y=1.1)
    plt.xlabel("Predict label")
    plt.ylabel("Actual label")
    plt.show()
    print("Classification report on {0}".format(name))
    print(classification_report(y_test, y_pred_LG, target_names=target_names))


################### Analysis & Evaluation ####################

# LogisticRegression
print("LogisticRegression")
model_LG = LogisticRegression()
model_LG.fit(X_train, y_train)
y_pred_LG = model_LG.predict(X_test)

print('Accuracy :', accuracy_score(y_test, y_pred_LG))

# Display confusin_matrix
cm_LG = confusion_matrix(y_test, y_pred_LG)
print(cm_LG)

# Draw heatmap
showResult(cm_LG, "LogisticRegression")

# Use 10-fold cross validation
cvs_LG = cross_val_score(model_LG, X, y, scoring=None, cv=10)
print("Accuracy score using 10-fold cv:", (np.mean(cvs_LG)))
print("-" * 60)

#################################################################
# DecisionTreeClassifer : entropy-based
print("DecisionTreeClassifer")
model_DT = DecisionTreeClassifier(criterion='entropy')
model_DT.fit(X_train, y_train)
y_pred_DT = model_DT.predict(X_test)

print('Accuracy :', accuracy_score(y_test, y_pred_DT))

# Display confusion_matrix
cm_DT = confusion_matrix(y_test, y_pred_DT)
print(cm_DT)

# Draw heatmap
showResult(cm_DT, "DecisionTree")

# Use 10-fold cross validation
cvs_DT = cross_val_score(model_DT, X, y, scoring=None, cv=10)
print("Accuracy score using 10-fold cv:", (np.mean(cvs_DT)))
print("-" * 60)
print("-" * 60)


# Ensemble Learning - BaggingClassifier, RandomForestClassifier

def essemble(name, n_estimators):
    if name == "BaggingClassifier":
        essembleModel = BaggingClassifier(base_estimator=model_DT,
                                          n_estimators=n_estimators,
                                          n_jobs=-1,
                                          max_samples=1.0,
                                          max_features=1.0,
                                          random_state=1).fit(X_train, y_train)
    else:
        essembleModel = RandomForestClassifier(n_estimators=n_estimators, max_leaf_nodes=16, n_jobs=-1,
                                               random_state=42).fit(X_train, y_train)

    y_pred = essembleModel.predict(X_test)
    accuracyResult.append(accuracy_score(y_test, y_pred))
    cm = confusion_matrix(y_test, y_pred)
    showResult(cm, name)


essembleName = ["BaggingClassifier", "RandomForestClassifier"]
n_estimators = [5, 10, 20, 50, 100]

for i in essembleName:
    accuracyResult = []
    for j in n_estimators:
        essemble(i, j)
    print("{0} Max Score : ".format(i), max(accuracyResult))
    print("-" * 60)
