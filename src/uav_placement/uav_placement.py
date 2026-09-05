import numpy as np

#Fix the seed for reproducibility
np.random.seed(42)
#Run the simulatilation for 10 iterations
N = 10 # Number of ground users

users = np.random.uniform(low=0, high=100, size=(N, 2))  # Randomly generate user positions in a 100x100 area

print(users)  # Print the generated user positions
print(users.shape)  # Print the shape of the user positions array