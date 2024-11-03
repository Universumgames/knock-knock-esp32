import PIL
from PIL import Image
import matplotlib.pyplot as plt
from matplotlib import pyplot  
import numpy as np

#open data.bin, read hex values and convert to float
def read_data():
    data = np.fromfile('./data_int.bin', dtype=np.int32)
    return data

#plot data
def plot_data(data):
    plt.plot(data)
    plt.show()

# show data
data = read_data()
plot_data(data)