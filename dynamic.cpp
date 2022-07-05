#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

#define dataType long
#define Matrix vector<vector<dataType>>

using namespace std;

void print(Matrix matrix){
    for (auto row : matrix){
        for (auto col : row){
            cout << col << " ";
        }
        cout << endl;
    }
}

vector<long> getPrefix(vector<long> &A){
    vector<long> p;
    long sum = 0;
    for (auto item : A){
        p.push_back(item + sum);
        sum+=item;
    }
    return p;
}

vector<long> getSecondaryPrefix(vector<long> &A){
    vector<long> p;
    long sum = 0, pos =1;
    for (auto item : A){
        p.push_back((item * pos) + sum);
        sum+=item*pos++;
    }
    return p;
}

long S(vector<long> &p,long l, long r){
    return p[r] - p[l-1];
}

long S2(vector<long> &p2,long l, long r){
    return p2[r] - p2[l-1];
}

long minPartition(Matrix &M,long n,vector<long> A,long k){
    //get Sum of prefix 
    vector<long> p = getPrefix(A);
    vector<long> p2 = getSecondaryPrefix(A);

    for (long i = 1; i <= n; i++){
        long sum = 0;
        //calculo de sumatoria
        for (long p = 1; p <= i; p++){
            sum += min(p - 1, i - p) * A[p - 1];
        }
        M[i - 1][0] = sum;        
    }

    for (long i = 1; i < n; i++){
        for (long j = 1; j < k;j++){
            M[i][j] = INT_MAX;
            for (long l = j; l <= i; l++){
                long sum = 0;
                long m = (j+n)/2;
                long cost = M[l][j - 1] + (S2(p2,l,m) - S(p,l,m)+ S2(p2,m+1,i) - S(p,m+1,i));
                M[i][j] = min(cost, M[i][j]); 
            }   
        }
    }

    return M[n-1][k-1]; 
}

int main(){
    vector<long> A = {10,20,30,50,60,70,80,90};
    long k  = 3;
    long n = 8;
    Matrix matrix (n,vector<long>(k));

    cout<<"resultao: "<<minPartition(matrix,n,A,k)<<endl;
    print(matrix);
    return 0;
}