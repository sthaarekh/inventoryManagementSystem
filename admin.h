//Inventory Management System by Arekh Shrestha
//sthaarekh

#define LEN 20
FILE *fpr, *fpa, *fpt;
struct products
{
    char name[100];
    float price;
    int quantity, id;
} p[100], q[100];
int i, j, k, c, id, quantity;
long int contact;
char name[100], choice,*tempPass,password[20];
char oldPassword[LEN],newPassword[LEN],confirmPassword[LEN],storedPassword[LEN];
float price, amount=0;

void productDetailsAdmin()
{
    fpr = fopen("products.txt", "r"); // file pointer to product.txt for reading
    printf("\e[1;1H\e[2J");
    printf("Product Details\n\n");
    printf("Id \t Name \t\t\t\t Price \t\t Quantity");
    printf("\n--------------------------------------------------");
    while (fscanf(fpr, "%d %s %f %d", &id, name, &price, &quantity) != EOF) // scans the products.txt until the end is reached
    {
        printf("\n%d \t %s \t\t\t\t %.2f \t\t %d", id, name, price, quantity); // prints the data from the file
    }
}
void newProduct()
{
    fpa = fopen("products.txt", "a+"); // file pointer to product.txt for appending
    do
    {
        printf("\e[1;1H\e[2J");
        getchar();
        printf("Adding a new product\n\n"); 
        printf("Enter product name: ");
        scanf("%[^\n]%*c", name);
        printf("Enter product ID: ");
        scanf("%d", &id);
        printf("Enter product price: ");
        scanf("%f", &price);
        printf("Enter product quantity: ");
        scanf("%d", &quantity);
        printf("\nDo you want to add more? (Y/N): ");
        scanf("%s", &choice);
        fprintf(fpa, "\n%d \t %s \t %.2f \t %d\n", id, name, price, quantity); // writes the data to the product.txt
        printf("%s is added sucessfully", name);
    } while (choice == 'Y' || choice == 'y');
    fclose(fpa);
}
void updateProduct()
{
    fpr = fopen("products.txt", "r"); // file pointer to product.txt for reading
    fpt = fopen("temp.txt", "w");     // file pointer to temp.txt for writing
    i = 1;
    c = 1;
    do
    {
        printf("\e[1;1H\e[2J");
        getchar();
        printf("Modifying a record.\n\n");
        printf("Enter the product name: ");
        scanf("%[^\n]%*c", p[0].name);
        fseek(fpr, 0, SEEK_SET); // moves the file pointer to start of the file
        // taking input for updating the data and storing in p[]
        while (fscanf(fpr, "%d %s %f %d", &id, name, &price, &quantity) != EOF) // scans the products.txt until the end is reached
        {
            if (strcasecmp(p[0].name, name) == 0) // strcasecmp does not take letter case -> "lays"=="LAYS"
            {
                strcpy(p[i].name, name);
                printf("Old Price = %.2f\nQuatity = %d\n", price, quantity);
                printf("Enter the new product price: ");
                scanf("%f", &p[i].price);
                printf("Enter the new product quantity: ");
                scanf("%d", &p[i].quantity);
                p[i].id = id;
                k = 0;
                break;
            }
            k = 1; // variable used instead of else because of loop
        }
        if (k == 1)
        {
            printf("\nProduct is not available.");
        }
        printf("\nDo you want to update another product?(Y/N): ");
        scanf("%s", &choice);
        c++;
        i++;
    } while (choice == 'Y' || choice == 'y');
    fseek(fpr, 0, SEEK_SET); // moves the file pointer to start of the file
    k = 1;
    // stores the data of products.txt to an array of structure q[]
    while (fscanf(fpr, "%d %s %f %d", &id, name, &price, &quantity) != EOF) // scans the products.txt until the end is reached
    {
        q[k].id = id;
        strcpy(q[k].name, name);
        q[k].price = price;
        q[k].quantity = quantity;
        k++;
    }
    // updates the data in q[] by overwriting it with the updated data from array p[]
    for (i = 1; i < c; i++)
    {
        for (j = 1; j < k; j++)
        {
            if (strcasecmp(p[i].name, q[j].name) == 0) // strcasecmp does not take letter case -> "lays"=="LAYS"
            {
                q[j].price = p[i].price;
                q[j].quantity = p[i].quantity;
            }
        }
    }
    // updates the file "products.txt" with the updated data from array q[]
    for (int j = 1; j < k; j++)
    {
        fprintf(fpt, "%d \t %s \t %.2f \t %d\n", q[j].id, q[j].name, q[j].price, q[j].quantity);
    }
    remove("products.txt");             // removes products.txt
    rename("temp.txt", "products.txt"); // renames temp.txt to products.txt
    printf("\nUpdated Sucessfully");
}
void deleteProduct()
{
    fpr = fopen("products.txt", "r"); // file pointer to product.txt for reading
    fpt = fopen("temp.txt", "w");     // file pointer to temp.txt for writing
    do
    {
        printf("\e[1;1H\e[2J");
        getchar();
        printf("Deleting a record.\n\n");
        printf("Enter the product name: ");
        scanf("%[^\n]%*c", p[0].name);
        fseek(fpr, 0, SEEK_SET); // moves the file pointer to start of the file
        k = 1;
        // stores the data of products.txt to an array of structure q[]
        while (fscanf(fpr, "%d %s %f %d", &id, name, &price, &quantity) != EOF) // scans the products.txt until the end is reached
        {
            q[k].id = id;
            strcpy(q[k].name, name);
            q[k].price = price;
            q[k].quantity = quantity;
            k++;
        }
        for (j = 1; j < k; j++)
        {
            if (strcasecmp(p[0].name, q[j].name) == 0) // strcasecmp does not take letter case -> "lays"=="LAYS"
            {
                strcpy(p[1].name, q[j].name);
                printf("Id: \t\t%d", q[j].id);
                printf("\nName: \t\t%s", q[j].name);
                printf("\nPrice: \t\t%.2f", q[j].price);
                printf("\nQuantity: \t%d", q[j].quantity);
                i = 0;
                break;
            }
            i = 1; // variable used instead of else because of loop
        }
        if (i == 1)
        {
            printf("\nProduct is not available.");
        }
        else
        {
            printf("\n\nDo you confirm to delete this record? (Y/N)");
            scanf("%s", &choice);
            if (choice == 'Y' || choice == 'y')
            {
                for (int j = 1; j < k; j++)
                {
                    if (strcasecmp(p[1].name, q[j].name) != 0)
                    {
                        fprintf(fpt, "%d \t %s \t %.2f \t %d\n", q[j].id, q[j].name, q[j].price, q[j].quantity);
                    }
                }
                remove("products.txt");             // removes products.txt
                rename("temp.txt", "products.txt"); // renames temp.txt to products.txt
                printf("\nDeleted Sucessfully");
            }
        }
        printf("\nDo you want to delete another product?(Y/N)");
        scanf("%s", &choice);
    } while (choice == 'Y' || choice == 'y');
}
void changePassword(){
    printf("\e[1;1H\e[2J");
    passAgain:
    printf("Enter old password: ");
    scanf("%s", oldPassword);
    
    //reads stored password from password.txt
    fpr = fopen("password.txt", "r");
    fscanf(fpr, "%c",storedPassword);

    if (strcmp(oldPassword, storedPassword) != 0) {
        printf("Old password is incorrect. Please enter it again. \n");
        goto passAgain;
    }

    changePass:
    printf("Enter new password: ");
    scanf("%s", newPassword);
    printf("Confirm new password: ");
    scanf("%s", confirmPassword);

    if (strcmp(newPassword, confirmPassword) != 0) {
        printf("New passwords do not match. Please enter correctly.\n");
        goto changePass;
    }

    //stores new password to password.txt
    fpa = fopen("password.txt", "w");
    fprintf(fpa, "%s",confirmPassword);
    printf("Password changed successfully.\n");
}
void adminSection()
{
admin:
    printf("\e[1;1H\e[2J");
    printf("ADMIN SECTION\n\n");
    printf("1. Display the product list.\n");
    printf("2. Add a new product.\n");
    printf("3. Modify the product details.\n");
    printf("4. Delete an existing product.\n");
    printf("5. Change Password\n");
    printf("6. Exit the program.\n");
    printf("\nWhat do you want to do? ");
    choice:
    scanf("%d", &c);
    
    switch (c)
    {
    case 1:
        productDetailsAdmin(); // call productDetails()
        printf("\nGo back to admin section: (Y/N)");
        scanf("%s", &choice);
        if (choice == 'Y' || choice == 'y')
            goto admin;
        break;
    case 2:
        newProduct(); // calls newProduct()
        printf("\nGo back to admin section: (Y/N)");
        scanf("%s", &choice);
        if (choice == 'Y' || choice == 'y')
            goto admin;
        break;
    case 3:
        updateProduct(); // calls updateProduct()
        printf("\nGo back to admin section: (Y/N)");
        scanf("%s", &choice);
        if (choice == 'Y' || choice == 'y')
            goto admin;
        break;
    case 4:
        deleteProduct(); // calls deleteProduct()
        printf("\nGo back to admin section: (Y/N)");
        scanf("%s", &choice);
        if (choice == 'Y' || choice == 'y')
            goto admin;
    case 5:
        changePassword();   // calls changePassword()
        printf("\nGo back to admin section: (Y/N)");
        scanf("%s", &choice);
        if (choice == 'Y' || choice == 'y')
            goto admin;
    case 6:
        printf("Exiting the program....");
        break;
    default:
        printf("\nInvalid Choice!! Please Enter a valid choice: ");
        goto choice;
    }
}