import serial
import csv

ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
print('Listening...')

path_data = []
obs_data = []

try:
    backup_file = open('backup.txt', 'a')
    
    while True:
        line = ser.readline().decode('utf-8').strip()
        if not line:
            continue
        
        backup_file.write(line + '\n') 
        
        
        parts = line.split(',')
        if parts[0] == 'PATH' and len(parts) == 4:
            lat = float(parts[1])
            lon = float(parts[2])
            heading = float(parts[3])
            path_data.append((lat, lon, heading))
            print(f'PATH: lat={lat}, lon={lon}, heading={heading}')

        elif parts[0] == 'OBS' and len(parts) == 5:
            lat = float(parts[1])
            lon = float(parts[2])
            heading = float(parts[3])
            distance = float(parts[4])
            obs_data.append((lat, lon, heading, distance))
            print(f'OBS: lat={lat}, lon={lon}, heading={heading}, distance={distance}')
        
            

except KeyboardInterrupt:
    print("Stopped by User")
    ser.close()
    backup_file.close()

with open('path_data.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Latitude', 'Longitude', 'Heading'])
    writer.writerows(path_data)

with open('obs_data.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Latitude', 'Longitude', 'Heading', 'Distance'])
    writer.writerows(obs_data)
    