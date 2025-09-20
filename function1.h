#pragma once
#include"function.h"

#define PAGE_SIZE 10

//辅助函数：根据指针打印该员工基本信息和工资信息
void printEmployee(Employee* current) {
    
    if (current != NULL) {
        printf("员工号：%d;名字：%s;性别：%c;部门：%s;职位：%s;工龄：%d;",
            current->employeeId,
            current->name,
            current->gender,
            current->department,
            PositionToString(current->position),
            current->seniority);
        printf("工时：%.2f;小时工资：%.2f;销售额：%.2f;底薪：%.2f;当月工资：%.2f;",
            current->salaryData.workingHours,
            current->salaryData.hourlyRate,
            current->salaryData.salesAmount,
            current->salaryData.baseSalary,
            current->salaryData.monthlySalary);
    }
    printf("\n");
}
//辅助函数：显示当前页的员工信息
void displayEmployees(Employee* head, int currentPage) {
    Employee* current = head;
    int count = 0;
    int start = (currentPage - 1) * PAGE_SIZE;
    int end = start + PAGE_SIZE;

    // 遍历链表，跳到正确的起始点
    for (int i = 0; i < start && current != NULL; ++i) {
        current = current->next;
    }
    printf("\nPage %d\n", currentPage);
    printf("--------------------------------------------------\n");

    while (current != NULL && count < PAGE_SIZE) {
        printEmployee(current);
        current = current->next;
        count++;
    }
}
//辅助函数：计算最大员工人数（注意：包含了在工资信息管理系统里面删除掉的员工，信息含-1）
int count_maxemployees(Employee* head) {
    Employee* p = head;
    int count = 0;
    while (p != NULL) { // 遍历链表
        count++; // 每遇到一个节点，计数加1
       p =p->next; // 移动到下一个节点
    }
    return count; // 返回员工总数
}
//功能函数：分页功能
void page(Employee* head) {
    int currentPage = 1;
    int totalEmployees =count_maxemployees(head);// 链表中员工总数的变量
    int choice;
    do {
        printf("===== 员工信息分页显示 =====\n");
        printf("当前页: %d\n", currentPage);
        printf("总员工数: %d\n", totalEmployees);
        printf("1. 上一页\n");
        printf("2. 下一页\n");
        printf("3. 首页\n");
        printf("4. 最后页\n");
        printf("5. 退出\n");
        printf("请选择操作：");

        scanf("%d", &choice);

        switch (choice) {
        case 1: // 上一页
            if (currentPage > 1) {
                currentPage--;
            }
            displayEmployees(head, currentPage);
            break;
        case 2: // 下一页
            if ((currentPage * PAGE_SIZE) < totalEmployees) {
                currentPage++;
            }
            displayEmployees(head, currentPage);
            break;
        case 3: // 首页
            currentPage = 1;
            displayEmployees(head, currentPage);
            break;
        case 4: // 最后页
            currentPage = (totalEmployees + PAGE_SIZE - 1) / PAGE_SIZE;
            displayEmployees(head, currentPage);
            break;
        case 5: // 退出
          // exit(0);
            break;
        default:
            printf("无效的选择，请重新选择。\n");
            break;
        }
    }while (choice != 5);
}

//功能函数：按部门显示本部门全部员工信息
//怎么解决已经查找过的不再查找问题
void department_show(Employee* head) {
    DepartmentSales* departments= Department(head);
    Employee* p;
    for (int i = 0; i < department_size; ++i) {
        if (departments[i].department[0] != '\0') {
            p = head;
            printf("department:%s             \n", departments[i]);
            printf("--------------------------------------------------\n");
            while (p != NULL) {
               
                if (strcmp(p->department, departments[i].department) == 0) {
                    
                    printEmployee(p);

                 }
                p = p->next;
            }
        }
    }
    free(departments);
}
//功能函数：按职位显示本职位全部员工信息
void position_show(Employee* head) {
    Employee* p = head;
    Position a[4] = { manager,technician,saleman,sales_manager };

    for (int i = 0; i < 4; i++) {
        printf("position:%s             \n", PositionToString(a[i]));
        printf("--------------------------------------------------\n");
        p = head;
        while (p != NULL) {
            if (p->position == a[i]) {
                printEmployee(p);
            }
            p = p->next;
        }
    }
}
//辅助函数：通过姓名查找员工
void search_By_name(Employee* head, char name[]) {
    Employee* p = head;
    while (p != NULL &&strcmp(p->name,name)!=0) {
        p = p->next;
    }
    if (p != NULL) {
        printEmployee(p);
    }
    else {
        printf("未找到该姓名的员工\n");
    }
}
//辅助函数：通过职工编号查找员工
void search_By_Id(Employee* head, int Id) {
    Employee* p = head;
    while (p != NULL && p->employeeId != Id) {
        p = p->next;
    }
    if (p != NULL) {
        printEmployee(p);
    }
    else {
        printf("未找到该编号的员工\n");
    }
}
//功能函数：通过职工号或者姓名查询员工信息
void search_By_Id_name(Employee* head) {
    int choice;
    do {
        printf("请选择查询方式\n");
        printf("1、退出\n");
        printf("2、姓名\n");
        printf("3、员工号\n");

        scanf("%d", &choice);
        switch(choice){
        case 1:
            break;
        case 2:
            printf("请输入要查询的员工姓名\n");
            char name[20];
            scanf("%19s",name);
            search_By_name(head, name);
            break;
        case 3:
            printf("请输入要查询的员工的职工号\n");
            int Id;
            scanf("%d", &Id);
            search_By_Id(head, Id);
            break;
        default:
            printf("无效的选择，请重新选择。\n");
            break;
        }
    } while (choice != 1);
}

//辅助函数:根据指针复制该结点
Employee* copyEmployee(const Employee* src) {
    if (src==NULL) return NULL;

    Employee* newEmp = (Employee*)malloc(sizeof(Employee));
    if (newEmp==NULL) return NULL; // 检查内存是否成功分配

    // 复制非指针成员
    newEmp->employeeId = src->employeeId;
    strncpy(newEmp->name, src->name, sizeof(newEmp->name));
    newEmp->name[sizeof(newEmp->name) - 1] = '\0';
    newEmp->gender = src->gender;
    strncpy(newEmp->department, src->department, sizeof(newEmp->department));
    newEmp->department[sizeof(newEmp->department) - 1] = '\0';
    newEmp->position = src->position;
    newEmp->seniority = src->seniority;
    // 复制SalaryData结构体
    newEmp->salaryData = src->salaryData;

    // 正确处理next指针
    newEmp->next = NULL;
   /* if (src->next) {
        newEmp->next = copyEmployee(src->next);
    }*/
    return newEmp;
}
//辅助函数:建立数值，把原本链表里面的信息存下来（在这个基础上去更改）
Employee* Saving(Employee* head) {
    Employee* newHead = NULL; // 新链表的头指针
    Employee* newTail = NULL; // 新链表的尾指针
    Employee* current = head; // 当前遍历到的节点
    // 遍历原链表，复制每个节点
    while (current != NULL) {
        Employee* newEmp = copyEmployee(current);
        if (newEmp == NULL) {
            // 处理内存分配失败的情况
            return NULL;
        }
        if (newHead == NULL) {
            newHead = newEmp; // 新链表的第一个节点
        }
        if (newTail != NULL) {
            newTail->next = newEmp; // 连接新节点到链表
        }
        newTail = newEmp; // 更新新链表的尾指针
        current = current->next; // 移动到原链表的下一个节点
    }
    return newHead; // 返回新链表的头指针
}
// 辅助函数:交换两个员工结点,要保证结点的前驱后继，不能丢失

// 辅助函数：交换两个员工结点
void swap(Employee*& head, Employee* p, Employee* q) {
    // 如果p和q是同一个节点或者其中一个是NULL，不需要交换
    if (p == q || p == NULL || q == NULL) return;

    // 找到p和q的前驱节点
    Employee* prevP = (p == head) ? NULL : p->next; // p的前驱是NULL或者p的下一个节点
    Employee* prevQ = (q == head) ? NULL : q->next; // q的前驱是NULL或者q的下一个节点

    // 特殊情况处理：p是头节点或者q是头节点
    if (p == head) {
        head = q;
    }
    else if (q == head) {
        head = p;
    }

    // 如果p的前驱存在，则将p的前驱指向q
    if (prevP != NULL) {
        prevP->next = q;
    }

    // 如果q的前驱存在，则将q的前驱指向p
    if (prevQ != NULL) {
        prevQ->next = p;
    }

    // 交换p和q的next指针
    p->next = prevQ;
    q->next = prevP;
}
// 功能函数：对所有员工当月工资排序（由高到低）
void All_Rank(Employee*& head) {
    if (head == NULL || maxEmployeeId == 0) return;

    bool swapped;
    do {
        swapped = false;
        Employee* current = head;
        while (current->next != NULL) { // 确保current不是最后一个节点
            Employee* next = current->next; // 保存下一个节点
            if (current->salaryData.monthlySalary < current->next->salaryData.monthlySalary) {
                swap(head, current,current->next);
                swapped = true;
            }
            current =next;
        }
        //循环出不来,停留在最小数组一行
    } while (swapped);
}

// 辅助函数：对特定部门的员工链表进行排序
void SortDepartmentEmployees(Employee*& head, const char* departmentName) {
    Employee* sortedHead = NULL; // 用于维护排序后的链表头部
    Employee* current = head;
    Employee* prev = NULL;
    Employee* temp = NULL;

    // 遍历整个员工链表，找到属于特定部门的员工
    while (current != NULL) {
        if (strcmp(current->department, departmentName) == 0) {
            // 如果当前员工属于特定部门，则进行排序
            temp = current;
            if (prev == NULL) {
                // 如果当前是第一个节点，设置sortedHead
                sortedHead = temp;
            }
            else {
                // 将当前节点插入到已排序链表中
                prev->next = temp;
            }

            // 从链表中移除当前节点，并更新prev和current指针
            prev = temp;
            temp = temp->next;
            current->next = NULL;
        }
        else {
            prev = current;
            current = current->next;
        }
    }

    // 对提取的特定部门员工链表进行冒泡排序
    bool swapped;
    do {
        swapped = false;
        temp = sortedHead;
        while (temp->next != NULL) {
            if (temp->salaryData.monthlySalary < temp->next->salaryData.monthlySalary) {
                swap(sortedHead, temp, temp->next);
                swapped = true;
            }
            temp = temp->next;
        }
    } while (swapped);

    // 将排序后的特定部门员工链表重新连接到原链表中
    if (prev != NULL) {
        prev->next = temp;
    }
    else {
        head = sortedHead;
    }
}

//功能函数：分岗位对员工当月工资排序(由高到低）
void Some_Rank(Employee*& head) {
    DepartmentSales* departments = Department(head); // 获取部门信息
    for (int i = 0; i < department_size; ++i) {
        if (departments[i].department[0] != '\0') {
            printf("Department: %s\n", departments[i].department);
            SortDepartmentEmployees(head, departments[i].department); // 对每个部门的员工进行排序
        }
    }
    free(departments); // 释放部门数组
}

//功能函数：统计并显示某个部门的平均工资、最低工资、最高工资
void statistics_department(Employee* head) {
    DepartmentSales* departments = Department(head);
    Employee* p;
    for (int i = 0; i < department_size; ++i) {
        if (departments[i].department[0] != '\0') {
            p = head;
            float sum = 0;
            int count = 0;
            float averageSalary;
            float minSalary = INFINITY;
            float maxSalary = -INFINITY;
            
            while (p != NULL) {
                if (strcmp(p->department, departments[i].department) == 0&&p->salaryData.monthlySalary!=-1) {
                    sum += p->salaryData.monthlySalary;
                    count++;
                    if (p->salaryData.monthlySalary < minSalary) minSalary = p->salaryData.monthlySalary;
                    if (p->salaryData.monthlySalary > maxSalary) maxSalary = p->salaryData.monthlySalary;
                }
                p = p->next;
            }
            averageSalary = count > 0 ? sum / count : 0;
         
            printf("--------------------------------------------------\n");
            printf("%s部门的情况如下:\n", departments[i].department);
            printf("平均工资: %.2f\n", averageSalary);
            printf("最低工资: %.2f\n", minSalary);
            printf("最高工资: %.2f\n", maxSalary);
           
        }
    }
    free(departments);
}
//功能函数：统计并显示某个部门超出平均工资的人数与员工信息
void statistics_department_over(Employee* head) {
    DepartmentSales* departments = Department(head);
    for (int i = 0; i < department_size; ++i) {
        if (departments[i].department[0] != '\0') {
            int countOverAverage = 0;
            float averageSalary;
            int count = 0;
            float sum = 0;
            Employee* p = head;
          
            while (p != NULL) {
                if (strcmp(p->department, departments[i].department) == 0&& p->salaryData.monthlySalary != -1){

                        sum += p->salaryData.monthlySalary;
                        count++;
                }
                p = p->next;
            }
            averageSalary = count > 0 ? sum / count : 0;
            p = head;
            while (p != NULL) {
                if (strcmp(p->department, departments[i].department) == 0 && p->salaryData.monthlySalary > averageSalary) {
                    countOverAverage++;
                    printEmployee(p);
                }
                p = p->next;
            }
            printf("%s部门超出平均工资的员工人数为: %d,这部分员工信息如上\n", departments[i].department, countOverAverage);
            printf("--------------------------------------------------\n");
        }
    }
    free(departments);
}
//功能函数：统计并显示所有员工中的最低工资和最高工资员工的信息
void Find_low_Hight(Employee* head) {
    if (head == NULL) return; // 如果链表为空，直接返回
    Employee* current = head;
    while (current->salaryData.monthlySalary == -1) {
        current = current->next;
    }
    Employee* max = current; // 假设第一个员工是工资最高的
    Employee* min = current; // 假设第一个员工是工资最低的
    Employee* p = head;
    
    while (p != NULL) {
       
        if (p->salaryData.monthlySalary != -1 ) {
            // 更新最高工资和最低工资的员工
            if (p->salaryData.monthlySalary > max->salaryData.monthlySalary) {
                max = p;
            }
            if (p->salaryData.monthlySalary < min->salaryData.monthlySalary) {
                min = p;
            }
        }
        p = p->next;
    }
    printf("全体员工中最高工资员工信息为:\n");
    printEmployee(max);
    printf("全体员工中最低工资员工信息为:\n");
    printEmployee(min);
}
//功能函数：统计并显示所有员工超出平均工资的人数与员工信息
void statistics_over(Employee* head) {
    int count=0;
    int Overcount=0;
    float sum = 0;
    float average = 0;
    Employee* p = head;
    while (p != NULL && p->salaryData.monthlySalary != -1) {
        sum +=p->salaryData.monthlySalary;
        count++;
        p = p->next;
    }
    average = sum / count;
    printf("全体员工平均工资为%.2f\n", average);
    p = head;
    while (p != NULL) {
        if (p->salaryData.monthlySalary > average) {
            printEmployee(p);
            Overcount++;
        }
        p = p->next;
    }
    printf("全体员工中超过平均工资的员工人数有%d个，信息如上：\n", Overcount);
}

