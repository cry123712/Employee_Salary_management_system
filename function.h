#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<malloc.h>
#include <ctype.h>
#include<math.h>

// ȫ�ֱ��������ڴ洢��ǰ����Ա�����
static int maxEmployeeId = 0;

#define MAX_LINE_LENGTH 1024
#define EXPECTED_FIELD_COUNT 11
#define department_size 10

// ����ö�����ͣ���ʾԱ���ĸ�λ
typedef enum {
    manager,//����
    technician,//����Ա
    saleman,//����Ա
    sales_manager//���۾���
} Position;

// Ա���������ݽṹ
typedef struct {
    float workingHours;
    float hourlyRate;
    float salesAmount;
    float baseSalary;
    float monthlySalary; // ����������ֶ�����
} SalaryData;

// Ա���������ݽṹ
typedef struct Employee {
    int employeeId;//ϵͳ�Զ�����
    char name[50];
    char gender;
    char department[50];
    Position position;
    int seniority;
    SalaryData salaryData;
    struct Employee* next; // ָ����һ��Ա����ָ��
} Employee;
//�й����۶��
typedef struct {
    char department[50];
    float totalSales; // �ò�����������Ա�����۾�������۶��ܺ�
    float managerSalary; //�ò��ž�������۶�
    //float averageSalary;
} DepartmentSales;

//���������������ṹ���Ա, ��ʼ���ṹ���Ա
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
//�������������ļ��ҵ������
void initializeMaxEmployeeId() {
    FILE* file = fopen("text.txt", "r");
    if (!file) {
        maxEmployeeId = 1; // ����ļ������ڣ���1��ʼ
    }
    else {
        Employee temp;
        // ����ÿ��Ա���ı�����ļ��еĵ�һ��
        while (fscanf(file, "%d", &temp.employeeId) > 0) {
            if (temp.employeeId > maxEmployeeId) {
                maxEmployeeId = temp.employeeId;
            }
        }
    }
    fclose(file);
}
// ������������ Position ö�ٺ��ַ����໥ת���ĺ���
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
//���ܺ���������
void addEmployee(Employee** head) {
    printf("������Ҫ���ӵ�Ա������:\n");
    int n;
    scanf("%d", &n);
   
    for (int i = 0; i < n; i++) {
      
        Employee* newEmployee = createEmployee();
        newEmployee->employeeId = ++maxEmployeeId;
        newEmployee->next = NULL;
        printf("������������%d��Ա��������: ", i + 1);
        scanf("%49s", newEmployee->name);
      

        printf("������������%d��Ա�����Ա� (M/F): ", i + 1);
        scanf(" %c", &newEmployee->gender);

        printf("������������%d��Ա���Ĳ���: ", i + 1);
        scanf("%49s", newEmployee->department);
 
        // ְ���ȡ�ʹ�����
        printf("������������%d��Ա����ְ��: ", i + 1);
        char positionStr[20];
        scanf("%19s", positionStr); // ʹ�� %19s ��ֹ���������
        newEmployee->position = stringToPosition(positionStr);

        // �������޶�ȡ
        printf("������������%d��Ա���Ĺ�������: ", i + 1);
        scanf("%d", &newEmployee->seniority);
        //// ��ʼ����������
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
//����������loadEmployees�����ǽ��ı��ļ���ԭ�еĶ�������
void loadEmployees(Employee** head) {
    FILE* file = fopen("text.txt", "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file)) { // ʹ�� fgets ����ȡ����
        char* token, * lineCopy = _strdup(line); // ���������ݵĸ���

        Employee* newEmployee = createEmployee(); // ʹ��֮ǰ����ĺ�������Ա��
        if (!newEmployee) {
            free(lineCopy); // �������Ա��ʧ�ܣ��ͷŸ������ڴ�
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
                newEmployee->seniority = atoi(token); // ʹ�� atoi �������ַ���ת��Ϊ����
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
                // ����ֶγ���Ԥ�������������������
                break;
            }
            parsedFields++;
            token = strtok(NULL, ";");
        }
            if (parsedFields < EXPECTED_FIELD_COUNT) { // ȷ��������Ԥ���������ֶ�
                // ���ݲ��������ͷ��ڴ�
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
 
       free(lineCopy); // �ͷ��и������ڴ�
        }
    fclose(file); // �ر��ļ�
 }
//���ܺ���������ְ�������޸�����Ա���ĳ�ְ�����������������������
void modifyEmployee(Employee* head) {
    //���������޸ĺ�ص��ı��ļ��޸�
    //FILE* fp = fopen("text.txt", "r+");
    //if (fp == NULL) {
    //    printf("error");
    //    return;
    //}
    //FILE* fpTemp = fopen("temp.txt", "w"); // ������ʱ�ļ�
    //if (fpTemp == NULL) {
    //    fclose(fp);
    //    perror("Error opening temp file");
    //    return;
    //}
    Employee* p = head;
    int n;
    printf("������Ҫ�޸ĵ�Ա������:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("�������%d��Ҫ�޸ĵ�Ա����ţ�", i + 1);
        int Id;
        scanf("%d", &Id);
       
        while (p != NULL && p->employeeId != Id) {
            p = p->next;
        }
        if (p == NULL) {
            printf("δ�ҵ����Ϊ %d ��Ա����\n", Id);
            continue;
        }
        int choice;
        do {
            printf("\n��ǰԱ����Ϣ���£�\n");
            printf("������%s\n", p->name);
            printf("�Ա�%c\n", p->gender);
            printf("���ţ�%s\n", p->department);
            const char* positionStr = PositionToString(p->position);
            printf("ְλ��%s\n", positionStr);
            printf("�������ޣ�%d\n", p->seniority);

            printf("\n��ѡ��Ҫ�޸ĵ��ֶΣ�\n");
            printf("1. ����\n");
            printf("2. �Ա�\n");
            printf("3. ����\n");
            printf("4. ְλ\n");
            printf("5. ��������\n");
            printf("6. �˳�\n");
            printf("��ѡ��");

            scanf("%d", &choice);
            Position newposition;
            switch (choice) {
            case 1:
                printf("�������޸ĺ������: ");
                scanf("%s", p->name);
                break;
            case 2:
                printf("�������޸ĺ���Ա�: ");
                scanf(" %c", &p->gender);
                break;
            case 3:
                printf("�������޸ĺ�Ĳ���: ");
                scanf("%s", p->department);
                break;
            case 4:
                printf("�������޸ĺ��ְλ: ");
                char positionStr[20]; // ����ְλ���Ʋ����� 19 ���ַ�����һ��������
                scanf("%19s", positionStr); // ʹ�� %19s ��ֹ���������
                newposition = stringToPosition(positionStr); // ���ú���ת���ַ����� Position ö��
                if (p != NULL) {
                    p->position = newposition; // ���������е�Ա��ְλ
                }
                break;
            case 5:
                printf("�������޸ĺ�Ĺ�������: ");
                scanf("%d", &p->seniority);
                break;
            case 6:
                printf("�˳��޸�");
                break;
            default:
                printf("��Чѡ��");
                break;
            }
            // ���޸ĺ��Ա����Ϣд���ļ���
        } while (choice != 6);
    //    fseek(fp, 0, SEEK_SET);
    //    rewind(fpTemp); // ������ʱ�ļ�ָ��

    //    Employee* current = head;
    //    while (current != NULL) {
    //        if (current->employeeId == Id) {
    //            // �����ƥ���Ա����д����º����Ϣ
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
    //            // �������ƥ���Ա��������ԭʼ��¼
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

    //// �ر��ļ�
    //fclose(fp);
    //fclose(fpTemp);

    //// ˢ���ļ�������
    //fflush(fp);
    //fflush(fpTemp);

    //// ��������ʱ�ļ�������ԭʼ�ļ�
    //if (rename("temp.txt", "text.txt") != 0) {
    //    perror("Error renaming file");
    //    //remove("temp.txt"); // ɾ����ʱ�ļ��Ա������ݶ�ʧ
    //}
    ////else {
    ////    remove("text.txt.bak"); // ����б��ݣ�Ҳɾ�������ļ�
    }
}
//����������ɾ��������Ȼ����������
void renumberEmployees(Employee* head) {
    Employee* current = head;
    int newId = 1;  // ͨ���� 1 ��ʼ���±��
    while (current != NULL) {
        current->employeeId = newId++;  // ��ֵ�±�Ų��������
        current = current->next;
    }
}
//���ܺ���������ְ����ɾ��һ��Ա��
void deleteEmployee(Employee** head) {
        
        Employee* p = *head;
        int n;
        printf("������Ҫɾ����Ա������:");
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            printf("������Ҫɾ���ĵ�%d��Ҫɾ����ְ����ְ����:", i + 1);
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
                printf("δ�ҵ����Ϊ %d ��Ա��\n", Id);
            }
        }
    }
// ���ܺ���������ְ����������������Ա��
void searchEmployee(Employee* head) {
 
    Employee* p = head;
    int n;
    printf("������Ҫ��ѯԱ������:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int Id;
        printf("������Ҫ��ѯ�ĵ�%d��Ա����ְ���ţ�", i + 1);
        scanf("%d", &Id);
        while (p!=NULL&&p->employeeId != Id) {
            p = p->next;
        }
        if (p != NULL) {
            printf("��Ա����Ϣ����\n");
            printf("Ա���ţ�%d;���֣�%s;�Ա�%c;���ţ�%s;ְλ��%s;���䣺%d;\n",
                p->employeeId,
                p->name,
                p->gender,
                p->department,
                PositionToString(p->position),
                p->seniority);
        }
        else {
            printf("δ���ҵ���Ա��\n");
            break;
        }
    }
}

// �����������ҵ����������е�һ���յĲ��Ų�λ
int findEmptyDepartmentSlot(DepartmentSales* departments, int size) {
    for (int i = 0; i < size; ++i) {
        if (departments[i].department[0] == '\0') {
            return i;
        }
    }
    return -1; // ���û���ҵ��ղ�λ
}
//�����������ҵ���ͬ�Ĳ���
DepartmentSales* Department(Employee* head) {
    DepartmentSales* departments = (DepartmentSales*)malloc(sizeof(DepartmentSales) * department_size);
    memset(departments, 0, sizeof(DepartmentSales) * department_size); // ��ʼ����������

    Employee* p = head;
    while (p != NULL) {
        // �ҵ���Ӧ���ŵ�����������򻯴������貿�������ڲ����������ж�Ӧ������
        int deptIndex = -1;
        for (int i = 0; i < department_size; ++i) {
            if (strcmp(p->department, departments[i].department) == 0) {
                deptIndex = i;
                break;
            }
        }
        // ������Ų��������У�����²���
        if (deptIndex == -1) {
            deptIndex = findEmptyDepartmentSlot(departments, department_size);
            strcpy(departments[deptIndex].department, p->department);
        }
        p = p->next;
    }
    return departments;
}
// ��������������ÿ�����ŵ����۶�Ȳ����¾�������۶�
void calculateSalaryAmount(Employee* head) {
    DepartmentSales* departments = Department(head);
    Employee* p;
    // �����������飬���������о�������۶�
    for (int i = 0; i < department_size; ++i) {
        if (departments[i].department[0] != '\0') { // ������ű�ʹ�ù�
            p = head;
            while (p != NULL) {
                if (strcmp(p->department, departments[i].department) == 0 && p->position == sales_manager) {
                    p->salaryData.salesAmount = departments[i].totalSales;
                }
                p = p->next;
            }
        }
    }
    // �ͷŲ�������
    free(departments);
}
// ���ܺ�������������Ա���ĵ��¹���
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

//���ܺ���������Ա��������Ϣ
void inputMonthlySalary(Employee* head) {
    FILE* file = fopen("text.txt", "r+"); // ���蹤����Ϣ�洢�� text.txt ��
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
            printf("��Ա����ϢΪ��Ա���ţ�%d;���֣�%s;�Ա�%c;���ţ�%s;ְλ��%s;���䣺%d;",
                p->employeeId,
                p->name,
                p->gender,
                p->department,
                PositionToString(p->position),
                p->seniority);
            printf("������IdΪ%d��ְ���Ĺ�����Ϣ\n", p->employeeId);
            printf("��ʱ: ");
            scanf("%f", &p->salaryData.workingHours);
            printf("Сʱ����: ");
            scanf("%f", &p->salaryData.hourlyRate);
            printf("���۶�: ");
            scanf("%f", &p->salaryData.salesAmount);
            printf("��н: ");
            scanf("%f", &p->salaryData.baseSalary);
        }
        p = p->next;
    }
    fclose(file);
    calculateMonthlySalary(head);
}
//���ܺ������޸Ĺ�����Ϣ
void changeMonthlySalary(Employee* head) {
    Employee* p = head;
    int n;
    printf("������Ҫ�޸ĵ�Ա������:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("�������%d��Ҫ�޸ĵ�Ա����ţ�", i + 1);
        int Id;
        scanf("%d", &Id);

        while (p != NULL && p->employeeId != Id) {
            p = p->next;
        }
        if (p == NULL) {
            printf("δ�ҵ����Ϊ %d ��Ա����\n", Id);
            continue;
        }
        int choice;
        do {
            printf("��ǰԱ��������Ϣ��");
            printf("%f;", p->salaryData.workingHours);
            printf("%f;", p->salaryData.hourlyRate);
            printf("%f;", p->salaryData.salesAmount);
            printf("%f;", p->salaryData.baseSalary);

            printf("\n��ѡ��Ҫ�޸ĵ�ѡ�\n");
            printf("1. ��ʱ\n");
            printf("2. Сʱ����\n");
            printf("3. ���۶�\n");
            printf("4. ��н\n");
            printf("5. �˳�\n");
            printf("��ѡ��");
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("�������޸ĺ�Ĺ�ʱ��");
                scanf("%f", &p->salaryData.workingHours);
                break;
            case 2:
                printf("�������޸ĺ��Сʱ���ʣ�");
                scanf("%f", &p->salaryData.hourlyRate);
                break;
            case 3:
                printf("�������޸ĺ�����۶");
                scanf("%f", &p->salaryData.salesAmount);
                break;
            case 4:
                printf("�������޸ĺ�ĵ�н��");
                scanf("%f", &p->salaryData.baseSalary);
                break;
            case 5:
                printf("�˳��޸�");
                break;
            default:
                printf("��Чѡ��");
                break;
            }
        } while (choice !=5 );
    }
    calculateMonthlySalary(head);
}

//���ܺ�����ɾ����ֻ�轫������������ó�-1
void deletemployeeSalary(Employee* head) {
  
    Employee* p = head;
    int n;
    printf("������Ҫɾ����Ա������:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("������Ҫɾ���ĵ�%d��Ҫɾ����ְ����ְ����:", i + 1);
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
            printf("δ�ҵ����Ϊ%d��Ա��\n",Id);
        }
    }
    calculateMonthlySalary(head);
}
//���ܺ�������ѯְ������������Ϣ
void searchSalary(Employee* head) {
    Employee* p = head;
    int n;
    printf("������Ҫ��ѯԱ�����ʵ�����:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int Id;
        printf("������Ҫ��ѯ�ĵ�%d��Ա����ְ���ţ�", i + 1);
        scanf("%d", &Id);
        while (p != NULL && p->employeeId != Id) {
            p = p->next;
        }
        if (p != NULL) {
            printf("��Ա��������Ϣ����\n");
            printf("��ʱ��%.2f;Сʱ���ʣ�%.2f;���۶%.2f;��н��%.2f;���¹��ʣ�%.2f;\n",
                p->salaryData.workingHours,
                p->salaryData.hourlyRate,
                p->salaryData.salesAmount,
                p->salaryData.baseSalary,
                p->salaryData.monthlySalary);
        }
        else {
            printf("δ���ҵ���Ա��\n");
            break;
        }
    }
}

// ���ܺ���/������������������Ա�����ݱ��浽�ļ�
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

