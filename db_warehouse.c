#include <stdio.h>
#include<stdlib.h>
#include<string.h>


struct product
{
  int p_no;
  char p_name[20];
  float price;
  int qnty;
}*prod[16];

static int count = 0;

int db_warehouse_init()
{
    for(int i =0;i<16;i++)
    {
       // prod[i]= NULL;
       struct product *temp;
       temp = (struct product *)malloc(sizeof(struct product));
       prod[i] = temp;

    }
    return 0;
}

int db_warehouse_create_product (char *product_name)
{
    if(count<16)
    {
      void *ptr = NULL;
      int *size;
      int x = db_warehouse_set_internal_data(product_name, ptr, size);
      if(x == -1)
      {
          printf("\nProduct %s already exists..\n",product_name);
      }
      else
        count++;
      return 0;
    }
    else
        return -1;
}

int db_warehouse_get_num_products(int *num_products)
{
    num_products = &count;

}

int db_warehouse_delete_product(char *product_name)
{
    for(int i =0;i<count;i++)
    {
        if(strcmp(prod[i]->p_name,product_name)==0)
        {
            for(int j = i;j<count-1;j++)
            {
                prod[j]=prod[j+1];
            }
            count--;
            printf("\n Product removed ...");
            break;
        }
    }
}

int db_warehouse_update_stock(char *product_name, int stock)
{
     int found = 0;
     for(int i = 0;i<16;i++)
     {
        if(strcmp(prod[i]->p_name,product_name)==0)
        {
            found = 1;
            prod[i]->qnty = stock;
            break;
        }
    }
    if(found==1)
        return 0;
    else
        return -1;
}

int db_warehouse_exists_product(char *product_name)
{
    int search = 0;
    for(int i = 0;i < count;i++)
    {
        if(strcmp(prod[i]->p_name,product_name)==0)
        {
            search = 1;
            break;
        }
    }
    if(search==1)
       return 1;
    else if(search==0)
        return 0;
}

int db_warehouse_get_stock(char *product_name, int *stock)
{
    int found = 0;
    for(int i = 0;i<16;i++)
    {
        int temp = prod[i]->qnty;
        if(strcmp(prod[i]->p_name,product_name)==0)
        {
            found = 1;
            *stock = temp;
            break;
        }
    }
    if(found==1)
        return 0;
    else
        return -1;
}

int db_warehouse_set_internal_data(char *product_name, void *ptr, int size)
{
    int existsPdt = db_warehouse_exists_product(product_name);
    if(existsPdt==0)
    {

  //  printf("Product %d\n",count+1);
    printf("\nEnter product no. :\n");
    scanf("%d", &prod[count]->p_no);
    strcpy(prod[count]->p_name,product_name);
    printf("Enter price :\n");
    scanf("%f", &prod[count]->price);
    printf("Enter quantity :\n");
    scanf("%d",&prod[count]->qnty);
    ptr = prod[count];
    size = sizeof(prod[count]);
    return 0;
    }
    else
        return -1;
}

int db_warehouse_get_internal_data(char *product_name, void **ptr, int *size)
{
    int found = 0;
    for(int i=0;i<count;i++)
    {
        if(strcmp(prod[i]->p_name,product_name)==0)
        {
            found = 1;
            *ptr = &prod[count];
            *size = sizeof(prod[count]);
        }
    }
        if(found == 1)
            return 0;
        else
            return -1;
}

int db_warehouse_destroy()
{
    for(int i=0;i<count;i++)
    {
        free(prod[i]);
    }
}

void db_printalldata()
{
    printf("\n");
    for(int i =0;i<count;i++)
    {
        printf("All Data i = %d  Product_no: %d  Product_Name: %s  Price: %f Qty: %d\n",i,prod[i]->p_no,prod[i]->p_name,prod[i]->price,prod[i]->qnty);
    }
}

