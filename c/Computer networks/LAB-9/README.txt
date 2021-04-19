1) gcc encrypt.c -lcrypto -o encrypt.out
2) gcc decrypt.c -lcrypto -o decrypt.out
3) ./encrypt.out public.pem data.txt encrypted
4) ./decrypt.out private.pem encrypted output.txt