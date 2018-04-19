import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt

mpl.rcParams['legend.fontsize'] = 10

#fig = plt.figure()
#ax = fig.gca(projection='3d')
#theta = np.linspace(-4 * np.pi, 4 * np.pi, 100)
#z = np.linspace(-2, 2, 100)
#r = z ** 2 + 1
#x = r * np.sin(theta)
#y = r * np.cos(theta)
#ax.plot(x, y, z, label='parametric curve')
#ax.legend()
#print(theta)
#plt.show()


fig = plt.figure()
ax = fig.gca(projection='3d')
ax.set_xlabel('X ')
ax.set_ylabel('Y ')
ax.set_zlabel('Z ')

ax.set_xlim((0, 20))
ax.set_ylim((20, 0))
ax.set_zlim((20, 0))
t = np.linspace(0 , 4, 100)
x = 2 * t
y = 3 * t
z = 4 * t
ax.plot(x, y, z, label='parametric curve')
ax.legend()

plt.show()