#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <string.h>
#include "../../libs/std_types.h"


typedef struct ST_cardData_t
{
    uint8 cardHolderName[25];
    uint8 primaryAccountNumber[20];
    uint8 cardExpirationDate[6];
} ST_cardData_t;

typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
} EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t *cardData);

EN_cardError_t getCardExpirationDate(ST_cardData_t *cardData);

EN_cardError_t getCardPan(ST_cardData_t *cardData);


#endif