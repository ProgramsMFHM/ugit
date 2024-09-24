/// \file list.c
/// \brief Funciones relacionadas a listas enlazadas simples, vistas en clase
/// \author Alan Almonacid y Milton Hernández
#include "list.h"

/// @brief Estructura para manejar el uso de Listas Enlazadas Simples
struct _node
{
    /// @brief Contenido del nodo
    ElementType Element;
    /// @brief Puntero al siguiente nodo de la lista
    Position Next;
};

/// @brief Vacía una lista dejando solamente el centinela apuntando a NULL
/// @param L Lista a vaciar
/// @return Puntero a la lista vacía
List makeEmpty( List L )
{
    char aux[30];
    if( L != NULL )
        deleteList( L );
    L = malloc( sizeof( struct _node ) );
    if( L == NULL )
    {
        sprintf(aux, "%lu", sizeof( struct _node ));
        printError(200, aux, NULL);
    }
    L->Next = NULL;
    return L;
}

/// @brief Indica si una lista está vacía
/// @param L Lista a comprobar
/// @return 0 en caso vacío
int isEmpty( List L )
{
    return L->Next == NULL;
}

/// @brief Indica si un nodo @p P es el último de una lista
/// @param P Nodo a revisar
/// @return 0 en caso de no pertenencia
int isLast( Position P)
{
    return P->Next == NULL;
}

/// @brief Busca un nodo dentro de @p L que contenga el elemento @p X
/// @param X Elemento a buscar
/// @param L Lista dentro de la que se buscará
/// @return Nodo donde se encuentra X, NULL en caso de no encontrar nada
Position find(unsigned int X, List L)
{
    Position P;

    P = L->Next;
    while( P != NULL && P->Element.ID != X )
        P = P->Next;

    return P;
}

/// @brief Busca un nodo dentro de @p L que contenga el elemento @p X y lo elimina
/// @param X Elemento a buscar
/// @param L Lista dentro de la que se buscará
void delete(unsigned int X, List L)
{
    Position P, TmpCell;

    P = findPrevious( X, L );

    if( !isLast( P ) )
    {
        TmpCell = P->Next;
        P->Next = TmpCell->Next;
        free(TmpCell);
    }
}

/// @brief Encuentra el nodo anterior al que contiene el elemento @p X
/// @param X Elemento a buscar
/// @param L Lista dentro de la que se buscará
/// @return El nodo previo al que contiene X, en caso de no encontrar nada devuelve NULL
Position findPrevious( unsigned int X, List L )
{
    Position P;
    P = L;
    while( P->Next != NULL && P->Next->Element.ID != X )
        P = P->Next;
    return P;
}

/// @brief Inserta el elemento @p X dentro de una lista luego del nodo @p P
/// @param X Elemento a insertar
/// @param P Nodo después del cuál se insertará el elemento @p X
void insert( ElementType X, Position P )
{
    char aux[30];
    Position TmpCell;

    TmpCell = malloc( sizeof( struct _node ) );
    if( TmpCell == NULL )
    {
        sprintf(aux, "%lu", sizeof( struct _node ));
        printError(200, aux, NULL);
    }
    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}

/// @brief Elimina la lista @p L
/// @param L Lista a eliminar
void deleteList( List L )
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

/// @brief Retorna el centinela de la lista @p L
/// @param L Lista de la que se retornará el centinela
/// @return Se retorna la misma lista
Position header( List L )
{
    return L;
}

/// @brief Retorna el elemento inmediatamente posterior al centinela de la lista @p L
/// @param L Lista de la que se retornará el primer elemento
/// @return Se retorna la misma lista
Position first( List L )
{
    return L->Next;
}

/// @brief Retorna el elemento inmediatamente posterior al nodo @p P
/// @param P Nodo sobre el que se buscará el siguiente
/// @return Se retorna el nodo correspondiente
Position advance( Position P )
{
    return P->Next;
}

/// @brief Devuelve el elemento dentro del nodo @p P
/// @param P Nodo dentro del que se encuentra la información a devolver
/// @return Retorna el elemento dentro de @p P
ElementType retrieve( Position P )
{
    return P->Element;
}

/// @brief Imprime por consola la lsita @p L
/// @param L Lista a imprimir
/// @return Retorna un nodo a la lista impresa
List printList( List L ){
    Position P = L->Next;

    while (P)
    {
        printCommit(P->Element);
        P = P->Next;
    }

    return L;
}