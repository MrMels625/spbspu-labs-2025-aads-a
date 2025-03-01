#ifndef EMPLACE_HPP
#define EMPLACE_HPP

#include "decl.hpp"

#include <utility>

template< class T >
template< class... Args >
typename rychkov::List< T >::reference rychkov::List< T >::emplace(const_iterator pos, Args&&... args)
{
  node_t< value_type >* inserted = new node_t< value_type >{{std::forward<Args>(args)...}};
  if (begin() == end())
  {
    tail_ = head_ = inserted;
  }
  else{
    if (pos == end())
    {
      inserted->prev = tail_;
      tail_->next = inserted;
      tail_ = inserted;
    }
    else
    {
      inserted->next = pos.node_;
    }
    if (pos == begin())
    {
      inserted->next = head_;
      head_->prev = inserted;
      head_ = inserted;
    }
    else
    {
      inserted->next = pos.node_;
    }
  }
  size_++;
  return inserted->data;
}
template< class T >
template< class... Args >
typename rychkov::List< T >::reference rychkov::List< T >::emplace_back(Args&&... args)
{
  return emplace(end(), std::forward<Args>(args)...);
}
template< class T >
template< class... Args >
typename rychkov::List< T >::reference rychkov::List< T >::emplace_front(Args&&... args)
{
  return emplace(begin(), std::forward<Args>(args)...);
}

template< class T >
void rychkov::List< T >::push_front(const value_type& value)
{
  return emplace_front(value);
}
template< class T >
void rychkov::List< T >::push_front(value_type&& value)
{
  return emplace_front(std::move(value));
}
template< class T >
void rychkov::List< T >::push_back(const value_type& value)
{
  return emplace_back(value);
}
template< class T >
void rychkov::List< T >::push_back(value_type&& value)
{
  return emplace_back(std::move(value));
}

template< class T >
void rychkov::List< T >::insert(const_iterator pos, const value_type& value)
{
  emplace(pos, value);
}
template< class T >
void rychkov::List< T >::insert(const_iterator pos, value_type&& value)
{
  emplace(pos, std::move(value));
}
template< class T >
void rychkov::List< T >::insert(const_iterator pos, size_type count, value_type value)
{
  splice(pos, rychkov::List< value_type >(value, count));
}
template< class T >
template< class InputIt >
void rychkov::List< T >::insert(const_iterator pos, InputIt from, InputIt to)
{
  splice(pos, rychkov::List< value_type >(from, to));
}
template< class T >
void rychkov::List< T >::insert(const_iterator pos, std::initializer_list< value_type > rhs)
{
  insert(pos, rhs.begin(), rhs.end());
}

template< class T >
void rychkov::List< T >::splice(const_iterator pos, List& rhs)
{
  splice(pos, rhs, rhs.begin(), rhs.end());
}
template< class T >
void rychkov::List< T >::splice(const_iterator pos, List&& rhs)
{
  splice(pos, rhs);
}
template< class T >
void rychkov::List< T >::splice(const_iterator pos, List& rhs, const_iterator from, const_iterator to)
{
  if (from == to)
  {
    return;
  }
  size_type erasedSize = 0;
  for (const_iterator i = from; i != to; ++i, ++erasedSize)
  {}

  if (from == rhs.begin())
  {
    rhs.head_ = to.node_;
  }
  else
  {
    from.node_->prev->next = to.node_;
  }
  const_iterator insertedTail;
  if (to == rhs.end())
  {
    insertedTail = rhs.tail_;
    rhs.tail_ = from.node_->prev;
  }
  else
  {
    insertedTail = to.node_->prev;
    to.node_->prev = from.node_->prev;
  }

  if (pos == begin())
  {
    head_ = from.node_;
    from.node_->prev = nullptr;
  }
  else
  {
    pos.node_->prev->next = from.node_;
    from.node_->prev = pos.node_->prev;
  }
  if (pos == end())
  {
    tail_ = insertedTail.node_;
    insertedTail.node_->next = nullptr;
  }
  else
  {
    pos.node_->prev = insertedTail.node_;
    insertedTail.node_->next = pos.node_;
  }

  rhs.size_ -= erasedSize;
  size_ += erasedSize;
}

#endif
