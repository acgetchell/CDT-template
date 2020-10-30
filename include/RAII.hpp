//
// Created by Adam Getchell on 10/29/20.
//

#ifndef CDT_TEMPLATE_RAII_HPP
#define CDT_TEMPLATE_RAII_HPP

#include <memory>

template<typename T>
class RAII
{
private:
  T const& source_data;
  std::unique_ptr<T> internal_copy;

public:
  explicit RAII(T const& dataset) : source_data{ dataset }, internal_copy{ std::make_unique<T>(dataset) } {}
  [[nodiscard]] auto source_get() const { return source_data; }
  [[nodiscard]] auto internal_get() const { return *internal_copy; }
  void mutate(T data)
  {
    internal_copy = std::make_unique<T>(data);
  }
  [[nodiscard]] bool isChanged() const
  {
    return static_cast<T>(source_data) != *internal_copy;
  }
};
#endif//CDT_TEMPLATE_RAII_HPP
