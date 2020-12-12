#include <iostream>
#include <stdio.h>
#include <array>
#include <string>
#include <iomanip>
#include "rmsch.h"
#include <math.h>


using namespace std;

int task_number(){
int a;
cout<<"Enter the total number of tasks"<<endl;
cin>>a;
return a;
}
/*
int *computation_time(int a,int comp_time[],int period_time[]){

  for(int i = 0 ; i<a ;i++ ){
    cout <<"Computation time for task "<< i+1 <<endl;
    cin>>comp_time[i];
    cout <<"Period time for task "<< i+1 <<endl;
    cin>>period_time[i];
  }
    return comp_time,period_time;
  }
*/
void computation_time(int a,int comp_time[], int period_time[],int table[][2],int rank_1[]){

//create my table
    for(int i = 0 ; i<a ;i++ ){
      cout <<"Computation time for task "<< i+1 <<endl;
      cin>>comp_time[i];
      cout <<"Period time for task "<< i+1 <<endl;
      cin>>period_time[i];

      //table[i][0]=comp_time[i];
      //table[i][1]=period_time[i];
    }

      //checking the differences and prioritising
      for(int j=0;j<a;j++){
      int counter = 1;
        for(int k=0;k<a;k++){
          if((period_time[j]-period_time[k])>0)
          counter++;
        }
        rank_1[j]=counter;
      }

    }
/*
void output2darray(int task,int table[][2], int rank_1[]){

for(int i=0; i<task; i++)
        {
            cout <<"TASK" <<i+1 ;
                for(int j=0; j<2; j++)
                {
                        cout<<" "<<table[i][j]<<"  ";
                }
                cout<<rank_1[i];
                cout<<"\n";
        }

}
*/

float utilization_factor(int task,int comp_time[], int period_time[]){
  float cond=  0.0f;
  float sum = 0.0f;
  for (int i = 0; i < task; i++){
  sum = sum + ((float)comp_time[i]/(float)period_time[i]);
  //cout<<setprecision(3)<<sum;
  }
  cout<<"utilization factor="<<sum<<"\n";
double div_1 =(double)1/task;
  cond =(double)task*(pow(2,div_1)-1);
  cout<<"The Sufficient condition test is = "<< cond<<endl;
  if(sum<=cond){
       cout << "It is schedulable" << '\n';
       return 0;
  }else{
     cout<<"Task did not pass sufficient condition test"<<endl;
     return 1;
  }

}
/*
void schedulability(float sum){
    if (sum<1){
    cout<<"It is schedulable"<<endl;}
  else
    cout<<"It is not schedulabe"<<endl;
}
*/
void prioritization(int task,int comp_time[], int period_time[], int rank_1[], int priority[][4]){

  cout<<"Priority   "<<"Tasknumber       "<<"P[i]           "<<"C[i]    "<<endl;

  for(int j=1;j<=task;j++){

    for(int i=1;i<=task;i++){
      if(rank_1[i-1]==j){
        priority[j-1][0]=task-j+1;
        priority[j-1][1]=i;
        priority[j-1][2]=period_time[i-1];
        priority[j-1][3]=comp_time[i-1];
        break;
      }
    }
  }
for(int i=0;i<task;i++){
  for(int j=0;j<=3;j++){
  cout<<priority[i][j]<<"             ";
   }
   cout<<endl;
}
}
int hyperperiod(int period_time[], int task){
   //find max of the array
   int lcm= 1;
   while(1){
   int i = 0;
      while(i<task){
        if (lcm%period_time[i] != 0) {
            lcm++;
            break;
          }
          i++;
      }
    if(i==task){
      break; }
   }
   return lcm;
}

void scheduling (int task, int priority[][4], int lcm, int Remainingtime[], int Completionstatus[], int Finishtime[][100]){
   int currenttime = 0;
   int endtime;
   int m[task]={0};




  while(1){
    int count=0;
    int idletimectr=0;
    if(currenttime>=lcm){
    break;}//do scheduling only for first hyperperiod
    for (int i=0;i<task;i++){
        if((currenttime%priority[i][2])==0){  //reset the task completion status to 0 at beginning of each task's period
        Completionstatus[i]=0;
        Remainingtime[i]=0;
        }
      }

    if(currenttime%priority[0][2]==0){//check if the highest priority task should start at current time, by checking if current time is a multiple of that task's period
      endtime=currenttime+priority[0][3]; //ending time is comp. time of highest priority task + current time
      Completionstatus[0]=1;
      cout<<currenttime<<"-"<<endtime<<"Task"<<priority[0][1]<<endl; //display in format 6-8 Task (tasknumber)
      Finishtime[0][m[0]] = endtime;
      m[0]++;
      //cout <<"m[i] is"<<m[0]<<"for"<<"priority[0][1]"<<endl;
      //cout<<"Finish time of task "<<priority[0][1]<<" = "<<endtime<<endl;
      currenttime=endtime; //update current time with ending time
      Remainingtime[0] = priority[0][2]-priority[0][3]; //remaining time window for other tasks to run is period - computational time of highest priority task
      //cout<<"Completionstatus"<<Completionstatus[1]<<endl;
      }

    for(int i=1;i<task;i++){
      if(Completionstatus[i]==0){  //task is still incomplete
        if(Remainingtime[i] > 0){  //checks if task was previously begun and stopped
          if(Remainingtime[i]<Remainingtime[0]){  //check if time to compute unfinished portion is less than window allowed before highest priority task starts again
            endtime = currenttime + Remainingtime[i];  //so add only time to compute unfinished portion of task
            Completionstatus[i] = 1;
            Finishtime[i][m[i]] = endtime;
            m[i]++;
            //cout <<"m[i] is"<<m[0]<<"for"<<i<<endl;
            //cout<<"Finish time of task "<<priority[i][1]<<" = "<<endtime<<endl;
            }
          else{
            endtime = currenttime + Remainingtime[0];  //only time gap before highest priority task restarts is added
         }
       }
         else{
            if(priority[i][3]<=Remainingtime[0]){//checks if computational time for priority i task is less than remaining time before highest priority task starts again
            endtime = (currenttime+priority[i][3]);
            Completionstatus[i] = 1;
            Finishtime[i][m[i]] = endtime;
            m[i]++;
            //cout <<m[i]<<endl;
          //  cout<<"Finish time of task "<<priority[i][1]<<" = "<<endtime<<endl;
            }
            else{//if not enough time to complete priority task i
              endtime=currenttime+Remainingtime[0];
              Remainingtime[i] = priority[i][3] - Remainingtime[0];  //updates computation time remaining to finish task
            }
          }
        cout<<currenttime<<"-"<<endtime<<"Task"<<priority[i][1]<<endl;
        currenttime=endtime;

        }
      }
    for (int i=0;i<task;i++){
      idletimectr=idletimectr+Completionstatus[i];
    }
  //  cout<<Completionstatus[0]<<endl;
  //  cout<<Completionstatus[1]<<endl;
//    cout<<idletimectr<<endl;
      if (idletimectr==task){
        int start_time=currenttime;
        for(int i=0;i<task;i++){
            if(currenttime%priority[i][2]!=0){
                count++;
            }
          //cout<<count;
        if(count == task){


          while(1){
          int counter=0;
           for(int i=0;i<task;i++){
               if(currenttime%priority[i][2]!=0){
                  counter++;
               }
           }
            if (counter==task){
                currenttime++;
            }
            else{
                 break;
             }
          }

          cout<<start_time<<"-"<<currenttime<<"Idle time"<<endl;
        }

      }
        }
      }
}
