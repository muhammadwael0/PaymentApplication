#include "queue.h"

static bool QueueIsFull(Queue_t *queue_obj){
    return (queue_obj->ElementCount == queue_obj->QueueMaxSize ? true : false);
}

static bool QueueIsEmpty(Queue_t *queue_obj){
    return (queue_obj->ElementCount == 0 ? true : false);
}

Queue_t *CreateQueue(uint32 maxSize, QueueStatus_t *ret_status){
    Queue_t *queue;
    /* Create queue object in the heap to hold the queue information */
    queue = (Queue_t *)malloc(sizeof(Queue_t));
    if(queue == NULL){
        *ret_status = QUEUE_NULL_POINTER;
    }
    else{
        queue->QueueArray = (struct transactionData *)calloc(maxSize, sizeof(void *));
        if(queue->QueueArray == NULL){
            *ret_status = QUEUE_NOK;
            queue = NULL;
        }
        else{
            queue->ElementCount = 0;
            queue->QueueFront = -1;
            queue->QueueRear = -1;
            queue->QueueMaxSize = maxSize;
            *ret_status = QUEUE_OK;
        }
    }
    return queue;
}

QueueStatus_t EnqueueElement(Queue_t *queue_obj, struct transactionData *item_ptr){
    QueueStatus_t status = QUEUE_NOK;
    if((queue_obj == NULL) || (item_ptr == NULL)){
        status = QUEUE_NULL_POINTER;
    }
    else{
        if(QueueIsFull(queue_obj)){
            status = QUEUE_FULL;
        }
        else{
            /* Increment Queue Rear Index */
            (queue_obj->QueueRear)++;
            if(queue_obj->QueueRear == queue_obj->QueueMaxSize){
                queue_obj->QueueRear = 0;
            }
            else{ /*Nothing */ }
            /* Insert the input data in to the rear position */
            queue_obj->QueueArray[queue_obj->QueueRear] = *item_ptr;
            /* validate if the queue was empty, (front and rear points to the first element) */
            if(queue_obj->ElementCount == 0){
                queue_obj->QueueFront = 0;
                queue_obj->ElementCount = 1;
            }
            else{
                (queue_obj->ElementCount)++; /* New element has been added to the Queue */
            }
            status = QUEUE_OK;
        }
    }
    return status;
}

struct transactionData *DequeueElement(Queue_t *queue_obj, QueueStatus_t *ret_status){
    struct transactionData *returnElement = NULL;
    if((queue_obj == NULL) || (ret_status == NULL))
    {
        /* do nothing */
    }
    else
    {
        if(QueueIsEmpty(queue_obj))
        {
            *ret_status = QUEUE_EMPTY;
            returnElement = NULL;
        }
        else
        {
            returnElement = &queue_obj->QueueArray[queue_obj->QueueFront];
            /* Increment Queue Front Index */
            (queue_obj->QueueFront)++;
            if(queue_obj->QueueFront == queue_obj->QueueMaxSize){
                queue_obj->QueueFront = 0;
            }
            else{
                /* Nothing */
            }
            /* Check if the element is the last element in the Queue */
            if(queue_obj->ElementCount == 1){
                queue_obj->QueueFront = -1; /* Queue is empty */
                queue_obj->QueueRear = -1;  /* Queue is empty */
            }
            else{
                /* Nothing */
            }
            (queue_obj->ElementCount)--; /* Element has been deleted from the Queue */
            *ret_status = QUEUE_OK;
        }
    }
    return returnElement;
}

struct transactionData *QueueFront(Queue_t *queue_obj, QueueStatus_t *ret_status){
    struct transactionData *returnElement = NULL;
    if((queue_obj == NULL) || (ret_status == NULL))
    {
        /* do nothing */
    }
    else
    {
        if(QueueIsEmpty(queue_obj))
        {
            *ret_status = QUEUE_EMPTY;
            returnElement = NULL;
        }
        else
        {
            returnElement = &queue_obj->QueueArray[queue_obj->QueueFront];
            *ret_status = QUEUE_OK;
        }
    }
    return returnElement;
}

struct transactionData *QueueRear(Queue_t *queue_obj, QueueStatus_t *ret_status){
    struct transactionData *returnElement = NULL;
    if((queue_obj == NULL) || (ret_status == NULL))
    {
        /* do nothing */
    }
    else
    {
        if(QueueIsEmpty(queue_obj))
        {
            *ret_status = QUEUE_EMPTY;
            returnElement = NULL;
        }
        else
        {
            returnElement = &queue_obj->QueueArray[queue_obj->QueueRear];
            *ret_status = QUEUE_OK;
        }
    }
    return returnElement;
}

QueueStatus_t GetQueueCount(Queue_t *queue_obj, uint32 *QueueCount){
    QueueStatus_t status = QUEUE_NOK;
    if((queue_obj == NULL) || (QueueCount == NULL)){
        status = QUEUE_NULL_POINTER;
    }
    else{
        if(QueueIsEmpty(queue_obj)){
            *QueueCount = 0;
        }
        else{
            *QueueCount = queue_obj->ElementCount;
        }
        status = QUEUE_OK;
    }
    return status;
}

QueueStatus_t DestroyQueue(Queue_t *queue_obj){
    QueueStatus_t status = QUEUE_NOK;
    if(queue_obj == NULL){
        status = QUEUE_NULL_POINTER;
    }
    else{
        free(queue_obj->QueueArray);
        free(queue_obj);
        status = QUEUE_OK;
    }
    return status;
}