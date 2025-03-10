#pragma once

#include "dot/Graph.hpp"
#include "dot/TableNode.hpp"

namespace cppgraphviz {

template<typename Index>
class IndexedContainerSet;

namespace detail {

template<typename Index>
class RankdirGraphData : public dot::GraphData
{
 private:
  IndexedContainerSet<Index>* owner_;

  void set_rankdir(dot::RankDir rankdir) const final;

 public:
  void set_owner(IndexedContainerSet<Index>* owner)
  {
    owner_ = owner;
  }
};

template<typename Index>
class RankdirGraph : public dot::GraphTemplate<RankdirGraphData<Index>>
{
 public:
  void set_owner(IndexedContainerSet<Index>* owner)
  {
    this->data().set_owner(owner);
  }
};

} // namespace detail

// A cluster graph containing one or more indexed containers that use Index as index type.
template<typename Index>
class IndexedContainerSet
{
 public:
  using data_type = dot::GraphData;

 private:
  detail::RankdirGraph<Index> outer_subgraph_;  // This subgraph wraps the inner subgraph.
  dot::Graph inner_subgraph_;                   // This subgraph contains the dot::TableNode's that represent the indexed containers.

 private:
  void initialize()
  {
    outer_subgraph_.add_attribute({"cluster", "true"});
    outer_subgraph_.add_attribute({"style", "rounded"});
    outer_subgraph_.add_attribute({"color", "lightblue"});
    outer_subgraph_.add_graph(inner_subgraph_);
    inner_subgraph_.add_attribute({"cluster", "false"});
    // We have to assume the default rankdir=TB and will adjust if set_rankdir is called with LR or RL.
    inner_subgraph_.add_attribute({"rank", "same"});
    outer_subgraph_.set_owner(this);
  }

 public:
  IndexedContainerSet() { initialize(); }
  IndexedContainerSet(std::string const& label) { initialize(); set_label(label); }

  void set_label(std::string const& label)
  {
    outer_subgraph_.add_attribute({"label", label});
  }

  template<dot::ConceptIsTableNodeData TND>
  void add_container(dot::TableNodeTemplate<TND> const& container)
  {
    inner_subgraph_.add_table_node(container);
  }

  template<dot::ConceptIsTableNodeData TND>
  void add_container(dot::TableNodeTemplate<TND>&& container)
  {
    inner_subgraph_.add_table_node(std::move(container));
  }

  void add_to_graph(dot::GraphData& graph_data);

  void rankdir_changed(dot::RankDir new_rankdir)
  {
    dot::RankDir old_rankdir = outer_subgraph_.get_rankdir();
    bool old_is_vertical = old_rankdir == dot::TB || old_rankdir == dot::BT;
    bool new_is_vertical = new_rankdir == dot::TB || new_rankdir == dot::BT;
    if (old_is_vertical != new_is_vertical)
    {
      if (new_is_vertical)
        inner_subgraph_.add_attribute({"rank", "same"});
      else
        inner_subgraph_.attribute_list().remove("rank");
    }
  }
};

template<typename Index>
void IndexedContainerSet<Index>::add_to_graph(dot::GraphData& graph_data)
{
  graph_data.add_graph(outer_subgraph_);
}

namespace detail {

template<typename Index>
void RankdirGraphData<Index>::set_rankdir(dot::RankDir rankdir) const
{
  owner_->rankdir_changed(rankdir);
  dot::GraphData::set_rankdir(rankdir);
}

} // namespace detail

} // namespace cppgraphviz
