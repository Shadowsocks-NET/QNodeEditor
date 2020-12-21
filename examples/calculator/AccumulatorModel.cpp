#include "AccumulatorModel.hpp"

#include "DecimalData.hpp"

QString
AccumulatorModel::
portCaption(QtNodes::PortType portType, QtNodes::PortIndex) const
{
  if(portType == PortType::In && _input.size() > 0)
  {
      return QString("Decimals (%1)").arg(_input.size());
  }

  return QStringLiteral("Decimal");
}

QtNodes::NodeDataType AccumulatorModel::dataType(QtNodes::PortType, QtNodes::PortIndex) const
{
  return DecimalData().type();
}

std::shared_ptr<QtNodes::NodeData> AccumulatorModel::outData(QtNodes::PortIndex)
{
  return _result;
}

void
AccumulatorModel::
  setInData(std::vector<std::shared_ptr<QtNodes::NodeData>> data, QtNodes::PortIndex)
{
  _input.clear();
  _input.reserve(data.size());
  for (auto& node : data)
  {
    std::shared_ptr<DecimalData> decimalData = std::dynamic_pointer_cast<DecimalData>(node);
    _input.push_back(decimalData);
  }

  compute();
}

void
AccumulatorModel::
compute()
{
  double result = 0.0f;
  int counter = 0;
  for (auto& node : _input)
  {
    std::shared_ptr<DecimalData> locked = node.lock();
    if(locked && locked->isValid())
    {
      result += locked->number();
      ++counter;
    }
  }

  if(counter > 0)
  {
    modelValidationState = NodeValidationState::Valid;
    _result = std::make_shared<DecimalData>(result);
  }
  else
  {
    modelValidationState = NodeValidationState::Warning;
    _result = std::make_shared<DecimalData>();
  }

  Q_EMIT dataUpdated(0);
}
