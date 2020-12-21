#pragma once

#include <nodes/TypeConverter>

#include "DecimalData.hpp"
#include "IntegerData.hpp"

using QtNodes::NodeData;
using QtNodes::NodeDataType;

class DecimalToIntegerConverter
{

public:

  std::shared_ptr<NodeData>
  operator()(std::shared_ptr<NodeData> data);

private:

  std::shared_ptr<NodeData> _integer;
};


class IntegerToDecimalConverter
{

public:

  std::shared_ptr<NodeData>
  operator()(std::shared_ptr<NodeData> data);

private:

  std::shared_ptr<NodeData> _decimal;
};
