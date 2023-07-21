# Webserver

Implementation of simple webserver handling basic HTTP GET requests.
Displays webpages from the specified directory.

## Usage:
Configure your `/etc/hosts` file so it contains the following:
```
127.0.0.1   domain_name
```

With that opening the address `http://domain_name:port/page.html` in a web browser should display the contents of the page directory `/domain_name/page.html`.

And then run:
```bash
$ ./server <port> <directory>
```

#### Example
In our case `/etc/hosts` should contain:

```
127.0.0.1   localhost
127.0.1.1   virbian
127.0.1.1   virtual-domain.example.com
```
With that, references to `virbian` and `virtual-domain.example.com` will be directed to the local computer.

```bash
$ ./server 8888 webpages
```
Where `webpages` is directory that contains `virbian` and `virbian-domain.example.com`.
So using `http://virbian:8888/` server directs us to `http://virbian/index.html`.
