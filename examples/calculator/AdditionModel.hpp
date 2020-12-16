#pragma once

#include <QtCore/QObject>

#include <QtWidgets/QLabel>

#include <nodes/NodeDataModel>

#include "MathOperationDataModel.hpp"
#include "DecimalData.hpp"

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class AdditionModel : public MathOperationDataModel
{
public:

  virtual
  ~AdditionModel() {}

public:

  QString
  caption() const override
  { return QStringLiteral("Addition"); }

  QString
  name() const override
  { return QStringLiteral("Addition"); }

private:

  void
  compute() override
  {
    PortIndex const outPortIndex = 0;

    auto n1 = _number1.lock();
    auto n2 = _number2.lock();

    if (n1 && n2)
    {
      modelValidationState = NodeValidationState::Valid;
      modelValidationError = QString();
      _result = std::make_shared<DecimalData>(n1->number() +
                                              n2->number());
    }
    else
    {
      modelValidationState = NodeValidationState::Warning;
      modelValidationError = QStringLiteral("Missing or incorrect inputs");
      _result.reset();
    }

    Q_EMIT dataUpdated(outPortIndex);
  }
};

class MultiAdditionModel : public NodeDataModel
{
public:
  QString
  caption() const override
  { return QStringLiteral("Multi Addition"); }

  QString
  name() const override
  { return QStringLiteral("Multi Addition"); }

  bool
  portCaptionVisible(PortType portType, PortIndex portIndex) const override
  {
    Q_UNUSED(portType); Q_UNUSED(portIndex);
    return true;
  }

  QString
  portCaption(PortType portType, PortIndex portIndex) const override
  {
    Q_UNUSED(portIndex);

    if(portType == PortType::In && _input.size() > 0)
    {
       return QString("Decimals (%1)").arg(_input.size());
    }

    return QStringLiteral("Decimal");
  }

  unsigned int
  nPorts(PortType portType) const override
  {
    Q_UNUSED(portType);
    return 1;
  }

  NodeDataType
  dataType(PortType portType,
           PortIndex portIndex) const override
  {
    Q_UNUSED(portType); Q_UNUSED(portIndex);
    return DecimalData().type();
  }

  std::shared_ptr<NodeData>
  outData(PortIndex portIndex) override
  {
    Q_UNUSED(portIndex);
    return _result;
  }

  void
  setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) override
  { Q_UNUSED(data); Q_UNUSED(portIndex); }

  void
  setInData(std::vector<std::shared_ptr<NodeData> > data, PortIndex portIndex) override
  {
     Q_UNUSED(portIndex);

    _input.clear();
    _input.reserve(data.size());
    for (auto& node : data)
    {
      std::shared_ptr<DecimalData> decimalData = std::dynamic_pointer_cast<DecimalData>(node);
      _input.push_back(decimalData);
    }

    if (_input.empty())
    {
      modelValidationState = NodeValidationState::Warning;
    }
    else
    {
      modelValidationState = NodeValidationState::Valid;
    }

    double result = 0.0f;
    int counter = 0;
    for (auto& node : _input)
    {
      if(std::shared_ptr<DecimalData> locked = node.lock())
      {
        result += locked->number();
        ++counter;
      }
    }

    if(counter > 0)
    {
      _result = std::make_shared<DecimalData>(result);
    }
    else
    {
       _result.reset();
    }

    Q_EMIT dataUpdated(0);
  }

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
  std::vector<std::weak_ptr<DecimalData> > _input;

  std::shared_ptr<DecimalData> _result;

  NodeValidationState modelValidationState = NodeValidationState::Warning;
  QString modelValidationError = QString("Missing or incorrect inputs");
};
