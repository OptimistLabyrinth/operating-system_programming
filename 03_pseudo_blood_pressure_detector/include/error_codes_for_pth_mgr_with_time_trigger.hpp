#ifndef ERROR_CODES_FOR_PTH_MNG_WITH_TT__84a7df5f_0741_4eba_b0b1_6b85171246c8__HPP___
#define ERROR_CODES_FOR_PTH_MNG_WITH_TT__84a7df5f_0741_4eba_b0b1_6b85171246c8__HPP___

// error codes in "uint initialize_variables(void)""
#define ON_INTIIALIZE_VARIABLES_SUCCESS             10000
#define ERROR_IN_PTHREAD_MUTEX_INIT                 10001
#define ERROR_IN_PTHREAD_COND_INIT                  10002

// error codes in "void execution(void)"
#define ON_EXECUTION_SUCCESS                        20000
#define ERROR_IN_CREATE_POSIX_TIMER                 20001
#define ERROR_IN_PTHREAD_CREATE                     20002

// error codes in "uint create_posix_timer(void*)"
#define ON_CREATE_POSIX_TIMER_SUCCESS               30000
#define ERROR_IN_TIMER_CREATE                       30001
#define ERROR_IN_TIMER_SETTIME                      30002
#define ERROR_IN_SWITCH_CASE                        30003

// error codes in "void* thread_to_be_managed(void*)"
#define ERROR_IN_TT_THREAD_REGISTER                 40001
#define ERROR_IN_TT_THREAD_WAIT_INVOCATION          40002

// error codes in "uint tt_thread_register(period_t, pthread_t)"
#define ON_TT_THREAD_REGISTER_SUCCESS               50000
#define ERROR_IN_PTHREAD_MUTEX_LOCK_REGISTER        50001
#define ERROR_IN_PTHREAD_MUTEX_UNLOCK_REGISTER      50003

// error codes in "uint tt_thread_wait_invocation(pthread_t)"
#define ON_TT_THREAD_WAIT_INVOCATION_SUCCESS        60000
#define ERROR_IN_PTHREAD_MUTEX_LOCK_WAIT_INVOKE     60001
#define ERROR_IN_PTHREAD_COND_WAIT_WAIT_INVOKE      60002
#define ERROR_IN_PTHREAD_MUTEX_UNLOCK_WAIT_INVOKE   60001

// error codes in "void periodic_handler(sigval_t)"
#define ERROR_IN_PTHREAD_MUTEX_LOCK_PER_HNDL        70001
#define ERROR_IN_PTHREAD_COND_SIGNAL_PER_HNDL       70002
#define ERROR_IN_PTHREAD_MUTEX_UNLOCK_PER_HNDL      70003



#endif /* ERROR_CODES_FOR_PTH_MNG_WITH_TT__84a7df5f_0741_4eba_b0b1_6b85171246c8__HPP___ */