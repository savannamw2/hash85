/***********************************************************************
 * Header:
 *    HASH
 * Summary:
 *    Our custom implementation of std::unordered_Set
 *        ____     _______        __
 *      .' __ '.  |  _____|   _  / /
 *      | (__) |  | |____    (_)/ /
 *      .`____'.  '_.____''.   / / _
 *     | (____) | | \____) |  / / (_)
 *     `.______.'  \______.' /_/
 * 
 *    This will contain the class definition of:
 *        unordered_set           : A class that represents a hash
 *        unordered_set::iterator : An interator through hash
 * Author
 *    <Your name here>
 ************************************************************************/

#pragma once

#include <cmath>            // for std::abs
#include <cassert>          // for assert()
#include <initializer_list> // for std::initializer_list
#include <utility>          // for std::move()
   
#define HASH_EMPTY_VALUE -1

class TestHash;             // forward declaration for Hash unit tests

namespace custom
{
/************************************************
 * UNORDERED SET
 * A set implemented as a hash
 ************************************************/
class unordered_set
{
   friend class ::TestHash;   // give unit tests access to the privates
public:
   //
   // Construct
   //
   unordered_set()
   {
   //set numElements to 0 and choose a value for buckets under 10
   numElements = 0;
   buckets[8];
   for (int i = 0; i < 10; ++i)
   {
      buckets[i] = HASH_EMPTY_VALUE; // initialize all buckets to empty
   }
   }
   unordered_set(unordered_set&  rhs)
   {
      //copy the rhs
      *this = rhs;
   }
   unordered_set(unordered_set&& rhs) noexcept
   {
      //move the rhs
      *this = std::move(rhs);
   }
   template <class Iterator>
   unordered_set(Iterator first, Iterator last)
   {
   }

   //
   // Assign
   //
   unordered_set& operator=(unordered_set& rhs);
   unordered_set& operator=(unordered_set&& rhs) noexcept;
   unordered_set& operator=(const std::initializer_list<int>& il);
   void swap(unordered_set& rhs)
   {
   }

   // 
   // Iterator
   //
   class iterator;
   iterator begin();
   iterator end();

   // Access
   size_t bucket(const int & t)
   {
       return std::abs(t) % 10;
   }
   iterator find(const int& t);

   //   
   // Insert
   //
   iterator insert(const int& t);
   void insert(const std::initializer_list<int> & il);


   // 
   // Remove
   //
   void clear() noexcept
   {
       for (int i = 0; i < 10; ++i)
       {
          buckets[i] = HASH_EMPTY_VALUE;
       }
       numElements = 0;
   }
   iterator erase(const int& t);

   //
   // Status
   //
   size_t size() const 
   {
       //numElements is our size
       return numElements;
   }
   bool empty() const 
   { 
       return numElements == 0;
   }
   size_t bucket_count() const 
   { 
       return 10;
   }
   size_t bucket_size(size_t i) const
    {
        assert(i < 10);  // safety check
        return (buckets[i] != HASH_EMPTY_VALUE) ? 1 : 0;
    }

private:
 
   int buckets[10];     // exactly 10 buckets of pointers. buckets[iBucket] == HASH_EMPTY_VALUE means it is not filled
   int numElements;     // number of elements in the Hash
};


/************************************************
 * UNORDERED SET ITERATOR
 * Iterator for an unordered set
 ************************************************/
class unordered_set::iterator
{
   friend class ::TestHash;   // give unit tests access to the privates
public:
   // 
   // Construct
   iterator() : pBucket(nullptr), pBucketEnd(nullptr) {}
    
   iterator(int * pBucket, int * pBucketEnd)
   {
       //Give pBucket and pBucket the values
       this->pBucket = pBucket;
       this->pBucketEnd = pBucketEnd;
   }
   iterator(const iterator& rhs) 
   {
       //copy the rhs values
       pBucket = rhs.pBucket;
       pBucketEnd = rhs.pBucketEnd;
   }

   //
   // Assign
   //
   iterator& operator = (const iterator& rhs)
   {
       pBucket = rhs.pBucket;
       pBucketEnd = rhs.pBucketEnd;
      return *this;
   }

   //
   // Compare
   //
   bool operator != (const iterator& rhs) const 
   {
       //Compare to see if they are not equal
       return pBucket != rhs.pBucket;
   }
   bool operator == (const iterator& rhs) const 
   {
       //Compare to see if they are equal.
       return pBucket == rhs.pBucket;
   }

   // 
   // Access
   //
   int& operator * ()
   {
       return *pBucket;  // return first item in the list
   }

   //
   // Arithmetic
   //
   iterator& operator ++ ();
   iterator operator ++ (int postfix)
   {
       iterator temp = *this;  // save current position
        ++(*this);              // call prefix increment to advance
        return temp;            // return the old value
   }

private:
   int* pBucket;
   int* pBucketEnd;
};


/*****************************************
 * UNORDERED SET ::ASSIGN
 ****************************************/
inline unordered_set& unordered_set::operator=(unordered_set& rhs)
{
    //set numElements to rhs value
      numElements = rhs.numElements;
      //iterate through buckets and copy each
      for (int i = 0; i < 10; ++i)
      {
         buckets[i] = rhs.buckets[i];
      }
      return *this;
}
inline unordered_set& unordered_set::operator=(unordered_set&& rhs) noexcept
{
   return *this;
}
inline unordered_set& unordered_set::operator=(const std::initializer_list<int>& il)
{
   return *this;
}


/*****************************************
 * UNORDERED SET :: BEGIN / END
 * Points to the first valid element in the has
 ****************************************/
inline typename unordered_set::iterator  unordered_set::begin()
{
   // find the first non-empty bucket
    int* pBegin = buckets;
    int* pEnd = buckets + 10;

    // skip empty buckets
    while (pBegin != pEnd && *pBegin == HASH_EMPTY_VALUE)
       ++pBegin;

    return iterator(pBegin, pEnd);
}
inline typename unordered_set::iterator  unordered_set::end()
{
    return iterator(buckets + 10, buckets + 10);
}


/*****************************************
 * UNORDERED SET :: ERASE
 * Remove one element from the unordered set
 ****************************************/
inline typename unordered_set::iterator unordered_set::erase(const int& t)
{
   return unordered_set::iterator();
}


/*****************************************
 * UNORDERED SET :: INSERT
 * Insert one element into the hash
 ****************************************/
inline custom::unordered_set::iterator unordered_set::insert(const int& t)
{
   return unordered_set::iterator();
}

inline void unordered_set::insert(const std::initializer_list<int> & il)
{
}

/*****************************************
 * UNORDERED SET :: FIND
 * Find an element in an unordered set
 ****************************************/
inline typename unordered_set::iterator unordered_set::find(const int& t)
{
   return unordered_set::iterator();
}

/*****************************************
 * UNORDERED SET :: ITERATOR :: INCREMENT
 * Advance by one element in an unordered set
 ****************************************/
inline typename unordered_set::iterator & unordered_set::iterator::operator ++ ()
{
   return *this;
}

/*****************************************
 * SWAP
 * Stand-alone unordered set swap
 ****************************************/
inline void swap(unordered_set& lhs, unordered_set& rhs)
{
}

}
