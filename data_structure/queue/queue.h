#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include "../../libs/std_types.h"

struct transactionData
{
    uint32 transactionSequenceNumber;
    uint8 transactionDate[11];
    float transactionAmount;
    uint8 transactionState[8];
    float terminalMaxAmount;
    uint8 cardHolderName[25];
    uint8 PAN[20];
    uint8 EXP_DATE[6];
};

typedef struct{
    struct transactionData *QueueArray;
    uint32 QueueMaxSize; /* Maximum elements in the Queue */
    sint32 ElementCount; /* Number of elements in the Queue */
    sint32 QueueFront;   /* Index of the front elements */
    sint32 QueueRear;    /* Index of the rear elements */
} Queue_t;

typedef enum{
    QUEUE_NOK = 0,     /* Queue operation not performed successfully */
    QUEUE_OK,          /* Queue operation performed successfully  */
    QUEUE_FULL,        /* Queue is full */
    QUEUE_EMPTY,       /* Queue is empty */
    QUEUE_NULL_POINTER /* NULL pointer passed to the Queue */
} QueueStatus_t;


Queue_t *CreateQueue(uint32 maxSize, QueueStatus_t *ret_status);

QueueStatus_t EnqueueElement(Queue_t *queue_obj, struct transactionData *item_ptr);

struct transactionData *DequeueElement(Queue_t *queue_obj, QueueStatus_t *ret_status);

struct transactionData *QueueFront(Queue_t *queue_obj, QueueStatus_t *ret_status);

struct transactionData *QueueRear(Queue_t *queue_obj, QueueStatus_t *ret_status);

QueueStatus_t GetQueueCount(Queue_t *queue_obj, uint32 *QueueCount);

QueueStatus_t DestroyQueue(Queue_t *queue_obj);


#endif