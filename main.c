#include "head.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

# define StudentNum 250
# define TeacherNum 5
# define IdLength 10
# define PasswordLength 6
# define TelLength 11
# define CourseIdLength 6
# define EmailLength 50
# define SelectNum 1001
int CourseNum;
int TIME = 0;


typedef struct CourseInfo
{
    char ID[CourseIdLength+1];
    char name[15];
    char credit[2];
    char period[3];
    char type[10];
    char TeacherName[6];
    char StartTime[3];
    char EndTime[3];
    char WhatTime[15];
    char place[6];
    int MaxStudentNum;
    int RemainNum;
    char TextBook[100];
    char intro[100];
    struct CourseInfo *NextAddr;
}CourseInfo;

typedef struct StudentInfo
{
    char ID[IdLength+1];
    char password[PasswordLength+1];
    char name[10];
    char gender[2];
    char academy[50];
    char major[30];
    char tel[TelLength+1];
    char email[EmailLength+1];
}StudentInfo;

typedef struct TeacherInfo
{
    char ID[IdLength+1];
    char password[PasswordLength+1];
    char name[10];
    char academy[25];
    char email[EmailLength+1];
}TeacherInfo;

typedef struct SelectInfo
{
    char StuId[IdLength+1];
    char Course1[50];
    char Course2[50];
    char Course3[50];
}SelectInfo;

typedef struct SelectInfo2
{
    
    char CourseName[50];
}SelectInfo2;
struct StudentInfo student[StudentNum];
struct TeacherInfo teacher[TeacherNum];
//从文件txt中读出数据
void InitTeacher(struct TeacherInfo teacher[]);
void InitStudent(struct StudentInfo student[]);
void InitCourse(struct CourseInfo course[]);
void InitSelect(struct SelectInfo select[]);
void InitTimePlace(int TAP[6][10]);

int welcome(void);

//学生系统
int Student(void);//学生整合函数
int GetCourseLineNum(void);
int Select1(void);//学生一级目录
int SelectCourse(struct StudentInfo Student);
int CheckCourseNULL(struct CourseInfo course);
int ChargeSelectedNum(struct SelectInfo SelectStu);
int SearchCourseNo(struct SelectInfo SelectStu);
int ChargeSelectSame(char CourseName[50],struct SelectInfo SelectStu);
void SearchCourseInfo(struct CourseInfo course[]);
void PrintfCourseInfo(struct CourseInfo course);
int SearchSelectResult(struct SelectInfo Student,struct CourseInfo course[]);
void ChangePerson(struct StudentInfo Student);
int CheckSymbol(char *change);
void DeleteCourse(struct SelectInfo Student);

//教师系统
int TeacherMain(void);
int TeacherLogin(void);
int deleteCourse(int IndexNum,struct CourseInfo course[],struct TeacherInfo teahcer[]);
void ModifyCourseInfo(int IndexNnum,struct TeacherInfo teacher[],struct CourseInfo course[]);
int FindCourse(int IndexNum,struct CourseInfo course[],struct TeacherInfo teacher[]);
void ModifyStudentMaxNum(int modify,struct CourseInfo course[]);
void TeacherCheckSelectSitu(char TeacherName[],int IndexNum);
void TeahcerCheckStudentInfo(void);
void CheckCourseViaKeyboard(void);
void ModifyTeacherInfo(int Arraynum,struct TeacherInfo tch[]);
void CoverTeacherInfo(void);
void CoverCourseInfo(struct CourseInfo course[]);
int AddCourse(char TeacherName[]);
int CanTeacherKeepAdding(struct CourseInfo course[],char TeacherName[]);
void ModifyInfo(char Modified[],int length);//printf+scanf+check+modify
void ModifyWeekInfo(void);
void TimeAndPlace(struct CourseInfo course[],char TeacherName[]);
int DuplicateCheck(struct CourseInfo course[],char gotten[]);
int TimeDuplicateCheck(struct CourseInfo course[],int option,char TeacherName[]);
int StringWhetherValid(char recieved[],int length);
void InputUntilEnter(char gotten[]);
int StringLenDetermined(char recieved[],int length);
//管理员系统
int Admin(void);
void AutoDeleteCourse(struct CourseInfo course[]);
int AdminLogin (void);

//检验输入是否合法
int OptionInput(char high);


int main()
{
    int charge = 0;
    int identity;
    do
    {
        charge = 0;
        identity = welcome();
        if (identity == 1)
        {
            charge = Student();
        }
        else if(identity == 2)
        {
            charge = TeacherMain();
        }
        else if (identity == 3)
        {
            charge = Admin();
        }
        
    }while (charge == 1);
    return 0;
}
void InitTeacher(struct TeacherInfo teacher[])
{
    FILE* fp;
    fp = fopen("/Users/a123456/Desktop/TeachInfo.txt", "r+");
    
    int i = 0, scan = 0;
    while (scan != EOF)//将文件中的数据储存到结构体数组中
    {
        scan = fscanf(fp, "%s%s", teacher[i].ID, teacher[i].password);
        scan = fscanf(fp, "%s%s%s", teacher[i].name, teacher[i].academy, teacher[i].email);
        i++;
    }
    fclose(fp);
}
void InitStudent(struct StudentInfo student[])
{
    FILE* fp;
    fp = fopen("/Users/a123456/Desktop/StudentInfo.txt", "r+");
    
    int i = 0, scan = 0;
    while (scan != EOF)//将文件中的数据储存到结构体数组中
    {
        scan = fscanf(fp, "%s%s%s%s", student[i].ID, student[i].password, student[i].name, student[i].gender);
        scan = fscanf(fp, "%s%s%s%s", student[i].academy, student[i].major, student[i].tel, student[i].email);
        i++;
    }
    fclose(fp);
}
void InitCourse(struct CourseInfo course[])
{
    FILE* fp;
    fp = fopen("/Users/a123456/Desktop/CourseInfo.txt", "r+");
    
    int i = 0, scan = 0;
    while (scan != EOF)//将文件中的数据储存到结构体数组中
    {
        scan = fscanf(fp, "%s%s%s%s", course[i].ID, course[i].name, course[i].credit, course[i].period);
        scan = fscanf(fp, "%s%s%s%s", course[i].type, course[i].TeacherName, course[i].StartTime, course[i].EndTime);
        scan = fscanf(fp, "%s%s", course[i].WhatTime, course[i].place);
        scan = fscanf(fp, "%d%d%s%s", &course[i].MaxStudentNum, &course[i].RemainNum,course[i].TextBook, course[i].intro);
        i++;
    }
    fclose(fp);
}
void InitSelect(struct SelectInfo select[])
{
    FILE* fp;
    fp = fopen("/Users/a123456/Desktop/SelectInfo.txt", "r+");
    
    int i = 0, scan = 0;
    while (scan != EOF)//将文件中的数据储存到结构体数组中
    {
        scan = fscanf(fp, "%s%s%s%s", select[i].StuId, select[i].Course1, select[i].Course2, select[i].Course3);
        i++;
    }
    fclose(fp);
}
void InitTimePlace(int TAP[6][10])
{
    FILE *fp = fopen("/Users/a123456/Desktop/课程时间地点.txt","r");
    
    while(!feof(fp))//把信息都存在二维数组中
    {
        for(int i = 0;i<6;i++)
        {
            for(int j = 0;j<10;j++)
                fscanf(fp,"%d",&TAP[i][j]);
        }
    }
    fclose(fp);
}


int Student()
{
    CourseNum = GetCourseLineNum();
    struct TeacherInfo teacher[TeacherNum];
    struct StudentInfo st[StudentNum];
    struct CourseInfo course[CourseNum];
    struct SelectInfo select[StudentNum];
    InitTeacher(teacher);
    InitSelect(select);
    InitCourse(course);
    InitStudent(st);
    
    char IDcode[IdLength + 1],password[PasswordLength];
    int i = 0,temp = 0;
    int select1Num;
    int charge = 0;
    
    while(charge == 0)
    {
        printf("\nPlease enter your ID and your password. \n");
       printf("ID:");
        scanf("%s",IDcode);//输入你的名字和密码
        printf("password:");
        scanf("%s",password);
        temp=-1;//两字符串相等时，temp = 0
        for(i = 0;temp!=0&&i<StudentNum;i++)
            temp=strcmp(IDcode,st[i].ID);
        if(i >= StudentNum)
            printf("\nERROR: Your ID has not been found.");
        else//找到了ID号码，现在看看能不能匹配
        {
            temp = strcmp(password,st[i-1].password);
            if(!temp)//密码对上了！
            {
                int logout = 0;
                printf("\nYou have successfully login your student selective system!\n");//做后续的工作
                while(logout == 0)
                {
                    select1Num = Select1();
                    if(select1Num == 1)//如果选择了选课
                    {
                        if(TIME == 1)//如果此时时间可以选课
                        {
                            SelectCourse(st[i-1]);
                        }
                        else
                        {
                            printf("\nIt is not time to select course\n");
                        }
                    }
                    else if(select1Num == 2)//如果选择了查询课程信息
                    {
                        SearchCourseInfo(course);
                    }
                    else if(select1Num == 3)
                    {
                        if(TIME != 0)
                        {
                            InitSelect(select);
                            InitCourse(course);
                            SearchSelectResult(select[i-1],course);
                        }
                        else
                        {
                            printf("\nIt is not select course time.\nYou can't search selected courses.\n");
                        }
                       
                    }
                    else if(select1Num == 4)
                    {
                        ChangePerson(st[i-1]);
                    }
                    else if(select1Num == 5)
                    {
                         if(TIME != 0)
                         {
                             InitSelect(select);
                             InitCourse(course);
                             if(SearchSelectResult(select[i-1],course) == 1)
                                 DeleteCourse(select[i-1]);
                         }
                        else
                        {
                            printf("\nIt is not delete time.\nYou can't delete selected courses.\n");
                        }
                        
                    }
                    else if(select1Num == 6)
                    {
                        return 1;
                    }
                }
            }
            else
            {
                printf("\nSorry,your password is wrong.\nTry it again.\n");
                charge = 0;

            }
                
        }
        
    }
    return 0;
}
int GetCourseLineNum(void)
{
    FILE *fp = fopen("/Users/a123456/Desktop/CourseInfo.txt","r+");
    
    int LineNum = 0;
    
    int num = 0;
    char temp[103] = {0};
    
    while(num!=EOF)
    {
        for(int i = 0;i<13;i++)
            num = fscanf(fp,"%s",temp);
        LineNum++;
    }
    LineNum--;
    
    return LineNum;
}
int Select1(void)//一级目录
{
    int SelectNo = 0;
    printf("\nWhat do you want to do?\n");
    printf("1 Select Course\n2 Search Course Infomation\n3 Search Selected Course\n4 Change personal Information\n5 Delete Selected Course\n6 Log out\n(number 1-6)\n");
    printf("number:");
    SelectNo = OptionInput('6');
    return SelectNo;
    
}
int SelectCourse(struct StudentInfo Student)//选课系统
{
        char ID[IdLength+1];//确定是哪个学生
        
        char ChargeSelectNum[20];
        int ChSlcNum = 0;
        int i = 0,j = 0,temp = 0;
        int StudentNo = 0;
        int SelectNo = 0;
        int RemainNumber = 0;
        int CourseNum = 0;
        int CourseNo = 0;
        int ChargeNum = 0;
        int ChargeSame = 0;
        int loop = 0;
        
        strcpy( ID, Student.ID);
        struct SelectInfo SelectStu[StudentNum];
        InitSelect(SelectStu);//课程信息已成功录入结构体数组
        temp = -1;//temp = -1;
        for(i = 0;temp!=0&&i<StudentNum;i++)
            temp=strcmp(ID,SelectStu[i].StuId);//两字符串相等时，temp = 0
            
        StudentNo = i - 1;
        CourseNum = GetCourseLineNum();
        struct CourseInfo course[CourseNum];
        InitCourse(course);
        struct CourseInfo copy[CourseNum];
        i = 0;
        printf("Please select in fllowing courses\n");
        for (i = 0; i < CourseNum; i++)
        {
            if(CheckCourseNULL(course[i]) == 0)
            {
                copy[j] = course[i];
                j++;
            }
        }
        int CourseNum2 = j;
        for (i = 0; i < CourseNum2; i++)
        {
            printf("----------%d--------------\n",i+1);
            PrintfCourseInfo(copy[i]);
        }
    
        do
        {
            printf("\nWhich one do you want to choose(number 1 - %d).\n",CourseNum2);
            printf("Once only can choose one lesson.\n");
            fflush(stdin);
            fgets(ChargeSelectNum,20,stdin);
            ChSlcNum = StringWhetherValid(ChargeSelectNum,20);
            if(ChargeSelectNum[2] == '\0')
            {
                SelectNo = ChargeSelectNum[0]-'0';
            }
            else
            {
                int tens, units;
                tens = (ChargeSelectNum[0]-'0') * 10;
                units = ChargeSelectNum[1]-'0';
                SelectNo = tens + units;
            }
                
           
            if(ChSlcNum == 1)
            {
                printf("Sorry, you just can choose one lesson");
                loop = 0;
            }
            else
            {
                if(SelectNo > CourseNum2 || SelectNo == 0)
                {
                    printf("\nSorry, you just can you just can put in number 1-%d\n ",i);
                }
                
                else
                {
                
                    if(copy[SelectNo - 1].RemainNum == 0)
                    {
                        printf("Sorry, the course is full.");
                    }
                    else
                    {
                        int No1 = 0, No2 = 0, No3 = 0;
                        if(strcmp(SelectStu[StudentNo].Course1 , "000000") != 0)
                        {
                            for(i = 0; i < GetCourseLineNum(); i++)
                            {
                                if(strcmp(SelectStu[StudentNo].Course1, course[i].name) == 0 )
                                {
                                    No1 = i;
                                }
                            }
                        }
                        if(strcmp(SelectStu[StudentNo].Course2 , "000000") != 0)
                        {
                            for(i = 0; i < GetCourseLineNum(); i++)
                            {
                                if(strcmp(SelectStu[StudentNo].Course2, course[i].name) == 0 )
                                {
                                    No2 = i;
                                }
                            }
                        }
                        if(strcmp(SelectStu[StudentNo].Course3 , "000000") != 0)
                        {
                            for(i = 0; i < GetCourseLineNum(); i++)
                            {
                                if(strcmp(SelectStu[StudentNo].Course3, course[i].name) == 0 )
                                {
                                    No3 = i;
                                }
                            }
                        }
                        if(strcmp(copy[SelectNo -1 ].WhatTime,course[No1].WhatTime) != 0 && strcmp(copy[SelectNo -1].WhatTime,course[No2].WhatTime) != 0&&strcmp(copy[SelectNo -1].WhatTime,course[No3].WhatTime) != 0)
                        {
                            ChargeNum = ChargeSelectedNum(SelectStu[StudentNo]);
                            if(ChargeNum == 3)
                            {
                                printf("\nSorry, you have already selected 3 lessons.\n");
                                loop = 1;
                            }
                            else
                            {
                                
                                CourseNo = SearchCourseNo(SelectStu[StudentNo]);
                                    if(CourseNo == 1)
                                        strcpy(SelectStu[StudentNo].Course1,copy[SelectNo-1].name);
                                    else if(CourseNo == 2)
                                        strcpy(SelectStu[StudentNo].Course2,copy[SelectNo-1].name);
                                    else
                                        strcpy(SelectStu[StudentNo].Course3,copy[SelectNo-1].name);
                                    
                                    
                                    FILE *fp;
                                    fp = fopen("/Users/a123456/Desktop/SelectInfo.txt","w");
                                    for(i = 0; i < StudentNum; i++)
                                    {
                                        fprintf(fp,"%s %s %s %s\n", SelectStu[i].StuId, SelectStu[i].Course1,SelectStu[i].Course2,SelectStu[i].Course3);
                                    }
                                    fclose(fp);
                                    
                                    //检验
                                    i = 0;
                                    fp=fopen("/Users/a123456/Desktop/SelectInfo.txt","rw+");
                                    while(temp!= EOF)//将文件中的数据储存到结构体数组中
                                    {
                                        temp=fscanf(fp,"%s%s%s%s",SelectStu[i].StuId,SelectStu[i].Course1,SelectStu[i].Course2,SelectStu[i].Course3);
                                        i++;
                                    }
                                    
                                    fclose(fp);//课程信息已成功录入结构体数组
                                    
                                    
                                    //写入课余量
                                    
                                    for(i = 0; i < CourseNum; i++)
                                    {
                                        if(strcmp(copy[SelectNo-1].ID,course[i].ID) == 0)
                                        {
                                            temp = 0;
                                            temp = course[i].RemainNum;
                                            RemainNumber = temp - 1;
                                            course[i].RemainNum = RemainNumber;
                                        }
                                    }
                                    fopen("/Users/a123456/Desktop/CourseInfo.txt","w");
                                    for(i = 0; i < CourseNum; i++)
                                    {
                                        fprintf(fp,"%s %s %s %s %s ",course[i].ID,course[i].name,course[i].credit,course[i].period,course[i].type);
                                        fprintf(fp,"%s %s %s %s ",course[i].TeacherName,course[i].StartTime,course[i].EndTime,course[i].WhatTime);
                                        fprintf(fp,"%s %d %d %s %s\n",course[i].place,course[i].MaxStudentNum,course[i].RemainNum,course[i].TextBook,course[i].intro);
                                    }
                                    fclose(fp);
                                    
                                    printf("Congratulations, you have chosen %s.\n", copy[SelectNo-1].name);
                                    loop = 1;
                                }
                                    
                            
                        }
                        else
                        {
                            ChargeSame = ChargeSelectSame(copy[SelectNo-1].name,SelectStu[StudentNo]);
                            if(ChargeSame == 1)
                                printf("\nSorry, you have already chosen %s. You can't choose the same course.\n",copy[SelectNo-1].name);
                            else
                            {
                                printf("\nSorry, you have one course in %s\n",copy[SelectNo - 1].WhatTime);
                            }
                            
                        }
                        
                    }
                    
                }
                
            }
        }while(!loop);
        return 0;
    }
int CheckCourseNULL(struct CourseInfo course)
{
    if(strcmp("000000", course.ID)== 0)
        return 1;
    else
        return 0;
}
int ChargeSelectedNum(struct SelectInfo SelectStu)//选课系统->查看学生是否选了3个
{
    int num = 3;
    if(strcmp("000000",SelectStu.Course1) == 0)
    {
        num--;
    }
    if(strcmp("000000",SelectStu.Course2) == 0)
    {
        num--;
    }
    if(strcmp("000000",SelectStu.Course3) == 0)
    {
        num--;
    }
    return num;
}
int SearchCourseNo(struct SelectInfo SelectStu)//选课系统->那个Course123是空的
{
    int temp;
    int num = 0;
    temp=strcmp("000000",SelectStu.Course1);//两字符串相等时，temp = 0
    if(temp == 0)
    {
        return 1;
    }
    temp=strcmp("000000",SelectStu.Course2);//两字符串相等时，temp = 0
    if(temp == 0)
    {
        return 2;
    }
    temp=strcmp("000000",SelectStu.Course3);//两字符串相等时，temp = 0
    if(temp == 0)
    {
        return 3;
    }
    return num;
}
int ChargeSelectSame(char CourseName[50],struct SelectInfo SelectStu)//选课系统->有没有选重
{
    if(strcmp(CourseName,SelectStu.Course1) ==0 ||strcmp(CourseName,SelectStu.Course2)==0||strcmp(CourseName,SelectStu.Course3)==0)
        return 1;
    else
        return 0;
}
void SearchCourseInfo(struct CourseInfo course[])//查询课程信息
{
    int No;
    printf("\nWhich one do you want to search or sort?\n");
    printf("1 Search according to course name\n");
    printf("2 Search according to academy\n");
    printf("3 Sort according to the number of remaining courses\n");
    printf("4 Sort according to the number of selected people\n");
    printf("(number 1-4)");
    int charge = 0;
    do
    {
        No = OptionInput('4');
        charge = 0;
        if(No == 1)
        {
            
            CourseNum = GetCourseLineNum();
        
            struct TeacherInfo teacher[TeacherNum];
            InitTeacher(teacher);
            struct StudentInfo student[StudentNum];
            InitStudent(student);
            struct CourseInfo course[CourseNum];
            InitCourse(course);
            

            char receive[20] = {0};//用户输入
              int courselinenum=GetCourseLineNum();
             int sign = 1;
             int i=0;
             do
             {
                 printf("\nHere are all the courses.\n");
                 for(i=0;i<courselinenum;i++)//向用户展示所有开设课程
                 {
                     if(CheckCourseNULL(course[i]) == 0)
                     {
                         printf("   %s\n",course[i].name);
                     }
                 }
                printf("Please enter the NAME of the courses one by one:\n");
                 scanf("%s",receive);
                 
                 for(i=0;i<courselinenum;i++)
                 {
                     if(strcmp(receive,course[i].name)==0)//查用户是否输入错误
                     {
                         sign=0;
                     }
                 }
                 if(sign==1)
             {
                 printf("Input error,please try again.\n");
             }
                 
             }while(sign==1);
             
            
             for(i=0;i<courselinenum;i++)//输出课程信息
             {
                 if(strcmp(receive,course[i].name)==0)
                 {
                     printf("----------------------%s-------------------------\n",course[i].name);
                     PrintfCourseInfo(course[i]);
                      printf("------------------------------------------------\n");
                     
                 }
              }
        }
        else if(No == 2)
        {
            CourseNum = GetCourseLineNum();

                struct TeacherInfo teacher[TeacherNum];
                InitTeacher(teacher);
                struct StudentInfo student[StudentNum];
                InitStudent(student);
                struct CourseInfo course[CourseNum];
                InitCourse(course);
                

                char receive[20];//用户输入学院名称
                int courselinenum=GetCourseLineNum();
                int sign = 1;
                int i=0;
                int check = 0;
                 //char temp[6]={'0'};
                 do
                 {
                     printf("\nHere are all the academies.\nWhich do you want to search?\n");
                     for(i=0;i<TeacherNum;i++)//向用户展示所有开设课程
                     {
                             printf("\t%s\n",teacher[i].academy);
                         
                     }
                    printf("Please enter the academy one by one:\n");
                     scanf("%s",receive);
                     
                     for(i=0;i<TeacherNum;i++)
                     {
                         if(strcmp(receive,teacher[i].academy)==0)//查用户是否输入错误
                         {
                             sign=0;
                         }
                     }
                     if(sign==1)
                     {
                         printf("\nInput error,please try again.\n");
                         
                     }
                     
                 }while(sign==1);
                 
                  for(i=0;i<TeacherNum;i++)
                  {
                          if(strcmp(receive,teacher[i].academy)==0)
                          {
                              int j=0;
                              for(j=0;j<courselinenum;j++)
                              {
                                  
                                  if(strcmp(teacher[i].name,course[j].TeacherName)==0)
                                  {
                                      if(CheckCourseNULL(course[i]) == 0)
                                      {
                                          printf("---------------%s-------------------\n",course[j].name);
                                          PrintfCourseInfo(course[j]);
                                          check = 1;
                                      }
                                      
                                      
                                  }
                              }
                              
                       }
                  }
            if(check == 0)
            {
                printf("\nSorry, there is no course\n.");
            }
        }
        else if(No == 3)
        {
            int i = 0;
            int j = 0;
            int m = 0;
            CourseNum = GetCourseLineNum();
            struct CourseInfo course[CourseNum];
            struct CourseInfo Copy[CourseNum];

            InitCourse(course);
            for(i = 0; i < CourseNum; i++)
                {
                    Copy[i] = course[i];
                }
            
            for(i = 0;i < 4;i++)
            {
                m = m - 1;
                for(j = 0;j < CourseNum + m;j++)
                {
                    if(Copy[j].RemainNum >Copy[j+1].RemainNum)
                    {
                        struct CourseInfo temp;
                        temp=Copy[j];
                        Copy[j]=Copy[j+1];
                        Copy[j+1]=temp;
                    }
            
                }
            }
            j = 0;
            for(i= 0; i < CourseNum; i++)
            {
                if(CheckCourseNULL(course[i]) == 0)
                {
                    printf("----------%d--------------\n",j+1);
                    PrintfCourseInfo(Copy[i]);
                    j++;
                }
               
            }
        }
         else if(No == 4)
         {
             int i = 0;
             int j = 0;
             int m = 0;
             CourseNum = GetCourseLineNum();
             struct CourseInfo course[CourseNum];
             struct CourseInfo Copy[CourseNum];

             InitCourse(course);
             for(i = 0; i < CourseNum; i++)
                 {
                     Copy[i] = course[i];
                 }
             
             for(i = 0;i < 4;i++)
             {
                 m = m - 1;
                 for(j = 0;j < CourseNum + m;j++)
                 {
                     if(Copy[j].MaxStudentNum - Copy[j].RemainNum <Copy[j+1].MaxStudentNum - Copy[j+1].RemainNum)
                     {
                         struct CourseInfo temp;
                         temp=Copy[j];
                         Copy[j]=Copy[j+1];
                         Copy[j+1]=temp;
                     }
             
                 }
             }
             j = 0;
             for(i= 0; i < CourseNum; i++)
             {
                 if( CheckCourseNULL(Copy[i]) == 0)
                 {
                     printf("----------%d--------------\n",j+1);
                     printf("course number: %s\ncourse name: %s\n",Copy[i].ID,Copy[i].name);
                     printf("credit: %s\nclass hour: %s\n",Copy[i].credit,Copy[i].period);
                     printf("optional or compulsory: %s\nteacher's name: %s\n",Copy[i].type,Copy[i].TeacherName);
                     printf("<start time> week %s\n<end time> week %s\n",Copy[i].StartTime,Copy[i].EndTime);
                     printf("<specific time> %s\n<specific place> %s\n",Copy[i].WhatTime,Copy[i].place);
                     printf("<max student num> %d\n<selected number> %d\n<textbook> %s\n<course description> %s\n",Copy[i].MaxStudentNum,Copy[i].MaxStudentNum-Copy[i].RemainNum,Copy[i].TextBook,Copy[i].intro);
                     j++;
                 }
                 
             }
        }
        else
        {
            printf("You just can put in number 1-4\nTry again.\n");
            charge = 1;
        }
    }while (charge == 1);
}
void PrintfCourseInfo(struct CourseInfo course)
{
        printf("course number: %s\ncourse name: %s\n",course.ID,course.name);
        printf("credit: %s\nclass hour: %s\n",course.credit,course.period);
        printf("optional or compulsory: %s\nteacher's name: %s\n",course.type,course.TeacherName);
        printf("<start time> week %s\n<end time> week %s\n",course.StartTime,course.EndTime);
        printf("<specific time> %s\n<specific place> %s\n",course.WhatTime,course.place);
        printf("<max student num> %d\n<remaining course number> %d\n",course.MaxStudentNum,course.RemainNum);
        char blank[100] = {'\0'};//转化成为空格的//
        for(int i=0;i<100;i++)
        {
            if(course.TextBook[i]=='+')
            {
                blank[i]=' ';
            }
            else
            {
                blank[i]=course.TextBook[i];
            }
        }
        printf("<text book>:%s\n",blank);
        char blank2[20] = {'\0'};//转化成为空格的//
        for(int i=0;i<100;i++)
        {
            if(course.intro[i]=='+')
        {
            blank2[i]=' ';
        }
        else
        {
            blank2[i]=course.intro[i];
        }
        }
        printf("<introduction>:%s\n",blank2);
}
int SearchSelectResult(struct SelectInfo Student,struct CourseInfo course[])
{
    char temp= '0';
    int number = 1;
    if(Student.Course1[0]!=temp||Student.Course2[0]!=temp||Student.Course3[0]!=temp)
    {
        
        if(Student.Course1[0]!=temp)
        {
            printf("---------------------%d---------------------\n",number);
            int j;
            for(j=0;j<CourseNum;j++)
            {
                if(strcmp(Student.Course1,course[j].name)==0)
                {
                    PrintfCourseInfo(course[j]);
                }
            }
            number++;
        }
        if(Student.Course2[0]!=temp)
        {
            printf("---------------------%d---------------------\n",number);
            int j;
            for(j=0;j<CourseNum;j++)
            {
                if(strcmp(Student.Course2,course[j].name)==0)
                {
                    PrintfCourseInfo(course[j]);
                }
            }
            number++;
        }
        if(Student.Course3[0]!=temp)
        {
            printf("---------------------%d---------------------\n",number);
            int j;
            for(j=0;j<CourseNum;j++)
            {
                if(strcmp(Student.Course3,course[j].name)==0)
                {
                    PrintfCourseInfo(course[j]);
                }
            }
            number++;
        }
        printf("\nThere are your all selected course\n");
        return 1;
    }
    else
       {
           printf("You have not chosen any course.\n");
           return 0;
       }
    
}
void ChangePerson(struct StudentInfo Student)
{
    struct StudentInfo st[StudentNum];
    InitStudent(st);
    int i = 0;
    while(strcmp(Student.ID,st[i].ID)!= 0)
    {
        i++;
    }
    int StuNo = 0;
    StuNo = i;
    int choose=0;
    char newpass[PasswordLength+1] = {0};
    unsigned long size = 0;
    unsigned long size2 = 0;
    int check=0;
    int a=0,b=0;
    int a1 = 0, b1 = 0;
    int charge = 0;
    int chargeall = 0;
    printf("Which info do you want to change? \n");
    printf("1.telephone number\n2.email\n3.password\n");
    printf("(number 1-3)\n");
    do
    {
        charge = 0;
        choose = OptionInput('3');
        if(choose == 1)
        {
            printf("\nPlease put in your new telephone number( 11 numbers ):\n");
            while(charge == 0)
            {
                char newtel[TelLength+1] = {'0'};
                char test[50] = {0};
                scanf("%s",test);
                int i = 0;
                size = strlen(test);
                for(i = 0; i < size; i++)
                {
                    if(test[i] >= '0' && test[i] <= '9')
                    newtel[i] = test[i];
                }
                size2 = strlen(newtel);
                if(size2 == 11 && size == 11)
                {
                    strcpy(st[StuNo].tel, newtel);
                    printf("you have successfully change the telephone number into:%s\n", newtel);
                    charge = 1;
                }
                else
                {
                    printf("You just can put in 11 numbers.\nTry again.\n");
                }
            }
            
            
        }
        else if(choose == 2)
        {
            while(charge == 0)
            {
                char newemail[EmailLength+1] = {'\0'};
                printf("\nPlease put in your new email:\n");
                scanf("%s",newemail);
                if(CheckSymbol(newemail) == 1)
                {
                    a1 = 0;
                    b1 = 0;
                    for(a=0;a<51;a++)
                    {
                        if(newemail[a]=='@')
                        {
                            a1++;
                        }
                        if(newemail[a]=='.')
                        {
                            b1++;
                        }
                    }
                    if(a1==1&&b1==1)
                    {
                        for(b=0;b<51;b++)
                        {
                            if(newemail[b]=='@')
                            {
                                for(a=b;a<51;a++)
                                {
                                    if(newemail[a]=='.')
                                    {
                                        if(b>0&& a-b>1 && newemail[a+1]!='\0')
                                        {
                                            check=1;
                                            break;
                                        }
                                        
                                    }
                                }
                            }
                        }
                    }
                    if(check==1)
                    {
                        strcpy(st[StuNo].email, newemail);
                        printf("you have successfully your email into:%s", newemail);
                        charge = 1;
                    }
                    else
                    {
                        printf(" ！format error！");
                    }
                }
                else
                {
                    printf("\nYou have put in something else.");
                }
            }
            
        }
        else if(choose == 3)
        {
            printf("\nPlease put in your new password( 6 characters ):\n");
            while(charge == 0)
            {
                char test[50] = {0};
                scanf("%s",test);
                size = strlen(test);
                if(size == 6)
                {
                    int i = 0;
                    for(i = 0; i < size; i++)
                    {
                        newpass[i] = test[i];
                    }
                    strcpy(st[StuNo].password, newpass);
                    printf("you have successfully change your password into:%s\n", newpass);
                    charge = 1;
                }
                else
                {
                    printf("You just can put in 6 characters.\nTry again.\n");
                }
            }
        }
        else
        {
            printf("\nYou have put in the wrong number!");
            printf("Try again\n");
            chargeall = 1;
        }
    }while(chargeall == 1);
    
    FILE *fp;
    fp=fopen("/Users/a123456/Desktop/StudentInfo.txt","w");
    for(int i=0;i<StudentNum;i++)
    {
        fprintf(fp,"%s %s %s %s %s %s %s %s\n",st[i].ID,st[i].password,st[i].name,st[i].gender,
                                        st[i].academy,st[i].major,st[i].tel,st[i].email);
    }
    fclose(fp);
}
int CheckSymbol(char *change)//查看email里有没有非法字符，例如“¥%……&*”
{
    int symbol=2;
    for(int j=0;j<51;j++)
    {
        if((change[j]>='0'&&change[j]<='9')||(change[j]>='a'&&change[j]<='z')||(change[j]=='.')||(change[j]=='@')||(change[j]=='\0')||(change[j]=='\n'))
        {
            symbol=1;
        }
        else
        {
            symbol=0;
            return symbol;
        }
    }
    return symbol;
}
void DeleteCourse(struct SelectInfo Student)
{
    struct SelectInfo select[StudentNum];
    InitSelect(select);
    CourseNum = GetCourseLineNum();
    struct CourseInfo course[CourseNum];
    InitCourse(course);
    int i = 0;
    while(strcmp(Student.StuId,select[i].StuId)!= 0)
    {
        i++;
    }
    
        char Delete[15];
        char initial[7]="000000";
        printf("Please put in the course NAME that you want to delete.\n");
        scanf("%s", Delete);
        int temp=0;
        while(temp!=1)
        {
            if(strcmp(select[i].Course1,Delete)==0)
            {
                printf("Success! You have deleted %s.\n",Delete);
                for(int j = 0; j < CourseNum; j++)
                {
                    if(strcmp(course[j].name,select[i].Course1) == 0)
                    {
                        course[j].RemainNum = course[j].RemainNum + 1;
                    }
                }
                strcpy(select[i].Course1,initial);
                temp=1;
            }
            else if(strcmp(select[i].Course2,Delete)==0)
            {
                printf("Success! You have deleted %s.\n",Delete);
                for(int j = 0; j < CourseNum; j++)
                {
                    if(strcmp(course[j].name,select[i].Course2) == 0)
                    {
                        course[j].RemainNum = course[j].RemainNum + 1;
                    }
                }
                temp=1;
                strcpy(select[i].Course2,initial);
            }
            else if(strcmp(select[i].Course3,Delete)==0)
            {
                printf("Success! You have deleted %s.\n",Delete);
                for(int j = 0; j < CourseNum; j++)
                {
                    if(strcmp(course[j].name,select[i].Course3) == 0)
                    {
                        course[j].RemainNum = course[j].RemainNum + 1;
                    }
                }
                temp=1;
                strcpy(select[i].Course3,initial);
            }
            else
            {
                temp=2;
                printf("You have put in the wrong number!\nPlease try again!\n");
                scanf("%s", Delete);
            }

            CoverCourseInfo(course);
        }

        FILE *fp;
        fp=fopen("/Users/a123456/Desktop/SelectInfo.txt","w");
        for(int i=0;i<StudentNum;i++)
        {
            fprintf(fp,"%s %s %s %s \n",select[i].StuId,select[i].Course1,select[i].Course2,select[i].Course3);
        }
        fclose(fp);
}



//----目的：教师版--------------------------------------------------------//
//----变量：无--------------------------------------------------------------//
//----输出：登出时，输出0；----------------------------------------------------//
int TeacherMain(void)
{
    CourseNum = GetCourseLineNum();
    InitTeacher(teacher);
    InitStudent(student);
    
    struct CourseInfo course[CourseNum];
    InitCourse(course);
    
    int function;
    int determine1 = 1,determine2 = 1;//do-while中使用，一级跳出，determine = -1；二级跳出，determine = 0
     
    int IndexNum = 0;
    IndexNum = TeacherLogin();
    printf("Hello, teacher %s.\n",teacher[IndexNum].name);
    
    while(determine1==1)
    {
        determine2 = 1;
        printf("\nPlease choose the following function:");
        printf("\n1. manage the selective courses");
        printf("\n2. manage the courses");
        printf("\n3. personal information management");
        printf("\n4. log out\n");
        function = OptionInput('4');
        
        switch(function)
        {
            case 1:
                printf("\n----- Manage the selective courses -----\n");
                while(determine2==1)
                {
                    printf("\nPlease choose the following functions:");
                    printf("\n1.check your course's information");
                    printf("\n2.check students' information via course name");
                    printf("\n3.return\n");
                    
                    function = OptionInput('3');
                    switch(function)
                    {
                        case 1:
                            printf("\n--------- Check your course's information ---------\n");
                            TeacherCheckSelectSitu(teacher[IndexNum].name, IndexNum);
                            break;
                        case 2:
                            printf("\n--- Check students' information via course name ---\n");
                            TeahcerCheckStudentInfo();
                            break;
                        case 3:
                            printf("\n--------------------- Return ----------------------\n");
                            determine2 = 0;
                            break;
                        case 4:
                            determine2 = 0;
                            break;
                        default:
                            break;
                    }
                }
                break;
            case 2:
                printf("\n---------- Manage the courses ----------\n");
                while(determine2==1)
                {
                    printf("\nPlease choose the following functions:");
                    printf("\n1.search the courses");
                    printf("\n2.add a course");
                    printf("\n3.delete a course ");
                    printf("\n4.modify information");
                    printf("\n5.return\n");
                    
                    function = OptionInput('5');
                    switch(function)
                    {
                        case 1:
                            printf("\n---------- Search the courses ----------\n");
                            CheckCourseViaKeyboard();
                            break;
                        case 2:
                            printf("\n------------- Add a course -------------\n");
                            if(AddCourse(teacher[IndexNum].name)==1)//修改课程成功
                                printf("You have successfully added a new course!\n");
                            else
                            {
                                printf("Sorry, the number of course you can add has reached the ceiling.\n");
                                printf("You can't add anymore.\n");
                            }
                            break;
                        case 3:
                            printf("\n------------ Delete a course -----------\n");
                            if(TIME==0)
                            {
                                printf("\nThe system is close to students now.");
                                printf("\nYou can delete your course.");
                                deleteCourse(IndexNum,course,teacher);
                                
                            }
                            else
                                printf("\nIt's not the time to delete course.\nYou cannot delete courses now!");
                            break;
                        case 4:
                            printf("\n---------- Modify information ----------\n");
                            ModifyCourseInfo(IndexNum, teacher, course);
                            break;
                        case 5:
                            printf("\n---------------- Return ----------------\n");
                            determine2 = 0;
                            break;
                        default:
                            break;
                    }
                }
                break;
            case 3:
                printf("\n--- Personal information management ----\n");
                ModifyTeacherInfo(IndexNum,teacher);
                break;
            case 4:
                determine1 = 0;
                break;
            default:
                printf("Sorry,you just can put number 1-4\n");
                break;
        }
    }
    
    CoverTeacherInfo();
    return 1;
}
//----目的：教师登录--------------------------------------------------------//
//----变量：无--------------------------------------------------------------//
//----输出：老师是第几个----------------------------------------------------//
int TeacherLogin(void)
{
    InitTeacher(teacher);//先初始化
    
    char IDcode[20],password[7];
    int temp = 0,determine = 1;
    int count = 0;

    do
    {
        printf("Please enter your ID and your password. \n");
        printf("ID:");
        scanf("%s",IDcode);//输入你的名字和密码
        printf("password:");
        scanf("%s",password);
        
        for(count = 0;count<5;count++)
        {
            temp = strcmp(IDcode,teacher[count].ID);
            if(temp==0)//ID号对上了
            {
                if(strcmp(password,teacher[count].password)==0)//密码也对上了
                {
                    printf("\nYou have successfully login your teacher selective system!\n");
                    return count;
                }
                else
                {
                       printf("\nSorry, incorrect password.\n");
                        printf("Please enter again.\n");
                    determine = 0;
                }
            }
        }
        if(temp!=0)
        {
            printf("\nSorry, your ID has not been found.");
            printf("Please enter again.\n");
            determine = 0;
        }
    }while(determine==0);
    return count;
}
//----目的：教师教室删除课程-------------------------------------------------//
//----变量：老师下标，course,teacher----------------------------------------//
//----输出：删除成功，返回1-----------------------------------------------//
int deleteCourse(int IndexNum,struct CourseInfo course[],struct TeacherInfo teahcer[])
{
    int CourseLineNum = GetCourseLineNum();
    InitTeacher(teacher);
    InitCourse(course);
    struct SelectInfo select[StudentNum];
    InitSelect(select);
    int temp=0;
    char delete[CourseIdLength+1];
    int modify=FindCourse(IndexNum,course,teacher);
    while(modify!=99)
    {
        printf("Please put in the course ID that you want to delete.\n");
        scanf("%s", delete);
        if(strcmp(delete,"000000")==0)
            printf("\nSorry, this course does not exist.\n");
        else
        {
            for(int i = 0;i<CourseLineNum;i++)
            {
                temp=strcmp(course[i].ID,delete);
                if(temp==0)//找到了这门课程
                {
                    strcpy(course[i].ID,"000000");
                    printf("You have successfully deleted the course!");
                    CoverCourseInfo(course);
                    for(int j=0;j<StudentNum;j++)
                    {
                        if(strcmp(course[i].name,select[j].Course1)==0)
                        {
                            strcpy(select[j].Course1,"000000");
                        }
                        if(strcmp(course[i].name,select[j].Course2)==0)
                        {
                            strcpy(select[j].Course2,"000000");
                        }
                        if(strcmp(course[i].name,select[j].Course3)==0)
                        {
                            strcpy(select[j].Course3,"000000");
                        }
                    }
                    FILE *fp;
                    fp=fopen("/Users/a123456/Desktop/SelectInfo.txt","w");
                    for(int i=0;i<StudentNum;i++)
                    {
                     fprintf(fp,"%s %s %s %s\n",select[i].StuId,select[i].Course1,select[i].Course2,select[i].Course3);
                    }
                    fclose(fp);
                    return 1;
                }
                
            }
            
            if(temp!=0)
                printf("\nSorry, this course does not exist.");
        }
    }
    return 0;
}
//----目的：教师修改自己课程的信息---------------------------------------//
//----变量：老师下标,teacher，course----------------------------------------//
//----输出：无-----------------------------------------------//
void ModifyCourseInfo(int IndexNnum,struct TeacherInfo teacher[],struct CourseInfo course[])
{
    InitTeacher(teacher);
    InitCourse(course);

    int modify=FindCourse(IndexNnum,course,teacher);
    if(modify!=99)//找到了这个课程
    {
        if(course[modify].MaxStudentNum-course[modify].RemainNum==0)//没人选
        {
            int choose;
            char change[100] = {0};
            int order = 0;
            char letter;
        
            printf("Which info do you want to change? \n");
            printf("\n1.text book introduction\n2.course introduction\n3.student number limit\n");
            choose = OptionInput('3');
            printf("Please put in what you want the information to be:\n");
            getchar();
            scanf("%c",&letter);
            while(letter!='\n')
            {
                if(letter==' ')
                {
                 change[order]='+';
                }
                else
                {
                 change[order]=letter;
                }
                order++;
                scanf("%c",&letter);
            }
            switch(choose)
            {
                case 1:
                    strcpy(course[modify].TextBook, change);
                    printf("you have successfully change the textbook introduction.\n");
                    break;
                case 2:
                    strcpy(course[modify].intro, change);
                    printf("you have successfully change the course introduction.\n");
                    break;
                case 3:
                    ModifyStudentMaxNum(modify,course);
                    break;
                default:
                    break;
            }
            CoverCourseInfo(course);
        }
        else
        {
            int choose = 0;
            
            printf("\nThere are more than 1 students who have chosen this course.");
            printf("\nAs a result you cannot change any info besides MaxStudentNum");
            printf("You want: \n");
            printf("1.to change MAXSTUDNUM\n");
            printf("2.nothing changed.\n");
            choose = OptionInput('2');
            switch(choose)
            {
              case 1:
                  ModifyStudentMaxNum(modify,course);
                  break;
              case 2:
                  printf("\nNothing will be changed.");
                  break;
              default:
                  break;
            }
            CoverCourseInfo(course);
        }
    }
    else
    {
        printf("You have no course to midify.\n");
    }
}
//----目的：找老师的课程---------------------------------------------------//
//----变量：这个老师在teacher里的下标，course，teacher--------------------//
//----输出：找到的课程在course中的下标,如果没找到，输出99--------------------//
int FindCourse(int IndexNum,struct CourseInfo course[],struct TeacherInfo teacher[])
{
    InitCourse(course);
    int CourseNum = GetCourseLineNum();
    int coursenum = 99;
    char ChangeID[100] = {0};
    int CheckCourse=99;
    int i = 0;
    printf("\nHere are the courses that you may want to modify:\n");
    for(i = 0;i<CourseNum;i++)
    {
        if((strcmp(course[i].TeacherName,teacher[IndexNum].name)==0)&&(strcmp(course[i].ID,"000000")!=0))//如果找到了这个老师的课程
        {
            printf("%s %s\n",course[i].ID,course[i].name);
            CheckCourse=1;
        }
    }
    if(CheckCourse==1)
    {
        int charge = 0;
        while(charge == 0)
        {
                    printf("\nPlease put in the course ID.");
                   scanf("%s",ChangeID);
                   if(strlen(ChangeID) == 6)
                   {
                       
                           for(i=0;i<CourseNum;i++)
                           {
                               if(strcmp(course[i].ID,ChangeID)==0)//找到了这个课
                               {
                                   if(strcmp(course[i].TeacherName,teacher[IndexNum].name)==0)
                                   {
                                       coursenum = i;
                                       charge = 1;
                                   }
                                   else
                                   {
                                       printf("\nYou cannot change this course's info!");
                                   }
                               }
                           }
                           /*if(coursenum==99)
                           {
                               printf("\nyou cannot change this course's info!");
                           }*/
                       
                       
                       
                   }
                   else
                   {
                       printf("Sorry, please put right course ID.\n");
                   }
                   
        }
       
    }
    else
    {
        printf("\nYou have no course.");
        coursenum = CheckCourse;
    }

    return coursenum;
}
//----目的：老师修改课程最大人数------------------------------------------//
//----变量：老师下标，course--------------------------------------------//
//----输出：无--------------------------------------------------------//
void ModifyStudentMaxNum(int modify,struct CourseInfo course[])
{
    InitCourse(course);
    int choose = 0;
    int remain = 0;
    printf("CourseID:%s, MaxStudentNum:%d\n",course[modify].ID,course[modify].MaxStudentNum);
    if(TIME==1||TIME==0)
    {
        if(course[modify].MaxStudentNum==80)
        {
            printf("If you want to change it into 100, please choose 1\n");
            printf("If you want to keep it, please choose 2\n");
            choose = OptionInput('2');
            if(choose==1)//80人要改成100人
            {
                remain = course[modify].RemainNum;
                course[modify].RemainNum = 100 - (course[modify].MaxStudentNum - remain);
                course[modify].MaxStudentNum=100;
            }
        }
        else if(course[modify].MaxStudentNum==100)
        {
            printf("Until now the remain number is %d .\n",course[modify].RemainNum);
            if(course[modify].RemainNum<=20)
            {
                printf("There are more than 80 students in this class.\n You cannot change the max number now.\n");
            }
            else
            {
                printf("If you want to change it into 80, please choose 1\n");
                printf("If you want to keep it, please choose 2\n");
                choose = OptionInput('2');
                if(choose==1)
                {
                    remain = course[modify].RemainNum;
                    course[modify].RemainNum = 80 - (course[modify].MaxStudentNum - remain);
                    course[modify].MaxStudentNum=80;
                }
            }


        }
            //course[ArrayNum].MaxStudentNum = atoi(change);//

    }
    printf("Until now the remain number is %d .\n",course[modify].RemainNum);
    printf("\nNow the MaxStudentNum is %d.",course[modify].MaxStudentNum);
}
//----目的：老师查看自己的课程的选课情况和课程详情--------------------------//
//----变量：老师的姓名------------------------------------------------------//
//----输出：无--------------------------------------------------------------//
void TeacherCheckSelectSitu(char TeacherName[], int IndexNum)
{
    //char TeacherID[IdLength+1];//确定是哪个老师

    struct TeacherInfo teacher[TeacherNum];
    InitTeacher(teacher);
     
    struct CourseInfo course[CourseNum];
    InitCourse(course);

    CourseNum = GetCourseLineNum();
    int i = 0;
    
    for(i = 0;i<CourseNum;i++)
    {
        if((strcmp(course[i].TeacherName,teacher[IndexNum].name)==0)&&(strcmp(course[i].ID,"000000")!=0))//如果找到了这个老师的课程
        {
            printf("------------------------%s---------------------------\n",course[i].name);
            PrintfCourseInfo(course[i]);
        }
    }
    
}
//----目的：老师根据课程名称查看选该课程的学生及其信息----------------------//
//----变量：无--------------------------------------------------------------//
//----输出：无--------------------------------------------------------------//
void TeahcerCheckStudentInfo(void)
{
    printf("Please enter the name of course you want to search.\n");
    struct SelectInfo select[StudentNum];
    InitSelect(select);
    int CourseLineNum = GetCourseLineNum();
    
    struct CourseInfo course[CourseLineNum];
    InitCourse(course);
    for(int i = 0; i < CourseLineNum; i++)
    {
        if(strcmp(course[i].ID,"000000") != 0)
           printf("%s\n",course[i].name);
    }
    char RecieveCourse[20] ={0};
    int determine = 1;
    do
    {
        int num = 0;
        determine = 1;
        int determine2 = 0;
        scanf("%s",RecieveCourse);
        for(int i = 0;i<CourseLineNum;i++)//检查输入课程名是否正确
        {
            if(strcmp(RecieveCourse,course[i].name)==0)//找到了这个课程
            {
                determine2 = 1;
                if(strcmp(course[i].ID,"000000")==0)
                {
                    printf("Sorry, the course you put in does not exist.\n");
                    printf("Please enter again.\n");
                    determine = 0;
                    num = 1;
                }
            }
            if(i==CourseLineNum -1 && determine2 == 0)//找完了也没找到
            {
                printf("Sorry, the course you put in does not exist.\n");
                printf("Please enter again.\n");
                determine = 0;
                num = 1;
            }
        }
          for(int i = 0;i<StudentNum && determine != 0 ;i++)
                {
                    int j = 0;
                    if(strcmp(select[i].Course1,RecieveCourse)==0)//比较selectinfo中学生选课与receivecourse，打印选课学生信息
                    {
                        for(j = 0;j<StudentNum;j++)
                        {
                            if(strcmp(select[i].StuId,student[j].ID)==0)
                            {
                                num++;
                                printf("-------------%d----------------\n",num);
                                printf("student ID: %s\nstudent name: %s\ngender: %s\n", student[j].ID, student[j].name, student[j].gender);
                                printf("academy: %s\nmajor: %s\nTel: %s\nE-mail: %s\n", student[j].academy, student[j].major, student[j].tel, student[j].email);
                            }
                        }
                    }
                    if(strcmp(select[i].Course2,RecieveCourse)==0)//找到了这门课程
                    {
                        for(j=0;j<StudentNum;j++)
                        {
                            if(strcmp(select[i].StuId,student[j].ID)==0)//是这个学生选了
                            {
                                num++;
                                printf("-------------%d----------------\n",num);
                                printf("student ID: %s\nstudent name: %s\ngender: %s\n", student[j].ID, student[j].name, student[j].gender);
                                printf("academy: %s\nmajor: %s\nTel: %s\nE-mail: %s\n", student[j].academy, student[j].major, student[j].tel, student[j].email);
                            }
                        }
                    }
                    if(strcmp(select[i].Course3,RecieveCourse)==0)
                    {
                        for(j=0;j<StudentNum;j++)
                        {
                            if(strcmp(select[i].StuId,student[j].ID)==0)
                            {
                                num++;
                                printf("-------------%d----------------\n",num);
                                printf("student ID: %s\nstudent name: %s\ngender: %s\n", student[j].ID, student[j].name, student[j].gender);
                                printf("academy: %s\nmajor: %s\nTel: %s\nE-mail: %s\n", student[j].academy, student[j].major, student[j].tel, student[j].email);
                            }
                        }
                    }
                }
                if(num==0 && determine == 1)
                    printf("\nNobody has chosen your course yet.\n");

    }while(determine==0);
}

void CheckCourseViaKeyboard(void)
{
    int courselinenum=GetCourseLineNum();
    struct CourseInfo course[courselinenum];
    InitCourse(course);
    
    char receive[20];//用户输入
     
    int sign = 1;
    do
    {
         printf("Here are all the courses.\n");
         for(int i = 0;i<courselinenum;i++)//向用户展示所有开设课程
         {
             if(strcmp(course[i].ID,"000000")!=0)
                 printf("%s\n",course[i].name);
        }
        
        printf("Please enter the name of the courses one by one:\n");
         scanf("%s",receive);
         for(int i=0;i<courselinenum;i++)
         {
             if(strcmp(receive,course[i].name)==0)//查用户是否输入错误
                 sign=0;
        }
        if(sign==1)
             printf("Input error, please try again.\n");
    }while(sign==1);
     
    char output1[100]={'\0'};
    char output2[100]={'\0'};
    for(int i=0;i<courselinenum;i++)//输出课程信息
    {
        
         if(strcmp(receive,course[i].name)==0)
         {
             for(int d=0;d<100;d++)
             {
                 if(course[i].TextBook[d]=='+')
                 {
                     output1[d]=' ';
                 }
                 else
                 {
                     output1[d]=course[i].TextBook[d];
                 }
                 
             }
             for(int d=0;d<100;d++)
             {
                 if(course[i].intro[d]=='+')
                 {
                     output2[d]=' ';
                 }
                 else
                 {
                     output2[d]=course[i].intro[d];
                 }
                 
             }
             printf("-----------------------%s-------------------------\n",course[i].name);
             printf("ID:%s\nname:%s\ncredit:%s\nperiod:%s\ntype:%s\n", course[i].ID, course[i].name, course[i].credit, course[i].period, course[i].type);
            printf("teacher name:%s\nstart time : %s\nendtime : %s\nspecific time : %s\nplace : %s\n", course[i].TeacherName, course[i].StartTime, course[i].EndTime, course[i].WhatTime, course[i].place);
            printf("maximum student number:%d\nremain student:%d\ntext book:%s\nintroduction:%s\n", course[i].MaxStudentNum, course[i].RemainNum, output1,output2);
        }
    }
}
//----目的：老师修改自己的email或者密码-------------------------------------//
//----变量：老师的结构体数组下标--------------------------------------------//
//----输出：无（改变结构体数组中的内容）------------------------------------//
void ModifyTeacherInfo(int Arraynum,struct TeacherInfo tch[])
{
    
    int choose;
    int check=0;
    int a=0,b=0;
    int a1=0,b1=0;
    int charge = 0;
    char test[50];
    char newpass[TelLength+1];
    unsigned long size = 0;
    int chargeall = 0;
    printf("Which info do you want to change? \n");
    printf("1.email\n2.password\n");
    choose = OptionInput('2');
    do
    {
        if(choose == 1)
           {
               while(charge == 0)
               {
                   char newemail[EmailLength+1] = {'\0'};
                   printf("\nPlease put in your new email:\n");
                   scanf("%s",newemail);
                   if(strlen(newemail)<=50)
                   {
                       if(CheckSymbol(newemail) == 1)
                       {
                           a1 = 0;
                           b1 = 0;
                           for(a=0;a<51;a++)
                           {
                               if(newemail[a]=='@')
                               {
                                   a1++;
                               }
                               if(newemail[a]=='.')
                               {
                                   b1++;
                               }
                           }
                           if(a1==1&&b1==1)
                           {
                               for(b=0;b<51;b++)
                               {
                                   if(newemail[b]=='@')
                                   {
                                       for(a=b;a<51;a++)
                                       {
                                           if(newemail[a]=='.')
                                           {
                                               if(b>0&& a-b>1 && newemail[a+1]!='\0')
                                               {
                                                   check=1;
                                                   break;
                                               }
                                               
                                           }
                                       }
                                   }
                               }
                           }
                           if(check==1)
                           {
                               strcpy(tch[Arraynum].email, newemail);
                               printf("you have successfully your email into:%s", newemail);
                               charge = 1;
                           }
                           else
                           {
                               printf(" ！format error！");
                           }
                       }
                       else
                       {
                           printf("\nYou have put in something else.");
                       }
                   }
                   else
                   {
                       printf("\nformat error！");
                   }
                   
                   
               }
           }
        else if(choose == 2)
           {

               printf("\nPlease put in your new password( 6 characters ):\n");
               while(charge == 0)
               {
                   scanf("%s",test);
                   size = strlen(test);
                   if(size == 6)
                   {
                       int i = 0;
                       for(i = 0; i < size; i++)
                       {
                           newpass[i] = test[i];
                       }
                       strcpy(tch[Arraynum].password, newpass);
                       printf("you have successfully change your password into:%s\n", newpass);
                       charge = 1;
                   }
                   else
                   {
                       printf("You just can put in 6 characters.\nTry again.\n");
                   }
               }
           }
        else
        {
            printf("\nYou have put in the wrong number!");
            printf("Try again\n");
            chargeall = 1;
        }
    }while(chargeall == 1);
    CoverTeacherInfo();
    
}
void CoverCourseInfo(struct CourseInfo course[])
{
    int CourseLineNum = 0;
    CourseLineNum = GetCourseLineNum();
    FILE *fp;
    fp=fopen("/Users/a123456/Desktop/CourseInfo.txt","w");
    for(int i=0;i<CourseLineNum;i++)
    {
        fprintf(fp,"%s\t%s\t%s\t%s\t" ,course[i].ID,course[i].name,course[i].credit,course[i].period);
        fprintf(fp,"%s\t%s\t%s\t%s\t",course[i].type,course[i].TeacherName,course[i].StartTime,course[i].EndTime);
        fprintf(fp,"%s\t%s\t%d\t%d\t",course[i].WhatTime,course[i].place,course[i].MaxStudentNum,course[i].RemainNum);
        fprintf(fp,"%s\t%s\n",course[i].TextBook,course[i].intro);
    }
    fclose(fp);
}
void CoverTeacherInfo(void)
{
    FILE *fp;
    fp=fopen("/Users/a123456/Desktop/TeachInfo.txt","w");
    for(int i = 0;i<TeacherNum;i++)
        fprintf(fp,"%s %s %s %s %s \n",teacher[i].ID,teacher[i].password,teacher[i].name,teacher[i].academy,teacher[i].email);
    
    fclose(fp);
}

//----目的：以老师的身份添加可供学生选课的课程------------------------------//
//----变量：老师姓名--------------------------------------------------------//
//----输出：修改达到上限，输出0；修改成功，输出1（修改课程信息.txt中的内容）//
int AddCourse(char TeacherName[])
{
    FILE *fp = fopen("/Users/a123456/Desktop/CourseInfo.txt","a+");
    
    unsigned long len = 0,i = 0;
    int LineNum = GetCourseLineNum();
    struct CourseInfo course[LineNum];
    InitCourse(course);

    if(CanTeacherKeepAdding(course,TeacherName)==0)
        return 0;
    
    int option = 0;
    struct CourseInfo added;
    
    added.ID[0] = '\n';
    if(LineNum<10)
    {
        for(i = 1;i<6;i++)
            added.ID[i] = '0';
        added.ID[i] = '0'+LineNum+1;//是添加，所以要+1
    }
    else//如果加到第十节课了
    {
        for(i = 1;i<5;i++)
            added.ID[i] = '0';
        added.ID[5] = '0'+LineNum/10;
        added.ID[6] = '0'+LineNum%10;
    }
    added.ID[7] = '\t';
    fwrite(added.ID,sizeof(char)*8,1,fp);
    
    printf("Please enter the name of the course.\n");
    printf("Requirements are as follow:\n");
    printf("If the name contains more than two words,\n");
    printf("please write them together without whitespace and uppercase the first letter of each word.\n");
    printf("The length of the name must be less than 15 letters.\n");
    printf("e.g.If the course name is Advanced Math, you must enter AdvancedMath. \n");
    
    char recieved[50] = {0};
    InputUntilEnter(recieved);
    while(StringWhetherValid(recieved,15)==0||DuplicateCheck(course,recieved)==0)
        InputUntilEnter(recieved);
    strcpy(added.name,recieved);

    len = strlen(added.name);
    added.name[len] = '\t';
    fwrite(added.name,sizeof(char)*(len+1),1,fp);
    fclose(fp);
    
    char credit[10] ="credit";
    ModifyInfo(credit,1);
    char period[10] = "period";
    ModifyInfo(period,2);
    
    fp = fopen("/Users/a123456/Desktop/CourseInfo.txt","a+");
    printf("You want your course to be\n1. optional 2. compulsory. \n");
    option = OptionInput('2');
    switch(option)
    {
        case 1:
            strcpy(recieved,"optional");
            break;
        case 2:
            strcpy(recieved,"compulsory");
            break;
        default:
            break;
    }
    len = strlen(recieved);
    recieved[len] = '\t';
    fwrite(recieved,sizeof(char)*(len+1),1,fp);
    
    len = strlen(TeacherName);
    TeacherName[len] = '\t';
    fwrite(TeacherName,sizeof(char)*(len+1),1,fp);
    fclose(fp);
    
    ModifyWeekInfo();
    
    /*char start[6] = "start";
    ModifyWeekInfo(start,2);
    char end[4] = "end";
    ModifyWeekInfo(end,2);*/
    
    TimeAndPlace(course,TeacherName);//这里传递course数据有问题
    int determine = -1;
    do
    {
        determine = -1;
        printf("Please choose the number of max student in your course:\n");
        printf("1. 80 2. 100\n");
        option = OptionInput('2');
        
        fp = fopen("/Users/a123456/Desktop/CourseInfo.txt","a+");
        switch(option)
        {
            case 1:
                strcpy(recieved,"80    80");
                break;
            case 2:
                strcpy(recieved,"100    100");
                break;//后面0的意思是加一个已选课程的人数
            default:
                printf("Sorry, your input is invalid. Please enter again.\n");
                determine = 0;
                break;
        }
    }while(determine==0);
    
    len = strlen(recieved);
    recieved[len] = '\t';
    fwrite(recieved,sizeof(char)*(len+1),1,fp);
    fclose(fp);
    
    char TextBook[20] = "book introduction";
    ModifyInfo(TextBook,100);
    
    char introduction[20] = "introduction";
    ModifyInfo(introduction,100);
    
    return 1;
}
//----目的：判断老师是否达到加课上限-----------------------------------------//
//----变量：CourseInfo, 老师姓名 --------------------------------------------//
//----输出：如果能加课，输出1；否则，输出0----------------------------------//
int CanTeacherKeepAdding(struct CourseInfo course[],char TeacherName[])
{
    int count = 0;
    
    int CourseLineNum = GetCourseLineNum();
    for(int i = 0;i<CourseLineNum;i++)
    {
        if(strcmp(course[i].TeacherName,TeacherName)==0&&strcmp(course[i].ID,"000000")!=0)
            count++;
    }
        
    if(count==2)
        return 0;
    else
        return 1;
}

//----目的：在老师添加选课的过程中添加课程的信息----------------------------//
//----变量：添加信息的种类，添加内容的限制长度------------------------------//
//----输出：无（改变txt文件数组中的内容）-----------------------------------//
void ModifyInfo(char Modified[],int length)//printf+scanf+check+modify
//仅仅适用于credit period introduction BookInfo
{
    printf("Please enter the %s of the new .\n",Modified);
    if(length==1)
        printf("Here you can just input %d letter.\n",length);
    else
        printf("Here you can input %d letters at most.\n",length);
    
    char ModifiedOne[length+3];
    for(int i = 0; i < length+3; i++)
        ModifiedOne[i] = '\0';
    
    if(Modified[0]=='i'||Modified[0]=='b')//修改information或BookIntro
    {
        char gotten[103];
        InputUntilEnter(gotten);
        unsigned long len = strlen(gotten);
        
        for(int i = 0;i<len;i++)
        {
            if(gotten[i]==' ')
                ModifiedOne[i]='+';
            else
                ModifiedOne[i]=gotten[i];
        }
    }
    else//修改credit||period
    {
        if(strcmp(Modified,"credit")==0)
        {
            printf("You can choose from 1-4.\n");
            ModifiedOne[0] = '0'+OptionInput('4');
        }
        else
        {
            int temp = 0;
            do
            {
                scanf("%s",ModifiedOne);
                unsigned long len = strlen(ModifiedOne);
                if(len>2)//太长了
                    printf("Sorry, your input is too long.\nPlease enter again.\n");
                else if(len==2)
                {
                    if((ModifiedOne[0]<'1'||ModifiedOne[0]>'9')||(ModifiedOne[1]<'0'||ModifiedOne[1]>'9'))//如果有一位不是数字
                        printf("Sorry, your input is invalid.\nPlease enter again.\n");
                    else
                        temp = 1;
                }
                else//一位长度
                {
                    if(ModifiedOne[0]<'1'||ModifiedOne[0]>'9')
                        printf("Sorry, your input is invalid.\nPlease enter again.\n");
                    else
                        temp = 1;
                }
            }while(temp==0);
        }
    }
    
    FILE *fp = fopen("/Users/a123456/Desktop/CourseInfo.txt","a+");
    unsigned long len = strlen(ModifiedOne);
    ModifiedOne[len] = '\t';
    fwrite(ModifiedOne,sizeof(char)*(len+1),1,fp);
    fclose(fp);
}
//----目的：在老师添加选课的过程中添加课程的起止周数------------------------//
//----变量：start||end，字符数组的长度--------------------------------------//
//----输出：无（改变txt文件数组中的内容）-----------------------------------//
void ModifyWeekInfo(void)
{
    char Start[10] = {0};
    char End[10] = {0};//分别储存老师输入的内容
    int temp = 0;//输入合法时，temp = 1
    do
    {
        printf("There are only 20 weeks in the first semester of the 2020-2021 academic year.\n");
        printf("Which week you want to start your class?\n");
        scanf("%s",Start);
        printf("Which week you want to end your class?\n");
        scanf("%s",End);
        
        if(strlen(Start)>2||strlen(End)>2)//要是太长了
            printf("Sorry, your input is too long.\nPlease enter again.\n");
        else if(Start[0]<'1'||Start[0]>'9'||End[0]<'1'||End[0]>'9')//Start或者End的第一位不是数字
            printf("Sorry, your input is invalid.\nPlease enter again.\n");
        else if((strlen(Start)==2&&(Start[1]<'0'||Start[1]>'9'))||(strlen(Start)==2&&(Start[1]<'0'||Start[1]>'9')))//Start或End是两位但第二位不是数字
            printf("Sorry, your input is invalid.\nPlease enter again.\n");
        else
        {
            int start = atoi(Start);
            int end = atoi(End);
            
            if(start>end)
            {
                printf("Sorry, you must start your course first and then end it.\n");
                printf("Please enter again.\n");
            }
            else if(start>20||end>20)
            {
                printf("Sorry, there are only 20 weeks in this semester.\n");
                printf("Please enter again.\n");
            }
            else
            {
                temp = 1;
                //输入合法，开始存入
            temp = 1;
                FILE *fp = fopen("/Users/a123456/Desktop/CourseInfo.txt","a+");
            Start[strlen(Start)] = '\t';
            End[strlen(End)] = '\t';
                fwrite(Start,sizeof(char)*strlen(Start),1,fp);
                fwrite(End,sizeof(char)*strlen(End),1,fp);
                fclose(fp);
            }
          }
            
    }while(temp==0);
    
}
//----目的：老师在添加选课的过程中添加课程具体时间地点----------------------//
//----变量：无--------------------------------------------------------------//
//----输出：无（改变txt文件中的内容）---------------------------------------//
void TimeAndPlace(struct CourseInfo course[],char TeacherName[])
{
    int TAP[6][10];//6个教室 10段时间
    int i=0,j=0;
    int time = 0,place = 0,count = 0,determine = 0;//time place分别用来存放两者的option
    InitTimePlace(TAP);
    
    do
    {
        determine = 0;
        printf("Please choose the specific time you want. \n");
        printf("1. 08:00-08:50 2. 09:00-09:50 3. 10:00-10:50 4. 11:00-11:50\n");
        printf("5. 13:30-14:20 6. 14:30-15:20 7. 15:30-16:20 8. 16:30-17:20\n");
        printf("9. 18:30-19:20 10. 19:30-20:20\n");
        time = OptionInput('9');
        
        if(TimeDuplicateCheck(course,time,TeacherName)==0)//如果时间错不开
            determine = 1;
        i = 0;
        for(i = 0;i<6&&determine==0;i++)
        {
            if(TAP[i][time-1]==0)//available
            {
                count++;
                if(i<3)
                    printf("%d. room 1-10%d ",count,i+1);
                else
                    printf("%d. room 2-10%d ",count,i+1-3);
            }
        }
        if(count==0&&determine!=1)//没有一个教室能用
        {
            printf("Sorry, the time you choose is unavailable.\nPlease choose again.\n");
            determine = 2;
        }
    }while(determine!=0);
    
    char temp[15] = {0};
    switch(time)
    {
        case 1:
            strcpy(temp,"08:00-08:50"); break;
        case 2:
            strcpy(temp,"09:00-09:50"); break;
        case 3:
            strcpy(temp,"10:00-10:50"); break;
        case 4:
            strcpy(temp,"11:00-11:50"); break;
        case 5:
            strcpy(temp,"13:30-14:20"); break;
        case 6:
            strcpy(temp,"14:30-15:20"); break;
        case 7:
            strcpy(temp,"15:30-16:20"); break;
        case 8:
            strcpy(temp,"16:30-17:20"); break;
        case 9:
            strcpy(temp,"18:30-19:20"); break;
        case 10:
            strcpy(temp,"19:30-20:20"); break;
        default:
            break;
    }
    FILE *fp = fopen("/Users/a123456/Desktop/CourseInfo.txt","a+");
    unsigned long len = strlen(temp);
    temp[len] = '\t';
    fwrite(temp,sizeof(char)*(len+1),1,fp);
    //FprintfCourseInfo(temp);
    printf("\n");
    scanf("%d",&place);

    determine = 0;//这个是为了记录能用的教室是第几个了
    for(j = 0;j<count;j++)
    {
        for(i = 0;i<6;i++)//在这个时间里一个一个教室的找
        {
            if(TAP[i][time-1]==0)//available
            {
                determine++;
                if(determine==place)//如果这个就是用户所选
                {
                    TAP[i][time-1] = 1;
                    strcpy(temp,"1-101\t");
                    if(i<3)
                    {
                        temp[0] = '1';
                        temp[4] = '0'+i+1;
                    }
                    else
                    {
                        temp[0] = '1';
                        temp[4] = '0'+i+1-3;
                    }
                }
            }
        }
    }
    len = strlen(temp);
    temp[len] = '\t';
    fwrite(temp,sizeof(char)*(len+1),1,fp);
    fclose(fp);

    FILE *fp2 = fopen("/Users/a123456/Desktop/课程时间地点.txt","w+");
    for(i = 0;i<6;i++)
    {
        for(j = 0;j<10;j++)
            fprintf(fp2,"%d\t",TAP[i][j]);
        fprintf(fp2,"\n");
    }
    fclose(fp2);
}
//----目的：在CourseInfo结构体数组中查找输入的课程姓名是否有重复------------//
//----变量：CourseInfo, 输入的内容------------------------------------------//
//----输出：如果无重复，输出1；否则，输出0----------------------------------//
int DuplicateCheck(struct CourseInfo course[],char gotten[])
{
    int LineNum = GetCourseLineNum();
    
    for(int i = 0;i<LineNum;i++)
    {
        if(strcmp(course[i].name,gotten)==0&&strcmp(course[i].ID,"000000")!=0)
        {
            printf("Sorry, your input is invalid.\n");
            printf("This course exists.\n");
            printf("Please enter again.\n");
            
            return 0;
        }
    }
    
    return 1;
}
//----目的：在CourseInfo结构体数组中查找选择的时间段是否有重复--------------//
//----变量：CourseInfo, 选的内容，加课教师姓名------------------------------//
//----输出：如果，无重复输出1；否则，输出0----------------------------------//
int TimeDuplicateCheck(struct CourseInfo course[],int option,char TeacherName[])
{
    char time[15] = {0};
    switch(option)
    {
        case 1:
            strcpy(time,"08:00-08:50"); break;
        case 2:
            strcpy(time,"09:00-09:50"); break;
        case 3:
            strcpy(time,"10:00-10:50"); break;
        case 4:
            strcpy(time,"11:00-11:50"); break;
        case 5:
            strcpy(time,"13:30-14:20"); break;
        case 6:
            strcpy(time,"14:30-15:20"); break;
        case 7:
            strcpy(time,"15:30-16:20"); break;
        case 8:
            strcpy(time,"16:30-17:20"); break;
        case 9:
            strcpy(time,"18:30-19:20"); break;
        case 10:
            strcpy(time,"19:30-20:20"); break;
        default:
            break;
    }
    
    int LineNum = GetCourseLineNum();
    int i;
    for( i = 0; i <= 7; i++)
    {
        if(TeacherName[i] == '\t')
            TeacherName[i] = '\0';
    }
    for(i = 0;i<LineNum -1;i++)
    {
        if(strcmp(course[i].TeacherName,TeacherName)==0&&strcmp(course[i].ID,"000000")!=0&&strcmp(time,course[i].WhatTime)==0)//同一个老师
        {
            printf("Sorry, this time is unavailable for you.\n");
            printf("You have another class in %s.\n",time);
            
            return  0;
        }
    }
    return 1;
}
//----目的：从键盘上获取一段字符串，知道打入回车键，获取完成----------------//
//----变量：字符串要储存的字符数组------------------------------------------//
//----输出：无（改变字符数组中的内容）--------------------------------------//
void InputUntilEnter(char gotten[])
{
    int i = 0;
    char ch;
    ch = getchar();
    if(ch=='\n')
        ch = getchar();
        
    while(ch!='\n')
    {
        gotten[i] = ch;
        ch = getchar();
        i++;
    }
    gotten[i] = '\0';
}
//----目的：看看接受的字符串是否符合长度要求，且不能有空格------------------//
//----变量：要看的字符串，长度要求------------------------------------------//
//----输出：符合要求，输出1；否则，输出0------------------------------------//
int StringWhetherValid(char recieved[],int length)//只能检测空格和长度
{
    int i;
    
    for(i = 0;recieved[i]!='\0'&&i<length;i++)//check单词与单词之间的空格
    {
        if(recieved[i]==' ')
        {
            printf("Sorry, your input is invalid. \nPlease enter again.\n");
            printf("Remember no whitespace allowed here.\n");
            return 0;
        }
    }
    
    unsigned long len = strlen(recieved);
    if(len>length)
    {
        printf("Sorry, your input is invalid. \nPlease enter again. \n");
        return 0;
    }
    else
        return 1;
}
//----目的：看看接受的字符串长度是否等于所给长度要求，且不能有空格----------//
//----变量：要看的字符串，长度要求------------------------------------------//
//----输出：符合要求，输出1；否则，输出0------------------------------------//
int StringLenDetermined(char recieved[],int length)
{
    unsigned long len = strlen(recieved);
    
    for(int i = 0;i<len;i++)//看看有没有空格，有空格，让重输
    {
        if(recieved[i]==' ')
        {
            printf("Sorry, no whitespace here!\n");
            return 0;
        }
    }
    if(len==length)
        return 1;
    else
    {
        printf("Sorry, you have to enter %d characters.\n",length);
    }
        return 0;
}

//----目的：用于读取用户的选项----------------------------------------------//
//----变量：表示选项的最大值------------------------------------------------//
//----输出：返回读到的选项，一定会返回一个1到high的字符---------------------//

int Admin()
{
        int doo=0;
        int check = 0;
        if(AdminLogin() == 1)
        {
            return 1;
        }
        printf("\nWhat do you want to do?\n");
    do
    {
        check = 0;
        printf("1.TIME->start 2.TIME->end 3.AUTODELETE 4.logout\n");
        doo = OptionInput('4');
        if(doo == 1)
        {
            TIME=1;
            printf("Now that TIME is %d\n", TIME);
        }
        else if(doo == 2)
        {
            TIME=2;
            printf("Now that TIME is %d\n", TIME);
        }
        else if(doo == 3)
        {
            CourseNum = GetCourseLineNum();
            struct CourseInfo course[CourseNum];
            printf("\ndeleting...\n");
            InitCourse(course);
            if(TIME==2)
            {
                AutoDeleteCourse(course);
                CoverCourseInfo(course);
                struct SelectInfo student[StudentNum];
                int i, j;
                for(j = 0; j < CourseNum; j++)
                {
                    for(i = 0; i < StudentNum; i++)
                    {
                        if(strcmp(student[i].Course1,course[j].name) == 0)
                        {
                            strcpy(student[i].Course1, "000000");
                        }
                        else if(strcmp(student[i].Course2,course[j].name) == 0)
                        {
                            strcpy(student[i].Course2, "000000");
                        }
                        else if(strcmp(student[i].Course3,course[j].name) == 0)
                        {
                            strcpy(student[i].Course3, "000000");
                        }
                   }
                }
            }
            else
            {
                printf("ADMIN cannot delete course now!\n");
            }
        }
        else if(doo == 4)
        {
            printf("AUTO:logging out.\n");
            return 1;
        }
            
        else
        {
            printf("\nERROR:You have put in the wrong number.\n");
        }
    }while (check == 0);
    return 0;
}
void AutoDeleteCourse(struct CourseInfo course[])
{
    char initial[7]="000000";
    struct SelectInfo select[StudentNum];
    InitSelect(select);
    int i;
    for( i=0;i<CourseNum ;i++)
    {
        if(strcmp(course[i].ID ,"000000") != 0)
        {
            if(course[i].MaxStudentNum-course[i].RemainNum < 30)
            {
                printf("\nNO. %s will be deleted.\n",course[i].ID);
                for(int j=0;j<StudentNum;j++)
                {
                    if(strcmp(course[i].name,select[j].Course1)==0)
                    {
                        strcpy(select[j].Course1,initial);
                    }
                    if(strcmp(course[i].name,select[j].Course2)==0)
                    {
                        strcpy(select[j].Course2,initial);
                    }
                    if(strcmp(course[i].name,select[j].Course3)==0)
                    {
                        strcpy(select[j].Course3,initial);
                    }
                }
                strcpy(course[i].ID,initial);
                
            }
        }
        
    }
        FILE *fp;
        fp=fopen("/Users/a123456/Desktop/SelectInfo.txt","w");
        for(int i=0;i<StudentNum;i++)
        {
         fprintf(fp,"%s %s %s %s\n",select[i].StuId,select[i].Course1,select[i].Course2,select[i].Course3);
        }
        fclose(fp);
   
}
int AdminLogin (void)
{
    char input[7];
    char key[7]="tom123";
    printf("Please enter your password:");
    printf("\n___");
    scanf("%s", input);
    if(strcmp(input,key)==0)
    {
        printf("HI, Admin!");
    }
    else
    {
        printf("Excess Denied!");
        printf("\nPlease make sure that you are ADMIN.\n");
        return 1;
    }
    return 0;
}

int OptionInput(char high)
{
    int validOption = 0;//等于1表示有效选项
    int option = 0;
    while(!validOption)
    {
        char primitiveInput[10] = {0};//原始输入，存放两个字符就够了，如果超过1个，就提示用户重新输入了
        scanf("%s",primitiveInput);
        if(high < 9)
        {
            if(strlen(primitiveInput) > 2)//如果超过一个字符，用户输入多了，可能是输入错误，需要提示重新输入
                    printf("\nThe choice you entered is too long.\nPlease enter again:\n");
                else if(strlen(primitiveInput) == 0)//如果没有字符，可能是没有输入，提示重新输入
                    printf("\nYou have not enter any choice.\nPlease enter again:\n");
                else if(high=='9')//意味着输入10也可以
                {
                    if(primitiveInput[0]=='1'&&primitiveInput[1]=='0')//输入的是10
                    {
                        option = 10;
                        validOption = 1;
                    }
                    else
                    {
                        option = primitiveInput[0]-'0';//其他情况表示合理
                        if(option>0&&option<high+2)
                            validOption = 1;
                    }
                }
                else
                {
                    option = primitiveInput[0]-'0';//其他情况表示合理
                    if(option>0&&option<high+1-'0')//如果在预定的区间内，表示合理
                        validOption = 1;
                    else//不在预定的区间内，提示重新输入
                        printf("\nThe choice you entered is not a number between 1 and %c.\nPlease enter again:\n", high);
                }
            
        }
        else if(high >= 9)
        {
            if(strlen(primitiveInput) >= 2)//如果超过一个字符，用户输入多了，可能是输入错误，需要提示重新输入
                printf("\nThe choice you entered is too long.\nPlease enter again:\n");
            else if(strlen(primitiveInput) == 0)//如果没有字符，可能是没有输入，提示重新输入
                printf("\nYou have not enter any choice.\nPlease enter again:\n");
            else if(high=='9')//意味着输入10也可以
            {
                if(primitiveInput[0]=='1'&&primitiveInput[1]=='0')//输入的是10
                {
                    option = 10;
                    validOption = 1;
                }
                else
                {
                    option = primitiveInput[0]-'0';//其他情况表示合理
                    if(option>0&&option<high+2)
                        validOption = 1;
                }
            }
            else
            {
                option = primitiveInput[0]-'0';//其他情况表示合理
                if(option>0&&option<high+1-'0')//如果在预定的区间内，表示合理
                    validOption = 1;
                else//不在预定的区间内，提示重新输入
                    printf("\nThe choice you entered is not a number between 1 and %c.\nPlease enter again:\n", high);
            }
        }
    }
        
    return option;//一定会返回一个1到high的字符
}
