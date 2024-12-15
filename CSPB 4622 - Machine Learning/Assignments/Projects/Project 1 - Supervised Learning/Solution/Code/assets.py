from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.ensemble import RandomForestClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import classification_report, confusion_matrix, roc_curve, auc
from sklearn.model_selection import GridSearchCV, RandomizedSearchCV
import joblib
import pandas as pd
import seaborn as sns
import os
import matplotlib.pyplot as plt

''' AnalyzeModel - Analyzes a model that was previously trained
        Input:
            modelName - The name of the model to analyze
            x_test - The features of the test data
            y_test - The target values of the test data
        Algorithm:
            * Load the model
            * Make predictions
            * Print the classification report
            * Create a confusion matrix and display it
            * Create an ROC curve and display it if the model supports probability predictions
        Output:
            None
'''
def AnalyzeModel(modelName, x_test, y_test):
    # Load the model
    model = joblib.load(f"../Models/{modelName}.pkl")
    # Make predictions
    predictions = model.predict(x_test)
    # Print the classification report
    print(f"Model - {modelName}, Classification Report:")
    print(classification_report(y_test, predictions))
    # Create Confusion Matrix
    cm = confusion_matrix(y_test, predictions)
    plt.figure(figsize=(10, 7))
    sns.heatmap(cm, annot=True, fmt="d", cmap='Blues')
    plt.xlabel('Predicted From Model (1: True, 0: False)')
    plt.ylabel('Actual Value (1: True, 0: False)')
    plt.title(f"Confusion Matrix For {modelName}")
    plt.show()
    # Create ROC Curve if model supports probability predictions
    if hasattr(model, "predict_proba"):
        probs = model.predict_proba(x_test)[:, 1]
        fpr, tpr, thresholds = roc_curve(y_test, probs)
        roc_auc = auc(fpr, tpr)
        plt.figure(figsize=(10, 7))
        plt.plot(fpr, tpr, color='darkorange', lw=2, label='ROC curve (area = %0.2f)' % roc_auc)
        plt.plot([0, 1], [0, 1], color='navy', lw=2, linestyle='--')
        plt.xlabel('False Positive Rate')
        plt.ylabel('True Positive Rate')
        plt.title(f'Receiver Operating Characteristic For {modelName}')
        plt.legend(loc="lower right")
        plt.show()
    else:
        print(f"{modelName} does not support probability predictions.")

''' TrainModel - Trains a model and saves it to a file
        Input:
            model - The model to train
            modelName - The name of the model
            x_train - The features of the training data
            y_train - The target values of the training data
            x_test - The features of the test data
        Algorithm:
            * Fit the model
            * Make predictions
            * Delete previous model if it exists
            * Save the model
        Output:
            [model, modelPred] - The trained model and its predictions
'''
def TrainModel(model, modelName, x_train, y_train, x_test):
    # Fit the model
    model.fit(x_train, y_train)
    # Make predictions
    modelPred = model.predict(x_test)
    # Delete previous model if it exists
    model_path = f"../Models/{modelName}.pkl"
    if os.path.exists(model_path):
        os.remove(model_path)
    # Save the model
    joblib.dump(model, model_path)
    return [model, modelPred]

''' PrepData - Prepares the data for training
        Input:
            data - The name of the data file
        Algorithm:
            * Read the data
            * Replace string values with numerical values
            * Drop rows with missing values in the 'HeartDisease' column
            * Save the cleaned data back to the CSV file
        Output:
            [X, Y] - The features and target values
'''
def PrepData(data):
    # Data Cleaning
    df = pd.read_csv(f'../Data/{data}.csv') # Read the data
    df = df.replace({"Yes": 1, "No": 0}) # Replace string values with numerical values
    df = df.replace({"Female": 1, "Male": 0}) # Replace string values with numerical values
    df = df.replace({
        "18-24": 0,
        "25-29": 1,
        "30-34": 2,
        "35-39": 3,
        "40-44": 4,
        "45-49": 5,
        "50-54": 6,
        "55-59": 7,
        "60-64": 8,
        "65-69": 9,
        "70-74": 10,
        "75-79": 11,
        "80 or older": 12,
    })
    df = df.replace({
        "American Indian/Alaskan Native": 0,
        "Asian": 1,
        "Black": 2,
        "Hispanic": 3,
        "Other": 4,
        "White": 5,
    }) # Replace string values with numerical values
    df = df[df['Diabetic'].isin([0,1])] # Drop rows with missing values in the 'Diabetic' column
    df = df.replace({
        "Poor": 0,
        "Fair": 1,
        "Good": 2,
        "Very good": 3,
        "Excellent": 4,
    }) # Replace string values with numerical values
    # Drop rows with missing values in the 'HeartDisease' column
    df = df.dropna(subset=['HeartDisease'])
    # Save the cleaned data back to the CSV file
    df.to_csv('../Data/Heart_Data.csv', index=False)
    X = df.drop('HeartDisease', axis=1)
    Y = df['HeartDisease']
    return [X, Y]

''' Run - Runs the program
        Input:
            None
        Algorithm:
            * Prepare the data
            * Split the data into training and testing sets
            * Train and analyze the models
        Output:
            None
'''
def Run():
    # Data
    X, Y = PrepData("Heart_Data")
    x_train, x_test, y_train, y_test = train_test_split(X, Y, test_size=0.2, random_state=42)
    def LR():
        ## Logistic Regression - Hyperparameter Tuning
        logReg = LogisticRegression(max_iter=2000)
        param_grid_logReg = {
            'penalty': ['l2'],  # 'l1', 'elasticnet' could be considered if 'liblinear' or 'saga' solver is used
            'C': [0.001, 0.01, 0.1, 1, 10, 100],  # Regularization strength
            'solver': ['lbfgs', 'liblinear', 'saga'],
        }
        grid_search_logReg = GridSearchCV(logReg, param_grid_logReg, cv=3, n_jobs=-1, verbose=2)
        logReg_opt = grid_search_logReg.fit(x_train, y_train)
        logReg_best = logReg_opt.best_estimator_

        # Train and Analyze the Best Logistic Regression Model
        logReg_best, logRegPred = TrainModel(logReg_best, "Optimized Logistic Regression", x_train, y_train, x_test)
        print("Logistic Regression Model Trained")
        return [logReg_best, logRegPred]
    def RF():
        # ## Random Forest - Hyperparameter Tuning
        rf = RandomForestClassifier(random_state=42)
        param_grid_rf = {
            'n_estimators': [100, 200, 300],               # Number of trees in the forest
            'max_depth': [10, 20, 30, None],               # Depth of the tree
            'min_samples_split': [2, 5, 10],               # Minimum samples required to split an internal node
            'min_samples_leaf': [1, 2, 4],                 # Minimum samples required to be at a leaf node
            'bootstrap': [True, False]                     # Whether bootstrap samples are used when building trees
        }
        random_search_rf = RandomizedSearchCV(rf, param_distributions=param_grid_rf, n_iter=50, cv=3, random_state=42, n_jobs=-1, verbose=2)
        rf_opt = random_search_rf.fit(x_train, y_train)
        rf_best = rf_opt.best_estimator_

        # Train and Analyze the Best Random Forest Model
        rf_best, rfPred = TrainModel(rf_best, "Optimized Random Forest", x_train, y_train, x_test)
        print("Random Forest Model Trained")
        return [rf_best, rfPred]
    def KNN():
        ## K Nearest Neighbors - Hyperparameter Tuning
        knn = KNeighborsClassifier()
        param_grid_knn = {
            'n_neighbors': [3, 5, 7, 9, 11, 15, 20],       # Number of neighbors to use
            'weights': ['uniform', 'distance'],            # Weight function used in prediction
            'metric': ['euclidean', 'manhattan', 'minkowski']  # Distance metric for neighbors
        }
        grid_search_knn = GridSearchCV(knn, param_grid_knn, cv=3, n_jobs=-1, verbose=2)
        knn_opt = grid_search_knn.fit(x_train, y_train)
        knn_best = knn_opt.best_estimator_

        # Train and Analyze the Best KNN Model
        knn_best, knnPred = TrainModel(knn_best, "Optimized K Nearest Neighbors", x_train, y_train, x_test)
        print("K Nearest Neighbors Model Trained")
        return [knn_best, knnPred]
    # Choices
    inp = input("Train Models (1), Evaluate Models (2), or Exit (3)? ")
    # Train Models
    if inp == "1":
        inputTrain = input("Train Logistic Regression (1), Random Forest (2), K Nearest Neighbors (3), or All (4)? ")
        # Logistic Regression
        if inputTrain == "1":
            LR()
        # Random Forest
        elif inputTrain == "2":
            RF()
        # K Nearest Neighbors
        elif inputTrain == "3":
            KNN()
        # All
        elif inputTrain == "4":
            LR()
            RF()
            KNN()
        return
    # Evaluate
    elif inp == "2":
        inputEval = input("Evaluate Logistic Regression (1), Random Forest (2), K Nearest Neighbors (3), or All (4)? ")
        # Logistic Regression
        if inputEval == "1":
            AnalyzeModel("Optimized Logistic Regression", x_test, y_test)
        # Random Forest
        elif inputEval == "2":
            AnalyzeModel("Optimized Random Forest", x_test, y_test)
        # K Nearest Neighbors
        elif inputEval == "3":
            AnalyzeModel("Optimized K Nearest Neighbors", x_test, y_test)
        # All
        elif inputEval == "4":
            AnalyzeModel("Optimized Logistic Regression", x_test, y_test)
            AnalyzeModel("Optimized Random Forest", x_test, y_test)
            AnalyzeModel("Optimized K Nearest Neighbors", x_test, y_test)
    # Other
    elif inp == "3":
        return
    return