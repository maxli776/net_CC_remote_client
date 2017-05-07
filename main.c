#include "includes.h"

int server_sockfd;
int fd,rc;
unsigned short _16data;
unsigned short power = 0;
unsigned short direction = 32767;
char number_of_axes = 0;  
char number_of_btns = 0;  
char js_name_str[128];  
unsigned int buttons_state = 0;  
AXES_T *tp_axes = NULL;  
int i, print_init_stat = 0;  
struct js_event jse;

void all_init();

void all_init()
{
    server_sockfd = net_init();
    if(handshake(server_sockfd) == 0)
    {
        perror("handshake error");
        exit(0);
    }
    fd = joystick_open("/dev/input/js0", 1);  
    if (fd < 0)
	{
		printf("open failed.\n");
        exit(1);  
    }  
    rc = ioctl(fd,JSIOCGAXES,&number_of_axes);  
    if (rc!= -1)
	{
		printf("number_of_axes:%d\n", number_of_axes);  
        if (number_of_axes > 0)
            tp_axes = (AXES_T*)calloc(sizeof(AXES_T),1);
    }  
    rc = ioctl(fd,JSIOCGBUTTONS,&number_of_btns);  
    if(rc != -1)
		printf("number_of_btns:%d\n", number_of_btns);   
    if(ioctl(fd,JSIOCGNAME(sizeof(js_name_str)),js_name_str) < 0)
		printf(js_name_str, "Unknown", sizeof(js_name_str));
	printf("joystick Name: %s\n", js_name_str);
}

int main()
{
    all_init();
    while(1)
	{
        if(joystick_read_ready(fd))
		{  
            rc = joystick_read_one_event(fd,&jse);
            _16data = (unsigned short)(jse.value+32767);
            if (rc > 0)
			{
				if(jse.type == JS_EVENT_AXIS)
				{
					switch(jse.number)
					{
						case 0:
							printf("AXIS!\nNumber:%d Value:%d\n",jse.number,jse.value+32767);
							send_dirction(server_sockfd,(unsigned char)_16data,(unsigned char)(_16data>>8));//send direction values
							break;
						case 4:
							printf("AXIS!\nNumber:%d Value:%d\n",jse.number,jse.value+32767);
							send_engine(server_sockfd,(unsigned char)_16data,(unsigned char)(_16data>>8));//sned engine values
							break;
						case 3:
							printf("AXIS!\nNumber:%d Value:%d\n",jse.number,jse.value+32767);
                        	send_backEngine(server_sockfd,(unsigned char)_16data,(unsigned char)(_16data>>8));//sned engine values
                        	break;
						case 6:
							printf("AXIS!\nNumber:%d Value:%d\n",jse.number,jse.value+32767);
							if(_16data == 65534)
								send_ramX(server_sockfd,0xFF);//sned engine values
							else if(_16data == 0)
								send_ramX(server_sockfd,0x00);//sned engine values
							else if(_16data == 32767)
								send_ramX(server_sockfd,0xFE);//sned engine values
							break;
						case 7:
							printf("AXIS!\nNumber:%d Value:%d\n",jse.number,jse.value+32767);
							if(_16data == 65534)
								send_ramY(server_sockfd,0xFF);//sned engine values
							else if(_16data == 0)
								send_ramY(server_sockfd,0x00);//sned engine values
							else if(_16data == 32767)
								send_ramY(server_sockfd,0xFE);//sned engine values
							break;
					}
				}
            }  
        }
        usleep(5000);
    }
    joystick_close(fd); 
    if (tp_axes)
    {  
        free(tp_axes);  
    }

}



