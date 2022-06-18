#include "stdafx.h"

#include "CStackOverflowError.h"

CStackOverflowError::CStackOverflowError() : std::runtime_error(MESSAGE)
{
}
