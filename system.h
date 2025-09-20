#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<malloc.h>
#include <ctype.h>
#include"function1.h"

void showEmployeeMenu(Employee* employees) {
    int choice2;
    do {
        printf("\n===== Ա�������������ݹ���ϵͳ =====\n");
        printf("1. �˳�\n");
     
        printf("2. �����Ա��\n");
        printf("3. �޸�Ա����Ϣ\n");
        printf("4. ɾ��Ա��\n");
        printf("5. ��ѯԱ��\n");

        printf("��ѡ�������");

        scanf("%d", &choice2);
        switch (choice2) {
        case 1:
            //saveEmployees(employees); // ��������
            //printf("�����ѱ��棬�˳�ϵͳ\n");
           // exit(0);
            break;
        case 2:
            addEmployee(&employees);
            printf("����Ա���ɹ�\n");
            break;
        case 3:
            modifyEmployee(employees);
            printf("�޸�Ա����Ϣ�ɹ�\n");
            break;
        case 4:
            deleteEmployee(&employees);
            printf("ɾ��Ա���ɹ�\n");
            break;
        case 5:
            searchEmployee(employees);
            printf("��ѯԱ���ɹ�\n");
            break;

        default:
            printf("������������Ч��ѡ�\n");
        }
    } while (choice2 != 1);
}

void  showSalaryMenu(Employee*employees) {
    int choice3;
    do {
        printf("\n===== Ա���������ݹ���ϵͳ =====\n");
        printf("1���������ݱ��沢�˳�\n");
        printf("2������Ա����������\n");
        printf("3���޸�Ա������ع�������\n");
        printf("4��ɾ��Ա��\n");
        printf("5����ѯԱ���Ĺ�������\n");
        printf("6������Ա�����¹���\n");

        printf("��ѡ�������");

        scanf("%d", &choice3);
        switch (choice3) {
        case 1:
           saveEmployees(employees);
           printf("�����ѱ��棬�˳�ϵͳ\n");
            break;
        case 2:
            inputMonthlySalary(employees);
            printf("����Ա��������Ϣ�ɹ�\n");
            break;
        case 3:
            changeMonthlySalary(employees);
            printf("Ա��������Ϣ�޸ĳɹ�\n");
            break;
        case 4:
            deletemployeeSalary(employees);
            printf("Ա��������Ϣɾ���ɹ�\n");
            break;
        case 5:
            searchSalary(employees);
            printf("Ա��������Ϣ��ѯ�ɹ�\n");
            break; 
        case 6:
            calculateMonthlySalary(employees);
            printf("Ա�����ʼ���ɹ�\n");
            break;
        default:
            printf("������������Ч��ѡ�\n");
        }
    } while (choice3 != 1);
}

void search(Employee*employees) {
    int choice4;
    do {
        printf("\n===== Ա����ѯϵͳ =====\n");
        printf("1���˳�\n");
        printf("2����ҳ��ʾȫ��Ա������Ϣ\n");
        printf("3����������ʾ������ȫ��Ա����Ϣ\n");
        printf("4��������ʾ4�ָ�λ��Ա����Ϣ\n");
        printf("5�����ݹ��Ż���������ѯԱ����Ϣ\n");

        printf("��ѡ�������");
        scanf("%d", &choice4);

        switch (choice4) {
        case 1:
            //exit(0);
            break;
        case 2:
            page(employees);
            break;
        case 3:
            department_show(employees);
            break;
        case 4:
            position_show(employees);
            break;
        case 5:
            search_By_Id_name(employees);
            break;
        default:
            printf("������������Ч��ѡ�\n");
        }

    } while (choice4 != 1);
}
//�����޷����
void RankSalary(Employee* employees) {
    int choice5;
    do {
        printf("\n===== Ա����������ϵͳ =====\n");
        printf("1���˳�\n");
        printf("2��ȫ�幤������\n");
        printf("3���ָ�λ����\n");
     
        printf("��ѡ�������");
        scanf("%d", &choice5);

        switch (choice5) {
        case 1:
            break;
        case 2:
            All_Rank(employees);
            printf("������ɣ�\n");
            break;
        case 3:
            Some_Rank(employees);
            printf("������ɣ�\n");
            break;
        default:
            printf("������������Ч��ѡ�\n");
        }
    } while (choice5 != 1);
}

void statistics(Employee* employees) {
    int choice6;
    do {
        printf("\n===== Ա������ͳ��ϵͳ =====\n");
        printf("1���˳�\n");
        printf("2��ͳ�Ʋ���ʾĳ�����ŵ�ƽ�����ʡ���͹��ʡ���߹���\n");
        printf("3��ͳ�Ʋ���ʾĳ�����ų���ƽ�����ʵ�������Ա����Ϣ\n");
        printf("4��ͳ�Ʋ���ʾ����Ա���е���͹��ʺ���߹���Ա������Ϣ\n");
        printf("5��ͳ�Ʋ���ʾ����Ա������ƽ�����ʵ�������Ա����Ϣ\n");

        printf("��ѡ��\n");
        scanf("%d", &choice6);

        switch (choice6) {
        case 1:
            break;
        case 2:
            statistics_department(employees);
            break;
        case 3:
            statistics_department_over(employees);
            break;
        case 4:
            Find_low_Hight(employees);
            break;
        case 5:
            statistics_over(employees);
            break;
        default:
            printf("������������Ч��ѡ�\n");
        }

    } while (choice6 != 1);
}