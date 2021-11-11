#include "cAuthRequester.h"

cAuthRequester::cAuthRequester()
	: buffer(DEFAULT_BUFLEN)
{
	socket = NULL;
	requestId = 0;
}