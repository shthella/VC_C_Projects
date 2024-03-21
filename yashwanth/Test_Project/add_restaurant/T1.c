#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include "T1.h"
#include "addrest.h"

void printest(int b,int n,int r){
	//sleep(1);
	if(r==0){
	printf("Test case T%d_%d - passed\n",b,n);
	}
	else{
	printf("Test case T%d_%d - failed>>\n",b,n);	
	}
}
void test_addrest(sqlite3 *db){
	int r1 = add_restaurant("VC", "Hyd", "123"); // Test valid data
	printest(1,1,r1);
	int r2 = add_restaurant(NULL, "Hyd", "123"); // Test invalid restaurant
	printest(1,2,r2);
	int r3 = add_restaurant("VC", NULL, "123"); // Test invalid address
	printest(1,3,r3);
	int r4 = add_restaurant("VC", "Hyd", NULL); // Test invalid contact_number
	printest(1,4,r4);
	int r5 = add_restaurant(NULL, NULL, "123"); // Test invalid restaurant, address
	printest(1,5,r5);
	int r6 = add_restaurant("VC", NULL, NULL); // Test invalid address, contact_number
	printest(1,6,r6);
	int r7 = add_restaurant(NULL, "Hyd", NULL); // Test invalid restaurant, contact_number
	printest(1,7,r7);
	int r8 = add_restaurant(NULL, NULL, NULL); // Test invalid restaurant, address and contact_number
	printest(1,8,r8);
}
