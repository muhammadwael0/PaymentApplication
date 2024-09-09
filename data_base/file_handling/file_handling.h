#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <stdlib.h>
#include <string.h>
#include "../../data_structure/list/list.h"
#include "../../data_structure/queue/queue.h"
#include "../../libs/std_types.h"


#define CARD_FILE_DB "../data_base/data/cards.csv"
#define TRANSACTION_FILE_DB "../data_base/data/transactions.csv"


typedef enum EN_fileError_t {
    FILE_OK, READING_FAILED, WRITING_FAILED
} EN_fileError_t;


EN_fileError_t write_data_to_cards(struct Node *List);

EN_fileError_t read_data_from_cards(struct Node **List);

EN_fileError_t write_data_to_transaction(Queue_t *queue);

EN_fileError_t read_data_from_transaction(Queue_t *queue);

#endif
