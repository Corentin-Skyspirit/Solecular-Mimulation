import numpy as np
import matplotlib.pyplot as plt

filename = "results.txt"  # nom fichier

data = np.loadtxt(filename, delimiter=",")

x = data[:, 0]
y = data[:, 1]
z = data[:, 2]

fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(projection="3d")
ax.scatter(x, y, z, s=10, alpha=0.7)
ax.scatter(x, y, z, c=z, cmap="viridis", s=10)
ax.set_box_aspect([1, 1, 1])

ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")
ax.set_title("Distribution des particules")

plt.tight_layout()
plt.show()
