#ifndef BASICSDK_GLOBAL_H
#define BASICSDK_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BASICSDK_LIBRARY)
#  define BASICSDK_EXPORT Q_DECL_EXPORT
#else
#  define BASICSDK_EXPORT Q_DECL_IMPORT
#endif




#endif // BASICSDK_GLOBAL_H
