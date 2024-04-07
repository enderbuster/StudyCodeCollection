//implement pstree -p,-n,-V
//-p,--show-pids:print pid
//-n,--numeric-sort,sort in ascending order
//-V,--version print info about version
#include<unistd.h>
#include<stdio.h>
#include<getopt.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>

#define MAX_OPTION_NUMBER 3 
#define MAX_PID_NAME_LENGTH 50
#define MAX_PROC_NUMBER 1000 
typedef struct proc_info proc_info;
typedef struct node node;

node * new_node(pid_t);
node * add_next(node *,pid_t);
node * add_child(node *,pid_t);
node * init_tree();
void create_tree(node *,int ,proc_info *);
void print_tree(node *,int,proc_info *,int);
char * get_proc_name(pid_t,int ,proc_info *);

struct proc_info{
	pid_t pid;
	pid_t ppid;
	char pid_name[MAX_PID_NAME_LENGTH];
};

struct node{
	//next is the siblings;
	pid_t pid;
	struct node *child;
	struct node *next;
};
//assign the space a node need
node * new_node(pid_t pid){
       	node *new_node=malloc(sizeof(node));
	if(new_node){
		new_node->child=NULL;
		new_node->next=NULL;
		new_node->pid=pid;
	}

	return new_node;
}
//initial the root node,whose pid=0
node * init_tree(){
	return new_node(0);
}
node * add_child(node *node,pid_t pid){
	if(node==NULL)
		return NULL;
	if(node->child)
		return add_next(node,pid);
	else
		return (node->child=new_node(pid));
}

node * add_next(node *n,pid_t pid){
	if(n==NULL)
		return NULL;
	while(n->next)
		n=n->next;
	n->next=new_node(pid);
	return n->next;
}
//create tree,read from the proc_list
void create_tree(node * root,int proc_num,proc_info * proc_list){
	int i=0;
	for(;i<proc_num;i++){
		if(root->pid==proc_list[i].ppid){
			node * child_ptr=add_child(root,proc_list[i].pid);
			create_tree(child_ptr,proc_num,proc_list);
		}
	}
}

//get the proc_name through pid
char * get_proc_name(pid_t pid,int proc_num,proc_info * proc_list){
	int i=0;
	for(;i<proc_num;i++){
		if(pid==proc_list[i].pid){
			char *dest;
			dest=(char*)malloc(strlen(proc_list[i].pid_name)+1);
			strcpy(dest,proc_list[i].pid_name);
			printf("%s",dest);
			return dest;
		}
	}
}
//print the pid tree
void print_tree(node * root,int proc_num,proc_info * proc_list,int depth){
	if(root==NULL){
		return;
	}
	int i=0;
	for(;i<depth;i++){
		printf("  ");
	}
	// somehow the return value of get_proc_name seems not to be a string
	// segmentation fault happens,i cant figure out why
//	char *s=get_proc_name(root->pid,proc_num,proc_list);
//	printf("%d\n",(int)strlen(s));
//	printf("%s\n",s);
	get_proc_name(root->pid,proc_num,proc_list);
	printf("(%d)\n",root->pid);
	print_tree(root->child,proc_num,proc_list,depth+1);
	print_tree(root->next,proc_num,proc_list,depth);
		
}
int main(int argc,char *argv[]){
	while(1){
		static struct option long_options[]=
		{
			{"show-pids",no_argument,0,'p'},
			{"numeic-sort",no_argument,0,'n'},
			{"version",no_argument,0,'V'},
			{0,0,0,0}
		};
		static int option_list[MAX_OPTION_NUMBER];	
		int rc=getopt_long(argc,argv,"pnV",long_options,NULL);
		
		//detect the end of the options
		if(rc==-1)
			break;
		//check if the same option is in command
		//like -p -p,or -V --version
		int current_index=optind-2;
		int current_option_num=optind-1;
		option_list[current_index]=rc;
		int i=0;
		for(;i<current_option_num-1;i++){
			if(rc==option_list[i]){
				printf("have two or more same input optipn!!!\n");
				abort();
			}
		}

		switch(rc)
		{
			case 'p':
				printf("option -p\n");
				break;
			case 'n':
				printf("option -n\n");
				break;
			case 'V':
				printf("option -V\n");
				break;
			case '?':
				printf("ur input command is wrong!!!\n");
			default:
				abort();
		}

	}
	// open the dir /proc and get all the dir that is a number
	DIR *dir;
	dir=opendir("/proc");
	if(dir==NULL){
		printf("cant open dir!!!\n");
		exit(1);
	}
	struct dirent *dir_ptr;
	struct proc_info proc_list[MAX_PROC_NUMBER];
	int index=0;
	while((dir_ptr=readdir(dir))!=NULL){
		pid_t pid=atoi(dir_ptr->d_name);
		if(pid!=0){
			proc_list[index].pid=pid;
			index++;
		}
	}
	closedir(dir);
	//get the dir of every /proc/[pid]/stat file to read info
	int i=0;
	char stat_dir[MAX_PROC_NUMBER][MAX_PID_NAME_LENGTH+11];
	for(;i<index;i++){
		sprintf(stat_dir[i],"/proc/%d/stat",proc_list[i].pid);
	}
	//open and read /proc/pid/stat
	i=0;
	for(;i<index;i++){
		FILE* fp;
		fp=fopen(stat_dir[i],"r");
		//there is a fking process in the form of something like this,((sd-pam)),oh my god
	//	fscanf(fp,"%*d (%[^)])  %*s %d",proc_list[i].pid_name,&proc_list[i].ppid);
		fscanf(fp,"%*d %s %*s %d",proc_list[i].pid_name,&proc_list[i].ppid);
		int len=strlen(proc_list[i].pid_name);
		int j=0;
		for(;j<len;j++){
			proc_list[i].pid_name[j]=proc_list[i].pid_name[j+1];
		}
		proc_list[i].pid_name[len-2]='\0';
		fclose(fp);
	}
	//test if the dir has been loaded into proc_list[index].pid
	i=0;
	//for(;i<index;i++){
	//	printf("pid:%d\n",proc_list[i].pid);
	//	printf("ppid:%d\n",proc_list[i].ppid);
	//	printf("pid_name:%s\n",proc_list[i].pid_name);
	//}
	// since we have already get the data.lets create a tree!
	node * root;
	root=init_tree();
	create_tree(root,index,proc_list);
	print_tree(root,index,proc_list,0);


	return 0;
}
