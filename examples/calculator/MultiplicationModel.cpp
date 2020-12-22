#include "MultiplicationModel.hpp"

#include "DecimalData.hpp"

void MultiplicationModel::compute()
{
  PortIndex const outPortIndex = 0;

  auto n1 = _number1.lock();
  auto n2 = _number2.lock();

  if (n1 && n2 && n1->isValid() && n2->isValid())
  {
    setValidState();
    _result = std::make_shared<DecimalData>(n1->number() * n2->number());
  }
  else
  {
    setWarningState();
    _result = std::make_shared<DecimalData>();
  }

  Q_EMIT dataUpdated(outPortIndex);
}
