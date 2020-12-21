#pragma once

#include <nodes/NodeData>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class IntegerData : public NodeData
{
public:

  IntegerData()
    : _number(0),
      _isValid(false)
  {}

  IntegerData(int number)
    : _number(number),
       _isValid(true)
  {}

  NodeDataType type() const override
  {
    return NodeDataType {"integer",
                         "Integer"};
  }

  int number() const
  { return _number; }

  QString numberAsText() const
  { return QString::number(_number); }

  bool isValid() const
  { return _isValid; }

private:

  int _number;
  int _isValid;
};
