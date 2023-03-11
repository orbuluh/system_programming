# TCP/IP

> Notes highlighted from sources:
> - [CompTIA Network+ Certification Exam guide](https://a.co/d/5Pw7oZR)
> - [Java, Java, Java: Object-Oriented Problem Solving, 2022E](https://runestone.academy/ns/books/published/javajavajava/sockets.html)


## Historical/Contextual

Unlike the hardware organizations that worked together to make solid standards, the different organizations developing network software worked separately, secretly, and competitively. The four major players—Microsoft, Apple, Novell, and UNIX developers such as AT&T—created network software solutions that were mostly incompatible and had very different answers to the question “What do we share on a network?" ....

... everyone’s software had its own set of Rules of What a Network Should Do and How to Do It. These sets of rules—and the software written to follow these rules—were broken down into individual rules or languages called **protocols**. No single protocol could do everything a network needed to do, so companies lumped together all their necessary protocols under the term **protocol suite**

... It took about 20 very confusing years, but eventually TCP/IP replaced every other protocol suite in all but the most rare and unique situations.


## TCP/IP basics

The first two layers of the OSI seven-layer model deal with physical connectivity—wires and such—and protocols that interact with the physical. These are Layer 1, Physical, and Layer 2, Data Link. The TCP/IP protocol suite operates
at **Layers 3–7** of the OSI seven-layer model.



## Network Layer Protocols

- Internet Protocol (IP) works at the **Network layer**, where it takes data chunks from the Transport layer (which become the packet’s payload ), adds addressing, and creates the final IP packet.
- IP then hands the IP packet to the Data Link layer for encapsulation into a frame.

**IPv4 and IPv6 aren’t the only TCP/IP protocols that work at the Network layer.**

- **Internet Control Message Protocol (ICMP)**, for example, plays a role in **IP error reporting and diagnostics.**
- TCP/IP users rarely start a program that uses ICMP (or its IPv6 counterpart, ICMPv6). For the most part, software automatically uses ICMP as needed without direct user action.
- There are exceptions to every rule: the `ping` utility, a popular network diagnostic tool, directly uses ICMP. You can use ping to answer a question like, “can my computer communicate with any device at the IP address 192.168.1.15?”

When thinking about the Network layer, remember the following three protocols:

- IPv4 (normally referred to as simply “IP”)
- IPv6
- ICMP

The full IPv4 packet header has 14 different fields ... The destination and source IP address fields are critical for getting packets to their destination. ... Here are a few

- **Version The version (Ver)**: field defines the IP address type: 4, for IPv4. ...(The IPv6 packet header also starts with a version field (which is “6”), but the formats differ after that field.)
- **Total Length**: The total size of the IP packet in octets. This includes the IP header and its payload. This field is 16 bits, which limits the packet size to 65 KB.
- **Time to Live (TTL)**: Implementations of routers on the Internet are not perfect and engineers sometimes create loops. The TTL field prevents an IP packet from indefinitely spinning through the Internet by **using a counter that decrements by one every time a packet goes through a router.** This number cannot start higher than 255; many operating systems start at 128.
- **Protocol**: In most cases, the protocol field is either TCP or UDP and identifies what’s encapsulated inside the packet.


### Transport Layer Protocols

When moving data from one system to another, the TCP/IP protocol suite needs to know if the communication is **connection-oriented** or **connectionless**.

- If the data moving between two systems m**ust get there in good order**, a connection-oriented application is
the safe bet. **If it’s not a big deal for data to miss a bit or two**, then connectionless is the way to go.

- The connection-oriented protocol used with TCP/IP is called the **Transmission Control Protocol (TCP)**. The connectionless one is called the **User Datagram Protocol (UDP).**


The people who develop an application decide which protocol to use (not the user of an application).

- The people pick (and sometimes even design) one or more protocols that they think will meet their application’s needs. These protocols are, in turn, designed to use TCP, UDP, or both.


:rice: TCP

- Most TCP/IP applications use TCP—that’s why the protocol suite is called “TCP/IP” and not “UDP/IP.”
- TCP gets an application’s data from one machine to another reliably and completely. As a result, TCP comes with **communication rules that require both the sending and receiving machines to acknowledge the other’s presence and readiness to send and receive data.**
- This process is referred to as the **TCP three-way handshake** of `SYN`, `SYN-ACK`, and `ACK`.

```txt
server -->   SYN   --> client
server <-- SYN-ACK <-- client
server -->   ACK   --> client
```

- TCP also chops up data into **segments**, gives the segments a **sequence number**, and then **verifies that all sent segments were received**.
  - If a segment goes missing, the **receiving system must request the missing segments.**

A simplified TCP header:

```txt
simplified TCP header:

source | destination | sequence |  ack   |
 port  |    port     |  number  | number |
```

- Notice the source port and the destination port. Port numbers, which range from 1 to 65,535, are **used by systems to determine what application needs the received data.**
- **Each application is assigned a specific port number on which to listen/send.**
- Web servers use port 80 (HTTP) or 443 (HTTPS), for example, whereas port 143 is used to receive e-mail messages from e-mail servers
(IMAP4)

- The client uses the **source port number to remember which client application requested the data.**
- For now, know that the **TCP or UDP header inside an IP packet stores these values.**

The header also contains these fields: Sequence number and acknowledgment number

- These numbers enable the sending and receiving computers to keep track of the various pieces of data flowing back and forth.
  - **Flags**: These individual bits give both sides detailed information about the state of the connection.
  - **Checksum**: The recipient can use the checksum to check the TCP header **for errors such as bits flipped or lost during transmission.**

:rice: UDP

UDP is the “fire and forget” missile of the TCP/IP protocol suite.

```txt
simplified UDP header:

source | destination | sequence |  ack   |
 port  |    port     |  number  | number |
```


- A UDP datagram header **doesn’t possess any of the extra fields TCP segment headers carry** to make sure the data is received intact.

UDP works best **when you have a lot of data that doesn’t need to be perfect or when the systems are so close to each other that the chances of a problem occurring are too small to bother worrying about.**
- A few dropped frames on a Voice over IP call, for example, won’t make much difference in the communication between two people.
- So, there’s a good reason to use UDP: it’s smoking fast compared to TCP.
- Two of the most important networking protocols, **Domain Name System (DNS)** and **Dynamic Host Configuration Protocol (DHCP)**, use UDP.

Note: Data gets chopped up into chunks at the Transport layer when using TCP. The chunks are called segments with TCP. UDP datagrams don’t get chopped up at the Transport layer; they just get a header.


## Application Layer Protocols

TCP/IP applications use TCP/IP protocols to move data back and forth between clients and servers.

- Because every application has different needs, I can’t show you a generic application header.
- Instead, we’ll look at a sample header from a pillar of the World Wide Web—the Hypertext Transfer Protocol (HTTP).

Web servers and Web browsers use HTTP (or, more accurately, HTTPS, a secure version of HTTP wrapped in encryption) to communicate.

You can see this when using Wireshark:

```txt
HTTP/1.1 200 OK
Date: ...
Server: ...
...

<!DOCTYPE html PUBLIC "....
```

A header of response from a Web server containing a resource the client previously requested.

- This header—it’s just text—begins with “HTTP/1.1,” which indicates the version of the HTTP protocol in use.
- The “200 OK” indicates a successful request.
- The first blank line separates the end of the header from the beginning of the response body (which contains the requested Web page)


## IP and Ethernet

TCP/IP supports simple networks and complex networks.

- You can use the protocol suite and a switch to connect a handful of computers in the same place into a local area network (LAN).
- TCP/IP also enables you to interconnect multiple LANs into a wide area network (WAN).

NOTE We say LAN so often in networking that you might assume it has a crystal-clear definition, but there’s a bit of art in it.

- A LAN generally (but not always) belongs to one household or organization.
- A LAN covers a limited place—but that **can mean anything from two devices in an apartment up to thousands of devices on a multi-building school or business campus**.
- A WAN in a basic sense means **a collection of interconnected LANs**. Most authors also add a geographical context to the term, such as “spread out
over a large area."



### How IP addressing works in a LAN.

At the LAN level, every host runs TCP/IP software over Ethernet hardware, creating a situation where **every host has two addresses: an IP address and an Ethernet MAC address** It’s the power behind TCP/IP’s ability to support both LANs and WANs.

- Imagine a situation where one computer, Computer A, wants to send an IP packet to another computer, Computer B, on the LAN.
- To send an IP packet to another computer, the sending computer (Computer A) must insert the IP packet into an Ethernet frame:

```txt
Encapsulation of an IP packet inside an Ethernet frame

                               Simplified IP packet
                             <--------------------------->
Destination | Source | Type | Destination | Source | Data | FCS |
     MAC    |   MAC  |      |     IP      |   IP   |      |     |
<--------------------------------------------------------------->
                 Simplified Ethernet frame

```

- Note that the IP packet is completely encapsulated inside the Ethernet frame.
- Also note that the Ethernet header — the initial portion of the frame - has both a **destination MAC address** and a **source MAC address**, while the IP packet encapsulated in the Ethernet frame has both a source IP address and a destination IP address.

This encapsulation idea works great, but there’s a problem: Computer A knows Computer B’s IP address, but how does Computer A know the MAC address of Computer B?

- To get Computer B’s MAC address, Computer A sends a special query called an ARP request to MAC address `FF-FF-FF-FF-FF-FF`, **the universal MAC address for broadcast.** The **switch forwards the broadcast to every connected node.**
- Computer B responds to the ARP request by sending Computer A an ARP reply through the switch.
- Once Computer A has Computer B’s MAC address, it starts sending unicast Ethernet frames to Computer B through the switch.

IP addresses provide several benefits that MAC addresses alone cannot offer.

- First, IP addresses are not a fixed part of the NIC. They can be changed to suit the needs of the network designer.
- Second, IP addresses group together sets of computers into logical networks, so you can, for example, distinguish one LAN from another.
- Finally, because TCP/IP network equipment understands the IP addressing scheme, computers can communicate with each other across all of the LANs that make up a WAN.

Just as every MAC address must be unique on a network, every IP address must be unique as well.

- For logical addressing to work, **no two computers on the same network may have the same IP address.**
- In a small network running TCP/IP, **every computer has both an IP address and a MAC address**, as you know from earlier in the chapter

- Every operating system has a command-line utility that gives you this information.
  - In Windows, for example, the `ipconfig` command can display the IP and MAC addresses. (The latter requires the `/all` switch.) Run `ipconfig /all` to see the results
  - In macOS, you can run the very similar `ifconfig` command.
  - On Linux systems, you can run either the newer `ip address` or the older `ifconfig` from a terminal to display a system’s IP and MAC addresses. (A lot of distros have removed net-tools, so ifconfig won’t be an option.) Note that most distros enable you to shorten the command switch and will fill in the word “address.” So `ip addr` or even `ip`