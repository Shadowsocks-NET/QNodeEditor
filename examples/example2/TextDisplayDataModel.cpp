#include "TextDisplayDataModel.hpp"

TextDisplayDataModel::
TextDisplayDataModel()
  : _label(nullptr)
{
}


unsigned int
TextDisplayDataModel::
nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 1;
      break;

    case PortType::Out:
      result = 0;

    default:
      break;
  }

  return result;
}


NodeDataType
TextDisplayDataModel::
dataType(PortType, PortIndex) const
{
  return TextData().type();
}


std::shared_ptr<NodeData>
TextDisplayDataModel::
outData(PortIndex)
{
  std::shared_ptr<NodeData> ptr;
  return ptr;
}

void TextDisplayDataModel::setInData(std::shared_ptr<QtNodes::NodeData> data, int)
{
  auto textData = std::dynamic_pointer_cast<TextData>(data);

  if (textData)
  {
     Q_EMIT updateLabel(textData->text());
  }
  else
  {
    Q_EMIT updateLabel("");
  }
}

QWidget*
TextDisplayDataModel::
embeddedWidget()
{
   if (!_label)
   {
      _label = new QLabel();
      _label->setMargin(3);
      connect(this, &TextDisplayDataModel::updateLabel,
              _label, [this](const QString& text){
                 _label->setText(text);
                 _label->adjustSize();
              });
   }

   return _label;
}
