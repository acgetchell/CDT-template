//
// Created by Adam Getchell on 10/29/20.
//

#ifndef CDT_TEMPLATE_DATASET_HPP
#define CDT_TEMPLATE_DATASET_HPP
template<typename T>
struct Dataset
{
  explicit Dataset(T& data) : data_{ data } {}
  T&   data_;
  bool operator==(Dataset const& rhs) const
  {
    return (this->data_ == rhs.data_);
  }
  bool operator!=(Dataset const& rhs) const
  {
    return this->data_ != rhs.data_;
  }
};
#endif//CDT_TEMPLATE_DATASET_HPP
