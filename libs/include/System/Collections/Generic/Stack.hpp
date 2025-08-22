#include "System/Private/private.hpp"
#include "System/Exception.hpp"
#include <stack>
#include <algorithm>


namespace System::Collections::Generic
{

template <class ElementType, class Container = std::deque<ElementType>>
class Stack
{
public:
    using container_type = Container;
    using value_type = Container::value_type;
    using size_type  = Container::size_type;
    using reference  = Container::reference;
    using const_reference = Container::const_reference;

    Stack() = default;

    Stack(const Container &container)
        :
        _stack( container )
    {
    }

    Stack(Container &&container)
        :
        _stack( std::move(container) )
    {
    }

    template <class InputIterator>
    Stack(InputIterator first, InputIterator one_past_last)
        :
        _stack( first, one_past_last )
    {
    }

    // For now, do nothing  (Don't know how to implement this)
    Stack(int initial_capacity) { assert(false); }

    // For now, do nothing  (Don't know how to implement this)
    size_type Capacity() const { assert(false); return 0; }

    size_type Count() const { return _stack.size(); }

    bool Contains(const ElementType &item) const
    {
        return std::find( _stack.cbegin(), _stack.cend(), item ) != _stack.cend();
    }

    void Clear()
    {
        while ( !_stack.empty() )
            _stack.pop();
    
        POSTCONDITION( Count() == 0 );
    }
#if 0
    void CopyTo() const
    {
    }
#endif
    void Push(const ElementType &item)
    {
        _stack.push( item );
    }

    void Push(ElementType &&item)
    {
        _stack.push( std::move(item) );
    }

    ElementType Pop()
    {
        using namespace std::literals;

        if ( _stack.empty() )
          ThrowWithTarget( InvalidOperationException( "Stack is empty"sv ) );

        ElementType r = _stack.top();

        _stack.pop();
        return r;
    }

    const ElementType &Peek() const
    {
        using namespace std::literals;

        if ( _stack.empty() )
          ThrowWithTarget( InvalidOperationException( "Stack is empty"sv ) );

        return _stack.top();
    }

    bool TryPeek(ElementType &out_parameter) const
    {
        if ( _stack.empty() )
        {
            out_parameter = ElementType{};
            return false;
        }
        
        out_parameter = _stack.top();
        return true;
    }

    bool TryPop(ElementType &out_parameter)
    {
        if ( _stack.empty() )
        {
            out_parameter = ElementType{};
            return false;
        }

        out_parameter = _stack.top();
        _stack.pop();
        return true;
    }
protected:

    class PrivateStackImplementation : public std::stack<ElementType, Container>
    {
    public:
        using iterator = Container::iterator;
        using const_iterator = Container::const_iterator;
        using reverse_iterator = Container::reverse_iterator;
        using const_reverse_iterator = Container::const_reverse_iterator;

        using std::stack<ElementType, Container>::stack;
        using std::stack<ElementType, Container>::c; // Assume the name of the non-public Container object is "c"

        const_iterator  begin() const { return c.begin(); }
        const_iterator cbegin() const { return c.cbegin(); }
              iterator  begin()       { return c.begin(); }
        const_reverse_iterator  rbegin() const { return c.rbegin(); }
        const_reverse_iterator crbegin() const { return c.crbegin(); }
              reverse_iterator  rbegin()       { return c.rbegin(); }

        const_iterator  end() const { return c.end(); }
        const_iterator cend() const { return c.end(); }
              iterator  end()       { return c.end(); }
        const_reverse_iterator  rend() const { return c.rend(); }
        const_reverse_iterator crend() const { return c.rend(); }
              reverse_iterator  rend()       { return c.rend(); }
    };

    PrivateStackImplementation _stack;
};

}