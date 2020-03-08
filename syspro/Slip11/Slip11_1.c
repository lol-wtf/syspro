/********************************************************
Write a command line program for line editor. The file to be edited is taken as command line argument; an empty file is opened for editing if no argument is supplied. It should display a ‘$’ prompt to accept the line editing commands.
Implement the following commands:
   i. a
  ii. p
 iii. p m n
 iv. i n
***********************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char fname[20];
     struct node
     {
      char line[80];
      struct node *prev,*next;
     }*start,*cur,*temp,*newn;
   FILE *fp;
   int arg=0,flag=0;
   char ch;
void display(int,int);
void load()
{
if(arg==1)
{
 printf("\n file empty.txt is opening\n"); 
 fp=fopen(fname,"w");
 if(fp==NULL)
   {
   printf("\n error in opening file\n\n");
   return;
   }
start=NULL;
}
else
{
 printf("\n File %s is opeing\n",fname);
fp=fopen(fname,"r");
if(fp==NULL)
  {
  printf("Error in opening file");
  return;
  }
     while(!feof(fp))
      {
      newn=(struct node *)malloc(sizeof(struct node));
      fgets(newn->line,80,fp);
      newn->next=NULL;
      if(start==NULL)
       start=cur=newn;
      else
       {
         cur->next=newn;
         newn->prev=cur;
         cur=cur->next;
         }
      flag++; 
    }
}
fclose(fp);
}
void append()
{
int y;
newn=NULL;
newn=(struct node *)malloc(sizeof(struct node));
y=0;
printf("\nenter line to append \n");
do
{
ch=getc(stdin);
newn->line[y]=ch;
y++;
}while(ch!='\n');
newn->next=NULL;
if(start==NULL)
    start=newn;
 else
   {
   temp=start;
    while(temp->next!=NULL)
        temp=temp->next;
        temp->next=newn;
        newn->prev=temp;
   }
  flag++;
}
void display(int m,int n)
{
int x=0,cnt,i;
cur=start;
if(m<0)
{
printf("\n error in display: lower limit exceeds...\n");
return;
}
if(n>flag)
{
printf("\n error in display: upper limit exceeds...\n");
return;
}
printf("\n File Name is %s\n",fname);
while(cur!=NULL)
{
if(x>=m-1 && x<n)
{
printf("%d  ",x+1);
puts(cur->line);
}
cur=cur->next;
x++;
continue;
}
if(n<0)
{
cnt=m+n;
temp=NULL;
 if(cnt>1)
  { 
 for(i=1,temp=start;i<m;i++,temp=temp->next);
   while(i>=cnt)
       {
        temp=temp->prev;
        i--;
       }
       i++;
     temp=temp->next;
   for(;i<m;i++,temp=temp->next)
       {
       printf("%d  ",i);
       puts(temp->line);
       }     
 }
 else
 {
for(i=1,temp=start;i<m;i++,temp=temp->next)
       {
       printf("%d  ",i);
       puts(temp->line);
       }     
 
 }  
}
}
void insert(int n)
{ char ch;
   int x=0;
  cur=temp=newn=NULL;
  if(n<0)
     {
        printf("\n error in display: lower limit exceeds...\n");
         return;
     }
      if(n>flag+1)
        {
         printf("\n error in display: upper limit exceeds...\n");
         return;
        }
  newn=(struct node *)malloc(sizeof(struct node));
 printf("\nenter new line to insert at line number %d \n",n);
     do{
         ch=getc(stdin);
         newn->line[x]=ch;
         x++;
       }while(ch!='\n');
  newn->next=NULL;
      if(n==1)
      {
       newn->next=start;
       start=newn;
      }
     else
     {
      cur=start;
      x=1;
      while(x<n-1)
         {
         cur=cur->next;
         x++;
         }
      temp=cur->next;
      cur->next=newn;
      newn->next=temp;
     }    
   flag++; 
}
int main(int argc,char *argv[])
{
 char cmd[15],t[4][10];
 int i,j,k;
 strcpy(t[0],"\0");
 strcpy(t[1],"\0");
 strcpy(t[2],"\0");
 strcpy(t[3],"\0");
 arg=argc;
 if(argc>1)
 strcpy(fname,argv[1]);
 else
 strcpy(fname,"empty.txt");
 load();
 while(1)
 {
 printf("\n$");
 gets(cmd);
 //scanf("%s",cmd);
 i=j=k=0;
 fflush(stdin);
 fflush(stdout);
 strcpy(t[0],"\0");
 strcpy(t[1],"\0");
 strcpy(t[2],"\0");
 strcpy(t[3],"\0");
 sscanf(cmd,"%s%s%s%s",t[0],t[1],t[2],t[3]);
 i=atoi(t[1]);
 j=atoi(t[2]);
 k=atoi(t[3]);
 if(strcmp(t[0],"e")==0)break;
 else
 if(strcmp(t[0],"s")==0)
 save();
 else
 if(strcmp(t[0],"a")==0)
 append();
 else
 if(strcmp(t[0],"p")==0)
        {
         if(strcmp(t[1],"\0")==0)
         display(1,flag);
         else
         display(i,j); 
        }
 
else
if(strcmp(t[0],"i")==0)
insert(i);

}
return(0);
}

/*Output:-
[root@localhost ~]#./a.out
file empty.txt is opening

$a
enter line to append 
Syspro

$a
enter line to append 
Tcs

$a
enter line to append 
Java

$a
enter line to append 
Computer Networking

$a
enter line to append 
PHP

$p
File Name is empty.txt
1  Syspro
2  Tcs
3  Java
4  Computer Networking
5  PHP

$p 1 3
File Name is empty.txt
1  Syspro
2  Tcs
3  Java

$i 6
enter new line to insert at line number 6 
OOSE

$p
File Name is empty.txt
1  Syspro
2  Tcs
3  Java
4  Computer Networking
5  PHP
6  OOSE
$e
[root@localhost ~]#
*/

