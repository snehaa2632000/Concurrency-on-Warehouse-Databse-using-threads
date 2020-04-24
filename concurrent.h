#ifndef CONCURRENT_H_INCLUDED
#define CONCURRENT_H_INCLUDED

/*
 * Add all necessary headers
 */
#include "db_warehouse.h"
#define MAX_READERS 5

/*
Description: initializes the database and the library resources, including all concurrent mechanisms necessary to protect the access to the database. Use once at the beginning.
Type and scope: none
Return value: 0 -> ok, -1 -> error
 */
int concurrent_init();

/*
Description: frees the resources of the database and the resources used by the library, including all synchronization mechanisms. Use once at the end of the program.
Type and scope: none.
Return value: 0 -> ok, -1 -> error
 */
int concurrent_destroy();

/*
Description: stores a new product in the warehouse. If the product already exists the operation is considered successful.
Type and scope: GLOBAL WRITE
Input: product name.
Return value: 0 -> ok, -1 -> error
 */
int concurrent_create_product(char *product_name);


 /*
Description: gets the number of products in the warehouse.
Type and scope: GLOBAL READ
Output: number of products.
Return value: 0 -> ok, -1 -> error
 */
int concurrent_get_num_products(int *num_products);


/*
Description: deletes from the warehouse the first matching product (the whole product including all its stock). If the product is not found the operation is considered successful.
Type and scope: GLOBAL WRITE
Input: product name.
Return value: 0 -> ok, -1 -> error
 */
int concurrent_delete_product(char *product_name);

/*
Description: increments the stock of a product and returns the updated stock.
Type and scope: GLOBAL READ. LOCAL (to that product) WRITE.
Input: product name and amount of stock to be added.
Output: stock updated.
Return value: 0 -> ok, -1 -> error (product not found, etc.)
 */
int concurrent_increment_stock(char *product_name, int stock, int *updated_stock);


/*
Description: decrements the stock of a product and returns the updated stock.
Type and scope: GLOBAL READ. LOCAL (to that product) WRITE.
Input: product name and amount of stock to be subtracted.
Output: stock updated.
Return value: 0 -> ok, -1 -> error (product not found, etc.)
 */
int concurrent_decrement_stock(char *product_name, int stock, int *updated_stock);


/*
Description: gets the stock of a product.
Type and scope: GLOBAL READ. LOCAL (to that product) READ.
Input: product name.
Output: updated stock.
Return value: 0 -> ok, -1 -> error (product not found, etc.)
 */
int concurrent_get_stock(char *product_name, int *stock);

#endif // CONCURRENT_H_INCLUDED
