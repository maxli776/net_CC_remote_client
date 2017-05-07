#include "includes.h"


LIST_HEAD(_t_js_ctx_head);


int joystick_open(char* cp_js_dev_name,int i4_block)  
{  
    int i4_open_flags = O_RDONLY;  
    JOYSTICK_CTX_T* pt_joystick_ctx = NULL;  
    if (!cp_js_dev_name)
	{  
        LOG_ERR("[%s] js device name is NULL\n",__func__);  
        return -1;  
    }
    pt_joystick_ctx = (JOYSTICK_CTX_T*)calloc(sizeof(JOYSTICK_CTX_T),1);  
    if (!pt_joystick_ctx)
	{  
        LOG_ERR("[%s] no memory!!\n", __func__);  
        return -1;  
    }
    pt_joystick_ctx->i4_op_block = i4_block ? 1 : 0;
    if (pt_joystick_ctx->i4_op_block == 0)
	{  
        i4_open_flags |= O_NONBLOCK;  
    }
    pt_joystick_ctx->i4_js_fd = open(cp_js_dev_name,i4_open_flags);  
    if (pt_joystick_ctx->i4_js_fd < 0)
	{  
        LOG_ERR("[%s] open device %s error\n",__func__,cp_js_dev_name);  
        free(pt_joystick_ctx);  
        return -1;  
    }
    list_add_tail(&pt_joystick_ctx->list,&_t_js_ctx_head);
    return pt_joystick_ctx->i4_js_fd; 
}

int joystick_close(int i4_fd)  
{  
    struct list_head* pt_entry;  
    struct list_head* pt_next;  
    JOYSTICK_CTX_T* pt_node;
    if (list_empty(&_t_js_ctx_head))
	{  
        LOG_ERR("[%s] device not opened\n", __func__);  
        return -1;  
    }
    list_for_each_safe(pt_entry,pt_next,&_t_js_ctx_head)
	{  
        pt_node = list_entry(pt_entry,JOYSTICK_CTX_T,list);  
        if (pt_node->i4_js_fd == i4_fd)
		{
            list_del_init(&pt_node->list);
            free(pt_node);
            return close(i4_fd);
        }
    }
    LOG_ERR("[%s] i4_fd=%d invalid\n",__func__, i4_fd);  
    return -1;  
}

int joystick_read_one_event(int i4_fd,struct js_event *tp_jse)  
{  
    int i4_rd_bytes;  
  
    /*do not check i4_fd again*/  
  
    i4_rd_bytes = read(i4_fd,tp_jse,sizeof(struct js_event));  
  
    if (i4_rd_bytes == -1)
	{  
        if (errno == EAGAIN)
		{ /*when no block, it is not error*/  
            return 0;  
        }  
        else
		{  
            return -1;  
        }  
    }  
    return i4_rd_bytes;  
}

int joystick_read_ready(int i4_fd)  
{  
    int i4_block = 2;  
    struct list_head *pt_entry;  
    JOYSTICK_CTX_T *pt_node;
    if (list_empty(&_t_js_ctx_head))
	{  
        LOG_ERR("[%s] device not opened\n", __func__);  
        return -1;  
    }
    list_for_each(pt_entry, &_t_js_ctx_head)
	{  
        pt_node = list_entry(pt_entry,JOYSTICK_CTX_T,list);  
        if (pt_node->i4_js_fd == i4_fd)
		{  
            i4_block = pt_node->i4_op_block;  
            break;  
        }  
    }  
    if (i4_block == 2)
	{  
        LOG_ERR("[%s] i4_fd=%d invalid\n", __func__, i4_fd);  
        return 0;  
    }  
    else if (i4_block == 1)
	{  
        fd_set readfd;  
        int i4_ret = 0;  
        struct timeval timeout = {0, 0};  
        FD_ZERO(&readfd);  
        FD_SET(i4_fd, &readfd);
        i4_ret = select(i4_fd + 1, &readfd, NULL, NULL, &timeout);
        if (i4_ret > 0 && FD_ISSET(i4_fd, &readfd))
		{  
            return 1;  
        }  
        else
		{  
            return 0;  
        }
    }
    return 1; /*noblock read, aways ready*/  
}

void debug_list(void)  
{  
    if (!list_empty(&_t_js_ctx_head))
	{  
        struct list_head* pt_entry;  
        JOYSTICK_CTX_T* pt_node;
        list_for_each(pt_entry, &_t_js_ctx_head)
		{  
            pt_node = list_entry(pt_entry, JOYSTICK_CTX_T, list);  
            LOG_DBG("fd:%d--block:%d\n", pt_node->i4_js_fd, pt_node->i4_op_block);  
        }  
    }  
    else
	{  
        LOG_DBG("-----------> EMPTY NOW\n");  
    }  
}
