#include <stdlib.h>
#include <stdio.h>
#include "db_warehouse.h"
#include "sequential.h"

int sequential_init(){
	int ret;

	ret = db_warehouse_init();

	return ret;
}

int sequential_destroy(){
	int ret;

	ret = db_warehouse_destroy();

	return ret;
}

int sequential_create_product(char *product_name){
	int ret;
	int size;
	void *st_int;

	ret = db_warehouse_exists_product(product_name);
	if (ret == 0){
		ret = db_warehouse_create_product(product_name);
		if (ret == 0){
			size = 0;
			st_int = NULL;
			ret = db_warehouse_set_internal_data(product_name, st_int, size);
		}
	}

	return ret;
}

int sequential_get_num_products(int *num_products){
	int ret;
	int num_products_aux = 0;

	// Obtain number of products from DB using the given library
	ret = db_warehouse_get_num_products(&num_products_aux);

	*num_products = num_products_aux;

	return ret;
}

int sequential_delete_product(char *product_name){
	int ret, size;
	void *st_int;

	// Read internal data to reset
	ret = db_warehouse_get_internal_data(product_name, &st_int, &size);
	if (ret == 0){
		st_int = NULL;
		size = 0;
		// Save internal data
		ret = db_warehouse_set_internal_data(product_name, st_int, size);
	}
	// Delete product from DB using the given library
	ret = db_warehouse_delete_product(product_name);


	return ret;
}

int sequential_increment_stock(char *product_name, int stock, int *updated_stock){
	int ret, size;
	void *st_int;

	int stock_aux=0;

	ret = db_warehouse_get_internal_data(product_name, &st_int, &size);
	if (ret == 0){
        ret = db_warehouse_get_stock(product_name, &stock_aux);

       	stock_aux += stock;

		ret = db_warehouse_update_stock(product_name, stock_aux);

		*updated_stock = stock_aux;
	}
	return ret;
}

int sequential_decrement_stock(char *product_name, int stock, int *updated_stock){
	int ret, size;
	void *st_int;

	int stock_aux=0;
	// Obtain internal data to work with them
	ret = db_warehouse_get_internal_data(product_name, &st_int, &size);
	if (ret == 0){
		ret = db_warehouse_get_stock(product_name, &stock_aux);

		stock_aux -= stock;

		ret = db_warehouse_update_stock(product_name, stock_aux);

		*updated_stock = stock_aux;
	}

	return ret;
}

int sequential_get_stock(char *product_name, int *stock){
    int stock_aux=0;
	int ret, size;
	void *st_int;

	ret = db_warehouse_get_internal_data(product_name, &st_int, &size);
	if (ret == 0){
		ret = db_warehouse_get_stock(product_name, &stock_aux);

		*stock = stock_aux;
	}

    return ret;
}
