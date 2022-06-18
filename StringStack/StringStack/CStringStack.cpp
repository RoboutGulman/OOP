#include "stdafx.h"

#include "CStackOverflowError.h"
#include "CStackUnderflowError.h"
#include "CStringStack.h"

CStringStack::CStringStack(CStringStack const &other)
{
    if (other.Empty())
    {
        return;
    }

    auto currentOtherNode = other.m_top;
    m_top = std::make_shared<Item>(currentOtherNode->value);
    auto currentMyNode = m_top;

    currentOtherNode = currentOtherNode->next;

    while (currentOtherNode)
    {
        //если будет выброшено исключение, начнётся рекурсивное удаление указателей и не хватит глубины стека
        currentMyNode->next = std::make_shared<Item>(currentOtherNode->value);
        currentMyNode = currentMyNode->next;
        currentOtherNode = currentOtherNode->next;
    }
    m_size = other.Size();
}

CStringStack::CStringStack(CStringStack &&other) noexcept : m_top(other.m_top), m_size(other.m_size)
{
    other.m_top = nullptr;
    other.m_size = 0;
}

CStringStack::~CStringStack() noexcept
{
    Clear();
}

CStringStack &CStringStack::operator=(CStringStack const &other)
{
    if (std::addressof(other) != this)
    {
        CStringStack copy(other);
        std::swap(m_top, copy.m_top);
        std::swap(m_size, copy.m_size);
    }
    return *this;
}

CStringStack &CStringStack::operator=(CStringStack &&other) noexcept
{
    if (std::addressof(other) != this)
    {
        m_top = other.m_top;
        m_size = other.m_size;

        other.m_top = nullptr;
        other.m_size = 0;
    }
    return *this;
}

void CStringStack::Push(const std::string &str)
{
    size_t newSize = m_size + 1;

    //overflow size_t condition
    if (newSize < m_size)
    {
        throw CStackOverflowError();
    }

    auto newNode = std::make_shared<Item>(str, m_top);
    m_top = newNode;
    m_size = newSize;
}

void CStringStack::Push(std::string &&str)
{
    size_t newSize = m_size + 1;

    //overflow size_t condition
    if (newSize < m_size)
    {
        throw CStackOverflowError();
    }

    auto newNode = std::make_shared<Item>(std::move(str), m_top);
    m_top = newNode;
    m_size = newSize;
}

void CStringStack::Pop()
{
    if (Empty())
    {
        throw CStackUnderflowError();
    }
    m_top = m_top->next;
    --m_size;
}

std::string CStringStack::Top() const
{
    if (Empty())
    {
        throw CStackUnderflowError();
    }
    return m_top->value;
}

bool CStringStack::Empty() const
{
    return m_size == 0;
}

std::size_t CStringStack::Size() const
{
    return m_size;
}

void CStringStack::Clear()
{
    while (!Empty())
    {
        Pop();
    }
}
