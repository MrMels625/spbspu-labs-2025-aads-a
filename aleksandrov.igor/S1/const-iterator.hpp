#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include <iterator>
#include <cassert>
#include "list.hpp"

namespace aleksandrov
{
  template< typename T >
  class List;

  template< typename T >
  class ConstIterator: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    ConstIterator():
      node_(nullptr)
    {}
    ConstIterator(detail::Node< T >* node):
      node_(node)
    {}
    ConstIterator< T >& operator++();
    ConstIterator< T > operator++(int);

    const T& operator*() const;
    const T* operator->() const;

    bool operator!=(const ConstIterator< T >&) const noexcept;
    bool operator==(const ConstIterator< T >&) const noexcept;
  private:
    friend List< T >;
    detail::Node< T >* node_;
  };

  template< typename T >
  ConstIterator< T >& ConstIterator< T >::operator++()
  {
    assert(node_);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  ConstIterator< T > ConstIterator< T >::operator++(int)
  {
    assert(node_);
    ConstIterator< T > result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  const T& ConstIterator< T >::operator*() const
  {
    assert(node_);
    return node_->data;
  }

  template< typename T >
  const T* ConstIterator< T >::operator->() const
  {
    assert(node_);
    return std::addressof(node_->data);
  }

  template< typename T >
  bool ConstIterator< T >::operator==(const ConstIterator< T >& rhs) const noexcept
  {
    return node_ == rhs.node_;
  }

  template< typename T >
  bool ConstIterator< T >::operator!=(const ConstIterator< T >& rhs) const noexcept
  {
    return !(rhs == *this);
  }
}

#endif

