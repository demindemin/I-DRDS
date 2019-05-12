//
//  global.cpp
//  IDRDS
//
//  Created by Shen Tong & Zhaoquan Gu on 2018/6/14.
//  Copyright © 2018 ShenTong & Zhaoquan Gu. All rights reserved.
//

#include "Header.h"

bool availiable(int c,vector<int> channel){
    
    for(int i=0;i<channel.size();i++){
        if(c==channel[i])
            return true;
        else if(channel[i]>c)
            return false;
    }
    return false;
}

void valueclear(){
    
    for(int i=0;i<alg;i++){
        gmttr[i]=0;
        gattr[i]=0;
        grank[i]=0;
        gari[i]=0;
    }
    return;
}

double random(double start,double end)
{
    return start+(end-start)*rand()/(RAND_MAX+1.0);
}

void output(vector<double> out){
    
    unsigned long n=out.size();
    for(int i=0;i<n;i++)
        cout<<out[i]<<" ";
    cout<<endl;
    return;
}

void outputnor(vector<double> nor){
    
    double sum=0;
    for(int i=0;i<nor.size();i++)
        sum+=nor[i];
    cout<<"P: ";
    for(int i=0;i<nor.size();i++){
        double p=nor[i]/sum;
        if(p!=0)
            cout<<"("<<i<<": "<<p<<") ";
    }
    cout<<endl;
    
    return ;
}

int findPrimeLarger(int n){
    
    bool isPrime = true;
    for(int res = n+1; res <=2*n; res++)
    {
        isPrime = true;
        for(int i = 2; i*i<= res; i++){
            if(res%i == 0){
                isPrime = false;
                break;
            }
        }
        if(isPrime)
            return res;
    }
    return 0;
}

int findPrimeLargerorEqual(int n){
    
    bool isPrime = true;
    for(int res = n; res <=2*n; res++)
    {
        isPrime = true;
        for(int i = 2; i*i<= res; i++)
        {
            if(res%i == 0)
            {
                isPrime = false;
                break;
            }
        }
        if(isPrime)
            return res;
    }
    return 0;
}

int findPrimeLargerorEqualTwice(int n){
    
    bool isPrime = true;
    for(int res = 2*n; res <=4*n; res++)
    {
        isPrime = true;
        for(int i = 2; i*i<= res; i++)
        {
            if(res%i == 0)
            {
                isPrime = false;
                break;
            }
        }
        if(isPrime)
            return res;
    }
    return 0;
}
