#include "TextSourceDataModel.hpp"

TextSourceDataModel::
TextSourceDataModel()
   : _text("Default Text"),
     _lineEdit(nullptr)
{
}

unsigned int
TextSourceDataModel::
nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 0;
      break;

    case PortType::Out:
      result = 1;

    default:
      break;
  }

  return result;
}


void
TextSourceDataModel::
onTextEdited(QString const &string)
{
  _text = string;

  Q_EMIT dataUpdated(0);
}


NodeDataType
TextSourceDataModel::
dataType(PortType, PortIndex) const
{
  return TextData().type();
}


std::shared_ptr<NodeData>
TextSourceDataModel::
outData(PortIndex)
{
  return std::make_shared<TextData>(_text);
}

QWidget* TextSourceDataModel::embeddedWidget()
{
   if(!_lineEdit)
   {
     _lineEdit = new QLineEdit(_text);

     connect(_lineEdit, &QLineEdit::textEdited,
             this, &TextSourceDataModel::onTextEdited);
   }

   return _lineEdit;
}
