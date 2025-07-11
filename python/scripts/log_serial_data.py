import serial
import csv

# Open serial port to read data from device (e.g., Arduino) at 115200 baud rate
ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
print('Listening...')

# Lists to store parsed PATH and OBS data
path_data = []
obs_data = []

try:
    # Open backup file in append mode to log all raw serial lines
    backup_file = open('backup.txt', 'a')
    
    while True:
        # Read a line from the serial port, decode to string, and strip whitespace
        line = ser.readline().decode('utf-8').strip()
        if not line:
            continue  # Skip empty lines
        
        # Write the raw line to the backup file
        backup_file.write(line + '\n') 
        
        # Split the line by commas to parse data
        parts = line.split(',')
        # If the line is a PATH message with correct number of fields
        if parts[0] == 'PATH' and len(parts) == 5:
            lat = float(parts[1])
            lon = float(parts[2])
            heading = float(parts[3])
            path_data.append((lat, lon, heading))
            print(f'PATH: lat={lat}, lon={lon}, heading={heading}')

        # If the line is an OBS message with correct number of fields
        elif parts[0] == 'OBS' and len(parts) == 6:
            lat = float(parts[1])
            lon = float(parts[2])
            heading = float(parts[3])
            distance = float(parts[4])
            obs_data.append((lat, lon, heading, distance))
            print(f'OBS: lat={lat}, lon={lon}, heading={heading}, distance={distance}')
        
            

except KeyboardInterrupt:
    # Handle Ctrl+C gracefully: close serial and backup file
    print("Stopped by User")
    ser.close()
    backup_file.close()

# After exiting the loop, save PATH data to CSV
with open('path_data.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Latitude', 'Longitude', 'Heading'])
    writer.writerows(path_data)

# Save OBS data to CSV
with open('obs_data.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Latitude', 'Longitude', 'Heading', 'Distance'])
    writer.writerows(obs_data)
    
print("Data saved to path_data.csv and obs_data.csv")
print("Backup saved to backup.txt")