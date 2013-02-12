#define MAXPATHLEN 4096

#define TR {printf("[Trace] in function %s, line %d, file %s\n",__FUNCTION__,__LINE__,__FILE__);}

#define PACKAGE_VERSION "1.9"
#define PREFIX "./"

#ifndef inline
#define inline __inline__
#endif

#define ALIGNED_128 __attribute__((aligned(128)))
#define ALIGNED_32 __attribute__((aligned(32)))
#define ALIGNED ALIGNED_128
