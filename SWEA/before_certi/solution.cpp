 // memory Pool
 struct Node{
     int a, b, c, d, e;
 }poolNode[10000];
 int nodeCnt;
Node* alloc_n(){
    return &poolNode[nodeCnt++];
}

// Trie
struct Trie{
    bool finish;
    Trie* next[26];
}poolTrie[10000];
int trieCnt;
Trie* root; 

void init(){
    root = &poolTrie[trieCnt++];
}

// sort 

int arr_2[10000];
void merge_s(int l, int r, int arr[]){
    if(l < r){
        int mid = (l + r) / 2;
        merge_s(l, mid, arr);
        merge_s(mid + 1, r, arr);

        int x = l, y = mid, z = mid;

        while(x < )
    }
}