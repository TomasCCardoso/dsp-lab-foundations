from math import inf
import numpy as np

#Fix the seed for reproducibility
np.random.seed(42)
#Run the simulatilation for 10 iterations
N = 10 # Number of ground users

users = np.random.uniform(low=0, high=100, size=(N, 2))  # Randomly generate user positions in a 100x100 area

print(users)  # Print the generated user positions
print(users.shape)  # Print the shape of the user positions array

# ============================================================
# UAV Candidate Position Grid Generation
# ============================================================

grid_size = 400 # 400 x 400 = 160000 candidate positions

xs = np.linspace(0,100, grid_size) # Generate 400 points from 0 to 100 for x-coordinates
ys = np.linspace(0,100, grid_size) # Generate 400 points from 0 to 100 for y-coordinates

best_position = None 
best_max_dist = inf

for x in xs:
    for y in ys:
        candidate = np.array([x, y])  # Create a candidate position for the UAV
        distances = np.linalg.norm(users - candidate, axis=1)  # Calculate distances from all users to the candidate position
        max_dist = np.max(distances)  # Find the maximum distance to any user
        
        if max_dist < best_max_dist:  # If this candidate position has a smaller maximum distance
            best_max_dist = max_dist  # Update the best maximum distance
            best_position = candidate  # Update the best position

print(f"Best UAV Position: {best_position}, with maximum distance to users: {best_max_dist}")