# SynPulse

A terminal-based LAN chat application written in C using POSIX sockets.

SynPulse is being built incrementally to understand networking fundamentals and low-level socket programming concepts such as TCP connections, IP addressing, ports, and client-server communication.

## Goals

- Understand the TCP/IP networking stack
- Learn POSIX socket programming in C
- Build client-server communication from first principles
- Explore how higher-level networking applications are implemented internally
- Maybe use ncurses or soemthing  bit but that was not the point of this project so prolly not gonna be doing that

## cool stuff ig?

- As it is LAN, private IP's will be used obviously so we get to see NAT, ports, IP addresses and sockets working in real time instead of as abstract concepts only.
- by phase 4/ phase 5 it is a highly simplified version of discord from first principles.
- we use multithreading using POSIX threads(pthreads) but the same outcome can also be achieved using poll() or epoll() 

## Roadmap

### Phase 1: Connection Establishment

- [x] Create a TCP socket
- [x] Bind the server to a port
- [x] Listen for incoming connections
- [x] Connect the client to the server
- [x] Establish a successful TCP connection

### Phase 2: Basic Communication

- [x] Send a single message from client to server
- [x] Receive and display the message on the server
- [x] Send a single message from server to client
- [x] Verify bidirectional communication

### Phase 3: Interactive Chat

- [x] Implement continuous message exchange
- [ ] Gracefully terminate connections
- [ ] Handle unexpected client disconnects
- [ ] Add basic input validation

### Phase 4: Concurrent Communication

- [x] Allow simultaneous sending and receiving
- [x] Introduce multithreading support
- [x] Remove blocking input behavior

### Phase 5: Multiple Clients

- [ ] Support multiple concurrent clients
- [ ] Maintain a list of active clients
- [ ] Broadcast messages to all connected clients

### Phase 6: Chat Features

- [ ] Usernames
- [ ] Join and leave notifications
- [ ] Timestamps
- [ ] Basic commands

### Phase 7: Advanced Features

- [ ] File transfer
- [ ] Private messaging
- [ ] Message history
- [ ] Configuration support

## Core Concepts Covered

- `getaddrinfo()`
- `socket()`
- `bind()`
- `listen()`
- `accept()`
- `connect()`
- `send()`
- `recv()`
- `close()`

## Technologies

- C
- POSIX Sockets
- TCP/IP

## Status

Im currently working on this project while learning about network-programming alongside. It is only for learning purposes.
