#pragma once
class CStringStack
{
  public:
    CStringStack() = default;
    CStringStack(CStringStack const &other);
    CStringStack(CStringStack &&other) noexcept;

    ~CStringStack() noexcept;

    CStringStack &operator=(CStringStack const &other);
    CStringStack &operator=(CStringStack &&other) noexcept;

    void Push(std::string const &str);
    void Push(std::string &&str);

    void Pop();
    std::string Top() const;

    bool Empty() const;
    std::size_t Size() const;

    void Clear();

  private:
    struct Item;
    typedef std::shared_ptr<Item> ItemPtr;
    struct Item
    {
        Item(std::string const &value, ItemPtr const &next) : value(value), next(next)
        {
        }
        explicit Item(std::string const &value) : value(value)
        {
        }
        std::string value;
        ItemPtr next = nullptr;
    };
    ItemPtr m_top = nullptr;
    std::size_t m_size = 0;
};
