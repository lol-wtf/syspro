#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct process_info
{
	char pname[20];
	int at,at1,bt,bt1,ct,cnt,p;
	struct process_info *link;
}NODE;

NODE *first,*last;
int nop;

void get_process_info()
{
	NODE *p;
	int i;

	printf("Enter no.of processes:");
	scanf("%d",&nop);

	for(i=0;i<nop;i++)
	{
		p = (NODE*)malloc(sizeof(NODE));
		
		printf("Enter process name:");
		scanf("%s",p->pname);

		printf("Enter arrival time:");
		scanf("%d",&p->at);

		printf("Enter CPU burst time:");
		scanf("%d",&p->bt);

		printf("Enter priority:");
		scanf("%d",&p->p);

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
	printf("Process\tAT\tBT\tP\tCT\tTAT\tWT\n");
	printf("-------------------------------------------------\n");

	p = first;
	while(p!=NULL)
	{
		tat = p->ct - p->at;
		wt = tat - p->bt;
	
		printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
				p->pname,p->at,p->bt,p->p,p->ct,tat,wt);

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

				t=p->p;
				p->p=q->p;
				q->p=t;
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
	printf("Process\tAT\tBT\tP\n");
	printf("-------------------------------\n");

	p = first;
	while(p!=NULL)
	{
		printf("%s\t%d\t%d\t%d\n",p->pname,p->at1,p->bt1,p->p);
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

NODE * get_p()
{
	NODE *p,*minp;
	int min=999;

	p=first;
	while(p!=NULL)
	{
		if(p->at1<=time && p->bt1!=0 && p->p<min)
		{
			min = p->p;
			minp = p;
		}
		p=p->link;
	}
	return minp;
}

struct gantt_chart
{
	int start;
	char pname[20];
	int end;
}s[100],s1[100];

int k;

void pnp()
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
			p = get_p();
			
			time+=p->bt1;
			p->ct = time;
			p->bt1 = 0;

			s[k].start = prev;
			strcpy(s[k].pname,p->pname);
			s[k].end = time;
			k++;

			prev = time;

/*			if(p->cnt == 0)
			{
				p->cnt++;

				p->bt1 = rand()%10+1;
				p->at1 = p->ct+2;
				p->bt += p->bt1;
			}

			if(p->cnt == 1 && p->bt1==0)*/
			{
				finish++;
			}
		}

		sort();
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
	pnp();
	print_output();
	print_gantt_chart();
}

	










	



















	
	
		














	
		
	
		
				
			
































































			
			




























































			



















































		


	


				
				
				




























































	

































	






























		














	







































