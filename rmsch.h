#include <iostream>
#include <stdio.h>

using namespace std;

#ifndef rmsch_H
#define rmsch_H

int task_number();
void computation_time(int a,int comp_time[], int period_time[],int table[][2],int rank_1[]);
void output2darray(int task,int table[][2], int rank_1[]);
float utilization_factor(int task,int comp_time[], int period_time[]);
//void schedulability(float sum);
void prioritization(int task,int comp_time[], int period_time[], int rank_1[], int priority[][4]);
int hyperperiod(int period_time[], int task);
void scheduling (int task, int priority[][4], int lcm, int Remainingtime[], int Completionstatus[],int Finishtime[][100]);

#endif
