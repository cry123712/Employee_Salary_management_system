#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"function.h"
#include"system.h"
#include"function1.h"

int main() {
    Employee* employees = NULL; // ��ʼ��Ա������ͷָ��
    FILE* fp = fopen("text.txt", "r");
    if (fp == NULL) {
        printf("error\n");
        return -1;
    }
    fclose(fp);
    loadEmployees(&employees);
    initializeMaxEmployeeId();
    // �Զ�����Ա������
    int choice1;
    do {
        printf("\n===== Ա��������ϵͳ =====\n");
        printf("1��������Ϣ���˳�ϵͳ\n");

        printf("2��Ա�������������ݹ���\n");
        printf("3��Ա���������ݹ���\n");

        printf("4����ѯ����\n");
        printf("5������\n");
        printf("6��ͳ��\n");

        printf("��ѡ�������");

        scanf("%d", &choice1);
        switch (choice1) {
        case 1:
            saveEmployees(employees);
            break;
        case 2:
            showEmployeeMenu(employees);
            break;
        case 3:
            showSalaryMenu(employees);
            break;
        case 4:
            search(employees);
            break;
        case 5:
            RankSalary(employees);
            break;
        case 6:
            statistics(employees);
            break;
        default:
            printf("������������Ч��ѡ�\n");
        }
    } while (choice1 != 1);

    Employee* current = employees;
    Employee* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
        return 0;
    }
    fclose(fp);
}
   