import csv
import numpy as np
import utm
from matplotlib import pyplot as plt

path_lat, path_lon, path_heading = [], [], []

with open('path_data.csv') as file:
    reader = csv.DictReader(file)
    for row in reader:
        if (abs(float(row['Latitude'])) < 1E-6 and abs(float(row['Longitude'])) < 1E-6):
            continue
        else:
            path_lat.append(float(row['Latitude']))
            path_lon.append(float(row['Longitude']))
            path_heading.append(float(row['Heading']))
            
path_easting, path_northing = [], []

for lat, lon in zip(path_lat, path_lon):
    x, y, zone, _ = utm.from_latlon(lat, lon)
    path_easting.append(x)
    path_northing.append(y)


obs_lat, obs_lon, obs_heading, obs_distance = [], [], [], []


with open('obs_data.csv') as file:
    reader = csv.DictReader(file)
    for row in reader:
        if (abs(float(row['Latitude'])) < 1E-6 and abs(float(row['Longitude'])) < 1E-6):
            continue
        else:
            obs_lat.append(float(row['Latitude']))
            obs_lon.append(float(row['Longitude']))
            obs_heading.append(float(row['Heading']))
            obs_distance.append(float(row['Distance']))

obs_easting, obs_northing = [], []

for lat, lon in zip(obs_lat, obs_lon):
    x, y, zone, _ = utm.from_latlon(lat, lon)
    obs_easting.append(x)
    obs_northing.append(y)

path_heading = [90 - h for h in path_heading] # Adjust heading to match North as 0 degrees
obs_heading = [90 - h for h in obs_heading] # Adjust obstacle heading similarly


dx = [(dist / 100) * np.cos(np.radians(heading)) for dist, heading in zip(obs_distance, obs_heading)] # E-W displacement
dy = [(dist / 100) * np.sin(np.radians(heading)) for dist, heading in zip(obs_distance, obs_heading)] # N-S displacement

obs_easting_est = [(element + i) for element, i in zip(obs_easting, dx)]
obs_northing_est = [(element + i) for element, i in zip(obs_northing, dy)]

with open('estimated_data.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Easting (m)', 'Northing (m)', 'Heading (°)', 'Distance (cm)'])
    writer.writerows(zip(obs_easting_est, obs_northing_est, obs_heading, obs_distance))

plt.figure(figsize=(14, 10))  # Larger figure

# Plot path
plt.plot(path_easting, path_northing, c='green', marker='o', linestyle='dashed',
         label='Path', markersize=4, zorder=1)

# Path heading quivers
skip = 5
u_path = [np.cos(np.radians(h)) for h in path_heading]
v_path = [np.sin(np.radians(h)) for h in path_heading]
plt.quiver(path_easting[::skip], path_northing[::skip], u_path[::skip], v_path[::skip],
           color='blue', alpha=0.2, scale=25, width=0.005, label='Path Heading', zorder=2)

# Plot estimated obstacle positions
plt.scatter(obs_easting_est, obs_northing_est, c='red', marker='x',
            s=70, label='Obstacle Estimate', zorder=4)

# Obstacle heading quivers
u_obs = [np.cos(np.radians(h)) for h in obs_heading]
v_obs = [np.sin(np.radians(h)) for h in obs_heading]
skip = 1
plt.quiver(obs_easting_est[::skip], obs_northing_est[::skip], u_obs[::skip], v_obs[::skip],
           color='red', alpha=0.7, scale=15, width=0.005, label='Obstacle Heading', zorder=3)

# Dotted lines to connect path and obstacles
for easting, northing, est_easting, est_northing in zip(obs_easting, obs_northing, obs_easting_est, obs_northing_est):
    plt.plot([easting, est_easting], [northing, est_northing], color='gray', linestyle='dotted', alpha=0.5, zorder=5)

# Graph decoration
plt.title("Path and Obstacles with Heading Directions", fontsize=16)
plt.xlabel("Easting (m)", fontsize=12)
plt.ylabel("Northing (m)", fontsize=12)
plt.grid(True)
plt.axis('equal')
plt.legend(fontsize=10)
plt.tight_layout()
plt.savefig("trajectory_absolute.png", dpi=300)
plt.show()


# Define origin for relative coordinates
origin_easting = path_easting[0]
origin_northing = path_northing[0]

# Relative path and obstacle coordinates
rel_path_x = [x - origin_easting for x in path_easting]
rel_path_y = [y - origin_northing for y in path_northing]
rel_obs_x = [x - origin_easting for x in obs_easting]
rel_obs_y = [y - origin_northing for y in obs_northing]
rel_obs_x_est = [x - origin_easting for x in obs_easting_est]
rel_obs_y_est = [y - origin_northing for y in obs_northing_est]

# Plot relative trajectory
plt.figure(figsize=(14, 10))
plt.plot(rel_path_x, rel_path_y, c='green', marker='o', linestyle='dashed',
         label='Path', markersize=4, zorder=1)

skip = 5
u_path = [np.cos(np.radians(h)) for h in path_heading]
v_path = [np.sin(np.radians(h)) for h in path_heading]
plt.quiver(rel_path_x[::skip], rel_path_y[::skip], u_path[::skip], v_path[::skip],
           color='blue', alpha=0.2, scale=25, width=0.005, label='Path Heading', zorder=2)

plt.scatter(rel_obs_x_est, rel_obs_y_est, c='red', marker='x',
            s=70, label='Obstacle Estimate', zorder=4)

u_obs = [np.cos(np.radians(h)) for h in obs_heading]
v_obs = [np.sin(np.radians(h)) for h in obs_heading]
plt.quiver(rel_obs_x_est[::skip], rel_obs_y_est[::skip], u_obs[::skip], v_obs[::skip],
           color='red', alpha=0.7, scale=15, width=0.005, label='Obstacle Heading', zorder=3)

# Dotted lines from bot to estimated obstacle positions
for x0, y0, x1, y1 in zip(rel_obs_x, rel_obs_y, rel_obs_x_est, rel_obs_y_est):
    plt.plot([x0, x1], [y0, y1], color='gray', linestyle='dotted', alpha=0.5, zorder=5)

# Decorations
plt.title("Relative Path and Obstacles (Origin at Start Point)", fontsize=16)
plt.xlabel("Easting Offset (m)", fontsize=12)
plt.ylabel("Northing Offset (m)", fontsize=12)
plt.grid(True)
plt.axis('equal')
plt.legend(fontsize=10)
plt.tight_layout()
plt.savefig("trajectory_relative.png", dpi=300)
plt.show()
