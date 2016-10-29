try:
    import usocket as socket
except:
    import socket


# from machine import Pin

# p0 = Pin(2, Pin.OUT)

request_method = ""
path = ""
request_version = ""


def parse_request(text):
        if text != '':
            request_line = text.split("\r\n")[0]
            request_line = request_line.split()
            print(request_line)
            # Break down the request line into components
            (request_method,  # GET
             path,            # /hello
             request_version  # HTTP/1.1
             ) = request_line
            print("Method:", request_method)
            print("Path:", path)
            print("Version:", request_version)
            if request_method == "POST":
                pass
            if request_method == "GET":
                if "?" in path:
                    filename, values = path.strip('/').split('?')
                    if values[0] == 'led=on':
                        # p0.low()
                        pass
                    else:
                        # p0.high()
                        pass
                else:
                    filename = path.strip('/')
                if filename == '':
                    filename = 'index.html'
                fileext = filename.split('.')[1]
                if fileext == 'html' or \
                       fileext == 'css' or \
                       fileext == 'js':
                    f = open(filename, 'r')
                    content = f.read()
                    f.close()
                    header = ''
                    header += 'HTTP/1.1 200 OK\r\n'
                    # html += 'Date: ' + time.localtime(time.time())
                    header += 'Content-Type: text/' + fileext + '\r\n'
                    header += 'Content-Length: ' + str(len(content)) + '\r\n'
                    header += '\r\n'
                    return header, content
                if fileext == 'png' or \
                        fileext == 'jpg' or \
                        fileext == 'gif' or \
                        fileext == 'png' or \
                        fileext == 'ico':
                    f = open(filename, 'rb')
                    content = f.read()
                    f.close()
                    header = ''
                    header += 'HTTP/1.1 200 OK\r\n'
                    # header += 'Date: ' + time.localtime(time.time())
                    header += 'Content-Type: image/' + fileext + '\r\n'
                    header += 'Content-Length: ' + str(len(content)) + '\r\n'
                    header += '\r\n'
                    return header, content


def main(use_stream=False):
    s = socket.socket()

    # Binding to all interfaces - server will be accessible to other hosts!
    ai = socket.getaddrinfo("0.0.0.0", 8080)
    print("Bind address info:", ai)
    addr = ai[0][-1]

    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind(addr)
    s.listen(5)
    print("Listening, connect your browser to http://<this_host>:8080/")

    while True:
        res = s.accept()
        client_s = res[0]
        client_addr = res[1]
        if use_stream:
            # MicroPython socket objects support stream (aka file) interface
            # directly.
            print (client_addr)
            header, content = parse_request(client_s.recv(4096).decode('utf-8'))
            if header != '':
                client_s.write(header)
                totalsent = 0
                while totalsent < len(content):
                    sent = client_s.write(content)
                    totalsent += len(sent)
        else:
            header, content = parse_request(client_s.recv(4096).decode('utf-8'))
            print('length of content:' + str(len(content)))
            print (client_addr)
            if header != '':
                client_s.send(header)
                client_s.send(content)
        client_s.close()

main()
