import numpy as np
import matplotlib.pyplot as plt

# Define time vector from 0 to 5 with small intervals
t = np.linspace(0, 5, 500)

# Compute the function e^(-2t)
y = np.exp(-2 * t)

# Plotting
plt.plot(t, y, label=r'$e^{-2t}$', color='blue')
plt.title('Plot of $e^{-2t}$')
plt.xlabel('t')
plt.ylabel('Amplitude')
plt.grid(True)
plt.legend()
plt.show()
