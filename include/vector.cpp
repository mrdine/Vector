#include <iostream>
#include "vector.h"

//=== ITERATORS
iterator begin()
{
  iterator i;
  pointer p = &data[0];
  i.current = p;
  return i;
}

iterator end()
{
  iterator i;
  pointer p = &data[capacity-1];
  p += 1;
  i.current = p;
  return i;
}

const_iterator cbegin() const
{
  const_iterator i;
  pointer p = &data[0];
  i.current = p;
  return i;
}

const_iterator cend() const
{
  const_iterator i;
  pointer p = &data[capacity-1];
  p += 1;
  i.current = p;
  return i;
}
