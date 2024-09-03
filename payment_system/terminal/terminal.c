#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *terminalData)
{
    EN_terminalError_t terminalError = TERMINAL_OK;
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    if (tm == NULL)
    {
        terminalError = WRONG_DATE;
    }
    else
    {
        /* do nothing */
    }
    sprintf(terminalData->transactionDate, "%02i/%02i/%i", (*tm).tm_mday, (*tm).tm_mon + 1, (*tm).tm_year + 1900);
    return terminalError;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *terminalData)
{
    EN_terminalError_t terminalError = TERMINAL_OK;
    uint8 monthCardDate = ((cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0'));
    uint8 monthTerminalDate = ((terminalData->transactionDate[3] - '0') * 10 + (terminalData->transactionDate[4] - '0'));
    uint8 yearCardDate = ((cardData->cardExpirationDate[3] - '0') * 10 + (cardData->cardExpirationDate[4] - '0'));
    uint8 yearTerminalDate = ((terminalData->transactionDate[8] - '0') * 10 + (terminalData->transactionDate[9] - '0'));
    if ((yearTerminalDate > yearCardDate) || (yearTerminalDate == yearCardDate && monthTerminalDate >= monthCardDate))
    {
        terminalError = EXPIRED_CARD;
    }
    else
    {
        /* do nothing */
    }
    return terminalError;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *terminalData)
{
    EN_terminalError_t terminalError = TERMINAL_OK;
    printf("Enter Transaction Amount: ");
    scanf("%f", &terminalData->transAmount);
    if (terminalData->transAmount <= 0)
    {
        terminalData->transAmount = 0;
        terminalError = INVALID_AMOUNT;
    }
    else
    {
        /* do nothing */
    }
    return terminalError;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *terminalData)
{
    EN_terminalError_t terminalError = TERMINAL_OK;
    if (terminalData->transAmount <= terminalData->maxTransAmount)
    {
        /* do nothing */
    }
    else
    {
        terminalError = EXCEED_MAX_AMOUNT;
    }
    return terminalError;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *terminalData, float maxAmount)
{
    EN_terminalError_t terminalError = TERMINAL_OK;
    if (maxAmount <= 0)
    {
        terminalError = INVALID_MAX_AMOUNT;
    }
    else
    {
        terminalData->maxTransAmount = maxAmount;
    }
    return terminalError;
}

EN_terminalError_t isValidCardPan(ST_cardData_t *cardData)
{
    EN_terminalError_t terminalError = TERMINAL_OK;

    uint8 digit_count = 0, iter = 0;
    int checkSum = 0;

    for (iter = 19; iter >= 0; --iter) {
        uint8 digit = cardData->primaryAccountNumber[iter] - '0';
        digit_count++;
        if (digit_count % 2 == 0)
        {
            digit *= 2;
            if (digit > 9)
            {
                digit -= 9;
            }
        }
        checkSum += digit;

    }
    if (checkSum % 10 == 0)
    {
        /* do nothing */
    }
    else
    {
        terminalError = INVALID_CARD;
    }
    return terminalError;
}