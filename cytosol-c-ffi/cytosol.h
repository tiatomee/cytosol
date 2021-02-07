/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>


typedef struct cyt_driver_runner cyt_driver_runner;

typedef struct cyt_program cyt_program;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct cyt_program *cyt_program_new(void);

void cyt_program_destroy(struct cyt_program *prog);

struct cyt_driver_runner *cyt_driver_runner_new(void);

void cyt_driver_runner_destroy(struct cyt_driver_runner *driver_runner);

/**
 * # Safety
 * `name` and `source` must be pointers to valid UTF-8 and NUL-terminated strings.
 */
void cyt_driver_runner_add_file_from_string(struct cyt_driver_runner *r,
                                            const char *name,
                                            const char *source);

/**
 * If an error occurs `false` is returned.
 * In that case the error will also be directly written to stdout.
 * If no error occurs then `true` is returned.
 */
bool cyt_driver_runner_compile(struct cyt_driver_runner *r,
                               struct cyt_program *prog);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus