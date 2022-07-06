#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>

#define dataType long long
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

vector<dataType> getPrefix(vector<dataType> &A){
    vector<dataType> p;
    dataType sum = 0;
    for (auto item : A){
        p.push_back(item + sum);
        sum+=item;
    }
    return p;
}

vector<dataType> getSecondaryPrefix(vector<dataType> &A){
    vector<dataType> p;
    dataType sum = 0, pos = 1;
    for (auto item : A){
        p.push_back((item * pos) + sum);
        sum+=item*pos++;
    }
    return p;
}

long S(vector<dataType> &p,dataType l, dataType r){
    if(l==0) return p[r];
    return p[r] - p[l-1];
}

long S2(vector<dataType> &p2,dataType l, dataType r){
    if(l==0) return p2[r];
    return p2[r] - p2[l-1];
}

long getCost(vector<dataType> &p, vector<dataType> &p2, dataType i, dataType j){
    dataType m = (i+j)/2;
    return S2(p2,i,m) - (i+1)*S(p,i,m) + (j+1)*S(p,m+1,j) - S2(p2,m+1,j);
}

long minPartition(Matrix &M,dataType n,vector<dataType> A,dataType k){
    //get Sum of prefix 
    vector<dataType> p = getPrefix(A);
    vector<dataType> p2 = getSecondaryPrefix(A);

    for (dataType i = 1; i <= n; i++){
        //calculo de sumatoria 
        M[i - 1][0] = getCost(p,p2,0,i-1);
    }

    for (dataType j = 1; j < k;j++){
        for (dataType i = 0; i < n; i++){
            M[i][j] = LLONG_MAX;
            for (dataType l = 0; l <= i; l++){
                dataType cost = M[l][j-1] + getCost(p,p2,l,i);
                M[i][j] = min(cost, M[i][j]); 
            }   
        }
    }
    return M[n-1][k-1]; 
}

int main(){
    dataType k;
    dataType n;
    ofstream myfile;
    myfile.open ("output.txt");
    cin >> n;
    vector<dataType> A(n);
    for(dataType i = 0; i < n; i++) cin >> A[i];

    if (n == 1) {
        cout<<0<<" ";
        myfile<<0<<" ";
    }
    else{
        k = n - 1;
        Matrix matrix (n,vector<dataType>(k));
        dataType mn = minPartition(matrix,n,A,k);

        for(dataType j = 1; j < n; j++){
            cout << matrix[n-1][j-1] << " ";
            myfile << matrix[n-1][j-1] << " ";
        }

        // cout << "\n";
        // myfile << "\n";
        //print(matrix);
    }
    return 0;

}