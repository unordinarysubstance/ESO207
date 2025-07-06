int RFib (int n)
{
    if (n==0 || n==1) return n;
    else return (RFib(n-1)%2025+RFib(n-2)%2025)%2025;
}

long CleverFib(long n)
{
    long arr[2][2], res[2][2];
    arr[0][0]=1, arr[0][1]=1, arr[1][0]=1, arr[1][1]=0;
    res[0][0]=1, res[0][1]=0, res[1][0]=0, res[1][1]=1;
    long a,b,c,d;
    while (n>0)
    {
        if (n&1)
        {
          a=(res[0][0]*arr[0][0]+res[0][1]*arr[1][0])%2025;
          b=(res[0][0]*arr[0][1]+res[0][1]*arr[1][1])%2025;
          c=(res[1][0]*arr[0][0]+res[1][1]*arr[1][0])%2025;
          d=(res[1][0]*arr[0][1]+res[1][1]*arr[1][1])%2025;
          
          res[0][0]=a;
          res[0][1]=b;
          res[1][0]=c;
          res[1][1]=d;
        }
        
        a=(arr[0][0]*arr[0][0]+arr[0][1]*arr[1][0])%2025;
        b=(arr[0][0]*arr[0][1]+arr[0][1]*arr[1][1])%2025;
        c=(arr[1][0]*arr[0][0]+arr[1][1]*arr[1][0])%2025;
        d=(arr[1][0]*arr[0][1]+arr[1][1]*arr[1][1])%2025;
        
        arr[0][0]=a;
        arr[0][1]=b;
        arr[1][0]=c;
        arr[1][1]=d;
        
        n/=2;
    }
    return res[0][1];
}

int TrivialGCD(int a, int b)
{
    for (int i=(b>a?a:b); i>0;i--)
        if (a%i==0 && b%i==0) return i;
}

long int EuclidGCD(long int a, long int b)
{
    if (b==0) return a;
    return EuclidGCD(b,a%b);
}