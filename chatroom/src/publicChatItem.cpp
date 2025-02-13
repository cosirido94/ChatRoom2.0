#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../include/publicChatItem.h"

PublicChatItem ::PublicChatItem(QWidget *parent)
    : ChatItem("#public" , parent)
{
    /**  Creazione della label #public  **/

    userNameLabel = new ClickLabel(this);
    userNameLabel->setText(chatId);

    /* Il widget non si adatta alle dimensioni del contenitore
     * ne in altezza ne in lunghezza ->setStylePolicy(Fixed,Fixed) */
    userNameLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


    userNameLabel->setStyleSheet("font-weight: bold;"
                                 "color: black;"
                                 "font-size:16px;");

    /** Creazione del contatore di messaggi non letti chat pubblica  **/
    unreadMessageCountLabel = new QLabel("0", this);

    /* Calcolo della dimensione di unread (rettangolo)
     * all'inizializzazione di "0" */

    QString countText = "0";
    int badgeWidth = 30 + (countText.length() - 1) * 10;  // Inizia con 30px e aggiunge 10px per ogni cifra in più
    unreadMessageCountLabel->setFixedSize(badgeWidth, 25);
    unreadMessageCountLabel->setText(countText);

    /* Queste righe ci serviranno dopo
     * QString countText = (0 > 999) ? "999+" : QString::number(0);
     * unreadMessageCountLabel->setText(countText); */

    unreadMessageCountLabel->setStyleSheet(
            "background-color: blue;"
            "color: white;"
            "border-radius: 12px;"
            "font-weight: bold;"
            "font-size: 16px;"
            "padding: 2px;"
    );

    /* Serve per centrare il numero dentro al rettangolo */
    unreadMessageCountLabel->setAlignment(Qt::AlignCenter);

    /** Creazione del contenitore (QWidget) che conterrà #public e #unread **/
    QWidget *container = new QWidget(this);

    /** Creo il layout per i 2 widget e lo associo al container
     * Quando verranno aggiunti #public e unread questi diventeranno
     * figli di container e il layout gestirà il loro posizionamento **/
    QHBoxLayout *layout = new QHBoxLayout(container);

    /* Imposto una larghezza fissa perchè sennò l'allineamento tra gli widget
     * viene sballato e la distanza non di 20px tra loro perchè ha prende più spazio tra
     * loro (perchè lo trova) del dovuto */
    container->setFixedWidth(180);
    container->setStyleSheet("");

    /* Serve per posizionare #public a distanza 10px da sinistra mettendo un margin left */
    layout->setContentsMargins(10, 0, 0, 0); // Margine sinistro di 15px

    /* Imposta la distanza tra i 2 widget: 20px */
    layout->setSpacing(20);

    /* Aggiunta widget al layout -> devo mettere AlignLeft per allinearli a sinistra */
    layout->addWidget(userNameLabel,0, Qt::AlignLeft);
    layout->addWidget(unreadMessageCountLabel,0,Qt::AlignLeft);

    /** Creo layout principale per gestire container e il tutto correttamente **/
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0); // Margini esterni del widget ChatItem
    mainLayout->addWidget(container);

    setLayout(mainLayout);
}
