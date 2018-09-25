#include "vr_config.h"
#include "vr_core.h"

static void
get_level_str(int level, char level_str[VR_LOG_LEVEL_STRLEN])
{
	const char * level_str_t;
	switch (level)
    {
    case VR_LOG_DEBUG:
        level_str_t = "DEBUG";
        break;
    case VR_LOG_NOTICE:
        level_str_t = "NOTICE";
        break;
    case VR_LOG_ERROR:
        level_str_t = "ERROR";
        break;
    case VR_LOG_WARNING:
        level_str_t = "WARNING";
        break;
    case VR_LOG_TRACE:
        level_str_t = "TRACE";
        break;
    default:
        level_str_t = "INFO";
        break;
    }
	snprintf(level_str, VR_LOG_LEVEL_STRLEN, "%s", level_str_t);
}

static void
get_date_str(char date_str[VR_LOG_DATE_STRLEN])
{
	time_t t;
    struct tm *p;
    t = time(NULL);
    p = localtime(&t);
	
	snprintf(date_str, 
		VR_LOG_DATE_STRLEN, 
		"%d-%02d-%02d %02d:%02d:%02d", 
		p->tm_year + 1900, 
		p->tm_mon + 1, 
		p->tm_mday, 
		p->tm_hour, 
		p->tm_min, 
		p->tm_sec);
}

vr_int_t 
vr_init_log(vr_context_t *vr_context)
{
	char *log_file;
	vr_core_conf_t *ccf = vr_context->ccf;
	struct conf *conf = vr_context->conf;
	
	log_file = conf_get_value(conf, "core", "log_file");
	vr_int_t log_fd = open(log_file, O_APPEND| O_RDWR | O_CREAT, 0666);
	
	if(log_fd < 0)
	{
		return VR_ERROR;
	}
	
	ccf->log_fd = log_fd;
	return VR_OK;
}

void 
vr_put_log(vr_context_t *vr_context, int level, char *cnt)
{
	int len;
	char log_str[VR_LOG_BUFFER_SIZE];
	char date_str[VR_LOG_DATE_STRLEN];
	char level_str[VR_LOG_LEVEL_STRLEN];
	
	vr_core_conf_t *ccf = vr_context->ccf;
	
	get_level_str(level, level_str);
	get_date_str(date_str);
	
	len = snprintf(log_str, VR_LOG_BUFFER_SIZE, "[%s]\t%s\t%s\n", date_str, level_str, cnt);
    
	if (write(ccf->log_fd, log_str, len) < 0)
    {
        printf("write(log_fd, size=%d) failed. Error: %s[%d].\n", len, strerror(errno), errno);
    }
}

void 
vr_destroy_log(vr_context_t *vr_context)
{
	vr_core_conf_t *ccf = vr_context->ccf;
	close(ccf->log_fd);
}