#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct medicine {
    char name[100];
    int quantity;
    float price;
};

struct customer {
    char name[100];
    char address[100];
    char phone[20];
};


void addMedicine(struct medicine *medicines, int *numMedicines) {
    char name[100];
    int quantity;
    float price;
    
    printf("Enter name of medicine: ");
    scanf("%s", name);
    printf("Enter quantity of medicine: ");
    scanf("%d", &quantity);
    printf("Enter price of medicine: ");
    scanf("%f", &price);    
    
    strcpy(medicines[*numMedicines].name, name);
    medicines[*numMedicines].quantity = quantity;
    medicines[*numMedicines].price = price;
    (*numMedicines)++;
}

void displayMedicines(struct medicine *medicines, int numMedicines) {
    printf("%-20s %-10s %-10s\n", "Name", "Quantity", "Price");
    for (int i = 0; i < numMedicines; i++) {
        printf("%-20s %-10d %-10.2f\n", medicines[i].name, medicines[i].quantity, medicines[i].price);
    }
}

int searchMedicine(struct medicine *medicines, int numMedicines, char *name) {
    for (int i = 0; i < numMedicines; i++) {
        if (strcmp(medicines[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void sellMedicine(struct medicine *medicines, int numMedicines) {
    char name[100];
    int quantity;
    
    printf("Enter name of medicine to sell: ");
    scanf("%s", name);
    
    int index = searchMedicine(medicines, numMedicines, name);
    if (index == -1) {
        printf("Medicine not found.\n");
    } else {
        printf("Enter quantity to sell: ");
        scanf("%d", &quantity);
        if (medicines[index].quantity < quantity) {
            printf("Not enough stock.\n");
        } else {
            medicines[index].quantity -= quantity;
            printf("Sold %d units of %s for %.2f.\n", quantity, name, quantity * medicines[index].price);
        }
    }
}

void addCustomerDetails() {
    struct customer cust;
    
    printf("\nEnter customer name: ");
    scanf("%s", cust.name);
    
    printf("\nEnter customer address: ");
    scanf("%s", cust.address);
    
    printf("\nEnter customer phone number: ");
    scanf("%s", cust.phone);
    
    FILE *fp;
    fp = fopen("customer_details.txt", "a");
    
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    
    fprintf(fp, "%s,%s,%s\n", cust.name, cust.address, cust.phone);
    
    fclose(fp);
    
    printf("\nCustomer details added successfully.\n");
}

int main() {
    struct medicine medicines[100];
    int numMedicines = 0;
    int choice;
    
    while (1) {
        printf("\n1. Add medicine\n");
        printf("2. Display medicines\n");
        printf("3. Sell medicine\n");
        printf("4. Add customer details\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addMedicine(medicines, &numMedicines);
                break;
            case 2:
                displayMedicines(medicines, numMedicines);
                break;
            case 3:
                sellMedicine(medicines, numMedicines);
                break;
            case 4:
                addCustomerDetails();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
    
    return 0;
}
