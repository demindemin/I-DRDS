//
//  CRSEQ.cpp
//  IDRDS
//
//  Created by Shen Tong & Zhaoquan Gu on 2018/6/14.
//  Copyright © 2018 ShenTong & Zhaoquan Gu. All rights reserved.
//

#include "Header.h"

int channel(int ch, int K){
    
    int x = ch/(3*K-1);
    int y = ch % (3*K-1);
    
    if(y < (K*2-1)){
        int z = ((x*(x+1)/2)+y) % K;
        return (z + 1);
    }
    else
        return ((x % K)+1);
}

int CHCRSEQ(int n,int T){
    
    int P=findPrimeLargerorEqual(n);
    int t1=T % (P*(3*P-1));
    int t2=0;
    int j1=-1;
    int j2=-2;
    
    while(true){
        j1=channel(t1,P)-1;
        j2=channel(t2,P)-1;
        if(!availiable(j1,Channel1))
            j1=-1;
        if(!availiable(j2,Channel2))
            j2=-2;
        if((j1==j2) && (RIrank[j1]>rtt*common)){
            grank[crseq]+=RIrank[j1];
            gari[crseq]+=interference1[j1]*interference2[j2];
            //channelcount[j1]++;
            return t2+1;
        }
        t1 = (t1+1) % (P*(3*P-1));
        t2++;
        if(t2 == P*(3*P-1)){
            cout<<"error:CRSEQ1"<<endl;
            return INT_MAX;
        }
    }
}

void CRSEQ(int n){
    
    int timeMax = 0;
    double timeAverage = 0;;
    //r=0;
    int delay;
    for(int i = 0; i< runtime; i++){
        
        delay = rand();
        int temp = CHCRSEQ(n,delay);
        if(temp > timeMax)
            timeMax = temp;
        timeAverage = timeAverage + temp;
    }
    timeAverage = timeAverage / runtime;
    //r = r / runtime;
    
    if(gmttr[crseq]<timeMax)
        gmttr[crseq]=timeMax;
    gattr[crseq]+=timeAverage;
    //grank[crseq]+=r;
    
}
