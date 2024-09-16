#include "list.h"

struct Node
{
    ElementType Element;
    Position    Next;
};

List MakeEmpty( List L )
{
    char aux[30];
    if( L != NULL )
        DeleteList( L );
    L = malloc( sizeof( struct Node ) );
    if( L == NULL )
    {
        sprintf(aux, "%lu", sizeof( struct Node ));
        printError(200, aux, NULL);
    }
    L->Next = NULL;
    return L;
}

int IsEmpty( List L )
{
    return L->Next == NULL;
}

int IsLast( Position P, List L )
{
    return P->Next == NULL;
}

Position Find(unsigned int X, List L)
{
    Position P;

    P = L->Next;
    while( P != NULL && P->Element.ID != X )
        P = P->Next;

    return P;
}

void Delete(unsigned int X, List L)
{
    Position P, TmpCell;

    P = FindPrevious( X, L );

    if( !IsLast( P, L ) )
    {
        TmpCell = P->Next;
        P->Next = TmpCell->Next;
        free(TmpCell);
    }
}

Position FindPrevious( unsigned int X, List L )
{
    Position P;
    P = L;
    while( P->Next != NULL && P->Next->Element.ID != X )
        P = P->Next;
    return P;
}

void Insert( ElementType X, List L, Position P )
{
    char aux[30];
    Position TmpCell;

    TmpCell = malloc( sizeof( struct Node ) );
    if( TmpCell == NULL )
    {
        sprintf(aux, "%lu", sizeof( struct Node ));
        printError(200, aux, NULL);
    }
    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}

void DeleteList( List L )
{
    Position P, Tmp;

    P = L->Next;
    L->Next = NULL;
    while( P != NULL )
    {
        Tmp = P->Next;
        free( P );
        P = Tmp;
    }
}
void InvertList( List L )
{
    Position P = L->Next;
    Position Next = P;
    Position Previous = NULL;

    while( P != NULL )
    {
        Next = P->Next;
        P->Next = Previous;
        Previous = P;
        P = Next;
    }
    L->Next = Previous;
}

Position Header( List L )
{
    return L;
}

Position First( List L )
{
    return L->Next;
}

Position Advance( Position P )
{
    return P->Next;
}

ElementType Retrieve( Position P )
{
    return P->Element;
}

List PrintList( List L ){
    Position P = L->Next;

    while (P)
    {
        printCommit(P->Element);
        P = P->Next;
    }

    return L;
}