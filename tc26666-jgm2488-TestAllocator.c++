// -------------------------------------
// projects/allocator/TestAllocator1.c++
// Copyright (C) 2015
// Glenn P. Downing
// -------------------------------------

// --------
// includes
// --------

#include <algorithm> // count
#include <memory>    // allocator

#include "gtest/gtest.h"

#include "Allocator.h"

// --------------
// Custom Unit Tests
// --------------

// my_allocator()

TEST(AllocatorFixture, my_allocator1) {
  my_allocator<int, 100> x;
  ASSERT_EQ(x[0], 92);
}

TEST(AllocatorFixture, my_allocator2) {
  my_allocator<double, 63> x;
  ASSERT_EQ(x[0], 55);
}

TEST(AllocatorFixture, my_allocator3) {
  my_allocator<char, 2904> x;
  ASSERT_EQ(x[0], 2896);
}

// exception test
TEST(AllocatorFixture, my_allocator4) {
  try {
    my_allocator<int, 1> x;
  } catch (std::bad_alloc &exception) {
  }
}

// allocate()

TEST(AllocatorFixture, allocate1) {
  my_allocator<int, 100> x;
  x.allocate(23);
  ASSERT_EQ(x[0], -92);
}

TEST(AllocatorFixture, allocate2) {
  my_allocator<double, 34> x;
  x.allocate(3);
  ASSERT_EQ(x[0], -26);
}

TEST(AllocatorFixture, allocate3) {
  my_allocator<char, 40> x;
  x.allocate(3);
  ASSERT_EQ(x[0], -3);
  ASSERT_EQ(x[11], 21);
}

// exception test
TEST(AllocatorFixture, allocate4) {
  my_allocator<int, 12> x;
  try {
    x.allocate(1);
    x.allocate(1);
  } catch (std::bad_alloc &exception) {
  }
}

// valid()

TEST(AllocatorFixture, valid1) {
  my_allocator<int, 100> x;
  int *p = (int *)&x[0];
  *p = -(*p);
  ASSERT_FALSE(x.valid());
}

TEST(AllocatorFixture, valid2) {
  my_allocator<int, 100> x;
  int *p = (int *)&x[0];
  *p = 4;
  *(p + 2) = 4;
  *(p + 3) = 4;
  *(p + 5) = 4;
  ASSERT_FALSE(x.valid());
}

TEST(AllocatorFixture, valid3) {
  my_allocator<int, 100> x;
  int *p = (int *)&x[0];
  *p = -4;
  *(p + 2) = -4;
  *(p + 3) = 80;
  *(p + 24) = 80;
  ASSERT_TRUE(x.valid());
}

TEST(AllocatorFixture, valid4) {
  my_allocator<int, 100> x;
  int *p = (int *)&x[0];
  *p = 4;
  *(p + 2) = -4;
  *(p + 3) = 4;
  *(p + 5) = -4;
  ASSERT_FALSE(x.valid());
}

// --------------
// Custom typed tests
// --------------

template <typename A> struct TestAllocatorCustom : testing::Test {
  // --------
  // typedefs
  // --------

  typedef A allocator_type;
  typedef typename A::value_type value_type;
  typedef typename A::size_type size_type;
  typedef typename A::pointer pointer;
};

typedef testing::Types<my_allocator<char, 44>> my_types_5;

TYPED_TEST_CASE(TestAllocatorCustom, my_types_5);

TYPED_TEST(TestAllocatorCustom, Custom_1) {
  typedef typename TestFixture::allocator_type allocator_type;
  typedef typename TestFixture::value_type value_type;
  typedef typename TestFixture::size_type size_type;
  typedef typename TestFixture::pointer pointer;

  allocator_type x;
  const size_type s1 = 5;
  const size_type s2 = 10;
  const value_type v = 2;
  const pointer p1 = x.allocate(s1);
  const pointer p2 = x.allocate(s2);
  const pointer p3 = x.allocate(s1);

  if (p1 != nullptr) {
    x.deallocate(p1, s1);
    x.deallocate(p3, s1);
    x.deallocate(p2, s2);
    x.allocate(9);
  }
}

template <typename A> struct TestAllocatorCustom2 : testing::Test {
  // --------
  // typedefs
  // --------

  typedef A allocator_type;
  typedef typename A::value_type value_type;
  typedef typename A::size_type size_type;
  typedef typename A::pointer pointer;
};

typedef testing::Types<my_allocator<int, 100>, my_allocator<double, 100>>
    my_types_6;

TYPED_TEST_CASE(TestAllocatorCustom2, my_types_6);

TYPED_TEST(TestAllocatorCustom2, custom_2) {
  typedef typename TestFixture::allocator_type allocator_type;
  typedef typename TestFixture::value_type value_type;
  typedef typename TestFixture::size_type size_type;
  typedef typename TestFixture::pointer pointer;

  allocator_type x;
  const size_type s1 = 1;
  const size_type s2 = 2;
  const value_type v = 2;
  const pointer p1 = x.allocate(s1);
  const pointer p2 = x.allocate(s2);
  const pointer p3 = x.allocate(s1);

  if (p1 != nullptr) {
    x.deallocate(p1, s1);
    x.deallocate(p2, s1);
    x.deallocate(p3, s2);
    x.allocate(92 / sizeof(value_type));
  }
}

template <typename A> struct TestAllocatorCustom3 : testing::Test {
  // --------
  // typedefs
  // --------

  typedef A allocator_type;
  typedef typename A::value_type value_type;
  typedef typename A::size_type size_type;
  typedef typename A::pointer pointer;
};

typedef testing::Types<my_allocator<int, 100>, my_allocator<double, 100>>
    my_types_7;

TYPED_TEST_CASE(TestAllocatorCustom3, my_types_7);

TYPED_TEST(TestAllocatorCustom3, custom_3) {
  typedef typename TestFixture::allocator_type allocator_type;
  typedef typename TestFixture::value_type value_type;
  typedef typename TestFixture::size_type size_type;
  typedef typename TestFixture::pointer pointer;

  allocator_type x;
  const size_type s1 = 400;
  const value_type v = 2;

  try {
    const pointer p1 = x.allocate(s1);
    assert(false);
  } catch (std::bad_alloc &exception) {
  }
}

// --------------
// TestAllocator1
// --------------

template <typename A> struct TestAllocator1 : testing::Test {
  // --------
  // typedefs
  // --------

  typedef A allocator_type;
  typedef typename A::value_type value_type;
  typedef typename A::size_type size_type;
  typedef typename A::pointer pointer;
};

typedef testing::Types<std::allocator<int>, std::allocator<double>,
                       my_allocator<int, 100>, my_allocator<double, 100>>
    my_types_1;

TYPED_TEST_CASE(TestAllocator1, my_types_1);

TYPED_TEST(TestAllocator1, test_1) {
  typedef typename TestFixture::allocator_type allocator_type;
  typedef typename TestFixture::value_type value_type;
  typedef typename TestFixture::size_type size_type;
  typedef typename TestFixture::pointer pointer;

  allocator_type x;
  const size_type s = 1;
  const value_type v = 2;
  const pointer p = x.allocate(s);
  x.construct(p, v);
  ASSERT_EQ(v, *p);
  x.destroy(p);
  x.deallocate(p, s);
}

TYPED_TEST(TestAllocator1, test_10) {
  typedef typename TestFixture::allocator_type allocator_type;
  typedef typename TestFixture::value_type value_type;
  typedef typename TestFixture::size_type size_type;
  typedef typename TestFixture::pointer pointer;

  allocator_type x;
  const size_type s = 10;
  const value_type v = 2;
  const pointer b = x.allocate(s);
  if (b != nullptr) {
    pointer e = b + s;
    pointer p = b;
    try {
      while (p != e) {
        x.construct(p, v);
        ++p;
      }
    } catch (...) {
      while (b != p) {
        --p;
        x.destroy(p);
      }
      x.deallocate(b, s);
      throw;
    }
    ASSERT_EQ(s, std::count(b, e, v));
    while (b != e) {
      --e;
      x.destroy(e);
    }
    x.deallocate(b, s);
  }
}

// --------------
// TestAllocator2
// --------------

TEST(TestAllocator2, const_index) {
  const my_allocator<int, 100> x;
  ASSERT_EQ(x[0], 92);
}

TEST(TestAllocator2, index) {
  my_allocator<int, 100> x;
  ASSERT_EQ(x[0], 92);
}

// --------------
// TestAllocator3
// --------------

template <typename A> struct TestAllocator3 : testing::Test {
  // --------
  // typedefs
  // --------

  typedef A allocator_type;
  typedef typename A::value_type value_type;
  typedef typename A::size_type size_type;
  typedef typename A::pointer pointer;
};

typedef testing::Types<my_allocator<int, 100>, my_allocator<double, 100>>
    my_types_2;

TYPED_TEST_CASE(TestAllocator3, my_types_2);

TYPED_TEST(TestAllocator3, test_1) {
  typedef typename TestFixture::allocator_type allocator_type;
  typedef typename TestFixture::value_type value_type;
  typedef typename TestFixture::size_type size_type;
  typedef typename TestFixture::pointer pointer;

  allocator_type x;
  const size_type s = 1;
  const value_type v = 2;
  const pointer p = x.allocate(s);
  if (p != nullptr) {
    x.construct(p, v);
    ASSERT_EQ(v, *p);
    x.destroy(p);
    x.deallocate(p, s);
  }
}

TYPED_TEST(TestAllocator3, test_10) {
  typedef typename TestFixture::allocator_type allocator_type;
  typedef typename TestFixture::value_type value_type;
  typedef typename TestFixture::size_type size_type;
  typedef typename TestFixture::pointer pointer;

  allocator_type x;
  const size_type s = 10;
  const value_type v = 2;
  const pointer b = x.allocate(s);
  if (b != nullptr) {
    pointer e = b + s;
    pointer p = b;
    try {
      while (p != e) {
        x.construct(p, v);
        ++p;
      }
    } catch (...) {
      while (b != p) {
        --p;
        x.destroy(p);
      }
      x.deallocate(b, s);
      throw;
    }
    ASSERT_EQ(s, std::count(b, e, v));
    while (b != e) {
      --e;
      x.destroy(e);
    }
    x.deallocate(b, s);
  }
}
