import network
import usocket

class NetworkUtil:    
    def connectWlan(self, ssid: str, password: str, ipTuple: tuple) -> str:
        # Connect to WLAN using secrets from secrets.py file.
        
        wLanScan = []
        while not wlanScan:
            wlan = network.WLAN(network.STA_IF)
            wlan.active(True)
            wlanScan = wlan.scan()
            print(f"Scanned SSIDs: {[_[0] for _ in wlanScan]}")
        
        wlan.connect(ssid, password)
        wlan.ifconfig(ipTuple)
        while wlan.status() < 1:
            print(f"Waiting for connection, status: {wlan.status()}...")
            
        return wlan.ifconfig()[0]
    
    def setupTcpSocketConnection(self, ip: str, port: int = 80, maxClients: int = 1) -> tuple:
        # Set up a TCP socket for calls over networks.
        
        print("Setting up TCP socket...")
        socketAddress = usocket.getaddrinfo(ip, port)[0][-1]
        
        listenerSocket = usocket.socket()
        listenerSocket.setsockopt(usocket.SOL_SOCKET, usocket.SO_REUSEADDR, 1)
        listenerSocket.bind(socketAddress)
        listenerSocket.listen(maxClients)
        
        print(f"TCP socket listening on {socketAddress}")
        return listenerSocket
