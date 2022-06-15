#include "stdafx.h"

#include "CStackUnderflowError.h"

CStackUnderflowError::CStackUnderflowError()
	: std::runtime_error(MESSAGE)
{
}