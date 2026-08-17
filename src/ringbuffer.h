//
// Created by ahtat204 on 8/8/26.
//

/**
 * @file mredis_ringbuffer_h.h
 * @brief Thread-unsafe, fixed-size byte-buffer parsing implementation for MRedis.
 *
 * This header defines a raw pointer-arithmetic ring buffer designed for temporary 
 * byte stream queuing. It operates with zero garbage collection overhead by utilizing 
 * direct manual memory allocations.
 */

#ifndef MREDIS_RINGBUFFER_H
#define MREDIS_RINGBUFFER_H

#include <stdio.h>
#include <stdint.h>

/**
 * @name Buffer Configuration & Status Code Constants
 * @{
 */
/** @brief Maximum storage capacity allocated for the linear byte array underlying the buffer. */
#define RINGBUFFER_SIZE 1024

/** @brief Operation executed successfully without any structural errors. */
#define RB_SUCCESS 0        

/** @brief Allocation failure or invalid structural reference pointers encountered. */
#define RB_MEMORY_ERROR 1   

/** @brief Push operation aborted because the underlying memory capacity limit was hit. */
#define RB_OVERFLOW_ERROR 2 

/** @brief Pop operation aborted because read and write synchronization pointers collided at zero bytes. */
#define RB_EMPTY_ERROR 3
/** @} */

/**
 * @brief Defensive diagnostic utility macro for isolated standard error stream reporting.
 *
 * Encapsulates error reporting operations in a standard do-while control block to guarantee
 * syntactic isolation during compound macro expansions. Automatically updates global system 
 * error structures.
 * 
 * @param msg Constant literal string containing the target system diagnostic notification.
 */
#define LOG_ERROR(msg) \
do { \
fprintf(stderr, "[ERROR] %s\n", msg); \
sys_log_count++; \
} while(0)


typedef struct buffer
{
 char* buffer;
 char *read;
 char *write;
 size_t size;
}ringbuffer;

/**
 * @brief Allocates or zeros internal tracking structure members at early lifecycle bootstrap.
 *
 * Prepares the target instance tracking layouts by configuring internal structural 
 * read and write management references.
 *
 * @param[in,out] rb Opaque handle referencing the allocation target instance.
 * @return int Status validation integer matching predefined \c RB_ codes.
 */
int8_t init(ringbuffer* rb);

/**
 * @brief Extracts the oldest unparsed single byte sequence from the current reference position.
 *
 * Evaluates tracking pointer conditions and safely updates the interior state context
 * tracking locations using lightweight arithmetic evaluation.
 *
 * @param[in,out] rb Context validation pointer referencing the operational buffer wrapper.
 * @return char The literal ASCII/byte block parsed from the current operational track.
 */
char readData(ringbuffer* rb);

/**
 * @brief Commits a single parsing byte to the current tracking memory boundary.
 *
 * Modifies tracking pointers directly via precise offset changes while managing limits 
 * safely. Avoids expensive dynamic system allocations during standard execution paths.
 *
 * @param[in,out] b Context validation pointer referencing the operational buffer wrapper.
 * @param[in] character Target element to safely write to the memory track layer.
 * @return uint8_t Status validation token matching predefined \c RB_ configuration codes.
 */
uint8_t writeData(ringbuffer* b, const char character);
uint8_t freeBuffer(ringbuffer* b);
#endif //MREDIS_RINGBUFFER_H
