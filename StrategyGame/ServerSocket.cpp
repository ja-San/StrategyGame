//
//  ServerSocket.cpp
//  Server_C_Socket
//
//  Created by Jake Sanders on 9/5/16.
//  Copyright © 2016 Jake Sanders. All rights reserved.
//

#include "ServerSocket.hpp"

ServerSocket::ServerSocket() {}

//Static functions

std::string ServerSocket::getHostName() {
    char name[1024];
    if (gethostname(name, 1024) < 0) {
        throw std::runtime_error(std::string("ERROR getting host name: ") + strerror(errno));
    }
    return std::string(name);
}

//Public member functions

void ServerSocket::setSocket(int portNum) {
    int returnVal;
    
    addrinfo hints; //A struct containing information on the address. Will be passed to getaddrinfo() to give hints about the connection to be made
    addrinfo* serverAddressList; //A pointer to an addrinfo struct that will be filled with the server address by getaddrinfo()
    
    memset(&hints, 0, sizeof(hints)); //Initializes hints with all 0's
    hints.ai_family = AF_UNSPEC; //Can be either IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; //TCP Socket
    hints.ai_flags = AI_PASSIVE; //Make the socket use localhost
    
    /* getaddrinfo
     The getaddrinfo() fills a given addrinfo struct with the relevant information. The return value is nonzero when there is an error.
     
     The first argument is the name of the host to connect with.
     
     The second argument is a string representation of the port number.
     
     The third argument is a pointer to an addrinfo struct which contains hints about the type of connection to be made.
     
     The fourth argument is a pointer which will be filled with a linked list of hosts returned. If just one host is being looked for, the first result can just be used.
     */
    returnVal = getaddrinfo(NULL, std::to_string(portNum).c_str(), &hints, &serverAddressList);
    
    if (returnVal != 0) {
        throw std::runtime_error(std::string("ERROR getting local address: ") + std::string(gai_strerror(returnVal))); //gai_strerror() returns a c string representation of the error
    }
    
    //Set the first host in the list to the desired host
    this->serverAddress = *serverAddressList;
    
    /* socket()
     The socket() function returns a new socket, with three parameters.
     
     The first argument is address of the domain of the socket.
     The two possible address domains are the unix, for commen file system sockets, and the internet, for anywhere on the internet.
     AF_UNIX is generally used for the former, and AF_INET generally for the latter.
     
     The second argument is the type of the socket.
     The two possible types are a stream socket where characters are read in a continuous stream, and a diagram socket, which reads in chunks.
     SOCK_STREAM is generally used for the former, and SOCK_DGRAM for the latter.
     
     The third argument is the protocol. It should always be 0 except in unusual circumstances, and then allows the operating system to chose TCP or UDP, based on the socket type. TCP is chosen for stream sockets, and UDP for diagram sockets
     
     The function returns an integer than can be used like a reference to the socket. Failure results in returning -1.
     */
    //In this case, the values are taken from getaddrinfo(), from the first returned addrinfo struct in the linked list.
    this->hostSocket = socket(this->serverAddress.ai_family, this->serverAddress.ai_socktype, this->serverAddress.ai_protocol);
    
    //Checks for errors initializing socket
    if (this->hostSocket < 0)
        throw std::runtime_error(std::string("ERROR opening socket") + std::string(strerror(errno)));
    
    int enable = 1;
    //This code tells the kernel that the port can be reused as long as there isn't an active socket listening there. This means that after the socket is closed the port can immediately be reused without giving an error
    if (setsockopt(this->hostSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1) {
        throw std::runtime_error(std::string("ERROR setting port to reusable") + std::string(strerror(errno)));
    }
    
    /* bind()
     The bind() function connects a socket to a local address, with three parameters.
     Here it will connect the socket to the (local) host at the proper port number.
     
     The first argument is the socket, by its simple integer reference.
     
     The second argument is a pointer to the address, contained as a sockaddr_in struct. It must be cast properly.
     
     The third argument is the size of the sockaddr_in struct that is passed in by reference.
     
     This function can fail for multiple reasons. The most likely one is if the port is already in use.
     */
    if (bind(this->hostSocket, this->serverAddress.ai_addr, this->serverAddress.ai_addrlen) < 0)
        throw std::runtime_error(std::string("ERROR binding socket to host: ") + std::string(strerror(errno)));
    
    /* listen()
     The listen() function listens for connections on the socket, with two arguments.
     
     The first argument is the socket, by its simple integer reference.=
     
     The second argument is the size of the "backlog queue", or the number of connections that can be waiting as another connection is handled. It basically is the number of connections that can wait before being accepted.
     
     This function cannot fail, as long as the socket is valid, so there is no error code.
     */
    if (listen(this->hostSocket, MAX_NUMBER_OF_CONNECTIONS) < 0) {
        throw std::runtime_error(std::string("ERROR listening for incoming connections") + std::string(strerror(errno)));
    }
    
    //Initialize activeConnections[] as false
    for (int a = 0; a < MAX_NUMBER_OF_CONNECTIONS; a++) {
        this->activeConnections[a] = false;
    }
    
    freeaddrinfo(serverAddressList); //Free the linked list now that we have the local host information
    this->setUp = true;
}

void ServerSocket::addClient() {
    if (!this->setUp)
        throw std::logic_error("Socket not set");
    
    int nextIndex = this->getNextAvailableIndex();
    
    if (nextIndex == -1) {
        throw std::range_error("Cannot connect more than " + std::to_string(MAX_NUMBER_OF_CONNECTIONS) + " sockets");
    }
    
    /* accept()
     The accept() function makes the process block until a connection is formed between the client and the server, with three arguments. It then wakes when the connection is successfully established.
     
     The first argument is the host side socket, passed by its reference.
     
     The second argument is a reference to the address of the client, in the form of a sockaddr struct pointer.
     
     The third argument is the size of the struct, passed by value.
     
     The return value is a socket, passed by a small integer reference.
     */
    this->clientSockets[nextIndex] = accept(this->hostSocket, (struct sockaddr *)&this->clientAddresses[nextIndex], &this->clientAddressSizes[nextIndex]);
    
    //Checks for error with accepting
    if (this->clientSockets[nextIndex] < 0)
        throw std::runtime_error(std::string("ERROR accepting client") + std::string(strerror(errno)));
    
    this->activeConnections[nextIndex] = true;
}

void ServerSocket::closeConnection(unsigned int clientIndex) {
    if (!this->setUp)
        throw std::logic_error("Socket not set");
    
    if (clientIndex >= MAX_NUMBER_OF_CONNECTIONS || !this->activeConnections[clientIndex])
        throw std::range_error("Socket index uninitialized");
    
    close(this->clientSockets[clientIndex]);
    
    this->clientAddresses[clientIndex] = sockaddr_storage();
    this->clientAddressSizes[clientIndex] = 0;
    
    this->activeConnections[clientIndex] = false;
}

void ServerSocket::send(const char* message, unsigned int clientIndex, bool throwErrorIfNotFullySent) {
    if (!this->setUp)
        throw std::logic_error("Socket not set");
    
    if (clientIndex >= MAX_NUMBER_OF_CONNECTIONS || !this->activeConnections[clientIndex])
        throw std::range_error("Socket index uninitialized");
    
    long messageLength = strlen(message);
    
    std::string str = std::string(message);
    
    if (str == "" || messageLength < 1)
        throw std::logic_error("No message to send");
    
    long messageSize = write(this->clientSockets[clientIndex], message, strlen(message));
    
    if (messageSize < 0) {
        throw std::runtime_error(std::string("ERROR sending message: ") + std::string(strerror(errno)));
    } else if (messageSize < messageLength) {
        if (throwErrorIfNotFullySent) { //Error sent only if optional parameter is manually set to true: if the message was too long to send all of it
            throw std::runtime_error(std::string("ERROR message too long: only sent ") + std::to_string(messageSize) + std::string(" of ") + std::to_string(messageLength) + std::string(" characters"));
        } else {
            std::cout << "ERROR message too long: only sent " << messageSize << " of " << messageLength << " characters" << std::endl;
        }
    }
}

void ServerSocket::broadcast(const char* message, bool throwErrorIfNotFullySent) {
    if (!this->setUp)
        throw std::logic_error("Socket not set");
    
    for (int a = 0; a < MAX_NUMBER_OF_CONNECTIONS; a++) {
        if (this->activeConnections[a]) {
            this->send(message, a, throwErrorIfNotFullySent);
        }
    }
}

std::string ServerSocket::receive(unsigned int clientIndex, bool* socketClosed) {
    if (!this->setUp)
        throw std::logic_error("Socket not set");
    
    if (clientIndex >= MAX_NUMBER_OF_CONNECTIONS || !this->activeConnections[clientIndex])
        throw std::range_error("Socket index uninitialized");
        
    char buffer[MAXIMUM_SOCKET_MESSAGE_SIZE]; //This program will read characters from the connection into this buffer
    
    //Initialize the buffer where received info is stored
    bzero(buffer, MAXIMUM_SOCKET_MESSAGE_SIZE);
    
    long messageSize; //Stores the return value from the calls to read() and write() by holding the number of characters either read or written
    
    /* read()
     The read() function will read in info from the client socket, with three arguments. It will block until the client writes and there is something to read in.
     
     The first argument is the reference for the client's socket.
     
     The second argument is the buffer to store the message.
     
     The third argument is the maximum number of characters to to be read into the buffer.
     */
    messageSize = read(this->clientSockets[clientIndex], buffer, MAXIMUM_SOCKET_MESSAGE_SIZE);
    
    //Checks for errors reading from the socket
    if (messageSize < 0)
        throw std::runtime_error(std::string("ERROR reading from socket: ") + std::string(strerror(errno)));
    
    if (socketClosed != nullptr && messageSize == 0) {
        *socketClosed = true;
    }
    
    std::string str = std::string(buffer, messageSize);
    
    //Check if there is more data waiting to be read, and if so, read it
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(this->hostSocket, &readfds);
    int n = this->hostSocket + 1;
    
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 20000;
    
    int returnValue = select(n, &readfds, NULL, NULL, &timeout);
    if (returnValue < 0) {
        throw std::runtime_error(std::string("ERROR finding information about socket: ") + std::string(strerror(errno)));
    } else if (returnValue > 0) {
        str += this->receive(clientIndex);
    }
    
    return str;
}

bool ServerSocket::allReceived(const char* messageToCompare) {
    for (int a = 0; a < MAX_NUMBER_OF_CONNECTIONS; a++) {
        bool connectionClosed = false;
        if (this->activeConnections[a] && this->receive(a, &connectionClosed) != messageToCompare)
            if (connectionClosed) {
                this->closeConnection(a);
                return false;
            }
    }
    return true;
}

void ServerSocket::setTimeout(unsigned int seconds, unsigned int milliseconds) {
#if defined(_WIN32)
    DWORD timeout = (seconds * 1000) + milliseconds;
    for (int a = 0; a < MAX_NUMBER_OF_CONNECTIONS; a++) {
        if (this->activeConnections[a]) setsockopt(this->clientSockets[a], SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
    }
#else
    struct timeval time;
    time.tv_sec = seconds;
    time.tv_usec = (milliseconds * 1000);
    for (int a = 0; a < MAX_NUMBER_OF_CONNECTIONS; a++) {
        if (this->activeConnections[a]) setsockopt(this->clientSockets[a], SOL_SOCKET, SO_RCVTIMEO, (struct timeval*)&time, sizeof(struct timeval));
    }
#endif
}

void ServerSocket::setHostTimeout(unsigned int seconds, unsigned int milliseconds) {
#if defined(_WIN32)
    DWORD timeout = (seconds * 1000) + milliseconds;
    setsockopt(this->hostSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
#else
    struct timeval time;
    time.tv_sec = seconds;
    time.tv_usec = (milliseconds * 1000);
    setsockopt(this->hostSocket, SOL_SOCKET, SO_RCVTIMEO, (struct timeval*)&time, sizeof(struct timeval));
#endif
}

unsigned int ServerSocket::numberOfClients() {
    int connections = 0;
    for (int a = 0; a < MAX_NUMBER_OF_CONNECTIONS; a++) {
        if (this->activeConnections[a]) {
            connections++;
        }
    }
    return connections;
}

bool ServerSocket::getSet() {
    return this->setUp;
}

//Private member functions

int ServerSocket::getNextAvailableIndex() {
    for (int a = 0; a < MAX_NUMBER_OF_CONNECTIONS; a++) {
        if (!this->activeConnections[a]) return a;
    }
    return -1;
}

//Destructor

ServerSocket::~ServerSocket() {
    if (this->setUp) {
        //Properly terminate the sockets
        for (int clientIndex = 0; clientIndex < MAX_NUMBER_OF_CONNECTIONS; clientIndex++) {
            if (this->activeConnections[clientIndex]) {
                close(this->clientSockets[clientIndex]);
            }
        }
        close(this->hostSocket);
    }
}
