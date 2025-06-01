import socket

host = '192.168.222.71'  # Replace with actual IP
port = 3333

s = socket.socket()
s.connect((host, port))

while True:
    data = s.recv(1024).decode().strip()
    if data:
        values = data.split(',')
        if len(values) == 6:
            ax, ay, az, gx, gy, gz = [float(v) for v in values]
            print(f"ax={ax}, ay={ay}, az={az}, gx={gx}, gy={gy}, gz={gz}")
        else:
            print(f"{data}")
