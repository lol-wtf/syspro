/************************************************************

Write a command line program for line editor. The file to be edited is taken as command line argument; an empty file is opened for editing if no argument is supplied. It should display a ‘$’ prompt to accept the line editing commands.
Implement the following commands:
   i. a
   ii. s
   iii. c n1 n2
   iv. c n1 n2 n3
**********************************************************/
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
void save()
{
printf("\n enter file name to save \n");
scanf("%s",fname);
fp=fopen(fname,"w");
 if(fp==NULL)
   {
    printf("\n error in file opening");
     return;
   }
 else
   {
      temp=start;
     while(temp!=NULL)
      {
      fputs(temp->line,fp);
       temp=temp->next;        
      }
   }
}
void copy(int m,int n)
{
  int x=1;
  temp=cur=NULL;
  if(m>flag || m<0 || n>(flag+1)||n<0)
   {
    printf("\n Error in copy..\n");
    return;
   }
  for(cur=start,x=1;x<m;x++,cur=cur->next);
  temp=(struct node *)malloc(sizeof(struct node)); 
  strcpy(temp->line,cur->line);
  temp->next=NULL;
  for(cur=start,x=1;x<n-1;x++,cur=cur->next);
  if(n==1)
  {
  temp->next=start;
  start=temp;
  }
  else
  {
   temp->next=cur->next;
   cur->next=temp;
  }
  flag++;
}
void mncopy(int a,int b,int c)
  {
   if(b<c)
   {
     while(a<b)
     copy(a++,c++);
   }
   else
   {
    while(a<b)
     {
     copy(a,c);
     a+=2;
     b++;
     c++;
     }
   }
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
if(strcmp(t[0],"c")==0 && strcmp(t[3],"\0")==0)
copy(i,j);
else
if(strcmp(t[0],"c")==0 && strcmp(t[3],"\0")!=0)
mncopy(i,j,k);
}
return(0);
}

/*
Output:-
[root@localhost ~]# ./a.out

file empty.txt is opening

$a
enter line to append 
India

$a
enter line to append 
China

$a
enter line to append 
America

$a
enter line to append 
China Town

$a
enter line to append 
Asia

$p

File Name is empty.txt
1  India
2  China
3  America
4  China Town
5  Asia


$s
enter file name to save 
Country


$p

 File Name is Country
1  India
2  China
3  America
4  China Town
5  Asia


$c 2 4

$p

 File Name is Country
1  India
2  China
3  America
4  China
5  China Town
6  Asia


$c 2 3 4

$p
File Name is Country
1  India
2  China
3  America
4  China
5  China
6  China Town
7  Asia


$e
[root@localhost ~]# 



