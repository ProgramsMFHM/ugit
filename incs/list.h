/// \file list.h
/// \brief Cabecera para list.c
#ifndef LIST
#define LIST
#include <stdlib.h>
#include "errors.h"
#include "commit.h"
#include "time.h"

typedef commit ElementType;
struct Node;
typedef struct _node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Log;
typedef PtrToNode Position;

List makeEmpty( List L );
int isEmpty( List L );
int isLast( Position P, List L );
Position find( unsigned int X, List L );
void delete( unsigned int X, List L );
Position findPrevious( unsigned int X, List L );
void insert( ElementType X, List L, Position P );
void deleteList( List L );
Position header( List L );
Position first( List L );
Position advance( Position P );
ElementType retrieve( Position P );
List printList( List L );

#endif
