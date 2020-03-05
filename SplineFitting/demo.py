import numpy as np
import matplotlib.pyplot as plt

import pysplfit

# Input point cloud in row-major format.
input = [0, 0, 0, .5, 0, 1, 1, 0, 1, 1]
fig, ax = plt.subplots()

input_np = np.reshape(np.array(input), (-1, 2))
ax.plot(input_np[:, 1], input_np[:, 0], linewidth=1, linestyle='', marker='x', markersize=7, color='blue')
# The control points and the contour in the same format. Only the first parameter is mandatory.
# alpha: curvature coeff, beta: curve length coeff, epsilon: stopping condition
fit_contorls, fit_contour = pysplfit.fit(input, controlnum=30, maxiternum=20, alpha=0.0025, beta=0.006, epsilon=0.002)

fit_controls_np = np.reshape(np.array(fit_contorls), (-1, 2))
fit_contour_np = np.reshape(np.array(fit_contour), (-1, 2))

ax.plot(fit_controls_np[:, 1], fit_controls_np[:, 0], linewidth=1, linestyle='', marker='o', markersize=3, color='red')
ax.plot(fit_contour_np[:, 1], fit_contour_np[:, 0], linewidth=1, linestyle='solid', markersize=2, color='green')

plt.show()
