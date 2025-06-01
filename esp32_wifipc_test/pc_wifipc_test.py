import socket

host = '192.168.222.71'  # Replace with actual ESP32 IP
port = 3333

s = socket.socket()
s.connect((host, port))

while True:
    data = s.recv(1024).decode().strip()
    if data:
        values = [float(v) for v in data.split(',')]
        print(values)
