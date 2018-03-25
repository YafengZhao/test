/*
 * =====================================================================================
 *
 *       Filename:  emptyStruct.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018年03月25日 01时05分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhaoyafeng (), zhaoyafeng0615@163.com
 *   Organization:  GNU
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>

struct A_t {

}A_t;


int main(void)
{

	fprintf(stderr, "empty struct size: %lu\n", sizeof (A_t ));
	return 0;
}
