// Created by: Gerges-Wageh [20/6/2020 | 5:00AM]
// Simple program to multiply Big integers (thousands of digits) which can`t fit into standard data types
// Time Complexity: O(n^log2(3)) almost O(n^1.58)

#include <iostream>
#include <string>
#include <math.h>
#include <stack>

using namespace std;

int* Multiply(int A[], int B[], int n, int a, int b){
    int* R = new int[2*n-1]{0};
    if(n==1){
        R[0]=A[a]*B[b];
        return R;
    }
    int* E1D1 = Multiply(A,B,n/2,a,b);
    int* E0D0 = Multiply(A,B,n/2,a+(n/2),b+(n/2));

    int x[n/2];
    int y[n/2];
    int j=a;
    for(int i=0;i<n/2;i++){
        x[i]=A[j]+A[j+n/2];
        y[i]=B[j]+B[j+n/2];
        j++;
    }
    int* c = Multiply(x,y,n/2,0,0);
    for(int i=0;i<n-1;i++){
        c[i]-=(E1D1[i]+E0D0[i]);
    }
    for(int i=0;i<n-1;i++){
        R[i]=E1D1[i];
        R[i+n]=E0D0[i];
    }
    for(int i=n/2;i<n+(n/2)-1;i++)
        R[i]+=c[i-n/2];

    delete [] E0D0;
    delete [] E1D1;
    delete [] c;

    return R;
}

string BigIntegerMult(string a, string b){
    int n = pow(2,ceil(log2(max(a.size(),b.size()))));
    int* A = new int[n]{0};
    int* B = new int[n]{0};
    int index = n-1;
    string R,Ans="0";
    stack<string> T;
    for(int i=a.size()-1;i>=0;i--)A[index--]=stoi(a.substr(i,1));
    index = n-1;
    for(int i=b.size()-1;i>=0;i--)B[index--]=stoi(b.substr(i,1));
    int* C = Multiply(A,B,n,0,0);
    for(int i=2*n-2;i>=0;i--){
        if(i==0){
            T.push(to_string(C[i]));
            break;
        }
        T.push(to_string(C[i]%10));
        C[i-1]+=C[i]/10;
    }
    while(!T.empty()){
        R+=T.top();
        T.pop();
    }
    for(int i=0;i<R.size();i++){
        if(R[i]!='0'){
            Ans = R.substr(i);
            break;
        }
    }
    return Ans;
}

// Driver code
int main()
{
   string a,b;
   a = "1000";     // First number
   b = "9000";     // Second number
   cout<<BigIntegerMult(a,b);    // Returns a string of a and b multiplication

    return 0;
}
