import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import glob

# 1) Récupération et tri des fichiers
files = sorted(glob.glob("results_*.txt"))

# 2) Chargement initial (première frame)
data = np.loadtxt(files[0], delimiter=",")
x, y, z = data[:, 0], data[:, 1], data[:, 2]

# 3) Création de la figure
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(projection="3d")

scat = ax.scatter(x, y, z, c=z, cmap="viridis", s=10)

ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")
ax.set_title("Évolution temporelle des particules")
ax.set_box_aspect([1, 1, 1])

# Limites fixes (important pour éviter un zoom qui bouge)
ax.set_xlim(-20, 20)
ax.set_ylim(-20, 20)
ax.set_zlim(-20, 20)

# 4) Fonction de mise à jour
def update(frame):
    data = np.loadtxt(files[frame], delimiter=",")
    x, y, z = data[:, 0], data[:, 1], data[:, 2]

    scat._offsets3d = (x, y, z)
    scat.set_array(z)  # met à jour la couleur
    ax.set_title(f"Frame {frame}")

    return scat,

# 5) Animation
ani = FuncAnimation(
    fig,
    update,
    frames=len(files),
    interval=200,   # ms entre deux frames
    blit=False
)

plt.show()
