#ifndef _CL_LOG_H_
#define _CL_LOG_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

typedef struct _CL_Logger CL_Logger;

enum CL_LogLevel
{
	CL_LOG_LEVEL_FATAL = 0,
	CL_LOG_LEVEL_ERROR,
	CL_LOG_LEVEL_WARN,
	CL_LOG_LEVEL_INFO,
	CL_LOG_LEVEL_TRACE,
	CL_LOG_LEVEL_COUNT
};

enum CL_ColorEnabled
{
	CL_COLOR_DISABLED = 0,
	CL_COLOR_ENABLED
};

#ifdef CL_LOG_DISABLED
#define CL_LOG(logger, level, ...)
#else
#define CL_LOG(logger, level, ...) _cl_logger_log(logger, level, __FILE__, __LINE__, __VA_ARGS__)
#endif

#define CL_LOG_TRACE(logger, ...) CL_LOG(logger, CL_LOG_LEVEL_TRACE, __VA_ARGS__)
#define CL_LOG_INFO(logger, ...) CL_LOG(logger, CL_LOG_LEVEL_INFO, __VA_ARGS__)
#define CL_LOG_WARN(logger, ...) CL_LOG(logger, CL_LOG_LEVEL_WARN, __VA_ARGS__)
#define CL_LOG_ERROR(logger, ...) CL_LOG(logger, CL_LOG_LEVEL_ERROR, __VA_ARGS__)
#define CL_LOG_FATAL(logger, ...) CL_LOG(logger, CL_LOG_LEVEL_FATAL, __VA_ARGS__)

#define CL_LOGGER_CREATE(output_count, name) _cl_logger_create(output_count, name)
#define CL_LOGGER_OUTPUT_ADD(logger, file, colors_enabled) _cl_logger_output_add(logger, file, colors_enabled)
#define CL_LOGGER_DESTROY(logger) _cl_logger_destroy(logger)

#define CL_INIT() _cl_init()
#define CL_TERMINATE() _cl_terminate()

void _cl_init();
void _cl_terminate();

CL_Logger *_cl_logger_create(uint16_t ouput_count, const char *name);
void _cl_logger_output_add(CL_Logger *logger, FILE *file, uint8_t color_output);
void _cl_logger_destroy(CL_Logger *logger);

void _cl_logger_log(CL_Logger *logger, uint32_t lvl, const char *file, uint32_t line,  const char *format, ...);

#endif