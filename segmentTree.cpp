//
//  main.cpp
//  SegmentTree
//
//  Created by Amit Sharma on 02/11/19.
//  Copyright © 2019 McGreen Lts. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;
const int N = 100005;
int a[N];
struct segmenttree{
    vector<int>st;
    void init(int n){
        st.resize(4*n,INT_MIN);
    }
    void build(int start, int end, int index){
        if(start == end){
            st[index]=a[start];
            return;
        }
        int mid = (start+end)/2;
        build(start, mid,index*2+1);
        build(mid+1, end,index*2+2);
        st[index]=max(st[index*2+1],st[index*2+2]);
    }
    void print(){
        for(auto x:st){
            if(x == INT_MIN ){
                cout<<" * ";
            }else{
                cout<<x<<" ";
            }
        }
    }
    void update(int start , int end, int i, int val, int index){
        if(start==end){
            a[i]+=val;
            st[index]+=val;
            return;
        }
        int mid = (start+end)/2;
        if(i<=mid){
            update(start, mid, i, val, index*2+1);
        }else{
            update(mid+1, end, i, val, index*2+2);
        }
        st[index]=max(st[index*2+1],st[index*2+2]);
        
    }
    void rangeUpdate(int start, int end ,int l ,int r, int val, int index){
        //no overlap
        if(start>r || l>end){
            return;
        }
        //leaf node
        if(start == end){
            st[index]+=val;
            return;
        }
             int mid = (start+end)/2;
       
            rangeUpdate(start, mid, l,r, val, index*2+1);
        
            rangeUpdate(mid+1, end, l,r, val, index*2+2);
        
           st[index]=max(st[index*2+1],st[index*2+2]);
        
    }
    
    int query(int start, int end, int l, int r, int node) {
        if (start > r || end < l || start > end) return INT_MIN;
        if (start >= l && end <= r) return st[node];
        int mid = (start + end) / 2;
        int q1 = query(start, mid, l, r, node * 2 + 1);//query left
        int q2 = query(mid + 1, end, l, r, node * 2 + 2);//query right
        return max(q1, q2);
    }
    
    
};

int main(int argc, const char * argv[]) {
    segmenttree tree;
    int i,t, j, k, n, m, ans = 0, cnt = 0, sum = 0;
    cin >> n;
    for (i = 0; i < n; i++) {
        cin >> a[i];
    }
    tree.init(n);
    tree.build(0, n - 1, 0);
      tree.print();
    cout<<"\nUpdate information\n"<<endl;
    cout<<"Index and Value\n\n"<<endl;
    int v;
    cin>>j>>v;
    tree.update(0, n-1,  j, v, 0);
    tree.print();
    
    tree.rangeUpdate(0, n-1,  0,n-1, 100, 0);
    tree.print();
        
        
        cout<<"\n\n\n :: QUERY RESULT::\n";
        int l,r;
        cin>>l>>r;
        cout<<tree.query(0, n-1, l, r, 0);
        cout<<"\n\n\n";
    return 0;
}
