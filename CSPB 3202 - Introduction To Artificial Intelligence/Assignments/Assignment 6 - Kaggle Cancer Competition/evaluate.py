import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

epoch_domain = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
epoch_tacc = [0.5981, 0.655, 0.6774, 0.6928, 0.6948, 0.6977, 0.7032, 0.7038, 0.7062, 0.7087]
epoch_tloss = [0.6611, 0.6204, 0.6048, 0.5944, 0.5885, 0.5855, 0.5799, 0.5789, 0.5751, 0.5720]
epoch_vacc = [0.6605, 0.6942, 0.6947, 0.6949, 0.7049, 0.7025, 0.7099, 0.7086, 0.7096, 0.7085]
epoch_vloss = [0.6245, 0.6078, 0.5972, 0.5890, 0.5863, 0.5819, 0.5756, 0.5761, 0.5739, 0.5715]

epochs = ('1', '2', '3', '4', '5', '6', '7', '8', '9', '10')
values = {
    'T. Acc': (0.5981, 0.655, 0.6774, 0.6928, 0.6948, 0.6977, 0.7032, 0.7038, 0.7062, 0.7087),
    'T. Loss': (0.6611, 0.6204, 0.6048, 0.5944, 0.5885, 0.5855, 0.5799, 0.5789, 0.5751, 0.5720),
    'V. Acc': (0.6605, 0.6942, 0.6947, 0.6949, 0.7049, 0.7025, 0.7099, 0.7086, 0.7096, 0.7085),
    'V. Loss': (0.6245, 0.6078, 0.5972, 0.5890, 0.5863, 0.5819, 0.5756, 0.5761, 0.5739, 0.5715)
}
x = np.arange(len(epochs))
width = 0.20
multiplier = 0

fig, ax = plt.subplots(layout='constrained')

for att, val in values.items():
    offset = width * multiplier
    rects = ax.bar(x + offset, val, width, label=att)
    multiplier += 1

ax.set_title('Training and Validation Accuracy and Loss')
ax.set_ylim(0, 1)
ax.set_xlabel('Epochs')
ax.set_ylabel('Percentage')
ax.set_xticks(x + width, epochs)
ax.legend(loc='upper left')

plt.show()

df = pd.read_csv('submission.csv')

plt.figure(figsize=(10, 6))
plt.hist(df['label'], bins=50, edgecolor='k', alpha=0.7)
plt.title('Distribution Of Cancer Probability')
plt.xlabel('Probability Of Cancer In Image')
plt.ylabel('Frequency Of Probability')
plt.show()