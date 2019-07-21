/*
	Project 3
	Hale Þahin
	150116841
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct course1{
	char course_name[20];
	int color;
	int colorx; // white = -1, grey = 0, black = 1 (for FS)
	struct course1 *nextPtr;
	struct course2 *nextCourse;
};

struct course2{
	char course_name[20];
	struct course2 *nextPtr;
};

void display(struct course1 *show);
void ReadFromFile();
void ReadFromFile1();
int insert(struct course1 ** header, char *x);
void insert1(struct course2 ** header1, char *x);
struct course1 * search(struct course1 *header, char *x);
void DFS(struct course1 *head);
void printDFS();

struct course1 *header = NULL;
char templine[300];
FILE *file;

int main(){
	ReadFromFile();
	ReadFromFile1();
	display(header);
	DFS(header);
	printDFS();
	return 0;
}

void ReadFromFile(){
	file = fopen("input1.txt" , "r");
	if(file){
		char line[300];
		while(fgets(line, sizeof line, file)){
			char *student;
			char *course;
			student = strtok(line, "\n");
			student = strtok(line, ":");
			student = strtok(NULL, ":");
			course = strtok(student, ",");
			
			while(course){
				insert(&header,course);
				course = strtok(NULL, ",");	
			}
		}
	}
	fclose(file);
}


void ReadFromFile1(){
	struct course1 *temp;
	file = fopen("input1.txt" , "r");
	if(file){
		char line[300];
		while(fgets(line, sizeof line, file)){
			strcpy(templine,line);
			temp=header;
			char *student;
			char *course;
			
	
			while(temp){
				strcpy(line,templine);
				student = strtok(line, "\n");
				student = strtok(line, ":");
				student = strtok(NULL, ":");
				course = strtok(student, ",");		
				if(strstr(templine,temp->course_name)){
					while(course){
						if(strcmp(temp->course_name,course)!=0)
							insert1(&(temp->nextCourse),course);	
						course = strtok(NULL, ",");
				//	printf("\n%s\n",temp);
				}
				}
				temp=temp->nextPtr;	
			}
			
		}
	}
	fclose(file);	
}

struct course1 * search(struct course1 *header, char *x){
	while(header){
		if(strcmp(header->course_name,x)==0)
			
			return header;
		header=header->nextPtr;
	}
	printf("Not found.");
	return NULL;
}

void DFS(struct course1 *head){
	int i=0,a=0;
	struct course1 *temp,*temp1;
	while(head){
		if(head->nextCourse){
			temp=search(header,head->nextCourse->course_name);
		}
		else{
			head->colorx=1;
			i++;
			a=0;
			temp1=header;
			while(a<i){
				temp1=temp1->nextPtr;
				a++;
			}
			head=temp1;
			continue;
		}
		if(head->color == temp->color){
		//	printf("\n\n%s->%d ------- %s->%d",head->course_name,head->color,temp->course_name,temp->color);
			if(temp->colorx != 1)
				temp->color++;
			else{
				head->color+=1;
			}	
		//	printf("\n%s->%d ------- %s->%d",head->course_name,head->color,temp->course_name,temp->color);
			DFS(temp);     //recursive call
		}else{
			head->colorx++;
			head->nextCourse=head->nextCourse->nextPtr;
		}
		
		
	}
}


int insert(struct course1 ** header, char *x){

	struct course1 *newcourse, *temp, *prev;

	// create course to insert and assign values to its fields
	newcourse=(struct course1*)malloc(sizeof(struct course1));
	strcpy(newcourse->course_name,x);
	newcourse->nextPtr=NULL;
	newcourse->nextCourse=NULL;
	newcourse->color=0;
	newcourse->colorx=-1;
	// if LL empty
	if (*header == NULL) 
		*header=newcourse;
	// if LL not empty
	else {
		temp=*header;
		while (temp != NULL && strcmp(temp->course_name, newcourse->course_name) < 0) {
			prev=temp;
			temp=temp->nextPtr;
		}

		if (temp!=NULL && strcmp(temp->course_name, newcourse->course_name) == 0) { 
			return 0;
		}

		// insert course in a sorted fashion
		if (temp!=NULL)
			newcourse->nextPtr=temp;

		// if value to insert is the least in LL then have header point to course
		if (temp==*header)
			*header=newcourse;
		// otherwise insert course in correct position
		else 
			prev->nextPtr=newcourse;
	}
	
	return 1;
	
}  

void insert1(struct course2 ** header1, char *x){

	struct course2 *newcourse, *temp, *prev;

	// create course to insert and assign values to its fields
	newcourse=(struct course2*)malloc(sizeof(struct course2));
	strcpy(newcourse->course_name,x);
	newcourse->nextPtr=NULL;
	// if LL empty
	if (*header1 == NULL) 
		*header1=newcourse;
	// if LL not empty
	else {
		temp=*header1;
		while (temp != NULL && strcmp(temp->course_name, newcourse->course_name) < 0) {
			prev=temp;
			temp=temp->nextPtr;
		}

		if (temp!=NULL && strcmp(temp->course_name, newcourse->course_name) == 0) { 
			return;
		}

		// insert course in a sorted fashion
		if (temp!=NULL)
			newcourse->nextPtr=temp;

		// if value to insert is the least in LL then have header point to course
		if (temp==*header1)
			*header1=newcourse;
		// otherwise insert course in correct position
		else 
			prev->nextPtr=newcourse;
	}
		
}

void display(struct course1 *show){
	struct course2 *show1=NULL;
	while(show){
	show1=show->nextCourse;
		printf("%s -> ",show->course_name);
		
		printf("%s",show1->course_name);
			show1=show1->nextPtr;
		while(show1){
			printf("-%s",show1->course_name);
			show1=show1->nextPtr;
		}
		printf("\n");
		show=show->nextPtr;
	}
}

void printDFS(){
	printf("\n\n");
	int i=0;
	int counter=0;
	int c = 0;
	struct course1 *show = header;
	int number=0;
	while(show){  //this will give the number of courses in show list
		show=show->nextPtr;
		number++;	
	}//take a loop until visit all courses in the show
	while(counter<number){
	printf("\nFinal Exam Period %d => ",i); //open a new period
	c = 0; //this value is for, if it is the first course to control "," in between courses
	show=header; 
	while(show){
				if(show->color==i){	
				if(c==0){
					printf("%s",show->course_name); //first course at ith period
					c++;
					counter++;//number of visited course
				}else{
				printf(",%s",show->course_name);//second and the rest course at ith period
				counter++;	}	}
		show=show->nextPtr;
	}
	
	i++;
}
}
