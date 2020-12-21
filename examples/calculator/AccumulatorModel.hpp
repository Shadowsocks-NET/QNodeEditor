#pragma once

#include <nodes/NodeDataModel>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

class DecimalData;

// This model show how to use an input port with ConnectionPolicy::Many
// Multiple output port can be connected to the same input port here
class AccumulatorModel : public NodeDataModel
{
public:

  QString
  caption() const override
  { return QStringLiteral("Accumulator"); }

  QString
  name() const override
  { return QStringLiteral("Accumulator"); }

  bool
  portCaptionVisible(PortType, PortIndex) const override
  { return true; }

  QString
  portCaption(PortType portType, PortIndex portIndex) const override;

  unsigned int
  nPorts(PortType) const override
  { return 1; }

  NodeDataType
  dataType(PortType, PortIndex) const override;

  std::shared_ptr<NodeData>
  outData(PortIndex) override;

  void
  setInData(std::shared_ptr<NodeData>, PortIndex) override
  {}

  void
  setInData(std::vector<std::shared_ptr<NodeData> > data, PortIndex portIndex) override;

  QWidget *
  embeddedWidget() override
  { return nullptr; }

  NodeValidationState
  validationState() const override
  { return modelValidationState; }

  QString
  validationMessage() const override
  { return modelValidationError; }

  ConnectionPolicy
  portInConnectionPolicy(PortIndex) const override
  { return ConnectionPolicy::Many; }

private:

  void
  compute();

  private:

  std::vector<std::weak_ptr<DecimalData> > _input;

  std::shared_ptr<DecimalData> _result;

  NodeValidationState modelValidationState = NodeValidationState::Warning;
  QString modelValidationError = QString("Missing or incorrect inputs");
};
