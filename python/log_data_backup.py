import csv

path_data = []
obs_data = []

with open('backup.txt', 'r') as backup_file:
    while True:
        line = backup_file.readline()
        if not line:
            break
        parts = line.strip().split(',')
        if parts[0] == 'PATH' and len(parts) == 5:
            lat = float(parts[1])
            lon = float(parts[2])
            heading = float(parts[3])
            path_data.append((lat, lon, heading))
            print(f'PATH: lat={lat}, lon={lon}, heading={heading}')
        
        elif parts[0] == 'OBS' and len(parts) == 6:
            lat = float(parts[1])
            lon = float(parts[2])
            heading = float(parts[3])
            distance = float(parts[4])
            obs_data.append((lat, lon, heading, distance))
            print(f'OBS: lat={lat}, lon={lon}, heading={heading}, distance={distance}')
with open('path_data.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Latitude', 'Longitude', 'Heading'])
    writer.writerows(path_data)

# Save OBS data to CSV
with open('obs_data.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Latitude', 'Longitude', 'Heading', 'Distance'])
    writer.writerows(obs_data)
    
print("Data saved to path_data.csv and obs_data.csv")# backup_file.close() is not needed when using a context manager