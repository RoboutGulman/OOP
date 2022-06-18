#pragma once
class CStackOverflowError : public std::runtime_error
{
  public:
    CStackOverflowError();

  private:
    inline static const std::string MESSAGE = "stack is overflowed";
};
