extern void *inlineReturnAddress;

// _ReturnAddress should be prototyped before use 
#ifdef __cplusplus
extern "C"
#endif
void * _ReturnAddress(void);

#pragma intrinsic(_ReturnAddress)

int Add(int a, int b)
{
	inlineReturnAddress = _ReturnAddress();
	return a+b;
}

