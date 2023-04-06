import numpy as np

first_guess = 3

estimate = np.array((first_guess))
burst = [6, 8, 7, 3]
alpha = 0.5


for i in estimate:
    np.append(estimate, alpha * burst[i] + (1.0 - alpha) * estimate[i])
    print(estimate)
