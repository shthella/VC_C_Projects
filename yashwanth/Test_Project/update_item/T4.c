#include "database.h"
#include <stdlib.h>
#include <sqlite3.h>
#include <stdio.h>
#include <sys/socket.h>

#include "T4.h"
#include "updateItem.h"

void printest(int b,int n,int r){
	//sleep(1);
	if(r==0){
	printf("Test case T%d_%d - passed\n",b,n);
	}
	else{
	printf("Test case T%d_%d - failed>>\n",b,n);	
	}
}
void test_updateItem(sqlite3 *db){
	int r1 = update_item(1, 1, "vada", 30); // Test valid data
	printest(1,1,r1);
	int r2 = update_item(3, 2, "poori", 40); // Test no restaurant_id
	printest(1,2,r2);
	int r3 = update_item(-1, -1, "idly", 20); // Test invalid restaurant_id, item_id
	printest(1,3,r3);
	int r4 = update_item(-1, 1, "vada", 10); // Test invalid restaurant_id
	printest(1,4,r4);
	int r5 = update_item(2, 1, NULL, 50); // Test null item_name
	printest(1,5,r5);
	int r6 = update_item(2, 2, "poori", -60); // Test invalid price
	printest(1,6,r6);

}
