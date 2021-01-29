MAX_SIZE=1000001

isprime=[True]*MAX_SIZE
prime=[]
SPF=[None]*(MAX_SIZE)

def seive(N):
    isprime[0]=isprime[1]=False
    
    for i in range(2,N):
        if(isprime[i]==True):
            prime.append(i)
            SPF[i]=i
        j=0
        while(j<len(prime) and i*prime[j]<N and prime[j]<=SPF[i]):
            isprime[i*prime[j]]=False
            SPF[i*prime[j]]=prime[j]
            j+=1
seive(MAX_SIZE)

T=int(input())
for i in range(T):
    N=int(input())
    ans=0
    j=0
    while(prime[j]<=N):
        j+=1
    for k in range(1,j-1):
            if((prime[k]+2) in prime[:j]):
                ans+=1
    print(ans)