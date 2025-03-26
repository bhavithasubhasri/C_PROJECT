#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
typedef struct stock
{
int code,quan;
char item_name[100];
float cost;

}s;
typedef struct dup//This function is used to copy item name, at billing
{
char dup_name[100];
}d;
int z;//used to allocate size
void search()//This function is used for searching the data of the product
{
printf("\t\t\t\t\tSEARCH ITEM\n\n");
int code,count=0;
printf("Enter the code of item to seacrh\n ");
scanf("%d",&code);
FILE *fp;
fp=fopen("billing.txt","r");

s stock;
while(fread(&stock,sizeof(s),1,fp))
{
if(code==stock.code)
{
printf("CODE\t\tITEM NAME\tQUANTITY\tCOST\n");

printf("%d\t\t%s\t\t%d\t\t%0.2f\n",stock.code,stock.item_name,stock.quan,stock.cost);

count=1;
break;
}
}
fclose(fp);
if(count!=1)
{
printf("The item was not found\n");
}
}

void create()//The create function is used when the stock was empty
{
printf("\t\t\t\t\tCREATE STOCK\n\n");
FILE *fp;
int i;// i used as LCV
s *stock;
fp=fopen("billing.txt","w");
printf("Enter how many items\n");



scanf("%d",&z);
stock=(s *)calloc(z,sizeof(s));
for( i=0;i<z;i++)
{
printf("Enter code of the item %d:\n",i+1);
scanf("%d",&stock[i].code);
printf("Enter the name of item %d:\n",i+1);
scanf(" %[^\n]s",stock[i].item_name);
printf("Enter the cost of item %d:\n",i+1);
scanf("%f",&stock[i].cost);
printf("Enter the quantity of item %d:\n",i+1);
scanf("%d",&stock[i].quan);
fwrite(&stock[i],sizeof(s),1,fp);
}
fclose(fp);
}

void update(int a,int q)//Update function is used for updating stock.Here a,q isused to copy code and quantity of an item from customer purpose
{
int code,count=0;
if(q==0)
{
printf("\t\t\t\t\tUPDATE STOCK\n\n");

printf("Enter the code of item to seacrh\n ");
scanf("%d",&code);
}
FILE *fp1;//fp1 is used as temporary file


fp1=fopen("removing.txt","w");
FILE *fp;
fp=fopen("billing.txt","r");
s stock;
while(fread(&stock,sizeof(s),1,fp))
{
if(code==stock.code || a==stock.code)
{
if(q!=0)
{
stock.quan=stock.quan-q;
}
else if(q==0)
{
printf("The item details are\n");
printf("ITEMNAME:%s\tCOST:%0.2f\tQUANTITY:%d\n",stock.item_name,stock.cost,stock.quan);
printf("Enter the cost of item :\n");
scanf("%f",&stock.cost);
printf("Enter the quantity of item :\n");
scanf("%d",&stock.quan);
}
fwrite(&stock,sizeof(s),1,fp1);

count=1;
}
else
{
fwrite(&stock,sizeof(s),1,fp1);
}
}
fclose(fp);
fclose(fp1);
if(count)
{
fp1=fopen("removing.txt","r");
fp=fopen("billing.txt","w");
while(fread(&stock,sizeof(s),1,fp1))
{
fwrite(&stock,sizeof(s),1,fp);
}

}
else
{
printf("The item was not found\n");
}
fclose(fp);
fclose(fp1);
}

void Insert()//Insert function is used to insert a new product
{
printf("\t\t\t\t\tINSERT STOCK\n\n");
FILE *fp;
int n;
s *stock;
fp=fopen("billing.txt","a");
printf("Enter how many items\n");
scanf("%d",&n);
n=z+n;
stock=(s *)realloc(stock,n*sizeof(s));
for( z;z<n;z++)
{
printf("Enter code of the item %d:\n",z+1);
scanf("%d",&stock[z].code);
printf("Enter the name of item %d:\n",z+1);
scanf(" %[^\n]s",stock[z].item_name);
printf("Enter the cost of item %d:\n",z+1);
scanf("%f",&stock[z].cost);
printf("Enter the quantity of item %d:\n",z+1);
scanf(" %d",&stock[z].quan);
fwrite(&stock[z],sizeof(s),1,fp);
}
fclose(fp);
}

void Remove()//The delete function for deleting the old product
{
printf("\t\t\t\t\tREMOVE ITEM\n\n");
int code,count=0;
printf("Enter the code of item to remove\n ");
scanf("%d",&code);
FILE *fp1;// fp1 is used as temporary file
fp1=fopen("removing.txt","w");
FILE *fp;
fp=fopen("billing.txt","r");
s stock;
while(fread(&stock,sizeof(s),1,fp))
{
if(code==stock.code)
{

count=1;
}
else
{
fwrite(&stock,sizeof(s),1,fp1);
}
}

fclose(fp);
fclose(fp1);
if(count)
{
fp1=fopen("removing.txt","r");
fp=fopen("billing.txt","w");
while(fread(&stock,sizeof(s),1,fp1))
{
fwrite(&stock,sizeof(s),1,fp);

}
}
else
{
printf("The item was not found\n");
}
fclose(fp);
fclose(fp1);
}

void display(int c)//The display function is used for displaying data.c is used to control if the statement
{
if(c==0)
printf("\t\t\t\tDISPLAY STOCK\n\n");
FILE *fp;
fp=fopen("billing.txt","r");
s stock;
printf("\t\t\tCODE\t\tITEM NAME\tQUANTITY\tCOST\n");
while(fread(&stock,sizeof(s),1,fp))
{

printf("\t\t\t%d\t\t%s\t\t%d\t\t%0.2f\n",stock.code,stock.item_name,stock.
quan,stock.cost);
}
fclose(fp);
}



int main()
{
int ch,pur,c,q;//ch,pur are used to read choice,purpose.q is used to copy quantity at customer purpose
printf("\t\t\t");
for(int i=0;i<50;i++)
printf("*");
printf("\n");
printf("\t\t\t\t\tWELCOME TO SUPERMARKET\t\t\t\n");
printf("\t\t\t");
for(int i=0;i<50;i++)
printf("*");
printf("\n");
menu :
printf("\t\t1->ADMIN PURPOSE\n\t\t2->CUSTOMER PURPOSE\n\tEnter the choice amoung this two\n");
scanf("%d",&pur);
q=0;
c=0;
if(pur==1)
{
while(1)

{
printf(" 1->create stock when the stock is empty\n 2->Update stock\n 3->Insert new stock\n 4->Remove old product\n 5->Display\n 6->search\n 7->goto menu\n 8->Exit\n Enter the choice amoung this seven\n");
scanf("%d",&ch);
switch(ch)
{



case 1: create();
break;
case 2: update(c,q);
break;
case 3: Insert();
break;
case 4: Remove();
break;
case 5: display(c);
break;
case 6: search();
break;
case 7: goto menu;
break;
case 8: exit(0);
break;
default: printf("Entered wrong choice\n");
}
}
}
if(pur==2)
{
system("cls");
printf("\t\t\t");
for(int i=0;i<50;i++)
printf("_");
printf("\n");
printf("\t\t\t\t\tSUPER MARKET BILLING");
printf("\n\t\t\t");
for(int i=0;i<50;i++)
printf("_");
printf("\n");
int k=1,j=1,a[100],quantity[100],z,code,count,i=1;
//a[100],cost[100] is used for copying the code and cost
float cost[100],total_cost; //total_cost is used for printing total cost

s stock;
d *dup;
dup=(d *)calloc(k,sizeof(d));
c++;
printf("The details of the items are\n");
display(c);
while(1)
{
printf("Enter the code of item\n ");
scanf("%d",&code);
FILE *fp;
fp=fopen("billing.txt","r");

count=0;

while(fread(&stock,sizeof(s),1,fp))
{
if(code==stock.code)
{
printf("The item details are\n");


printf("CODE:%d\tITEMNAME:%s\tCOST:%0.2f\t",stock.code,stock.item_name,stock.cost);

count=1;
a[k]=stock.code;
printf("Enter quantity :");
scanf("%d",&quantity[k]);
if(quantity[k]<=stock.quan)
{
q=quantity[k];
cost[k]=quantity[k]*stock.cost;
printf("Cost=%0.2f\n",cost[k]);

update(stock.code,q);

k++;
dup=(d *)realloc(dup,k*sizeof(d));
while(i<k)
{

strcpy(dup[i].dup_name,stock.item_name);
i++;
}

}
else

{

printf("Out of stock We had only%d\n",stock.quan);
cost[k]=0;
}
break;
}
}
if(count==0)
{
printf("You have entered wrong code\n");
}

printf("Press 0 if you don't want to add another item or else press 1\n");
scanf("%d",&z);
fclose(fp);

if(z==0)
break;
}
system("cls");
printf("\t\t\t");
for(int i=0;i<55;i++)
printf("-");
printf("\n");
printf("\t\t\t\t\t\tRECEIPT\t\t\n");

printf("\t\t\tDATE:%s\t\t\tTIME:%s\n\t\t\t",__DATE__,__TIME__);//DATE,TIME are macros

for(int i=0;i<55;i++)
printf("-");
printf("\n");
printf("\t\t\tITEM NAME\t\tQUANTITY\t\tCOST\n");


while(j<k)
{

printf("\t\t\t%s\t\t\t%d\t\t\t%0.2f\n",dup[j].dup_name,quantity[j],cost[j]);

total_cost+=cost[j];
j++;
}
printf("\t\t\t");
for(int i=0;i<55;i++)
printf("-");
printf("\n");
printf("\t\t\t\t\t\tPRICE\t\t\t:%0.2f\n\t\t\t",total_cost);
total_cost+=(total_cost*18)/100;
for(int i=0;i<55;i++)
printf("-");
printf("\n");
printf("\t\t\t\t\tGRAND TOTAL WITH 18%%GST\t:%0.2f\n\t\t\t",total_cost);
for(int i=0;i<55;i++)
printf("-");
printf("\n");
printf("\t\t\t\t\tTHANKYOU!!VISIT AGAIN\n\n");
goto menu;
}
return(0);
}
 