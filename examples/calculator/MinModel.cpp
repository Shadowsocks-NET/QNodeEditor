#include "MinModel.hpp"


unsigned int
MinModel::
nPorts(QtNodes::PortType portType) const
{
   if (portType == PortType::In)
      return _numberList.size()+1;
   else
      return 1;
}

bool
MinModel::
hasDynamicPorts(QtNodes::PortType portType) const
{
  if(portType == PortType::In)
    return true;

  return false;
}

QtNodes::NodeDataType
MinModel::
dataType(QtNodes::PortType, QtNodes::PortIndex) const
{
  return DecimalData().type();
}

std::shared_ptr<QtNodes::NodeData>
MinModel::
outData(QtNodes::PortIndex)
{
  return _result;
}

void
MinModel::
setInData(std::shared_ptr<QtNodes::NodeData> data, QtNodes::PortIndex portIndex)
{
  if (auto numberData = std::dynamic_pointer_cast<DecimalData>(data))
  {
    if (portIndex == static_cast<int>(_numberList.size()))
    {
      _numberList.push_back(numberData);
      Q_EMIT portAdded(PortType::In, _numberList.size());
    }
    else
    {
      _numberList[portIndex] = numberData;
    }
  }
  else
  {
     if(portIndex < static_cast<int>(_numberList.size()))
    {
      _numberList.erase(_numberList.begin() + portIndex);
      Q_EMIT portRemoved(PortType::In, portIndex);
    }
  }

  compute();
}

QString
MinModel::
caption() const
{
  return QStringLiteral("Min");
}

bool
MinModel::
portCaptionVisible(QtNodes::PortType, QtNodes::PortIndex) const
{
  return true;
}

QString
MinModel::
portCaption(QtNodes::PortType portType, QtNodes::PortIndex) const
{
  switch (portType)
  {
    case PortType::In:
      return QStringLiteral("Decimal");

    case PortType::Out:
      return QStringLiteral("Result");

    default:
      break;
  }
  return QString();
}

QString
MinModel::
name() const
{
   return QStringLiteral("Min");
}

QtNodes::NodeValidationState
MinModel::
validationState() const
{
  return _modelValidationState;
}

QString
MinModel::
validationMessage() const
{
  return _modelValidationError;
}

void
MinModel::
compute()
{
  if(_numberList.size() > 0)
  {
    _modelValidationState = NodeValidationState::Valid;
    _modelValidationError = "";
  }
  else
  {
    _modelValidationState = NodeValidationState::Warning;
    _modelValidationError = QString("Missing or incorrect inputs");
  }

  std::vector<double> numbers;
  numbers.reserve(_numberList.size());

  for (auto& portData : _numberList)
  {
    auto num = portData.lock();
    if (num && num->isValid())
    {
      numbers.emplace_back(num->number());
    }
  }

  if(!numbers.empty())
    _result = std::make_shared<DecimalData>(*std::min_element(numbers.begin(), numbers.end()));
  else
    _result = std::make_shared<DecimalData>();

  Q_EMIT dataUpdated(0);
}

void
MinModel::
restore(const QJsonObject& obj)
{
   int in = obj["dynamic_inputs"].toInt();
   if(in > 0){
     // since when node is saved port's number is size+1 with an empty port
     // to restore the correct size of the array it has to be input-1
      _numberList.resize(in-1);
   }
}
