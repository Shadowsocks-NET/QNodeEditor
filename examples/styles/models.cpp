#include "models.hpp"

QString
MyDataModel::
caption() const
{
  return QString("My Data Model");
}

QString
MyDataModel::
name() const
{
  return QString("MyDataModel");
}

QJsonObject
MyDataModel::
save() const
{
  QJsonObject modelJson;

  modelJson["name"] = name();

  return modelJson;
}

unsigned int
MyDataModel::
nPorts(QtNodes::PortType) const
{
  return 3;
}

QtNodes::NodeDataType
MyDataModel::
dataType(QtNodes::PortType, QtNodes::PortIndex) const
{
  return MyNodeData().type();
}

std::shared_ptr<QtNodes::NodeData>
MyDataModel::
outData(QtNodes::PortIndex)
{
  return std::make_shared<MyNodeData>();
}

void
MyDataModel::
setInData(std::shared_ptr<QtNodes::NodeData>, PortIndex)
{
}

QWidget*
MyDataModel::
embeddedWidget()
{
  return nullptr;
}
