#pragma once
#include <string>
#include "eRegisterResultType.h"

struct sRegisterResponse
{
	long requestId;
	long userId;
	eRegisterResultType result;
};