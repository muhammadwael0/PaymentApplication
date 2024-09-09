#include "list.h"


//void find_node(struct Node *List, uint8 *cardPan, struct accountData *accountData)
//{
//    struct Node *TempNode = List;
//    if (TempNode == NULL || accountData == NULL || cardPan == NULL)
//    {
//        return;
//    }
//    else
//    {
//        while (TempNode != NULL)
//        {
//            if (!strcmp(TempNode->NodeData.primaryAccountNumber, cardPan))
//            {
//                *accountData = TempNode->NodeData;
//                break;
//            }
//            TempNode = TempNode->NodeLink;
//        }
//    }
//}
//
void update_node(struct Node *List, struct accountData *accountData)
{
    struct Node *TempNode = List;
    if (TempNode == NULL || accountData == NULL)
    {
        return;
    }
    else
    {
        while (TempNode != NULL)
        {
            if (!strcmp(TempNode->NodeData.primaryAccountNumber, accountData->primaryAccountNumber))
            {
                TempNode->NodeData.balance = accountData->balance;
                break;
            }
            TempNode = TempNode->NodeLink;
        }
    }
}

void push_front(struct Node **List, struct accountData accountData){
    struct Node *TempNode = NULL;

    TempNode = (struct Node *)malloc(sizeof(struct Node));
    if(NULL != TempNode){
        TempNode->NodeData = accountData;
        /* Check if linked list is empty */
        if(NULL == *List){ /* Linked list is empty */
            TempNode->NodeLink = NULL;
            *List = TempNode;
        }
        else{ /* Linked list is not empty */
            TempNode->NodeLink = *List;
            *List = TempNode;
        }
    }
    else{
        /* Nothing */
    }
}

void push_back(struct Node **List, struct accountData accountData){
    struct Node *TempNode = NULL;
    struct Node *LastNode = NULL;

    TempNode = (struct Node *)malloc(sizeof(struct Node));
    if(TempNode != NULL){
        TempNode->NodeData = accountData;
        TempNode->NodeLink = NULL;

        /* Check if linked list is empty */
        if(*List == NULL){ /* Linked list is empty */
            *List = TempNode;
        }
        else{ /* Linked list is not empty */
            LastNode = *List;
            while(LastNode->NodeLink != NULL){
                LastNode = LastNode->NodeLink;
            }
            LastNode->NodeLink = TempNode;
        }
    }
    else{
        /* Nothing */
    }
}

//void insert_after(struct Node *List){
//    struct Node *TempNode = NULL;
//    struct Node *NodeListCounter = NULL;
//    uint32 NodePosition = 0;    /*  */
//    uint32 ListLength = 0;      /*  */
//    uint32 NodeCounter = 1;     /* Points to the first node */
//
//    printf("Enter Node Position (First node is position = 1): ");
//    scanf("%i", &NodePosition);
//
//    ListLength = length(List);
//    if(NodePosition > ListLength){
//        printf("Invalid Node Position -> List has ( %i ) Nodes \n", ListLength);
//    }
//    else{
//        NodeListCounter = List;
//        while(NodeCounter < NodePosition){
//            NodeCounter++;
//            NodeListCounter = NodeListCounter->NodeLink;
//        } /* TempNode points to the node where we have to insert after it */
//        TempNode = (struct Node *)malloc(sizeof(struct Node));
//        if(NULL != TempNode){
//            printf("Enter Node Data : ");
//            scanf("%i", &TempNode->NodeData);
//            /* Connect the right side connection */
//            TempNode->NodeLink = NodeListCounter->NodeLink;
//            /* Connect the Left side connection */
//            NodeListCounter->NodeLink = TempNode;
//        }
//        else{
//            /* Nothing */
//        }
//    }
//}

//void pop_front(struct Node **List){
//    struct Node *TempNode = *List;
//    uint32 ListLength = 0;      /*  */
//
//    ListLength = length(*List);
//    if(ListLength == 0){
//        printf("List is Empty , nothing to be deleted !! \n");
//    }
//    else{
//        *List = TempNode->NodeLink;
//        TempNode->NodeLink = NULL; /* TempNode is a free node */
//        free(TempNode);
//    }
//}

//void remove_element(struct Node *List){
//    struct Node *NodeListCounter = List;
//    struct Node *NextNode = List;
//    uint32 NodePosition = 0;    /*  */
//    uint32 ListLength = 0;      /*  */
//    uint32 NodeCounter = 1;     /* Points to the first node */
//
//    printf("Enter Node Position (First node is position = 1): ");
//    scanf("%i", &NodePosition);
//    ListLength = length(List);
//    if((NodePosition > ListLength) || (ListLength == 1)){
//        printf("Please use Delete_Node_At_Beginning !! \n");
//    }
//    else{
//        while(NodeCounter < (NodePosition - 1)){
//            NodeCounter++;
//            NodeListCounter = NodeListCounter->NodeLink;
//        }
//        NextNode = NodeListCounter->NodeLink;
//        NodeListCounter->NodeLink = NextNode->NodeLink;
//        free(NextNode);
//    }
//}

//void display_all(struct Node *List){
//    struct Node *TempNode = List;
//
//    printf("List Values : ");
//    if(TempNode == NULL){
//        printf("List is empty !! \n");
//    }
//    else{
//        while(TempNode != NULL){
//            printf("%i -> ", TempNode->NodeData);
//            TempNode = TempNode->NodeLink;
//        }
//        if(TempNode == NULL){
//            printf("NULL \n");
//        }
//    }
//}

uint32 length(struct Node *List){
    struct Node *TempNode = List;
    uint32 NodeCount = 0;

    while(TempNode != NULL){
        NodeCount++;
        TempNode = TempNode->NodeLink;
    }

    return NodeCount;
}

void destroy_List(struct Node *List)
{
    struct Node *tempNode;
    while (List != NULL)
    {
        tempNode = List;
        List = List->NodeLink;
        free(tempNode);
    }
}