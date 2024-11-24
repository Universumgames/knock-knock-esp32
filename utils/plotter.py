import PIL
from PIL import Image
import matplotlib.pyplot as plt
from matplotlib import pyplot  
import numpy as np

#open data.bin, read hex values and convert to float
def read_data_raw():
    data = np.fromfile('./encoded_raw.bin', dtype=np.uint16)
    return data

def read_data_avg():
    data = np.fromfile('./encoded_avg.bin', dtype=np.uint16)
    return data

def read_data_delta():
    data = np.fromfile('./encoded_delta.bin', dtype=np.int32)
    return data

def read_data_delta_ms():
    data = np.fromfile('./encoded_delta_ms.bin', dtype=np.uint64)
    return data

#plot data
def plot_data(data):
    plt.plot(data)
    plt.show()

# show data
avg = read_data_avg()
delta = read_data_delta()
raw = read_data_raw()
delta_ms = read_data_delta_ms()

plot_data(raw)
plot_data(delta)
plot_data(avg)
plot_data(delta_ms)