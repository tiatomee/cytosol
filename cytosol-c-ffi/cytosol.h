/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>


typedef enum cyt_run_result {
        CYT_RUN_RESULT_MADE_PROGRESS,
        CYT_RUN_RESULT_NO_PROGRESS,
} cyt_run_result;

typedef enum cyt_value_type {
        CYT_VALUE_TYPE_BOOL,
        CYT_VALUE_TYPE_INTEGER,
        CYT_VALUE_TYPE_STRING,
        CYT_VALUE_TYPE_RECORD,
} cyt_value_type;

typedef struct cyt_cell_env cyt_cell_env;

typedef struct cyt_driver_runner cyt_driver_runner;

typedef struct cyt_exec_state cyt_exec_state;

typedef struct cyt_program cyt_program;

typedef struct cyt_value_buffer cyt_value_buffer;

typedef struct cyt_record_id {
        uint32_t _0;
        size_t _1;
} cyt_record_id;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct cyt_program *cyt_program_new(void);

void cyt_program_destroy(struct cyt_program *prog);

/**
 * # Safety
 * `name` must be a valid pointer to a UTF-8 and NUL-terminated string.
 */
bool cyt_program_record_by_name(const struct cyt_program *prog,
                                const char *name,
                                struct cyt_record_id *out_id);

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
 * Load a file from a path
 *
 * When the loading was successful, `0` is returned.
 * If an error occured then the OS error code will be returned.
 * If there was an error but no OS error code is present then `-1` will be returned.
 *
 * # Safety
 * `path` must be a pointer to a NUL-terminated string representing a path.
 */
int32_t cyt_driver_runner_add_file_from_path(struct cyt_driver_runner *r,
                                             const char *path);

/**
 * If an error occurs `false` is returned.
 * In that case the error will also be directly written to stdout.
 * If no error occurs then `true` is returned.
 */
bool cyt_driver_runner_compile(struct cyt_driver_runner *r,
                               struct cyt_program *prog);

/**
 * Run the program for one single iteration.
 */
enum cyt_run_result cyt_driver_runner_run_single_iteration(struct cyt_driver_runner *r,
                                                           const struct cyt_program *prog,
                                                           struct cyt_exec_state *exec_state,
                                                           struct cyt_cell_env *cell_env);

/**
 * Run the program for multiple iterations.
 *
 * This runs the program until it either no longer makes progress or
 * the iteration bound was reached.
 *
 * An iteration bound of `0` means that there is no bound.
 */
void cyt_driver_runner_run(struct cyt_driver_runner *r,
                           const struct cyt_program *prog,
                           struct cyt_exec_state *exec_state,
                           struct cyt_cell_env *cell_env,
                           size_t iter_bound);

struct cyt_value_buffer *cyt_value_buffer_new(size_t size);

size_t cyt_value_buffer_get_size(const struct cyt_value_buffer *buf);

void cyt_value_buffer_set_bool(struct cyt_value_buffer *buf,
                               size_t idx,
                               bool b);

void cyt_value_buffer_set_int(struct cyt_value_buffer *buf,
                              size_t idx,
                              ptrdiff_t i);

/**
 * # Safety
 * `s` must be a valid pointer to a UTF-8 and NUL-terminated string.
 */
void cyt_value_buffer_set_string(struct cyt_value_buffer *buf,
                                 size_t idx,
                                 const char *s);

/**
 * # Safety
 * `fields` will be consumed, do **not** call the destructor on the value buffer
 */
void cyt_value_buffer_set_record(struct cyt_value_buffer *buf,
                                 size_t idx,
                                 struct cyt_value_buffer *fields);

void cyt_value_buffer_destroy(struct cyt_value_buffer *buf);

/**
 * Get the type of the value at index `idx`.
 *
 * If the index is out of bounds then `Integer` will be returned.
 */
enum cyt_value_type cyt_value_get_type(const struct cyt_value_buffer *buf,
                                       size_t idx);

/**
 * Get the boolean value in `buf` at `idx` by writing it in `out_b`.
 *
 * If the value is not a boolean then `false` is returned, `true` otherwise.
 */
bool cyt_value_buffer_get_bool(const struct cyt_value_buffer *buf,
                               size_t idx,
                               bool *out_b);

/**
 * Get the integer value in `buf` at `idx` by writing it in `out_i`.
 *
 * If the value is not an integer then `false` is returned, `true` otherwise.
 */
bool cyt_value_buffer_get_integer(const struct cyt_value_buffer *buf,
                                  size_t idx,
                                  ptrdiff_t *out_i);

/**
 * Get the string value in `buf` at `idx` by writing a pointer to `out_ptr`
 * and the length to `out_len`.
 *
 * The string is **NOT** NUL-terminated.
 *
 * If the value is not a string then `false` is returned, `true` otherwise.
 */
bool cyt_value_buffer_get_string(const struct cyt_value_buffer *buf,
                                 size_t idx,
                                 const char **out_ptr,
                                 size_t *out_len);

/**
 * Get the field value buffer of the record in `buf` at `idx`.
 *
 * The value buffer in `out_value` will be owned, so the `destroy` function
 * needs to be called.
 *
 * If the value at `idx` is not a record or if `idx` is out of bounds then
 * `false` is returned, `true` otherwise.
 */
bool cyt_value_buffer_get_record_fields(const struct cyt_value_buffer *buf,
                                        size_t idx,
                                        struct cyt_value_buffer **out_value);

struct cyt_cell_env *cyt_cellenv_new(void);

void cyt_cellenv_destroy(struct cyt_cell_env *cell_env);

/**
 * Add a record with id `record_id` to the environment `quantity` times.
 *
 * The ownership of `fields` will be transferred, so **do not** call the
 * destroy function on this value buffer.
 */
void cyt_cellenv_add_record(struct cyt_cell_env *cell_env,
                            size_t quantity,
                            struct cyt_record_id record_id,
                            struct cyt_value_buffer *fields);

size_t cyt_cellenv_count_records(const struct cyt_cell_env *cell_env,
                                 struct cyt_record_id record_id);

struct cyt_exec_state *cyt_exec_state_new(void);

void cyt_exec_state_destroy(struct cyt_exec_state *exec_state);

/**
 * # Safety
 * `s` must be a valid pointer to a UTF-8 and NUL-terminated string.
 * `f` must be a valid function pointer.
 */
void cyt_exec_state_set_extern_function(struct cyt_exec_state *exec_state,
                                        const char *name,
                                        void (*f)(void*, const struct cyt_value_buffer*),
                                        void *data);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
