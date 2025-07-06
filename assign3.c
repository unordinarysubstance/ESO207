#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct Node { ll value; struct Node* left; struct Node* right; } node;
typedef struct { int pv, p1, p2, p3; ll k1, k2; } input_23;

typedef struct node_23 { ll key1, key2; struct node_23 *left; struct node_23 *middle; 
                struct node_23 *right; struct node_23 *parent; } node_23;

typedef struct { int *a; int front, back, size; } queue;
typedef struct { ll left, right, height; } Building;
typedef struct { ll x, height; } skyline_point;

int compare(const void *a, const void *b) { return (*(int*)a - *(int*)b); }

node* new_node(ll val) 
{
    node* new_node = (node*) malloc(sizeof(node));
    new_node->value = val;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

node_23* create_node_23(ll key1, ll key2) 
{
    node_23* new_node = (node_23*)malloc(sizeof(node_23));
    new_node->key1 = key1;
    new_node->key2 = key2;
    new_node->left = NULL;
    new_node->middle = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;
    return new_node;
}

node* insert_bst(ll val, node* root)
{
    if (!root) return new_node(val);
    if (val < root->value) root->left = insert_bst(val, root->left);
    else if (val > root->value) root->right = insert_bst(val, root->right);
    return root;
}

int height(node* root) 
{
    if (!root) return 0;
    int left = height(root->left);
    int right = height(root->right);
    return 1 + (left > right ? left : right);
}

int search_23(node_23* root, ll x) 
{
    if (root == NULL) return 0;
    if (root->key1 == x || (root->key2 != -1 && root->key2 == x)) return 1;
    if (x < root->key1) return search_23(root->left, x);
    else if (root->key2 == -1 || x < root->key2) return search_23(root->middle, x);
    else return search_23(root->right, x);
}

ll find_min_23(node_23* node) 
{
    if (node == NULL) return -1;
    while (node->left != NULL)
        node = node->left;
    return node->key1;
}


node_23* search_node_23(node_23* root, ll x, int *key_index) {
    if (root == NULL) return NULL;
    if (root->key1 == x) { *key_index = 1; return root; }
    if (root->key2 != -1 && root->key2 == x) { *key_index = 2; return root; }
    if (x < root->key1) return search_node_23(root->left, x, key_index);
    else if (root->key2 == -1 || x < root->key2) return search_node_23(root->middle, x, key_index);
    else return search_node_23(root->right, x, key_index);
}


ll find_successor_23(node_23* root, ll x) 
{
    int pos;
    node_23 *node = search_node_23(root, x, &pos);
    if (!node) return 0;  

    
    if (pos == 1) 
    {
        if (node->middle != NULL)
            return find_min_23(node->middle);
        
        if (node->key2 != -1)
            return node->key2;
    }
   
    if (pos == 2 && node->right != NULL) return find_min_23(node->right);
    
    node_23 *curr = node;
    while (curr->parent != NULL) 
    {
        node_23 *p = curr->parent;
        
        if (p->left == curr) 
        {
            if (p->key1 > x)
                return p->key1;
            
        }
        
        else if (p->middle == curr) 
        {
            if (p->key2 != -1 && p->key2 > x)
                return p->key2;
        }
        
        curr = p;
    }
    return 0; 
}

node_23** build_tree_23(input_23* input, int n) 
{
    node_23** nodes = (node_23**)malloc(n * sizeof(node_23*));
    for (int i = 0; i < n; i++) nodes[i] = create_node_23(input[i].k1, input[i].k2);
    for (int i = 0; i < n; i++) 
    {
        if (input[i].p1 != -1) 
        {
            nodes[i]->left = nodes[input[i].p1];
            nodes[input[i].p1]->parent = nodes[i];
        }
        if (input[i].p2 != -1) 
        {
            nodes[i]->middle = nodes[input[i].p2];
            nodes[input[i].p2]->parent = nodes[i];
        }
        if (input[i].p3 != -1) 
        {
            nodes[i]->right = nodes[input[i].p3];
            nodes[input[i].p3]->parent = nodes[i];
        }
    }
    return nodes;
}

int is_empty(queue *q) { return q->front == q->back; }
void enqueue(queue *q, int val) { q->a[q->back++] = val; }
int dequeue(queue *q) { return q->a[q->front++]; }

void bfs(int start, int n, int **graph, int *sizes, int *dist) 
{
    queue *q = (queue*)malloc(sizeof(queue));
    q->a = (int*)malloc(n * sizeof(int));
    q->front = q->back = 0;
    q->size = n;

    for (int i = 0; i < n; i++) dist[i] = -1;
    dist[start] = 0;
    enqueue(q, start);

    while (!is_empty(q)) 
    {
        int out = dequeue(q);
        for (int i = 0; i < sizes[out]; i++) 
        {
            int f = graph[out][i];
            if (dist[f] == -1) 
            { 
                dist[f] = dist[out] + 1;
                enqueue(q, f);
            }
        }
    }
}

skyline_point* merge(skyline_point* left, int left_size, skyline_point* right, int right_size, int* return_size) 
{
    skyline_point* result = (skyline_point*)malloc((left_size + right_size) * sizeof(skyline_point));
    int i = 0, j = 0, k = 0;
    ll left_height = 0, right_height = 0;
    
    while (i < left_size && j < right_size) 
    {
        ll x;
        if (left[i].x < right[j].x) 
        {
            x = left[i].x;
            left_height = left[i].height;
            i++;
        } 
        else if (left[i].x > right[j].x) 
        {
            x = right[j].x;
            right_height = right[j].height;
            j++;
        } 
        else 
        {
            x = left[i].x;
            left_height = left[i].height;
            right_height = right[j].height;
            i++;
            j++;
        }
        ll max_height = (left_height > right_height) ? left_height : right_height;
        if (k == 0 || result[k - 1].height != max_height)
            result[k++] = (skyline_point){x, max_height};
    }
    
    while (i < left_size) 
    {
        if (k == 0 || result[k - 1].height != left[i].height) result[k++] = left[i];
        i++;
    }
    
    while (j < right_size) 
    {
        if (k == 0 || result[k - 1].height != right[j].height) result[k++] = right[j];
        j++;
    }
    
    *return_size = k;
    return result;
}

skyline_point* divide_and_conquer(Building* buildings, int first, int last, int* return_size) 
{
    if (first == last) 
    {
        skyline_point* ans = (skyline_point*)malloc(2 * sizeof(skyline_point));
        ans[0] = (skyline_point){buildings[first].left, buildings[first].height};
        ans[1] = (skyline_point){buildings[first].right, 0LL};
        *return_size = 2;
        return ans;
    }
    
    int mid = first + (last - first) / 2;
    int left_size, right_size;
    
    skyline_point* left = divide_and_conquer(buildings, first, mid, &left_size);
    skyline_point* right = divide_and_conquer(buildings, mid + 1, last, &right_size);
    
    return merge(left, left_size, right, right_size, return_size);
}

void function1() 
{
    int n; 
    scanf("%d", &n);
    node* root = NULL;
    for (int i = 0; i < n; i++) 
    {
        ll x; 
        scanf("%lld", &x);
        root = insert_bst(x, root);
    }
    printf("%d", height(root));
}

void function2() 
{
    int n, q; scanf("%d %d", &n, &q);
    
    input_23* input = (input_23*)malloc(n * sizeof(input_23));
    for (int i = 0; i < n; i++) 
    {
        scanf("%d %d %lld %d %lld %d", 
              &input[i].pv, &input[i].p1, &input[i].k1, 
              &input[i].p2, &input[i].k2, &input[i].p3);
    }
    
    node_23** nodes = build_tree_23(input, n);
    node_23* root = nodes[0];
    
    for (int i = 0; i < q; i++) 
    {
        int query;
        ll x;
        scanf("%d %lld", &query, &x);
        if (query == 1)
            printf("%d\n", search_23(root, x));
        else printf("%lld\n", find_successor_23(root, x));
    }
}

void function3() {
    int n, e, m;
    scanf("%d %d %d", &n, &e, &m);

    int edges[e][2];
    for (int i = 0; i < e; i++) scanf("%d %d", &edges[i][0], &edges[i][1]);

    int o, h; scanf("%d %d", &o, &h);

    int markets[m];
    for (int i = 0; i < m; i++) scanf("%d", &markets[i]);
    
    int **graph = (int**)malloc(n * sizeof(int*));
    int *sizes = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < e; i++) 
    {
        sizes[edges[i][0]]++;
        sizes[edges[i][1]]++;
    }

    for (int i = 0; i < n; i++) 
    {
        graph[i] = (int*)malloc(sizes[i] * sizeof(int));
        sizes[i] = 0;
    }

    for (int i = 0; i < e; i++) 
    {
        int u = edges[i][0], v = edges[i][1];
        graph[u][sizes[u]++] = v;
        graph[v][sizes[v]++] = u;
    }

    int *dist1 = (int*)malloc(n * sizeof(int));
    int *dist2 = (int*)malloc(n * sizeof(int));

    bfs(o, n, graph, sizes, dist1);
    bfs(h, n, graph, sizes, dist2);

    qsort(markets, m, sizeof(int), compare);

    int min = 1e9, count = 0;
    int ans[m];

    for (int i = 0; i < m; i++) 
    {
        int total = dist1[markets[i]] + dist2[markets[i]];
        if (total < min) 
        {
            min = total;
            count = 0;
            ans[count++] = markets[i];
        } 
        else if (total == min) ans[count++] = markets[i];
    }

    printf("%d %d\n", min, count);
    for (int i = 0; i < count; i++) printf("%d ", ans[i]);
}

void function4() 
{
    int n; 
    scanf("%d", &n);
    Building buildings[n];
    
    for (int i = 0; i < n; i++)
        scanf("%lld %lld %lld", &buildings[i].left, &buildings[i].right, &buildings[i].height);

    int skyline_size;
    skyline_point* skyline = divide_and_conquer(buildings, 0, n - 1, &skyline_size);

    for (int i = 0; i < skyline_size; i++) 
        printf("%lld %lld ", skyline[i].x, skyline[i].height);
}
