#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"function.h"
#include"system.h"
#include"function1.h"

int main() {
    Employee* employees = NULL; // 初始化员工链表头指针
    FILE* fp = fopen("text.txt", "r");
    if (fp == NULL) {
        printf("error\n");
        return -1;
    }
    fclose(fp);
    loadEmployees(&employees);
    initializeMaxEmployeeId();
    // 自动加载员工数据
    int choice1;
    do {
        printf("\n===== 员工管理主系统 =====\n");
        printf("1、保存信息并退出系统\n");

        printf("2、员工基本资料数据管理\n");
        printf("3、员工工资数据管理\n");

        printf("4、查询数据\n");
        printf("5、排序\n");
        printf("6、统计\n");

        printf("请选择操作：");

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
            printf("错误：请输入有效的选项！\n");
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
   