import re
T=int(input())
for i in range(T):
    password = input()
    flag=0


    if(len(password)<10):
        flag=-1
    elif not(re.search("[a-z]",password)):
        flag=-1
    elif not(re.search("[A-Z]",password[1:-1])):
        flag=-1
    elif not(re.search("[0-9]",password[1:-1])):
        flag=-1
    elif not(re.search("[@#%&?]",password[1:-1])):
        flag=-1
    else:
        flag=0

    if flag==0:
        print("YES")
    else:
        print("NO")
    