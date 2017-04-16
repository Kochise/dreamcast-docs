/* @doc
 *
 * @module TEMPLATE.CPP - Some Template Examples |
 *
 * This module shows how to code Autoduck tags for C++ template
 * classes and member functions.
 *
 * Autoduck example by Eric Artzt (erica@microsoft.com)
 */


//@class Template class
//@tcarg class | T | A class to store in stack
//@tcarg int | i | Initial size of stack

template<class T, int i> class MyStack
{
    //@cmember The top

    T*  pStack;

    //@cmember The stack

    T StackBuffer[i];

    //@cmember The count

    int cItems = i * sizeof(T);

public:
    //@cmember Constructor

    MyStack( void );

    //@cmember Addd one

    void push( const T item );

    //@cmember Remove one

    T& pop( void );

    //@cmember No link - function template args

    T& popper<class B>( B foo);

    //@cmember Link - function template args

    T& popperlink<class B>( B foo);
};


//@func Template function test
//@tfarg class | B | A class.
//@tfarg class | C | Another class.

template<class B, class C>
int TemplateFunc(
    B foo,                 //@parm A Foo
    C bar)                 //@parm A Bar
{
}

//@mfunc Function template args
//@tfarg class | B | A class to pass
//@tcarg class | T | A class to store in stack
//@tcarg int | i | Initial size of stack

template< class T, int i > 
MyStack< T, i>::popperlink<class B>( void )
{ 

}

//@mfunc Template constructor function
//@tcarg class | T | A class to store in stack
//@tcarg int | i | Initial size of stack

template< class T, int i > 
MyStack< T, i>::MyStack( void )
{ 

}

//@mfunc Pushes something on stack
//@tcarg class | T | A class to store in stack
//@tcarg int | i | Initial size of stack

template< class T, int i > 
void MyStack< T, i >::push( 
    const T item )  //@parm Item to push on stack
{ 

}

//@mfunc Pops something off stack
//@tcarg class | T | A class to store in stack
//@tcarg int | i | Initial size of stack

template< class T, int i > 
T& MyStack< T, i >::pop( void )
{ 

}



