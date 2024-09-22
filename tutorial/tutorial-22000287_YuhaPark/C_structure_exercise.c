/*-------------------------------------------------------------------------------\
@ C-Tutorial by Yuha-Park - Handong Global University
Author           : �ڵ� ����
Created          : 29-08-2024
Modified         : 29-08-2024
Language/ver     : C in MSVS2022
Description      : C_structure_exercise.c
-------------------------------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[20];
    int grade;
    int class;
    float average;
};

int main()
{
    struct Student* s1 = malloc(sizeof(struct Student));

    strcpy(s1->name, "Yuha_Park");
    s1->grade = 3;
    s1->class = 1;
    s1->average = 65.38999f;

    printf("�̸�: %s\n", s1->name);
    printf("�г�: %d\n", s1->grade);
    printf("��: %d\n", s1->class);
    printf("�������: %f\n", s1->average);

    free(s1);

    return 0;
}