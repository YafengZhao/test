/*
 * =====================================================================================
 *
 *       Filename:  notify.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018年04月20日 19时34分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhaoyafeng (), zhaoyafeng0615@163.com
 *   Organization:  GNU
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/inotify.h>
#include <errno.h>
#include <error.h>
#include <cstdio>
#include <cstring>

int main(void)
{
	int fd = inotify_init();
	if(fd == -1) {

		std::cout << "Can not create fd errmsg: " << std::strerror(errno) << std::endl;
	}

	std::cout << "Successfully ..." << fd << std::endl;

	getchar();
	return 0;
}
