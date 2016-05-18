#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <errno.h>
#include <ctype.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

int main()
{
	int fd;
	char arr[128];
	int screensize, row_size, blue, green, red, i=256, j=128;
	fd = open("/dev/fb0", O_RDWR, 777);
	if (fd == -1) {
		perror("Error: cannot open framebuffer device");
		exit(0);
	}
	struct fb_var_screeninfo vinfo;
	if(ioctl(fd, FBIOGET_VSCREENINFO, &vinfo)== -1) {
		perror("Error reading variable information");
		exit (-1);
	}
	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel /8;
	row_size = vinfo.xres * vinfo.bits_per_pixel /8;
	
	char  *fbp;
	fbp = (char  *)mmap(0,screensize,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
	while(fbp != NULL) {

		printf("%s", fbp++);
	}
	munmap(fbp, screensize);
	close(fd);

}

