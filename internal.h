#ifndef _CL_LOG_INTERNAL_H_
#define _CL_LOG_INTERNAL_H_

#include "c_log.h"

typedef struct _CL_TimeInfo CL_TimeInfo;
typedef struct _CL_GlobalInfo CL_GlobalInfo;

extern CL_GlobalInfo *g_cl_info;

// --- Time --- //

#ifdef __unix__
#include <sys/time.h>
typedef struct _CL_TimeInfo
{
	struct timeval tv;
	time_t t;
	struct tm info;
	char string[10];
} CL_TimeInfo;

#define _CL_LOG_UPDATE_TIME()                               \
	gettimeofday(&g_cl_info->time.tv, NULL);                \
	g_cl_info->time.t = g_cl_info->time.tv.tv_sec;          \
	localtime_r(&g_cl_info->time.t, &g_cl_info->time.info); \
	strftime(g_cl_info->time.string, sizeof(g_cl_info->time.string), "%H:%M:%S", &g_cl_info->time.info);

#elif defined _WIN32 || defined WIN32
#include <Windows.h>
#undef ERROR

typedef struct _CL_TimeInfo
{
	SYSTEMTIME info;
	char string[10];
} CL_TimeInfo;

#define _CL_LOG_UPDATE_TIME()             \
	GetSystemTime(&g_cl_info->time.info); \
	GetTimeFormatA(LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, &g_cl_info->time.info, NULL, g_cl_info->time.string, sizeof(g_cl_info->time.string));

#endif
// --- --- //

// --- Color --- //

#ifdef __unix__
#define _CL_LOG_COLOR_SET(lvl) fprintf(stdout, "%s", g_cl_info->color[lvl])
#define _CL_LOG_COLOR_RESET() _CL_LOG_COLOR_SET(CL_LOG_LEVEL_COUNT)
#elif defined _WIN32 || defined WIN32
#define _CL_LOG_COLOR_SET(lvl) /* color not supported yet on windows */
#define _CL_LOG_COLOR_RESET()
#endif

// --- --- //

// --- Pattern --- //

enum CL_SegmentType
{
	CL_SEGMENT_TYPE_FILE = 0,
	CL_SEGMENT_TYPE_LINE,
	CL_SEGMENT_TYPE_LOG_LEVEL,
	CL_SEGMENT_TYPE_TIME,
	CL_SEGMENT_TYPE_MESSAGE,
	CL_SEGMENT_TYPE_NAME,
	CL_SEGMENT_TYPE_COLOR,
	CL_SEGMENT_TYPE_STRING,
	CL_SEGMENT_TYPE_COUNT
};

typedef struct _CL_Pattern
{
	const char *string;
	uint32_t segment_count_c;
	uint32_t segment_count_m;
	uint8_t *segment_types;
	char **segment_values;
} CL_Pattern;

// --- --- //

typedef struct _CL_Logger
{
	uint32_t log_level;
	uint16_t output_count_c;
	uint16_t output_count_m;
	uint8_t *output_colors;
	FILE **outputs;
	const char *name;
	CL_Pattern pattern;
} CL_Logger;

typedef struct _CL_GlobalInfo
{
	CL_TimeInfo time;
	const char *color[CL_LOG_LEVEL_COUNT + 1];
	const char *log_level_names[CL_LOG_LEVEL_COUNT];
	CL_Logger default_logger;
	const char *default_pattern;
} CL_GlobalInfo;

#endif