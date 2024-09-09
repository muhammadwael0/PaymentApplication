#ifndef SERVER_H
#define SERVER_H


#include "../../libs/std_types.h"
#include "../card/card.h"
#include "../terminal/terminal.h"
#include "../../data_base/file_handling/file_handling.h"
#include "../../data_structure/list/list.h"
#include "../../data_structure/queue/queue.h"


typedef enum EN_transaction_t {
    APPROVED, DECLINED_INSUFFICIENT_FUND, DECLINED_STOLEN_CARD,
    FRAUD_CARD, INTERNAL_SERVER_ERROR
} EN_transaction_t;

typedef struct ST_transaction_t {
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transaction_t transState;
    uint32 transactionSequenceNumber;
} ST_transaction_t;

typedef enum EN_serverError_t {
    SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND,
    LOW_BALANCE, BLOCKED_ACCOUNT
} EN_serverError_t;

typedef enum EN_accountState_t {
    RUNNING,
    BLOCKED
} EN_accountState_t;

typedef struct ST_accountsDB_t {
    float balance;
    EN_accountState_t state;
    uint8 primaryAccountNumber[20];
} ST_accountsDB_t;


EN_transaction_t receiveTransactionData(ST_transaction_t *transactionData);

EN_serverError_t isValidAccount(ST_cardData_t *cardData, struct accountData *accountRef);

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference);

EN_serverError_t isAmountAvailable(ST_terminalData_t *terminalData, ST_accountsDB_t *accountReference);

EN_serverError_t saveTransaction(ST_transaction_t *transactionData);

void listSavedTransaction(void);


#endif