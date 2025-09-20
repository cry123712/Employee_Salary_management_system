#pragma once
#include"function.h"

#define PAGE_SIZE 10

//��������������ָ���ӡ��Ա��������Ϣ�͹�����Ϣ
void printEmployee(Employee* current) {
    
    if (current != NULL) {
        printf("Ա���ţ�%d;���֣�%s;�Ա�%c;���ţ�%s;ְλ��%s;���䣺%d;",
            current->employeeId,
            current->name,
            current->gender,
            current->department,
            PositionToString(current->position),
            current->seniority);
        printf("��ʱ��%.2f;Сʱ���ʣ�%.2f;���۶%.2f;��н��%.2f;���¹��ʣ�%.2f;",
            current->salaryData.workingHours,
            current->salaryData.hourlyRate,
            current->salaryData.salesAmount,
            current->salaryData.baseSalary,
            current->salaryData.monthlySalary);
    }
    printf("\n");
}
//������������ʾ��ǰҳ��Ա����Ϣ
void displayEmployees(Employee* head, int currentPage) {
    Employee* current = head;
    int count = 0;
    int start = (currentPage - 1) * PAGE_SIZE;
    int end = start + PAGE_SIZE;

    // ��������������ȷ����ʼ��
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
//�����������������Ա��������ע�⣺�������ڹ�����Ϣ����ϵͳ����ɾ������Ա������Ϣ��-1��
int count_maxemployees(Employee* head) {
    Employee* p = head;
    int count = 0;
    while (p != NULL) { // ��������
        count++; // ÿ����һ���ڵ㣬������1
       p =p->next; // �ƶ�����һ���ڵ�
    }
    return count; // ����Ա������
}
//���ܺ�������ҳ����
void page(Employee* head) {
    int currentPage = 1;
    int totalEmployees =count_maxemployees(head);// ������Ա�������ı���
    int choice;
    do {
        printf("===== Ա����Ϣ��ҳ��ʾ =====\n");
        printf("��ǰҳ: %d\n", currentPage);
        printf("��Ա����: %d\n", totalEmployees);
        printf("1. ��һҳ\n");
        printf("2. ��һҳ\n");
        printf("3. ��ҳ\n");
        printf("4. ���ҳ\n");
        printf("5. �˳�\n");
        printf("��ѡ�������");

        scanf("%d", &choice);

        switch (choice) {
        case 1: // ��һҳ
            if (currentPage > 1) {
                currentPage--;
            }
            displayEmployees(head, currentPage);
            break;
        case 2: // ��һҳ
            if ((currentPage * PAGE_SIZE) < totalEmployees) {
                currentPage++;
            }
            displayEmployees(head, currentPage);
            break;
        case 3: // ��ҳ
            currentPage = 1;
            displayEmployees(head, currentPage);
            break;
        case 4: // ���ҳ
            currentPage = (totalEmployees + PAGE_SIZE - 1) / PAGE_SIZE;
            displayEmployees(head, currentPage);
            break;
        case 5: // �˳�
          // exit(0);
            break;
        default:
            printf("��Ч��ѡ��������ѡ��\n");
            break;
        }
    }while (choice != 5);
}

//���ܺ�������������ʾ������ȫ��Ա����Ϣ
//��ô����Ѿ����ҹ��Ĳ��ٲ�������
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
//���ܺ�������ְλ��ʾ��ְλȫ��Ա����Ϣ
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
//����������ͨ����������Ա��
void search_By_name(Employee* head, char name[]) {
    Employee* p = head;
    while (p != NULL &&strcmp(p->name,name)!=0) {
        p = p->next;
    }
    if (p != NULL) {
        printEmployee(p);
    }
    else {
        printf("δ�ҵ���������Ա��\n");
    }
}
//����������ͨ��ְ����Ų���Ա��
void search_By_Id(Employee* head, int Id) {
    Employee* p = head;
    while (p != NULL && p->employeeId != Id) {
        p = p->next;
    }
    if (p != NULL) {
        printEmployee(p);
    }
    else {
        printf("δ�ҵ��ñ�ŵ�Ա��\n");
    }
}
//���ܺ�����ͨ��ְ���Ż���������ѯԱ����Ϣ
void search_By_Id_name(Employee* head) {
    int choice;
    do {
        printf("��ѡ���ѯ��ʽ\n");
        printf("1���˳�\n");
        printf("2������\n");
        printf("3��Ա����\n");

        scanf("%d", &choice);
        switch(choice){
        case 1:
            break;
        case 2:
            printf("������Ҫ��ѯ��Ա������\n");
            char name[20];
            scanf("%19s",name);
            search_By_name(head, name);
            break;
        case 3:
            printf("������Ҫ��ѯ��Ա����ְ����\n");
            int Id;
            scanf("%d", &Id);
            search_By_Id(head, Id);
            break;
        default:
            printf("��Ч��ѡ��������ѡ��\n");
            break;
        }
    } while (choice != 1);
}

//��������:����ָ�븴�Ƹý��
Employee* copyEmployee(const Employee* src) {
    if (src==NULL) return NULL;

    Employee* newEmp = (Employee*)malloc(sizeof(Employee));
    if (newEmp==NULL) return NULL; // ����ڴ��Ƿ�ɹ�����

    // ���Ʒ�ָ���Ա
    newEmp->employeeId = src->employeeId;
    strncpy(newEmp->name, src->name, sizeof(newEmp->name));
    newEmp->name[sizeof(newEmp->name) - 1] = '\0';
    newEmp->gender = src->gender;
    strncpy(newEmp->department, src->department, sizeof(newEmp->department));
    newEmp->department[sizeof(newEmp->department) - 1] = '\0';
    newEmp->position = src->position;
    newEmp->seniority = src->seniority;
    // ����SalaryData�ṹ��
    newEmp->salaryData = src->salaryData;

    // ��ȷ����nextָ��
    newEmp->next = NULL;
   /* if (src->next) {
        newEmp->next = copyEmployee(src->next);
    }*/
    return newEmp;
}
//��������:������ֵ����ԭ�������������Ϣ�������������������ȥ���ģ�
Employee* Saving(Employee* head) {
    Employee* newHead = NULL; // �������ͷָ��
    Employee* newTail = NULL; // �������βָ��
    Employee* current = head; // ��ǰ�������Ľڵ�
    // ����ԭ��������ÿ���ڵ�
    while (current != NULL) {
        Employee* newEmp = copyEmployee(current);
        if (newEmp == NULL) {
            // �����ڴ����ʧ�ܵ����
            return NULL;
        }
        if (newHead == NULL) {
            newHead = newEmp; // ������ĵ�һ���ڵ�
        }
        if (newTail != NULL) {
            newTail->next = newEmp; // �����½ڵ㵽����
        }
        newTail = newEmp; // �����������βָ��
        current = current->next; // �ƶ���ԭ�������һ���ڵ�
    }
    return newHead; // �����������ͷָ��
}
// ��������:��������Ա�����,Ҫ��֤����ǰ����̣����ܶ�ʧ

// ������������������Ա�����
void swap(Employee*& head, Employee* p, Employee* q) {
    // ���p��q��ͬһ���ڵ��������һ����NULL������Ҫ����
    if (p == q || p == NULL || q == NULL) return;

    // �ҵ�p��q��ǰ���ڵ�
    Employee* prevP = (p == head) ? NULL : p->next; // p��ǰ����NULL����p����һ���ڵ�
    Employee* prevQ = (q == head) ? NULL : q->next; // q��ǰ����NULL����q����һ���ڵ�

    // �����������p��ͷ�ڵ����q��ͷ�ڵ�
    if (p == head) {
        head = q;
    }
    else if (q == head) {
        head = p;
    }

    // ���p��ǰ�����ڣ���p��ǰ��ָ��q
    if (prevP != NULL) {
        prevP->next = q;
    }

    // ���q��ǰ�����ڣ���q��ǰ��ָ��p
    if (prevQ != NULL) {
        prevQ->next = p;
    }

    // ����p��q��nextָ��
    p->next = prevQ;
    q->next = prevP;
}
// ���ܺ�����������Ա�����¹��������ɸߵ��ͣ�
void All_Rank(Employee*& head) {
    if (head == NULL || maxEmployeeId == 0) return;

    bool swapped;
    do {
        swapped = false;
        Employee* current = head;
        while (current->next != NULL) { // ȷ��current�������һ���ڵ�
            Employee* next = current->next; // ������һ���ڵ�
            if (current->salaryData.monthlySalary < current->next->salaryData.monthlySalary) {
                swap(head, current,current->next);
                swapped = true;
            }
            current =next;
        }
        //ѭ��������,ͣ������С����һ��
    } while (swapped);
}

// �������������ض����ŵ�Ա�������������
void SortDepartmentEmployees(Employee*& head, const char* departmentName) {
    Employee* sortedHead = NULL; // ����ά������������ͷ��
    Employee* current = head;
    Employee* prev = NULL;
    Employee* temp = NULL;

    // ��������Ա�������ҵ������ض����ŵ�Ա��
    while (current != NULL) {
        if (strcmp(current->department, departmentName) == 0) {
            // �����ǰԱ�������ض����ţ����������
            temp = current;
            if (prev == NULL) {
                // �����ǰ�ǵ�һ���ڵ㣬����sortedHead
                sortedHead = temp;
            }
            else {
                // ����ǰ�ڵ���뵽������������
                prev->next = temp;
            }

            // ���������Ƴ���ǰ�ڵ㣬������prev��currentָ��
            prev = temp;
            temp = temp->next;
            current->next = NULL;
        }
        else {
            prev = current;
            current = current->next;
        }
    }

    // ����ȡ���ض�����Ա���������ð������
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

    // ���������ض�����Ա�������������ӵ�ԭ������
    if (prev != NULL) {
        prev->next = temp;
    }
    else {
        head = sortedHead;
    }
}

//���ܺ������ָ�λ��Ա�����¹�������(�ɸߵ��ͣ�
void Some_Rank(Employee*& head) {
    DepartmentSales* departments = Department(head); // ��ȡ������Ϣ
    for (int i = 0; i < department_size; ++i) {
        if (departments[i].department[0] != '\0') {
            printf("Department: %s\n", departments[i].department);
            SortDepartmentEmployees(head, departments[i].department); // ��ÿ�����ŵ�Ա����������
        }
    }
    free(departments); // �ͷŲ�������
}

//���ܺ�����ͳ�Ʋ���ʾĳ�����ŵ�ƽ�����ʡ���͹��ʡ���߹���
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
            printf("%s���ŵ��������:\n", departments[i].department);
            printf("ƽ������: %.2f\n", averageSalary);
            printf("��͹���: %.2f\n", minSalary);
            printf("��߹���: %.2f\n", maxSalary);
           
        }
    }
    free(departments);
}
//���ܺ�����ͳ�Ʋ���ʾĳ�����ų���ƽ�����ʵ�������Ա����Ϣ
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
            printf("%s���ų���ƽ�����ʵ�Ա������Ϊ: %d,�ⲿ��Ա����Ϣ����\n", departments[i].department, countOverAverage);
            printf("--------------------------------------------------\n");
        }
    }
    free(departments);
}
//���ܺ�����ͳ�Ʋ���ʾ����Ա���е���͹��ʺ���߹���Ա������Ϣ
void Find_low_Hight(Employee* head) {
    if (head == NULL) return; // �������Ϊ�գ�ֱ�ӷ���
    Employee* current = head;
    while (current->salaryData.monthlySalary == -1) {
        current = current->next;
    }
    Employee* max = current; // �����һ��Ա���ǹ�����ߵ�
    Employee* min = current; // �����һ��Ա���ǹ�����͵�
    Employee* p = head;
    
    while (p != NULL) {
       
        if (p->salaryData.monthlySalary != -1 ) {
            // ������߹��ʺ���͹��ʵ�Ա��
            if (p->salaryData.monthlySalary > max->salaryData.monthlySalary) {
                max = p;
            }
            if (p->salaryData.monthlySalary < min->salaryData.monthlySalary) {
                min = p;
            }
        }
        p = p->next;
    }
    printf("ȫ��Ա������߹���Ա����ϢΪ:\n");
    printEmployee(max);
    printf("ȫ��Ա������͹���Ա����ϢΪ:\n");
    printEmployee(min);
}
//���ܺ�����ͳ�Ʋ���ʾ����Ա������ƽ�����ʵ�������Ա����Ϣ
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
    printf("ȫ��Ա��ƽ������Ϊ%.2f\n", average);
    p = head;
    while (p != NULL) {
        if (p->salaryData.monthlySalary > average) {
            printEmployee(p);
            Overcount++;
        }
        p = p->next;
    }
    printf("ȫ��Ա���г���ƽ�����ʵ�Ա��������%d������Ϣ���ϣ�\n", Overcount);
}

