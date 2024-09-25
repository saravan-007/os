
#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME 100
#define MAX_EMPLOYEES 100

typedef struct Employee {
    int id;
    char name[MAX_NAME];
    float salary;
} Employee;

int main() {
    FILE* file = fopen("employee_details.txt", "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int numEmployees;
    printf("Enter number of employees: ");
    scanf("%d", &numEmployees);

    fprintf(file, "| %-10s | %-20s | %-10s |\n", "ID", "Name", "Salary");
    fprintf(file, "|------------|----------------------|------------|\n");

    
    for (int i = 0; i < numEmployees; i++) {
        Employee emp;
        printf("Enter ID: ");
        scanf("%d", &emp.id);
        printf("Enter Name: ");
        scanf("%s", emp.name);
        printf("Enter Salary: ");
        scanf("%f", &emp.salary);


        fprintf(file, "| %-10d | %-20s | %-10.2f |\n", emp.id, emp.name, emp.salary);
    }

    fprintf(file, "|------------|----------------------|------------|\n");

    fclose(file);
    printf("Employee details written to employee_details.txt\n");

    return 0;
}

