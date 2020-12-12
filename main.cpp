#include <iostream>
#include <stdio.h>
#include <array>
#include <string>
#include <iomanip>
#include "rmsch.h"


using namespace std;

void display_results (int task ,int period_time[],int lcm, int release_time[][100],int N[], int Finishtime[][100]){

       for(int i=0 ; i<task ; i++){
          N[i]=(lcm/period_time[i]);

          cout<<"The number of releases,(N[i]), of task "<< i+1 << " = "<<N[i]<<endl;

          cout << "The release times of task " <<i+1<<" are "<<endl;
          for(int j=0;j<N[i];j++){
            release_time[i][j]=j*period_time[i];
            cout<<release_time[i][j]<<endl;
          }

          cout<<"the finish times of Task"<<i+1<<" are "<<endl;
          for(int j=0;j<N[i];j++){
            cout<<Finishtime[i][j]<<endl;
          }

        }
  }

void averageresp_time (int task,int Finishtime[][100],int release_time[][100],int N[]){

double avg[task]={0};
int sum[task]={0};

    for(int i=0 ;i<task;i++ ){
      for(int j=0;j<N[i];j++){
        if (Finishtime[i][j]!=0) {
          /* code */
        int timetaken=Finishtime[i][j]-release_time[i][j];
        sum[i]=timetaken+sum[i];
      }
      }
        avg[i] = (double)sum[i]/(double)N[i];
}
      cout<<"the average response times of Tasks 1 to "<<task<<" are "<<endl;
      for(int i=0 ;i<task;i++ ){
      cout<<avg[i]<<endl;
    }
    cout<<"respectively"<<endl;

}





int main(){
  int task = task_number();
  int comp_time[100]={0};
  int period_time[100]={0};
  int table[100][2]={{0},{0}};
  int rank_1[100]={0};
  int priority[10][4]={0};
  int Remainingtime[100]={0};
  int Complet_time[100]={0};
  int Completionstatus[100]={0};
  int arr[4][100]={{0},{0}};
  int N[100];
  int release_time[20][100];
  int Finishtime[20][100];
//  int avg[task][100];
//cout<<"Total task no = "<<task<<endl;
computation_time(task,comp_time,period_time,table,rank_1);
//output2darray(task,table,rank_1);
//cout<<"time"<< comp_time[1]<<endl;
float sum = utilization_factor(task,comp_time,period_time);
int lcm = hyperperiod(period_time,task);
prioritization(task,comp_time,period_time,rank_1,priority);
//schedulability(sum);
if(sum==0){
  cout<<"Hyperperiod is"<<lcm<<endl;
  scheduling (task, priority, lcm, Remainingtime,Completionstatus, Finishtime);
  display_results(task,period_time,lcm,release_time,N,Finishtime);
  averageresp_time (task, Finishtime, release_time,N);
}

}
