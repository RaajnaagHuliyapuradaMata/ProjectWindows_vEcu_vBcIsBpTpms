

#ifndef __VRM__1__
#define __VRM__1__

#define osdVrmMajRelNumRef 1

#define osdVrmMinRelNumRef 1

#define osdVrmGenMajRelNumRef 1

#define osdVrmGenMinRelNumRef 1

#else

#ifndef __VRM__2__
#define __VRM__2__

#if defined osdVrmMajRelNum && defined osdVrmMinRelNum

#if osdVrmMajRelNum!=osdVrmMajRelNumRef
#error "VRM: major release number mismatch (Source)"
#endif

#if osdVrmMinRelNum!=osdVrmMinRelNumRef
#error "VRM: minor release number mismatch (Source)"
#endif

#endif

#if defined osdVrmGenMajRelNum && defined osdVrmGenMinRelNum

#if osdVrmGenMajRelNum!=osdVrmGenMajRelNumRef
#error "VRM: major release number mismatch (Generator)"
#endif

#if osdVrmGenMinRelNum!=osdVrmGenMinRelNumRef
#error "VRM: minor release number mismatch (Generator)"
#endif

#endif

#ifdef osdVrmMajRelNum
#undef osdVrmMajRelNum
#endif

#ifdef osdVrmMinRelNum
#undef osdVrmMinRelNum
#endif

#ifdef osdVrmGenMajRelNum
#undef osdVrmGenMajRelNum
#endif

#ifdef osdVrmGenMinRelNum
#undef osdVrmGenMinRelNum
#endif

#endif
#undef  __VRM__2__

#endif

