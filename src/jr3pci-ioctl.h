#include <linux/ioctl.h>
#include <linux/types.h>

#ifndef __JR3IOCTL__
#define __JR3IOCTL__

typedef struct jr3_force_array {
	  int f[3];
	  int m[3];
	  int v[2];
} jr3_force_array;

typedef struct jr3_six_axis_array {
	  int f[3];
	  int m[3];
} jr3_six_axis_array;

#define JR3_IOC_MAGIC 'k'
#define JR3_TYPE JR3_IOC_MAGIC

#define JR3_CONF_RESET							0
#define JR3_CONF_FILTER							1
#define JR3_CONF_ZEROOFFS						8
#define JR3_CONF_GET_FULL_SCALES		9
#define JR3_CONF_NEXT_DEVICE				10

#define IOCTLx_JR3_RESET(d)								_IO ( JR3_TYPE, JR3_CONF_NEXT_DEVICE * d + JR3_CONF_RESET )
#define IOCTLx_JR3_FILTER(d, f)						_IOR( JR3_TYPE, JR3_CONF_NEXT_DEVICE * d + JR3_CONF_FILTER + f,  struct jr3_six_axis_array )
#define IOCTLx_JR3_ZEROOFFS(d)						_IO ( JR3_TYPE, JR3_CONF_NEXT_DEVICE * d + JR3_CONF_ZEROOFFS)
#define IOCTLx_JR3_GET_FULL_SCALES(d)			_IOR( JR3_TYPE, JR3_CONF_NEXT_DEVICE * d + JR3_CONF_GET_FULL_SCALES,  struct jr3_force_array )

#define IOCTL0_JR3_RESET              _IO ( JR3_TYPE, JR3_CONF_RESET )
#define IOCTL0_JR3_FILTER0            _IOR( JR3_TYPE, JR3_CONF_FILTER,  struct jr3_six_axis_array )
#define IOCTL0_JR3_FILTER1            _IOR( JR3_TYPE, JR3_CONF_FILTER + 1,  struct jr3_six_axis_array )
#define IOCTL0_JR3_FILTER2            _IOR( JR3_TYPE, JR3_CONF_FILTER + 2,  struct jr3_six_axis_array )
#define IOCTL0_JR3_FILTER3            _IOR( JR3_TYPE, JR3_CONF_FILTER + 3,  struct jr3_six_axis_array )
#define IOCTL0_JR3_FILTER4            _IOR( JR3_TYPE, JR3_CONF_FILTER + 4,  struct jr3_six_axis_array )
#define IOCTL0_JR3_FILTER5            _IOR( JR3_TYPE, JR3_CONF_FILTER + 5,  struct jr3_six_axis_array )
#define IOCTL0_JR3_FILTER6            _IOR( JR3_TYPE, JR3_CONF_FILTER + 6,  struct jr3_six_axis_array )
#define IOCTL0_JR3_ZEROOFFS           _IO ( JR3_TYPE, JR3_CONF_ZEROOFFS   )
#define IOCTL0_JR3_GET_FULL_SCALES    _IOR( JR3_TYPE, JR3_CONF_GET_FULL_SCALES,  struct jr3_force_array )

#define IOCTL1_JR3_RESET              _IO ( JR3_TYPE, JR3_CONF_NEXT_DEVICE + JR3_CONF_RESET )
#define IOCTL1_JR3_FILTER0            _IOR( JR3_TYPE, JR3_CONF_NEXT_DEVICE + JR3_CONF_FILTER,  struct jr3_six_axis_array )
#define IOCTL1_JR3_FILTER1            _IOR( JR3_TYPE, JR3_CONF_NEXT_DEVICE + JR3_CONF_FILTER + 1,  struct jr3_six_axis_array )
#define IOCTL1_JR3_FILTER2            _IOR( JR3_TYPE, JR3_CONF_NEXT_DEVICE + JR3_CONF_FILTER + 2,  struct jr3_six_axis_array )
#define IOCTL1_JR3_FILTER3            _IOR( JR3_TYPE, JR3_CONF_NEXT_DEVICE + JR3_CONF_FILTER + 3,  struct jr3_six_axis_array )
#define IOCTL1_JR3_FILTER4            _IOR( JR3_TYPE, JR3_CONF_NEXT_DEVICE + JR3_CONF_FILTER + 4,  struct jr3_six_axis_array )
#define IOCTL1_JR3_FILTER5            _IOR( JR3_TYPE, JR3_CONF_NEXT_DEVICE + JR3_CONF_FILTER + 5,  struct jr3_six_axis_array )
#define IOCTL1_JR3_FILTER6            _IOR( JR3_TYPE, JR3_CONF_NEXT_DEVICE + JR3_CONF_FILTER + 6,  struct jr3_six_axis_array )
#define IOCTL1_JR3_ZEROOFFS           _IO ( JR3_TYPE, JR3_CONF_NEXT_DEVICE + JR3_CONF_ZEROOFFS   )
#define IOCTL1_JR3_GET_FULL_SCALES    _IOR( JR3_TYPE, JR3_CONF_NEXT_DEVICE + JR3_CONF_GET_FULL_SCALES,  struct jr3_force_array )

#define IOCTL_JR3_MAXNR 20
#endif

