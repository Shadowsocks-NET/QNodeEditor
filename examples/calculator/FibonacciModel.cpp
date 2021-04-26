#include "FibonacciModel.hpp"

#include <nodes/Connection>

int fibo(int n)
{
   if(n<=1) return 1;

   int fibo = 0;
   int fibo1 = 1;
   int fibo2 = 1;
   int i = 1;

   while (i<n) {
      fibo = fibo1 + fibo2;
      ++i;
      fibo2 = fibo1;
      fibo1 = fibo;
   }

   return fibo;
}

FibonacciModel::FibonacciModel()
   : NodeDataModel(),
     _indexCounter(1)
{
}

unsigned int
FibonacciModel::
   nPorts(QtNodes::PortType portType) const
{
   if (portType == PortType::In)
      return 0;
   else
      return std::max(1, _indexCounter);
}

bool
FibonacciModel::
   hasDynamicPorts(QtNodes::PortType portType) const
{
   if(portType == PortType::Out)
      return true;

   return false;
}

QtNodes::NodeDataType
FibonacciModel::
   dataType(QtNodes::PortType, QtNodes::PortIndex) const
{
   return DecimalData().type();
}

std::shared_ptr<QtNodes::NodeData>
FibonacciModel::
   outData(QtNodes::PortIndex port)
{
   return std::make_shared<DecimalData>(fibo(port));
}

void
FibonacciModel::
   setInData(std::shared_ptr<QtNodes::NodeData>, QtNodes::PortIndex)
{
}

QString
FibonacciModel::
   caption() const
{
   return QStringLiteral("Fibonacci");
}

bool
FibonacciModel::
   portCaptionVisible(QtNodes::PortType, QtNodes::PortIndex) const
{
   return true;
}

QString
FibonacciModel::
   portCaption(QtNodes::PortType, QtNodes::PortIndex portIndex) const
{
   return QString("Fibo %1").arg(portIndex);
}

QString
FibonacciModel::
   name() const
{
   return QStringLiteral("Fibonacci");
}

QtNodes::NodeValidationState
FibonacciModel::
   validationState() const
{
   return _modelValidationState;
}

QString
FibonacciModel::
   validationMessage() const
{
   return _modelValidationError;
}

void FibonacciModel::restore(const QJsonObject& obj)
{
   int out = obj["dynamic_outputs"].toInt();
   if(out > 1){
      _indexCounter = out;
   }
}

void FibonacciModel::outputConnectionCreated(const QtNodes::Connection& c)
{
  auto outIndex = static_cast<int>(c.getPortIndex(QtNodes::PortType::Out));

  // Create a new port only if the last port is connected and the connection is completed
  if (outIndex == _indexCounter-1 && c.complete()){
    ++_indexCounter;
    Q_EMIT portAdded(PortType::Out, _indexCounter-1);
  }
}

void FibonacciModel::outputConnectionDeleted(const QtNodes::Connection& c)
{
   auto outIndex = static_cast<int>(c.getPortIndex(QtNodes::PortType::Out));

   // outIndex >= 0 ---> dynamic remove only for ports exceding 0
   // !c.complete() ---> port is removed only if connection is removed e and mouse released
   // outIndex != _indexCounter-1 --> if you start a connection from the last port but do not connect it
   // the connection is destroyed as incomplete, but the port must not be removed because that
   // port is already the last one

   if ((outIndex >= 0) && (!c.complete()) && (outIndex != _indexCounter-1)){
      Q_EMIT portRemoved(PortType::Out, outIndex);
      --_indexCounter;

      // Recalculate ports
      for(int i = outIndex; i<_indexCounter; ++i){
         Q_EMIT dataUpdated(i);
      }
   }
}
