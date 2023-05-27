# Network


## How do server listen on one port and making connections with multiple clients?

When a server is listening on a specific port while being able to accept connections from multiple clients, the operating system manages the underlying network communication using the following steps:

- **Binding**: The server program binds to a specific port on the network interface of the operating system. This ensures that incoming client connections are directed to the server's designated port.

- **Listening**: The server sets the socket to a listening state, indicating its readiness to accept incoming client connections. The operating system maintains a queue of pending connections **for the server socket.**

- **Accepting Connections**: As clients attempt to establish a connection with the server, the operating system accepts their connection requests and establishes separate communication channels known as **sockets** for each client.

- **Socket Creation**: The operating system creates **a new socket for each accepted client connection**. These **client sockets** are **distinct and independent from the server socket**.

- **Communication**: The server and each client can now communicate over their respective sockets. **The operating system handles the data transmission between the sockets**, ensuring that the messages from each client reach the server, and vice versa.

- **Multiplexing**: The operating system uses various mechanisms such as `select`, `poll`, or `epoll` to efficiently manage multiple client connections and multiplex data across them. This allows the server to handle concurrent communication with multiple clients without blocking or missing data.

- **Demultiplexing**: When the operating system receives data from any of the client sockets, it demultiplexes the data, determining which socket the data belongs to. This ensures that the server program can process the data from each client separately.

- **Closing Connections**: When a client or the server decides to end the connection, the corresponding socket is closed. The operating system releases the resources associated with that socket and updates its internal state accordingly.

By handling the binding, listening, socket creation, multiplexing, and demultiplexing operations, the operating system enables a server to listen on a single port and handle connections from multiple clients concurrently. This allows for efficient and simultaneous communication between the server and multiple clients over a network.