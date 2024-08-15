import pandas as pd
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.applications import ResNet50
from tensorflow.keras.models import Model
from tensorflow.keras.layers import GlobalAveragePooling2D, Dense, Input
from tensorflow.keras.callbacks import ModelCheckpoint, EarlyStopping

# Load the labels from the CSV file
df = pd.read_csv('train_labels.csv')

# Create a data frame for the training data
df['label'] = df['label'].astype(str)
df['id'] = df['id'] + '.tif'

''' train_datagen - Image Data Generator for training data
        rescale - Rescale the pixel values to be between 0 and 1
        rotation_range - Rotate the image up to 20 degrees
        width_shift_range - Shift the image left or right by 20% of the width
        height_shift_range - Shift the image up or down by 20% of the height
        zoom_range - Zoom in on the image by 20%
        horizontal_flip - Flip the image horizontally
        validation_split - Split the data into training and validation sets
'''
train_datagen = ImageDataGenerator(
    rescale=1./255,
    rotation_range=20,
    width_shift_range=0.2,
    height_shift_range=0.2,
    zoom_range=0.2,
    horizontal_flip=True,
    validation_split=0.2
)

''' train_generator - Image Data Generator for training data
        dataframe - Data frame containing the image IDs and labels
        directory - Directory containing the images
        x_col - Column in the data frame containing the image IDs
        y_col - Column in the data frame containing the labels
        target_size - Size to resize the images to
        batch_size - Number of images to process at a time
        class_mode - Type of classification task (binary in this case)
        shuffle - Shuffle the data
        subset - Subset of the data (training or validation)
'''
train_generator = train_datagen.flow_from_dataframe(
    dataframe=df,
    directory='train/',
    x_col='id',
    y_col='label',
    target_size=(96, 96),
    batch_size=32,
    class_mode='binary',
    shuffle=True,
    subset='training'
)

''' validation_generator - Image Data Generator for validation data
        dataframe - Data frame containing the image IDs and labels
        directory - Directory containing the images
        x_col - Column in the data frame containing the image IDs
        y_col - Column in the data frame containing the labels
        target_size - Size to resize the images to
        batch_size - Number of images to process at a time
        class_mode - Type of classification task (binary in this case)
        shuffle - Shuffle the data
        subset - Subset of the data (training or validation)
'''
validation_generator = train_datagen.flow_from_dataframe(
    dataframe=df,
    directory='train/',
    x_col='id',
    y_col='label',
    target_size=(96, 96),
    batch_size=32,
    class_mode='binary',
    shuffle=True,
    subset='validation'
)

# Create a ResNet50 model with pre-trained weights
input_tensor = Input(shape=(96, 96, 3))

# Load the ResNet50 model with pre-trained weights and set trainable to false
base_model = ResNet50(input_tensor=input_tensor, include_top=False, weights='imagenet')
base_model.trainable = False

# Add a global average pooling layer and a dense layer for binary classification
x = base_model.output
x = GlobalAveragePooling2D()(x)

# Add a dense layer with a sigmoid activation function
output_tensor = Dense(1, activation='sigmoid')(x)

# Define the model with the input tensor and output tensor
model = Model(inputs=base_model.input, outputs=output_tensor)

# Compile the model with an Adam optimizer and binary cross-entropy loss function
model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])

# Fit the model with the training and validation data
callbacks = [
    ModelCheckpoint('best_model.keras', save_best_only=True),
    EarlyStopping(patience=10, restore_best_weights=True)
]

# Fit the model with the training and validation data, run for 10 epochs
model.fit(
    train_generator,
    epochs=10,
    validation_data=validation_generator,
    callbacks=callbacks
)

# Save the model
model.save('cancer_detector.keras')