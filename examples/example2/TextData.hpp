#pragma once

#include <nodes/NodeData>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class TextData : public NodeData
{
public:
  TextData() = default;

  TextData(QString const &text)
    : _text(text)
  {}

  NodeDataType type() const override
  { return NodeDataType {"text", "Text"}; }

  QString text() const { return _text; }

private:

  QString _text;
};
