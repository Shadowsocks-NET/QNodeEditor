#pragma once

#include <nodes/NodeData>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class DecimalData : public NodeData
{
public:

  DecimalData()
    : _number(0.0),
      _isValid(false)
  {}

  DecimalData(double number)
    : _number(number),
      _isValid(true)
  {}

  NodeDataType type() const override
  {
    return NodeDataType {"decimal",
                         "Decimal"};
  }

  double number() const
  { return _number; }

  QString numberAsText() const
  { return QString::number(_number, 'f'); }

  bool isValid() const
  { return _isValid; }

private:

  double _number;
  bool _isValid;
};


