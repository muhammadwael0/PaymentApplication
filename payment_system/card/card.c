#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    char name[30] = "\0";
    EN_cardError_t cardError = CARD_OK; /* cardError tor return error state */
    size_t len = 0, iter = 0; /* length of string, iter to iterate through string */
    printf("%sEnter Holder Name: %s", BLUE, GREEN);
    fflush(stdin);
    fgets(name, sizeof(name), stdin);
    printf("%s", RESET);
    len = strlen(name);
    name[len - 1] = '\0';

    if(len >= 20 && len <= 24)
    {
        for (iter = 0; iter < len - 1; ++iter)
        {
            if ((name[iter] >= 'A' && name[iter] <= 'Z') || (name[iter] >= 'a' && name[iter] <= 'z') || name[iter] == ' ')
            {
                /* do nothing */
            }
            else
            {
                cardError = WRONG_NAME;
                break;
            }
        }
    }
    else
    {
        cardError = WRONG_NAME;
    }
    if (cardError == CARD_OK)
    {
        strcpy(cardData->cardHolderName, name);
    }
    return cardError;
}

EN_cardError_t getCardExpirationDate(ST_cardData_t *cardData)
{
    char expDate[10] = "\0";
    EN_cardError_t cardError = CARD_OK; /* cardError tor return error state */
    size_t len = 0; /* length of string */
    printf("%sEnter Expiration Date: %s", BLUE, GREEN);
    fflush(stdin);
    scanf("%s", expDate);
    printf("%s", RESET);
    len = strlen(expDate);
    if(len == 5)
    {
        bool cond = (expDate[0] >= '0' && expDate[0] <= '9'
                  && expDate[1] >= '0' && expDate[1] <= '9'
                  && expDate[2] == '/'
                  && expDate[3] >= '0' && expDate[3] <= '9'
                  && expDate[4] >= '0' && expDate[4] <= '9');
        if (cond)
        {
            /* do nothing */
        }
        else
        {
            cardError = WRONG_EXP_DATE;
        }
    }
    else
    {
        cardError = WRONG_EXP_DATE;
    }
    if (cardError == CARD_OK)
    {
        strcpy(cardData->cardExpirationDate, expDate);
    }
    return cardError;
}

EN_cardError_t getCardPan(ST_cardData_t *cardData)
{
    char pan[30] = "\0";
    EN_cardError_t cardError = CARD_OK; /* cardError tor return error state */
    size_t len = 0, iter = 0; /* length of string, iter to iterate through string */
    printf("%sEnter PAN: %s", BLUE, GREEN);
    fflush(stdin);
    scanf("%s", pan);
    printf("%s", RESET);
    len = strlen(pan);
    if(len >= 16 && len <= 19)
    {
        for (iter = 0; iter < len; ++iter)
        {
            if ((pan[iter] >= '0' && pan[iter] <= '9'))
            {
                /* do nothing */
            }
            else
            {
                cardError = WRONG_PAN;
                break;
            }
        }
    }
    else
    {
        cardError = WRONG_PAN;
    }
    if (cardError == CARD_OK)
    {
        strcpy(cardData->primaryAccountNumber, pan);
    }
    return cardError;
}