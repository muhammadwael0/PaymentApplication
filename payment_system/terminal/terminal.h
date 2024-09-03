#ifndef TERMINAL_H
#define TERMINAL_H


#include <time.h>
#include "../../libs/std_types.h"
#include "../card/card.h"


typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8 transactionDate[11];
} ST_terminalData_t;

typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT,
    EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
} EN_terminalError_t;


EN_terminalError_t getTransactionDate(ST_terminalData_t *terminalData);

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *terminalData);

EN_terminalError_t getTransactionAmount(ST_terminalData_t *terminalData);

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *terminalData);

EN_terminalError_t setMaxAmount(ST_terminalData_t *terminalData, float maxAmount);

EN_terminalError_t isValidCardPan(ST_cardData_t *cardData);


#endif