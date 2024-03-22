#include "database.h"
#include <stdlib.h>
#include <sqlite3.h>
#include <stdio.h>
#include <sys/socket.h>

#include "T3.h"
#include "remItem.h"

void printest(int b,int n,int r){
	//sleep(1);
	if(r==0){
	printf("Test case T%d_%d - passed\n",b,n);
	}
	else{
	printf("Test case T%d_%d - failed>>\n",b,n);	
	}
}
void test_remitem(sqlite3 *db){
	int r1 = remove_item(1, 2); // Test valid data
	printest(1,1,r1);
	int r2 = remove_item(1, 10); // Test invalid item_name
	printest(1,2,r2);
	int r3 = remove_item(-1, 1); // Test invalid restuarant_id
	printest(1,3,r3);
	int r4 = remove_item(-2, -3); // Test invalid  restaurant_id, item_name
	printest(1,4,r4);
	int r5 = remove_item(2, -4); // Test invalid item_name
	printest(1,5,r5);
	int r6 = remove_item(9, 3); // Test no restaurant-id 
	printest(1,6,r6);
}
	
