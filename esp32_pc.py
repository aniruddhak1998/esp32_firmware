import socket

# bind all IP
HOST = '0.0.0.0'
#Listen on port
PORT = 44444
#Size of recieve buffer
BUFFER_SIZE =8
#Create a TCP/IP socket
s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
#Bind the socket to the host and port
s.bind((HOST,PORT))
teamID = chr(127)
motor1 =chr(30)
motor2 = chr(30)
motor3 = chr(30)
motor4 = chr(0)
kicker = chr(255)
a = motor1+motor2+motor3+motor4

while True:
	data = s.recvfrom(BUFFER_SIZE)
	if data:
		#print recieved data
		print ('Clent to server: ', data)
		#send data to the client
		s.sendto(a,data[1])
		print(a)
