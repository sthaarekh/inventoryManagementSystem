// Inventory Management System by Arekh Shrestha
// sthaarekh

void cashFlow()
{
    fpa = fopen("cashInflow.txt", "a+");
    fprintf(fpa, "\n%s \t %ld\n", name, contact);
    for (int i = 1; i < c; i++)
    {
        fprintf(fpa, "%s : %d\n", p[i].name, p[i].quantity);
    }
    fprintf(fpa, "Total Bill:  %.2f\n", amount);
    fclose(fpa);
}
void bill()
{
    char address[100], payment[20];
    getchar();
    printf("Enter your name: ");
    scanf("%[^\n]%*c", name);
    printf("Enter your contact info: ");
    scanf("%ld", &contact);
    getchar();
    printf("Enter your address: ");
    scanf("%[^\n]%*c", address);
    printf("How do you want to pay (Online/Cash)? ");
    scanf("%[^\n]%*c", payment);
    printf("\e[1;1H\e[2J");
    // displays the bill
    printf("                                                                                            Date: %s\n", __DATE__);
    printf("                                                  Grocery Store\n");
    printf("                                                28 Kilo, Dhulikel\n");
    printf("                                                  Mob:9876543210\n\n");
    printf("                                                      RECEIPT\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("Name: %s                                                                       Cell: %ld\n", name, contact);
    printf("Address: %s\n\n", address);
    printf("S.N.    |\t\t\tITEM\t\t\t|\tQUANTITY\t|\tRATE\t|\tAMOUNT  \n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    for (int i = 1; i < c; i++)
    {
        printf("%d\t|\t\t\t%s\t\t\t|\t   %d\t\t|\t%.2f0\t|       %.2f  \n", i, p[i].name, p[i].quantity, p[i].price, p[i].price * p[i].quantity);
        amount += p[i].price * p[i].quantity;
    }
    printf("\n\n                                                                                          Total Amount: %.2f", amount);
    printf("\n                                                                                          Payment Type: %s ", payment);
    printf("\n                                                                                          Cashier: sthaarekh\n");
    cashFlow();
}
void buyProducts()
{
    fpr = fopen("products.txt", "r");
    fpa = fopen("temp.txt", "w");
    int i = 1;
    getchar();

    printf("You are about to buy something...\n");
    do
    {
        printf("\nEnter the product name: ");
        scanf("%s", p[0].name);
        printf("Enter product quantity: ");
        scanf("%d", &p[0].quantity);

        fseek(fpr, 0, SEEK_SET);                                                // moves the file pointer to start
        while (fscanf(fpr, "%d %s %f %d", &id, name, &price, &quantity) != EOF) // scans the product.txt until the end is reached
        {

            if (strcasecmp(p[0].name, name) == 0 && p[0].quantity <= quantity)
            {
                strcpy(p[i].name, p[0].name);
                p[i].price = price;
                p[i].quantity = p[0].quantity;
                // quantity =
                p[i].id = id;
                i++;
                printf("%d %s are listed.\n", p[0].quantity, p[0].name);
                c = 0;
                break;
            }
            c = 1;
        }
        if (c == 1)
        {
            printf("\nProduct is not available.");
            printf("\nDo you want to search for another product? (Y/N)");
            scanf(" %c", &choice);
            if (choice == 'Y' || choice == 'y')
            {
                getchar();
                continue;
            }
            break;
        }
        printf("\nDo you want to add more items? (Y/N) ");
        scanf(" %c", &choice);
        getchar();
    } while (choice == 'Y' || choice == 'y');
    c = i;

    printf("\e[1;1H\e[2J");
    // displays the selected item
    printf("You Selected:\n");
    printf("\n Id \t Name \t Quantity \t Rate \t Price ");
    for (i = 1; i < c; i++)
    {
        printf("\n %d \t %s \t %d \t\t %.2f \t %.2f ", p[i].id, p[i].name, p[i].quantity, p[i].price, p[i].price * p[i].quantity);
    }
    printf("\n\nConfirm this order (Y/N): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y')
    {
        fseek(fpr, 0, SEEK_SET); // moves the file pointer to start
        int k = 1;
        while (fscanf(fpr, "%d %s %f %d", &id, name, &price, &quantity) != EOF) // scans the product.txt until the end is reached
        {
            q[k].id = id;
            strcpy(q[k].name, name);
            q[k].price = price;
            q[k].quantity = quantity; // stores the selected item in array q[]
            k++;
        }
        for (i = 1; i < c; i++)
        {
            for (int j = 1; j <= k; j++)
            {
                if (strcasecmp(p[i].name, q[j].name) == 0)
                {
                    q[j].quantity -= p[i].quantity; // decrement of sold items
                }
            }
        }
        // stores new data to temp.txt
        for (int j = 1; j < k; j++)
        {
            fprintf(fpa, "%d \t %s \t %.2f \t %d\n", q[j].id, q[j].name, q[j].price, q[j].quantity);
        }
        remove("products.txt");             // removes products.txt
        rename("temp.txt", "products.txt"); // renames temp.txt to products.txt
        bill();                             // calls the bill()
    }
    fclose(fpr);
    fclose(fpa);
}
void searchProduct()
{
    fpr = fopen("products.txt", "r"); // file pointer to product.txt for reading
    do
    {
        printf("\e[1;1H\e[2J");
        getchar();
        printf("Searching a record.\n");
        printf("\nEnter the product name: ");
        scanf("%[^\n]%*c", p[0].name);
        fseek(fpr, 0, SEEK_SET); // moves the file pointer to start of the file
        k = 1;
        // stores the data of products.txt to an array of structure q[]
        while (fscanf(fpr, "%d %s %f %d", &id, name, &price, &quantity) != EOF) // scans the products.txt until the end is reached
        {
            if (strcasecmp(p[0].name, name) == 0) // strcasecmp does not take letter case -> "lays"=="LAYS"
            {
                printf("Id: \t\t%d", id);
                printf("\nName: \t\t%s", name);
                printf("\nPrice: \t\t%.2f", price);
                i = 0;
                break;
            }
            i = 1;
        }
        if (i == 1)
        {
            printf("\nProduct is not available.");
        }
        printf("\nDo you want to search another product?(Y/N) ");
        scanf("%s", &choice);
    } while (choice == 'Y' || choice == 'y');
}
void productDetails()
{
    // displays the product details from products.txt
    fpr = fopen("products.txt", "r"); // file pointer to read products.txt
    printf("Product Details\n\n");
    printf("Id \t Name \t\t\t\t Price");
    printf("\n-----------------------------------------------");
    while (fscanf(fpr, "%d %s %f %d", &id, name, &price, &quantity) != EOF)
    {
        printf("\n%d \t %s \t\t\t\t %.2f ", id, name, price);
    }
    printf("\n\nDo you want to make a purchase? (Y/N)");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y')
        buyProducts(); // calls the buyProducts()
    fclose(fpr);
}
void customerSection()
{
customer:
    printf("\e[1;1H\e[2J");
    // Customer login page
    printf("Customer Section\n");
    printf("1. Show the products available.\n");
    printf("2. Search for a product.\n");
    printf("3. Buy some products.\n");
    printf("4. Exit the program.\n");
    printf("\nWhat do you want to do? ");
choice:
    scanf("%d", &c);
    switch (c)
    {

    case 1:
        printf("\e[1;1H\e[2J");
        productDetails(); // calls productDetails()
        printf("\nGo back to customer section (Y/N): ");
        scanf("%s", &choice);
        if (choice == 'Y' || choice == 'y')
            goto customer;
        printf("\nThank You for visiting us.\n");
        break;
    case 2:
        searchProduct();
        printf("\nGo back to customer section: (Y/N)");
        scanf("%s", &choice);
        if (choice == 'Y' || choice == 'y')
            goto customer;
        else
            printf("\nThank You for visiting us.\n");
        break;
    case 3:
        printf("\e[1;1H\e[2J");
        buyProducts(); // calls buyProducts()
        printf("\nThank You for visiting us.\n");
        break;
    case 4:
        printf("Exiting the program....");
        break;
    default:
        printf("\nInvalid Choice!! Please Enter a valid choice: ");
        goto choice;
    }
}