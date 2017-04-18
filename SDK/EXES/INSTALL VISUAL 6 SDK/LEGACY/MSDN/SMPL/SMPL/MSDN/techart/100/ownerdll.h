//////////////////////////////////////////////////////////////////////////
// OwnerDLL -
//		This DLL in conjunction with Owner.Exe helps to demonstrate the 
//		issues involved in memory ownership between a DLL and an App.
//

////////////////////////////////////////////////////////////////////////
// Define a Contained Class.
// Classes contained in exported classes must be exported.
//
class __export CContainedClass{
	public:
		char aMessage[1024] ;
};

//////////////////////////////////////////////////////////////////////
// Define the class to be exported.
//
//
class __export CFooInDLL{
	public:
		CFooInDLL() ;
		~CFooInDLL() ;
		
		///////////////////
		// The next two functions are identical except yourString is inline.
	   //
		void yourString() ;
		void myString() ;
		
		//////////////////
		// Contained objects
	   //							
		CContainedClass aContainedClass ;
		char aBuffer[1024] ;
		char *aString ;
} ;

/////// INLINE FUNCTION ////////
//    APP will own memory     //
//
inline
void CFooInDLL::yourString()
{
	if (aString)
		delete aString ; // This line will fail an assertion in memory.cpp
							  // when compiled with the MFC debug libraries, if
							  // an attempt is made to delete memory owned by
							  // the DLL.

	
	aString = new char[1024] ;
}