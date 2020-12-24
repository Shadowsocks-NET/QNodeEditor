#pragma once

#include <nodes/NodeDataModel>

#include <memory>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class MyNodeData : public NodeData
{
public:

  NodeDataType
  type() const override
  { return NodeDataType {"MyNodeData", "My Node Data"}; }
};

//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class MyDataModel : public NodeDataModel
{
  Q_OBJECT

public:

  QString
  caption() const override;

  QString
  name() const override;

public:

  QJsonObject
  save() const override;

public:

  unsigned int
  nPorts(PortType) const override;

  NodeDataType
  dataType(PortType, PortIndex) const override;

  std::shared_ptr<NodeData>
  outData(PortIndex) override;

  void
  setInData(std::shared_ptr<NodeData>, int) override;

  QWidget *
  embeddedWidget() override;
};
