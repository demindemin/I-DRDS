//
//  Header.h
//  IDRDS
//
//  Created by Shen Tong & Zhaoquan Gu on 2018/6/14.
//  Copyright © 2018 ShenTong & Zhaoquan Gu. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include<vector>
#include <cstdio>
#include<string>
using namespace std;

#define dscr    0
#define crseq   1
#define ejs     2
#define drds    3
#define idrdsp  4
#define idrdsd  5
#define alg     6

//Global parameter
extern int N;                      //the number of total channels
extern int M;                      //the number of total extended channels
extern string name[6];
extern double gmttr[6];
extern double gattr[6];
extern double grank[6];
extern double gari[6];
extern int runtime;                //test for different time draft
extern unsigned int common;        //the number of common channels of two users
extern double ra;                  //available channel ratio for user 1
extern double rb;                  //available channel ratio for user 2
extern double rg;                  //common available channel ratio
//extern double r;                   //count for RI rank
extern double rtt;                 //threshold ratio

extern vector<int> Channel1,Channel2;  //available channels for the two users
extern vector<double> interference1;   //channel RSSI value for user 1
extern vector<double> interference2;   //channel RSSI value for user 2
extern vector<double> normal1;         //normalized interference for user 1
extern vector<double> normal2;         //normalized interference for user 2
extern vector<int> mapchannel1;
extern vector<int> mapchannel2;
extern vector<int> RIrank;

//global.cpp
void valueclear();
bool availiable(int c,vector<int> channel);
double random(double start,double end);//generate a random float between [start,end);
void output(vector<double> out);//output vector<double>
void outputnor(vector<double> nor);//output probability that relates to the normalization
int findPrimeLarger(int n);//find a prime number larger than N
int findPrimeLargerorEqual(int n);///find a prime number no less than N
int findPrimeLargerorEqualTwice(int n);//find a prime number no less than 2*N

//initialize.cpp
void initchannel();
double RSSI(double R);
//double value(int ch,int tip);
void RIinit();//initialize RI value of channels;
int generatechannel(vector<double> nor);//generate a random available channel with probability
vector<double> initialize_interference(int tip);//initialize vector interference: 0 for generate data; 10 for tau51 data 11 for hula51 data
vector<double> normalize_interference(vector<int> channel,vector<double> inf);//normalize vector interference
vector<int> mapchannel(vector<int> channel,vector<double> nor,int tip);//interference mapping
int findlargest(vector<int> a);

//evaluation.cpp
void test_real_data_rg(double ra0,double rb0,double rg0);
void test_real_data_rb(double ra0,double rb0,double rg0);
void test_generate_data_rg(double ra0,double rb0,double rg0);
void test_generate_data_rb(double ra0,double rb0,double rg0);
void test_generate_data_N(double ra0,double rb0,double rg0);
void evaluation();

//DSCR.cpp
void DSC(int n);
int rendezvousDSCR(int n,int delay);
void DSCR(int n);

//CRSEQ.cpp
int channel(int ch, int K);
int CHCRSEQ(int n,int T);
void CRSEQ(int n);

//EJS.cpp
int EJSHopping(int M0,int P0,int r0,int i0,long t0);
int runtotal(int T);
void EJS(int n);

//DRDS.cpp
int DRDSChannel(int n,int t);
int rendezvousDRDS(int n,int delay);
void DRDS(int n);
void I_DRDS_P(int n);
void I_DRDS_D(int n);

#endif /* Header_h */
