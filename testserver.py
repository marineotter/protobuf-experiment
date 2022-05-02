import sample_pb2
import pprint
import socket

person = sample_pb2.Person()

server_ip = "127.0.0.1"
server_port = 8080
listen_num = 5
buffer_size = 1024

tcp_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcp_server.bind((server_ip, server_port))
tcp_server.listen(listen_num)

while True:
    client, address = tcp_server.accept()
    data = client.recv(buffer_size)
    person.ParseFromString(data)
    pprint.pprint(person)
