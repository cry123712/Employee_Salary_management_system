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
        printf("\n===== 员工基本资料数据管理系统 =====\n");
        printf("1. 退出\n");
     
        printf("2. 添加新员工\n");
        printf("3. 修改员工信息\n");
        printf("4. 删除员工\n");
        printf("5. 查询员工\n");

        printf("请选择操作：");

        scanf("%d", &choice2);
        switch (choice2) {
        case 1:
            //saveEmployees(employees); // 保存数据
            //printf("数据已保存，退出系统\n");
           // exit(0);
            break;
        case 2:
            addEmployee(&employees);
            printf("新增员工成功\n");
            break;
        case 3:
            modifyEmployee(employees);
            printf("修改员工信息成功\n");
            break;
        case 4:
            deleteEmployee(&employees);
            printf("删除员工成功\n");
            break;
        case 5:
            searchEmployee(employees);
            printf("查询员工成功\n");
            break;

        default:
            printf("错误：请输入有效的选项！\n");
        }
    } while (choice2 != 1);
}

void  showSalaryMenu(Employee*employees) {
    int choice3;
    do {
        printf("\n===== 员工工资数据管理系统 =====\n");
        printf("1、工资数据保存并退出\n");
        printf("2、输入员工工资数据\n");
        printf("3、修改员工的相关工资数据\n");
        printf("4、删除员工\n");
        printf("5、查询员工的工资数据\n");
        printf("6、计算员工当月工资\n");

        printf("请选择操作：");

        scanf("%d", &choice3);
        switch (choice3) {
        case 1:
           saveEmployees(employees);
           printf("数据已保存，退出系统\n");
            break;
        case 2:
            inputMonthlySalary(employees);
            printf("输入员工工资信息成功\n");
            break;
        case 3:
            changeMonthlySalary(employees);
            printf("员工工资信息修改成功\n");
            break;
        case 4:
            deletemployeeSalary(employees);
            printf("员工工资信息删除成功\n");
            break;
        case 5:
            searchSalary(employees);
            printf("员工工资信息查询成功\n");
            break; 
        case 6:
            calculateMonthlySalary(employees);
            printf("员工工资计算成功\n");
            break;
        default:
            printf("错误：请输入有效的选项！\n");
        }
    } while (choice3 != 1);
}

void search(Employee*employees) {
    int choice4;
    do {
        printf("\n===== 员工查询系统 =====\n");
        printf("1、退出\n");
        printf("2、分页显示全部员工的信息\n");
        printf("3、按部门显示本部门全部员工信息\n");
        printf("4、分类显示4种岗位的员工信息\n");
        printf("5、根据工号或者姓名查询员工信息\n");

        printf("请选择操作：");
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
            printf("错误：请输入有效的选项！\n");
        }

    } while (choice4 != 1);
}
//排序无法完成
void RankSalary(Employee* employees) {
    int choice5;
    do {
        printf("\n===== 员工工资排序系统 =====\n");
        printf("1、退出\n");
        printf("2、全体工资排序\n");
        printf("3、分岗位排序\n");
     
        printf("请选择操作：");
        scanf("%d", &choice5);

        switch (choice5) {
        case 1:
            break;
        case 2:
            All_Rank(employees);
            printf("排序完成！\n");
            break;
        case 3:
            Some_Rank(employees);
            printf("排序完成！\n");
            break;
        default:
            printf("错误：请输入有效的选项！\n");
        }
    } while (choice5 != 1);
}

void statistics(Employee* employees) {
    int choice6;
    do {
        printf("\n===== 员工工资统计系统 =====\n");
        printf("1、退出\n");
        printf("2、统计并显示某个部门的平均工资、最低工资、最高工资\n");
        printf("3、统计并显示某个部门超出平均工资的人数与员工信息\n");
        printf("4、统计并显示所有员工中的最低工资和最高工资员工的信息\n");
        printf("5、统计并显示所有员工超出平均工资的人数与员工信息\n");

        printf("请选择：\n");
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
            printf("错误：请输入有效的选项！\n");
        }

    } while (choice6 != 1);
}