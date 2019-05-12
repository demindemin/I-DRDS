//
//  initialize.cpp
//  IDRDS
//
//  Created by Shen Tong & Zhaoquan Gu on 2018/6/14.
//  Copyright © 2018 ShenTong & Zhaoquan Gu. All rights reserved.
//

#include "Header.h"

//double value(int ch,int tip){
//    if(tip==0)
//        return interference1[ch]*interference2[ch];
//    else if(tip==1)
//        return max(interference1[ch],interference2[ch]);
//    else{
//        cout<<"error"<<endl;
//        return -1;
//    }
//}

double RSSI(double R){
    
    return pow(10,(R-95)/10)/1000;
}

void RIinit(){
    
    vector<double> RI;
    RI.clear();
    RIrank.clear();
    for(int i=0;i<N;i++){
        RI.push_back(0);
        RIrank.push_back(-1);
    }
    for(int i=0;i<N;i++){
        if(availiable(i,Channel1) && availiable(i,Channel2))
            RI[i]=interference1[i]*interference2[i]; //#
    }
    for(int i=0;i<N;i++){
        if(RI[i]!=0){
            int s=1;
            for(int j=0;j<N;j++)
                if(RI[j]>RI[i])
                    s++;
            RIrank[i]=s;
        }
    }
}

void initchannel(){
    
    Channel1.clear();
    Channel2.clear();
    int a=ra*N;
    int b=rb*N;
    int g=rg*N;
    common=g;
    bool C[10000];
    for(int i=0;i<N;i++)
        C[i]=false;
    for(int i=0;i<g;i++){
        int temp=int(random(0,N));
        while(C[temp])
            temp=int(random(0,N));
        Channel1.push_back(temp);
        Channel2.push_back(temp);
        C[temp]=true;
    }
    for(int i=0;i<(a-g);i++){
        int temp=int(random(0,N));
        while(C[temp])
            temp=int(random(0,N));
        Channel1.push_back(temp);
        C[temp]=true;
    }
    for(int i=0;i<(b-g);i++){
        int temp=int(random(0,N));
        while(C[temp])
            temp=int(random(0,N));
        Channel2.push_back(temp);
        C[temp]=true;
    }
    sort(Channel1.begin(),Channel1.end());
    sort(Channel2.begin(),Channel2.end());
}


vector<double> initialize_interference(int tip){
    
    vector<double> inf;
    inf.clear();
    if(tip==0){
        //generate randomly between[1,99]
        for(int i=0;i<N;i++)
            inf.push_back(random(100,200));
        return inf;
        
    }
    else if(tip==10||tip==11){
        //under reality condition
        double in[51];
        int count[51];
        for(int i=0;i<51;i++){
            count[i]=0;
            in[i]=0;
        }
        
        int  ran=int(random(0, 35));
        
        FILE *fp;
        if(tip==10)
            fp=fopen("/users/st/Documents/code/IDRDS/IDRDS/tau51.txt","r");
        else if(tip==11)
            fp=fopen("/users/st/Documents/code/IDRDS/IDRDS/hula51.txt","r");
        else{
            cout<<"error5!"<<endl;
            fp=NULL;
        }
        if(fp==NULL){
            printf("打开文件失败! \n");
            exit(0);
        }
        
        double temp,interference;
        int channel;
        
        double start=0;
        double tt=0;
        fscanf(fp, "%lf",&start);
        
        while((tt-start)<ran*600){
            fscanf(fp, "%lf",&temp);
            fscanf(fp, "%lf",&temp);
            fscanf(fp, "%lf",&temp);
            fscanf(fp, "%lf",&temp);
            fscanf(fp, "%lf",&temp);
            fscanf(fp, "%lf",&temp);
            fscanf(fp, "%lf",&temp);
            fscanf(fp, "%lf",&temp);
            fscanf(fp, "%lf",&temp);
            fscanf(fp, "%lf",&tt);
        }
        double time=tt;
        while((time-tt)<600){
            fscanf(fp, "%lf",&temp);
            
            //channel
            fscanf(fp, "%d",&channel);
            channel=(channel/100)%4310;
            
            fscanf(fp, "%lf",&temp);
            fscanf(fp, "%lf",&temp);
            fscanf(fp, "%lf",&temp);
            fscanf(fp, "%lf",&temp);
            
            //interference
            fscanf(fp, "%lf",&interference);
            //interference=RSSI(interference);
            fscanf(fp, "%lf",&temp);
            fscanf(fp, "%lf",&temp);
            
            if((channel<51)&&(channel>=0)){
                count[channel]++;
                in[channel]+=interference;
            }
            
            fscanf(fp, "%lf",&time);
        }
        
        for(int i=0;i<N;i++)
            inf.push_back(in[i]/count[i]);
        
        fclose(fp);
        return inf;
    }
    else{
        cout<<"error4!"<<endl;
        return inf;
    }
}

vector<double> normalize_interference(vector<int> channel,vector<double> inf){
    
    vector<double> nor;
    nor.clear();
    double max=0;
    double min=100000000;
    for(int i=0;i<inf.size();i++){
        if(!availiable(i, channel))
            continue;
        if(max<inf[i])
            max=inf[i];
        if(min>inf[i])
            min=inf[i];
    }
    double c=max-min;
    double tip;
    double temp;
    for(int i=0;i<inf.size();i++){
        if(availiable(i, channel))
            tip=1;
        else
            tip=0;
        temp=tip*(max-inf[i])/c;
        nor.push_back(temp);
    }
    
    return nor;
}


vector<int> mapchannel(vector<int> channel,vector<double> nor,int tip){
    
    vector<int> mapchannel;
    mapchannel.clear();
   
    if(tip==0){
        for(int i=0;i<N;i++){
            if(availiable(i, channel))
                mapchannel.push_back(i);
            else{
                mapchannel.push_back(generatechannel(nor));
            }
        }
        for(int i=N;i<M;i++){
            mapchannel.push_back(generatechannel(nor));
        }
        return mapchannel;
    }
    else{
        int n = M - channel.size();
        double sum = 0;
        for(int i=0;i<nor.size();i++)
            sum+=nor[i];
        vector<int> xm;
        for(int i=0;i<nor.size();i++)
            xm.push_back(ceil(nor[i]/sum*n));
        
        int ch=findlargest(xm);
        for(int i=0;i<N;i++){
            if(availiable(i, channel))
                mapchannel.push_back(i);
            else{
                mapchannel.push_back(ch);
                xm[ch]--;
                if(xm[ch]==0)
                    ch=findlargest(xm);
            }
        }
        for(int i=N;i<M;i++){
            mapchannel.push_back(ch);
            xm[ch]--;
            if(xm[ch]==0)
                ch=findlargest(xm);
        }
        
        return mapchannel;
    }

}

int generatechannel(vector<double> nor){
    
    int channel=-1;
    double sum=0;
    for(int i=0;i<nor.size();i++)
        sum+=nor[i];
    double pro=0;
    double p=rand()/(RAND_MAX+1.0);
    for(int i=0;i<nor.size();i++){
        pro+=nor[i]/sum;
        if(pro>p){
            channel=i;
            break;
        }
    }
    return channel;
}

int findlargest(vector<int> a){
    
    int x=-1;
    double y=-10000000;
    for(int i=0;i<a.size();i++){
        if(y<a[i]){
            y=a[i];
            x=i;
        }
    }
    if(x==-1){
        cout<<"error:Find!"<<endl;
    }
    return x;
}
