#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "head.h"

int welcome()
{

       printf("----------------Welcome------------------");
       printf("\nThis is ZARA. What can I do for you?\n");

       printf("\nPlease Choose your identity:");
       printf("\n1.Student\n2.Teacher\n3.Admin\n");
    
        int validOption = 0;//等于1表示有效选项
        int option = 0;
        while(!validOption)
        {
            char primitiveInput[10] = {0};//原始输入，存放两个字符就够了，如果超过1个，就提示用户重新输入了
            scanf("%s",primitiveInput);
            if(strlen(primitiveInput) >= 2)//如果超过一个字符，用户输入多了，可能是输入错误，需要提示重新输入
                printf("\nThe choice you entered is too long.\nPlease enter again:\n");
            else if(strlen(primitiveInput) == 0)//如果没有字符，可能是没有输入，提示重新输入
                printf("\nYou have not enter any choice.\nPlease enter again:\n");
            else
            {
                option = primitiveInput[0]-'0';//其他情况表示合理
                if(option>0&&option<4)//如果在预定的区间内，表示合理
                    validOption = 1;
                else//不在预定的区间内，提示重新输入
                    printf("\nThe choice you entered is not a number between 1 and 3.\nPlease enter again:\n");
            }
        }

        if(option==1)
        {
           printf("Welcome Student!\n");
            return option;
        }
        else if(option==2)
        {
           printf("Welcome Teacher!\n");
            return option;
        }
        else if(option==3)
        {
           printf("Welcome Admin!\n");
            return option;
        }
        else
        {
           printf("Sorry, please input the number 1-3");
        }
    
    return option;
}

