#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<malloc.h>
#include <ctype.h>
#include<math.h>

// 全局变量，用于存储当前最大的员工编号
static int maxEmployeeId = 0;

#define MAX_LINE_LENGTH 1024
#define EXPECTED_FIELD_COUNT 11
#define department_size 10

// 定义枚举类型，表示员工的岗位
typedef enum {
    manager,//经理
    technician,//技术员
    saleman,//销售员
    sales_manager//销售经理
} Position;

// 员工工资数据结构
typedef struct {
    float workingHours;
    float hourlyRate;
    float salesAmount;
    float baseSalary;
    float monthlySalary; // 计算项，不可手动输入
} SalaryData;

// 员工基本数据结构
typedef struct Employee {
    int employeeId;//系统自动生成
    char name[50];
    char gender;
    char department[50];
    Position position;
    int seniority;
    SalaryData salaryData;
    struct Employee* next; // 指向下一个员工的指针
} Employee;
//有关销售额的
typedef struct {
    char department[50];
    float totalSales; // 该部门所有销售员和销售经理的销售额总和
    float managerSalary; //该部门经理的销售额
    //float averageSalary;
} DepartmentSales;

//辅助函数：创建结构体成员, 初始化结构体成员
Employee* createEmployee() {
    Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
    if (!newEmployee) {
        perror("Memory allocation failed");
        return NULL;
    }
  
    newEmployee->salaryData.workingHours = 0.00;
    newEmployee->salaryData.hourlyRate = 0.00;
    newEmployee->salaryData.salesAmount = 0.00;
    newEmployee->salaryData.baseSalary = 0.00;
    newEmployee->salaryData.monthlySalary = 0.00;
    newEmployee->next = NULL;
    return newEmployee;
}
//辅助函数：打开文件找到最大编号
void initializeMaxEmployeeId() {
    FILE* file = fopen("text.txt", "r");
    if (!file) {
        maxEmployeeId = 1; // 如果文件不存在，从1开始
    }
    else {
        Employee temp;
        // 假设每个员工的编号是文件中的第一列
        while (fscanf(file, "%d", &temp.employeeId) > 0) {
            if (temp.employeeId > maxEmployeeId) {
                maxEmployeeId = temp.employeeId;
            }
        }
    }
    fclose(file);
}
// 辅助函数：将 Position 枚举和字符串相互转换的函数
Position stringToPosition(const char* positionStr) {
    char buffer[20];
    strncpy(buffer, positionStr, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    for (int i = 0; buffer[i]; ++i) {
        buffer[i] = tolower((unsigned char)buffer[i]);
    }
    if (strcmp(buffer, "manager") == 0) {
        return manager;
    }
    else if (strcmp(buffer, "technician") == 0) {
        return technician;
    }
    else if (strcmp(buffer, "saleman") == 0) {
        return saleman;
    }
    else if (strcmp(buffer, "sales_manager") == 0) {
        return sales_manager;
    }
    else {
        fprintf(stderr, "Unknown position '%s', defaulting to 'manager'.\n", positionStr);
        return manager;
    }
}
const char* PositionToString(Position pos) {
    switch (pos) {
    case manager: return "manager";
    case technician: return "technician";
    case saleman: return "saleman";
    case sales_manager: return "sales_manager";
    default: return "unknown";
    }
}
//功能函数：新增
void addEmployee(Employee** head) {
    printf("请输入要增加的员工人数:\n");
    int n;
    scanf("%d", &n);
   
    for (int i = 0; i < n; i++) {
      
        Employee* newEmployee = createEmployee();
        newEmployee->employeeId = ++maxEmployeeId;
        newEmployee->next = NULL;
        printf("请输入新增第%d个员工的姓名: ", i + 1);
        scanf("%49s", newEmployee->name);
      

        printf("请输入新增第%d个员工的性别 (M/F): ", i + 1);
        scanf(" %c", &newEmployee->gender);

        printf("请输入新增第%d个员工的部门: ", i + 1);
        scanf("%49s", newEmployee->department);
 
        // 职务读取和错误处理
        printf("请输入新增第%d个员工的职务: ", i + 1);
        char positionStr[20];
        scanf("%19s", positionStr); // 使用 %19s 防止缓冲区溢出
        newEmployee->position = stringToPosition(positionStr);

        // 工作年限读取
        printf("请输入新增第%d个员工的工作年限: ", i + 1);
        scanf("%d", &newEmployee->seniority);
        //// 初始化工资数据
        //memset(&newEmployee->salaryData, 0, sizeof(SalaryData));

        //FILE* file = fopen("text.txt", "a");
        //fprintf(file, "%d;%s;%c;%s;%s;%d\n", newEmployee->employeeId, newEmployee->name, newEmployee->gender, newEmployee->department, positionStr, newEmployee->seniority);
        //fclose(file);

        Employee* current = *head;
        if (current == NULL) {
            *head = newEmployee;
        }
        else {
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newEmployee;
        }
     
    } 
}
//辅助函数：loadEmployees函数是将文本文件中原有的读入链表
void loadEmployees(Employee** head) {
    FILE* file = fopen("text.txt", "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file)) { // 使用 fgets 来读取整行
        char* token, * lineCopy = _strdup(line); // 创建行内容的副本

        Employee* newEmployee = createEmployee(); // 使用之前定义的函数创建员工
        if (!newEmployee) {
            free(lineCopy); // 如果创建员工失败，释放副本的内存
            continue;
        }

        token = strtok(lineCopy, ";");
        int parsedFields = 0;
        while (token != NULL) {
            switch (parsedFields) {
            case 0:
                newEmployee->employeeId = atoi(token);
                if (newEmployee->employeeId > maxEmployeeId) {
                    maxEmployeeId = newEmployee->employeeId;
                }
                break;
            case 1:
                strncpy(newEmployee->name, token, sizeof(newEmployee->name) - 1);
                newEmployee->name[sizeof(newEmployee->name) - 1] = '\0';
                break;
            case 2:
                newEmployee->gender = token[0];
                break;
            case 3:
                strncpy(newEmployee->department, token, sizeof(newEmployee->department) - 1);
                newEmployee->department[sizeof(newEmployee->department) - 1] = '\0';
                break;
            case 4:
                newEmployee->position = stringToPosition(token);
                break;
            case 5:
                newEmployee->seniority = atoi(token); // 使用 atoi 函数将字符串转换为整数
                break;
            case 6:
                newEmployee->salaryData.workingHours = atof(token);
                break;
            case 7:
                newEmployee->salaryData.hourlyRate = atof(token);
                break;
            case 8:
                newEmployee->salaryData.salesAmount = atof(token);
                break;
            case 9:
                newEmployee->salaryData.baseSalary = atof(token);
                break;
            case 10:
                newEmployee->salaryData.monthlySalary = atof(token);
                break;
            default:
                // 如果字段超过预期数量，处理错误或忽略
                break;
            }
            parsedFields++;
            token = strtok(NULL, ";");
        }
            if (parsedFields < EXPECTED_FIELD_COUNT) { // 确保解析了预期数量的字段
                // 数据不完整，释放内存
                free(newEmployee);
                continue;
            }
           
                Employee* current = *head;
                if (current == NULL) {
                    newEmployee->next = NULL;
                    *head = newEmployee;
                }
                else {
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = newEmployee;
                    newEmployee->next = NULL;
                }
 
       free(lineCopy); // 释放行副本的内存
        }
    fclose(file); // 关闭文件
 }
//功能函数：根据职工号来修改任意员工的除职工号外的其他基本资料数据
void modifyEmployee(Employee* head) {
    //先在链表修改后回到文本文件修改
    //FILE* fp = fopen("text.txt", "r+");
    //if (fp == NULL) {
    //    printf("error");
    //    return;
    //}
    //FILE* fpTemp = fopen("temp.txt", "w"); // 创建临时文件
    //if (fpTemp == NULL) {
    //    fclose(fp);
    //    perror("Error opening temp file");
    //    return;
    //}
    Employee* p = head;
    int n;
    printf("请输入要修改的员工人数:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("请输入第%d个要修改的员工编号：", i + 1);
        int Id;
        scanf("%d", &Id);
       
        while (p != NULL && p->employeeId != Id) {
            p = p->next;
        }
        if (p == NULL) {
            printf("未找到编号为 %d 的员工。\n", Id);
            continue;
        }
        int choice;
        do {
            printf("\n当前员工信息如下：\n");
            printf("姓名：%s\n", p->name);
            printf("性别：%c\n", p->gender);
            printf("部门：%s\n", p->department);
            const char* positionStr = PositionToString(p->position);
            printf("职位：%s\n", positionStr);
            printf("工作年限：%d\n", p->seniority);

            printf("\n请选择要修改的字段：\n");
            printf("1. 姓名\n");
            printf("2. 性别\n");
            printf("3. 部门\n");
            printf("4. 职位\n");
            printf("5. 工作年限\n");
            printf("6. 退出\n");
            printf("请选择：");

            scanf("%d", &choice);
            Position newposition;
            switch (choice) {
            case 1:
                printf("请输入修改后的姓名: ");
                scanf("%s", p->name);
                break;
            case 2:
                printf("请输入修改后的性别: ");
                scanf(" %c", &p->gender);
                break;
            case 3:
                printf("请输入修改后的部门: ");
                scanf("%s", p->department);
                break;
            case 4:
                printf("请输入修改后的职位: ");
                char positionStr[20]; // 假设职位名称不超过 19 个字符加上一个结束符
                scanf("%19s", positionStr); // 使用 %19s 防止缓冲区溢出
                newposition = stringToPosition(positionStr); // 调用函数转换字符串到 Position 枚举
                if (p != NULL) {
                    p->position = newposition; // 更新链表中的员工职位
                }
                break;
            case 5:
                printf("请输入修改后的工作年限: ");
                scanf("%d", &p->seniority);
                break;
            case 6:
                printf("退出修改");
                break;
            default:
                printf("无效选择");
                break;
            }
            // 将修改后的员工信息写入文件中
        } while (choice != 6);
    //    fseek(fp, 0, SEEK_SET);
    //    rewind(fpTemp); // 重置临时文件指针

    //    Employee* current = head;
    //    while (current != NULL) {
    //        if (current->employeeId == Id) {
    //            // 如果是匹配的员工，写入更新后的信息
    //            fprintf(fpTemp, "%d;%s;%c;%s;%s;%d;\n",
    //                current->employeeId,
    //                current->name,
    //                current->gender,
    //                current->department,
    //                PositionToString(current->position),
    //                current->seniority
    //                );
    //        }
    //        else {
    //            // 如果不是匹配的员工，复制原始记录
    //            fprintf(fpTemp, "%d;%s;%c;%s;%s;%d;\n",
    //                current->employeeId,
    //                current->name,
    //                current->gender,
    //                current->department,
    //                PositionToString(current->position),
    //                current->seniority
    //                );
    //        }
    //        current = current->next;
    //    }
    //}

    //// 关闭文件
    //fclose(fp);
    //fclose(fpTemp);

    //// 刷新文件缓冲区
    //fflush(fp);
    //fflush(fpTemp);

    //// 重命名临时文件，覆盖原始文件
    //if (rename("temp.txt", "text.txt") != 0) {
    //    perror("Error renaming file");
    //    //remove("temp.txt"); // 删除临时文件以避免数据丢失
    //}
    ////else {
    ////    remove("text.txt.bak"); // 如果有备份，也删除备份文件
    }
}
//辅助函数：删除后编号仍然保存有序性
void renumberEmployees(Employee* head) {
    Employee* current = head;
    int newId = 1;  // 通常从 1 开始重新编号
    while (current != NULL) {
        current->employeeId = newId++;  // 赋值新编号并递增编号
        current = current->next;
    }
}
//功能函数：根据职工号删除一个员工
void deleteEmployee(Employee** head) {
        
        Employee* p = *head;
        int n;
        printf("请输入要删除的员工人数:");
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            printf("请输入要删除的第%d个要删除的职工的职工号:", i + 1);
            int Id;
            scanf("%d", &Id);
            while (p != NULL && p->employeeId == Id) {
                *head = p->next;
                free(p);
                renumberEmployees(*head);
                p = *head;
                continue;
            }
            Employee* previous = NULL;
            while (p != NULL && p->employeeId != Id) {
                previous = p;
                p = p->next;
            }
            if (p != NULL) {
                previous->next = p->next;
                free(p);
                renumberEmployees(*head);
                p = previous->next;
            }
            else {
                printf("未找到编号为 %d 的员工\n", Id);
            }
        }
    }
// 功能函数：根据职工号在链表中搜索员工
void searchEmployee(Employee* head) {
 
    Employee* p = head;
    int n;
    printf("请输入要查询员工人数:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int Id;
        printf("请输入要查询的第%d个员工的职工号：", i + 1);
        scanf("%d", &Id);
        while (p!=NULL&&p->employeeId != Id) {
            p = p->next;
        }
        if (p != NULL) {
            printf("该员工信息如下\n");
            printf("员工号：%d;名字：%s;性别：%c;部门：%s;职位：%s;工龄：%d;\n",
                p->employeeId,
                p->name,
                p->gender,
                p->department,
                PositionToString(p->position),
                p->seniority);
        }
        else {
            printf("未查找到该员工\n");
            break;
        }
    }
}

// 辅助函数：找到部门数组中第一个空的部门槽位
int findEmptyDepartmentSlot(DepartmentSales* departments, int size) {
    for (int i = 0; i < size; ++i) {
        if (departments[i].department[0] == '\0') {
            return i;
        }
    }
    return -1; // 如果没有找到空槽位
}
//辅助函数：找到不同的部门
DepartmentSales* Department(Employee* head) {
    DepartmentSales* departments = (DepartmentSales*)malloc(sizeof(DepartmentSales) * department_size);
    memset(departments, 0, sizeof(DepartmentSales) * department_size); // 初始化部门数组

    Employee* p = head;
    while (p != NULL) {
        // 找到对应部门的索引，这里简化处理，假设部门名称在部门数组中有对应的索引
        int deptIndex = -1;
        for (int i = 0; i < department_size; ++i) {
            if (strcmp(p->department, departments[i].department) == 0) {
                deptIndex = i;
                break;
            }
        }
        // 如果部门不在数组中，添加新部门
        if (deptIndex == -1) {
            deptIndex = findEmptyDepartmentSlot(departments, department_size);
            strcpy(departments[deptIndex].department, p->department);
        }
        p = p->next;
    }
    return departments;
}
// 辅助函数：计算每个部门的销售额度并更新经理的销售额
void calculateSalaryAmount(Employee* head) {
    DepartmentSales* departments = Department(head);
    Employee* p;
    // 遍历部门数组，更新链表中经理的销售额
    for (int i = 0; i < department_size; ++i) {
        if (departments[i].department[0] != '\0') { // 如果部门被使用过
            p = head;
            while (p != NULL) {
                if (strcmp(p->department, departments[i].department) == 0 && p->position == sales_manager) {
                    p->salaryData.salesAmount = departments[i].totalSales;
                }
                p = p->next;
            }
        }
    }
    // 释放部门数组
    free(departments);
}
// 功能函数：计算所有员工的当月工资
void calculateMonthlySalary(Employee* head) {
    Employee* p = head;
    calculateSalaryAmount(head);
    while (p != NULL) {
        if (p->position == manager)
        {
            if (p->salaryData.baseSalary != -1)
                p->salaryData.monthlySalary = 35 * p->seniority + p->salaryData.baseSalary;
            else p->salaryData.monthlySalary = -1;
        }
        if (p->position == technician)
        {
            if (p->salaryData.hourlyRate != -1)
                p->salaryData.monthlySalary = 35 * p->seniority + (p->salaryData.hourlyRate * p->salaryData.workingHours);
            else p->salaryData.monthlySalary = -1;
        }
        if (p->position == saleman)
        {
            if (p->salaryData.salesAmount != -1)
                p->salaryData.monthlySalary = (35 * p->seniority) + (0.04 * p->salaryData.salesAmount);
            else p->salaryData.monthlySalary = -1;
        }

        if (p->position == sales_manager)
        {
            if (p->salaryData.baseSalary != -1)
                p->salaryData.monthlySalary = (35 * p->seniority) + p->salaryData.baseSalary + (0.005 * p->salaryData.salesAmount);
            else p->salaryData.monthlySalary = -1;
        }
        p = p->next;
    }

}

//功能函数：输入员工工资信息
void inputMonthlySalary(Employee* head) {
    FILE* file = fopen("text.txt", "r+"); // 假设工资信息存储在 text.txt 中
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    Employee* p = head;
    while (p != NULL) {
        if ((p->position == manager && p->salaryData.baseSalary == 0.00) ||
            (p->position == technician && p->salaryData.hourlyRate == 0.00) ||
            (p->position == saleman && p->salaryData.salesAmount == 0.00) ||
            (p->position == sales_manager && p->salaryData.baseSalary == 0.00)
            ) 
        {
            printf("该员工信息为：员工号：%d;名字：%s;性别：%c;部门：%s;职位：%s;工龄：%d;",
                p->employeeId,
                p->name,
                p->gender,
                p->department,
                PositionToString(p->position),
                p->seniority);
            printf("请输入Id为%d的职工的工资信息\n", p->employeeId);
            printf("工时: ");
            scanf("%f", &p->salaryData.workingHours);
            printf("小时工资: ");
            scanf("%f", &p->salaryData.hourlyRate);
            printf("销售额: ");
            scanf("%f", &p->salaryData.salesAmount);
            printf("底薪: ");
            scanf("%f", &p->salaryData.baseSalary);
        }
        p = p->next;
    }
    fclose(file);
    calculateMonthlySalary(head);
}
//功能函数：修改工资信息
void changeMonthlySalary(Employee* head) {
    Employee* p = head;
    int n;
    printf("请输入要修改的员工人数:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("请输入第%d个要修改的员工编号：", i + 1);
        int Id;
        scanf("%d", &Id);

        while (p != NULL && p->employeeId != Id) {
            p = p->next;
        }
        if (p == NULL) {
            printf("未找到编号为 %d 的员工。\n", Id);
            continue;
        }
        int choice;
        do {
            printf("当前员工工资信息：");
            printf("%f;", p->salaryData.workingHours);
            printf("%f;", p->salaryData.hourlyRate);
            printf("%f;", p->salaryData.salesAmount);
            printf("%f;", p->salaryData.baseSalary);

            printf("\n请选择要修改的选项：\n");
            printf("1. 工时\n");
            printf("2. 小时工资\n");
            printf("3. 销售额\n");
            printf("4. 底薪\n");
            printf("5. 退出\n");
            printf("请选择：");
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("请输入修改后的工时：");
                scanf("%f", &p->salaryData.workingHours);
                break;
            case 2:
                printf("请输入修改后的小时工资：");
                scanf("%f", &p->salaryData.hourlyRate);
                break;
            case 3:
                printf("请输入修改后的销售额：");
                scanf("%f", &p->salaryData.salesAmount);
                break;
            case 4:
                printf("请输入修改后的底薪：");
                scanf("%f", &p->salaryData.baseSalary);
                break;
            case 5:
                printf("退出修改");
                break;
            default:
                printf("无效选择");
                break;
            }
        } while (choice !=5 );
    }
    calculateMonthlySalary(head);
}

//功能函数：删除，只需将相关数据项设置成-1
void deletemployeeSalary(Employee* head) {
  
    Employee* p = head;
    int n;
    printf("请输入要删除的员工人数:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("请输入要删除的第%d个要删除的职工的职工号:", i + 1);
        int Id;
        scanf("%d", &Id);
        while (p!=NULL&&p->employeeId != Id) p = p->next;
        if (p != NULL) {
            if (PositionToString(p->position )== "manager") {
                p->salaryData.baseSalary = -1;
            }
            if (PositionToString(p->position) == "technician") {
                p->salaryData.hourlyRate = -1;
            }
            if (PositionToString(p->position) == "saleman") {
                p->salaryData.salesAmount = -1;
           }
            if (PositionToString(p->position) == "sales_manager") {
                p->salaryData.baseSalary = -1;
            }
        }
        else {
            printf("未找到编号为%d的员工\n",Id);
        }
    }
    calculateMonthlySalary(head);
}
//功能函数：查询职工基本工资信息
void searchSalary(Employee* head) {
    Employee* p = head;
    int n;
    printf("请输入要查询员工工资的人数:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int Id;
        printf("请输入要查询的第%d个员工的职工号：", i + 1);
        scanf("%d", &Id);
        while (p != NULL && p->employeeId != Id) {
            p = p->next;
        }
        if (p != NULL) {
            printf("该员工工资信息如下\n");
            printf("工时：%.2f;小时工资：%.2f;销售额：%.2f;底薪：%.2f;当月工资：%.2f;\n",
                p->salaryData.workingHours,
                p->salaryData.hourlyRate,
                p->salaryData.salesAmount,
                p->salaryData.baseSalary,
                p->salaryData.monthlySalary);
        }
        else {
            printf("未查找到该员工\n");
            break;
        }
    }
}

// 功能函数/辅助函数：将链表中员工数据保存到文件
void saveEmployees(Employee* head) {
    
    FILE* fp = fopen("text.txt", "w");
    if (fp == NULL) {
        printf("error");
        return;
    }
    Employee* p = head;
    calculateMonthlySalary(p);
    while (p != NULL) {
        fprintf(fp, "%d;%s;%c;%s;%s;%d;%.2f;%.2f;%.2f;%.2f;%.2f;\n",
            p->employeeId,
            p->name,
            p->gender,
            p->department,
            PositionToString(p->position),
            p->seniority,
            p->salaryData.workingHours,
            p->salaryData.hourlyRate,
            p->salaryData.salesAmount,
            p->salaryData.baseSalary,
            p->salaryData.monthlySalary);

        p = p->next;
    }
    fclose(fp);
}

