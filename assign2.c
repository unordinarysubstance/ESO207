void function1()
{
    int q; scanf("%d", &q);
    int queue[q],maxx[q];
    int l=0, r=0;
    int maxl=0, maxr=0;
    for(int i=0; i<q;i++)
    {
        int type; scanf("%d", &type);
        if (type==1)
        {
            int x; scanf("%d", &x);
            queue[r++]=x;
            while (maxr>maxl && maxx[maxr-1]<x) maxr--;
            maxx[maxr++]=x;
            continue;
        }
        if (type==2)
        {
            if (l<r) if (queue[l]==maxx[maxl]) maxl++;
            l++;
            continue;
        }
        printf("%d\n", maxx[maxl]);
    }
}


void function2()
{
    int n,q; scanf("%d%d", &n,&q);

    int logn=0,dummy=n;
    while (dummy>0)
    {
        dummy/=2;
        logn++;
    }
    
    int arr[n+1];
    for (int i=1;i<=n;i++) scanf("%d", &arr[i]);
    
    int dp[n+1][logn+1];

    for (int i=1; i<=n;i++) dp[i][0]=arr[i];
    
    for (int j=1;(1<<j)<=n;j++)
    { 
        for (int i=1; (i+(1<<j)-1)<=n;i++)
            dp[i][j] = (dp[i][j-1]<dp[i+(1<<(j-1))][j-1]) ?
                        dp[i][j-1]:dp[i+(1<<(j-1))][j-1];
    }

    for (int i=0;i<q;i++)
    {
        int first,last; scanf("%d%d", &first, &last);
        
        int power=0;
        while ((1<<(power+1))<=(last-first+1)) power++;
        
        int min=(dp[first][power]<dp[last-(1<<power)+1][power])?
                  dp[first][power]:dp[last-(1<<power)+1][power];
        
        printf("%d\n", min);
    }
}


void function3()
{
    int n; scanf("%d", &n);
    int mod = 1e9+7;
    int ans[n+1];
    ans[0]=1, ans[1]=1;
    for (int i=2; i<=n;i++)
    {
        ans[i]=0;
        for (int j=0; j<=i-1;j++) ans[i]+=((ans[j]%mod)*(ans[i-1-j]%mod))%mod;
    }
    printf("%d", ans[n]);
}

void function4()
{
    int n,q; scanf("%d %d", &n,&q);
    int a[n];
    int maxx=-1;
    for (int i=0; i<n;i++)
    {
        scanf("%d", &a[i]);
        if(a[i]>maxx) maxx= a[i];
    }
    int stack[n], l[n], r[n];
    int top =-1;
    for (int i=n-1;i>=0;i--)
    {
        while (top>=0 && a[stack[top]]>=a[i]) top--;
        if(top<0) r[i] = n;
        else r[i] = stack[top];
        top++;
        stack[top] = i;
    }
    
    top = -1;
    for (int i=0;i<n;i++)
    {
        while (top >= 0 && a[stack[top]]>=a[i]) top--;
        if(top < 0) l[i]=-1;
        else l[i] = stack[top];
        top++;
        stack[top] = i;
    }

    int ans[maxx+1];
    for (int i=0; i<=maxx;i++) ans[i]=0;

    for (int i=0;i<n;i++)
    {
        int len = r[i]-l[i]-1;
        if(len>ans[a[i]]) ans[a[i]] = len;
    }

    for (int i=0;i<q;i++)
    {
        int k; scanf("%d", &k);
        if(k>maxx) printf("0\n");
        else printf("%d\n", ans[k]);
    }
}


