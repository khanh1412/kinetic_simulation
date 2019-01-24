import numpy as np
import matplotlib.pyplot as plt
data = np.genfromtxt("./data.csv", delimiter=",");
plt.plot(data[:,0], data[:,1], "k-");
plt.plot(data[:,0], data[:,2], "r-");
plt.plot(data[:,0], data[:,3], "b-");
plt.plot(data[:,0], data[:,4], "g-");
plt.show();
