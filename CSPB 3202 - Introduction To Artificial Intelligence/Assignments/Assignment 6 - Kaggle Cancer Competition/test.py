import os
import pandas as pd
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.models import load_model

# Load the model from the file
model = load_model('cancer_detector.keras')

# Create a data frame for the test data
test_datagen = ImageDataGenerator(rescale=1./255)

''' test_generator - Image Data Generator for test data
        directory - Directory containing the images
        target_size - Size to resize the images to
        batch_size - Number of images to process at a time
        class_mode - Type of classification task (None in this case)
        shuffle - Shuffle the data
        classes - List of class subdirectories
'''
test_generator = test_datagen.flow_from_directory(
    directory='test/',
    target_size=(96, 96),
    batch_size=32,
    class_mode=None,
    shuffle=False,
    classes=['.']
)

# Get the image IDs
image_ids = [os.path.basename(f) for f in test_generator.filenames]
image_ids = [f[:-4] if f.endswith('.tif') else f for f in image_ids]

# Make predictions on the test data
predictions = model.predict(test_generator)

# Create a data frame for the submission file
submission_df = pd.DataFrame({
    'id': image_ids,
    'label': predictions.flatten()
})

# Save the submission file
submission_df.to_csv('submission.csv', index=False)

# Print a message when the csv file is saved
print("Submission file saved as submission.csv")