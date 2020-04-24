#ifndef DB_WAREHOUSE_H_INCLUDED
#define DB_WAREHOUSE_H_INCLUDED

/*
Description: initializes the database. Use once at the beginning.
Return value: 0  ok, -1  error
 */
int db_warehouse_init();

/*
Description: frees the resources of the database. Use once at the ending.
Return value: 0  ok, -1  error
 */
int db_warehouse_destroy();

/*
Description: stores a new product in the warehouse. It doesn’t check if that product already exists.
Input: product name.
Return value: 0  ok, -1 error there is no space.  (16 products max).
 */
int db_warehouse_create_product(char *product_name);

/*
Description: gets the number of products in the warehouse.
Output: number of products.
Return value: 0 ok, -1 error
 */
int db_warehouse_get_num_products(int *num_products);

/*
Description: deletes from the warehouse the first matching product (the whole product including all its stock).
Input: product name.
Return value: 0  ok, -1  error product not found.
 */
int db_warehouse_delete_product(char *product_name);

/*
Description: checks if a product exists.
Input: product name to be checked.
Return value: 1   exists, 0  doesn’t exist
 */
int db_warehouse_exists_product(char *product_name);

/*
Description: updates the stock of a product.
Input: product name and stock.
Return value: 0  ok, -1  error product not found
 */
int db_warehouse_update_stock(char *product_name, int stock);

/*
Description: gets the stock of a product.
Input: product name.
Output: product stock.
Return value: 0  ok, -1  error product not found.
 */
int db_warehouse_get_stock(char *product_name, int *stock);

/*
Description: allows to associate to a product internal data defined by the user. It can be used to store structures necessary to synchronize concurrent accesses to a product.
Input: product name, pointer to the data and size of the data.
Return value: 0  ok, -1  error product not found.
 */
int db_warehouse_set_internal_data(char *product_name, void *ptr, int size);

/*
Description: returns the internal data associated to a product.
Input: product name.
Output: pointer to the data and size of the data.
Return value: 0  ok, -1  error product not found.
 */
int db_warehouse_get_internal_data(char *product_name, void **ptr, int *size);


#endif // DB_WAREHOUSE_H_INCLUDED
