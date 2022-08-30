#include <stdio.h>
#include <stdlib.h>
#define maximum 10
#define length 5
typedef char unit8;
typedef struct simple_DB node;
typedef enum
{
    false,
    true
}bool;
unit8 z =0;
struct simple_DB
{
    unit8 student_ID;
    unit8 student_year;
    unit8 course_ID[length];
    unit8 course_grade[length];
    node*next;
};
unit8 Position_Node(node*first,unit8 id);
bool SDB_IsFull(void);
unit8 SDB_GetUsedlength();
bool SDB_AddEntry(unit8 id,unit8 year,unit8*subjects,unit8*grades,node**first);
void SDB_DeleteEntry(node**first,unit8 id);
bool IsExist(node*first,unit8 id);
bool SDB_ReadEntry(unit8 id,unit8*year,unit8**subject,unit8**grade,node*first);
void SDB_GetList(node*first);

int main ()
{
    unit8 st_id;
	unit8 year;
	unit8 grade[3];
	unit8 course_id[3];
	unit8 ch;
	unit8 *subjects;
	unit8 *grades;
	node*first=NULL;
    label3:
    printf("-------------------------------------------------\n");
    printf("1-Check if the data base is full\n");
    printf("2-get the number of students\n");
    printf("3-Add student in database\n");
    printf("4-Delete student by his id\n");
    printf("5-Print information about student\n");
    printf("6-Get list of id in the database\n");
    printf("7-Check if this student is in data base or not\n");
    printf("8-Exit the program\n");
    printf("--------------------------------------------------\n");
    printf("pick your choice\n");
    scanf("%d",&ch);
    switch(ch)
    {
  case 1:
        {
           if(SDB_IsFull())
            printf("The database is full\n");
           else
            printf("The data base is not full\n\n");
            goto label3;
        }
  case 2:
        {
           unit8 n=SDB_GetUsedlength();
           printf("The number of entries is %d",n);
           printf("\n\n");
           goto label3;
        }
  case 3:
        {
           if(SDB_AddEntry(st_id,year,subjects,grades,&first))
           {
               printf("The entry is added successfully\n\n");
           }
           goto label3;
        }
  case 4:
        {
            SDB_DeleteEntry(&first,st_id);
            goto label3;
        }
  case 5:
        {
            if(z==0)
            {
                printf("there is no students in data base\n\n");
                goto label3;
            }
            if(SDB_ReadEntry(st_id,&year,&subjects,&grades,first))
            {
                printf("The year is %d",year);
                printf("\n");
            for(int i=1;i<4;i++)
              {
                printf("The course %d",i);
                printf(" id %d",subjects[i-1]);
                printf("\n");
                subjects++;
              }
            for(int i=1;i<4;i++)
              {
                printf("The course %d",i);
                printf(" grade %d",grades[i-1]);
                printf("\n");
                grades++;
              }
            }
                goto label3;
        }
  case 6:
        {
                SDB_GetList(first);
                goto label3;
        }
  case 7:
        {
                if(IsExist(first,st_id))
                {
                    printf("This student exists in the database\n\n");
                    goto label3;
                }
                else
                {
                    printf("This student doesnot exist in the database\n\n");
                    goto label3;
                }
        }
  case 8:
        {
             printf("Thanks for using my program  (:  \n");
             return 0;
        }
    }
}

unit8 Position_Node(node*first,unit8 id)
{
   unit8 position=1;
   while(first)
   {
       if(first->student_ID==id)
        return position;
       else
       {
           position++;
       }
       first=first->next;
   }
   return -1;
}
bool SDB_IsFull(void)
{
  if(z==maximum)
    return true;
  else
    return false;
}
unit8 SDB_GetUsedlength()
{
    return z;
}
bool SDB_AddEntry(unit8 id,unit8 year,unit8*subjects,unit8*grades,node**first)
{
    if (SDB_IsFull())
    {
        printf("The data base is already full\n\n");
        return false;
    }
    else
    {
        node*st=(node*)malloc(sizeof(node));
        subjects=st->course_ID;
        grades=st->course_grade;
        printf("Enter student number %d",z+1);
        printf(" id \n");
        label1:
        scanf("%d",&id);
        st->student_ID=id;
        unit8 pos=Position_Node(*first,st->student_ID);
        if(pos==-1)
        {
        z++;
        printf("Enter student year \n");
        scanf("%d",&year);
        st->student_year=year;
        for(int i=1;i<4;i++)
        {
            printf("Enter the course %d",i);
            printf(" id\n");
            scanf("%d",&subjects[i-1]);
            subjects++;
        }
        subjects=st->course_ID;
        for(int i=1;i<4;i++)
        {
            printf("Enter the course %d",i);
            printf(" grade\n");
            label:
            scanf("%d",&grades[i-1]);
                if(grades[i-1]>100||grades[i-1]<0)
                {
                    printf("Warning you entered a wrong grade\n");
                    printf("Please enter another grade\n");
                    goto label;
                }
            grades++;
        }
        grades=st->course_grade;
        if(*first==NULL)
        {
            *first=st;
            (*first)->next=NULL;
        }
        else
        {
            node*ptr=*first;
            while(ptr->next)
            {
                ptr=ptr->next;
            }
            ptr->next=st;
            (st)->next=NULL;
        }
        return true;
        }
        else
        {
           printf("something is wrong\n");
            printf("The id has been created\n");
            printf("Enter another id\n");
            goto label1;
        }
    }
}
void SDB_DeleteEntry(node**first,unit8 id)
{
    if(z==0)
    {
         printf("empty data base\n");
		printf("you didnot add any student before\n");
        return;
    }
    unit8 p;
    node*p1=*first;
    node*p2=*first;
    printf("Enter the id of \n");
    printf("you want to delete \n");
    label2:
    scanf("%d",&id);
    p=Position_Node(*first,id);
    if(p<0)
    {
      printf("invalid id try again \n");
        printf("Please enter valid id\n");
        goto label2;
    }
    else
    {
        if(p==1)
        {
            node*ptr=*first;
            *first=(*first)->next;
            free(ptr);
        }
        for(int i=0;i<p-2;i++)
        {
            p2=p2->next;
            p1=p1->next;
        }
        p1=p1->next;
        p2->next=p1->next;
        z--;
        printf("This student has been successfully deleted\n\n");
    }
}
bool IsExist(node*first,unit8 id)
{
   printf("Enter the id of student ");
	printf(" who you want to search about him\n");
    scanf("%d",&id);
    while(first)
    {
        if(first->student_ID==id)
            return true;
        else
            first=first->next;
    }
          return false;
}
bool SDB_ReadEntry(unit8 id,unit8*year,unit8**subject,unit8**grade,node*first)
{
   printf("enter the id of student \n");
	printf("who you want to see his information \n");
    scanf("%d",&id);
    unit8 p=Position_Node(first,id);
    if(p<0)
    {
        printf("the id not exist\n\n");
        return false;
    }
  else
    {
        for(int i=0;i<p-1;i++)
        first=first->next;
        *year=first->student_year;
        *subject=first->course_ID;
        *grade=first->course_grade;
    }
}
void SDB_GetList(node*first)
{
    if(z==0)
    {
        printf("empty data base\n\n");
        printf("you didnot add any student\n\n");
        return;
    }
    for(int i=0;i<z;i++)
    {
        printf("The student number %d",i+1);
        printf(" his id is = %d",first->student_ID);
        printf("\n");
        first=first->next;
    }
    printf("\n");
}