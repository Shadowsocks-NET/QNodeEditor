#pragma once

#include <nodes/NodeDataModel>

#include "IntegerData.hpp"

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

class IntegerData;

class ModuloModel : public NodeDataModel
{
  Q_OBJECT

public:
   ModuloModel();

public:

  QString
  caption() const override
  { return QStringLiteral("Modulo"); }

  bool
  captionVisible() const override
  { return true; }

  bool
  portCaptionVisible(PortType, PortIndex ) const override
  { return true; }

  QString
  portCaption(PortType portType, PortIndex portIndex) const override;

  QString
  name() const override
  { return QStringLiteral("Modulo"); }

public:

  QJsonObject
  save() const override;

public:

  unsigned int
  nPorts(PortType portType) const override;

  NodeDataType
  dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData>
  outData(PortIndex port) override;

  void
  setInData(std::shared_ptr<NodeData>, int) override;

  QWidget *
  embeddedWidget() override
  { return nullptr; }

  NodeValidationState
  validationState() const override;

  QString
  validationMessage() const override;

private:

  void
  compute();

private:

  std::weak_ptr<IntegerData> _number1;
  std::weak_ptr<IntegerData> _number2;

  std::shared_ptr<IntegerData> _result;

  NodeValidationState modelValidationState = NodeValidationState::Warning;
  QString modelValidationError = QStringLiteral("Missing or incorrect inputs");
};
