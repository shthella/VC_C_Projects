#include "database.h"
#include <stdlib.h>
#include <sqlite3.h>
#include <stdio.h>
#include <sys/socket.h>
#include "T2.h"
#include "addItem.h"

void printest(int b,int n,int r){
	//sleep(1);
	if(r==0){
	printf("Test case T%d_%d - passed\n",b,n);
	}
	else{
	printf("Test case T%d_%d - failed>>\n",b,n);	
	}
}
void test_additem(sqlite3 *db){
	int r1 = add_item(1, "upma", 33); // Test valid data
	printest(1,1,r1);
	int r2 = add_item(10, "upma", 44); // Test no restaurant_id
	printest(1,2,r2);
	int r3 = add_item(-1, "upma", 22); // Test invalid restaurant_id
	printest(1,3,r3);
	int r4 = add_item(1, NULL, 11); // Test invalid item_name
	printest(1,4,r4);
	int r5 = add_item(2, "vada", 55.0); // Test valid data
	printest(1,5,r5);
	int r6 = add_item(2, "vada", -66); // Test invalid price 
	printest(1,6,r6);
	int r7 = add_item(2, "vada", -77.0); // Test incalid price
	printest(1,7,r7);
}
