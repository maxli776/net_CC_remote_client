#ifndef JOY_H
#define JOY_H

#if 1  
#define LOG_DBG(fmt, ...)  fprintf(stdout, fmt, ##__VA_ARGS__)  
#else  
#define LOG_DBG(fmt, ...)  
#endif

#define LOG_ERR(fmt, ...)  fprintf(stderr, fmt, ##__VA_ARGS__)

typedef struct _joy_stick_ctx
{
	struct list_head list;
	int i4_js_fd;
	unsigned int i4_op_block;  
}JOYSTICK_CTX_T;

typedef struct _axes_t
{
	int x;
	int y;  
}AXES_T;

extern AXES_T *tp_axes;
extern JOYSTICK_CTX_T *pt_joystick_ctx;
extern JOYSTICK_CTX_T *pt_node;


int joystick_open(char* cp_js_dev_name, int i4_block);
int joystick_close(int i4_fd);
int joystick_read_one_event(int i4_fd, struct js_event* tp_jse);
int joystick_read_ready(int i4_fd);
void debug_list(void);

#endif