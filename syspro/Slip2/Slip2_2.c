#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct process_info
{
	char pname[20];
	int at,at1,bt,bt1,ct,cnt;
	struct process_info *link;
}NODE;

NODE *first,*last;
int nop,ts;

void get_process_info()
{
	NODE *p;
	int i;

	printf("Enter no.of processes:");
	scanf("%d",&nop);

	printf("Enter time slice:");
	scanf("%d",&ts);

	for(i=0;i<nop;i++)
	{
		p = (NODE*)malloc(sizeof(NODE));
		
		printf("Enter process name:");
		scanf("%s",p->pname);

		printf("Enter arrival time:");
		scanf("%d",&p->at);

		printf("Enter CPU burst time:");
		scanf("%d",&p->bt);

		p->at1 = p->at;
		p->bt1 = p->bt;

		p->cnt = 0;
		
		p->link = NULL;

		if(first==NULL)
			first = p;
		else
			last->link = p;
		last = p;
	}
}

void print_output()
{
	NODE *p;
	float avgTAT=0,avgWT=0;
	int tat,wt;

	printf("-------------------------------------------------\n");
	printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
	printf("-------------------------------------------------\n");

	p = first;
	while(p!=NULL)
	{
		tat = p->ct - p->at;
		wt = tat - p->bt;
	
		printf("%s\t%d\t%d\t%d\t%d\t%d\n",
				p->pname,p->at,p->bt,p->ct,tat,wt);

		avgTAT+=tat;
		avgWT+=wt;
		p=p->link;
	}
	
	printf("-------------------------------------------------\n");
	printf("Avg TAT=%f\tAvg WT=%f\n",avgTAT/nop,avgWT/nop);
}


void sort()
{
	NODE *p,*q;

	p = first;
	while(p->link!=NULL)
	{
		q=p->link;

		while(q!=NULL)
		{
			if(p->at1 > q->at1)
			{
				int t;
				char tname[20];

				strcpy(tname,p->pname);
				strcpy(p->pname,q->pname);
				strcpy(q->pname,tname);

				t = p->at;
				p->at = q->at;
				q->at = t;

				t = p->at1;
				p->at1 = q->at1;
				q->at1 = t;

				t = p->bt;
				p->bt = q->bt;
				q->bt = t;

				t = p->bt1;
				p->bt1 = q->bt1;
				q->bt1 = t;

				t = p->cnt;
				p->cnt = q->cnt;
				q->cnt = t;

				t = p->ct;
				p->ct = q->ct;
				q->ct = t;
			}
			q=q->link;
		}
		p=p->link;
	}
}

void print_input()
{
	NODE *p;

	printf("-------------------------------\n");
	printf("Process\tAT\tBT\n");
	printf("-------------------------------\n");

	p = first;
	while(p!=NULL)
	{
		printf("%s\t%d\t%d\n",p->pname,p->at1,p->bt1);
		p=p->link;
	}
}

int time;

int is_arrived()
{
	NODE *p;

	p = first;
	while(p!=NULL)
	{
		if(p->at1<=time && p->bt1!=0)
			return 1;
		p=p->link;
	}

	return 0;
}

struct gantt_chart
{
	int start;
	char pname[20];
	int end;
}s[100],s1[100];

int k;

void rr()
{
	NODE *p;
	int finish=0,prev=0;

	while(finish!=nop)
	{
		if(!is_arrived())
		{
			time++;
			s[k].start = prev;
			strcpy(s[k].pname,"*");
			s[k].end = time;
			k++;
			prev = time;
		}
		else
		{
			if(first->at1>time || first->bt1==0)
			{
				while(1)
				{
					p = first;
					if(p->at1<=time && p->bt1!=0) break;
					first=first->link;
					last->link = p;
					last=p;
					last->link = NULL;
				}
			}
			if(first->at1<=time && first->bt1!=0)
			{
				if(first->bt1<=ts)
				{
					time+=first->bt1;
					first->bt1=0;
				}
				else
				{
					time+=ts;
					first->bt1-=ts;
				}

				first->ct=time;
			
				s[k].start = prev;
				strcpy(s[k].pname,first->pname);
				s[k].end = time;
				k++;

				prev = time;

/*				if(first->cnt==0 && first->bt1==0)
				{
					first->cnt++;
					first->at1 = first->ct+2;
					first->bt1 = rand()%10+1;
					first->bt += first->bt1;
				}

				if(first->cnt==1 && first->bt1==0)
				{
					finish++;
				}*/

				if(first->bt1==0) finish++;
				
				p = first;
				first = first->link;
				last->link = p;
				last = p;
				last->link = NULL;
			}
		}
		print_input();
	}
}

void print_gantt_chart()
{
	int i,j=0;

	s1[0] = s[0];

	for(i=1;i<k;i++)
		if(strcmp(s[i].pname,s1[j].pname)==0)
			s1[j].end = s[i].end;
		else
			s1[++j] = s[i];

	printf("0");
	for(i=0;i<=j;i++)
	{
		int m = s1[i].end - s1[i].start;

		for(k=0;k<m/2;k++)
			printf("-");

		printf("%s",s1[i].pname);
		
		for(k=0;k<(m+1)/2;k++)
			printf("-");

		printf("%d",s1[i].end);
	}
}

void main()
{
	system("clear");
	get_process_info();
	sort();
	rr();
	print_output();
	print_gantt_chart();
}
