#pragma once
#include <string>
#include "eAuthResultType.h"

struct sLoginResponse
{
	long requestId;
	long userId;
	eAuthResultType result;
};