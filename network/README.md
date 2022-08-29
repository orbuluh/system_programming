# [What's the Difference Between `localhost` and `127.0.0.1`?](https://phoenixnap.com/kb/localhost-vs-127-0-0-1)

- `localhost` is an alias used to refer to IP addresses **reserved for loopback.**
  - While IPv4 uses the last block of class A addresses (from `127.0.0.1` to `127.255.255`)
  - IPv6 reserves the first (`0:0:0:0:0:0:0:1` - or `::1`, in short) as its loopback address.
- e.g. `localhost` does not refer exclusively to `127.0.0.1` but to **a whole range of IP addresses reserved for loopback**
- IPv6 only systems do not respond to such requests since their localhost is linked to the address `::1` - so you cannot always use `127.0.0.1` for loopback.
- configuring the host file can easily link localhost with a different IP address.
  - mac: `/private/etc/hosts`
  - it is not recommended as it may crash local applications that rely on the localhost connection and break system functionality.
- Another significant difference between `localhost` and `127.0.0.1` is how the request is sent.
  - The request does not go through the network card when pinging the loopback address with the `localhost`.
  - On the other hand, running `127.0.0.1` does pass through the network card, which may be affected by firewall settings and configurations.


# [How linux kernel does the source port allocation](https://idea.popcount.org/2014-04-03-bind-before-connect/)
- To establish a connection BSD API requires two steps: first you need to create a socket, then call connect() on it
![wiki TCP socket flow diagram](https://upload.wikimedia.org/wikipedia/commons/a/a1/InternetSocketBasicDiagram_zhtw.png)
- When a connection is made the operating system needs to select an unused source port number. Linux selects **a port from an ephemeral port range**, which by default is a set to range from 32768 to 61000:
- On Linux the ephemeral port range is a global resource1, it's not a specific setting local to an IP address.
- ephemeral port is selected by:
```markdown
- we start with a hint port number and increase it until we find a source port that is either:
  - Completely unused.
  - Used by some connections but it's ok for it to be reused: it passes the `check_established` check.
```
- By default there are 28232 ports in the ephemeral range, so the first condition could be matched at most that number of times.
- If you have more than 28k connections Linux will need to find a port that passes check_established check.
  - **It's okay to reuse a port if no connection already exists between the same source and destination endpoints.**
- With multiple destination addresses it's possible to have pretty much unlimited number of connections. But establishing more than 28k concurrent connections to a single {destination IP, destination port} pair will fail.
- If you really want to establish even more than 64k connections to a single destination address **you'll have to use more than one source IP address.**
- It is possible to ask the kernel to select a specific source IP and port by calling `bind()` before calling `connect()`:
- This method is fairly well known, but there's a catch. **Bind is usually called for listening sockets so the kernel needs to make sure that the source address is not shared with anyone else.**
  - It's a problem. When using this technique in this form it's impossible to establish more than 64k (ephemeral port range) outgoing connections in total. 
  - After that the attempt to call `bind()` will fail with an `EADDRINUSE` error - all the source ports will be busy.
- To work around this we need to understand two flags that affect the kernel port allocation behavior: `SO_REUSEADDR` and `SO_REUSEPORT`.

## `SO_REUSEADDR`
- By setting `SO_REUSEADDR` **user informs the kernel of an intention to share the bound port with anyone else**, but o**nly if it doesn't cause a conflict on the protocol layer**. There are at least three situations when this flag is useful:
  - Normally after binding to a port and stopping a server it's necessary to wait for a socket to time out before another server can bind to the same port.With `SO_REUSEADDR` set it's possible to rebind immediately, even if the socket is in a `TIME_WAIT` state.
  - When one server binds to `INADDR_ANY`, say `0.0.0.0:1234`, it's impossible to have another server binding to a specific address like `192.168.1.21:1234`. With `SO_REUSEADDR` flag this behavior is allowed.
  - When using the bind before connect trick **only a single connection can use a single outgoing source port**. With this flag, **it's possible for many connections to reuse the same source port**, given that they connect to different destination addresses.

## `SO_REUSEPORT`
- SO_REUSEPORT is poorly documented. It was introduced for UDP multicast sockets.
- Initially, **only a single server was able to use a particular port to listen to a multicast group**.
- This flag allowed **different sockets to bind to exactly the same IP and port**, and **receive datagrams for selected multicast groups.**
- More generally speaking, setting `SO_REUSEPORT` informs a kernel of **an intention to share a particular bound port between many processes,** but only for a single user.
- For multicast datagrams are distributed based on multicast groups, for usual UDP datagrams are distributed in round-robin way.
- For a long time this flag wasn't available for TCP sockets, but recently Google submitted patches that fix it and distribute incoming connections in round-robin way between listening sockets.

## Port allocation
- With 0 passed to bind the kernel does a source port allocation.
- This type of port allocation works differently than when using straight connect()
- Basically, the kernel doesn't use hint variable as previously, instead it selects a random port from the ephemeral range and increases it until it finds a conflict-free port.
  - What is a "conflict-free" very much depends on the SO_REUSEADDR and SO_REUSEPORT flags.
- There's another catch: when we call `bind()` the kernel knows **only the source address we're asking for**. We'll **inform the kernel of a destination address only when we call `connect()` later**.
- This may lead to problems as kernel may reuse source port already used by another connection possibly to the same destination we want to use.
- In such case `connect()` will fail with `EADDRNOTAVAIL` error.

- If you want to establish more than 64k (ephemeral port range) connections to a single destination, you need to use all the tricks:
  - Tweak kernel parameters to increase ephemeral port range.
  - Manually specify many source IP addresses by using `bind` before `connect`.
  - Set SO_REUSEADDR flag on outging connections.
  - Check bind() for `EADDRINUSE` errors, in case we run out of available ports.
  - Check connect() for `EADDRNOTAVAIL` errors in case there is a connection conflict and retry if necessary.