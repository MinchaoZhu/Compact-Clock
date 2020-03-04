/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QtGui>
#include <QTextCodec>
#include <QSettings>
#include "rasterwindow.h"

//! [5]
class AnalogClockWindow : public RasterWindow
{
public:
    AnalogClockWindow();

protected:
    void timerEvent(QTimerEvent *) override;
    void render(QPainter *p) override;
    void keyPressEvent(QKeyEvent *) override;

private:
    int m_timerId;
    float scale = 1.0;
    int up = 0;
    int right = 0;
    int isFrameless = false;
};
//! [5]


void AnalogClockWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_F11)
    {
        if(this->isFrameless == false){
            this->setFlag(Qt::FramelessWindowHint);
            this->isFrameless = true;
        }
        else{
            this->setFlag(Qt::FramelessWindowHint, false);
            this->isFrameless = false;
        }
    }
    if(event->key() == Qt::Key_Equal){
        scale += 0.05;
        renderNow();
    }
    if(event->key() == Qt::Key_Minus){
        scale -= 0.05;
        renderNow();
    }
    if(event->key() == Qt::Key_Left){
        up -= 5;
        renderNow();
    }
    if(event->key() == Qt::Key_Right){
        up += 5;
        renderNow();
    }
    if(event->key() == Qt::Key_Up){
        right -= 5;
        renderNow();
    }
    if(event->key() == Qt::Key_Down){
        right += 5;
        renderNow();
    }

}

//! [6]
AnalogClockWindow::AnalogClockWindow()
{
    setTitle("Pig Clock");
    resize(480, 270);
    QSettings *iniObject = new QSettings("setting.ini", QSettings::IniFormat);
    scale = iniObject->value("/setting/scale").toFloat();
    up = iniObject->value("/setting/up").toInt();
    right = iniObject->value("/setting/right").toInt();
    m_timerId = startTimer(1000);
}
//! [6]

//! [7]
void AnalogClockWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timerId)
        renderLater();
}
//! [7]


//! [1] //! [14]
void AnalogClockWindow::render(QPainter *p)
{

    QSettings *iniObject = new QSettings("setting.ini", QSettings::IniFormat);
    iniObject->setValue("/setting/scale", QString::number(up));
    iniObject->setValue("/setting/scale", QString::number(right));
    iniObject->setValue("/setting/scale", QString::number(scale));
    float side = qMin((width()*1.0)/480.0, (height()*1.0)/270.0);
    side *= scale;
    p->scale(side, side);
    QFont font1("SimHei", 50, QFont::Bold, false);
    p->setFont(font1);
    p->setPen(QColor("#FFFFFF"));
    QTime ct = QTime::currentTime();
    QString outTime = "";

    outTime += ct.toString("h:mm:ss ap");

    p->drawText(up + 15, right + 140, outTime);
    QFont font2("SimHei", 8, QFont::Bold, false);
    p->setFont(font2);
    p->drawText(up + 350, right + 250, "开发: 猪猪超");


    QDate qd = QDate::currentDate();
    QFont font3("SimHei", 20, QFont::Bold, false);
    p->setFont(font3);
    p->drawText(up + 114, right + 50, qd.toString("yyyy.MM.dd dddd"));



}

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    AnalogClockWindow clock;
    clock.show();

    return app.exec();
}
