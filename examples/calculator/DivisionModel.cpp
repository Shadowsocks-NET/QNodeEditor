#include "DivisionModel.hpp"

#include "DecimalData.hpp"

QString
DivisionModel::
portCaption(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const
{
  switch (portType)
  {
  case PortType::In:
    if (portIndex == 0)
      return QStringLiteral("Dividend");
    else if (portIndex == 1)
      return QStringLiteral("Divisor");

    break;

  case PortType::Out:
    return QStringLiteral("Result");

  default:
    break;
  }
  return QString();
}

void
DivisionModel::
compute()
{
  auto n1 = _number1.lock();
  auto n2 = _number2.lock();

  if (n1 && n2 && n1->isValid() && n2->isValid())
  {
    if(n2->number() == 0.0)
    {
      setErrorState("Division by zero error");
      _result = std::make_shared<DecimalData>();
    }
    else
    {
      setValidState();
      _result = std::make_shared<DecimalData>(n1->number() /  n2->number());
    }
  }
  else
  {
    setWarningState();
    _result = std::make_shared<DecimalData>();
  }

  Q_EMIT dataUpdated(0);
}
