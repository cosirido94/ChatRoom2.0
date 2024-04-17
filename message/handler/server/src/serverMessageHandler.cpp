#include "../include/serverMessageHandler.h"


//QMap<int,QString> MessageHandler::headers =
//{
//    {1 , "NEW_USER"},
//    {2,"USER_COLOR"},
//    {3,"NICKNAME_NOT_AVAILABLE"}
//};
//
//QString MessageHandler::addHeader(const QString message, int opcode)
//{
//    if (headers.contains(opcode))
//    {
//        QString header = "<" + headers[opcode] + ">";
//        return header + message;
//    }
//    else
//    {
//        return message;
//    }
//}
//
//QString MessageHandler::extractHeader(const QString& message)
//{
//    int endIndex = message.indexOf('>');
//    if (endIndex != -1 )
//    {
//        QString header = message.mid(1 , endIndex -1);
//
//        if( headers.values().contains(header) )
//        {
//            return header;
//        }
//    }
//    return QString();
//}
//
//QString MessageHandler::extractMessage(const QString message)
//{
//    int startIndex = message.indexOf('>') + 1; // Ottieni l'indice del carattere '>' e aggiungi 1 per ottenere l'indice del primo carattere dopo '>'
//
//    if (startIndex >= 1 && startIndex < message.length()) {
//        return message.mid(startIndex);
//    }
//
//    return QString();
//}

