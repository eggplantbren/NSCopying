"""
A little script to simulate what would happen with particle
depletion in a deep problem with two identical but separated modes.
"""

import numpy as np
import numpy.random as rng
import matplotlib.pyplot as plt

# Number of particles
N = 10000

# Which of the two modes they're all in
mode = (rng.rand(N) < 0.5).astype('int')

# Number of NS iterations to do
steps = 1000*N

# Do the NS loop
for i in range(0, steps):
	# Delete a particle
	which = rng.randint(N)

	# Overwrite it with a clone of another
	copy = rng.randint(N)
	while copy == which:
		copy = rng.randint(N)
	mode[which] = mode[copy]

	if (i+1)%N == 0:
		print('After {j} iterations, fraction in mode 1 is {f}'.format\
							(j=(i+1), f=mode.mean()))

