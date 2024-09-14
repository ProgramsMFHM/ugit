#ifndef LIST
#define LIST
#include "commit.h"
#include "time.h"

typedef commit ElementType;
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Log;
typedef PtrToNode Position;

List MakeEmpty( List L );
int IsEmpty( List L );
int IsLast( Position P, List L );
Position Find( time_t X, List L );
void Delete( time_t X, List L );
Position FindPrevious( time_t X, List L );
void Insert( ElementType X, List L, Position P );
void DeleteList( List L );
Position Header( List L );
Position First( List L );
Position Advance( Position P );
ElementType Retrieve( Position P );
List PrintList( List L );

#endif
