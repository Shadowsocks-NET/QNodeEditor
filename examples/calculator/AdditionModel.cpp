#include "AdditionModel.hpp"

#include "DecimalData.hpp"

void
AdditionModel::
compute()
{
  auto n1 = _number1.lock();
  auto n2 = _number2.lock();

  if (n1 && n2)
  {
    setValidState();
    _result = std::make_shared<DecimalData>(n1->number() + n2->number());
  }
  else
  {
    setWarningState();
    _result = std::make_shared<DecimalData>();
  }

  Q_EMIT dataUpdated(0);
}


