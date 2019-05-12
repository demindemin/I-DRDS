//
//  DSCR.cpp
//  IDRDS
//
//  Created by Shen Tong & Zhaoquan Gu on 2018/6/14.
//  Copyright © 2018 ShenTong & Zhaoquan Gu. All rights reserved.
//

#include "Header.h"

vector<int> dsc;

void DSC(int n){
    
    dsc.clear();
    vector<vector<int> > C;
    vector<int> Ci;
    int P=findPrimeLargerorEqual(n);
    C.clear();
    for(int i=0; i<P; i++){
        C.push_back(Ci);
        C[i].clear();
    }
    for(int i=0; i<P; i++){
        for(int j=0; j<P; j++){
            C[i].push_back(j*(2*P+P/2)+i);
            dsc.push_back(-1);
        }
        for(int k=1; k<=P+P/2; k++){
            int l=k*(3*k-1)/2;
            int rik=i*(2*P+P/2)+P+k-1;
            C[(i+l)%P].push_back(rik);
            dsc.push_back(-1);
        }
    }
    
    for(int i=0;i<P;i++){
        for(int j=0;j<C[i].size();j++){
            if(i>=n)
                dsc[C[i][j]]=i%n;
            else
                dsc[C[i][j]]=i;
        }
    }
    for(int i=0;i<dsc.size();i++)
        if(dsc[i]==-1)
            cout<<"error:DSC1"<<endl;
    
}

int rendezvousDSCR(int n,int delay){
    
    int P= findPrimeLargerorEqual(n);
    int length = P*(2*P+P/2);
    for(int i = 0; i<length; i++){
        int t1 = i;
        int t2 = (i+delay)%length;
        int c1 = dsc[t1];
        int c2 = dsc[t2];
        if(!availiable(c1,Channel1)){
            //c1=-1;
            c1=Channel1[int(random(0,Channel1.size()))];
        }
        if(!availiable(c2,Channel2)){
            //c2=-2;
            c2=Channel2[int(random(0,Channel2.size()))];
        }
        if((c1 == c2) && (RIrank[c1]>rtt*common)){
            grank[dscr]+=RIrank[c1];
            gari[dscr]+=interference1[c1]*interference2[c2];
            //channelcount[c1]++;
            return i+1;
        }
    }
    cout<<" errorDSCR!"<<endl;
    return INT_MAX;
}

void DSCR(int n){
    
    int timeMax = 0;
    double timeAverage = 0;
    //r=0;
    DSC(n);
    int delay;
    for(int i = 0; i< runtime; i++){
        delay = rand();
        int temp = rendezvousDSCR(n,delay);
        if(temp > timeMax)
            timeMax = temp;
        timeAverage = timeAverage + temp;
    }
    timeAverage = timeAverage / runtime;
    //r = r / runtime;
    
    if(gmttr[dscr]<timeMax)
        gmttr[dscr]=timeMax;
    gattr[dscr]+=timeAverage;
    //grank[dscr]+=r;
    
}
