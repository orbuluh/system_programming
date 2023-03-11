# Client server communication

> Notes highlighted from sources:
> - [Java, Java, Java: Object-Oriented Problem Solving, 2022E](https://runestone.academy/ns/books/published/javajavajava/sockets.html)

many networking applications are based on the client/ server model.

- According to this model, a **task** is viewed as a service that can be **requested by clients and handled by servers**.

- socket is a simple communication channel through which two programs communicate over a network.
- A socket supports two-way communication between a client and a server, using a well-established **protocol**.
- The **protocol simply prescribes rules and behavior that both the server and client must follow in order to establish two-way communication**.
- According to this protocol, a **server program creates a socket at a certain port and waits until a client requests a connection**.
- A port is a particular address or entry point on the **host** compute.
- Once the connection is established, the server creates input and output streams to the socket and begins sending messages to and receiving messages from the client. Either the client or the server can close the connection, but it's usually done by the client.
- Think of some service performed by a human using a telephone connection. The “server” waits for the phone to ring. When it rings, the server picks it up and begins communicating with the client. A socket, combined with input and output streams, is something like a two-way phone connection.
- From the client's side, the protocol goes as follows: The **client creates a socket and attempts to make a connection to the server. The client has to know the server's URL and the port at which the service exists.** Once a connection has been established, the client creates input and output streams to the socket and begins exchanging messages with the server. The client can close the connection when the service is completed.
  - Think again of the telephone analogy. A human client picks up the phone and dials the number of a particular service. This is analogous to the client program creating a socket and making a connection to a server. Once the service agent answers the phone, two-way communication between the client and the server can begin.
- Note that a socket has two channels. Once a connection has been established between a client and a server, a single two-way channel exists between them.
- The client's output stream is connected to the server's input stream. The server's output stream is connected to the client's input stream.