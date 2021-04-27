Compilation:

1) gcc server.c -lssl -lcrypto -o server.out
2) gcc client.c -lssl -lcrypto -o client.out

Run:

1) ./server.out 8082
2) ./client.out 127.0.0.1 8082 private_key_1.pem public_key_2.pem
3) ./client.out 127.0.0.1 8082 private_key_2.pem public_key_1.pem

Usage:

1) send data from any client
2) enter exit to exit both clients