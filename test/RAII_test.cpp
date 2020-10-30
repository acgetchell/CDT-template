//
// Created by Adam Getchell on 10/29/20.
//
#include "Dataset.hpp"
#include "RAII.hpp"
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <vector>

SCENARIO("Instantiate a Dataset", "[Dataset]")
{
  GIVEN("A vector.")
  {
    std::vector a{ 1, 2, 3 };
    WHEN("A Dataset is constructed with the vector.")
    {
      auto c = Dataset(a);
      THEN("The Dataset matches the vector.")
      {
        REQUIRE(a == c.data_);
      }
    }
  }
}

SCENARIO("Instantiate an RAII class", "[RAII]")
{
  GIVEN("A dataset.")
  {
    std::vector a{ 1, 2, 3 };
    auto        c = Dataset(a);
    WHEN("An RAII class is constructed with the dataset.")
    {
      auto e = RAII(c);
      THEN("The RAII internal data == the dataset.")
      {
        REQUIRE(e.source_get().data_ == c.data_);
      }
      THEN("THe RAII internal data == RAII source data.")
      {
        REQUIRE(e.source_get().data_ == e.internal_get().data_);
      }
    }
  }
}

SCENARIO("Mutating the RAII class", "[RAII]")
{
  GIVEN("A RAII class constructed with a dataset.")
  {
    std::vector a{ 1, 2, 3 };
    auto        c = Dataset(a);
    auto        e = RAII(c);
    WHEN("The internal data is changed.")
    {
      std::vector b{ 4, 5, 6 };
      auto        d = Dataset(b);
      e.mutate(d);
      REQUIRE_FALSE(e.internal_get().data_ == e.source_get().data_);
      THEN("The source data doesn't change.")
      {
        REQUIRE(e.source_get().data_ == c.data_);
        fmt::print("Dataset constructed with {}\n", a);
        fmt::print("Source data is {}\n", e.source_get().data_);
        fmt::print("Internal data is {}\n", e.internal_get().data_);
      }
    }
    WHEN("The source vector is changed.")
    {
      a[1] = 20;
      THEN("The RAII source data is also changed.")
      {
        REQUIRE(e.source_get().data_ == a);
        fmt::print("Dataset vector is now {}\n", a);
        fmt::print("Source data is {}\n", e.source_get().data_);
      }
      THEN("But the RAII internal data is not changed.")
      {
        fmt::print("Dataset constructed with {}\n", a);
        fmt::print("Source data is {}\n", e.source_get().data_);
        fmt::print("Internal data is {}\n", e.internal_get().data_);
        REQUIRE_FALSE(e.internal_get().data_ == a);
      }
    }
  }
}
