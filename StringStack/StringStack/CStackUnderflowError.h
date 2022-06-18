#pragma once
class CStackUnderflowError : public std::runtime_error
{
  public:
    CStackUnderflowError();

  private:
    inline static const std::string MESSAGE = "stack is empty";
};
