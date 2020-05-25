#include<iostream>
#include<cstdlib>
#include<cstring>
#include<fstream>
#include<iomanip>
using namespace std;
struct items
{ char name[30];
 int price;
 int profit;
 float density;
}itm[50];
void greedy(items itm[], int num, int W);
int max(int a, int b) { return (a > b)? a : b; }
void dynamicProgramming(int W, items itm[], int n)
{
 int i, w;
 int K[n + 1][W + 1];
 for (i = 0; i <= n; i++) {
 for (w = 0; w <= W; w++) {
 if (i == 0 || w == 0)
 K[i][w] = 0;
 else if (itm[i - 1].price <= w) 
 K[i][w] = max(itm[i-1].profit + K[i - 1][w - itm[i - 1].price], K[i - 1][w]);
 else
 K[i][w] = K[i - 1][w];
 }
 }
 int res = K[n][W];
 cout<<"\nMaximum Profit= "<< res<<endl;
 w = W;
 for (i = n; i > 0 && res > 0; i--)
{
 if (res == K[i - 1][w])
 continue;
 else {
 res = res - itm[i-1].profit;
 w = w - itm[i - 1].price;
 }
 }
}
void bruteforce(items itm[],int c,int n)
{
int i,j,isSelected=1,maxWt,maxProfit;
int selected[n];
int iter=2^n;
int result=0;
int temp[n];
for(i =0;i<n;i++)
temp[i]=0;
for(i=0;i<iter;i++) {
isSelected=1;
maxProfit=0;
maxWt=0;
for(j=0;j<n;j++){
if(temp[j]==1){
maxWt+=itm[j].price;
maxProfit+= itm[j].profit;
}
}
if( maxWt <= c && maxProfit>result){
for(j=0;j<n;j++)
selected[j]=temp[j];
result=maxProfit;
}
for(j=0;j<n;j++){
temp[j]=temp[j]+isSelected;
isSelected = temp[j]/2;
temp[j]=temp[j]%2;
}
}
cout<<"\nMaximum Profit="<< result<<endl;
}
void greedy( items itm[], int num, int W)
{
 int i,j, wt,var[num];
 float value;
 float totalWeight = 0, totalBenefit = 0;
items temp;
 for(i = 0; i < num; i++)
 {
 itm[i].density = float(itm[i].profit) / itm[i].price;
 var[i]=0;
 }
 for(i = 1; i < num; i++) {
 for(j = 0; j < num - i; j++) {
 if(itm[j+1].density > itm[j].density) {
 temp = itm[j+1];
 itm[j+1] = itm[j];
 itm[j] = temp;
 }
 }
 }
 int v=W;
 for(i=0;i<num && itm[i].price<=v;i++)
 {
 var[i]=1;
 v=v-itm[i].price;
 }
 for(i=0;i<num;i++)
 {
 totalWeight=totalWeight+(itm[i].price*var[i]);
 totalBenefit=totalBenefit+(itm[i].profit*var[i]);
 }
 cout<<"Maximum Profit:"<< totalBenefit<<endl;
}
int main(void)
{
 int i, j,W,num,choice;
 cout<<"\nEnter Maximum investment: ";
 cin>>W;
 char ch;
cout<<"\nEnter number of items: ";
cin>>num;
 for(i=0;i<num;i++)
 {
cout<<"\nEnter item name: ";
cin>>itm[i].name;
cout<<"\nEnter cost: ";
cin>>itm[i].price;
cout<<"\nEnter profit: ";
cin>>itm[i].profit;
cout<<"\n";
}
cout<<"\nGREEDY APPROACH:\n";
greedy(itm,num,W);
 cout<<"\nDYNAMIC PROGRAMMING:\n";
 dynamicProgramming(W,itm,num);
 cout<<"\nBRUTE FORCE APPROACH:\n";
 bruteforce(itm,W,num);

 return 0;
}
