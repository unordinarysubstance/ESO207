#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct 
{
    int u, v;
} bridge;

int compare(const void *a, const void *b) 
{
    bridge *b1 = (bridge *)a;
    bridge *b2 = (bridge *)b;
    if (b1->u != b2->u) return b1->u - b2->u;
    return b1->v - b2->v;
}

void add_edge(int **adj, int *cap, int *size, int u, int v) 
{
    if (size[u] >= cap[u]) 
    {
        cap[u] = cap[u] == 0 ? 2 : cap[u] * 2;
        adj[u] = (int*)realloc(adj[u], cap[u] * sizeof(int));
    }
    adj[u][size[u]++] = v;
}

void dfs(int v, int parent, int **adj, int *adj_size, int *visited, int *tin, int *low, int *timer, bridge *bridges, int *bridge_count) 
{
    visited[v] = 1;
    tin[v] = low[v] = (*timer)++;

    for (int i = 0; i < adj_size[v]; i++) 
    {
        int to = adj[v][i];
        if (to == parent) continue;

        if (visited[to]) 
        {
            if (low[v] > tin[to]) low[v] = tin[to];
        } 
        else 
        {
            dfs(to, v, adj, adj_size, visited, tin, low, timer, bridges, bridge_count);
            if (low[v] > low[to]) low[v] = low[to];
            if (low[to] > tin[v]) 
            {
                bridges[*bridge_count].u = v < to ? v : to;
                bridges[*bridge_count].v = v > to ? v : to;
                (*bridge_count)++;
            }
        }
    }
}

void function1()
{
    //Write code for Q1
    int t; scanf("%d", &t);
    while(t--)
    {
        int n; scanf("%d", &n);
        ll  arr[n];
        ll  cand1=-1, cand2=-1;
        int count1=0, count2=0;
        
        for (int i=0; i<n;i++)
        {
            scanf("%lld", &arr[i]);
            if (arr[i] == cand1) count1++;
            else if (arr[i] == cand2) count2++;
            else if (count1 == 0) 
            {
                cand1 = arr[i];
                count1 = 1;
            } 
            else if (count2 == 0) 
            {
                cand2 = arr[i];
                count2 = 1;
            } 
            else 
            {
                count1--;
                count2--;
            }
        }

        count1 = 0;
        count2 = 0;
        for (int i = 0; i < n; i++) 
        {
            if (arr[i] == cand1) count1++;
            else if (arr[i] == cand2) count2++;
        }
          
        ll  win[2];
        int count=0;
        if (count1 > n/3) win[count++] = cand1;
        if (count2 > n/3) win[count++] = cand2;
        if (count < 2) printf("NO\n");
        else
        {
            printf("YES\n");
            if (win[0]<win[1]) printf("%lld %lld\n", win[0], win[1]);
            else printf("%lld %lld\n", win[1], win[0]);
        }
    }
}

void function2()
{
    //Write code for Q2
    int n, m; scanf("%d %d", &n, &m);

    int **adj = (int **)calloc(n, sizeof(int *));
    int *adj_size = (int *)calloc(n, sizeof(int));
    int *adj_cap = (int *)calloc(n, sizeof(int));

    
    for (int i = 0; i < m; i++) 
    {
        int u, v; scanf("%d %d", &u, &v);
        add_edge(adj, adj_cap, adj_size, u, v);
        add_edge(adj, adj_cap, adj_size, v, u);
    }

    int *visited = (int *)calloc(n, sizeof(int));
    int *tin = (int *)malloc(n * sizeof(int));
    int *low = (int *)malloc(n * sizeof(int));
    bridge *bridges = (bridge *)malloc(m * sizeof(bridge));
    int bridge_count = 0;
    int timer = 0;

    for (int i = 0; i < n; i++) 
    {
        if (!visited[i]) 
            dfs(i, -1, adj, adj_size, visited, tin, low, &timer, bridges, &bridge_count);
    }

    if (bridge_count == 0) printf("-1\n");
    else 
    {
        qsort(bridges, bridge_count, sizeof(bridge), compare);
        for (int i = 0; i < bridge_count; i++) 
            printf("%d %d\n", bridges[i].u, bridges[i].v);
    }

}

ll* merge_two(ll* a, int n, ll* b, int m) 
{
    ll* result = (ll*)malloc((n + m) * sizeof(ll));
    int i = 0, j = 0, k = 0;

    while (i < n && j < m) 
    {
        if (a[i] <= b[j]) result[k++] = a[i++];
        else result[k++] = b[j++];
    }
    while (i < n) result[k++] = a[i++];
    while (j < m) result[k++] = b[j++];

    return result;
}


void function3()
{
    //Write code for Q3
    int k; scanf("%d", &k);

    ll** arrays = (ll**)malloc(k * sizeof(ll*));
    int* sizes = (int*)malloc(k * sizeof(int));

    for (int i = 0; i < k; i++) 
    {
        scanf("%d", &sizes[i]);
        arrays[i] = (ll*)malloc(sizes[i] * sizeof(ll));
        for (int j = 0; j < sizes[i]; j++) scanf("%lld", &arrays[i][j]);
    }

    while (k > 1) 
     {
        int new_k = (k + 1) / 2;
        for (int i = 0; i < k / 2; i++) 
        {
            ll* merged = merge_two(arrays[2*i], sizes[2*i], arrays[2*i + 1], sizes[2*i + 1]);
            arrays[i] = merged;
            sizes[i] = sizes[2*i] + sizes[2*i + 1];
        }
        if (k % 2 == 1) 
        {
            arrays[k / 2] = arrays[k - 1];
            sizes[k / 2] = sizes[k - 1];
        }
        k = new_k;
    }

    for (int i = 0; i < sizes[0]; i++) printf("%lld ", arrays[0][i]);
    
}
