
import network
import socket
import time
import uasyncio

import secrets # Secret values in secrets.py

def connectWlan() -> str:
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    
    wlan.connect(secrets.ssid, secrets.password)
    ipStruct = (secrets.ipStruct) # https://docs.micropython.org/en/latest/library/network.html#network.Abstract
    wlan.ifconfig(ipStruct)
    while wlan.status() < 1:
        print("Waiting for reconnect")
        
    ip = wlan.ifconfig()[0]
    print(f"Connected on IP: {ip}")
    return ip

def udp():
    print('UDP')
    s=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    #s.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
    a = ('', 81)
    s.bind(a)
    
    print("UDP setup")
    
    #s.sendto(b'hello', ('127.0.0.1', 81))
    
    print('waiting....')
    data,addr= s.recvfrom(1024)
    print('ok....')
    s.sendto(data,addr)
    print('received:',data,'from',addr)
        
    print('end....')
    return 1

def tcp():
    print('TCP')
    s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
    a = ('', 80)
    s.bind(a)
    s.listen(1)
    
    print("TCP setup")
    connection, _ = s.accept()
    request = str(connection.recv(1024))
    
    print(request)
    s.close()
    
    return 1

ip = connectWlan()
udp()
#tcp()

        
