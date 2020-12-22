#include "Converters.hpp"

#include <QDoubleValidator>

std::shared_ptr<NodeData>
DecimalToIntegerConverter::
operator()(std::shared_ptr<NodeData> data)
{
  auto numberData = std::dynamic_pointer_cast<DecimalData>(data);
  if (numberData && numberData->isValid())
  {
    _integer = std::make_shared<IntegerData>(numberData->number());
  }
  else
  {
    _integer = std::make_shared<IntegerData>();
  }

  return _integer;
}


std::shared_ptr<NodeData>
IntegerToDecimalConverter::
operator()(std::shared_ptr<NodeData> data)
{
  auto numberData = std::dynamic_pointer_cast<IntegerData>(data);
  if (numberData && numberData->isValid())
  {
    _decimal = std::make_shared<DecimalData>(numberData->number());
  }
  else
  {
    _decimal = std::make_shared<DecimalData>();
  }

  return _decimal;
}
