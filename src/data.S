#include "data.h"
	.data
	datafile license          "../data/LICENSE"
  datafile version          "../data/VERSION"
#ifdef DEVELOPMENT_BUILD
  datafile version_temp     "../data/VERSION_TEMPLATE_DEV"
#else
  datafile version_temp     "../data/VERSION_TEMPLATE"
#endif

