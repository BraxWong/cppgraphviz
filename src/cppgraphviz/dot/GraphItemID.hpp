#pragma once

#include "DotID.hpp"
#include "AttributeList.hpp"

namespace cppgraphviz::dot {

class GraphItemID
{
 private:
  // The unique dot ID of this item.
  DotID_type dot_id_;
  // Attribute list of this item.
  AttributeList attribute_list_;

 public:
  GraphItemID(DotID_type dot_id) : dot_id_(dot_id) { }

  // Accessors.
  DotID_type dot_id() const { return dot_id_; }
  AttributeList const& attribute_list() const { return attribute_list_; }
  AttributeList& attribute_list() { return attribute_list_; }
};

} // namespace cppgraphviz::dot
