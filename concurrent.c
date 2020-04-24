#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "db_warehouse.h"
#include "concurrent.h"

sem_t wrt;
pthread_mutex_t mutex1;
int numread;

int concurrent_init(){
	int ret;

    pthread_mutex_init(&mutex1,NULL);
    sem_init(&wrt,0,1);
    numread = 0;

	ret = db_warehouse_init();
	return ret;
}

int concurrent_destroy(){
	int ret;

	pthread_mutex_destroy(&mutex1);
	sem_destroy(&wrt);

	ret = db_warehouse_destroy();

	return ret;
}

int concurrent_create_product(char *product_name){
	int ret;
	int size;
	void *st_int;

	sem_wait(&wrt);

	//writing into database
	ret = db_warehouse_exists_product(product_name);
	if (ret == 0){
		ret = db_warehouse_create_product(product_name);
		if (ret == 0){
			size = 0;
			st_int = NULL;
			ret = db_warehouse_set_internal_data(product_name, st_int, size);
		}
	}
	else
        printf("\n Product %s already exists",product_name);

    sem_post(&wrt);

	return ret;
}

int concurrent_get_num_products(int *num_products){

	int ret;
	int num_products_aux = 0;

    pthread_mutex_lock(&mutex1);
    numread++;
    if(numread == 1)
    {
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex1);

	// Obtain number of products from DB using the given library
	ret = db_warehouse_get_num_products(&num_products_aux);

	*num_products = num_products_aux;

	pthread_mutex_lock(&mutex1);
	numread--;
	if(numread == 0)
        sem_post(&wrt);
    pthread_mutex_unlock(&mutex1);

	return ret;
}

int concurrent_delete_product(char *product_name){

	int ret, size;
	void *st_int;

	sem_wait(&wrt);

	// Read internal data for reset
	ret = db_warehouse_get_internal_data(product_name, &st_int, &size);
	if (ret == 0){
		st_int = NULL;
		size = 0;
		// Save the internal data after reset
		ret = db_warehouse_set_internal_data(product_name, st_int, size);
	}
	// Delete product from DB using the given library
	ret = db_warehouse_delete_product(product_name);

	sem_post(&wrt);

	return ret;
}

int concurrent_increment_stock(char *product_name, int stock, int *updated_stock){
	int ret, size;
	void *st_int;
	int stock_aux=0;

	sem_wait(&wrt);

	// Obtain internal data to work with them
	ret = db_warehouse_get_internal_data(product_name, &st_int, &size);
	if (ret == 0){
		// Obtain current stock of the product using the given library
		ret = db_warehouse_get_stock(product_name, &stock_aux);

		// Increment stock
		stock_aux += stock;

		// Update stock of the product using the given library
		ret = db_warehouse_update_stock(product_name, stock_aux);
		*updated_stock = stock_aux;
	}
	sem_post(&wrt);

	return ret;
}

int concurrent_decrement_stock(char *product_name, int stock, int *updated_stock){
	int ret, size;
	void *st_int;
	int stock_aux=0;

    sem_wait(&wrt);

	// Obtain internal data to work with them
	ret = db_warehouse_get_internal_data(product_name, &st_int, &size);
	if (ret == 0){
		// Obtain current stock of the product using the given library
		ret = db_warehouse_get_stock(product_name, &stock_aux);

		// Decrement stock
		stock_aux -= stock;

		// Update stock of the product using the given library
		ret = db_warehouse_update_stock(product_name, stock_aux);
		*updated_stock = stock_aux;
	}
	sem_post(&wrt);

	return ret;
}

int concurrent_get_stock(char *product_name, int *stock){
    int stock_aux=0;
	int ret, size;
	void *st_int;

	pthread_mutex_lock(&mutex1);
	numread++;
	if(numread == 1)
        sem_wait(&wrt);

    pthread_mutex_unlock(&mutex1);

	// Obtain internal data to work with them
	ret = db_warehouse_get_internal_data(product_name, &st_int, &size);
	if (ret == 0){

		// Obtain current stock from the product using the given library
		ret = db_warehouse_get_stock(product_name, &stock_aux);
		*stock = stock_aux;

	}

	pthread_mutex_lock(&mutex1);
	numread--;
	if(numread == 0)
        sem_post(&wrt);
    pthread_mutex_unlock(&mutex1);

    return ret;
}
