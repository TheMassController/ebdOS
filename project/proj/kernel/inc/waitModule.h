/**
 * @brief A module that unifies a wait-like subsystem
 * @author Jacko Dirks
 *
 * There are many situations in which you want to wait for x time or event y and stop waiting if one of both happens.
 * This module handles the waiting part of this equation. It manages a system timer which works in the same way as the sleep timer.
 * If a process is added, it is added in combination with a remove function, this function is guaranteed to be called by this function if the timer runs out.
 * This is the only action taken on timer run out, the callee is responsible for re-adding the process to the scheduler if that is what it wants.
 * There is also a way to remove a process from this subsystem.
 *
 * This module never touches the state of the process.
 *
 * This module manages its own timer, the waitTimer. Its inner workings are very alike to the sleep timer.
 * In fact, this module might partially replace the sleep timer in the future.
 */

#include "process.h"
#include "core/inc/sleep.h"

/**
 * @brief Adds a process to the wait queue
 * @param remove The function that is called with the given process as param whenvever its timer expires
 * @param proc The process that needs to wait
 * @param sleepReq The sleep request struct
 * @return 0 if everything went ok
 *  ETIMEDOUT if the timer had already ran out
 */
int addWaiter(void(*remove)(struct Process*), struct Process* proc, const struct SleepRequest* sleepReq);

/**
 * @brief Removes a waiter from this module
 *
 * The earlier passed `remove` function is NOT called when this function is called.
 *
 * @param proc The process you want to remove
 * @return 0 if everything was ok
 *  EINVAL if the requested process was not found
 * @warning If EINVAL is returned, the kernel might already be done for.
 */
int removeWaiter(struct Process* proc);

/**
 * @brief Should be called whenever the Managed Lock timer finishes
 */
struct Process* waitTimerTimeout(void);

/**
 *@brief Should be called whenever the system timer overflows
 */
struct Process* waitTimerSysTimerOverflow(void);
