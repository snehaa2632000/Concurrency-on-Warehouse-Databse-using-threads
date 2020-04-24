#ifndef SEQUENTIAL_H_INCLUDED
#define SEQUENTIAL_H_INCLUDED

#include "db_warehouse.h"

/*
Description: initializes the database and the library resources. Use once at the beginning.
Return value: 0 ->ok, -1 ->error
 */
int sequential_init();


/*
Description: frees the resources of the database and the resources used by the library. Use once at the end of the program.
Return value: 0->ok, -1->error
 */
int sequential_destroy();


/*
Description: stores a new product in the warehouse. If the product already exists the operation is considered successful.
Input: product name.
Return value: 0 ok, -1 error
 */
int sequential_create_product(char *product_name);


 /*
Description: gets the number of products in the warehouse.
Output: number of products.
Return value: 0->ok, -1 -> error
 */
int sequential_get_num_products(int *num_products);


/*
Description: deletes from the warehouse the first matching product (the whole product including all its stock). If the product is not found the operation is considered successful.
Input: product name.
Return value: 0 -> ok, -1->error
 */
int sequential_delete_product(char *product_name);

/*
Description: increments the stock of a product and returns the updated stock.
Input: product name and amount of stock to be added.
Output: updated stock.
Return value: 0 ->ok, -1 ->error (product not found, etc.)
*/
int sequential_increment_stock(char *product_name, int stock, int *updated_stock);


/*
Description decrements the stock of a product and returns the updated stock.
Input: product name and amount of stock to be subtracted.
Output: updated stock.
Return value: 0->ok, -1 ->error (product not found, etc.)
 */
int sequential_decrement_stock(char *product_name, int stock, int *updated_stock);


/*
Description: gets the stock of a product.
Input: product name.
Output: updated stock.
Return value: 0->ok, -1 ->error (product not found, etc.)
 */
int sequential_get_stock(char *product_name, int *stock);


#endif // SEQUENTIAL_H_INCLUDED
