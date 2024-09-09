#include "app.h"

int main()
{
    uint16 choose = 0;
    EN_transaction_t transactionState;
    EN_cardError_t cardState;
    EN_terminalError_t terminalState;
    ST_transaction_t transactionData;
    Program:
        system("clear");
        system("sleep 1");
        printf("%s▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄%s\n", YELLOW, RESET);
        printf("%s▄▄%s ▗▄▄▖  ▗▄▖▗▖  ▗▖▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖ %s  ▗▄▄▖▗▖  ▗▖▗▄▄▖▗▄▄▄▖▗▄▄▄▖▗▖  ▗▖ %s▄▄%s\n", YELLOW, RED, BLUE, YELLOW, RESET);
        printf("%s▄▄%s ▐▌ ▐▌▐▌ ▐▌▝▚▞▘ ▐▛▚▞▜▌▐▌   ▐▛▚▖▐▌  █   %s ▐▌    ▝▚▞▘▐▌     █  ▐▌   ▐▛▚▞▜▌ %s▄▄%s\n", YELLOW, RED, BLUE, YELLOW, RESET);
        printf("%s▄▄%s ▐▛▀▘ ▐▛▀▜▌ ▐▌  ▐▌  ▐▌▐▛▀▀▘▐▌ ▝▜▌  █   %s  ▝▀▚▖  ▐▌  ▝▀▚▖  █  ▐▛▀▀▘▐▌  ▐▌ %s▄▄%s\n", YELLOW, RED, BLUE, YELLOW, RESET);
        printf("%s▄▄%s ▐▌   ▐▌ ▐▌ ▐▌  ▐▌  ▐▌▐▙▄▄▖▐▌  ▐▌  █   %s ▗▄▄▞▘  ▐▌ ▗▄▄▞▘  █  ▐▙▄▄▖▐▌  ▐▌ %s▄▄%s\n", YELLOW, RED, BLUE, YELLOW, RESET);
        printf("%s▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄%s\n\n", YELLOW, RESET);

        while (1)
        {
            cardState = getCardHolderName(&transactionData.cardHolderData) ||
                        getCardPan(&transactionData.cardHolderData) ||
                        getCardExpirationDate(&transactionData.cardHolderData);
            if (cardState != CARD_OK)
            {
                printf("%s[%s!%s]%sError: %sEnter Valid Card Holder Data%s\n", BLUE, YELLOW, BLUE, RED, YELLOW, RESET);
                break;
            }
            else
            {
                /* do nothing */
            }
            terminalState = isValidCardPan(&transactionData.cardHolderData);
            if (terminalState != TERMINAL_OK)
            {
                printf("%s[%s!%s]%sError: %sEnter Valid Card PAN%s\n", BLUE, YELLOW, BLUE, RED, YELLOW, RESET);
                break;
            }
            else
            {
                /* do nothing */
            }
            terminalState = getTransactionDate(&transactionData.terminalData);
            if (terminalState != TERMINAL_OK)
            {
                printf("%s[%s!%s]%sError: %sCan't Get Date From Server%s\n", BLUE, YELLOW, BLUE, RED, YELLOW, RESET);
                break;
            }
            else
            {
                /* do nothing */
            }
            setMaxAmount(&transactionData.terminalData, MAX_AMOUNT);
            terminalState = getTransactionDate(&transactionData.terminalData);
            if (terminalState == INVALID_CARD)
            {
                printf("%s[%s!%s]%sError: %sInvalid Card PAN%s\n", BLUE, YELLOW, BLUE, RED, YELLOW, RESET);
                break;
            }
            else
            {
                /* do nothing */
            }
            terminalState = isCardExpired(&transactionData.cardHolderData, &transactionData.terminalData);
            if (terminalState == EXPIRED_CARD)
            {
                printf("%s[%s!%s]%sError: %sExpired Card%s\n", BLUE, YELLOW, BLUE, RED, YELLOW, RESET);
                break;
            }
            else
            {
                /* do nothing */
            }
            getTransactionAmount(&transactionData.terminalData);
            terminalState = isBelowMaxAmount(&transactionData.terminalData);
            if (terminalState == EXCEED_MAX_AMOUNT)
            {
                printf("%s[%s!%s]%sError: %sInvalid Amount Exceeding Limit, Max Amount = %.2f $%s\n",
                       BLUE, YELLOW, BLUE, RED, YELLOW, MAX_AMOUNT, RESET);
                break;
            }
            else
            {
                /* do nothing */
            }
            transactionState = receiveTransactionData(&transactionData);
            if (transactionState == FRAUD_CARD)
            {
                printf("%s[%s!%s]%sDeclined: %sCard Not Found%s\n", BLUE, YELLOW, BLUE, RED, YELLOW, RESET);
            }
            else if (transactionState == DECLINED_INSUFFICIENT_FUND)
            {
                printf("%s[%s!%s]%sDeclined: %sNot Enough Fund%s\n", BLUE, YELLOW, BLUE, RED, YELLOW, RESET);
            }
            else if (transactionState == DECLINED_STOLEN_CARD)
            {
                printf("%s[%s!%s]%sDeclined: %sBlocked Account%s\n", BLUE, YELLOW, BLUE, RED, YELLOW, RESET);
            }
            else if (transactionState == INTERNAL_SERVER_ERROR)
            {
                printf("%s[%s!%s]%sError: %sCan't Save Transaction%s\n", BLUE, YELLOW, BLUE, RED, YELLOW, RESET);
            }
            else
            {
                /* do nothing */
            }
            printf("\n");
            system("sleep 1.4");
            listSavedTransaction();
            break;
        }
        printf("\n%sDo you want another operation (yes 1/no 0): %s", BLUE, RESET);
        fflush(stdin);
        scanf("%hi", &choose);
        if (choose)
        {
            goto Program;
        }
        else
        {
            /* do nothing */
        }
}



