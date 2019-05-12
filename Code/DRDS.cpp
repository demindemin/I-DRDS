//
//  DRDS.cpp
//  IDRDS
//
//  Created by Shen Tong & Zhaoquan Gu on 2018/6/14.
//  Copyright © 2018 ShenTong & Zhaoquan Gu. All rights reserved.
//

#include "Header.h"
double gr,gri;
int DRDSChannel(int n,int t){
    
    int j = -1;
    int P = n;
    
    int index = t % (3*P);
    int period = t / (3*P);
    if(index < P)
        j = period;
    else
        j = (period * period + index*2) % P ;
    
    return j;
}

int rendezvousDRDS(int n,int delay){
    
    int length = 3*n*n;
    int per = length + n*2;
    for(int i = 0; i<per; i++){
        int t1 = i;
        int t2 = (i+delay)%length;
        int c1,c2;
        if(t1 < 2*n)
            c1 = Channel1[0];
        else
            c1 = DRDSChannel(n,t1);
        if(t2 < 2*n)
            c2 = Channel2[0];
        else
            c2 = DRDSChannel(n,t2);
        int tio = findPrimeLargerorEqual(N);
        if(n==M){
            c1=mapchannel1[c1];
            c2=mapchannel2[c2];
        }
        else if(n==tio){
            
            if(!availiable(c1,Channel1)){
                //c1=-1;
                c1=Channel1[int(random(0,Channel1.size()))];
            }
            if(!availiable(c2,Channel2)){
                //c2=-2;
                c2=Channel2[int(random(0,Channel2.size()))];
            }
        }
        else
            cout<<"error:DRDS1!"<<n<<" "<<M<<" "<<tio<<endl;
        if((c1 == c2) && (RIrank[c1]>rtt*common)){
            gr+=RIrank[c1];
            gri+=interference1[c1]*interference2[c2];
            return i+1;
        }
    }
    
    cout<<" error:DRDS2!"<<endl;
    return INT_MAX;
}

void DRDS(int n){
    
    int Plarger;
    int timeMax;
    double timeAverage;
    
    //DRDS
    Plarger=findPrimeLargerorEqual(n);
    timeMax = 0;
    timeAverage = 0;
    //r=0;
    gr=0;
    gri=0;
    int delay;
    for(int i = 0; i< runtime; i++){
        
        delay = rand();
        int temp = rendezvousDRDS(Plarger,delay);
        if(temp > timeMax)
            timeMax = temp;
        timeAverage = timeAverage + temp;
    }
    timeAverage = timeAverage / runtime;
    //r = r / runtime;
    
    if(gmttr[drds]<timeMax)
        gmttr[drds]=timeMax;
    gattr[drds]+=timeAverage;
    grank[drds]+=gr;
    gari[drds]+=gri;
    
}

void I_DRDS_P(int n){
    
    int timeMax;
    double timeAverage;
    
    //DRDS_interference
    if(M != findPrimeLargerorEqualTwice(n))
        cout<<"error:I-DRDS!"<<endl;
    timeMax = 0;
    timeAverage = 0;
    //r=0;
    gr=0;
    gri=0;
    int delay;
    for(int i = 0; i<runtime; i++){
        
        delay = rand();
        int temp = rendezvousDRDS(M,delay);
        if(temp > timeMax)
            timeMax = temp;
        timeAverage = timeAverage + temp;
    }
    timeAverage = timeAverage / runtime;
    //r = r / runtime;
    
    if(gmttr[idrdsp]<timeMax)
        gmttr[idrdsp]=timeMax;
    gattr[idrdsp]+=timeAverage;
    grank[idrdsp]+=gr;
    gari[idrdsp]+=gri;
}

void I_DRDS_D(int n){
    
    int timeMax;
    double timeAverage;
    
    //DRDS_interference
    if(M != findPrimeLargerorEqualTwice(n))
        cout<<"error:I-DRDS!"<<endl;
    timeMax = 0;
    timeAverage = 0;
    //r=0;
    gr=0;
    gri=0;
    int delay;
    for(int i = 0; i<runtime; i++){
        
        delay = rand();
        int temp = rendezvousDRDS(M,delay);
        if(temp > timeMax)
            timeMax = temp;
        timeAverage = timeAverage + temp;
    }
    timeAverage = timeAverage / runtime;
    //r = r / runtime;
    
    if(gmttr[idrdsd]<timeMax)
        gmttr[idrdsd]=timeMax;
    gattr[idrdsd]+=timeAverage;
    grank[idrdsd]+=gr;
    gari[idrdsd]+=gri;
}
