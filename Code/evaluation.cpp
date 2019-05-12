//
//  evaluation.cpp
//  IDRDS
//
//  Created by Shen Tong & Zhaoquan Gu on 2018/6/14.
//  Copyright © 2018 ShenTong & Zhaoquan Gu. All rights reserved.
//

#include "Header.h"

int N;                      //the number of total channels
int M;                      //the number of total extended channels
unsigned int common;        //the number of common channels of two users
//double r;                   //count for RI rank
double ra;                  //available channel ratio for user 1
double rb;                  //available channel ratio for user 2
double rg;                  //common available channel ratio
double rtt;
int fig;
string name[6] = {  "DSCR",
    "CRSEQ",
    "EJS",
    "DRDS",
    "I-DRDS-P",
    "I-DRDS-D"
};
string eva[4] = {   "RIrank",
                    "RI",
                    "MTTR",
                    "ATTR"
};
double gmttr[6];
double gattr[6];
double grank[6];
double gari[6];
int runtime;                //test for different time draft

vector<int> Channel1,Channel2;  //available channels for the two users
vector<double> interference1;   //channel RSSI value for user 1
vector<double> interference2;   //channel RSSI value for user 2
vector<double> normal1;         //normalized interference for user 1
vector<double> normal2;         //normalized interference for user 2
vector<int> mapchannel1;
vector<int> mapchannel2;
vector<int> RIrank;

int iruntime;
string s1 = "/users/st/Documents/code//IDRDS/IDRDS/figure";
string s2 = ".txt";
string ss;
string s3;

void test_real_data_rg(double ra0,double rb0,double rg0){
    
    iruntime=100;
    runtime=100;
    rtt = 0;
    M = findPrimeLargerorEqualTwice(N);
    ra=ra0;
    rb=rb0;
    rg=rg0;
    
    cout<<"real data :"<<endl;
    fig++;
    cout<<"Fig: "<<fig<<endl;
    //figure1-4:RIrank
    ss='0'+fig;
    s3= s1 + ss + eva[0] + s2;
    ofstream fout1(s3);
    fout1<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    //figure1-4:RI
    s3= s1 + ss + eva[1] + s2;
    ofstream fout2(s3);
    fout2<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    //figure1-4:mttr
    s3= s1 + ss + eva[2] + s2;
    ofstream fout3(s3);
    fout3<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    //figure1-4:attr
    s3= s1 + ss + eva[3] + s2;
    ofstream fout4(s3);
    fout4<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    
    for(int fww=1;fww<=10;fww++){
        
        rg=rg0*fww;
        fout1<<rg<<" ";
        fout2<<rg<<" ";
        fout3<<rg<<" ";
        fout4<<rg<<" ";
        valueclear();
        for(int i=0;i<iruntime;i++){
            if(i%20==0)
                cout<<i<<endl;
            initchannel();
            interference1=initialize_interference(10);
            interference2=initialize_interference(11);
            RIinit();
            normal1=normalize_interference(Channel1, interference1);
            //outputnor(normal1);
            normal2=normalize_interference(Channel2, interference2);
            //outputnor(normal2);
            mapchannel1=mapchannel(Channel1, normal1,0);
            mapchannel2=mapchannel(Channel2, normal2,0);
                    
            DSCR(N);
            CRSEQ(N);
            EJS(N);
            DRDS(N);
            I_DRDS_P(N);
            mapchannel1=mapchannel(Channel1, normal1,1);
            mapchannel2=mapchannel(Channel2, normal2,1);
            I_DRDS_D(N);
                    
            }
            cout<<"rg: "<<rg<<endl;
                double temp1,temp2,temp3,temp4;
                for(int i=0;i<alg;i++){
                    temp1=grank[i]/(iruntime*runtime)/common;
                    temp2=log(gari[i]/(iruntime*runtime))/log(2.0);
                    temp3=log(gmttr[i])/log(2.0);
                    temp4=log(gattr[i]/iruntime)/log(2.0);
                    cout<<name[i]<<": "<<endl;
                    cout<<"Average RI rank: "<<temp1<<endl;
                    cout<<"Average RI: "<<temp2<<endl;
                    cout<<"MTTR: "<<temp3<<endl;
                    cout<<"ATTR: "<<temp4<<endl;
                    fout1<<temp1<<" ";
                    fout2<<temp2<<" ";
                    fout3<<temp3<<" ";
                    fout4<<temp4<<" ";
                }
                fout1<<endl;
                fout2<<endl;;
                fout3<<endl;
                fout4<<endl;
                cout<<endl;
            }
            fout1.close();
            fout2.close();
            fout3.close();
            fout4.close();
            cout<<"____________________"<<endl;
    
}

void test_real_data_rb(double ra0,double rb0,double rg0){
    
    iruntime=100;
    runtime=100;
    rtt = 0;
    M = findPrimeLargerorEqualTwice(N);
    ra=ra0;
    rb=rb0;
    rg=rg0;
    
    cout<<"real data :"<<endl;
    fig++;
    cout<<"Fig: "<<fig<<endl;
    //figure1-4:RIrank
    ss='0'+fig;
    s3= s1 + ss + eva[0] + s2;
    ofstream fout1(s3);
    fout1<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    //figure1-4:RI
    s3= s1 + ss + eva[1] + s2;
    ofstream fout2(s3);
    fout2<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    //figure1-4:mttr
    s3= s1 + ss + eva[2] + s2;
    ofstream fout3(s3);
    fout3<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    //figure1-4:attr
    s3= s1 + ss + eva[3] + s2;
    ofstream fout4(s3);
    fout4<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    
    for(int fww=1;fww<=10;fww++){
        rb=rb0*fww;
        rg=rg0*fww;
        fout1<<rg<<" ";
        fout2<<rg<<" ";
        fout3<<rg<<" ";
        fout4<<rg<<" ";
        valueclear();
        for(int i=0;i<iruntime;i++){
            if(i%20==0)
                cout<<i<<endl;
            initchannel();
            interference1=initialize_interference(10);
            interference2=initialize_interference(11);
            RIinit();
            normal1=normalize_interference(Channel1, interference1);
            //outputnor(normal1);
            normal2=normalize_interference(Channel2, interference2);
            //outputnor(normal2);
            mapchannel1=mapchannel(Channel1, normal1,0);
            mapchannel2=mapchannel(Channel2, normal2,0);
            
            DSCR(N);
            CRSEQ(N);
            EJS(N);
            DRDS(N);
            I_DRDS_P(N);
            mapchannel1=mapchannel(Channel1, normal1,1);
            mapchannel2=mapchannel(Channel2, normal2,1);
            I_DRDS_D(N);
            
        }
        cout<<"rg: "<<rg<<endl;
        double temp1,temp2,temp3,temp4;
        for(int i=0;i<alg;i++){
            temp1=grank[i]/(iruntime*runtime)/common;
            temp2=log(gari[i]/(iruntime*runtime))/log(2.0);
            temp3=log(gmttr[i])/log(2.0);
            temp4=log(gattr[i]/iruntime)/log(2.0);
            cout<<name[i]<<": "<<endl;
            cout<<"Average RI rank: "<<temp1<<endl;
            cout<<"Average RI: "<<temp2<<endl;
            cout<<"MTTR: "<<temp3<<endl;
            cout<<"ATTR: "<<temp4<<endl;
            fout1<<temp1<<" ";
            fout2<<temp2<<" ";
            fout3<<temp3<<" ";
            fout4<<temp4<<" ";
        }
        fout1<<endl;
        fout2<<endl;;
        fout3<<endl;
        fout4<<endl;
        cout<<endl;
    }
    fout1.close();
    fout2.close();
    fout3.close();
    fout4.close();
    cout<<"____________________"<<endl;
    
}

void test_generate_data_rg(double ra0,double rb0,double rg0){
    
    iruntime=100;
    runtime=100;
    rtt = 0;
    M = findPrimeLargerorEqualTwice(N);
    ra=ra0;
    rb=rb0;
    rg=rg0;
    
    cout<<"real data :"<<endl;
    fig++;
    cout<<"Fig: "<<fig<<endl;
    //figure1-4:RIrank
    ss='0'+fig;
    s3= s1 + ss + eva[0] + s2;
    ofstream fout1(s3);
    fout1<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    //figure1-4:RI
    s3= s1 + ss + eva[1] + s2;
    ofstream fout2(s3);
    fout2<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    //figure1-4:mttr
    s3= s1 + ss + eva[2] + s2;
    ofstream fout3(s3);
    fout3<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    //figure1-4:attr
    s3= s1 + ss + eva[3] + s2;
    ofstream fout4(s3);
    fout4<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    
    for(int fww=1;fww<=10;fww++){
        
        rg=rg0*fww;
        fout1<<rg<<" ";
        fout2<<rg<<" ";
        fout3<<rg<<" ";
        fout4<<rg<<" ";
        valueclear();
        for(int i=0;i<iruntime;i++){
            if(i%20==0)
                cout<<i<<endl;
            initchannel();
            interference1=initialize_interference(0);
            interference2=initialize_interference(0);
            RIinit();
            normal1=normalize_interference(Channel1, interference1);
            //outputnor(normal1);
            normal2=normalize_interference(Channel2, interference2);
            //outputnor(normal2);
            mapchannel1=mapchannel(Channel1, normal1,0);
            mapchannel2=mapchannel(Channel2, normal2,0);
            
            DSCR(N);
            CRSEQ(N);
            EJS(N);
            DRDS(N);
            I_DRDS_P(N);
            mapchannel1=mapchannel(Channel1, normal1,1);
            mapchannel2=mapchannel(Channel2, normal2,1);
            I_DRDS_D(N);
            
        }
        cout<<"rg: "<<rg<<endl;
        double temp1,temp2,temp3,temp4;
        for(int i=0;i<alg;i++){
            temp1=grank[i]/(iruntime*runtime)/common;
            temp2=log(gari[i]/(iruntime*runtime))/log(2.0);
            temp3=log(gmttr[i])/log(2.0);
            temp4=log(gattr[i]/iruntime)/log(2.0);
            cout<<name[i]<<": "<<endl;
            cout<<"Average RI rank: "<<temp1<<endl;
            cout<<"Average RI: "<<temp2<<endl;
            cout<<"MTTR: "<<temp3<<endl;
            cout<<"ATTR: "<<temp4<<endl;
            fout1<<temp1<<" ";
            fout2<<temp2<<" ";
            fout3<<temp3<<" ";
            fout4<<temp4<<" ";
        }
        fout1<<endl;
        fout2<<endl;;
        fout3<<endl;
        fout4<<endl;
        cout<<endl;
    }
    fout1.close();
    fout2.close();
    fout3.close();
    fout4.close();
    cout<<"____________________"<<endl;
    
}

void test_generate_data_rb(double ra0,double rb0,double rg0){
    
    iruntime=100;
    runtime=100;
    rtt = 0;
    M = findPrimeLargerorEqualTwice(N);
    ra=ra0;
    rb=rb0;
    rg=rg0;
    
    cout<<"real data :"<<endl;
    fig++;
    cout<<"Fig: "<<fig<<endl;
    //figure1-4:RIrank
    ss='0'+fig;
    s3= s1 + ss + eva[0] + s2;
    ofstream fout1(s3);
    fout1<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    //figure1-4:RI
    s3= s1 + ss + eva[1] + s2;
    ofstream fout2(s3);
    fout2<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    //figure1-4:mttr
    s3= s1 + ss + eva[2] + s2;
    ofstream fout3(s3);
    fout3<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    //figure1-4:attr
    s3= s1 + ss + eva[3] + s2;
    ofstream fout4(s3);
    fout4<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    
    for(int fww=1;fww<=10;fww++){
        rb=rb0*fww;
        rg=rg0*fww;
        fout1<<rg<<" ";
        fout2<<rg<<" ";
        fout3<<rg<<" ";
        fout4<<rg<<" ";
        valueclear();
        for(int i=0;i<iruntime;i++){
            if(i%20==0)
                cout<<i<<endl;
            initchannel();
            interference1=initialize_interference(0);
            interference2=initialize_interference(0);
            RIinit();
            normal1=normalize_interference(Channel1, interference1);
            //outputnor(normal1);
            normal2=normalize_interference(Channel2, interference2);
            //outputnor(normal2);
            mapchannel1=mapchannel(Channel1, normal1,0);
            mapchannel2=mapchannel(Channel2, normal2,0);
            
            DSCR(N);
            CRSEQ(N);
            EJS(N);
            DRDS(N);
            I_DRDS_P(N);
            mapchannel1=mapchannel(Channel1, normal1,1);
            mapchannel2=mapchannel(Channel2, normal2,1);
            I_DRDS_D(N);
            
        }
        cout<<"rg: "<<rg<<endl;
        double temp1,temp2,temp3,temp4;
        for(int i=0;i<alg;i++){
            temp1=grank[i]/(iruntime*runtime)/common;
            temp2=log(gari[i]/(iruntime*runtime))/log(2.0);
            temp3=log(gmttr[i])/log(2.0);
            temp4=log(gattr[i]/iruntime)/log(2.0);
            cout<<name[i]<<": "<<endl;
            cout<<"Average RI rank: "<<temp1<<endl;
            cout<<"Average RI: "<<temp2<<endl;
            cout<<"MTTR: "<<temp3<<endl;
            cout<<"ATTR: "<<temp4<<endl;
            fout1<<temp1<<" ";
            fout2<<temp2<<" ";
            fout3<<temp3<<" ";
            fout4<<temp4<<" ";
        }
        fout1<<endl;
        fout2<<endl;;
        fout3<<endl;
        fout4<<endl;
        cout<<endl;
    }
    fout1.close();
    fout2.close();
    fout3.close();
    fout4.close();
    cout<<"____________________"<<endl;
    
}

void test_generate_data_N(double ra0,double rb0,double rg0){
    
    iruntime=100;
    runtime=100;
    rtt=0;
    rg = rg0;
    ra = ra0;
    rb = rb0;

    cout<<"generated data :"<<endl;
    fig++;
    cout<<"Fig: "<<fig<<endl;
    //figure1-4:RIrank
    ss='0'+fig;
    s3= s1 + ss + eva[0] + s2;
    ofstream fout1(s3);
    fout1<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    //figure1-4:RI
    s3= s1 + ss + eva[1] + s2;
    ofstream fout2(s3);
    fout2<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    //figure1-4:mttr
    s3= s1 + ss + eva[2] + s2;
    ofstream fout3(s3);
    fout3<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;
    //figure1-4:attr
    s3= s1 + ss + eva[3] + s2;
    ofstream fout4(s3);
    fout4<<"DSCR CRSEQ EJS DRDS I-DRDS-P I-DRDS-D"<<endl;

    for(int fww=1;fww<=10;fww++){
                    
        N=50*fww;
        M=findPrimeLargerorEqualTwice(N);
        fout1<<N<<" ";
        fout2<<N<<" ";
        fout3<<N<<" ";
        fout4<<N<<" ";
        valueclear();
        for(int i=0;i<iruntime;i++){
            if(i%20==0)
                cout<<i<<endl;
            initchannel();
            interference1=initialize_interference(0);
            interference2=initialize_interference(0);
            RIinit();
            normal1=normalize_interference(Channel1, interference1);
            //outputnor(normal1);
            normal2=normalize_interference(Channel2, interference2);
            //outputnor(normal2);
            mapchannel1=mapchannel(Channel1, normal1,0);
            mapchannel2=mapchannel(Channel2, normal2,0);
            
            DSCR(N);
            CRSEQ(N);
            EJS(N);
            DRDS(N);
            I_DRDS_P(N);
            mapchannel1=mapchannel(Channel1, normal1,1);
            mapchannel2=mapchannel(Channel2, normal2,1);
            I_DRDS_D(N);
            
        }
        cout<<"N: "<<N<<endl;
        double temp1,temp2,temp3,temp4;
        for(int i=0;i<alg;i++){
            temp1=grank[i]/(iruntime*runtime)/common;
            temp2=log(gari[i]/(iruntime*runtime))/log(2.0);
            temp3=log(gmttr[i])/log(2.0);
            temp4=log(gattr[i]/iruntime)/log(2.0);
            cout<<name[i]<<": "<<endl;
            cout<<"Average RI rank: "<<temp1<<endl;
            cout<<"Average RI: "<<temp2<<endl;
            cout<<"MTTR: "<<temp3<<endl;
            cout<<"ATTR: "<<temp4<<endl;
            fout1<<temp1<<" ";
            fout2<<temp2<<" ";
            fout3<<temp3<<" ";
            fout4<<temp4<<" ";
        }
        fout1<<endl;
        fout2<<endl;;
        fout3<<endl;
        fout4<<endl;
        cout<<endl;
    }
    fout1.close();
    fout2.close();
    fout3.close();
    fout4.close();
    cout<<"____________________"<<endl;
   
}

void evaluation(){
    
    //Pro: tip = 0
    //Det: tip = 1
    fig=0;
    //figure order: DSDR CRSEQ EJS DRDS IA-DRDS
    //real data***********************************
    //Efficiency
    //fig1/7:   ra = 0.5, rb = 0.5, N = 51
    //          when rg increases from 0.05 to 0.5;
    N=51;
    test_real_data_rg(0.5,0.5,0.05);
    //fig2/8:   ra = 1, rb = rg N =51
    //          when rb increases from 0.1 to 1
    N=51;
    test_real_data_rb(1,0.1,0.1);
    
    //generate data*******************************
    //Efficiency
    //fig3/9:   ra = 0.5, rb = 0.5, N = 50
    //          when rg increases from 0.05 to 0.5;
    N=50;
    test_generate_data_rg(0.5,0.5,0.05);
    //fig4/10:  ra = 1, rb = rg N = 50
    //          when rb increases from 0.1 to 1
    N=50;
    test_generate_data_rb(1,0.1,0.1);
    //Scalibility
    //fig5/11:  ra = 0.2, rb = 0.3, rg = 0.1
    //          when N increases from 100 to 500
    test_generate_data_N(0.2,0.3,0.1);
    //fig6/12:  ra = 0.7, rb = 0.7, rg = 0.5
    //          when N increases from 100 to 500
    test_generate_data_N(0.7,0.7,0.5);
    
}
