#include "server.h"

static struct Node *list = NULL;

EN_transaction_t receiveTransactionData(ST_transaction_t *transactionData)
{
    EN_transaction_t transactionError = APPROVED;
    EN_serverError_t serverError = SERVER_OK;
    struct accountData accountData;
    read_data_from_cards(&list);
    serverError = isValidAccount(&transactionData->cardHolderData, &accountData);
    if (serverError == SERVER_OK)
    {
        ST_accountsDB_t accountsDb;
        accountsDb.balance = accountData.balance;
        accountsDb.state = (!strcmp(accountData.state, "RUNNING") ? RUNNING : BLOCKED);
        strcpy(accountsDb.primaryAccountNumber, accountData.primaryAccountNumber);
        serverError = isBlockedAccount(&accountsDb);
        if (serverError == SERVER_OK)
        {
            serverError = isAmountAvailable(&transactionData->terminalData, &accountsDb);
            if (serverError == SERVER_OK)
            {
                accountData.balance -= transactionData->terminalData.transAmount;
                update_node(list, &accountData);
                write_data_to_cards(list);
            }
            else
            {
                transactionError = DECLINED_INSUFFICIENT_FUND;
            }
        }
        else
        {
            transactionError = DECLINED_STOLEN_CARD;
        }
    }
    else
    {
        transactionError = FRAUD_CARD;
    }
    transactionData->transState = transactionError;
    serverError = saveTransaction(transactionData);
    if (serverError != SERVER_OK)
    {
        transactionError = INTERNAL_SERVER_ERROR;
    }
    else
    {
        /* do nothing */
    }
    destroy_List(list);
    list = NULL;
    return transactionError;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, struct accountData *accountRef)
{
    EN_serverError_t serverError = SERVER_OK;
    bool found = false;
    struct Node *tempNode = list;
    if (list == NULL || cardData == NULL || accountRef == NULL)
    {
        serverError = ACCOUNT_NOT_FOUND;
    }
    else
    {
        while (tempNode != NULL)
        {

            if (!strcmp(cardData->primaryAccountNumber, tempNode->NodeData.primaryAccountNumber))
            {
                found = true;
                *accountRef = tempNode->NodeData;
                break;
            }
            else
            {
                tempNode = tempNode->NodeLink;
            }

        }
    }
    if (found == true)
    {
        /* do nothing */
    }
    else
    {
        serverError = ACCOUNT_NOT_FOUND;
    }
    return serverError;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference)
{
    EN_serverError_t serverError = SERVER_OK;
    if (accountReference != NULL)
    {
        if (accountReference->state == RUNNING)
        {
            /* do nothing */
        }
        else if (accountReference->state == BLOCKED)
        {
            serverError = BLOCKED_ACCOUNT;
        }
    }
    else
    {
        /* do nothing */
    }
    return serverError;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *terminalData, ST_accountsDB_t *accountReference)
{
    EN_serverError_t serverError = SERVER_OK;
    if (accountReference == NULL || terminalData == NULL)
    {
        /* do nothing */
    }
    else
    {
        if (terminalData->transAmount <= accountReference->balance)
        {
            /* do nothing */
        }
        else
        {
             serverError = LOW_BALANCE;
        }
    }
    return serverError;
}

EN_serverError_t saveTransaction(ST_transaction_t *transactionData)
{
    EN_serverError_t serverError = SERVER_OK;
    QueueStatus_t status = QUEUE_NOK;
    struct transactionData queue_obj, *ptr = NULL;
    EN_fileError_t fileError = FILE_OK;

    strcpy(queue_obj.transactionDate, transactionData->terminalData.transactionDate);
    queue_obj.transactionAmount = transactionData->terminalData.transAmount;
    if (transactionData->transState == APPROVED)
    {
        strcpy(queue_obj.transactionState, "Approved");
    }
    else
    {
        strcpy(queue_obj.transactionState, "Declined");
    }
    queue_obj.terminalMaxAmount = transactionData->terminalData.maxTransAmount;
    strcpy(queue_obj.cardHolderName, transactionData->cardHolderData.cardHolderName);
    strcpy(queue_obj.PAN, transactionData->cardHolderData.primaryAccountNumber);
    strcpy(queue_obj.EXP_DATE, transactionData->cardHolderData.cardExpirationDate);

    Queue_t *queue = CreateQueue(10000, &status);
    if (status == QUEUE_OK)
    {
        fileError = read_data_from_transaction(queue);
        if (fileError == FILE_OK)
        {
            ptr = QueueRear(queue, &status);
            if (ptr != NULL)
            {
                queue_obj.transactionSequenceNumber = ptr->transactionSequenceNumber + 1;
            }
            else
            {
                queue_obj.transactionSequenceNumber = 100000;
            }
            status = EnqueueElement(queue, &queue_obj);
            if (status == QUEUE_OK)
            {
                fileError = write_data_to_transaction(queue);
            }
            else
            {
                serverError = SAVING_FAILED;
            }
        }
        else
        {
            serverError = SAVING_FAILED;
        }
    }
    else
    {
        serverError = SAVING_FAILED;
    }
    if (fileError != FILE_OK)
    {
        serverError = SAVING_FAILED;
    }
    else
    {
        /* do nothing */
    }
    status = DestroyQueue(queue);
    queue = NULL;
    return serverError;
}

void listSavedTransaction(void)
{
    Queue_t *queue = NULL;
    EN_fileError_t fileError = FILE_OK;
    QueueStatus_t status = QUEUE_NOK;
    struct transactionData *transactionData;

    queue = CreateQueue(10000, &status);
    if (status == QUEUE_OK)
    {
        fileError = read_data_from_transaction(queue);
        if (fileError == FILE_OK)
        {
            while (status == QUEUE_OK)
            {
                transactionData = DequeueElement(queue, &status);
                if (status == QUEUE_OK && transactionData != NULL)
                {
                    printf("%s#############################################################%s\n", YELLOW, RESET);
                    printf("%sTransaction Sequence Number: %s%i%s\n", BLUE, GREEN, transactionData->transactionSequenceNumber, RESET);
                    printf("%sTransaction Date: %s%s%s\n", BLUE, GREEN, transactionData->transactionDate, RESET);
                    printf("%sTransaction Amount: %s%.2f $%s\n", BLUE, GREEN, transactionData->transactionAmount, RESET);
                    printf("%sTransaction State: %s%s%s\n", BLUE, GREEN, transactionData->transactionState, RESET);
                    printf("%sTerminal Max Amount: %s%.2f $%s\n", BLUE, GREEN, transactionData->terminalMaxAmount, RESET);
                    printf("%sCard Holder Name: %s%s%s\n", BLUE, GREEN, transactionData->cardHolderName, RESET);
                    printf("%sPAN: %s%s%s\n", BLUE, GREEN, transactionData->PAN, RESET);
                    printf("%sCard Expiration Date: %s%s%s\n", BLUE, GREEN, transactionData->EXP_DATE, RESET);
                    printf("%s#############################################################%s\n", YELLOW, RESET);
                }
                else
                {
                    /* do nothing */
                }
            }

        }
        else
        {
            /* do nothing */
        }

    }
    else
    {
        /* do nothing */
    }
    status = DestroyQueue(queue);
    queue = NULL;
}