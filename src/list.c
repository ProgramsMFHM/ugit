#include <stdlib.h>
#include "list.h"
#include "errors.h"

struct Node
{
    ElementType Element;
    Position    Next;
};

List MakeEmpty( List L )
{
    if( L != NULL )
        DeleteList( L );
    L = malloc( sizeof( struct Node ) );
    if( L == NULL )
        fatal_error( "No se pudo asignar espacio" );
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

Position Find(time_t X, List L)
{
    Position P;

    P = L->Next;
    while( P != NULL && P->Element.date != X )
        P = P->Next;

    return P;
}

void Delete(time_t X, List L)
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

Position FindPrevious( time_t X, List L )
{
    Position P;
    P = L;
    while( P->Next != NULL && P->Next->Element.date != X )
        P = P->Next;
    return P;
}

void Insert( ElementType X, List L, Position P )
{
    Position TmpCell;

    TmpCell = malloc( sizeof( struct Node ) );
    if( TmpCell == NULL )
        fatal_error( "No se pudo asignar espacio" );

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
        // Liberamos punteros dentro del nodo
        free(P->Element.message);

        // Liberamos el nodo
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