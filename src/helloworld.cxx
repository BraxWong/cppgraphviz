#include "sys.h"
#include "debug.h"
#include "cppgraphviz/Graph.hpp"
#include "cppgraphviz/Node.hpp"
#include "cppgraphviz/Edge.hpp"
#include <utils/Vector.h>
#include <iostream>

struct A : cppgraphviz::Node
{
  int m_;

  A(int m) : m_(m) { }
};

using AIndex = utils::VectorIndex<A>;

int main()
{
  Debug(NAMESPACE_DEBUG::init());

  cppgraphviz::Digraph g0;
  cppgraphviz::Node n;

  g0.add_node(n);

  n.add_attribute({"style", "filled"});
  n.add_attribute({"fillcolor", "green"});
  n.add_attribute({"shape", "hexagon"});

  cppgraphviz::Node n2;
  n2.add_attribute({"label", "n2"});
  cppgraphviz::Edge e1(n, n);
  cppgraphviz::Edge e2(n2, n);

  g0.add_edge(e1);
  g0.add_edge(e2);

  e1.add_attribute({"label", "e1"});
  e2.add_attribute({"label", "e2"});
  n.add_attribute({"label", "n"});

  g0.add_node(n2);

  cppgraphviz::Node n10;
  n10.add_attribute({"label", "n10"});

  cppgraphviz::Node n11;
  n11.add_attribute({"label", "n11"});

  cppgraphviz::Edge e3(n10, n11);
  e3.add_attribute({"label", "e3"});

  cppgraphviz::Graph g1;
  g1.add_attribute({"label", "g1"});
  g1.add_node(n10);
  g1.add_node(n11);
  g1.add_edge(e3);

  g0.add_graph(g1);
  cppgraphviz::Edge e4;
  g0.add_edge(e4);
  e4.set_nodes(n2, n10);

  // node [style="filled", fillcolor="white"]
  g0.add_node_attribute({"style", "filled"});
  g0.add_node_attribute({"fillcolor", "white"});
  // graph [label="g1", style="rounded", fillcolor="white", bgcolor="lightgrey"]
  g1.add_attribute({"style", "rounded"});
  g1.add_attribute({"fillcolor", "gray"});
  g1.add_attribute({"bgcolor", "lightgrey"});

  utils::Vector<A, AIndex> v1 = { {3}, {4}, {5} };
  g0.add_table(v1);

  g0.write_dot(std::cout);
}
