#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<dirent.h>
#include<fcntl.h>

void list(char c,char *dn)
{
  DIR *dir;
  int cnt=0;
  struct dirent *entry;
  struct stat buff;
  
  dir=opendir(dn);
  if(dir==NULL)
  {
     printf("\n Directory %s does not found",dn);
     return;
  }
  
  switch(c)
  {
    case 'f':
              while((entry=readdir(dir))!=NULL)
	      {
		stat(entry->d_name,&buff);
		
		if(S_IFREG && buff.st_mode)
		  printf("%s\n",entry->d_name);
	      }
	      break;
   case 'n':
              while((entry=readdir(dir))!=NULL)
	      {
		cnt++;
		  printf("Total Number of Enteries=%d",cnt);
	      }
	      break;
  case 'i':
              while((entry=readdir(dir))!=NULL)
	      {
		stat(entry->d_name,&buff);
		
		if(S_IFREG && buff.st_mode)
		  printf("%s\t %d\n",entry->d_name,buff.st_ino);
	      }
	      break;
	      
  default:printf("Invalid Argument!");
  }
  closedir(dir);
}

 main()
 {
   char command[80],t1[20],t2[20],t3[2],t4[20];
   int n;
   
   system("clear");
   
   while(1)
   {
      printf("myshell$");
      fflush(stdin);
      fgets(command,80,stdin);
      
       n=sscanf(command,"%s,%s,%s,%s",t1,t2,t3,t4);
       
       switch(n)
       {
	 case 1:
	        if(!fork())
		{
		  execlp(t1,t1,NULL);
		  perror(t1);
		}
		break;
        case 2:
	        if(!fork())
		{
		  execlp(t1,t1,t2,NULL);
		  perror(t1);
		}
		break;		
	case 3:
	       if(strcmp(t1,"list")==0)
	       {
		 list(t2[0],t3);
	       }
	       else
		{
		  execlp(t1,t1,t2,t3,NULL);
		  perror(t1);
		}
		break;	
	 case 4:
	        if(!fork())
		{
		  execlp(t1,t1,t2,t3,t4,NULL);
		  perror(t1);
		}
       }
   }
 }
		
