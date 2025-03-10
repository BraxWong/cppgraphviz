#include "sys.h"
#include "Edge.hpp"
#include "Node.hpp"

namespace cppgraphviz::dot {

void EdgeData::set_nodes(Port const& from, Port const& to)
{
  from_ = from;
  to_ = to;
}

} // namespace cppgraphviz::dot
