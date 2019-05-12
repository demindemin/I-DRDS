//
//  EJS.cpp
//  IDRDS
//
//  Created by Shen Tong & Zhaoquan Gu on 2018/6/14.
//  Copyright © 2018 ShenTong & Zhaoquan Gu. All rights reserved.
//

#include "Header.h"

int EJSHopping(int M0,int P0,int r0,int i0,long t0){
    
    t0=t0%(4*P0);
    int j0;
    if(t0<3*P0)
        j0=((i0+t0*r0-1)%P0)+1;
    else
        j0=r0;
    if(j0>M0)
        j0=(j0-1)%M0+1;
    return j0;
    
}

int runtotal(int n,int T){
    
    long t1=T;
    int t2=0;
    int P=findPrimeLarger(n);
    
    int r1=Channel1[random(0, Channel1.size())]+1;
    int r2=Channel2[random(0, Channel2.size())]+1;
    int i01=random(1, P+1);
    int i02=random(1, P+1);
    
    while(true){
        long n1;
        int n2,i1,i2,j1,j2;
        
        //user A
        n1=t1/(4*P);
        i1=((i01+n1-1)%P)+1;
        j1=EJSHopping(N,P,r1,i1,t1)-1;
        if(!availiable(j1,Channel1))
            j1=Channel1[(j1-1) % Channel1.size()];
        //user B
        n2=t2/(4*P);
        i2=((i02+n2-1)%P)+1;
        j2=EJSHopping(N,P,r2,i2,t2)-1;
        if(!availiable(j2,Channel2))
            j2=Channel2[(j2-1) % Channel2.size()];
        
        t1++;
        t2++;
        if((j1 == j2) && (RIrank[j1]>rtt*common)){
            grank[ejs]+=RIrank[j1];
            gari[ejs]+=interference1[j1]*interference2[j2];
            //channelcount[j1]++;
            return t2;
        }
        if(t2 % (4*P*(P+1)) == 0){
            r1=Channel1[random(0, Channel1.size())]+1;
            r2=Channel2[random(0, Channel2.size())]+1;
            //cout<<"error:EJS1"<<endl;
            //return INT_MAX;
        }
        if(t2 == 10*4*P*(P+1)){
            cout<<"error:EJS1"<<endl;
            return INT_MAX;
        }
    }
}

void EJS(int n){
    
    int timeMax = 0;
    double timeAverage = 0;;
    //r=0;
    int delay;
    for(int i = 0; i< runtime; i++){
        
        delay = rand();
        int temp = runtotal(n,delay);
        if(temp > timeMax)
            timeMax = temp;
        timeAverage = timeAverage + temp;
    }
    timeAverage = timeAverage / runtime;
    //r = r / runtime;
    
    if(gmttr[ejs]<timeMax)
        gmttr[ejs]=timeMax;
    gattr[ejs]+=timeAverage;
    //grank[ejs]+=r;
    
}
