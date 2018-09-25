#include "vr_config.h"
#include "vr_core.h"

vr_int_t 
vr_init_context(vr_context_t *vr_context, u_char  *vr_conf_file)
{
	struct conf *conf;
	
	vr_core_conf_t *ccf = (vr_core_conf_t *)vr_malloc(sizeof(vr_core_conf_t));
	if(ccf == NULL || vr_context == NULL)
		return VR_ERROR;
	
	ccf->conf_r = NULL;
	
	conf = read_conf(&ccf->conf_r, vr_conf_file);
	if(conf == NULL)
		return VR_ERROR;
	
	vr_context->conf = conf;
	vr_context->ccf = ccf;
	return VR_OK;
}

void 
vr_destroy_context(vr_context_t *vr_context)
{

}