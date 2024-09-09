#include "file_handling.h"


EN_fileError_t write_data_to_cards(struct Node *List)
{
    EN_fileError_t fileError = FILE_OK;
    FILE *cards_DB = fopen(CARD_FILE_DB, "w");
    struct Node *tempNode = List;
    if (cards_DB == NULL || tempNode == NULL) {
        fileError = WRITING_FAILED;
    }
    else
    {
        fprintf(cards_DB, "Holder Name,PAN,EXP_DATE,Balance,State\n");
        while (tempNode != NULL)
        {
            fprintf(cards_DB, "%s,%s,%s,%.2f,%s\n", tempNode->NodeData.cardHolderName,
                    tempNode->NodeData.primaryAccountNumber, tempNode->NodeData.cardExpirationDate,
                    tempNode->NodeData.balance, tempNode->NodeData.state);
            tempNode = tempNode->NodeLink;
        }

    }
    fclose(cards_DB);
    cards_DB = NULL;
    return fileError;
}

EN_fileError_t read_data_from_cards(struct Node **List)
{
    EN_fileError_t fileError = FILE_OK;
    FILE *cards_DB = fopen(CARD_FILE_DB, "r");
    uint8 *line_buffer = NULL;
    struct accountData *accountData = NULL;
    if (cards_DB == NULL)
    {
        /* do nothing */
    }
    else
    {
        line_buffer = (uint8 *)calloc(150, sizeof(uint8));
        accountData = (struct accountData *) malloc(sizeof (struct accountData));
        if (line_buffer == NULL || accountData == NULL)
        {
            fileError = READING_FAILED;
        }
        else
        {
            fgets(line_buffer, 150, cards_DB);

            while(fgets(line_buffer, 150, cards_DB) != NULL)
            {
                sscanf(strtok(line_buffer, ","), "%[^,]s", accountData->cardHolderName);
                sscanf(strtok(NULL, ","), "%s", accountData->primaryAccountNumber);
                sscanf(strtok(NULL, ","), "%s", accountData->cardExpirationDate);
                sscanf(strtok(NULL, ","), "%f", &(accountData)->balance);
                sscanf(strtok(NULL, ""), "%s", accountData->state);
                push_back(List, *accountData);
            }
        }

    }
    fclose(cards_DB);
    free(accountData);
    free(line_buffer);
    cards_DB = NULL;
    accountData = NULL;
    line_buffer = NULL;
    return fileError;
}

EN_fileError_t write_data_to_transaction(Queue_t *queue)
{
    EN_fileError_t fileError = FILE_OK;
    FILE *transaction_DB = fopen(TRANSACTION_FILE_DB, "w");
    QueueStatus_t state = QUEUE_OK;

    if (transaction_DB == NULL || queue == NULL) {
        fileError = WRITING_FAILED;
    }
    else
    {
        fprintf(transaction_DB, "Transaction Sequence Number,Transaction Date,Transaction Amount,Transaction State,"
                                "Terminal Max Amount,Card Holder Name,PAN,EXP_DATE\n");
        while (state != QUEUE_EMPTY)
        {
            struct transactionData *queue_obj = DequeueElement(queue, &state);
            if (state == QUEUE_OK)
            {
                fprintf(transaction_DB, "%i,%s,%.2f,%s,%.2f,%s,%s,%s\n", queue_obj->transactionSequenceNumber,
                        queue_obj->transactionDate, queue_obj->transactionAmount, queue_obj->transactionState,
                        queue_obj->terminalMaxAmount, queue_obj->cardHolderName, queue_obj->PAN, queue_obj->EXP_DATE);
            }
            else
            {
                /* do nothing */
            }
        }
    }

    fclose(transaction_DB);
    transaction_DB = NULL;
    return fileError;
}

EN_fileError_t read_data_from_transaction(Queue_t *queue)
{
    EN_fileError_t fileError = FILE_OK;
    FILE *transaction_DB = fopen(TRANSACTION_FILE_DB, "r");
    uint8 *line_buffer = NULL;
    struct transactionData transactionData;
    if (transaction_DB == NULL)
    {
        /* do nothing */
    }
    else
    {
        line_buffer = (uint8 *)calloc(150, sizeof(uint8));
        if (line_buffer == NULL || queue == NULL)
        {
            fileError = READING_FAILED;
        }
        else
        {
            fgets(line_buffer, 150, transaction_DB);

            while(fgets(line_buffer, 150, transaction_DB) != NULL)
            {
                sscanf(strtok(line_buffer, ","), "%i", &transactionData.transactionSequenceNumber);
                sscanf(strtok(NULL, ","), "%s", transactionData.transactionDate);
                sscanf(strtok(NULL, ","), "%f", &transactionData.transactionAmount);
                sscanf(strtok(NULL, ","), "%s", transactionData.transactionState);
                sscanf(strtok(NULL, ","), "%f", &transactionData.terminalMaxAmount);
                sscanf(strtok(NULL, ","), "%[^,]s", transactionData.cardHolderName);
                sscanf(strtok(NULL, ","), "%s", transactionData.PAN);
                sscanf(strtok(NULL, ""), "%s", transactionData.EXP_DATE);
                QueueStatus_t state = EnqueueElement(queue, &transactionData);
                if (state == QUEUE_OK)
                {
                    /* do nothing */
                }
                else
                {
                    fileError = READING_FAILED;
                    break;
                }
            }
        }

    }
    fclose(transaction_DB);
    free(line_buffer);
    transaction_DB = NULL;
    line_buffer = NULL;
    return fileError;
}